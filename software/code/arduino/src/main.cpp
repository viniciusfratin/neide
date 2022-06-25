#include "core.hpp"
#include "standard_configuration.hpp"
#include "irrigator_interface.hpp"
#include "wrap_up_action_interface.hpp"
#include "soil_irrigator.hpp"
#include "air_irrigator.hpp"
#include "wrap_up_action.hpp"
#include "air_sensors/dht11.hpp"
#include "soil_sensors/hl69.hpp"
#include "air_interface/air_interface.hpp"
#include "soil_interface/soil_interface.hpp"
#include "user_configuration/air_configuration.hpp"
#include "user_configuration/soil_configuration.hpp"
#include "pin_utils/adc_defs.hpp"
#include "clock/clock.hpp"
#include "system_timer/system_timer.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>

#define DHT11_DATA_PIN_INPUT_REGISTER_PTR (&PINB)
#define DHT11_DATA_PIN_DDR_PTR (&DDRB)
#define DHT11_DATA_PIN_PORT_PTR (&PORTB)
#define DHT11_DATA_PIN (PB4)

#define SOIL_IRRIGATOR_DATA_PIN_DDR_PTR (&DDRD)
#define SOIL_IRRIGATOR_DATA_PIN_PORT_PTR (&PORTD)
#define SOIL_IRRIGATOR_DATA_PIN (PD2)

#define AIR_IRRIGATOR_DATA_PIN_DDR_PTR (&DDRD)
#define AIR_IRRIGATOR_DATA_PIN_PORT_PTR (&PORTD)
#define AIR_IRRIGATOR_DATA_PIN (PD3)

static SoilIrrigator* soil_irrigator;
static AirIrrigator* air_irrigator;
static WrapUpAction* wrap_up_action;
static StandardConfiguration* standard_configuration;
static SystemCore* system_core;

void setup();
void loop();

bool should_wake_up();
long get_time_from_last_soil_irrigation();
long get_time_from_last_air_irrigation();

int main()
{
    setup();

    while(1)
    {
        loop();
    }

    return 0;
}

void setup()
{
    SystemTimer_Initialize();

    DHT11_Initialize(DHT11_DATA_PIN_INPUT_REGISTER_PTR,
        DHT11_DATA_PIN_DDR_PTR,
        DHT11_DATA_PIN_PORT_PTR, 
        DHT11_DATA_PIN
    );
    AirConfiguration_Initialize(IDENTIFIER_ADC0);
    AirInterface_Initialize(DHT11_GetAirInformation, AirConfiguration_GetAirUserConfiguration);
    
    HL69_Initialize(IDENTIFIER_ADC1);
    SoilConfiguration_Initialize(IDENTIFIER_ADC2);
    SoilInterface_Initialize(HL69_GetSoilInformation, SoilConfiguration_GetSoilUserConfiguration);

    soil_irrigator = new SoilIrrigator(SystemTimer_GetCurrentTimeSeconds, 
        SOIL_IRRIGATOR_DATA_PIN_DDR_PTR, 
        SOIL_IRRIGATOR_DATA_PIN_PORT_PTR, 
        SOIL_IRRIGATOR_DATA_PIN
    );

    air_irrigator = new AirIrrigator(SystemTimer_GetCurrentTimeSeconds, 
        AIR_IRRIGATOR_DATA_PIN_DDR_PTR,
        AIR_IRRIGATOR_DATA_PIN_PORT_PTR,
        AIR_IRRIGATOR_DATA_PIN,
        IDENTIFIER_ADC3
    );

    wrap_up_action = new WrapUpAction();

    standard_configuration = new StandardConfiguration(
        should_wake_up,
        SoilInterface_GetSoilHumidityInformation,
        get_time_from_last_soil_irrigation,
        8L * 60L * 60L,
        soil_irrigator,
        15L,
        AirInterface_GetAirHumidityInformation,
        get_time_from_last_air_irrigation,
        3L * 60L * 60L,
        air_irrigator,
        15L,
        wrap_up_action
    );

    system_core = standard_configuration->GetSystemCore();

    sei();
}

void loop()
{
    system_core->AdvanceCycle();
}

bool should_wake_up()
{
    static long last_wake_up_time = 0;

    bool should_wake_up = false;
    long current_time = SystemTimer_GetCurrentTimeSeconds();

    if((current_time - last_wake_up_time) >= (15 * 60))
    {
        should_wake_up = true;
        last_wake_up_time = current_time;
    }
    else
    {
        should_wake_up = false;
    }

    return should_wake_up;
}

long get_time_from_last_soil_irrigation()
{
    return soil_irrigator->GetTimeFromLastIrrigation();
}

long get_time_from_last_air_irrigation()
{
    return air_irrigator->GetTimeFromLastIrrigation();
}
