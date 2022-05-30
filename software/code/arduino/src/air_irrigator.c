#include "air_irrigator.h"
#include "irrigator_interface.h"
#include "irrigator_interface_construction.h"
#include "pin_utils/gpio_utils.h"
#include <stdlib.h>
#include <avr/io.h>

#define PWM_DDR_PIN (DDRB)
#define PWM_PIN (PB1)

typedef struct AirIrrigatorInternal
{
    IrrigatorInterface irrigator_interface;
    int32_t last_irrigation_time;
    GetCurrentTimeSecondsCallback get_current_time_seconds_callback;
    volatile uint8_t* pin_ddr_ptr;
    volatile uint8_t* pin_port_ptr;
    uint8_t pin;
} AirIrrigatorImplementation;

static void AirIrrigator_Irrigate(void* object_instance, int32_t irrigation_time_seconds);

AirIrrigator AirIrrigator_Construct(GetCurrentTimeSecondsCallback get_current_time_seconds_callback, volatile uint8_t* pin_ddr_ptr, volatile uint8_t* pin_port_ptr, uint8_t pin)
{
    AirIrrigator instance = (AirIrrigator)malloc(sizeof(AirIrrigatorImplementation));

    if(instance != NULL)
    {
        instance->irrigator_interface = IrrigatorInterface_Construct(
            (void*)instance,
            AirIrrigator_Irrigate
        );

        if(instance->irrigator_interface != IRRIGATOR_INTERFACE_INVALID_INSTANCE)
        {
            instance->last_irrigation_time = 0;
            instance->get_current_time_seconds_callback = get_current_time_seconds_callback;
            instance->pin_ddr_ptr = pin_ddr_ptr;
            instance->pin_port_ptr = pin_port_ptr;
            instance->pin = pin;

            SET_GPIO_PIN_AS_OUTPUT(instance->pin_ddr_ptr, instance->pin);
            SET_GPIO_PIN_TO_LOW(instance->pin_port_ptr, instance->pin);

            /* Set fast PWM on pin 9 with maximum frequency, initially turned off. */
            TCCR1A |= _BV(WGM10);
	        TCCR1B |= _BV(CS10) | _BV(WGM12);
            PWM_DDR_PIN &= ~(_BV(PWM_PIN));
        }
        else
        {
            instance = AIR_IRRIGATOR_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = AIR_IRRIGATOR_INVALID_INSTANCE;
    }

    return instance;
}

void AirIrrigator_Destruct(AirIrrigator* instancePtr)
{
    if(instancePtr != NULL)
    {
        IrrigatorInterface_Destruct(&((*instancePtr)->irrigator_interface));

        free(*instancePtr);
        (*instancePtr) = AIR_IRRIGATOR_INVALID_INSTANCE;
    }
}

IrrigatorInterface AirIrrigator_GetIrrigatorInterface(AirIrrigator instance)
{
    return instance->irrigator_interface;
}

int32_t AirIrrigator_GetTimeFromLastIrrigation(AirIrrigator instance)
{
    int32_t current_time = instance->get_current_time_seconds_callback();

    return (current_time - instance->last_irrigation_time);
}

static void AirIrrigator_Irrigate(void* object_instance, int32_t irrigation_time_seconds)
{
    AirIrrigator instance = (AirIrrigator)object_instance;
    instance->last_irrigation_time = instance->get_current_time_seconds_callback();

    /* Turn on indication LED. */
    SET_GPIO_PIN_TO_HIGH(instance->pin_port_ptr, instance->pin);

    /* Enable fast PWM on pin 9 with maximum frequency. */
    PWM_DDR_PIN |= _BV(PWM_PIN);

    while((instance->get_current_time_seconds_callback() - instance->last_irrigation_time) <= irrigation_time_seconds);

    /* Disable PWM. */
    PWM_DDR_PIN &= ~(_BV(PWM_PIN));

    /* Turn off indication LED. */
    SET_GPIO_PIN_TO_LOW(instance->pin_port_ptr, instance->pin);
}


