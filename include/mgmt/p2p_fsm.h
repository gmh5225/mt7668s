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

#ifndef _P2P_FSM_H
#define _P2P_FSM_H

VOID p2pFsmRunEventScanRequest(IN P_ADAPTER_T prAdapter, IN P_MSG_HDR_T prMsgHdr);

VOID p2pFsmRunEventChGrant(IN P_ADAPTER_T prAdapter, IN P_MSG_HDR_T prMsgHdr);

VOID p2pFsmRunEventNetDeviceRegister(IN P_ADAPTER_T prAdapter, IN P_MSG_HDR_T prMsgHdr);

VOID p2pFsmRunEventUpdateMgmtFrame(IN P_ADAPTER_T prAdapter, IN P_MSG_HDR_T prMsgHdr);

#if CFG_SUPPORT_WFD
VOID p2pFsmRunEventWfdSettingUpdate(IN P_ADAPTER_T prAdapter, IN P_MSG_HDR_T prMsgHdr);
#endif

VOID p2pFsmRunEventScanDone(IN P_ADAPTER_T prAdapter, IN P_MSG_HDR_T prMsgHdr);

#endif /* _P2P_FSM_H */
