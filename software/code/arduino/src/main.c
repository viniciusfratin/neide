#include "core.h"
#include "standard_configuration.h"
#include "irrigator_interface.h"
#include "wrap_up_action_interface.h"
#include "irrigator.h"
#include "wrap_up_action.h"
#include <avr/io.h>

Bool should_wake_up()
{
    Bool should_wake_up = TRUE;

    return should_wake_up;
}

SoilHumidityInformation get_soil_humidity_information()
{
    SoilHumidityInformation information;
    information.current_relative_humidity = 70.0f;
    information.relative_humidity_threshold = 60.0f;

    return information;
}

int get_time_from_last_soil_irrigation()
{
    int time = 4 * 60 * 60;

    return time;
}

AirHumidityInformation get_air_humidity_information()
{
    AirHumidityInformation information;
    information.current_relative_humidity = 70.0f;
    information.relative_humidity_threshold = 60.0f;

    return information;
}

int get_time_from_last_air_irrigation()
{
    int time = 5 * 60 * 60;

    return time;
}

int main()
{
    Irrigator soil_irrigator = Irrigator_Construct();
    IrrigatorInterface soil_irrigator_interface = Irrigator_GetIrrigatorInterface(soil_irrigator);

    Irrigator air_irrigator = Irrigator_Construct();
    IrrigatorInterface air_irrigator_interface = Irrigator_GetIrrigatorInterface(air_irrigator);

    WrapUpAction wrap_up_action = WrapUpAction_Construct();
    WrapUpActionInterface wrap_up_action_interface = WrapUpAction_GetWrapUpActionInterface(wrap_up_action);


    StandardConfiguration standard_configuration = StandardConfiguration_Construct(
        should_wake_up,
        get_soil_humidity_information,
        get_time_from_last_soil_irrigation,
        3 * 60 * 60,
        &soil_irrigator_interface,
        10,
        get_air_humidity_information,
        get_time_from_last_air_irrigation,
        3 * 60 * 60,
        &air_irrigator_interface,
        10,
        &wrap_up_action_interface
    );

    SystemCore system_core = StandardConfiguration_GetSystemCore(standard_configuration);

    while(1)
    {
        SystemCore_AdvanceCycle(system_core);
    }

    return 0;
}