#include "stubs.hpp"

Bool stub_should_wake_up_true()
{
    return TRUE;
}

Bool stub_should_wake_up_false()
{
    return FALSE;
}

SoilHumidityInformation stub_get_soil_humidity_50_threshold_60()
{
    SoilHumidityInformation soil_humidity_information;

    soil_humidity_information.current_relative_humidity = 50.0f;
    soil_humidity_information.relative_humidity_threshold = 60.0f;

    return soil_humidity_information;
}

SoilHumidityInformation stub_get_soil_humidity_70_threshold_60()
{
    SoilHumidityInformation soil_humidity_information;

    soil_humidity_information.current_relative_humidity = 70.0f;
    soil_humidity_information.relative_humidity_threshold = 60.0f;

    return soil_humidity_information;
}

SoilHumidityInformation stub_get_soil_humidity_60_threshold_60()
{
    SoilHumidityInformation soil_humidity_information;

    soil_humidity_information.current_relative_humidity = 60.0f;
    soil_humidity_information.relative_humidity_threshold = 60.0f;

    return soil_humidity_information;
}

AirHumidityInformation stub_get_air_humidity_50_threshold_60()
{
    AirHumidityInformation air_humidity_information;

    air_humidity_information.current_relative_humidity = 50.0f;
    air_humidity_information.relative_humidity_threshold = 60.0f;

    return air_humidity_information;
}

AirHumidityInformation stub_get_air_humidity_70_threshold_60()
{
    AirHumidityInformation air_humidity_information;

    air_humidity_information.current_relative_humidity = 70.0f;
    air_humidity_information.relative_humidity_threshold = 60.0f;

    return air_humidity_information;
}

AirHumidityInformation stub_get_air_humidity_60_threshold_60()
{
    AirHumidityInformation air_humidity_information;

    air_humidity_information.current_relative_humidity = 60.0f;
    air_humidity_information.relative_humidity_threshold = 60.0f;

    return air_humidity_information;
}

int32_t stub_get_time_from_last_soil_irrigation_2_hours()
{
    return 2 * 60 * 60;
}

int32_t stub_get_time_from_last_soil_irrigation_3_hours()
{
    return 3 * 60 * 60;
}

int32_t stub_get_time_from_last_soil_irrigation_4_hours()
{
    return 4 * 60 * 60;
}

int32_t stub_get_time_from_last_air_irrigation_2_hours()
{
    return 2 * 60 * 60;
}

int32_t stub_get_time_from_last_air_irrigation_3_hours()
{
    return 3 * 60 * 60;
}

int32_t stub_get_time_from_last_air_irrigation_4_hours()
{
    return 4 * 60 * 60;
}
