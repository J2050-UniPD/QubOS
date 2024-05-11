/**
 **************************************************************************************** 
 * @file rx_comm_task.h
 * @brief Handle received payload.
 * @author J2050
 ****************************************************************************************
 * Task which job is waiting for a payload and handling it, 
 * sending the contained command to the appropriate handler task.
 */
#ifndef RX_COMM_TASK_H
void rx_comm_task();
#endif // !RX_COMM_TASK_H
