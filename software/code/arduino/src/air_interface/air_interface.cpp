#include "air_interface.hpp"

typedef struct AirInterfaceStateInternal
{
    bool is_initialized;
    GetAirInformationCallback get_air_information_callback;
    GetAirUserConfigurationCallback get_air_user_configuration_callback;
} AirInterfaceState;

static AirInterfaceState singleton = {false, nullptr, nullptr};

void AirInterface_Initialize(GetAirInformationCallback get_air_information_callback, 
    GetAirUserConfigurationCallback get_air_user_configuration_callback
)
{
    singleton.is_initialized = true;
    singleton.get_air_information_callback = get_air_information_callback;
    singleton.get_air_user_configuration_callback = get_air_user_configuration_callback;
}

AirHumidityInformation AirInterface_GetAirHumidityInformation()
{
    AirHumidityInformation information;

    float current_relative_humidity = 0.0f;
    float relative_humidity_threshold = 0.0f;

    if(singleton.is_initialized == true)
    {
        current_relative_humidity = singleton.get_air_information_callback().relative_humidity;
        relative_humidity_threshold = singleton.get_air_user_configuration_callback().relative_humidity_threshold;
    }

    information.current_relative_humidity = current_relative_humidity;
    information.relative_humidity_threshold = relative_humidity_threshold;

    return information;
}