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
 * @defgroup RM_ZMOD4XXX_API ZMOD4XXX Middleware Interface
 * @brief Interface for ZMOD4XXX Middleware functions.
 *
 * @section RM_ZMOD4XXX_API_Summary Summary
 * The ZMOD4XXX interface provides ZMOD4XXX functionality.
 *
 * The ZMOD4XXX interface can be implemented by:
 * - @ref RM_ZMOD4XXX
 *
 * @{
 **********************************************************************************************************************/

/* Guards against multiple inclusion */
#ifndef RM_ZMOD4XXX_API_H_
#define RM_ZMOD4XXX_API_H_

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "platform.h"
 #include "r_comms_i2c_if.h"
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
 #include "r_cg_macrodriver.h"
 #include <stddef.h>
#else
 #include "bsp_api.h"
 #include "r_timer_api.h"
 #include "r_external_irq_api.h"
#endif

#include "rm_comms_api.h"

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/** Event in the callback function */
typedef enum e_rm_zmod4xxx_event
{
    RM_ZMOD4XXX_EVENT_SUCCESS = 0,
    RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE,
    RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE,
    RM_ZMOD4XXX_EVENT_ERROR,
} rm_zmod4xxx_event_t;

/** ZMOD4XXX sensor API callback parameter definition */
typedef struct st_rm_zmod4xxx_callback_args
{
    void const        * p_context;
    rm_zmod4xxx_event_t event;
} rm_zmod4xxx_callback_args_t;

/** ZMOD4XXX raw data structure */
typedef struct st_rm_zmod4xxx_raw_data
{
    uint8_t adc_data[32];
} rm_zmod4xxx_raw_data_t;

/** Sulfur-Odor status */
typedef enum e_rm_zmod4xxx_sulfur_odor
{
    RM_ZMOD4XXX_SULFUR_ODOR_ACCEPTABLE = 0,
    RM_ZMOD4XXX_SULFUR_ODOR_UNACCEPTABLE,
} rm_zmod4xxx_sulfur_odor_t;

/** ZMOD4XXX IAQ 1st gen data structure */
typedef struct st_rm_zmod4xxx_iaq_1st_data
{
    float rmox;                        ///< MOx resistance.
    float rcda;                        ///< CDA resistance.
    float iaq;                         ///< IAQ index.
    float tvoc;                        ///< TVOC concentration (mg/m^3).
    float etoh;                        ///< EtOH concentration (ppm).
    float eco2;                        ///< eCO2 concentration (ppm).
} rm_zmod4xxx_iaq_1st_data_t;

/** ZMOD4XXX IAQ 2nd gen data structure */
typedef struct st_rm_zmod4xxx_iaq_2nd_data
{
    float rmox[13];                    ///< MOx resistance.
    float log_rcda;                    ///< log10 of CDA resistance.
    float iaq;                         ///< IAQ index.
    float tvoc;                        ///< TVOC concentration (mg/m^3).
    float etoh;                        ///< EtOH concentration (ppm).
    float eco2;                        ///< eCO2 concentration (ppm).
} rm_zmod4xxx_iaq_2nd_data_t;

/** ZMOD4XXX Odor structure */
typedef struct st_rm_zmod4xxx_odor_data
{
    bool  control_signal;              ///< Control signal input for odor lib.
    float odor;                        ///< Concentration ratio for odor lib.
} rm_zmod4xxx_odor_data_t;

/** ZMOD4XXX Sulfur-Odor structure */
typedef struct st_rm_zmod4xxx_sulfur_odor_data
{
    float rmox[9];                     ///< MOx resistance.
    float intensity;                   ///< odor intensity rating ranges from 0.0 to 5.0 for sulfur lib
    rm_zmod4xxx_sulfur_odor_t odor;    ///< sulfur_odor classification for lib
} rm_zmod4xxx_sulfur_odor_data_t;

/** ZMOD4XXX OAQ 1st gen data structure */
typedef struct st_rm_zmod4xxx_oaq_1st_data
{
    float rmox[15];                    ///< MOx resistance
    float aiq;                         ///< Air Quality
} rm_zmod4xxx_oaq_1st_data_t;

/** ZMOD4XXX OAQ 2nd gen data structure */
typedef struct st_rm_zmod4xxx_oaq_2nd_data
{
    float    rmox[8];                  ///< MOx resistance.
    float    ozone_concentration;      ///< The ozone concentration in part-per-billion
    uint16_t fast_aqi;                 ///< 1-minute average of the Air Quality Index according to the EPA standard based on ozone
    uint16_t epa_aqi;                  ///< The Air Quality Index according to the EPA standard based on ozone
} rm_zmod4xxx_oaq_2nd_data_t;

/** ZMOD4XXX configuration block */
typedef struct st_rm_zmod4xxx_cfg
{
    rm_comms_instance_t const * p_comms_instance;                    ///< Pointer to Communications Middleware instance.
    void const                * p_timer_instance;                    ///< Pointer to Timer driver instance.
    void const                * p_irq_instance;                      ///< Pointer to IRQ instance.
    void const                * p_zmod4xxx_device;                   ///< Pointer to ZMOD4XXX device structure.
    void const                * p_zmod4xxx_handle;                   ///< Pointer to ZMOD4XXX library handler.
    void const                * p_zmod4xxx_results;                  ///< Pointer to ZMOD4XXX library results.
    void const                * p_context;                           ///< Pointer to the user-provided context.
    void const                * p_extend;                            ///< Pointer to extended configuration by instance of interface.
    void (* p_comms_callback)(rm_zmod4xxx_callback_args_t * p_args); ///< I2C Communications callback
    void (* p_irq_callback)(rm_zmod4xxx_callback_args_t * p_args);   ///< IRQ callback
} rm_zmod4xxx_cfg_t;

/** ZMOD4xxx Control block. Allocate an instance specific control block to pass into the API calls.
 * @par Implemented as
 * - rm_zmod4xxx_instance_ctrl_t
 */
typedef void rm_zmod4xxx_ctrl_t;

/** ZMOD4XXX APIs */
typedef struct st_rm_zmod4xxx_api
{
    /** Open sensor.
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_Open()
     *
     * @param[in]  p_api_ctrl   Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_cfg_t const * const p_cfg);

    /** Start measurement
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_MeasurementStart()
     *
     * @param[in]  p_api_ctrl             Pointer to control structure.
     */
    fsp_err_t (* measurementStart)(rm_zmod4xxx_ctrl_t * const p_api_ctrl);

    /** Stop measurement
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_MeasurementStop()
     *
     * @param[in]  p_api_ctrl             Pointer to control structure.
     */
    fsp_err_t (* measurementStop)(rm_zmod4xxx_ctrl_t * const p_api_ctrl);

    /** Read status of the sensor
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_StatusCheck()
     *
     * @param[in]  p_api_ctrl             Pointer to control structure.
     */
    fsp_err_t (* statusCheck)(rm_zmod4xxx_ctrl_t * const p_api_ctrl);

    /** Read ADC data.
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_Read()
     *
     * @param[in]  p_api_ctrl             Pointer to control structure.
     * @param[in]  p_raw_data             Pointer to raw data structure.
     */
    fsp_err_t (* read)(rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_raw_data_t * const p_raw_data);

    /** Calculate IAQ 1st Gen. values from ADC data.
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_Iaq1stGenDataCalculate()
     *
     * @param[in]  p_api_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data           Pointer to raw data.
     * @param[in]  p_zmod4xxx_data      Pointer to ZMOD4XXXX data structure.
     */
    fsp_err_t (* iaq1stGenDataCalculate)(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                         rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                         rm_zmod4xxx_iaq_1st_data_t * const p_zmod4xxx_data);

    /** Calculate IAQ 2nd Gen. values from ADC data.
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_Iaq2ndGenDataCalculate()
     *
     * @param[in]  p_api_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data           Pointer to raw data.
     * @param[in]  p_zmod4xxx_data      Pointer to ZMOD4XXXX data structure.
     */
    fsp_err_t (* iaq2ndGenDataCalculate)(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                         rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                         rm_zmod4xxx_iaq_2nd_data_t * const p_zmod4xxx_data);

    /** Calculate Odor values from ADC data.
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_OdorDataCalculate()
     *
     * @param[in]  p_api_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data           Pointer to raw data.
     * @param[in]  p_zmod4xxx_data      Pointer to ZMOD4XXXX data structure.
     */
    fsp_err_t (* odorDataCalculate)(rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_raw_data_t * const p_raw_data,
                                    rm_zmod4xxx_odor_data_t * const p_zmod4xxx_data);

    /** Calculate Sulfur Odor values from ADC data.
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_SulfurOdorDataCalculate()
     *
     * @param[in]  p_api_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data           Pointer to raw data.
     * @param[in]  p_zmod4xxx_data      Pointer to ZMOD4XXXX data structure.
     */
    fsp_err_t (* sulfurOdorDataCalculate)(rm_zmod4xxx_ctrl_t * const             p_api_ctrl,
                                          rm_zmod4xxx_raw_data_t * const         p_raw_data,
                                          rm_zmod4xxx_sulfur_odor_data_t * const p_zmod4xxx_data);

    /** Calculate OAQ 1st Gen. values from ADC data.
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_Oaq1stGenDataCalculate()
     *
     * @param[in]  p_api_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data           Pointer to raw data.
     * @param[in]  p_zmod4xxx_data      Pointer to ZMOD4XXXX data structure.
     */
    fsp_err_t (* oaq1stGenDataCalculate)(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                         rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                         rm_zmod4xxx_oaq_1st_data_t * const p_zmod4xxx_data);

    /** Calculate OAQ 2nd Gen. values from ADC data.
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_Oaq2ndGenDataCalculate()
     *
     * @param[in]  p_api_ctrl           Pointer to control structure.
     * @param[in]  p_raw_data           Pointer to raw data.
     * @param[in]  p_zmod4xxx_data      Pointer to ZMOD4XXXX data structure.
     */
    fsp_err_t (* oaq2ndGenDataCalculate)(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                         rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                         rm_zmod4xxx_oaq_2nd_data_t * const p_zmod4xxx_data);

    /** Set temperature and humidity.
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_TemperatureAndHumiditySet()
     *
     * @param[in]  p_api_ctrl             Pointer to control structure.
     * @param[in]  temperature            Temperature (deg C).
     * @param[in]  humidity               Humidity (percent).
     */
    fsp_err_t (* temperatureAndHumiditySet)(rm_zmod4xxx_ctrl_t * const p_api_ctrl, float temperature, float humidity);

    /** Close the sensor
     * @par Implemented as
     * - @ref RM_ZMOD4XXX_Close()
     *
     * @param[in]  p_api_ctrl           Pointer to control structure.
     */
    fsp_err_t (* close)(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
} rm_zmod4xxx_api_t;

/** ZMOD4XXX instance */
typedef struct st_rm_zmod4xxx_instance
{
    rm_zmod4xxx_ctrl_t      * p_ctrl;  /**< Pointer to the control structure for this instance */
    rm_zmod4xxx_cfg_t const * p_cfg;   /**< Pointer to the configuration structure for this instance */
    rm_zmod4xxx_api_t const * p_api;   /**< Pointer to the API structure for this instance */
} rm_zmod4xxx_instance_t;

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_ZMOD4XXX_API_H_*/

/******************************************************************************************************************//**
 * @} (end addtogroup RM_ZMOD4XXX_API)
 *********************************************************************************************************************/
