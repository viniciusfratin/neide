#include "dummy_soil_configuration.hpp"

typedef struct DummySoilConfigurationStateInternal
{
    bool is_initialized;
} DummySoilConfigurationState;

static DummySoilConfigurationState singleton = {false};

void DummySoilConfiguration_Initialize()
{
    singleton.is_initialized = true;
}

SoilUserConfiguration DummySoilConfiguration_GetSoilUserConfiguration()
{
    SoilUserConfiguration soil_user_configuration;

    soil_user_configuration.relative_humidity_threshold = 0.0f;

    return soil_user_configuration;
}