#include "core.h"
#include "standard_configuration.h"
#include "irrigator_interface.h"
#include "wrap_up_action_interface.h"
#include "irrigator.h"
#include "wrap_up_action.h"
#include "air_sensors/dht11.h"
#include "soil_sensors/hl69.h"
#include "air_interface/air_interface.h"
#include "soil_interface/soil_interface.h"
#include "user_configuration/air_configuration.h"
#include "user_configuration/soil_configuration.h"
#include "pin_utils/adc_defs.h"
#include "clock/clock.h"
#include "system_timer/system_timer.h"
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

static IrrigatorInterface soil_irrigator_interface;
static Irrigator soil_irrigator;
static Irrigator air_irrigator;
static IrrigatorInterface air_irrigator_interface;
static WrapUpAction wrap_up_action;
static WrapUpActionInterface wrap_up_action_interface;
static StandardConfiguration standard_configuration;
static SystemCore system_core;

void setup();
void loop();

Bool should_wake_up();
int get_time_from_last_soil_irrigation();
int get_time_from_last_air_irrigation();

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

    soil_irrigator = Irrigator_Construct(SystemTimer_GetCurrentTimeSeconds, 
        SOIL_IRRIGATOR_DATA_PIN_DDR_PTR, 
        SOIL_IRRIGATOR_DATA_PIN_PORT_PTR, 
        SOIL_IRRIGATOR_DATA_PIN
    );
    soil_irrigator_interface = Irrigator_GetIrrigatorInterface(soil_irrigator);

    air_irrigator = Irrigator_Construct(SystemTimer_GetCurrentTimeSeconds, 
        AIR_IRRIGATOR_DATA_PIN_DDR_PTR, 
        AIR_IRRIGATOR_DATA_PIN_PORT_PTR, 
        AIR_IRRIGATOR_DATA_PIN
    );
    air_irrigator_interface = Irrigator_GetIrrigatorInterface(air_irrigator);

    wrap_up_action = WrapUpAction_Construct();
    wrap_up_action_interface = WrapUpAction_GetWrapUpActionInterface(wrap_up_action);


    standard_configuration = StandardConfiguration_Construct(
        should_wake_up,
        SoilInterface_GetSoilHumidityInformation,
        get_time_from_last_soil_irrigation,
        3 * 60 * 60,
        &soil_irrigator_interface,
        60,
        AirInterface_GetAirHumidityInformation,
        get_time_from_last_air_irrigation,
        3 * 60 * 60,
        &air_irrigator_interface,
        60,
        &wrap_up_action_interface
    );

    system_core = StandardConfiguration_GetSystemCore(standard_configuration);

    sei();
}

void loop()
{
    SystemCore_AdvanceCycle(system_core);
}

Bool should_wake_up()
{
    static int last_wake_up_time = 0;

    Bool should_wake_up = FALSE;
    int current_time = SystemTimer_GetCurrentTimeSeconds();

    if((current_time - last_wake_up_time) >= (15 * 60))
    {
        should_wake_up = TRUE;
        last_wake_up_time = current_time;
    }
    else
    {
        should_wake_up = FALSE;
    }

    return should_wake_up;
}

int get_time_from_last_soil_irrigation()
{
    return Irrigator_GetTimeFromLastIrrigation(soil_irrigator);
}

int get_time_from_last_air_irrigation()
{
    return Irrigator_GetTimeFromLastIrrigation(air_irrigator);
}
