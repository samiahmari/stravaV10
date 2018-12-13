/*
 * segger_wrapper.c
 *
 *  Created on: 5 oct. 2017
 *      Author: Vincent
 */


#include "segger_wrapper.h"
#include "app_util_platform.h"
#include "app_error.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if USE_SVIEW

#define W_SYSVIEW_OnIdle(...)            SEGGER_SYSVIEW_OnIdle()

#define W_SYSVIEW_OnTaskStartExec(X)     SEGGER_SYSVIEW_OnTaskStartExec(X)
#define W_SYSVIEW_OnTaskStopExec(X)      SEGGER_SYSVIEW_OnTaskStopExec()
#define W_SYSVIEW_OnTaskStartReady(X)    SEGGER_SYSVIEW_OnTaskStartReady(X)
#define W_SYSVIEW_OnTaskStopReady(X, M)  SEGGER_SYSVIEW_OnTaskStopReady(X, M)

#define W_SYSVIEW_RecordVoid(X)          SEGGER_SYSVIEW_RecordVoid(X)
#define W_SYSVIEW_RecordEndCall(X)       SEGGER_SYSVIEW_RecordEndCall(X)

#else

#define W_SYSVIEW_OnIdle(...)            EMPTY_MACRO
#define W_SYSVIEW_OnTaskStartExec(X)     EMPTY_MACRO
#define W_SYSVIEW_OnTaskStopExec(X)      EMPTY_MACRO
#define W_SYSVIEW_OnTaskCreate(X)        EMPTY_MACRO
#define W_SYSVIEW_OnTaskStartReady(X)    EMPTY_MACRO
#define W_SYSVIEW_OnTaskStopReady(X, M)  EMPTY_MACRO

#endif


#if USE_SVIEW
#include "SEGGER_SYSVIEW.h"
static SEGGER_SYSVIEW_TASKINFO pInfo[SYSVIEW_MAX_NOF_TASKS];
static uint32_t nb_tasks;

SEGGER_SYSVIEW_OS_API os_api;
#endif


static uint32_t m_cur_task_id;
static uint32_t m_cur_void_id;

/*******************************************************************************
 * Functions
 ******************************************************************************/
void cbSendTaskList(void) {

#if USE_SVIEW

	for (int i = 0; i < nb_tasks; i++) {

		SEGGER_SYSVIEW_SendTaskInfo(&pInfo[i]);

	}

#endif

}

void sysview_task_block(uint32_t evt_mask) {
	W_SYSVIEW_OnTaskStopReady(sysview_id_get(), evt_mask);
	W_SYSVIEW_OnTaskStopExec(sysview_id_get());
}

void sysview_task_transfer(uint32_t task_id) {
	W_SYSVIEW_OnTaskStartExec(task_id);
	m_cur_task_id = task_id;
}

void sysview_task_void_enter(uint32_t void_id) {
	// TODO
	m_cur_void_id = void_id;
	W_SYSVIEW_RecordVoid(m_cur_void_id);
}

void sysview_task_void_exit(void) {
	// TODO
	W_SYSVIEW_RecordEndCall(m_cur_void_id);
	m_cur_void_id = 0;
}

void sysview_task_idle(void) {
	if (m_cur_task_id != 0) {
		m_cur_task_id = 0;
		W_SYSVIEW_OnIdle();
	}
}

void segger_init(void) {

//#if USE_RTT && !USE_SVIEW
//	  // RTT
//	  SEGGER_RTT_Init();
//#endif

#if USE_SVIEW

#warning "SysView is active"

	  // SYSVIEW
	  os_api.pfSendTaskList = cbSendTaskList;
//	  os_api.pfGetTime = (U64)millis();
	  os_api.pfGetTime = 0;

	  nb_tasks = 0;

	  pInfo[nb_tasks].TaskID = BOUCLE_TASK;
	  pInfo[nb_tasks++].sName  = "BOUCLE_TASK";

	  pInfo[nb_tasks].TaskID = SYSTEM_TASK;
	  pInfo[nb_tasks++].sName  = "SYSTEM_TASK";

	  pInfo[nb_tasks].TaskID = PERIPH_TASK;
	  pInfo[nb_tasks++].sName  = "PERIPH_TASK";

	  pInfo[nb_tasks].TaskID = LCD_TASK;
	  pInfo[nb_tasks++].sName  = "LCD_TASK";

	  pInfo[nb_tasks].TaskID = I2C_TASK;
	  pInfo[nb_tasks++].sName  = "I2C_TASK";

	  pInfo[nb_tasks].TaskID = SPI_TASK;
	  pInfo[nb_tasks++].sName  = "SPI_TASK";

	  pInfo[nb_tasks].TaskID = UART_TASK;
	  pInfo[nb_tasks++].sName  = "UART_TASK";

	  pInfo[nb_tasks].TaskID = BLE_TASK;
	  pInfo[nb_tasks++].sName  = "BLE_TASK";

	  pInfo[nb_tasks].TaskID = SD_ACCESS_TASK;
	  pInfo[nb_tasks++].sName  = "SD_ACCESS_TASK";

	  pInfo[nb_tasks].TaskID = SEG_PERF_TASK;
	  pInfo[nb_tasks++].sName  = "SEG_PERF_TASK";

	  pInfo[nb_tasks].TaskID = NRF52_TASK;
	  pInfo[nb_tasks++].sName  = "NRF52_TASK";

	  pInfo[nb_tasks].TaskID = DISPLAY_TASK3;
	  pInfo[nb_tasks++].sName  = "DISPLAY_TASK3";

	  pInfo[nb_tasks].TaskID = DISPLAY_TASK4;
	  pInfo[nb_tasks++].sName  = "DISPLAY_TASK4";

	  pInfo[nb_tasks].TaskID = USB_VCOM_TASK;
	  pInfo[nb_tasks++].sName  = "USB_VCOM_TASK";

	  pInfo[nb_tasks].TaskID = SST_TASK;
	  pInfo[nb_tasks++].sName  = "SST_TASK";

	  pInfo[nb_tasks].TaskID = EMPTY1;
	  pInfo[nb_tasks++].sName  = "EMPTY1";

	  pInfo[nb_tasks].TaskID = EMPTY2;
	  pInfo[nb_tasks++].sName  = "EMPTY2";

	  SEGGER_SYSVIEW_Conf();

	  SEGGER_SYSVIEW_Start();

	  for (int i = 0; i < nb_tasks; i++) {

		  SEGGER_SYSVIEW_OnTaskCreate(pInfo[i].TaskID);

	  }

#endif

}

/* System clock frequency. */
//extern uint32_t SystemCoreClock;
//void segger_update_clocks() {
//#if USE_SVIEW
//	SEGGER_SYSVIEW_UpdateClocks(SystemCoreClock, SystemCoreClock);
//#endif
//}
//
//void segger_send(UART_Type* base, const uint8_t* buffer, size_t length) {
//#if USE_RTT
//
//	SEGGER_RTT_Write(RTT_LOG_CHANNEL, buffer, (unsigned) length);
//
//#endif
//}
//
//status_t segger_recv(UART_Type* base, uint8_t* buffer, size_t length) {
//#if USE_RTT
//
//	unsigned read_bytes = 0;
//
//	read_bytes = SEGGER_RTT_Read(RTT_LOG_CHANNEL, buffer + read_bytes, length);
//
//	if (!read_bytes) return 1;
//
//#endif
//
//	return 0;
//}
