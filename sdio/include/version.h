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

#ifndef _VERSION_H
#define _VERSION_H
/*******************************************************************************
 *                         C O M P I L E R   F L A G S
 *******************************************************************************/

/*******************************************************************************
 *                    E X T E R N A L   R E F E R E N C E S
 *******************************************************************************/

/*******************************************************************************
 *                              C O N S T A N T S
 *******************************************************************************/

#ifndef NIC_AUTHOR
#define NIC_AUTHOR "NIC_AUTHOR"
#endif
#ifndef NIC_DESC
#define NIC_DESC "NIC_DESC"
#endif

#ifndef NIC_NAME
#define NIC_NAME "MT7668"
#define NIC_DEVICE_ID "MT7668"
#define NIC_DEVICE_ID_LOW "mt7668s"
#endif

/* NIC driver information */
#define NIC_VENDOR "MediaTek Inc."
#define NIC_VENDOR_OUI \
	{ \
		0x00, 0x0C, 0xE7 \
	}

#define NIC_PRODUCT_NAME "MediaTek Inc. Wireless LAN Adapter"
#define NIC_DRIVER_NAME "MediaTek Inc. Wireless LAN Adapter Driver"

/* Define our driver version */
#define NIC_DRIVER_MAJOR_VERSION 2
#define NIC_DRIVER_MINOR_VERSION 3
#define NIC_DRIVER_SERIAL_VERSION 1_20240626_yhpgi
// #define NIC_DRIVER_SERIAL_VERSION 1_20210111_dc6104

#define STR(s) #s
#define XSTR(x) STR(x)
#define NDV(v) XSTR(NIC_DRIVER_##v##_VERSION)
#define NDV_STR(a, i, s) NDV(a) "." NDV(i) "." NDV(s)
#define NIC_DRIVER_VERSION_STRING NDV_STR(MAJOR, MINOR, SERIAL)

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

#endif /* _VERSION_H */
