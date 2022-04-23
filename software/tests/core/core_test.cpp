#include "gtest/gtest.h"

extern "C"
{
#include "core_states.h"
#include "core_state_interface.h"
#include "core.h"
#include "idle_state.h"
#include "woke_state.h"
#include "soil_humidity_check_state.h"
#include "irrigate_soil_state.h"
#include "soil_irrigator_interface.h"
#include "air_humidity_check_state.h"
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

class CoreInitialIrrigateSoilWith10Seconds : public ::testing::Test
{
    private:
        IrrigateSoilState irrigate_soil_state;
        GeneralStateMock air_humidity_check_state_mock;

        CoreStateInterface irrigate_soil_state_interface;
        SoilIrrigatorInterface soil_irrigator_mock_interface;
        CoreStateInterface air_humidity_check_state_mock_interface;

    protected:
        SystemCore system_core;
        SoilIrrigatorMock soil_irrigator_mock;
        
        void SetUp() override
        {
            soil_irrigator_mock = SoilIrrigatorMock_Construct();
            soil_irrigator_mock_interface = SoilIrrigatorMock_GetSoilIrrigatorInterface(soil_irrigator_mock);
            
            air_humidity_check_state_mock = GeneralStateMock_Construct(CORE_STATE_AIR_HUMIDITY_CHECK);
            air_humidity_check_state_mock_interface = GeneralStateMock_GetCoreStateInterface(air_humidity_check_state_mock);
            
            irrigate_soil_state = IrrigateSoilState_Construct(
                &air_humidity_check_state_mock_interface,
                &soil_irrigator_mock_interface,
                10);
            irrigate_soil_state_interface = IrrigateSoilState_GetCoreStateInterface(irrigate_soil_state);

            system_core = SystemCore_Construct(
                irrigate_soil_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&air_humidity_check_state_mock);
            IrrigateSoilState_Destruct(&irrigate_soil_state);
            SoilIrrigatorMock_Destruct(&soil_irrigator_mock);
            SystemCore_Destruct(&system_core);
        }
};

class CoreInitialAirHumidityCheckWithRelativeHumidity50Threshold60 : public ::testing::Test
{
    private:
        AirHumidityCheckState air_humidity_check_state;
        GeneralStateMock irrigate_air_state_mock;
        GeneralStateMock air_periodic_check_state_mock;

        CoreStateInterface air_humidity_check_state_interface;
        CoreStateInterface irrigate_air_state_mock_interface;
        CoreStateInterface air_periodic_check_state_mock_interface;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            air_humidity_check_state = AirHumidityCheckState_Construct(
                stub_get_air_humidity_50_threshold_60,
                &irrigate_air_state_mock_interface,
                &air_periodic_check_state_mock_interface
            );
            irrigate_air_state_mock = GeneralStateMock_Construct(CORE_STATE_IRRIGATE_AIR);
            air_periodic_check_state_mock = GeneralStateMock_Construct(CORE_STATE_AIR_PERIODIC_CHECK);
            
            air_humidity_check_state_interface = AirHumidityCheckState_GetCoreStateInterface(air_humidity_check_state);
            irrigate_air_state_mock_interface = GeneralStateMock_GetCoreStateInterface(irrigate_air_state_mock);
            air_periodic_check_state_mock_interface = GeneralStateMock_GetCoreStateInterface(air_periodic_check_state_mock);

            system_core = SystemCore_Construct(
                air_humidity_check_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&air_periodic_check_state_mock);
            GeneralStateMock_Destruct(&irrigate_air_state_mock);
            AirHumidityCheckState_Destruct(&air_humidity_check_state);
            SystemCore_Destruct(&system_core);
        }
};

class CoreInitialAirHumidityCheckWithRelativeHumidity70Threshold60 : public ::testing::Test
{
    private:
        AirHumidityCheckState air_humidity_check_state;
        GeneralStateMock irrigate_air_state_mock;
        GeneralStateMock air_periodic_check_state_mock;

        CoreStateInterface air_humidity_check_state_interface;
        CoreStateInterface irrigate_air_state_mock_interface;
        CoreStateInterface air_periodic_check_state_mock_interface;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            air_humidity_check_state = AirHumidityCheckState_Construct(
                stub_get_air_humidity_70_threshold_60,
                &irrigate_air_state_mock_interface,
                &air_periodic_check_state_mock_interface
            );
            irrigate_air_state_mock = GeneralStateMock_Construct(CORE_STATE_IRRIGATE_AIR);
            air_periodic_check_state_mock = GeneralStateMock_Construct(CORE_STATE_AIR_PERIODIC_CHECK);

            air_humidity_check_state_interface = AirHumidityCheckState_GetCoreStateInterface(air_humidity_check_state);
            irrigate_air_state_mock_interface = GeneralStateMock_GetCoreStateInterface(irrigate_air_state_mock);
            air_periodic_check_state_mock_interface = GeneralStateMock_GetCoreStateInterface(air_periodic_check_state_mock);

            system_core = SystemCore_Construct(
                air_humidity_check_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&air_periodic_check_state_mock);
            GeneralStateMock_Destruct(&irrigate_air_state_mock);
            AirHumidityCheckState_Destruct(&air_humidity_check_state);
            SystemCore_Destruct(&system_core);
        }
};

class CoreInitialAirHumidityCheckWithRelativeHumidity60Threshold60 : public ::testing::Test
{
    private:
        AirHumidityCheckState air_humidity_check_state;
        GeneralStateMock irrigate_air_state_mock;
        GeneralStateMock air_periodic_check_state_mock;

        CoreStateInterface air_humidity_check_state_interface;
        CoreStateInterface irrigate_air_state_mock_interface;
        CoreStateInterface air_periodic_check_state_mock_interface;

    protected:
        SystemCore system_core;
        
        void SetUp() override
        {
            air_humidity_check_state = AirHumidityCheckState_Construct(
                stub_get_air_humidity_60_threshold_60,
                &irrigate_air_state_mock_interface,
                &air_periodic_check_state_mock_interface
            );
            irrigate_air_state_mock = GeneralStateMock_Construct(CORE_STATE_IRRIGATE_AIR);
            air_periodic_check_state_mock = GeneralStateMock_Construct(CORE_STATE_AIR_PERIODIC_CHECK);

            air_humidity_check_state_interface = AirHumidityCheckState_GetCoreStateInterface(air_humidity_check_state);
            irrigate_air_state_mock_interface = GeneralStateMock_GetCoreStateInterface(irrigate_air_state_mock);
            air_periodic_check_state_mock_interface = GeneralStateMock_GetCoreStateInterface(air_periodic_check_state_mock);
            
            system_core = SystemCore_Construct(
                air_humidity_check_state_interface
            );
        }

        void TearDown() override
        {
            GeneralStateMock_Destruct(&air_periodic_check_state_mock);
            GeneralStateMock_Destruct(&irrigate_air_state_mock);
            AirHumidityCheckState_Destruct(&air_humidity_check_state);
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

TEST_F(CoreInitialIrrigateSoilWith10Seconds, ShouldIrrigateSoilFor10SecondsWhenAdvancingCycle)
{
    /* Given fixture */
    /* When */
    SystemCore_AdvanceCycle(system_core);

    /* Then */
    EXPECT_EQ(SoilIrrigatorMock_GetLastIrrigationTime(soil_irrigator_mock), 10);
}

TEST_F(CoreInitialIrrigateSoilWith10Seconds, ShouldBeAirHumidityCheckStateWhenIrrigateSoilStateAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    SystemCore_AdvanceCycle(system_core);

    /* Then */
    EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_AIR_HUMIDITY_CHECK);
}

TEST_F(CoreInitialAirHumidityCheckWithRelativeHumidity50Threshold60, ShouldBeIrrigateAirWhenAirHumidityCheckStateAndRelativeHumidityBelowThresholdAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    SystemCore_AdvanceCycle(system_core);

    /* Then */
    EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_IRRIGATE_AIR);
}

TEST_F(CoreInitialAirHumidityCheckWithRelativeHumidity70Threshold60, ShouldBeAirPeriodicCheckStateWhenAirHumidityCheckStateAndRelativeHumidityAboveThresholdAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    SystemCore_AdvanceCycle(system_core);

    /* Then */
    EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_AIR_PERIODIC_CHECK);
}

TEST_F(CoreInitialAirHumidityCheckWithRelativeHumidity60Threshold60, ShouldBeAirPeriodicCheckStateWhenAirHumidityCheckStateAndRelativeHumidityEqualThresholdAndAdvancingCycle)
{
    /* Given fixture */
    /* When */
    SystemCore_AdvanceCycle(system_core);

    /* Then */
    EXPECT_EQ(SystemCore_GetCurrentState(system_core), CORE_STATE_AIR_PERIODIC_CHECK);
}