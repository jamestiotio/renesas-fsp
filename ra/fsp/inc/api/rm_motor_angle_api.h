/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup MOTOR_ANGLE_API Motor angle Interface
 * @brief Interface for motor angle and speed calculation functions.
 *
 * @section MOTOR_ANGLE_API_Summary Summary
 * The Motor angle interface calculates the rotor angle and rotational speed from other data.
 *
 * The motor angle interface can be implemented by:
 * - @ref MOTOR_ESTIMATE
 * - @ref MOTOR_SENSE_ENCODER
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_ANGLE_API_H
#define RM_MOTOR_ANGLE_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Motor Angle Control block.  Allocate an instance specific control block to pass into the API calls.
 * @par Implemented as
 * - motor_angle_ctrl_t
 */
typedef void motor_angle_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_angle_cfg
{
    void const * p_context;
    void const * p_extend;
} motor_angle_cfg_t;

/** Interface structure **/
typedef struct st_motor_angle_current
{
    float id;                          ///< d-axis current
    float iq;                          ///< q-axis current
} motor_angle_current_t;

typedef struct st_motor_angle_voltage_reference
{
    float vd;                          ///< d-axis voltage reference
    float vq;                          ///< q-axis voltage reference
} motor_angle_voltage_reference_t;

/* encoder angle adjustment status */
typedef enum e_motor_sense_encoder_angle_adjust
{
    MOTOR_SENSE_ENCODER_ANGLE_ADJUST_90_DEGREE = 1, ///< Roter Angle Adjustment to pull in 90degree
    MOTOR_SENSE_ENCODER_ANGLE_ADJUST_0_DEGREE,      ///< Roter Angle Adjustment to pull in 0degree
    MOTOR_SENSE_ENCODER_ANGLE_ADJUST_FINISH,        ///< Roter Angle Adjustment Finish
} motor_sense_encoder_angle_adjust_t;

typedef struct st_motor_angle_encoder_info
{
    motor_sense_encoder_angle_adjust_t e_adjust_status; ///< Encoder Adjustment Status
    uint8_t u1_adjust_count_full;                       ///< Adjustment count became full
} motor_angle_encoder_info_t;

/** Functions implemented as application interface will follow these APIs. */
typedef struct st_motor_angle_api
{
    /** Initialize the Motor_Angle.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_Open()
     * - @ref RM_MOTOR_SENSE_ENCODER_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * const p_cfg);

    /** Close (Finish) the Motor_Angle.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_Close()
     * - @ref RM_MOTOR_SENSE_ENCODER_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_angle_ctrl_t * const p_ctrl);

    /** Reset the Motor_Angle.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_Reset()
     * - @ref RM_MOTOR_SENSE_ENCODER_Reset()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_angle_ctrl_t * const p_ctrl);

    /** Set (Input) Current & Voltage Reference data into the Motor_Angle.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_CurrentSet()
     * - @ref RM_MOTOR_SENSE_ENCODER_CurrentSet()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  p_st_current   Pointer to current structure
     * @param[in]  p_st_voltage   Pointer to voltage Reference structure
     */
    fsp_err_t (* currentSet)(motor_angle_ctrl_t * const p_ctrl, motor_angle_current_t * const p_st_current,
                             motor_angle_voltage_reference_t * const p_st_voltage);

    /** Set (Input) Speed Information into the Motor_Angle.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_SpeedSet()
     * - @ref RM_MOTOR_SENSE_ENCODER_SpeedSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  speed_ctrl   Control reference of rotational speed [rad/s]
     * @param[in]  damp_speed   Damping rotational speed [rad/s]
     */
    fsp_err_t (* speedSet)(motor_angle_ctrl_t * const p_ctrl, float const speed_ctrl, float const damp_speed);

    /** Set the flag of PI Control runs.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_FlagPiCtrlSet()
     * - @ref RM_MOTOR_SENSE_ENCODER_FlagPiCtrlSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  flag_pi      The flag of PI control runs
     */
    fsp_err_t (* flagPiCtrlSet)(motor_angle_ctrl_t * const p_ctrl, uint32_t const flag_pi);

    /** Calculate internal parameters of encoder process.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_InternalCalculate()
     * - @ref RM_MOTOR_SENSE_ENCODER_InternalCalculate()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* internalCalculate)(motor_angle_ctrl_t * const p_ctrl);

    /** Get rotor angle and rotational speed from the Motor_Angle.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_AngleSpeedGet()
     * - @ref RM_MOTOR_SENSE_ENCODER_AngleSpeedGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_angl       Memory address to get rotor angle data
     * @param[out] p_speed      Memory address to get rotational speed data
     * @param[out] p_phase_err  Memory address to get phase(angle) error data
     */
    fsp_err_t (* angleSpeedGet)(motor_angle_ctrl_t * const p_ctrl, float * const p_angle, float * const p_speed,
                                float * const p_phase_err);

    /** Angle Adjustment Process.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_AngleAdjust()
     * - @ref RM_MOTOR_SENSE_ENCODER_AngleAdjust()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* angleAdjust)(motor_angle_ctrl_t * const p_ctrl);

    /** Encoder Cyclic Process.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_EncoderCyclic()
     * - @ref RM_MOTOR_SENSE_ENCODER_EncoderCyclic()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* encoderCyclic)(motor_angle_ctrl_t * const p_ctrl);

    /** Get estimated d/q-axis component from the Motor_Angle.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_EstimatedComponentGet()
     * - @ref RM_MOTOR_SENSE_ENCODER_EstimatedComponentGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_ed         Memory address to get estimated d-axis component
     * @param[out] p_eq         Memory address to get estimated q-axis component
     */
    fsp_err_t (* estimatedComponentGet)(motor_angle_ctrl_t * const p_ctrl, float * const p_ed, float * const p_eq);

    /** Get Encoder Calculate Information.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_InfoGet()
     * - @ref RM_MOTOR_SENSE_ENCODER_InfoGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_info       Memory address to get encoder calculate information
     */
    fsp_err_t (* infoGet)(motor_angle_ctrl_t * const p_ctrl, motor_angle_encoder_info_t * const p_info);

    /** Update Parameters for the calculation in the Motor_Angle.
     * @par Implemented as
     * - @ref RM_MOTOR_ESTIMATE_ParameterUpdate()
     * - @ref RM_MOTOR_SENSE_ENCODER_ParameterUpdate()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure include update parameters.
     */
    fsp_err_t (* parameterUpdate)(motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * p_cfg);
} motor_angle_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_motor_angle_instance
{
    motor_angle_ctrl_t      * p_ctrl;  ///< Pointer to the control structure for this instance
    motor_angle_cfg_t const * p_cfg;   ///< Pointer to the configuration structure for this instance
    motor_angle_api_t const * p_api;   ///< Pointer to the API structure for this instance
} motor_angle_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_ANGLE_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_ANGLE_API_H */
