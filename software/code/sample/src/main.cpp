#include "core.hpp"
#include "standard_configuration.hpp"
#include "irrigator_interface.hpp"
#include "wrap_up_action_interface.hpp"
#include <stdio.h>
#include <memory>
#include <cstdint>

#define NUMBER_OF_SAMPLE_CYCLES 50

bool should_wake_up()
{
    bool should_wake_up = true;

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

class Irrigator : public IrrigatorInterface
{
    public:
    void Irrigate(int32_t irrigation_time_seconds) override
    {
        printf("- Irrigating: %d\n", irrigation_time_seconds);
    }
};

class WrapUpAction : public WrapUpActionInterface
{
    public:
    void WrapUp() override
    {
        return;
    }
};

int32_t main()
{
    printf("neide system.\n");

    std::unique_ptr<Irrigator> soil_irrigator = std::make_unique<Irrigator>();
    std::unique_ptr<Irrigator> air_irrigator = std::make_unique<Irrigator>();
    std::unique_ptr<WrapUpAction> wrap_up_action = std::make_unique<WrapUpAction>();

    std::unique_ptr<StandardConfiguration> standard_configuration = std::make_unique<StandardConfiguration>(
        should_wake_up,
        get_soil_humidity_information,
        get_time_from_last_soil_irrigation,
        3 * 60 * 60,
        soil_irrigator.get(),
        10,
        get_air_humidity_information,
        get_time_from_last_air_irrigation,
        3 * 60 * 60,
        air_irrigator.get(),
        10,
        wrap_up_action.get()
    );

    SystemCore* system_core = standard_configuration->GetSystemCore();

    for(int32_t num_cycles = 0; num_cycles < NUMBER_OF_SAMPLE_CYCLES; num_cycles++)
    {
        printf("Current state: %d\n", (int32_t)system_core->GetCurrentState());
        
        system_core->AdvanceCycle();
    }

    return 0;
}