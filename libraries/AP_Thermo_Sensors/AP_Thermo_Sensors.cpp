/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
/*
 *   APM_Thermo_Sensors.cpp - Thermopile Sensor drivers
 */

#include <AP_Math.h>
#include <AP_Common.h>
#include <AP_HAL.h>
#include <AP_Thermo_Sensors.h>

extern const AP_HAL::HAL& hal;

// table of user settable parameters
const AP_Param::GroupInfo AP_Thermo_Sensors::var_info[] PROGMEM = {

    // @Param: ENABLE
    // @DisplayName: Thermo Sensors enable
    // @Description: enable Thermo Sensors
    // @Values: 0:Disable,1:Enable
    AP_GROUPINFO("ENABLE",    0, AP_Thermo_Sensors, _enable, 1),

    // @Param: USE
    // @DisplayName: Thermo Sensors use
    // @Description: use Thermo Sensors for flight control
    // @Values: 1:Use,0:Don't Use
    AP_GROUPINFO("USE",    1, AP_Thermo_Sensors, _use, 0),

    // @Param: OFFSET
    // @DisplayName: Thermo Sensors offset
    // @Description: Thermo Sensors calibration offset
    // @Increment: 0.1
    AP_GROUPINFO("OFFSET", 2, AP_Thermo_Sensors, _offset, 0),

    // @Param: RATIO
    // @DisplayName: Thermo Sensors ratio
    // @Description: Thermo Sensors calibration ratio
    // @Increment: 0.1
    AP_GROUPINFO("RATIO",  3, AP_Thermo_Sensors, _ratio, 1.9936f),

    AP_GROUPEND
};

// calibrate the Thermo Sensors. This must be called at least once before
// the get_thermo_sensors() interface can be used
void AP_Thermo_Sensors::calibrate()
{
    Vector3f sum; 
    sum = Vector3f(0,0,0);

    uint8_t c;
    if (!_enable) {
        return;
    }
    _sourceX->read_average();
    _sourceY->read_average();
    _sourceZ->read_average();
    for (c = 0; c < 10; c++) {
        hal.scheduler->delay(100);
        sum.x += _sourceX->read_average();
        sum.y += _sourceY->read_average();
        sum.z += _sourceZ->read_average();
    }
    sum = sum/c;
    _offset.set(sum);
    _thermo_sensors = Vector3f(0,0,0);
    _enable = 1;
}

// read the Thermo Sensors
void AP_Thermo_Sensors::read(void)
{
    float thermo_sensors_measurementX;
    float thermo_sensors_measurementY;
    float thermo_sensors_measurementZ;
    bool  filter7030SQRT = 0;
    Vector3f ofs;
    ofs = _offset.get();
    
    if (!_enable) {  
	return;
    }

    _thermo_sensors_rawX           = _sourceX->read_average();
    _thermo_sensors_rawY           = _sourceY->read_average();
    _thermo_sensors_rawZ           = _sourceZ->read_average();

    
    if (filter7030SQRT) 
    { 
      thermo_sensors_measurementX     = max(_thermo_sensors_rawX - ofs.x, 0);
    	thermo_sensors_measurementY     = max(_thermo_sensors_rawY - ofs.y, 0);
    	thermo_sensors_measurementZ     = max(_thermo_sensors_rawZ - ofs.z, 0);
    	_thermo_sensors.x               = 0.7f * _thermo_sensors.x +
                                     0.3f * sqrtf(thermo_sensors_measurementX * _ratio);
    	_thermo_sensors.y               = 0.7f * _thermo_sensors.y +
                                     0.3f * sqrtf(thermo_sensors_measurementY * _ratio);
    	_thermo_sensors.z               = 0.7f * _thermo_sensors.z +
                                     0.3f * sqrtf(thermo_sensors_measurementZ * _ratio);
    }
    else 
    {
        _thermo_sensors.x = _thermo_sensors_rawX;
	_thermo_sensors.y = _thermo_sensors_rawY;
	_thermo_sensors.z = _thermo_sensors_rawZ;
    }
    
}

void AP_Thermo_Sensors::set_offsets(Vector3f offsets)
{
    _offset.set(offsets);
}

void AP_Thermo_Sensors::save_offsets()
{
    _offset.save();
}

Vector3f AP_Thermo_Sensors::get_offsets()
{
    return _offset;
}