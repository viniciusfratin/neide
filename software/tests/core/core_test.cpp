#include "gtest/gtest.h"


#include "core_states.hpp"
#include "core_state_interface.hpp"
#include "core.hpp"
#include "idle_state.hpp"
#include "woke_state.hpp"
#include "soil_humidity_check_state.hpp"
#include "soil_periodic_check_state.hpp"
#include "irrigate_soil_state.hpp"
#include "irrigator_interface.hpp"
#include "wrap_up_action_interface.hpp"
#include "air_humidity_check_state.hpp"
#include "air_periodic_check_state.hpp"
#include "irrigate_air_state.hpp"
#include "wrap_up_state.hpp"

#include "stubs.hpp"
#include "general_state_mock.hpp"
#include "irrigator_mock.hpp"
#include "wrap_up_action_mock.hpp"

#include <memory>

class CoreInitialIdleWithWakeUpTrue : public ::testing::Test
{
    private:
        std::unique_ptr<IdleState> idle_state;
        std::unique_ptr<GeneralStateMock> woke_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {
            idle_state = std::make_unique<IdleState>(stub_should_wake_up_true);
            woke_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_WOKE);

            idle_state->SetTransitions(woke_state_mock.get());

            system_core = std::make_unique<SystemCore>(
                idle_state.get()
            );
        }
};

class CoreInitialIdleWithWakeUpFalse : public ::testing::Test
{
    private:
        std::unique_ptr<IdleState> idle_state;
        std::unique_ptr<GeneralStateMock> woke_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {
            idle_state = std::make_unique<IdleState>(stub_should_wake_up_false);
            woke_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_WOKE);

            idle_state->SetTransitions(woke_state_mock.get());

            system_core = std::make_unique<SystemCore>(
                idle_state.get()
            );
        }
};

class CoreInitialWoke : public ::testing::Test
{
    private:
        std::unique_ptr<WokeState> woke_state;
        std::unique_ptr<GeneralStateMock> soil_humidity_check_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {
            woke_state = std::make_unique<WokeState>();
            soil_humidity_check_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_SOIL_HUMIDITY_CHECK);
            
            woke_state->SetTransitions(soil_humidity_check_state_mock.get());
            
            system_core = std::make_unique<SystemCore>(
                woke_state.get()
            );
        }
};

class CoreInitialSoilHumidityCheckWithRelativeHumidity50Threshold60 : public ::testing::Test
{
    private:
        std::unique_ptr<SoilHumidityCheckState> soil_humidity_check_state;
        std::unique_ptr<GeneralStateMock> irrigate_soil_state_mock;
        std::unique_ptr<GeneralStateMock> soil_periodic_check_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {
            soil_humidity_check_state = std::make_unique<SoilHumidityCheckState>(stub_get_soil_humidity_50_threshold_60);
            irrigate_soil_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IRRIGATE_SOIL);
            soil_periodic_check_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_SOIL_PERIODIC_CHECK);

            soil_humidity_check_state->SetTransitions(
                irrigate_soil_state_mock.get(),
                soil_periodic_check_state_mock.get()
            );

            system_core = std::make_unique<SystemCore>(
                soil_humidity_check_state.get()
            );
        }
};

class CoreInitialSoilHumidityCheckWithRelativeHumidity70Threshold60 : public ::testing::Test
{
    private:
        std::unique_ptr<SoilHumidityCheckState> soil_humidity_check_state;
        std::unique_ptr<GeneralStateMock> irrigate_soil_state_mock;
        std::unique_ptr<GeneralStateMock> soil_periodic_check_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {
            soil_humidity_check_state = std::make_unique<SoilHumidityCheckState>(stub_get_soil_humidity_70_threshold_60);
            irrigate_soil_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IRRIGATE_SOIL);
            soil_periodic_check_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_SOIL_PERIODIC_CHECK);

            soil_humidity_check_state->SetTransitions(
                irrigate_soil_state_mock.get(),
                soil_periodic_check_state_mock.get()
            );

            system_core = std::make_unique<SystemCore>(
                soil_humidity_check_state.get()
            );
        }
};

class CoreInitialSoilHumidityCheckWithRelativeHumidity60Threshold60 : public ::testing::Test
{
    private:
        std::unique_ptr<SoilHumidityCheckState> soil_humidity_check_state;
        std::unique_ptr<GeneralStateMock> irrigate_soil_state_mock;
        std::unique_ptr<GeneralStateMock> soil_periodic_check_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {
            soil_humidity_check_state = std::make_unique<SoilHumidityCheckState>(stub_get_soil_humidity_60_threshold_60);
            irrigate_soil_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IRRIGATE_SOIL);
            soil_periodic_check_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_SOIL_PERIODIC_CHECK);

            soil_humidity_check_state->SetTransitions(
                irrigate_soil_state_mock.get(),
                soil_periodic_check_state_mock.get()
            );

            system_core = std::make_unique<SystemCore>(
                soil_humidity_check_state.get()
            );
        }
};

class CoreInitialSoilPeriodicCheckWith3HoursAnd2HoursFromLastIrrigation : public ::testing::Test
{
    private:
        std::unique_ptr<SoilPeriodicCheckState> soil_periodic_check_state;
        std::unique_ptr<GeneralStateMock> irrigate_soil_state_mock;
        std::unique_ptr<GeneralStateMock> air_humidity_check_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {   
            soil_periodic_check_state = std::make_unique<SoilPeriodicCheckState>(
                stub_get_time_from_last_soil_irrigation_2_hours,
                3 * 60 * 60
            );

            irrigate_soil_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IRRIGATE_SOIL);
            air_humidity_check_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_AIR_HUMIDITY_CHECK);
            
            soil_periodic_check_state->SetTransitions(
                irrigate_soil_state_mock.get(),
                air_humidity_check_state_mock.get()
            );

            system_core = std::make_unique<SystemCore>(
                soil_periodic_check_state.get()
            );
        }
};

class CoreInitialSoilPeriodicCheckWith3HoursAnd3HoursFromLastIrrigation : public ::testing::Test
{
    private:
        std::unique_ptr<SoilPeriodicCheckState> soil_periodic_check_state;
        std::unique_ptr<GeneralStateMock> irrigate_soil_state_mock;
        std::unique_ptr<GeneralStateMock> air_humidity_check_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {   
            soil_periodic_check_state = std::make_unique<SoilPeriodicCheckState>(
                stub_get_time_from_last_soil_irrigation_3_hours,
                3 * 60 * 60
            );

            irrigate_soil_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IRRIGATE_SOIL);
            air_humidity_check_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_AIR_HUMIDITY_CHECK);
            
            soil_periodic_check_state->SetTransitions(
                irrigate_soil_state_mock.get(),
                air_humidity_check_state_mock.get()
            );

            system_core = std::make_unique<SystemCore>(
                soil_periodic_check_state.get()
            );
        }
};

class CoreInitialSoilPeriodicCheckWith3HoursAnd4HoursFromLastIrrigation : public ::testing::Test
{
    private:
        std::unique_ptr<SoilPeriodicCheckState> soil_periodic_check_state;
        std::unique_ptr<GeneralStateMock> irrigate_soil_state_mock;
        std::unique_ptr<GeneralStateMock> air_humidity_check_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {   
            soil_periodic_check_state = std::make_unique<SoilPeriodicCheckState>(
                stub_get_time_from_last_soil_irrigation_4_hours,
                3 * 60 * 60
            );

            irrigate_soil_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IRRIGATE_SOIL);
            air_humidity_check_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_AIR_HUMIDITY_CHECK);
            
            soil_periodic_check_state->SetTransitions(
                irrigate_soil_state_mock.get(),
                air_humidity_check_state_mock.get()
            );

            system_core = std::make_unique<SystemCore>(
                soil_periodic_check_state.get()
            );
        }
};

class CoreInitialIrrigateSoilWith10Seconds : public ::testing::Test
{
    private:
        std::unique_ptr<IrrigateSoilState> irrigate_soil_state;
        std::unique_ptr<GeneralStateMock> air_humidity_check_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        std::unique_ptr<IrrigatorMock> soil_irrigator_mock;
        
        void SetUp() override
        {
            soil_irrigator_mock = std::make_unique<IrrigatorMock>();
            air_humidity_check_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_AIR_HUMIDITY_CHECK);
            irrigate_soil_state = std::make_unique<IrrigateSoilState>(soil_irrigator_mock.get(), 10);

            irrigate_soil_state->SetTransitions(air_humidity_check_state_mock.get());            

            system_core = std::make_unique<SystemCore>(
                irrigate_soil_state.get()
            );
        }
};

class CoreInitialAirHumidityCheckWithRelativeHumidity50Threshold60 : public ::testing::Test
{
    private:
        std::unique_ptr<AirHumidityCheckState> air_humidity_check_state;
        std::unique_ptr<GeneralStateMock> irrigate_air_state_mock;
        std::unique_ptr<GeneralStateMock> air_periodic_check_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {
            air_humidity_check_state = std::make_unique<AirHumidityCheckState>(stub_get_air_humidity_50_threshold_60);
            irrigate_air_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IRRIGATE_AIR);
            air_periodic_check_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_AIR_PERIODIC_CHECK);

            air_humidity_check_state->SetTransitions(
                irrigate_air_state_mock.get(),
                air_periodic_check_state_mock.get()
            );

            system_core = std::make_unique<SystemCore>(
                air_humidity_check_state.get()
            );
        }
};

class CoreInitialAirHumidityCheckWithRelativeHumidity70Threshold60 : public ::testing::Test
{
    private:
        std::unique_ptr<AirHumidityCheckState> air_humidity_check_state;
        std::unique_ptr<GeneralStateMock> irrigate_air_state_mock;
        std::unique_ptr<GeneralStateMock> air_periodic_check_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {
            air_humidity_check_state = std::make_unique<AirHumidityCheckState>(stub_get_air_humidity_70_threshold_60);
            irrigate_air_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IRRIGATE_AIR);
            air_periodic_check_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_AIR_PERIODIC_CHECK);

            air_humidity_check_state->SetTransitions(
                irrigate_air_state_mock.get(),
                air_periodic_check_state_mock.get()
            );

            system_core = std::make_unique<SystemCore>(
                air_humidity_check_state.get()
            );
        }
};

class CoreInitialAirHumidityCheckWithRelativeHumidity60Threshold60 : public ::testing::Test
{
    private:
        std::unique_ptr<AirHumidityCheckState> air_humidity_check_state;
        std::unique_ptr<GeneralStateMock> irrigate_air_state_mock;
        std::unique_ptr<GeneralStateMock> air_periodic_check_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {
            air_humidity_check_state = std::make_unique<AirHumidityCheckState>(stub_get_air_humidity_60_threshold_60);
            irrigate_air_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IRRIGATE_AIR);
            air_periodic_check_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_AIR_PERIODIC_CHECK);

            air_humidity_check_state->SetTransitions(
                irrigate_air_state_mock.get(),
                air_periodic_check_state_mock.get()
            );

            system_core = std::make_unique<SystemCore>(
                air_humidity_check_state.get()
            );
        }
};

class CoreInitialAirPeriodicCheckWith3HoursAnd2HoursFromLastIrrigation : public ::testing::Test
{
    private:
        std::unique_ptr<AirPeriodicCheckState> air_periodic_check_state;
        std::unique_ptr<GeneralStateMock> irrigate_air_state_mock;
        std::unique_ptr<GeneralStateMock> wrap_up_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {   
            air_periodic_check_state = std::make_unique<AirPeriodicCheckState>(stub_get_time_from_last_air_irrigation_2_hours, 3 * 60 * 60);
            irrigate_air_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IRRIGATE_AIR);
            wrap_up_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_WRAP_UP);

            air_periodic_check_state->SetTransitions(
                irrigate_air_state_mock.get(),
                wrap_up_state_mock.get()
            );

            system_core = std::make_unique<SystemCore>(
                air_periodic_check_state.get()
            );
        }
};

class CoreInitialAirPeriodicCheckWith3HoursAnd3HoursFromLastIrrigation : public ::testing::Test
{
    private:
        std::unique_ptr<AirPeriodicCheckState> air_periodic_check_state;
        std::unique_ptr<GeneralStateMock> irrigate_air_state_mock;
        std::unique_ptr<GeneralStateMock> wrap_up_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {   
            air_periodic_check_state = std::make_unique<AirPeriodicCheckState>(stub_get_time_from_last_air_irrigation_3_hours, 3 * 60 * 60);
            irrigate_air_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IRRIGATE_AIR);
            wrap_up_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_WRAP_UP);

            air_periodic_check_state->SetTransitions(
                irrigate_air_state_mock.get(),
                wrap_up_state_mock.get()
            );

            system_core = std::make_unique<SystemCore>(
                air_periodic_check_state.get()
            );
        }
};

class CoreInitialAirPeriodicCheckWith3HoursAnd4HoursFromLastIrrigation : public ::testing::Test
{
    private:
        std::unique_ptr<AirPeriodicCheckState> air_periodic_check_state;
        std::unique_ptr<GeneralStateMock> irrigate_air_state_mock;
        std::unique_ptr<GeneralStateMock> wrap_up_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        
        void SetUp() override
        {   
            air_periodic_check_state = std::make_unique<AirPeriodicCheckState>(stub_get_time_from_last_air_irrigation_4_hours, 3 * 60 * 60);
            irrigate_air_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IRRIGATE_AIR);
            wrap_up_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_WRAP_UP);

            air_periodic_check_state->SetTransitions(
                irrigate_air_state_mock.get(),
                wrap_up_state_mock.get()
            );

            system_core = std::make_unique<SystemCore>(
                air_periodic_check_state.get()
            );
        }
};

class CoreInitialIrrigateAirWith10Seconds : public ::testing::Test
{
    private:
        std::unique_ptr<IrrigateAirState> irrigate_air_state;
        std::unique_ptr<GeneralStateMock> wrap_up_state_mock;

    protected:
        std::unique_ptr<SystemCore> system_core;
        std::unique_ptr<IrrigatorMock> air_irrigator_mock;
        
        void SetUp() override
        {
            air_irrigator_mock = std::make_unique<IrrigatorMock>();
            wrap_up_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_WRAP_UP);
            irrigate_air_state = std::make_unique<IrrigateAirState>(air_irrigator_mock.get(), 10);

            irrigate_air_state->SetTransitions(wrap_up_state_mock.get());
            
            system_core = std::make_unique<SystemCore>(
                irrigate_air_state.get()
            );
        }
};

class CoreInitialWrapUp : public ::testing::Test
{
    private:
        std::unique_ptr<WrapUpState> wrap_up_state;
        std::unique_ptr<GeneralStateMock> idle_state_mock;
        
    protected:
        std::unique_ptr<SystemCore> system_core;
        std::unique_ptr<WrapUpActionMock> wrap_up_action_mock;
        
        void SetUp() override
        {
            wrap_up_action_mock = std::make_unique<WrapUpActionMock>();
            wrap_up_state = std::make_unique<WrapUpState>(wrap_up_action_mock.get());
            idle_state_mock = std::make_unique<GeneralStateMock>(CoreState::CORE_STATE_IDLE);

            wrap_up_state->SetTransitions(idle_state_mock.get());

            system_core = std::make_unique<SystemCore>(
                wrap_up_state.get()
            );
        }
};

TEST_F(CoreInitialIdleWithWakeUpTrue, ShouldBeIdleWhenIdleState)
{
    /* Given fixture */
    /* When */
    CoreState current_state = system_core->GetCurrentState();

    /* Then */
    EXPECT_EQ(current_state, CoreState::CORE_STATE_IDLE);
}

TEST_F(CoreInitialIdleWithWakeUpTrue, ShouldBeWokeStateWhenIdleStateAndAdvancingCycleAndWakeUpCallbackIsTrue)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_WOKE);
}

TEST_F(CoreInitialIdleWithWakeUpFalse, ShouldBeIdleStateWhenIdleStateAndAdvancingCycleAndWakeUpCallbackIsFalse)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_IDLE);
}

TEST_F(CoreInitialWoke, ShouldBeWokeWhenWokeState)
{
    /* Given fixture */
    /* When */
    CoreState current_state = system_core->GetCurrentState();

    /* Then */
    EXPECT_EQ(current_state, CoreState::CORE_STATE_WOKE);
}

TEST_F(CoreInitialWoke, ShouldBeSoilHumidityCheckStateWhenWokeStateAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_SOIL_HUMIDITY_CHECK);
}

TEST_F(CoreInitialSoilHumidityCheckWithRelativeHumidity50Threshold60, ShouldBeSoilHumidityCheckWhenSoilHumidityCheckState)
{
    /* Given fixture */
    /* When */
    CoreState current_state = system_core->GetCurrentState();

    /* Then */
    EXPECT_EQ(current_state, CoreState::CORE_STATE_SOIL_HUMIDITY_CHECK);
}

TEST_F(CoreInitialSoilHumidityCheckWithRelativeHumidity50Threshold60, ShouldBeIrrigateSoilWhenSoilHumidityCheckStateAndRelativeHumidityBelowThresholdAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_IRRIGATE_SOIL);
}

TEST_F(CoreInitialSoilHumidityCheckWithRelativeHumidity70Threshold60, ShouldBeSoilPeriodicCheckStateWhenSoilHumidityCheckStateAndRelativeHumidityAboveThresholdAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_SOIL_PERIODIC_CHECK);
}

TEST_F(CoreInitialSoilHumidityCheckWithRelativeHumidity60Threshold60, ShouldBeSoilPeriodicCheckStateWhenSoilHumidityCheckStateAndRelativeHumidityEqualThresholdAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_SOIL_PERIODIC_CHECK);
}

TEST_F(CoreInitialSoilPeriodicCheckWith3HoursAnd2HoursFromLastIrrigation, ShouldBeSoilPeriodicCheckWhenSoilPeriodicCheckState)
{
    /* Given fixture */
    /* When */
    CoreState current_state = system_core->GetCurrentState();

    /* Then */
    EXPECT_EQ(current_state, CoreState::CORE_STATE_SOIL_PERIODIC_CHECK);
}

TEST_F(CoreInitialSoilPeriodicCheckWith3HoursAnd2HoursFromLastIrrigation, ShouldBeAirHumidityCheckStateWhenSoilPeriodicCheckStateAndTimeFromLastIrrigationIsLessThanMaximumPeriodAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_AIR_HUMIDITY_CHECK);
}

TEST_F(CoreInitialSoilPeriodicCheckWith3HoursAnd3HoursFromLastIrrigation, ShouldBeAirHumidityCheckStateWhenSoilPeriodicCheckStateAndTimeFromLastIrrigationIsEqualToMaximumPeriodAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_AIR_HUMIDITY_CHECK);
}

TEST_F(CoreInitialSoilPeriodicCheckWith3HoursAnd4HoursFromLastIrrigation, ShouldBeAirHumidityCheckStateWhenSoilPeriodicCheckStateAndTimeFromLastIrrigationIsGreaterThanMaximumPeriodAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_IRRIGATE_SOIL);
}

TEST_F(CoreInitialIrrigateSoilWith10Seconds, ShouldBeIrrigateSoilWhenIrrigateSoilState)
{
    /* Given fixture */
    /* When */
    CoreState current_state = system_core->GetCurrentState();

    /* Then */
    EXPECT_EQ(current_state, CoreState::CORE_STATE_IRRIGATE_SOIL);
}

TEST_F(CoreInitialIrrigateSoilWith10Seconds, ShouldIrrigateSoilFor10SecondsWhenAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(soil_irrigator_mock->GetLastIrrigationTime(), 10);
}

TEST_F(CoreInitialIrrigateSoilWith10Seconds, ShouldBeAirHumidityCheckStateWhenIrrigateSoilStateAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_AIR_HUMIDITY_CHECK);
}

TEST_F(CoreInitialAirHumidityCheckWithRelativeHumidity50Threshold60, ShouldBeAirHumidityCheckWhenAirHumidityCheckState)
{
    /* Given fixture */
    /* When */
    CoreState current_state = system_core->GetCurrentState();

    /* Then */
    EXPECT_EQ(current_state, CoreState::CORE_STATE_AIR_HUMIDITY_CHECK);
}

TEST_F(CoreInitialAirHumidityCheckWithRelativeHumidity50Threshold60, ShouldBeIrrigateAirWhenAirHumidityCheckStateAndRelativeHumidityBelowThresholdAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_IRRIGATE_AIR);
}

TEST_F(CoreInitialAirHumidityCheckWithRelativeHumidity70Threshold60, ShouldBeAirPeriodicCheckStateWhenAirHumidityCheckStateAndRelativeHumidityAboveThresholdAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_AIR_PERIODIC_CHECK);
}

TEST_F(CoreInitialAirHumidityCheckWithRelativeHumidity60Threshold60, ShouldBeAirPeriodicCheckStateWhenAirHumidityCheckStateAndRelativeHumidityEqualThresholdAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_AIR_PERIODIC_CHECK);
}

TEST_F(CoreInitialAirPeriodicCheckWith3HoursAnd2HoursFromLastIrrigation, ShouldBeAirPeriodicCheckWhenAirPeriodicCheckState)
{
    /* Given fixture */
    /* When */
    CoreState current_state = system_core->GetCurrentState();

    /* Then */
    EXPECT_EQ(current_state, CoreState::CORE_STATE_AIR_PERIODIC_CHECK);
}

TEST_F(CoreInitialAirPeriodicCheckWith3HoursAnd2HoursFromLastIrrigation, ShouldBeWrapUpStateWhenAirPeriodicCheckStateAndTimeFromLastIrrigationIsLessThanMaximumPeriodAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_WRAP_UP);
}

TEST_F(CoreInitialAirPeriodicCheckWith3HoursAnd3HoursFromLastIrrigation, ShouldBeWrapUpStateWhenAirPeriodicCheckStateAndTimeFromLastIrrigationIsEqualToMaximumPeriodAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_WRAP_UP);
}

TEST_F(CoreInitialAirPeriodicCheckWith3HoursAnd4HoursFromLastIrrigation, ShouldBeWrapUpStateWhenAirPeriodicCheckStateAndTimeFromLastIrrigationIsGreaterThanMaximumPeriodAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_IRRIGATE_AIR);
}

TEST_F(CoreInitialIrrigateAirWith10Seconds, ShouldBeIrrigateAirWhenIrrigateAirState)
{
    /* Given fixture */
    /* When */
    CoreState current_state = system_core->GetCurrentState();

    /* Then */
    EXPECT_EQ(current_state, CoreState::CORE_STATE_IRRIGATE_AIR);
}

TEST_F(CoreInitialIrrigateAirWith10Seconds, ShouldIrrigateAirFor10SecondsWhenAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(air_irrigator_mock->GetLastIrrigationTime(), 10);
}

TEST_F(CoreInitialIrrigateAirWith10Seconds, ShouldBeWrapUpStateWhenIrrigateAirStateAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_WRAP_UP);
}

TEST_F(CoreInitialWrapUp, ShouldBeWrapUpWhenWrapUpState)
{
    /* Given fixture */
    /* When */
    CoreState current_state = system_core->GetCurrentState();

    /* Then */
    EXPECT_EQ(current_state, CoreState::CORE_STATE_WRAP_UP);
}

TEST_F(CoreInitialWrapUp, ShouldExecuteWrapUpActionWhenWrapUpStateAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(wrap_up_action_mock->GetNumberOfCalls(), 1);
}

TEST_F(CoreInitialWrapUp, ShouldBeIdleWhenWrapUpStateAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    system_core->AdvanceCycle();

    /* Then */
    EXPECT_EQ(system_core->GetCurrentState(), CoreState::CORE_STATE_IDLE);
}