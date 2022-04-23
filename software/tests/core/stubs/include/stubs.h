#ifndef STUBS_H
#define STUBS_H

#include "common.h"
#include "soil_humidity_check_state.h"
#include "air_humidity_check_state.h"

Bool stub_should_wake_up_true();
Bool stub_should_wake_up_false();
SoilHumidityInformation stub_get_soil_humidity_50_threshold_60();
SoilHumidityInformation stub_get_soil_humidity_70_threshold_60();
SoilHumidityInformation stub_get_soil_humidity_60_threshold_60();
AirHumidityInformation stub_get_air_humidity_50_threshold_60();
AirHumidityInformation stub_get_air_humidity_70_threshold_60();
AirHumidityInformation stub_get_air_humidity_60_threshold_60();

#endif