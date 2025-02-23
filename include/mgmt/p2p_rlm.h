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

#ifndef _P2P_RLM_H
#define _P2P_RLM_H

/*******************************************************************************
 *                         C O M P I L E R   F L A G S
 *******************************************************************************/

/*******************************************************************************
 *                    E X T E R N A L   R E F E R E N C E S
 *******************************************************************************/

/*******************************************************************************
 *                              C O N S T A N T S
 *******************************************************************************/
#define CHANNEL_SPAN_20 20

/*******************************************************************************
 *                                 M A C R O S
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
 *                  F U N C T I O N   D E C L A R A T I O N S
 *******************************************************************************/

VOID rlmBssInitForAP(P_ADAPTER_T prAdapter, P_BSS_INFO_T prBssInfo);

BOOLEAN rlmUpdateBwByChListForAP(P_ADAPTER_T prAdapter, P_BSS_INFO_T prBssInfo);

VOID rlmUpdateParamsForAP(P_ADAPTER_T prAdapter, P_BSS_INFO_T prBssInfo, BOOLEAN fgUpdateBeacon);

VOID rlmFuncInitialChannelList(IN P_ADAPTER_T prAdapter);

VOID rlmFuncCommonChannelList(IN P_ADAPTER_T prAdapter, IN P_CHANNEL_ENTRY_FIELD_T prChannelEntryII,
			      IN UINT_8 ucChannelListSize);

UINT_8 rlmFuncFindOperatingClass(IN P_ADAPTER_T prAdapter, IN UINT_8 ucChannelNum);

BOOLEAN
rlmFuncFindAvailableChannel(IN P_ADAPTER_T prAdapter, IN UINT_8 ucCheckChnl, IN PUINT_8 pucSuggestChannel,
			    IN BOOLEAN fgIsSocialChannel, IN BOOLEAN fgIsDefaultChannel);

ENUM_CHNL_EXT_T rlmDecideScoForAP(P_ADAPTER_T prAdapter, P_BSS_INFO_T prBssInfo);

ENUM_CHNL_EXT_T rlmGetScoForAP(P_ADAPTER_T prAdapter, P_BSS_INFO_T prBssInfo);

UINT_8 rlmGetVhtS1ForAP(P_ADAPTER_T prAdapter, P_BSS_INFO_T prBssInfo);

#endif
