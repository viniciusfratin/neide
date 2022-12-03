#include "potentiometer_irrigation_time_provider.hpp"

struct PotentiometerIrrigationTimeProvider::impl
{
    PotentiometerInterface* potentiometer;
    int min_irrigation_time_seconds;
    int max_irrigation_time_seconds;

    impl(
        PotentiometerInterface* potentiometer,
        int min_irrigation_time_seconds,
        int max_irrigation_time_seconds
    )
    {
        this->potentiometer = potentiometer;
        this->min_irrigation_time_seconds = min_irrigation_time_seconds;
        this->max_irrigation_time_seconds = max_irrigation_time_seconds;
    }

    int GetIrrigationTimeSeconds()
    {
        float potentiometer_relative_value = this->potentiometer->GetRelativeValue();

        return (
            min_irrigation_time_seconds +
            (int)((max_irrigation_time_seconds - min_irrigation_time_seconds) * potentiometer_relative_value)
        );
    }
};

PotentiometerIrrigationTimeProvider::PotentiometerIrrigationTimeProvider(
    PotentiometerInterface* potentiometer,
    int min_irrigation_time_seconds,
    int max_irrigation_time_seconds
) : pImpl(
        new impl(
            potentiometer,
            min_irrigation_time_seconds,
            max_irrigation_time_seconds
        )
    )
{

}

PotentiometerIrrigationTimeProvider::~PotentiometerIrrigationTimeProvider()
{
    delete pImpl;
}

int PotentiometerIrrigationTimeProvider::GetIrrigationTimeSeconds()
{
    return pImpl->GetIrrigationTimeSeconds();
}
