/*
 * task_manager_wrapper.h
 *
 *  Created on: 30 oct. 2018
 *      Author: Vincent
 */

#ifndef TASK_MANAGER_WRAPPER_H_
#define TASK_MANAGER_WRAPPER_H_

#include "task_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

void sysview_task_block(uint32_t);
void sysview_task_transfer(uint32_t);
void sysview_task_void_enter(uint32_t);
void sysview_task_void_exit(void);
void sysview_task_idle(void);

#ifdef __cplusplus
}
#endif


/**@brief Returns ID of currently running task.
 *
 * @return ID of active task.
 */
inline task_id_t sysview_id_get(void) {
	return (task_id_get() + TASK_BASE_NRF);
}

/**@brief Yield CPU to other tasks.
 */
inline void yield(void) {
	if (task_id_get() == TASK_ID_INVALID) return;

	task_yield();
	sysview_task_transfer(sysview_id_get());

}

/**@brief Wait for events. Set events are cleared after this function returns.
 *
 * @param[in] evt_mask Mask of events to wait
 *
 * @return Mask with set events (can be a subset of evt_mask).
 */
inline uint32_t events_wait(uint32_t evt_mask) {
	if (task_id_get() == TASK_ID_INVALID) return 0;

	sysview_task_block(evt_mask);
	uint32_t mask = task_events_wait(evt_mask);
	sysview_task_transfer(sysview_id_get());

	return mask;
}

/**@brief Set events for given task.
 *
 * @param[in]  task_id  Id of the task which shall receive events.
 * @param[in]  evt_mask Events for the task.
 *
 */
inline void events_set(task_id_t task_id, uint32_t evt_mask) {
	if (task_id == TASK_ID_INVALID) return;

	task_events_set(task_id, evt_mask);
}


#endif /* TASK_MANAGER_WRAPPER_H_ */
