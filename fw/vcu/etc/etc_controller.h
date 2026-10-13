//
// Created by Jackson Pinsonneault on 3/24/26.
//

#ifndef ETC_CONTROLLER_H
#define ETC_CONTROLLER_H

#include "AnalogIn.h"
#include "mbed.h"

class ETCController {
public:

    /*
        Start of public variables
    */

    int16_t torque_demand = 0;
    bool apps_out_of_range_implausible = false; //rule #T.4.2.10, if the sensor voltages are outside its valid range
    bool apps_deviation_implausible = false; //rule #T.4.2.4, if the sensors disagree by >10%.



    /*
        End of public variables
    */

    /*
        Public method definitions, don't edit
    */
    ETCController(PinName APPS1_pin, PinName APPS2_pin);

    void update_state();

private:
    /*
        Start of private variables
    */

    AnalogIn apps1;
    AnalogIn apps2;

    float apps1_voltage = 0.0f; //sensor readings of voltage from the two pins
    float apps2_voltage = 0.0f;

    float apps1_position = 0.0f; //pedal position quantified between 0 (release) and 1 (press)
    float apps2_position = 0.0f;

    Timer out_of_range; //how long fault conditions are lasting
    Timer deviation_timer;



    

    /*
        End of private variables
    */

    /*  
        !! IMPORTANT: All global voltages are based off     !!
        !! an older testing time. Still, voltages           !!
        !! should always be checked and updated if wrong.   !!
    */

    static constexpr std::chrono::milliseconds IMPLAUS_TIME_LIMIT{100}; //rule #T.4.2.5 (implausibilty buffer, needs to act this long before any action)

    static constexpr float APPS_DEVIATION_LIMIT = 0.10f; //rule #T.4.2.4 (max allowed difference between both pedal positions before error).

    static constexpr float APPS_RANGE_MARGIN = 0.10f; //rule #T.4.2.10 (tolerance in Volts beyond defined min/max before error)




    static constexpr float APPS1_MIN_VOLTAGE = 0.396f;
    static constexpr float APPS1_MAX_VOLTAGE = 1.086f;

    static constexpr float APPS2_MIN_VOLTAGE = 0.439f;
    static constexpr float APPS2_MAX_VOLTAGE = 1.133f;

    static constexpr float PEDAL_DEADZONE_PERCENTAGE = 0.03;

    static constexpr int16_t MAX_TORQUE = 32767 * 0.1; // Multiplied by 0.1 for controlled 
                                                       // motor torque during onboarding.

    float clamp(float value);

    bool in_range(float value, float low, float high);

    void update_implausibilities();
};

#endif
