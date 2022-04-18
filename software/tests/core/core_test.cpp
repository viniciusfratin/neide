#include "gtest/gtest.h"

extern "C"
{
#include "core_states.h"
#include "core_state_interface.h"
#include "core.h"
#include "idle_state.h"
#include "woke_state.h"
#include "soil_humidity_check_state.h"
}

#include "stubs_cpp.hpp"
#include "mocks_cpp.hpp"

class CoreInitialIdleWithWakeUpTrue : public ::testing::Test
{
    private:
        IdleState idle_state;
        GeneralStateMock woke_state_mock;
        CoreStateInterface idle_state_interface;
        CoreStateInterface woke_state_mock_interface;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            idle_state = IdleState_Construct(stub_should_wake_up_true, &woke_state_mock_interface);
            woke_state_mock = GeneralStateMock_Construct(CORE_STATE_WOKE);

            idle_state_interface = IdleState_GetCoreStateInterface(idle_state);
            woke_state_mock_interface = GeneralStateMock_GetCoreStateInterface(woke_state_mock);

            system_core = SystemCore_Construct(
                idle_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&woke_state_mock);
            IdleState_Destruct(&idle_state);
            SystemCore_Destruct(&system_core);
        }
};

class CoreInitialIdleWithWakeUpFalse : public ::testing::Test
{
    private:
        IdleState idle_state;
        GeneralStateMock woke_state_mock;
        CoreStateInterface idle_state_interface;
        CoreStateInterface woke_state_mock_interface;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            idle_state = IdleState_Construct(stub_should_wake_up_false, &woke_state_mock_interface);
            woke_state_mock = GeneralStateMock_Construct(CORE_STATE_WOKE);

            idle_state_interface = IdleState_GetCoreStateInterface(idle_state);
            woke_state_mock_interface = GeneralStateMock_GetCoreStateInterface(woke_state_mock);

            system_core = SystemCore_Construct(
                idle_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&woke_state_mock);
            IdleState_Destruct(&idle_state);
            SystemCore_Destruct(&system_core);
        }
};

class CoreInitialWoke : public ::testing::Test
{
    private:
        WokeState woke_state;
        GeneralStateMock soil_humidity_check_state_mock;
        CoreStateInterface woke_state_interface;
        CoreStateInterface soil_humidity_check_state_mock_interface;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            woke_state = WokeState_Construct(&soil_humidity_check_state_mock_interface);
            soil_humidity_check_state_mock = GeneralStateMock_Construct(CORE_STATE_SOIL_HUMIDITY_CHECK);

            woke_state_interface = WokeState_GetCoreStateInterface(woke_state);
            soil_humidity_check_state_mock_interface = GeneralStateMock_GetCoreStateInterface(soil_humidity_check_state_mock);

            system_core = SystemCore_Construct(
                woke_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&soil_humidity_check_state_mock);
            WokeState_Destruct(&woke_state);
            SystemCore_Destruct(&system_core);
        }
};

class CoreInitialSoilHumidityCheckWithRelativeHumidity50Threshold60 : public ::testing::Test
{
    private:
        SoilHumidityCheckState soil_humidity_check_state;
        GeneralStateMock irrigate_soil_state_mock;
        GeneralStateMock soil_periodic_check_state_mock;

        CoreStateInterface soil_humidity_check_state_interface;
        CoreStateInterface irrigate_soil_state_mock_interface;
        CoreStateInterface soil_periodic_check_state_mock_interface;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            soil_humidity_check_state = SoilHumidityCheckState_Construct(
                stub_get_soil_humidity_50_threshold_60,
                &irrigate_soil_state_mock_interface,
                &soil_periodic_check_state_mock_interface
            );
            irrigate_soil_state_mock = GeneralStateMock_Construct(CORE_STATE_IRRIGATE_SOIL);
            soil_periodic_check_state_mock = GeneralStateMock_Construct(CORE_STATE_SOIL_PERIODIC_CHECK);
            
            soil_humidity_check_state_interface = SoilHumidityCheckState_GetCoreStateInterface(soil_humidity_check_state);
            irrigate_soil_state_mock_interface = GeneralStateMock_GetCoreStateInterface(irrigate_soil_state_mock);
            soil_periodic_check_state_mock_interface = GeneralStateMock_GetCoreStateInterface(soil_periodic_check_state_mock);

            system_core = SystemCore_Construct(
                soil_humidity_check_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&soil_periodic_check_state_mock);
            GeneralStateMock_Destruct(&irrigate_soil_state_mock);
            SoilHumidityCheckState_Destruct(&soil_humidity_check_state);
            SystemCore_Destruct(&system_core);
        }
};

class CoreInitialSoilHumidityCheckWithRelativeHumidity70Threshold60 : public ::testing::Test
{
    private:
        SoilHumidityCheckState soil_humidity_check_state;
        GeneralStateMock irrigate_soil_state_mock;
        GeneralStateMock soil_periodic_check_state_mock;

        CoreStateInterface soil_humidity_check_state_interface;
        CoreStateInterface irrigate_soil_state_mock_interface;
        CoreStateInterface soil_periodic_check_state_mock_interface;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            soil_humidity_check_state = SoilHumidityCheckState_Construct(
                stub_get_soil_humidity_70_threshold_60,
                &irrigate_soil_state_mock_interface,
                &soil_periodic_check_state_mock_interface
            );
            irrigate_soil_state_mock = GeneralStateMock_Construct(CORE_STATE_IRRIGATE_SOIL);
            soil_periodic_check_state_mock = GeneralStateMock_Construct(CORE_STATE_SOIL_PERIODIC_CHECK);

            soil_humidity_check_state_interface = SoilHumidityCheckState_GetCoreStateInterface(soil_humidity_check_state);
            irrigate_soil_state_mock_interface = GeneralStateMock_GetCoreStateInterface(irrigate_soil_state_mock);
            soil_periodic_check_state_mock_interface = GeneralStateMock_GetCoreStateInterface(soil_periodic_check_state_mock);

            system_core = SystemCore_Construct(
                soil_humidity_check_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&soil_periodic_check_state_mock);
            GeneralStateMock_Destruct(&irrigate_soil_state_mock);
            SoilHumidityCheckState_Destruct(&soil_humidity_check_state);
            SystemCore_Destruct(&system_core);
        }
};

class CoreInitialSoilHumidityCheckWithRelativeHumidity60Threshold60 : public ::testing::Test
{
    private:
        SoilHumidityCheckState soil_humidity_check_state;
        GeneralStateMock irrigate_soil_state_mock;
        GeneralStateMock soil_periodic_check_state_mock;

        CoreStateInterface soil_humidity_check_state_interface;
        CoreStateInterface irrigate_soil_state_mock_interface;
        CoreStateInterface soil_periodic_check_state_mock_interface;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            soil_humidity_check_state = SoilHumidityCheckState_Construct(
                stub_get_soil_humidity_60_threshold_60,
                &irrigate_soil_state_mock_interface,
                &soil_periodic_check_state_mock_interface
            );
            irrigate_soil_state_mock = GeneralStateMock_Construct(CORE_STATE_IRRIGATE_SOIL);
            soil_periodic_check_state_mock = GeneralStateMock_Construct(CORE_STATE_SOIL_PERIODIC_CHECK);

            soil_humidity_check_state_interface = SoilHumidityCheckState_GetCoreStateInterface(soil_humidity_check_state);
            irrigate_soil_state_mock_interface = GeneralStateMock_GetCoreStateInterface(irrigate_soil_state_mock);
            soil_periodic_check_state_mock_interface = GeneralStateMock_GetCoreStateInterface(soil_periodic_check_state_mock);
            
            system_core = SystemCore_Construct(
                soil_humidity_check_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&soil_periodic_check_state_mock);
            GeneralStateMock_Destruct(&irrigate_soil_state_mock);
            SoilHumidityCheckState_Destruct(&soil_humidity_check_state);
            SystemCore_Destruct(&system_core);
        }
};

TEST_F(CoreInitialIdleWithWakeUpTrue, ShouldBeIdleWhenIdleState)
{
	/* Given fixture */
	/* When */
	CoreState current_state = SystemCore_GetCurrentState(system_core);

	/* Then */
	EXPECT_EQ(current_state, CORE_STATE_IDLE);
}

TEST_F(CoreInitialIdleWithWakeUpTrue, ShouldBeWokeStateWhenIdleStateAndAdvancingCycleAndWakeUpCallbackIsTrue)
{
	/* Given fixture */
	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_WOKE);
}

TEST_F(CoreInitialIdleWithWakeUpFalse, ShouldBeIdleStateWhenIdleStateAndAdvancingCycleAndWakeUpCallbackIsFalse)
{
	/* Given fixture */
	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_IDLE);
}

TEST_F(CoreInitialWoke, ShouldBeSoilHumidityCheckStateWhenWokeStateAndAdvancingCycle)
{
	/* Given fixture */
	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_SOIL_HUMIDITY_CHECK);
}

TEST_F(CoreInitialSoilHumidityCheckWithRelativeHumidity50Threshold60, ShouldBeIrrigateSoilWhenSoilHumidityCheckStateAndRelativeHumidityBelowThresholdAndAdvancingCycle)
{
    /* Given fixture */
	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_IRRIGATE_SOIL);
}

TEST_F(CoreInitialSoilHumidityCheckWithRelativeHumidity70Threshold60, ShouldBeSoilPeriodicCheckStateWhenSoilHumidityCheckStateAndRelativeHumidityAboveThresholdAndAdvancingCycle)
{
    /* Given fixture */
	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_SOIL_PERIODIC_CHECK);
}

TEST_F(CoreInitialSoilHumidityCheckWithRelativeHumidity60Threshold60, ShouldBeSoilPeriodicCheckStateWhenSoilHumidityCheckStateAndRelativeHumidityEqualThresholdAndAdvancingCycle)
{
    /* Given fixture */
	/* When */
	SystemCore_AdvanceCycle(system_core);

	/* Then */
	EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_SOIL_PERIODIC_CHECK);
}
