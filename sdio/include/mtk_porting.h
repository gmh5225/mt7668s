/******************************************************************************
 *
 * GPLv2 License
 *
 * Copyright(C) 2016 MediaTek Inc.
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

/* porting layer */
/* Android */

#ifndef _MTK_PORTING_H_
#define _MTK_PORTING_H_

#include <linux/kernel.h> /* include stddef.h for NULL */

/* typedef void VOID, *PVOID; */

typedef int MTK_WCN_BOOL;
#ifndef MTK_WCN_BOOL_TRUE
#define MTK_WCN_BOOL_FALSE ((MTK_WCN_BOOL)0)
#define MTK_WCN_BOOL_TRUE ((MTK_WCN_BOOL)1)
#endif

typedef int MTK_WCN_MUTEX;

typedef int MTK_WCN_TIMER;

/* system APIs */
/* mutex */
typedef MTK_WCN_MUTEX (*MUTEX_CREATE)(const char *const name);
typedef INT_32 (*MUTEX_DESTROY)(MTK_WCN_MUTEX mtx);
typedef INT_32 (*MUTEX_LOCK)(MTK_WCN_MUTEX mtx);
typedef INT_32 (*MUTEX_UNLOCK)(MTK_WCN_MUTEX mtx, unsigned long flags);
/* debug */
typedef INT_32 (*DBG_PRINT)(const char *str, ...);
typedef INT_32 (*DBG_ASSERT)(INT_32 expr, const char *file, INT_32 line);
/* timer */
typedef void (*MTK_WCN_TIMER_CB)(void);
typedef MTK_WCN_TIMER (*TIMER_CREATE)(const char *const name);
typedef INT_32 (*TIMER_DESTROY)(MTK_WCN_TIMER tmr);
typedef INT_32 (*TIMER_START)(MTK_WCN_TIMER tmr, UINT_32 timeout, MTK_WCN_TIMER_CB tmr_cb, void *param);
typedef INT_32 (*TIMER_STOP)(MTK_WCN_TIMER tmr);
/* kernel lib */
typedef void *(*SYS_MEMCPY)(void *dest, const void *src, UINT_32 n);
typedef void *(*SYS_MEMSET)(void *s, INT_32 c, UINT_32 n);
typedef INT_32 (*SYS_SPRINTF)(char *str, const char *format, ...);

#endif /* _MTK_PORTING_H_ */
