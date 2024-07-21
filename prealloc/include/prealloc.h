/******************************************************************************
 *
 * GPLv2 License
 *
 * Copyright(C) 2017 MediaTek Inc.
 * Copyright(C) 2024 Yogi Hermawan <yogist.xda@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 *
 *****************************************************************************/

/*******************************************************************************
 *                         C O M P I L E R   F L A G S
 *******************************************************************************/

/*******************************************************************************
 *                    E X T E R N A L   R E F E R E N C E S
 *******************************************************************************/
#ifndef _PREALLOC_H
#define _PREALLOC_H

/*******************************************************************************
 *                              C O N S T A N T S
 *******************************************************************************/

/*******************************************************************************
 *                             D A T A   T Y P E S
 *******************************************************************************/
enum ENUM_MEM_ID {
	MEM_ID_NIC_ADAPTER,
	MEM_ID_IO_BUFFER,
#if 1
	MEM_ID_IO_CTRL,
	MEM_ID_RX_DATA,
#endif
#if 0
	MEM_ID_TX_CMD,
	MEM_ID_TX_DATA_FFA,
	MEM_ID_TX_DATA,
	MEM_ID_RX_EVENT,
	MEM_ID_RX_DATA,
#endif

	MEM_ID_NUM, /* END, Do not modify */
};

/*******************************************************************************
 *                            P U B L I C   D A T A
 *******************************************************************************/

/*******************************************************************************
 *                           P R I V A T E   D A T A
 *******************************************************************************/

/*******************************************************************************
 *                                 M A C R O S
 *******************************************************************************/
#define PreLog(level, ...) printk(level "[wlan][MemPrealloc] " __VA_ARGS__)
#define MP_Dbg(...) PreLog(KERN_DEBUG, __VA_ARGS__)
#define MP_Info(...) PreLog(KERN_INFO, __VA_ARGS__)
#define MP_Err(...) PreLog(KERN_ERR, __VA_ARGS__)

/*******************************************************************************
 *                   F U N C T I O N   D E C L A R A T I O N S
 *******************************************************************************/
PVOID preallocGetMem(enum ENUM_MEM_ID memId);

#endif /* _PREALLOC_H */
