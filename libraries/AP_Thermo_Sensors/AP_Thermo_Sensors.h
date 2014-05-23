/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_THERMO_SENSORS_H__
#define __AP_THERMO_SENSORS_H__

#include <AP_Common.h>
#include <AP_HAL.h>
#include <AP_Param.h>

class AP_Thermo_Sensors
{
public:
    // constructor
    AP_Thermo_Sensors() 
    {
        AP_Param::setup_object_defaults(this, var_info);
    };

    void init(AP_HAL::AnalogSource *sourceX, AP_HAL::AnalogSource *sourceY, AP_HAL::AnalogSource *sourceZ) 
    {
        _sourceX = sourceX;
        _sourceY = sourceY;
        _sourceZ = sourceZ;
        _offset.set(Vector3f(0,0,0)); // remove existing gyro offsets
    }
    
    void     set_offsets(Vector3f offsets); 
    void     save_offsets();
    Vector3f get_offsets(); 

    // read the analog source and update _thermo_sensors
    void        read(void);

    // calibrate the thermo sensors. This must be called on startup
    void            calibrate();

    // return the current brightness
    Vector3f    get_thermo_sensors(void) 
    {
        return _thermo_sensors;
    }

    // return true if thermo sensors are enabled, and thermo sensors use is set
    bool use(void) 
    {
        Vector3f ofsck;
        ofsck = _offset.get();
        return _enable && _use && ofsck.x != 0 && ofsck.y != 0 && ofsck.z != 0;
    }

    // return true if thermo sensors are enabled
    bool enabled(void) 
    {
        return _enable;
    }

    static const struct AP_Param::GroupInfo var_info[];

private:
    AP_HAL::AnalogSource *_sourceX;
    AP_HAL::AnalogSource *_sourceY;
    AP_HAL::AnalogSource *_sourceZ;
    AP_Vector3f           _offset;
    AP_Float              _ratio;
    AP_Int8               _use;
    AP_Int8               _enable;
    Vector3f              _thermo_sensors;
    float                 _thermo_sensors_rawX;
    float                 _thermo_sensors_rawY;
    float                 _thermo_sensors_rawZ;
};


#endif // __AP_THERMO_SENSORS_H__
