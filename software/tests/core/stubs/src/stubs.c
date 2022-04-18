#include "stubs.h"

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
