#include "dummy_air_configuration.hpp"

typedef struct DummyAirConfigurationStateInternal
{
    bool is_initialized;
} DummyAirConfigurationState;

static DummyAirConfigurationState singleton = {false};

void DummyAirConfiguration_Initialize()
{
    singleton.is_initialized = true;
}

AirUserConfiguration DummyAirConfiguration_GetAirUserConfiguration()
{
    AirUserConfiguration air_user_configuration;

    air_user_configuration.relative_humidity_threshold = 0.0f;

    return air_user_configuration;
}