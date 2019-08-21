
/****************************************************************
file:         cfg_para_def.h
description:  the source file of parameter definition
date:         2016/9/26
author        liuzhongwen
****************************************************************/

CFG_TABLE_BEGIN()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_SN_NUM)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Terminal Addr", CFG_DATA_UINT,
           sizeof(unsigned int))                    /* set sn number */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DEV_NUM)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Device Number", CFG_DATA_UINT,
           sizeof(unsigned int))                    /* set dev number */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_SLEEP_MODE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Sleep Mode", CFG_DATA_UCHAR, sizeof(unsigned char)) /* set sleep mode */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_LOCAL_APN)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Local APN", CFG_DATA_STRING, 32)        /* set local APN */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_LOC_APN_AUTH)
CFG_MEMBER_BEGIN()
CFG_MEMBER("User: ", CFG_DATA_STRING, 32)           /* set dial auth */
CFG_MEMBER("PassWord:", CFG_DATA_STRING, 32)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_WAN_APN)
CFG_MEMBER_BEGIN()
CFG_MEMBER("WAN APN", CFG_DATA_STRING, 32)          /* set wan APN */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_WAN_APN_AUTH)
CFG_MEMBER_BEGIN()
CFG_MEMBER("User: ", CFG_DATA_STRING, 32)           /* set dial auth */
CFG_MEMBER("PassWord:", CFG_DATA_STRING, 32)
CFG_MEMBER_END()
CFG_ITEM_END()


CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DBC_PATH)
CFG_MEMBER_BEGIN()
CFG_MEMBER("DBC path", CFG_DATA_STRING, 256)        /* DBC PATH */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_WIFI_SET)
CFG_MEMBER_BEGIN()
CFG_MEMBER("WiFi enable", CFG_DATA_UCHAR,
           sizeof(unsigned char))                   /* set wifi state */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DCOM_SET)
CFG_MEMBER_BEGIN()
CFG_MEMBER("DCOM enable", CFG_DATA_UCHAR,
           sizeof(unsigned char))                   /* set public net switch */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_NET_TYPE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Mobile Net type", CFG_DATA_UCHAR,
           sizeof(unsigned char))                   /* set net type */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_WIFI_MAXASSOC)
CFG_MEMBER_BEGIN()
CFG_MEMBER("WiFi maxassoc", CFG_DATA_UCHAR,
           sizeof(unsigned char))                   /* set wifi max assoc */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_WIFI_SSID)
CFG_MEMBER_BEGIN()
CFG_MEMBER("WiFi SSID", CFG_DATA_STRING, 32)        /* set ap ssid */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_WIFI_KEY)
CFG_MEMBER_BEGIN()
CFG_MEMBER("WiFi Key", CFG_DATA_STRING, 32)         /* set ap password */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_ICALL)
CFG_MEMBER_BEGIN()
CFG_MEMBER("iCall Number", CFG_DATA_STRING, 32)            /* set icall number */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_BCALL)
CFG_MEMBER_BEGIN()
CFG_MEMBER("bCall Number", CFG_DATA_STRING, 32)            /* set bcall number */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_ECALL)
CFG_MEMBER_BEGIN()
CFG_MEMBER("eCall Number", CFG_DATA_STRING, 32)            /* set ecall number */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_WHITE_LIST)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Call white list", CFG_DATA_STRING, 512)      /* set white list */
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_SLEEP_TIME)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Sleep Time(min)", CFG_DATA_UINT, 4)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DSLEEP_TIME)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Deep Sleep Time(min)", CFG_DATA_UINT, 4)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_VTD)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Vehicle anti-theft function", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_ACC_THS)
CFG_MEMBER_BEGIN()
CFG_MEMBER("G-sensor Threshold(0-4096)mg", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_ICALL_F)
CFG_MEMBER_BEGIN()
CFG_MEMBER("iCall function", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_BCALL_F)
CFG_MEMBER_BEGIN()
CFG_MEMBER("bCall function", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_ECALL_F)
CFG_MEMBER_BEGIN()
CFG_MEMBER("eCall function", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_CAN_DEFAULT_BAUD_0)
CFG_MEMBER_BEGIN()
CFG_MEMBER("CAN 1 default baud rate", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_CAN_DEFAULT_BAUD_1)
CFG_MEMBER_BEGIN()
CFG_MEMBER("CAN 2 default baud rate", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_CAN_DEFAULT_BAUD_2)
CFG_MEMBER_BEGIN()
CFG_MEMBER("CAN 3 default baud rate", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_CAN_DEFAULT_BAUD_3)
CFG_MEMBER_BEGIN()
CFG_MEMBER("CAN 4 default baud rate", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_CAN_DEFAULT_BAUD_4)
CFG_MEMBER_BEGIN()
CFG_MEMBER("CAN 5 default baud rate", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_LOG_ENABLE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Log Save", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_RTC_WAKEUP_TIME)
CFG_MEMBER_BEGIN()
CFG_MEMBER("RTC wakeup time", CFG_DATA_UINT, 4)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_BAT_TYPE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("BATTERY type", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

#if 0
CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_GB32960_VIN)
CFG_MEMBER_BEGIN()
CFG_MEMBER("GB32960 VIN", CFG_DATA_STRING, 18)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_GB32960_URL)
CFG_MEMBER_BEGIN()
CFG_MEMBER("GB32960 server url", CFG_DATA_STRING, 256)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_GB32960_PORT)
CFG_MEMBER_BEGIN()
CFG_MEMBER("GB32960 server port", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_GB32960_INTERVAL)
CFG_MEMBER_BEGIN()
CFG_MEMBER("GB32960 report interval", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_GB32960_REGINTV)
CFG_MEMBER_BEGIN()
CFG_MEMBER("GB32960 login interval", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_GB32960_TIMEOUT)
CFG_MEMBER_BEGIN()
CFG_MEMBER("GB32960 network timeout", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_GB32960_REGSEQ)
CFG_MEMBER_BEGIN()
CFG_MEMBER("GB32960 login sequence", CFG_DATA_UINT, 4)
CFG_MEMBER_END()
CFG_ITEM_END()
#endif
CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DSU_AUTHKEY)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Authkey", CFG_DATA_STRING, 256)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DSU_CANLOG_TIME)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Canlog time", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DSU_CANLOG_MODE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("Canlog mode", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DSU_SDHZ)
CFG_MEMBER_BEGIN()
CFG_MEMBER("SDHZ", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DSU_HOURFILE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("HourFile", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DSU_LOOPFILE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("LoopFile", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FOTON_VIN)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON VIN", CFG_DATA_STRING, 18)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FOTON_URL)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON server url", CFG_DATA_STRING, 256)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FOTON_PORT)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON server port", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FOTON_INTERVAL)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON report interval", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FOTON_REGINTV)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON login interval", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FOTON_TIMEOUT)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON network timeout", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

/*Logistics FT_UDS_PARAS: Cindy added 20180502*/
CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_UDS_REPAIR_SHOP_CODE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON UDS REPAIR SHOP CODE", CFG_DATA_STRING, 10)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_UDS_AVN_SERIAL_NUMBER)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON UDS AVN SN", CFG_DATA_STRING, 16)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_UDS_VEHICLE_TYPE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON UDS VEHICLE TYPE", CFG_DATA_UCHAR, sizeof(unsigned char))
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_CAN2_AUTO_BAUD)
CFG_MEMBER_BEGIN()
CFG_MEMBER("CAN2_AUTO_BAUD", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_UDS_POWER)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON UDS POWER", CFG_DATA_UCHAR, sizeof(unsigned char))
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FUELCELL)
CFG_MEMBER_BEGIN()
CFG_MEMBER("fuel cell", CFG_DATA_UCHAR, sizeof(unsigned char))
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_PART_NUM)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON PART NUM", CFG_DATA_STRING, 14)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_UDS_HW)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON UDS HW", CFG_DATA_STRING, 14)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_INTEST_HW)
CFG_MEMBER_BEGIN()
CFG_MEMBER("INTEST HW", CFG_DATA_STRING, 32)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_HBINTV)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON Heart intv", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_REGISTER)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON register status", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_TID)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON Terminal ID", CFG_DATA_STRING, 7)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_SIM)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON SIM", CFG_DATA_STRING, 13)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_DTN)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON Devices TN", CFG_DATA_STRING, 29)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_DEV_TYPE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON Device Model", CFG_DATA_STRING, 10)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_DEV_SN)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON Devices Number", CFG_DATA_STRING, 13)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_TYPE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON Engine Type", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FT_PORT)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FOTON Port", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FTTSP_VIN)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FTTSP VIN", CFG_DATA_STRING, 18)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FTTSP_URL)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FTTSP server url", CFG_DATA_STRING, 256)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FTTSP_PORT)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FTTSP server port", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FTTSP_INTERVAL)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FTTSP report interval", CFG_DATA_USHORT, 2)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_FTTSP_TUKEY)
CFG_MEMBER_BEGIN()
CFG_MEMBER("FTTSP TUKEY", CFG_DATA_STRING, 17)
CFG_MEMBER_END()
CFG_ITEM_END()

#if 0
////////HOZON remote Config
CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_HOZON_TSP_RMTCFG)
CFG_MEMBER_BEGIN()
CFG_MEMBER("remote_configure", CFG_DATA_STRING, 512)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_HOZON_TSP_TBOXID)
CFG_MEMBER_BEGIN()
CFG_MEMBER("HOZON tsp tboxid", CFG_DATA_UINT,4)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_HOZON_TSP_MCUSW)
CFG_MEMBER_BEGIN()
CFG_MEMBER("mcuSw", CFG_DATA_STRING, 11)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_HOZON_TSP_MPUSW)
CFG_MEMBER_BEGIN()
CFG_MEMBER("mpuSw", CFG_DATA_STRING, 11)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_HOZON_TSP_TBOXSN)
CFG_MEMBER_BEGIN()
CFG_MEMBER("hozon tboxsn", CFG_DATA_STRING, 19)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_HOZON_TSP_DIAGDATE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("hozon diag datetime", CFG_DATA_UINT, 4)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_HOZON_TSP_DIAGFLAG)
CFG_MEMBER_BEGIN()
CFG_MEMBER("hozon diag flag", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_HOZON_TSP_RMTAPPOINT)
CFG_MEMBER_BEGIN()
CFG_MEMBER("hozon remote ctrl appointment", CFG_DATA_STRING, 32)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_HOZON_TSP_RMTACAPPOINT)
CFG_MEMBER_BEGIN()
CFG_MEMBER("hozon remote ctrl ac appointment", CFG_DATA_STRING, 100)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_HOZON_TSP_CERT_VALID)
CFG_MEMBER_BEGIN()
CFG_MEMBER("hozon certificate validity", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_HOZON_TSP_CERT_EN)
CFG_MEMBER_BEGIN()
CFG_MEMBER("hozon certificate enable", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_HOZON_TSP_CERT)
CFG_MEMBER_BEGIN()
CFG_MEMBER("hozon certificate", CFG_DATA_STRING, 32)
CFG_MEMBER_END()
CFG_ITEM_END()
#endif

/* UDS*/
CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DID_MDATE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("manufacture date", CFG_DATA_STRING, DID_LEN_MANUFACTURE_DATE)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DID_SN)
CFG_MEMBER_BEGIN()
CFG_MEMBER("SN", CFG_DATA_STRING, DID_LEN_SN)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DID_VIN)
CFG_MEMBER_BEGIN()
CFG_MEMBER("VIN", CFG_DATA_STRING, DID_LEN_VIN)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DID_TESTER_SN)
CFG_MEMBER_BEGIN()
CFG_MEMBER("tester SN", CFG_DATA_STRING, DID_LEN_TESTER_SN)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DID_INSTALL_DATE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("installation date", CFG_DATA_STRING, DID_LEN_INSTALLATION_DATE)
CFG_MEMBER_END()
CFG_ITEM_END()
    
CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DID_SW_UPGRADE_VER)
CFG_MEMBER_BEGIN()
CFG_MEMBER("software number", CFG_DATA_STRING, DID_LEN_SOFTWARE_UPGRADE_VERSION)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_DID_ESK)
CFG_MEMBER_BEGIN()
CFG_MEMBER("ESK", CFG_DATA_STRING, DID_LEN_ESK)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_EN_BLE)
CFG_MEMBER_BEGIN()
CFG_MEMBER("BLE EN", CFG_DATA_UCHAR, 1)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_ITEM_BEGIN()
CFG_ITEM_ID(CFG_ITEM_BLE_NAME)
CFG_MEMBER_BEGIN()
CFG_MEMBER("BLE NAME", CFG_DATA_STRING, 50)
CFG_MEMBER_END()
CFG_ITEM_END()

CFG_TABLE_END()

