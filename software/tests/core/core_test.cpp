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


class CoreInitialIdleWithWakeUpTrue : public ::testing::Test
{
    private:
        IdleState* idle_state;
        GeneralStateMock* woke_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {
            idle_state = new IdleState(stub_should_wake_up_true);
            woke_state_mock = new GeneralStateMock(CoreState::CORE_STATE_WOKE);

            idle_state->SetTransitions(woke_state_mock);

            system_core = new SystemCore(
                idle_state
            );
        }
};

class CoreInitialIdleWithWakeUpFalse : public ::testing::Test
{
    private:
        IdleState* idle_state;
        GeneralStateMock* woke_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {
            idle_state = new IdleState(stub_should_wake_up_false);
            woke_state_mock = new GeneralStateMock(CoreState::CORE_STATE_WOKE);

            idle_state->SetTransitions(woke_state_mock);

            system_core = new SystemCore(
                idle_state
            );
        }
};

class CoreInitialWoke : public ::testing::Test
{
    private:
        WokeState* woke_state;
        GeneralStateMock* soil_humidity_check_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {
            woke_state = new WokeState();
            soil_humidity_check_state_mock = new GeneralStateMock(CoreState::CORE_STATE_SOIL_HUMIDITY_CHECK);
            
            woke_state->SetTransitions(soil_humidity_check_state_mock);
            
            system_core = new SystemCore(
                woke_state
            );
        }
};

class CoreInitialSoilHumidityCheckWithRelativeHumidity50Threshold60 : public ::testing::Test
{
    private:
        SoilHumidityCheckState* soil_humidity_check_state;
        GeneralStateMock* irrigate_soil_state_mock;
        GeneralStateMock* soil_periodic_check_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {
            soil_humidity_check_state = new SoilHumidityCheckState(stub_get_soil_humidity_50_threshold_60);
            irrigate_soil_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IRRIGATE_SOIL);
            soil_periodic_check_state_mock = new GeneralStateMock(CoreState::CORE_STATE_SOIL_PERIODIC_CHECK);

            soil_humidity_check_state->SetTransitions(
                irrigate_soil_state_mock,
                soil_periodic_check_state_mock
            );

            system_core = new SystemCore(
                soil_humidity_check_state
            );
        }
};

class CoreInitialSoilHumidityCheckWithRelativeHumidity70Threshold60 : public ::testing::Test
{
    private:
        SoilHumidityCheckState* soil_humidity_check_state;
        GeneralStateMock* irrigate_soil_state_mock;
        GeneralStateMock* soil_periodic_check_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {
            soil_humidity_check_state = new SoilHumidityCheckState(stub_get_soil_humidity_70_threshold_60);
            irrigate_soil_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IRRIGATE_SOIL);
            soil_periodic_check_state_mock = new GeneralStateMock(CoreState::CORE_STATE_SOIL_PERIODIC_CHECK);

            soil_humidity_check_state->SetTransitions(
                irrigate_soil_state_mock,
                soil_periodic_check_state_mock
            );

            system_core = new SystemCore(
                soil_humidity_check_state
            );
        }
};

class CoreInitialSoilHumidityCheckWithRelativeHumidity60Threshold60 : public ::testing::Test
{
    private:
        SoilHumidityCheckState* soil_humidity_check_state;
        GeneralStateMock* irrigate_soil_state_mock;
        GeneralStateMock* soil_periodic_check_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {
            soil_humidity_check_state = new SoilHumidityCheckState(stub_get_soil_humidity_60_threshold_60);
            irrigate_soil_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IRRIGATE_SOIL);
            soil_periodic_check_state_mock = new GeneralStateMock(CoreState::CORE_STATE_SOIL_PERIODIC_CHECK);

            soil_humidity_check_state->SetTransitions(
                irrigate_soil_state_mock,
                soil_periodic_check_state_mock
            );

            system_core = new SystemCore(
                soil_humidity_check_state
            );
        }
};

class CoreInitialSoilPeriodicCheckWith3HoursAnd2HoursFromLastIrrigation : public ::testing::Test
{
    private:
        SoilPeriodicCheckState* soil_periodic_check_state;
        GeneralStateMock* irrigate_soil_state_mock;
        GeneralStateMock* air_humidity_check_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {   
            soil_periodic_check_state = new SoilPeriodicCheckState(
                stub_get_time_from_last_soil_irrigation_2_hours,
                3 * 60 * 60
            );

            irrigate_soil_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IRRIGATE_SOIL);
            air_humidity_check_state_mock = new GeneralStateMock(CoreState::CORE_STATE_AIR_HUMIDITY_CHECK);
            
            soil_periodic_check_state->SetTransitions(
                irrigate_soil_state_mock,
                air_humidity_check_state_mock
            );

            system_core = new SystemCore(
                soil_periodic_check_state
            );
        }
};

class CoreInitialSoilPeriodicCheckWith3HoursAnd3HoursFromLastIrrigation : public ::testing::Test
{
    private:
        SoilPeriodicCheckState* soil_periodic_check_state;
        GeneralStateMock* irrigate_soil_state_mock;
        GeneralStateMock* air_humidity_check_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {   
            soil_periodic_check_state = new SoilPeriodicCheckState(
                stub_get_time_from_last_soil_irrigation_3_hours,
                3 * 60 * 60
            );

            irrigate_soil_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IRRIGATE_SOIL);
            air_humidity_check_state_mock = new GeneralStateMock(CoreState::CORE_STATE_AIR_HUMIDITY_CHECK);
            
            soil_periodic_check_state->SetTransitions(
                irrigate_soil_state_mock,
                air_humidity_check_state_mock
            );

            system_core = new SystemCore(
                soil_periodic_check_state
            );
        }
};

class CoreInitialSoilPeriodicCheckWith3HoursAnd4HoursFromLastIrrigation : public ::testing::Test
{
    private:
        SoilPeriodicCheckState* soil_periodic_check_state;
        GeneralStateMock* irrigate_soil_state_mock;
        GeneralStateMock* air_humidity_check_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {   
            soil_periodic_check_state = new SoilPeriodicCheckState(
                stub_get_time_from_last_soil_irrigation_4_hours,
                3 * 60 * 60
            );

            irrigate_soil_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IRRIGATE_SOIL);
            air_humidity_check_state_mock = new GeneralStateMock(CoreState::CORE_STATE_AIR_HUMIDITY_CHECK);
            
            soil_periodic_check_state->SetTransitions(
                irrigate_soil_state_mock,
                air_humidity_check_state_mock
            );

            system_core = new SystemCore(
                soil_periodic_check_state
            );
        }
};

class CoreInitialIrrigateSoilWith10Seconds : public ::testing::Test
{
    private:
        IrrigateSoilState* irrigate_soil_state;
        GeneralStateMock* air_humidity_check_state_mock;

    protected:
        SystemCore* system_core;
        IrrigatorMock* soil_irrigator_mock;
        
        void SetUp() override
        {
            soil_irrigator_mock = new IrrigatorMock();
            air_humidity_check_state_mock = new GeneralStateMock(CoreState::CORE_STATE_AIR_HUMIDITY_CHECK);
            irrigate_soil_state = new IrrigateSoilState(soil_irrigator_mock, 10);

            irrigate_soil_state->SetTransitions(air_humidity_check_state_mock);            

            system_core = new SystemCore(
                irrigate_soil_state
            );
        }
};

class CoreInitialAirHumidityCheckWithRelativeHumidity50Threshold60 : public ::testing::Test
{
    private:
        AirHumidityCheckState* air_humidity_check_state;
        GeneralStateMock* irrigate_air_state_mock;
        GeneralStateMock* air_periodic_check_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {
            air_humidity_check_state = new AirHumidityCheckState(stub_get_air_humidity_50_threshold_60);
            irrigate_air_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IRRIGATE_AIR);
            air_periodic_check_state_mock = new GeneralStateMock(CoreState::CORE_STATE_AIR_PERIODIC_CHECK);

            air_humidity_check_state->SetTransitions(
                irrigate_air_state_mock,
                air_periodic_check_state_mock
            );

            system_core = new SystemCore(
                air_humidity_check_state
            );
        }
};

class CoreInitialAirHumidityCheckWithRelativeHumidity70Threshold60 : public ::testing::Test
{
    private:
        AirHumidityCheckState* air_humidity_check_state;
        GeneralStateMock* irrigate_air_state_mock;
        GeneralStateMock* air_periodic_check_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {
            air_humidity_check_state = new AirHumidityCheckState(stub_get_air_humidity_70_threshold_60);
            irrigate_air_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IRRIGATE_AIR);
            air_periodic_check_state_mock = new GeneralStateMock(CoreState::CORE_STATE_AIR_PERIODIC_CHECK);

            air_humidity_check_state->SetTransitions(
                irrigate_air_state_mock,
                air_periodic_check_state_mock
            );

            system_core = new SystemCore(
                air_humidity_check_state
            );
        }
};

class CoreInitialAirHumidityCheckWithRelativeHumidity60Threshold60 : public ::testing::Test
{
    private:
        AirHumidityCheckState* air_humidity_check_state;
        GeneralStateMock* irrigate_air_state_mock;
        GeneralStateMock* air_periodic_check_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {
            air_humidity_check_state = new AirHumidityCheckState(stub_get_air_humidity_60_threshold_60);
            irrigate_air_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IRRIGATE_AIR);
            air_periodic_check_state_mock = new GeneralStateMock(CoreState::CORE_STATE_AIR_PERIODIC_CHECK);

            air_humidity_check_state->SetTransitions(
                irrigate_air_state_mock,
                air_periodic_check_state_mock
            );

            system_core = new SystemCore(
                air_humidity_check_state
            );
        }
};

class CoreInitialAirPeriodicCheckWith3HoursAnd2HoursFromLastIrrigation : public ::testing::Test
{
    private:
        AirPeriodicCheckState* air_periodic_check_state;
        GeneralStateMock* irrigate_air_state_mock;
        GeneralStateMock* wrap_up_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {   
            air_periodic_check_state = new AirPeriodicCheckState(stub_get_time_from_last_air_irrigation_2_hours, 3 * 60 * 60);
            irrigate_air_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IRRIGATE_AIR);
            wrap_up_state_mock = new GeneralStateMock(CoreState::CORE_STATE_WRAP_UP);

            air_periodic_check_state->SetTransitions(
                irrigate_air_state_mock,
                wrap_up_state_mock
            );

            system_core = new SystemCore(
                air_periodic_check_state
            );
        }
};

class CoreInitialAirPeriodicCheckWith3HoursAnd3HoursFromLastIrrigation : public ::testing::Test
{
    private:
        AirPeriodicCheckState* air_periodic_check_state;
        GeneralStateMock* irrigate_air_state_mock;
        GeneralStateMock* wrap_up_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {   
            air_periodic_check_state = new AirPeriodicCheckState(stub_get_time_from_last_air_irrigation_3_hours, 3 * 60 * 60);
            irrigate_air_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IRRIGATE_AIR);
            wrap_up_state_mock = new GeneralStateMock(CoreState::CORE_STATE_WRAP_UP);

            air_periodic_check_state->SetTransitions(
                irrigate_air_state_mock,
                wrap_up_state_mock
            );

            system_core = new SystemCore(
                air_periodic_check_state
            );
        }
};

class CoreInitialAirPeriodicCheckWith3HoursAnd4HoursFromLastIrrigation : public ::testing::Test
{
    private:
        AirPeriodicCheckState* air_periodic_check_state;
        GeneralStateMock* irrigate_air_state_mock;
        GeneralStateMock* wrap_up_state_mock;

    protected:
        SystemCore* system_core;
        
        void SetUp() override
        {   
            air_periodic_check_state = new AirPeriodicCheckState(stub_get_time_from_last_air_irrigation_4_hours, 3 * 60 * 60);
            irrigate_air_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IRRIGATE_AIR);
            wrap_up_state_mock = new GeneralStateMock(CoreState::CORE_STATE_WRAP_UP);

            air_periodic_check_state->SetTransitions(
                irrigate_air_state_mock,
                wrap_up_state_mock
            );

            system_core = new SystemCore(
                air_periodic_check_state
            );
        }
};

class CoreInitialIrrigateAirWith10Seconds : public ::testing::Test
{
    private:
        IrrigateAirState* irrigate_air_state;
        GeneralStateMock* wrap_up_state_mock;

    protected:
        SystemCore* system_core;
        IrrigatorMock* air_irrigator_mock;
        
        void SetUp() override
        {
            air_irrigator_mock = new IrrigatorMock();
            wrap_up_state_mock = new GeneralStateMock(CoreState::CORE_STATE_WRAP_UP);
            irrigate_air_state = new IrrigateAirState(air_irrigator_mock, 10);

            irrigate_air_state->SetTransitions(wrap_up_state_mock);
            
            system_core = new SystemCore(
                irrigate_air_state
            );
        }
};

class CoreInitialWrapUp : public ::testing::Test
{
    private:
        WrapUpState* wrap_up_state;
        GeneralStateMock* idle_state_mock;
        
    protected:
        SystemCore* system_core;
        WrapUpActionMock* wrap_up_action_mock;
        
        void SetUp() override
        {
            wrap_up_action_mock = new WrapUpActionMock();
            wrap_up_state = new WrapUpState(wrap_up_action_mock);
            idle_state_mock = new GeneralStateMock(CoreState::CORE_STATE_IDLE);

            wrap_up_state->SetTransitions(idle_state_mock);

            system_core = new SystemCore(
                wrap_up_state
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