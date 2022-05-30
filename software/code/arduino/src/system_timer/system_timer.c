#include "system_timer.h"
#include "common.h"
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

typedef struct SystemTimerStateInternal
{
    Bool is_initialized;
    volatile int32_t current_time_seconds;
    volatile int32_t current_num_of_overflows;
} SystemTimerState;

static SystemTimerState singleton = {FALSE, 0, 0};

#define NUM_OVERFLOWS_PER_SECOND ((F_CPU/256)/1024)

void SystemTimer_Initialize()
{
    singleton.is_initialized = TRUE;
    singleton.current_time_seconds = 0;
    singleton.current_num_of_overflows = 0;

    uint8_t tccr0a_value = 0;
    tccr0a_value &= ~(_BV(COM0A1));
    tccr0a_value &= ~(_BV(COM0A0));
    tccr0a_value &= ~(_BV(COM0B1));
    tccr0a_value &= ~(_BV(COM0B0));
    tccr0a_value &= ~(_BV(WGM01));
    tccr0a_value &= ~(_BV(WGM00));

    TCCR0A = tccr0a_value;

    uint8_t tccr0b_value = 0;
    tccr0b_value |= _BV(CS02);
    tccr0b_value &= ~(_BV(CS01));
    tccr0b_value |= _BV(CS00);

    TCCR0B = tccr0b_value;

    uint8_t timsk0_value = 0;
    timsk0_value |= _BV(TOIE0);

    TIMSK0 = timsk0_value;
}

int32_t SystemTimer_GetCurrentTimeSeconds()
{
    return singleton.current_time_seconds;
}

ISR(TIMER0_OVF_vect)
{
    singleton.current_num_of_overflows++;
    if(singleton.current_num_of_overflows == NUM_OVERFLOWS_PER_SECOND)
    {
        singleton.current_time_seconds++;
        singleton.current_num_of_overflows = 0;
    }
}