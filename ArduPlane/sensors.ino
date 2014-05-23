// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

// filter altitude from the barometer with a low pass filter
static LowPassFilterInt32 altitude_filter;


static void init_barometer(void)
{
    gcs_send_text_P(SEVERITY_LOW, PSTR("Calibrating barometer"));    
    barometer.calibrate();

    // filter at 100ms sampling, with 0.7Hz cutoff frequency
    altitude_filter.set_cutoff_frequency(0.1, 0.7);

    gcs_send_text_P(SEVERITY_LOW, PSTR("barometer calibration complete"));
}

// read the barometer and return the updated altitude in centimeters
// above the calibration altitude
static int32_t read_barometer(void)
{
    barometer.read();
    if (should_log(MASK_LOG_IMU)) {
        Log_Write_Baro();
    }
    return altitude_filter.apply(barometer.get_altitude() * 100.0);
}

static void init_sonar(void)
{
#if CONFIG_HAL_BOARD == HAL_BOARD_APM1
    sonar.Init(&apm1_adc);
#else
    sonar.Init(NULL);
#endif
}

// read the sonars
static void read_sonars(void)
{
    if (!sonar.enabled()) {
        // this makes it possible to disable sonar at runtime
        return;
    }

    if (should_log(MASK_LOG_SONAR))
        Log_Write_Sonar();
}

/*
  ask airspeed sensor for a new value
 */
static void read_airspeed(void)
{
    if (airspeed.enabled()) {
        airspeed.read();
        if (should_log(MASK_LOG_IMU)) {
            Log_Write_Airspeed();
        }
        calc_airspeed_errors();
    }
}

static void zero_airspeed(void)
{
    airspeed.calibrate();
    gcs_send_text_P(SEVERITY_LOW,PSTR("zero airspeed calibrated"));
}

// read_battery - reads battery voltage and current and invokes failsafe
// should be called at 10hz
static void read_battery(void)
{
    battery.read();

    if (!usb_connected && battery.exhausted(g.fs_batt_voltage, g.fs_batt_mah)) {
        low_battery_event();
    }
}


// read the receiver RSSI as an 8 bit number for MAVLink
// RC_CHANNELS_SCALED message
void read_receiver_rssi(void)
{
    // avoid divide by zero
    if (g.rssi_range <= 0) {
        receiver_rssi = 0;
    }else{
        rssi_analog_source->set_pin(g.rssi_pin);
        float ret = rssi_analog_source->voltage_average() * 255 / g.rssi_range;
        receiver_rssi = constrain_int16(ret, 0, 255);
    }
}

/*
  return current_loc.alt adjusted for ALT_OFFSET
  This is useful during long flights to account for barometer changes
  from the GCS, or to adjust the flying height of a long mission
 */
static int32_t adjusted_altitude_cm(void)
{
    return current_loc.alt - (g.alt_offset*100);
}

// ************************************************************************************
// ************************************************************************************
// Added Thermo code from Ardupilot
// ************************************************************************************
// ************************************************************************************


void read_XY_sensors()
{  
        thermo_sensors.read();
        raw_thermo_reading_prev     = raw_thermo_reading;
        raw_thermo_reading          = thermo_sensors.get_thermo_sensors();
        thermopile.roll_sensor    = getRoll() + ROLL_TRIM;
        thermopile.pitch_sensor   = getPitch() + PITCH_TRIM;

  #if ENABLE_Z_SENSOR == 0
    if (raw_thermo_reading.y > 511){
      thermo_max = max((abs(511 - raw_thermo_reading.y) * THERMO_MAX_FIX), thermo_max);
      thermo_max = constrain(thermo_max, 40, 600);
      if(thermo_max > thermo_max_save){
                                // Not sure how necessary these two lines are
        //eeprom_busy_wait();
        //eeprom_write_word((uint16_t *)  EE_THERMO_MAX, thermo_max);  // thermo_max 
        //**************
                                thermo_max_save = thermo_max;
      }
    }
        #else
                read_z_sensor();
  #endif
}

void read_z_sensor(void)
{
  //Serial.print("thermo_max: ");
  //Serial.println(thermo_max,DEC);
  
  //Checks if the roll is less than 10 degrees to read z sensor
  if(abs(thermopile.roll_sensor) <= 1500){
    raw_thermo_reading.z = (raw_thermo_reading.z * 0.10) + (raw_thermo_reading_prev.z * .90);
    thermo_max = abs(511 - raw_thermo_reading.z) * THERMO_MAX_FIX;\
    thermo_max = fmin(fmax(thermo_max,40),600);
  }
}

// returns the sensor values as degrees of roll
//   0 ----- 511  ---- 1023    Thermo Sensor
// -90°       0         90°      degree output * 100
// sensors are limited to +- 60° (6000 when you multply by 100)

long getRoll(void)
{
  #if XY_SENSOR_LOCATION ==1
  return fmin(fmax((x_axis() + y_axis()) / 2,-6000),6000);
  #endif
  
  #if XY_SENSOR_LOCATION ==0
  return fmin(fmax((-x_axis() - y_axis()) / 2, -6000), 6000);
  #endif

  #if XY_SENSOR_LOCATION ==3
  return fmin(fmax((-x_axis() - y_axis()) / 2, -6000), 6000);
  #endif
  
  #if XY_SENSOR_LOCATION ==2
  return fmin(fmax((x_axis() + y_axis()) / 2, -6000), 6000);
  #endif
}

long getPitch(void)
{
  #if XY_SENSOR_LOCATION ==1
  return fmin(fmax((-x_axis() + y_axis()) / 2, -6000), 6000);
  #endif
  
  #if XY_SENSOR_LOCATION ==0
  return fmin(fmax((x_axis() - y_axis()) / 2, -6000), 6000);
  #endif

  #if XY_SENSOR_LOCATION ==3
  return fmin(fmax((-x_axis() + y_axis()) / 2, -6000), 6000);
  #endif
  
  #if XY_SENSOR_LOCATION ==2
  return fmin(fmax((x_axis() - y_axis()) / 2, -6000), 6000);
  #endif
}

long x_axis(void)// roll
{
  return ((raw_thermo_reading.x - 511l) * 9000l) / thermo_max;
  //      611 - 511 
  //         100 * 9000 / 100 = 90°  low = underestimate  = 36 looks like 90 = flat plane or bouncy plane
  //         100 * 9000 / 250 = 36°               = 36 looks like 36
  //       100 * 9000 / 500 = 18°  high = over estimate = 36 looks like 18 = crash plane
}

long y_axis(void)// pitch
{
  return ((raw_thermo_reading.y - 511l) * 9000l) / thermo_max;
}
/*

thermo sensor looks at the difference of the two readings and gives a value the same = 511
differnce is +=40°
(temp dif / 40) * 511
if the top sees the ground its the dif is positive or negative


Analog 0 = Pitch sensor
Analog 0 = Roll sensor - unmarked
     
                 ^ GROUND
    285          713
              P
       \      /
        \      /
        \  /
        511
        /  \
        /     \
      /      \
     P
    300        707
         ||||
        ||||
        ||||
       cable       
        
        
 */ 
