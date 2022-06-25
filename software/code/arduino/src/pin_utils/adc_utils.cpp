#include "adc_utils.hpp"
#include <cstdint>
#include <avr/io.h>

#define NUM_ADCS 8

static uint8_t adc_selection_bits[NUM_ADCS] = {
    0x00U,
    0x01U,
    0x02U,
    0x03U,
    0x04U,
    0x05U,
    0x06U,
    0x07U
};

static void select_adc(ADCIdentifier adc_identifier);
static void set_free_running_mode();
static void set_inputs_as_analog();
static void begin_read();
static float get_read_value();

float read_adc(ADCIdentifier adc_identifier)
{
    float adc_value;

    select_adc(adc_identifier);
    set_free_running_mode();
    set_inputs_as_analog();
    begin_read();
    adc_value = get_read_value();

    return adc_value;
}

static void select_adc(ADCIdentifier adc_identifier)
{
    uint8_t admux_value = 0x00U;
    admux_value &= ~(_BV(REFS1));
    admux_value |= _BV(REFS0);
    admux_value &= ~(_BV(ADLAR));
    admux_value |= adc_selection_bits[adc_identifier];

    ADMUX = admux_value;
}

static void set_free_running_mode()
{
    uint8_t adcsrb_value = 0x00U;
    adcsrb_value &= ~(_BV(ACME));
    adcsrb_value &= ~(_BV(ADTS2));
    adcsrb_value &= ~(_BV(ADTS1));
    adcsrb_value &= ~(_BV(ADTS0));

    ADCSRB = adcsrb_value;
}

static void set_inputs_as_analog()
{
    uint8_t didr0_value = 0x00U;
    didr0_value &= ~(_BV(ADC5D));
    didr0_value &= ~(_BV(ADC4D));
    didr0_value &= ~(_BV(ADC3D));
    didr0_value &= ~(_BV(ADC2D));
    didr0_value &= ~(_BV(ADC1D));
    didr0_value &= ~(_BV(ADC0D));

    DIDR0 = didr0_value;
}

static void begin_read()
{
    ADCSRA &= ~(_BV(ADATE));
    ADCSRA &= ~(_BV(ADIE));
    ADCSRA |= _BV(ADPS2);
    ADCSRA |= _BV(ADPS1);
    ADCSRA |= _BV(ADPS0);

    ADCSRA |= _BV(ADEN);
    ADCSRA |= _BV(ADSC);
}

static float get_read_value()
{
    float actual_value;
    int32_t raw_value = 0;

    while((ADCSRA & _BV(ADSC)) != 0);
    raw_value = ADCL;
    raw_value |= (ADCH << 8);

    actual_value = (raw_value * A_VCC) / 1024.0f;

    return actual_value;
}