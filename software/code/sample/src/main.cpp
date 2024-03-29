#include "core.hpp"
#include "standard_configuration.hpp"
#include "irrigator_interface.hpp"
#include "wrap_up_action_interface.hpp"
#include "time_from_last_irrigation_provider_interface.hpp"
extern "C" 
{
    #include <stdio.h>
}

#define NUMBER_OF_SAMPLE_CYCLES 50

bool should_wake_up()
{
    bool should_wake_up = true;

    printf("- Should wake up: %d\n", (int)should_wake_up);
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

class TimeFromLastSoilIrrigationProvider : public TimeFromLastIrrigationProviderInterface
{
    public:
    long GetTimeFromLastIrrigationSeconds() override
    {
        long time = 4L * 60L * 60L;

        printf("- Time from last soil irrigation: %ld\n", time);

        return time;
    }

    virtual ~TimeFromLastSoilIrrigationProvider()
    {

    }
};

class SoilIrrigationTimeProvider : public IrrigationTimeProviderInterface
{
    public:
    int GetIrrigationTimeSeconds() override
    {
        int time = 10;

        return time;
    }

    virtual ~SoilIrrigationTimeProvider()
    {
        
    }
};

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

class TimeFromLastAirIrrigationProvider : public TimeFromLastIrrigationProviderInterface
{
    public:
    long GetTimeFromLastIrrigationSeconds() override
    {
        long time = 5L * 60L * 60L;

        printf("- Time from last air irrigation: %ld\n", time);

        return time;
    }

    virtual ~TimeFromLastAirIrrigationProvider()
    {
        
    }
};

class AirIrrigationTimeProvider : public IrrigationTimeProviderInterface
{
    public:
    int GetIrrigationTimeSeconds() override
    {
        int time = 10;

        return time;
    }

    virtual ~AirIrrigationTimeProvider()
    {
        
    }
};

class Irrigator : public IrrigatorInterface
{
    public:
    void Irrigate(long irrigation_time_seconds) override
    {
        printf("- Irrigating: %ld\n", irrigation_time_seconds);
    }

    virtual ~Irrigator()
    {
        
    }
};

class WrapUpAction : public WrapUpActionInterface
{
    public:
    void WrapUp() override
    {
        return;
    }

    virtual ~WrapUpAction()
    {

    }
};

int main()
{
    printf("neide system.\n");

    Irrigator* soil_irrigator = new Irrigator();
    Irrigator* air_irrigator = new Irrigator();
    WrapUpAction* wrap_up_action = new WrapUpAction();
    TimeFromLastSoilIrrigationProvider* time_from_last_soil_irrigation_provider = new TimeFromLastSoilIrrigationProvider();
    TimeFromLastAirIrrigationProvider* time_from_last_air_irrigation_provider = new TimeFromLastAirIrrigationProvider();
    SoilIrrigationTimeProvider* soil_irrigation_time_provider = new SoilIrrigationTimeProvider();
    AirIrrigationTimeProvider* air_irrigation_time_provider = new AirIrrigationTimeProvider();

    StandardConfiguration* standard_configuration = new StandardConfiguration(
        should_wake_up,
        get_soil_humidity_information,
        time_from_last_soil_irrigation_provider,
        3 * 60 * 60,
        soil_irrigator,
        soil_irrigation_time_provider,
        get_air_humidity_information,
        time_from_last_air_irrigation_provider,
        3 * 60 * 60,
        air_irrigator,
        air_irrigation_time_provider,
        wrap_up_action
    );

    SystemCore* system_core = standard_configuration->GetSystemCore();

    for(long num_cycles = 0; num_cycles < NUMBER_OF_SAMPLE_CYCLES; num_cycles++)
    {
        printf("Current state: %ld\n", (long)system_core->GetCurrentState());
        
        system_core->AdvanceCycle();
    }

    delete standard_configuration;
    delete soil_irrigation_time_provider;
    delete air_irrigation_time_provider;
    delete time_from_last_soil_irrigation_provider;
    delete time_from_last_air_irrigation_provider;
    delete wrap_up_action;
    delete air_irrigator;
    delete soil_irrigator;
    
    return 0;
}