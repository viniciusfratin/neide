#include "soil_interface.hpp"

typedef struct SoilInterfaceStateInternal
{
    bool is_initialized;
    GetSoilInformationCallback get_soil_information_callback;
    GetSoilUserConfigurationCallback get_soil_user_configuration_callback;
} SoilInterfaceState;

static SoilInterfaceState singleton = {false, nullptr, nullptr};

void SoilInterface_Initialize(GetSoilInformationCallback get_soil_information_callback, 
    GetSoilUserConfigurationCallback get_soil_user_configuration_callback
)
{
    singleton.is_initialized = true;
    singleton.get_soil_information_callback = get_soil_information_callback;
    singleton.get_soil_user_configuration_callback = get_soil_user_configuration_callback;
}

SoilHumidityInformation SoilInterface_GetSoilHumidityInformation()
{
    SoilHumidityInformation information;

    float current_relative_humidity = 0.0f;
    float relative_humidity_threshold = 0.0f;

    if(singleton.is_initialized == true)
    {
        current_relative_humidity = singleton.get_soil_information_callback().relative_humidity;
        relative_humidity_threshold = singleton.get_soil_user_configuration_callback().relative_humidity_threshold;
    }

    information.current_relative_humidity = current_relative_humidity;
    information.relative_humidity_threshold = relative_humidity_threshold;

    return information;
}