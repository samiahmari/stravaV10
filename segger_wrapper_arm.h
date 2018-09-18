/*
 * segger_wrapper.h
 *
 *  Created on: 5 oct. 2017
 *      Author: Vincent
 */

#ifndef LIBRARIES_UTILS_SEGGER_WRAPPER_H_
#define LIBRARIES_UTILS_SEGGER_WRAPPER_H_


#include "nrf_log.h"
#include <stddef.h>


/////////    PARAMETERS

#ifndef USE_VCOM_LOGS
#define USE_VCOM_LOGS     0
#endif

#ifndef USE_SVIEW
#define USE_SVIEW         0
#endif


#ifndef NRF_LOG_BACKEND_RTT_ENABLED
#define NRF_LOG_BACKEND_RTT_ENABLED 1
#endif

#if USE_SVIEW
#include "SEGGER_SYSVIEW.h"
#endif

/////////    DEFINES

#define RTT_LOG_CHANNEL   0


#if USE_SVIEW
#define LOG_INFO(...)                  EMPTY_MACRO
#define LOG_RAW_INFO(X)                EMPTY_MACRO
#define LOG_DEBUG(...)                 EMPTY_MACRO
//#define LOG_ERROR(...)                 SEGGER_SYSVIEW_ErrorfHost(__VA_ARGS__)
#define LOG_ERROR(...)                 SEGGER_SYSVIEW_PrintfHost(__VA_ARGS__)
#define LOG_FLUSH(...)                 EMPTY_MACRO
#define LOG_SET_TERM(X)                EMPTY_MACRO
#define SVIEW_INIT(...)                segger_init()
#elif USE_VCOM_LOGS
#include "usb_cdc.h"
#define LOG_INFO(...)                  usb_printf(__VA_ARGS__)
#define LOG_RAW_INFO(X)                usb_print(X)
#define LOG_WARNING(...)               usb_printf(__VA_ARGS__)
#define LOG_DEBUG(...)                 EMPTY_MACRO
#define LOG_ERROR(...)                 usb_printf(__VA_ARGS__)
#define LOG_GRAPH(...)                 EMPTY_MACRO
#define LOG_FLUSH(...)                 usb_flush();
#define LOG_SET_TERM(X)                EMPTY_MACRO
#define USB_PRINTF(...)                usb_printf(__VA_ARGS__)
#define USB_PRINT(X)                   usb_print(X)
#define SVIEW_INIT(...)                EMPTY_MACRO
//#undef NRF_LOG_BACKEND_RTT_ENABLED
//#define NRF_LOG_BACKEND_RTT_ENABLED 0
#elif NRF_LOG_BACKEND_RTT_ENABLED
#define LOG_INFO(...)                  NRF_LOG_INFO(__VA_ARGS__)
#define LOG_RAW_INFO(X)                NRF_LOG_RAW_INFO("%c", X)
#define LOG_WARNING(...)               NRF_LOG_WARNING(__VA_ARGS__)
#define LOG_DEBUG(...)                 EMPTY_MACRO
#define LOG_ERROR(...)                 NRF_LOG_ERROR(__VA_ARGS__)
#define LOG_GRAPH(...)                 EMPTY_MACRO
#define LOG_FLUSH(...)                 NRF_LOG_FLUSH();
#define LOG_SET_TERM(X)                EMPTY_MACRO
#define SVIEW_INIT(...)                EMPTY_MACRO
#define USB_PRINTF(...)                EMPTY_MACRO
#define USB_PRINT(...)                 EMPTY_MACRO
#else
#define LOG_INFO(...)                  EMPTY_MACRO
#define LOG_RAW_INFO(X)                EMPTY_MACRO
#define LOG_WARNING(...)               EMPTY_MACRO
#define LOG_DEBUG(...)                 EMPTY_MACRO
#define LOG_ERROR(...)                 EMPTY_MACRO
#define LOG_GRAPH(...)                 EMPTY_MACRO
#define LOG_FLUSH(...)                 EMPTY_MACRO
#define LOG_SET_TERM(X)                EMPTY_MACRO
#define SVIEW_INIT(...)                EMPTY_MACRO
#endif


#if USE_SVIEW
#define W_SYSVIEW_RecordEnterISR(...)  SEGGER_SYSVIEW_RecordEnterISR()
#define W_SYSVIEW_RecordExitISR(...)   SEGGER_SYSVIEW_RecordExitISR()
//#define W_SYSVIEW_RecordEnterISR(...)  EMPTY_MACRO
//#define W_SYSVIEW_RecordExitISR(...)   EMPTY_MACRO
#define W_SYSVIEW_OnIdle(...)          SEGGER_SYSVIEW_OnIdle()
#define W_SYSVIEW_OnTaskStartExec(X)   SEGGER_SYSVIEW_OnTaskStartExec(X)
#define W_SYSVIEW_OnTaskStopExec(X)    SEGGER_SYSVIEW_OnTaskTerminate(X);SEGGER_SYSVIEW_OnIdle()
#define W_SYSVIEW_OnTaskCreate(X)      SEGGER_SYSVIEW_OnTaskCreate(X)
#else
#define W_SYSVIEW_RecordEnterISR(...)  EMPTY_MACRO
#define W_SYSVIEW_RecordExitISR(...)   EMPTY_MACRO
#define W_SYSVIEW_OnIdle(...)          EMPTY_MACRO
#define W_SYSVIEW_OnTaskStartExec(X)   EMPTY_MACRO
#define W_SYSVIEW_OnTaskStopExec(X)    EMPTY_MACRO
#define W_SYSVIEW_OnTaskCreate(X)      EMPTY_MACRO
#endif

#define SYSVIEW_MAX_NOF_TASKS          30

#define TASK_BASE                      (36u)

#define I2C_TASK                       (TASK_BASE + 0u)
#define SPI_TASK                       (TASK_BASE + 1u)
#define UART_TASK                      (TASK_BASE + 2u)

#define ANT_TASK                       (TASK_BASE + 6u)
#define BLE_TASK                       (TASK_BASE + 7u)
#define SD_ACCESS_TASK                 (TASK_BASE + 8u)
#define SEG_PERF_TASK                  (TASK_BASE + 9u)
#define NRF52_TASK                     (TASK_BASE + 10u)
#define LCD_TASK                       (TASK_BASE + 11u)
#define DISPLAY_TASK3                  (TASK_BASE + 12u)
#define DISPLAY_TASK4                  (TASK_BASE + 13u)
#define USB_VCOM_TASK                  (TASK_BASE + 14u)
#define EMPTY1                         (TASK_BASE + 15u)
#define EMPTY2                         (TASK_BASE + 16u)


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

/////////    FUNCTIONS

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */


void segger_init(void);


#if defined(__cplusplus)
}
#endif /* _cplusplus */

#endif /* LIBRARIES_UTILS_SEGGER_WRAPPER_H_ */