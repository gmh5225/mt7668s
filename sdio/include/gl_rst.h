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

#ifndef _GL_RST_H
#define _GL_RST_H

/*******************************************************************************
 *                         C O M P I L E R   F L A G S
 *******************************************************************************/

/*******************************************************************************
 *                    E X T E R N A L   R E F E R E N C E S
 *******************************************************************************/
#include "gl_typedef.h"
#include <linux/of_gpio.h>
#include <linux/mmc/host.h>
/*******************************************************************************
 *                              C O N S T A N T S
 *******************************************************************************/

/*******************************************************************************
 *                             D A T A   T Y P E S
 *******************************************************************************/

struct rst_struct {
#ifdef _HIF_SDIO
	struct sdio_func *func;
	struct work_struct rst_work;
#endif
	struct mutex rst_mutex;
	int entry_conut;
};

/*******************************************************************************
 *                    E X T E R N A L   F U N C T I O N S
 *******************************************************************************/

/*******************************************************************************
 *                            P U B L I C   D A T A
 *******************************************************************************/
extern struct rst_struct rst_data;

#ifdef _HIF_SDIO
extern const struct sdio_device_id mtk_sdio_ids[];
#endif
/*******************************************************************************
 *                           P R I V A T E   D A T A
 *******************************************************************************/

/*******************************************************************************
 *                                 M A C R O S
 *******************************************************************************/

/*******************************************************************************
 *                  F U N C T I O N   D E C L A R A T I O N S
 *******************************************************************************/
#ifdef _HIF_SDIO
extern int sdio_reset_comm(struct mmc_card *card);
#endif

/*******************************************************************************
 *                              F U N C T I O N S
 *******************************************************************************/

BOOLEAN kalIsResetting(VOID);

#if CFG_CHIP_RESET_SUPPORT

BOOLEAN checkResetState(void);
VOID glResetTrigger(P_ADAPTER_T prAdapter);
INT_32 notify_wlan_toggle_rst_end(INT_32 reserved);
#else
#define glResetTrigger(A)
#endif

#endif /* _GL_RST_H */
