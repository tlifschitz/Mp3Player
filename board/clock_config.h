/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _CLOCK_CONFIG_H_
#define _CLOCK_CONFIG_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_XTAL0_CLK_HZ                         12000000U  /*!< Board xtal0 frequency in Hz */
#define BOARD_XTAL32K_CLK_HZ                          32768U  /*!< Board RTC xtal frequency in Hz */

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes default configuration of clocks.
 *
 */
void BOARD_InitBootClocks(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ********************* Configuration BOARD_ClockInternal ***********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_ClockInternal configuration
 ******************************************************************************/
#define BOARD_CLOCKINTERNAL_CORE_CLOCK             20971520U  /*!< Core clock frequency: 20971520Hz */

/*! @brief MCG set for BOARD_ClockInternal configuration.
 */
extern const mcg_config_t mcgConfig_BOARD_ClockInternal;
/*! @brief SIM module set for BOARD_ClockInternal configuration.
 */
extern const sim_clock_config_t simConfig_BOARD_ClockInternal;
/*! @brief OSC set for BOARD_ClockInternal configuration.
 */
extern const osc_config_t oscConfig_BOARD_ClockInternal;

/*******************************************************************************
 * API for BOARD_ClockInternal configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_ClockInternal(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ********************* Configuration BOARD_ClockExternal ***********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_ClockExternal configuration
 ******************************************************************************/
#define BOARD_CLOCKEXTERNAL_CORE_CLOCK            120000000U  /*!< Core clock frequency: 120000000Hz */

/*! @brief MCG set for BOARD_ClockExternal configuration.
 */
extern const mcg_config_t mcgConfig_BOARD_ClockExternal;
/*! @brief SIM module set for BOARD_ClockExternal configuration.
 */
extern const sim_clock_config_t simConfig_BOARD_ClockExternal;
/*! @brief OSC set for BOARD_ClockExternal configuration.
 */
extern const osc_config_t oscConfig_BOARD_ClockExternal;

/*******************************************************************************
 * API for BOARD_ClockExternal configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_ClockExternal(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 *********************** Configuration BOARD_ClockSleep ************************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_ClockSleep configuration
 ******************************************************************************/
#define BOARD_CLOCKSLEEP_CORE_CLOCK                 4000000U  /*!< Core clock frequency: 4000000Hz */

/*! @brief MCG set for BOARD_ClockSleep configuration.
 */
extern const mcg_config_t mcgConfig_BOARD_ClockSleep;
/*! @brief SIM module set for BOARD_ClockSleep configuration.
 */
extern const sim_clock_config_t simConfig_BOARD_ClockSleep;
/*! @brief OSC set for BOARD_ClockSleep configuration.
 */
extern const osc_config_t oscConfig_BOARD_ClockSleep;

/*******************************************************************************
 * API for BOARD_ClockSleep configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_ClockSleep(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* _CLOCK_CONFIG_H_ */
