/****************************************************************
file:         uds_diag_def.h
description:  the source file of uds diagnose item definition
date:         2016/9/26
author        liuzhongwen
****************************************************************/
#include "uds_diag.h"
#include "uds_did_def.h"
#include "uds_dtc_def.h"
#include "uds_diag_item_def.h"
#include "uds_did_op.h"
#include "uds_diag_op.h"
#include "ft_uds_did_attr.h"
#include "ft_uds_did_cfg.h"
#include "uds_did.h"
#include "uds_define.h"



/* DID*/
DIAG_DID_TABLE_BEGIN()

/* DynamicData DID */

/* developed and self-tested*/
DIAG_DID_ATTR("Power Voltage", DID_POWER_VOLTAGE, DIAG_DATA_STRING, DID_LEN_POWER_VOLTAGE, 
              SecurityAccess_LEVEL0, uds_did_get_pow_voltage, NULL)

/* developed and self-tested*/
DIAG_DID_ATTR("Time", DID_TIME, DIAG_DATA_STRING, DID_LEN_TIME,
              SecurityAccess_LEVEL0, uds_did_get_time, NULL)
/* developed */
DIAG_DID_ATTR("Odometer Reading",     DID_ODOMETER_READING, DIAG_DATA_STRING, DID_LEN_ODOMETER_READING,
              SecurityAccess_LEVEL0, uds_did_get_odometer_reading, NULL)

/* developed */
DIAG_DID_ATTR("Vehicle Speed", DID_VEHICLE_SPEED, DIAG_DATA_STRING, DID_LEN_VEHICLE_SPEED,
              SecurityAccess_LEVEL0, uds_did_get_vehicle_speed,   NULL)

/* developed */
DIAG_DID_ATTR("Ignition Status", DID_IGNITION_STATUS, DIAG_DATA_STRING, DID_LEN_IGNITION_STATUS,
              SecurityAccess_LEVEL0, uds_did_get_ignition_status,NULL)

/* developed and self-tested*/
DIAG_DID_ATTR("GPS Module Status", DID_GPS_MODULE_STATUS, DIAG_DATA_STRING, DID_LEN_GPS_MODULE_STATUS,
              SecurityAccess_LEVEL0, uds_did_get_gps_module, NULL)

/* developed and self-tested*/
DIAG_DID_ATTR("GPS Positioning Status", DID_GPS_POSITIONING_STATUS, DIAG_DATA_STRING, DID_LEN_GPS_POSITIONING_STATUS,
              SecurityAccess_LEVEL0, uds_did_get_fix_status, NULL)

/* developed */
DIAG_DID_ATTR("SD Card Status", DID_SD_CARD_STATUS, DIAG_DATA_STRING, DID_LEN_SD_CARD_STATUS,
              SecurityAccess_LEVEL0, uds_did_get_emmc, NULL)

/* developed and not self-tested*/
DIAG_DID_ATTR("4G Antenna Status", DID_4G_ANTENNA_STATUS, DIAG_DATA_STRING, DID_LEN_4G_ANTENNA_STATUS,
              SecurityAccess_LEVEL0, uds_did_get_4G_main_ant, NULL)

/* developed */
DIAG_DID_ATTR("Platform Connection Status", DID_PLATFORM_CONNECTION_STATUS, DIAG_DATA_STRING, DID_LEN_PLATFORM_CONNECTION_STATUS,
              SecurityAccess_LEVEL0, uds_did_get_platform_connection_status, NULL)

/* developed and not self-tested*/
DIAG_DID_ATTR("4G Ant Signal Strength", DID_4G_ANT_SIGNAL_STRENGTH, DIAG_DATA_STRING, DID_LEN_4G_ANT_SIGNAL_STRENGTH,
              SecurityAccess_LEVEL0, uds_did_get_4G_sig, NULL)

/* developed and not self-tested*/
DIAG_DID_ATTR("CAN1 Status", DID_CAN1_STATUS, DIAG_DATA_STRING, DID_LEN_CAN1_STATUS,
              SecurityAccess_LEVEL0, uds_did_get_can1, NULL)

/* developed and not self-tested*/
DIAG_DID_ATTR("CAN2 Status", DID_CAN2_STATUS, DIAG_DATA_STRING, DID_LEN_CAN2_STATUS,
              SecurityAccess_LEVEL0, uds_did_get_can2, NULL)

/* developed */
DIAG_DID_ATTR("ESK", DID_ESK, DIAG_DATA_STRING, DID_LEN_ESK,
              SecurityAccess_LEVEL1, uds_did_get_esk, uds_did_set_esk)

/* developed and not self-tested*/
DIAG_DID_ATTR("PKI status", DID_PKI_STATUS, DIAG_DATA_STRING, DID_LEN_PKI_STATUS,
              SecurityAccess_LEVEL1, uds_did_get_pki_status, NULL)


/*  StoredData DID */

/* No need */
DIAG_DID_ATTR("Bootloader Identifier",  DID_BOOTLOADER_IDENTIFIER, DIAG_DATA_STRING, DID_LEN_BOOTLOADER_IDENTIFIER,
              SecurityAccess_LEVEL0, uds_did_get_bootloader_identifier, NULL)

/* Developed and self-tested,read only*/
DIAG_DID_ATTR("Diagnostic Session", DID_DIAGNOSTIC_SESSION, DIAG_DATA_STRING, DID_LEN_DIAGNOSTIC_SESSION,
              SecurityAccess_LEVEL0, uds_did_get_diagnostic_session, NULL)

/* Developed and self-tested,read only*/
DIAG_DID_ATTR("Spare Part Number",  DID_SPARE_PART_NUMBER, DIAG_DATA_STRING, DID_LEN_SPARE_PART_NUMBER,
              SecurityAccess_LEVEL0, uds_did_get_spare_part_number, NULL)
              
/* read only, get finished*/
DIAG_DID_ATTR("Software Upgrade Version",  DID_SOFTWARE_UPGRADE_VERSION, DIAG_DATA_STRING, DID_LEN_SOFTWARE_UPGRADE_VERSION,
              SecurityAccess_LEVEL0, uds_did_get_software_upgrade_version, NULL)

/* Developed and self-tested,read only */
DIAG_DID_ATTR("Software Fixed Version",  DID_SOFTWARE_FIXED_VERSION, DIAG_DATA_STRING, DID_LEN_SOFTWARE_FIXED_VERSION,
              SecurityAccess_LEVEL0, uds_did_get_software_fixed_version, NULL)


/*No need*/
DIAG_DID_ATTR("Calibration Software Number",  DID_CALIBRATION_SOFTWARE_NUMBER, DIAG_DATA_STRING, DID_LEN_CALIBRATION_SOFTWARE_NUMBER,
              SecurityAccess_LEVEL0, uds_did_get_calibration_software_number, NULL)

/* Developed and self-tested,read only*/
DIAG_DID_ATTR("Supplier Code",     DID_SUPPLIER_CODE, DIAG_DATA_STRING, DID_LEN_SUPPLIER_CODE,
              SecurityAccess_LEVEL0, uds_did_get_supplier_code, NULL)

/* read only,production configuration required,Developed but not self-tested */
DIAG_DID_ATTR("Manufacture Date", DID_MANUFACTURE_DATE, DIAG_DATA_STRING, DID_LEN_MANUFACTURE_DATE,
              SecurityAccess_LEVEL0, uds_did_get_manufacture_date, NULL)

/* read only,production configuration required,Developed but not self-tested */
DIAG_DID_ATTR("SN", DID_SN,  DIAG_DATA_STRING, DID_LEN_SN,
              SecurityAccess_LEVEL0, uds_did_get_sn, NULL)

/* read and write,Developed and self-tested */
DIAG_DID_ATTR("VIN", DID_VIN, DIAG_DATA_STRING, DID_LEN_VIN,
              SecurityAccess_LEVEL1, uds_did_get_vin, uds_did_set_vin)

/* read only,developed and not self_tested*/
DIAG_DID_ATTR("HW Version", DID_HW_VERSION, DIAG_DATA_STRING, DID_LEN_HW_VERSION,
              SecurityAccess_LEVEL0, uds_did_get_hw_version, NULL)

/* read and write,developed and not self-tested */
DIAG_DID_ATTR("Tester SN", DID_TESTER_SN, DIAG_DATA_STRING, DID_LEN_TESTER_SN,
              SecurityAccess_LEVEL1, uds_did_get_tester_sn, uds_did_set_tester_sn)

/* No need*/
DIAG_DID_ATTR("Programming Date", DID_PROGRAMMING_DATE, DIAG_DATA_STRING, DID_LEN_PROGRAMMING_DATE,
              SecurityAccess_LEVEL0, uds_did_get_programming_date, NULL)

/* read and write,developed and not self-tested*/
DIAG_DID_ATTR("Installation Date", DID_INSTALLATION_DATE, DIAG_DATA_STRING, DID_LEN_INSTALLATION_DATE,
              SecurityAccess_LEVEL1, uds_did_get_installation_date, uds_did_set_installation_date)
/* No need*/
DIAG_DID_ATTR("Configuration Code", DID_CONFIGURATION_CODE, DIAG_DATA_UCHAR, DID_LEN_CONFIGURATION_CODE,
              SecurityAccess_LEVEL0, uds_did_get_configuration_code, NULL)

/* read only,developed and self-tested*/
DIAG_DID_ATTR("Phone", DID_PHONE, DIAG_DATA_UCHAR, DID_LEN_PHONE,
              SecurityAccess_LEVEL0, uds_did_get_phone, NULL)

/* read only,developed and self-tested*/
DIAG_DID_ATTR("ICCID", DID_ICCID, DIAG_DATA_UCHAR, DID_LEN_ICCID, 
              SecurityAccess_LEVEL0, uds_did_get_iccid, NULL)

/* read only,developed and self-tested*/
DIAG_DID_ATTR("IMSI", DID_IMSI, DIAG_DATA_UCHAR, DID_LEN_IMSI,
              SecurityAccess_LEVEL0, uds_did_get_imsi, NULL)

/* read only,developed and self-tested*/
DIAG_DID_ATTR("IMEI", DID_IMEI, DIAG_DATA_UCHAR, DID_LEN_IMEI,
              SecurityAccess_LEVEL0, uds_did_get_imei, NULL)



DIAG_DID_TABLE_END()


DIAG_TABLE_BEGIN()

DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_ECALL_SWITCH)
DIAG_ITEM_DTC(DTC_ECALL_SWITCH)
DIAG_ITEM_NAME("ECALL")
DIAG_ITEM_FUN(ft_uds_diag_dev_ecall)
DIAG_ITEM_THSD(45)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_GPS_ANTENNA_SHORT_TO_GND)
DIAG_ITEM_DTC(DTC_GPS_ANTENNA_SHORT_TO_GND)
DIAG_ITEM_NAME("GPS ANT TO GND")
DIAG_ITEM_FUN(ft_uds_diag_gps_ant_gnd)
DIAG_ITEM_THSD(4)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_GPS_ANTENNA_OPEN)
DIAG_ITEM_DTC(DTC_GPS_ANTENNA_OPEN)
DIAG_ITEM_NAME("GPS ANT OPEN")
DIAG_ITEM_FUN(ft_uds_diag_gps_ant_open)
DIAG_ITEM_THSD(4)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_GPS_MODULE_FAULT)
DIAG_ITEM_DTC(DTC_GPS_MODULE_FAULT)
DIAG_ITEM_NAME("GPS MODULE FAULT")
DIAG_ITEM_FUN(ft_uds_diag_dev_gps_module)
DIAG_ITEM_THSD(4)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_WAN_ANTENNA_SHORT_TO_GND)
DIAG_ITEM_DTC(DTC_WAN_ANTENNA_SHORT_TO_GND)
DIAG_ITEM_NAME("WAN ANT GND")
DIAG_ITEM_FUN(ft_uds_diag_wan_ant_gnd)
DIAG_ITEM_THSD(4)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_WAN_ANTENNA_OPEN)
DIAG_ITEM_DTC(DTC_WAN_ANTENNA_OPEN)
DIAG_ITEM_NAME("WAN ANT OPEN")
DIAG_ITEM_FUN(ft_uds_diag_wan_ant_open)
DIAG_ITEM_THSD(12)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_GSM_MODULE)
DIAG_ITEM_DTC(DTC_GSM_MODULE)
DIAG_ITEM_NAME("GSM")
DIAG_ITEM_FUN(ft_uds_diag_gsm)
DIAG_ITEM_THSD(60)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_SIM_FAULT)
DIAG_ITEM_DTC(DTC_SIM_FAULT)
DIAG_ITEM_NAME("SIM")
DIAG_ITEM_FUN(ft_uds_diag_sim)
DIAG_ITEM_THSD(60)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_BATTERY_TOO_LOW)
DIAG_ITEM_DTC(DTC_BATTERY_TOO_LOW)
DIAG_ITEM_NAME("BAT LOW")
DIAG_ITEM_FUN(ft_uds_diag_bat_low)
DIAG_ITEM_THSD(10)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_BATTERY_TOO_HIGH)
DIAG_ITEM_DTC(DTC_BATTERY_TOO_HIGH)
DIAG_ITEM_NAME("BAT HIGH")
DIAG_ITEM_FUN(ft_uds_diag_bat_high)
DIAG_ITEM_THSD(10)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_BATTERY_AGED)
DIAG_ITEM_DTC(DTC_BATTERY_AGED)
DIAG_ITEM_NAME("BAT AGED")
DIAG_ITEM_FUN(ft_uds_diag_bat_aged)
DIAG_ITEM_THSD(10)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()


DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_POWER_VOLTAGE_HIGH)
DIAG_ITEM_DTC(DTC_POWER_VOLTAGE_HIGH)
DIAG_ITEM_NAME("power high")
DIAG_ITEM_FUN(ft_uds_diag_power_high)
DIAG_ITEM_THSD(1)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_POWER_VOLTAGE_LOW)
DIAG_ITEM_DTC(DTC_POWER_VOLTAGE_LOW)
DIAG_ITEM_NAME("power low")
DIAG_ITEM_FUN(ft_uds_diag_power_low)
DIAG_ITEM_THSD(1)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()


/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_GW_TBOXCAN)
DIAG_ITEM_DTC(DTC_Missing_GW_TBOXCAN)
DIAG_ITEM_NAME("Missing GW")
DIAG_ITEM_FUN(uds_diag_dev_missing_gw)
DIAG_ITEM_THSD(1)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_BUSOFF)
DIAG_ITEM_DTC(DTC_BUSOFF)
DIAG_ITEM_NAME("Busoff")
DIAG_ITEM_FUN(uds_diag_dev_can_busoff)
DIAG_ITEM_THSD(1)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()


/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_ACU)
DIAG_ITEM_DTC(DTC_MISSING_ACU)
DIAG_ITEM_NAME("missing acu")
DIAG_ITEM_FUN(uds_diag_dev_acu_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_BMS)
DIAG_ITEM_DTC(DTC_MISSING_BMS)
DIAG_ITEM_NAME("missing bms")
DIAG_ITEM_FUN(uds_diag_dev_bms_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_CDU)
DIAG_ITEM_DTC(DTC_MISSING_CDU)
DIAG_ITEM_NAME("missing cdu")
DIAG_ITEM_FUN(uds_diag_dev_cdu_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_MCU)
DIAG_ITEM_DTC(DTC_MISSING_MCU)
DIAG_ITEM_NAME("missing mcu")
DIAG_ITEM_FUN(uds_diag_dev_mcu_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_VCU1)
DIAG_ITEM_DTC(DTC_MISSING_VCU1)
DIAG_ITEM_NAME("missing vcu1")
DIAG_ITEM_FUN(uds_diag_dev_vcu1_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_EPS)
DIAG_ITEM_DTC(DTC_MISSING_EPS)
DIAG_ITEM_NAME("missing eps")
DIAG_ITEM_FUN(uds_diag_dev_eps_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_ESC)
DIAG_ITEM_DTC(DTC_MISSING_ESC)
DIAG_ITEM_NAME("missing esc")
DIAG_ITEM_FUN(uds_diag_dev_esc_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_EHB)
DIAG_ITEM_DTC(DTC_MISSING_EHB)
DIAG_ITEM_NAME("missing ehb")
DIAG_ITEM_FUN(uds_diag_dev_ehb_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_EACP)
DIAG_ITEM_DTC(DTC_MISSING_EACP)
DIAG_ITEM_NAME("missing eacp")
DIAG_ITEM_FUN(uds_diag_dev_eacp_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_PTC)
DIAG_ITEM_DTC(DTC_MISSING_PTC)
DIAG_ITEM_NAME("missing ptc")
DIAG_ITEM_FUN(uds_diag_dev_ptc_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_PLG)
DIAG_ITEM_DTC(DTC_MISSING_PLG)
DIAG_ITEM_NAME("missing plg")
DIAG_ITEM_FUN(uds_diag_dev_plg_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_CLM)
DIAG_ITEM_DTC(DTC_MISSING_CLM)
DIAG_ITEM_NAME("missing clm")
DIAG_ITEM_FUN(uds_diag_dev_clm_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_BDCM)
DIAG_ITEM_DTC(DTC_MISSING_BDCM)
DIAG_ITEM_NAME("missing bdcm")
DIAG_ITEM_FUN(uds_diag_dev_bdcm_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_ALM)
DIAG_ITEM_DTC(DTC_MISSING_ALM)
DIAG_ITEM_NAME("missing alm")
DIAG_ITEM_FUN(uds_diag_dev_alm_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_ICU)
DIAG_ITEM_DTC(DTC_MISSING_ICU)
DIAG_ITEM_NAME("missing icu")
DIAG_ITEM_FUN(uds_diag_dev_icu_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_IHU)
DIAG_ITEM_DTC(DTC_MISSING_IHU)
DIAG_ITEM_NAME("missing ihu")
DIAG_ITEM_FUN(uds_diag_dev_ihu_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

/* developed */
DIAG_ITEM_BEGIN()
DIAG_ITEM_ID(DTC_NUM_MISSING_TAP)
DIAG_ITEM_DTC(DTC_MISSING_TAP)
DIAG_ITEM_NAME("missing tap")
DIAG_ITEM_FUN(uds_diag_dev_tap_can_bus_miss)
DIAG_ITEM_THSD(20)
DIAG_FREEZE_BEGIN()
DIAG_DID(DID_POWER_VOLTAGE)
DIAG_DID(DID_ODOMETER_READING)
DIAG_DID(DID_VEHICLE_SPEED)    
DIAG_DID(DID_IGNITION_STATUS)
DIAG_DID(DID_TIME)
DIAG_FREEZE_END()
DIAG_ITEM_END()

DIAG_TABLE_END()




