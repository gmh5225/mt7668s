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

#define P2P_INF_NAME "p2p%d"
#define AP_INF_NAME "ap%d"

/*******************************************************************************
 *                             D A T A   T Y P E S
 *******************************************************************************/

/*******************************************************************************
 *                            P U B L I C   D A T A
 *******************************************************************************/

/*******************************************************************************
 *                           P R I V A T E   D A T A
 *******************************************************************************/
static PUCHAR ifname = P2P_INF_NAME;
static PUCHAR ifname2 = P2P_INF_NAME;
static UINT_16 mode = RUNNING_P2P_MODE;

/*******************************************************************************
 *                                 M A C R O S
 *******************************************************************************/

/*******************************************************************************
 *                   F U N C T I O N   D E C L A R A T I O N S
 *******************************************************************************/

/*******************************************************************************
 *                              F U N C T I O N S
 *******************************************************************************/

VOID p2pSetSuspendMode(P_GLUE_INFO_T prGlueInfo, BOOLEAN fgEnable)
{
	struct net_device *prDev = NULL;

	if (!prGlueInfo)
		return;

	if (!prGlueInfo->prAdapter->fgIsP2PRegistered) {
		DBGLOG(INIT, INFO, "%s: P2P is not enabled, SKIP!\n", __func__);
		return;
	}

	prDev = prGlueInfo->prP2PInfo[0]->prDevHandler;
	if (!prDev) {
		DBGLOG(INIT, INFO, "%s: P2P dev is not available, SKIP!\n", __func__);
		return;
	}

	kalSetNetAddressFromInterface(prGlueInfo, prDev, fgEnable);
	wlanNotifyFwSuspend(prGlueInfo, prDev, fgEnable);
}

/*----------------------------------------------------------------------------*/
/*!
 * \brief
 *       run p2p init procedure, glue register p2p and set p2p registered flag
 *
 * \retval 1     Success
 */
/*----------------------------------------------------------------------------*/
BOOLEAN p2pLaunch(P_GLUE_INFO_T prGlueInfo)
{
	if (prGlueInfo->prAdapter->fgIsP2PRegistered == TRUE) {
		DBGLOG(P2P, INFO, "p2p is already registered\n");
		return FALSE;
	}

	if (!glRegisterP2P(prGlueInfo, ifname, ifname2, mode)) {
		DBGLOG(P2P, ERROR, "Launch failed\n");
		return FALSE;
	}

	prGlueInfo->prAdapter->fgIsP2PRegistered = TRUE;
	prGlueInfo->prAdapter->p2p_scan_report_all_bss = CFG_P2P_SCAN_REPORT_ALL_BSS;
	DBGLOG(P2P, INFO, "Launch success, fgIsP2PRegistered TRUE\n");
	return TRUE;
}

VOID p2pSetMode(IN UINT_8 ucAPMode)
{
	PUCHAR prAPInfName = AP_INF_NAME;
	PUCHAR prP2PInfName = P2P_INF_NAME;

#ifdef CFG_DRIVER_INF_NAME_CHANGE

	if (kalStrLen(gprifnamep2p) > 0) {
		if (kalStrStr(gprifnamep2p, "%d"))
			prP2PInfName = gprifnamep2p;
		else
			prP2PInfName = kalStrCat(gprifnamep2p, "%d");
		DBGLOG(INIT, WARN, "P2P ifname customized, use %s\n", prP2PInfName);
	}

	if (kalStrLen(gprifnameap) > 0) {
		if (kalStrStr(gprifnameap, "%d"))
			prAPInfName = gprifnameap;
		else
			prAPInfName = kalStrCat(gprifnameap, "%d");
		DBGLOG(INIT, WARN, "AP ifname customized, use %s\n", prAPInfName);
	}

#endif /* CFG_DRIVER_INF_NAME_CHANGE */

	switch (ucAPMode) {
	case 0:
		mode = RUNNING_P2P_MODE;
		ifname = prP2PInfName;
		break;
	case 1:
		mode = RUNNING_AP_MODE;
		ifname = prAPInfName;
		break;
	case 2:
		mode = RUNNING_DUAL_AP_MODE;
		ifname = prAPInfName;
		break;
	case 3:
		mode = RUNNING_P2P_AP_MODE;
		ifname = prP2PInfName;
		ifname2 = prAPInfName;
		break;
	}
} /* p2pSetMode */

/*----------------------------------------------------------------------------*/
/*!
 * \brief
 *       run p2p exit procedure, glue unregister p2p and set p2p registered flag
 *
 * \retval 1     Success
 */
/*----------------------------------------------------------------------------*/
BOOLEAN p2pRemove(P_GLUE_INFO_T prGlueInfo)
{
	int idx = 0;
	if (prGlueInfo->prAdapter->fgIsP2PRegistered == FALSE) {
		DBGLOG(P2P, INFO, "p2p is not registered\n");
		return FALSE;
	}

	DBGLOG(P2P, INFO, "fgIsP2PRegistered FALSE\n");
	prGlueInfo->prAdapter->fgIsP2PRegistered = FALSE;
	prGlueInfo->prAdapter->p2p_scan_report_all_bss = FALSE;
	glUnregisterP2P(prGlueInfo);

	/* gprP2pWdev/gprP2pRoleWdev[0]: base P2P dev
	 * gprP2pRoleWdev[1]: AP dev
	 * Becase the interface dev (ex: usb_device) would be free
	 * after un-plug event. Should set the wiphy->dev->parent which
	 * pointer to the interface dev to NULL. Otherwise, the corresponding
	 * system operation (poweroff, suspend) might reference it.
	 * set_wiphy_dev(wiphy, NULL): set the wiphy->dev->parent = NULL
	 * The trunk-ce1 does this, but the trunk seems not.
	 * ce1 do set_wiphy_dev(prWdev->wiphy, prDev) in wlanNetCreate.
	 * But that is after wiphy_register, and will cause exception in
	 * wiphy_unregister(), if do not set_wiphy_dev(wiphy, NULL).
	 */
	for (idx = 0; idx < KAL_P2P_NUM; idx++) {
		if (gprP2pRoleWdev[idx] == NULL)
			continue;

		DBGLOG(INIT, INFO, "Clean parent dev of P2P[%d] wiphy\n", idx);
		set_wiphy_dev(gprP2pRoleWdev[idx]->wiphy, NULL);
	}

	return TRUE;
}
