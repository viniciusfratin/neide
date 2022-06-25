#include "core.hpp"
#include "standard_configuration.hpp"
#include "irrigator_interface.hpp"
#include "wrap_up_action_interface.hpp"
#include "irrigator.hpp"
#include "wrap_up_action.hpp"
#include <stdio.h>
#include <stdint.h>

#define NUMBER_OF_SAMPLE_CYCLES 50

Bool should_wake_up()
{
    Bool should_wake_up = TRUE;

    printf("- Should wake up: %d\n", should_wake_up);
    return should_wake_up;
}

SoilHumidityInformation get_soil_humidity_information()
{
    SoilHumidityInformation information;
    information.current_relative_humidity = 70.0f;
    information.relative_humidity_threshold = 60.0f;

    printf("- Soil humidity information:\n");
    printf("-- Current relative humidity: %.2f\n", information.current_relative_humidity);
    printf("-- Relative humidity threshold: %.2f\n", information.relative_humidity_threshold);
    return information;
}

int32_t get_time_from_last_soil_irrigation()
{
    int32_t time = 4 * 60 * 60;

    printf("- Time from last soil irrigation: %d\n", time);

    return time;
}

AirHumidityInformation get_air_humidity_information()
{
    AirHumidityInformation information;
    information.current_relative_humidity = 70.0f;
    information.relative_humidity_threshold = 60.0f;

    printf("- Air humidity information:\n");
    printf("-- Current relative humidity: %.2f\n", information.current_relative_humidity);
    printf("-- Relative humidity threshold: %.2f\n", information.relative_humidity_threshold);
    return information;
}

int32_t get_time_from_last_air_irrigation()
{
    int32_t time = 5 * 60 * 60;

    printf("- Time from last air irrigation: %d\n", time);

    return time;
}

int32_t main()
{
    printf("neide system.\n");

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

    for(int32_t num_cycles = 0; num_cycles < NUMBER_OF_SAMPLE_CYCLES; num_cycles++)
    {
        printf("Current state: %d\n", SystemCore_GetCurrentState(system_core));
        
        SystemCore_AdvanceCycle(system_core);
    }

    return 0;
}