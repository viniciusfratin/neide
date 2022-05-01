#include "common.h"
#include "air_configuration.h"

typedef struct AirConfigurationStateInternal
{
    Bool is_initialized;
} AirConfigurationState;

static AirConfigurationState singleton = {FALSE};

void AirConfiguration_Initialize()
{
    singleton.is_initialized = TRUE;
}

AirUserConfiguration AirConfiguration_GetAirUserConfiguration()
{
    AirUserConfiguration air_user_configuration;

    float relative_humidity_threshold = 0.0f;

    air_user_configuration.relative_humidity_threshold = relative_humidity_threshold;

    return air_user_configuration;
}