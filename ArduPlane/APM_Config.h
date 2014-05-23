// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

// This file is just a placeholder for your configuration file.  If
// you wish to change any of the setup parameters from their default
// values, place the appropriate #define statements here.

// If you used to define your CONFIG_APM_HARDWARE setting here, it is no
// longer valid! You should switch to using CONFIG_HAL_BOARD via the HAL_BOARD
// flag in your local config.mk instead.

// The following are the recommended settings for Xplane
// simulation. Remove the leading "/* and trailing "*/" to enable:

//#define HIL_MODE            HIL_MODE_DISABLED

/*
 *  // HIL_MODE SELECTION
 *  //
 *  // Mavlink supports
 *  // 2. HIL_MODE_SENSORS: full sensor simulation
 *
 */
//Thermopile sensors:
#define ENABLE_Z_SENSOR 1      // 0 = no Z sensor, 1 = use Z sensor (no Z requires field calibration with each flight)
#define XY_SENSOR_LOCATION 0   // XY Thermopiles Sensor placement
                // Mounted right side up:  0 = cable in front, 1 = cable behind
                // Mounted upside down:   2 = cable in front, 3 = cable behind
#define PITCH_TRIM 0      // deg * 100 : allows you to offset bad IR sensor placement
#define ROLL_TRIM 0        // deg * 100 : allows you to offset bad IR sensor placement
#define THERMO_MAX_FIX .88 

