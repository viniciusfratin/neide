#include "core.hpp"
#include "standard_configuration.hpp"
#include "irrigator_interface.hpp"
#include "wrap_up_action_interface.hpp"
#include "time_from_last_irrigation_provider_interface.hpp"
#include "soil_irrigator.hpp"
#include "air_irrigator.hpp"
#include "wrap_up_action.hpp"
#include "air_sensors/dht11.hpp"
#include "soil_sensors/sen0193.hpp"
#include "air_interface/air_interface.hpp"
#include "soil_interface/soil_interface.hpp"
#include "user_configuration/dummy_air_configuration.hpp"
#include "user_configuration/dummy_soil_configuration.hpp"
#include "devices/potentiometer_interface.hpp"
#include "devices/adc_potentiometer.hpp"
#include "irrigation_time_providers/potentiometer_irrigation_time_provider.hpp"
#include "pin_utils/adc_defs.hpp"
#include "clock/clock.hpp"
#include "system_timer/system_timer.hpp"

extern "C" 
{
    #include <avr/io.h>
    #include <avr/interrupt.h>
}

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

    ADCPotentiometer* air_potentiometer = new ADCPotentiometer(IDENTIFIER_ADC0);
    ADCPotentiometer* soil_potentiometer = new ADCPotentiometer(IDENTIFIER_ADC2);
    
    PotentiometerIrrigationTimeProvider* air_irrigation_time_provider = new PotentiometerIrrigationTimeProvider(
        air_potentiometer,
        15,
        120
    );
    PotentiometerIrrigationTimeProvider* soil_irrigation_time_provider = new PotentiometerIrrigationTimeProvider(
        soil_potentiometer,
        40,
        60
    );

    DummyAirConfiguration_Initialize();
    AirInterface_Initialize(DHT11_GetAirInformation, DummyAirConfiguration_GetAirUserConfiguration);
    
    SEN0193_Initialize(IDENTIFIER_ADC1);
    DummySoilConfiguration_Initialize();
    SoilInterface_Initialize(SEN0193_GetSoilInformation, DummySoilConfiguration_GetSoilUserConfiguration);

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
        soil_irrigator,
        48L * 60L * 60L,
        soil_irrigator,
        soil_irrigation_time_provider,
        AirInterface_GetAirHumidityInformation,
        air_irrigator,
        3L * 60L * 60L,
        air_irrigator,
        air_irrigation_time_provider,
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

    if((current_time - last_wake_up_time) >= (15L * 60L))
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
