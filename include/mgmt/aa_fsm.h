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

#ifndef _AA_FSM_H
#define _AA_FSM_H

/*******************************************************************************
 *                         C O M P I L E R   F L A G S
 *******************************************************************************/

/*******************************************************************************
 *                    E X T E R N A L   R E F E R E N C E S
 *******************************************************************************/

/*******************************************************************************
 *                              C O N S T A N T S
 *******************************************************************************/
/* Retry interval for retransmiting authentication-request MMPDU. */
#define TX_AUTHENTICATION_RETRY_TIMEOUT_TU 100 /* TU. */

/* Retry interval for retransmiting association-request MMPDU. */
#define TX_ASSOCIATION_RETRY_TIMEOUT_TU 100 /* TU. */

/* Wait for a response to a transmitted authentication-request MMPDU. */
#define DOT11_AUTHENTICATION_RESPONSE_TIMEOUT_TU 512 /* TU. */

/* Wait for a response to a transmitted association-request MMPDU. */
#define DOT11_ASSOCIATION_RESPONSE_TIMEOUT_TU 512 /* TU. */
#if CFG_SUPPORT_CFG80211_AUTH
/* Wait for a response to a transmitted SAE authentication MMPDU. */
/* Default value on 802.11-REVmd-D0.5 */
#define DOT11_RSNA_SAE_RETRANS_PERIOD_TU 2000
#endif
/* The maximum time to wait for JOIN process complete. */
#define JOIN_FAILURE_TIMEOUT_BEACON_INTERVAL 20 /* Beacon Interval, 20 * 100TU = 2 sec. */

/* Retry interval for next JOIN request. */
#define JOIN_RETRY_INTERVAL_SEC 10 /* Seconds */

/* Maximum Retry Count for accept a JOIN request. */
#define JOIN_MAX_RETRY_FAILURE_COUNT 2 /* Times */

#define TX_AUTHENTICATION_RESPONSE_TIMEOUT_TU 512 /* TU. */

#define TX_ASSOCIATE_TIMEOUT_TU 512 /* TU. */

/*******************************************************************************
 *                             D A T A   T Y P E S
 *******************************************************************************/
typedef enum _ENUM_AA_STATE_T {
	AA_STATE_IDLE = 0,
	SAA_STATE_SEND_AUTH1,
	SAA_STATE_WAIT_AUTH2,
	SAA_STATE_SEND_AUTH3,
	SAA_STATE_WAIT_AUTH4,
	SAA_STATE_SEND_ASSOC1,
	SAA_STATE_WAIT_ASSOC2,
	AAA_STATE_SEND_AUTH2,
	AAA_STATE_SEND_AUTH4, /* We may not use, because P2P GO didn't support WEP and 11r */
	AAA_STATE_SEND_ASSOC2,
	AA_STATE_RESOURCE, /* A state for debugging the case of out of msg buffer. */
	AA_STATE_NUM
} ENUM_AA_STATE_T;

#if CFG_SUPPORT_CFG80211_AUTH
enum ENUM_AA_SENT_T {
	AA_SENT_NONE = 0,
	AA_SENT_AUTH1, /* = auth transaction SN */
	AA_SENT_AUTH2,
	AA_SENT_AUTH3,
	AA_SENT_AUTH4,
	AA_SENT_ASSOC1,	  /* req */
	AA_SENT_ASSOC2,	  /* resp */
	AA_SENT_RESOURCE, /* A state for debug the case of out of msg buffer */
	AA_SENT_NUM
};
#endif

typedef enum _ENUM_AA_FRM_TYPE_T { FRM_DISASSOC = 0, FRM_DEAUTH } ENUM_AA_FRM_TYPE_T;

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
 *                  F U N C T I O N   D E C L A R A T I O N S
 *******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Routines in saa_fsm.c                                                      */
/*----------------------------------------------------------------------------*/
VOID saaFsmSteps(IN P_ADAPTER_T prAdapter, IN P_STA_RECORD_T prStaRec, IN ENUM_AA_STATE_T eNextState,
		 IN P_SW_RFB_T prRetainedSwRfb);

WLAN_STATUS
saaFsmSendEventJoinComplete(IN P_ADAPTER_T prAdapter, WLAN_STATUS rJoinStatus, P_STA_RECORD_T prStaRec,
			    P_SW_RFB_T prSwRfb);

VOID saaFsmRunEventStart(IN P_ADAPTER_T prAdapter, IN P_MSG_HDR_T prMsgHdr);

WLAN_STATUS
saaFsmRunEventTxDone(IN P_ADAPTER_T prAdapter, IN P_MSDU_INFO_T prMsduInfo, IN ENUM_TX_RESULT_CODE_T rTxDoneStatus);

VOID saaFsmRunEventTxReqTimeOut(IN P_ADAPTER_T prAdapter, IN ULONG plParamPtr);

VOID saaFsmRunEventRxRespTimeOut(IN P_ADAPTER_T prAdapter, IN ULONG ulParamPtr);

VOID saaFsmRunEventRxAuth(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb);

WLAN_STATUS saaFsmRunEventRxAssoc(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb);

WLAN_STATUS saaFsmRunEventRxDeauth(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb);

WLAN_STATUS saaFsmRunEventRxDisassoc(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb);

VOID saaFsmRunEventAbort(IN P_ADAPTER_T prAdapter, IN P_MSG_HDR_T prMsgHdr);

VOID saaChkDeauthfrmParamHandler(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb, IN P_STA_RECORD_T prStaRec);

VOID saaChkDisassocfrmParamHandler(IN P_ADAPTER_T prAdapter, IN P_WLAN_DISASSOC_FRAME_T prDisassocFrame,
				   IN P_STA_RECORD_T prStaRec, IN P_SW_RFB_T prSwRfb);

VOID saaSendDisconnectMsgHandler(IN P_ADAPTER_T prAdapter, IN P_STA_RECORD_T prStaRec, IN P_BSS_INFO_T prAisBssInfo,
				 IN ENUM_AA_FRM_TYPE_T eFrmType);

#if CFG_SUPPORT_CFG80211_AUTH
VOID saaSendAuthAssoc(IN P_ADAPTER_T prAdapter, IN P_STA_RECORD_T prStaRec);
void saaSendAuthSeq3(IN P_ADAPTER_T prAdapter, IN P_STA_RECORD_T prStaRec);
#endif

/*----------------------------------------------------------------------------*/
/* Routines in aaa_fsm.c                                                      */
/*----------------------------------------------------------------------------*/
VOID aaaFsmRunEventRxAuth(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb);

WLAN_STATUS aaaFsmRunEventRxAssoc(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb);

WLAN_STATUS
aaaFsmRunEventTxDone(IN P_ADAPTER_T prAdapter, IN P_MSDU_INFO_T prMsduInfo, IN ENUM_TX_RESULT_CODE_T rTxDoneStatus);

/*******************************************************************************
 *                              F U N C T I O N S
 *******************************************************************************/

#endif /* _AA_FSM_H */
