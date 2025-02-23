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

/*******************************************************************************
 *                         C O M P I L E R   F L A G S
 *******************************************************************************/

/*******************************************************************************
 *                    E X T E R N A L   R E F E R E N C E S
 *******************************************************************************/
#include "precomp.h"

/*******************************************************************************
 *                              C O N S T A N T S
 *******************************************************************************/

/*******************************************************************************
 *                             D A T A   T Y P E S
 *******************************************************************************/

/*******************************************************************************
 *                            P U B L I C   D A T A
 *******************************************************************************/

/*******************************************************************************
 *                           P R I V A T E   D A T A
 *******************************************************************************/

/*******************************************************************************
 *                                 M A C R O S
 *******************************************************************************/

/*******************************************************************************
 *                   F U N C T I O N   D E C L A R A T I O N S
 *******************************************************************************/

/*******************************************************************************
 *                              F U N C T I O N S
 *******************************************************************************/
/*----------------------------------------------------------------------------*/
/*!
 * @brief This function is used to initial the MGMT memory pool for CMD Packet.
 *
 * @param prAdapter  Pointer to the Adapter structure.
 *
 * @return (none)
 */
/*----------------------------------------------------------------------------*/
VOID cmdBufInitialize(IN P_ADAPTER_T prAdapter)
{
	P_CMD_INFO_T prCmdInfo;
	UINT_32 i;

	ASSERT(prAdapter);

	QUEUE_INITIALIZE(&prAdapter->rFreeCmdList);

	for (i = 0; i < CFG_TX_MAX_CMD_PKT_NUM; i++) {
		prCmdInfo = &prAdapter->arHifCmdDesc[i];
		QUEUE_INSERT_TAIL(&prAdapter->rFreeCmdList, &prCmdInfo->rQueEntry);
	}

} /* end of cmdBufInitialize() */

/*----------------------------------------------------------------------------*/
/*!
 * @brief Allocate CMD_INFO_T from a free list and MGMT memory pool.
 *
 * @param[in] prAdapter      Pointer to the Adapter structure.
 * @param[in] u4Length       Length of the frame buffer to allocate.
 *
 * @retval NULL      Pointer to the valid CMD Packet handler
 * @retval !NULL     Fail to allocat CMD Packet
 */
/*----------------------------------------------------------------------------*/
P_CMD_INFO_T cmdBufAllocateCmdInfo(IN P_ADAPTER_T prAdapter, IN UINT_32 u4Length)
{
	P_CMD_INFO_T prCmdInfo;

	KAL_SPIN_LOCK_DECLARATION();

	DEBUGFUNC("cmdBufAllocateCmdInfo");

	ASSERT(prAdapter);

	KAL_ACQUIRE_SPIN_LOCK(prAdapter, SPIN_LOCK_CMD_RESOURCE);
	QUEUE_REMOVE_HEAD(&prAdapter->rFreeCmdList, prCmdInfo, P_CMD_INFO_T);
	KAL_RELEASE_SPIN_LOCK(prAdapter, SPIN_LOCK_CMD_RESOURCE);

	if (prCmdInfo) {
		/* Setup initial value in CMD_INFO_T */
		prCmdInfo->u2InfoBufLen = 0;
		prCmdInfo->fgIsOid = FALSE;

		if (u4Length) {
			/* Start address of allocated memory */
			u4Length = TFCB_FRAME_PAD_TO_DW(u4Length);

			prCmdInfo->pucInfoBuffer = cnmMemAlloc(prAdapter, RAM_TYPE_BUF, u4Length);

			if (prCmdInfo->pucInfoBuffer == NULL) {
				KAL_ACQUIRE_SPIN_LOCK(prAdapter, SPIN_LOCK_CMD_RESOURCE);
				QUEUE_INSERT_TAIL(&prAdapter->rFreeCmdList, &prCmdInfo->rQueEntry);
				KAL_RELEASE_SPIN_LOCK(prAdapter, SPIN_LOCK_CMD_RESOURCE);

				prCmdInfo = NULL;
			} else {
				kalMemZero(prCmdInfo->pucInfoBuffer, u4Length);
			}
		} else {
			prCmdInfo->pucInfoBuffer = NULL;
		}
	}

	if (prCmdInfo) {
		DBGLOG(MEM, LOUD, "CMD[0x%p] allocated! LEN[%04u], Rest[%u]\n", prCmdInfo, u4Length,
		       prAdapter->rFreeCmdList.u4NumElem);
	} else {
		DBGLOG(MEM, WARN, "CMD allocation failed! LEN[%04u], Rest[%u]\n", u4Length,
		       prAdapter->rFreeCmdList.u4NumElem);
	}

	return prCmdInfo;

} /* end of cmdBufAllocateCmdInfo() */

/*----------------------------------------------------------------------------*/
/*!
 * @brief This function is used to free the CMD Packet to the MGMT memory pool.
 *
 * @param prAdapter  Pointer to the Adapter structure.
 * @param prCmdInfo  CMD Packet handler
 *
 * @return (none)
 */
/*----------------------------------------------------------------------------*/
VOID cmdBufFreeCmdInfo(IN P_ADAPTER_T prAdapter, IN P_CMD_INFO_T prCmdInfo)
{
	KAL_SPIN_LOCK_DECLARATION();

	DEBUGFUNC("cmdBufFreeCmdInfo");

	ASSERT(prAdapter);

	if (prCmdInfo) {
		if (prCmdInfo->pucInfoBuffer) {
			cnmMemFree(prAdapter, prCmdInfo->pucInfoBuffer);
			prCmdInfo->pucInfoBuffer = NULL;
		}

		KAL_ACQUIRE_SPIN_LOCK(prAdapter, SPIN_LOCK_CMD_RESOURCE);
		QUEUE_INSERT_TAIL(&prAdapter->rFreeCmdList, &prCmdInfo->rQueEntry);
		KAL_RELEASE_SPIN_LOCK(prAdapter, SPIN_LOCK_CMD_RESOURCE);
	}

	if (prCmdInfo)
		DBGLOG(MEM, LOUD, "CMD[0x%p] freed! Rest[%u]\n", prCmdInfo, prAdapter->rFreeCmdList.u4NumElem);

	return;

} /* end of cmdBufFreeCmdPacket() */
