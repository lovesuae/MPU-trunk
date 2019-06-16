/******************************************************
�ļ�����	PrvtProt_Shell.c

������	��ҵ˽��Э�飨�㽭���ڣ�	
Data			Vasion			author
2018/1/10		V1.0			liujian
*******************************************************/

/*******************************************************
description�� include the header file
*******************************************************/
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include  <errno.h>
#include <sys/times.h>
#include "timer.h"
#include "log.h"
#include "shell_api.h"
#include "hozon_PP_api.h"
#include "PrvtProt_callCenter.h"
#include "PrvtProt_xcall.h"
#include "PrvtProt_remoteConfig.h"
//#include "remoteControl/PP_doorLockCtrl.h"
#include "PP_rmtCtrl.h"
#include "PrvtProt_VehiSt.h"
#include "PrvtProt_shell.h"
/*******************************************************
description�� global variable definitions
*******************************************************/

/*******************************************************
description�� static variable definitions
*******************************************************/


/*******************************************************
description�� function declaration
*******************************************************/
/*Global function declaration*/

/*Static function declaration*/
static int PP_shell_setHeartBeatPeriod(int argc, const char **argv);
static int PP_shell_setSuspend(int argc, const char **argv);
static int PP_shell_setEcallReq(int argc, const char **argv);
static int PP_shell_setEcallResp(int argc, const char **argv);
static int PP_shell_SetRmtCfgReq(int argc, const char **argv);
static int PP_shell_SetRmtCtrlReq(int argc, const char **argv);
static int PP_shell_SetRmtVSReq(int argc, const char **argv);
static int PP_shell_SetTboxid(int argc, const char **argv);
static int PP_shell_SetTmcuSw(int argc, const char **argv);
static int PP_shell_SetTmpuSw(int argc, const char **argv);
static int PP_shell_Seticcid(int argc, const char **argv);

static int PP_shell_showpara(int argc, const char **argv);
/******************************************************
description�� function code
******************************************************/
/******************************************************
*��������PrvtProt_shell_init

*��  �Σ�void

*����ֵ��void

*��  ������ʼ��

*��  ע��
******************************************************/
void PrvtProt_shell_init(void)
{
	shell_cmd_register("hozon_setHeartBeatPeriod", PP_shell_setHeartBeatPeriod, "set HOZON PrvtProt HeartBeat Period");
	shell_cmd_register("hozon_setSuspend", PP_shell_setSuspend, "set HOZON PrvtProt suspend");
	shell_cmd_register("hozon_setEcallReq", PP_shell_setEcallReq, "set HOZON PrvtProt ecall request");
	shell_cmd_register("hozon_setEcallResp", PP_shell_setEcallResp, "set HOZON PrvtProt ecall response");
	shell_cmd_register("hozon_setRmtCfgReq", PP_shell_SetRmtCfgReq, "set HOZON PrvtProt remote config request");
	shell_cmd_register("hozon_setRmtCtrlReq", PP_shell_SetRmtCtrlReq, "set HOZON PrvtProt remote control request");
	shell_cmd_register("hozon_setRmtVSReq", PP_shell_SetRmtVSReq, "set HOZON PrvtProt remote VS request");

	shell_cmd_register("hozon_settboxid", PP_shell_SetTboxid, "set HOZON tboxid");
	shell_cmd_register("hozon_setmcuSw", PP_shell_SetTmcuSw, "set HOZON mcuSw");
	shell_cmd_register("hozon_setmpuSw", PP_shell_SetTmpuSw, "set HOZON mpuSw");
	shell_cmd_register("hozon_seticcid", PP_shell_Seticcid, "set HOZON iccid");


	/* show */
	shell_cmd_register("hozon_showpara", PP_shell_showpara, "show HOZON parameter");
}


/******************************************************
*��������PP_shell_setHeartBeatPeriod

*��  �Σ�
argv[0] - �������� ����λ:��


*����ֵ��void

*��  ����

*��  ע��
******************************************************/
static int PP_shell_setHeartBeatPeriod(int argc, const char **argv)
{
	unsigned int period;
    if (argc != 1)
    {
        shellprintf(" usage: HOZON_PP_SetheartbeatPeriod <heartbeat period>\r\n");
        return -1;
    }
	
	sscanf(argv[0], "%u", &period);
	log_o(LOG_HOZON, "heartbeat period = %d",period);
	if(period == 0)
	{
		 shellprintf(" usage: heartbeat period invalid\r\n");
		 return -1;
	}	
	PrvtPro_SetHeartBeatPeriod((uint8_t)period);
	
	sleep(1);
    return 0;
}


/******************************************************
*��������PP_shell_setSuspend

*��  �Σ�������ͣ


*����ֵ��void

*��  ����

*��  ע��
******************************************************/
static int PP_shell_setSuspend(int argc, const char **argv)
{
	unsigned int suspend;
    if (argc != 1)
    {
        shellprintf(" usage: HOZON_PP_Setsuspend <suspend>\r\n");
        return -1;
    }
	
	sscanf(argv[0], "%u", &suspend);
	log_o(LOG_HOZON, "suspend = %d",suspend);
	PrvtPro_Setsuspend((uint8_t)suspend);
	
    sleep(1);
    return 0;
}

/******************************************************
*��������PP_shell_setEcallReq

*��  �Σ�����ecall request


*����ֵ��void

*��  ����

*��  ע��
******************************************************/
static int PP_shell_setEcallReq(int argc, const char **argv)
{
	unsigned int EcallReq;
    if (argc != 1)
    {
        shellprintf(" usage: HOZON_PP_Setsuspend <ecall req>\r\n");
        return -1;
    }
	
	sscanf(argv[0], "%u", &EcallReq);
	log_o(LOG_HOZON, "EcallReq = %d",EcallReq);
	PP_xcall_SetEcallReq((uint8_t)EcallReq);
	
    sleep(1);
    return 0;
}


/******************************************************
*��������PP_shell_setEcallResp

*��  �Σ�����ecall response


*����ֵ��void

*��  ����

*��  ע��
******************************************************/
static int PP_shell_setEcallResp(int argc, const char **argv)
{
	unsigned int EcallResp;
    if (argc != 1)
    {
        shellprintf(" usage: HOZON_PP_SetecallResponse <ecall resp>\r\n");
        return -1;
    }

	sscanf(argv[0], "%u", &EcallResp);
	log_o(LOG_HOZON, "EcallReq = %d",EcallResp);
	//PP_xcall_SetEcallResp((uint8_t)EcallResp);
	PrvtPro_SetcallCCReq((uint8_t)EcallResp);
    sleep(1);
    return 0;
}


/******************************************************
*��������PP_shell_SetRmtCfgReq

*��  �Σ�����


*����ֵ��void

*��  ����

*��  ע��
******************************************************/
static int PP_shell_SetRmtCfgReq(int argc, const char **argv)
{
	unsigned int rmtCfgReq;
    if (argc != 1)
    {
        shellprintf(" usage: HOZON_PP_SetRemoteCfgReq <remote config req>\r\n");
        return -1;
    }

	sscanf(argv[0], "%u", &rmtCfgReq);
	PP_rmtCfg_SetCfgReq((uint8_t)rmtCfgReq);
    sleep(1);
    return 0;
}

/******************************************************
*��������PP_shell_SetRmtCtrlReq

*��  �Σ�����


*����ֵ��void

*��  ����

*��  ע��
******************************************************/
static int PP_shell_SetRmtCtrlReq(int argc, const char **argv)
{
	unsigned int rmtCtrlReq;
	unsigned int rmtCtrlReqtype;
    if (argc != 2)
    {
        shellprintf(" usage: HOZON_PP_SetRemoteCtrlReq <remote ctrl req>\r\n");
        return -1;
    }

	sscanf(argv[0], "%u", &rmtCtrlReq);
	sscanf(argv[1], "%u", &rmtCtrlReqtype);

	PP_rmtCtrl_SetCtrlReq((uint8_t)rmtCtrlReq,rmtCtrlReqtype);
    sleep(1);
    return 0;
}

/******************************************************
*��������PP_shell_SetRmtVSReq

*��  �Σ�����


*����ֵ��void

*��  ����

*��  ע��
******************************************************/
static int PP_shell_SetRmtVSReq(int argc, const char **argv)
{
	unsigned int rmtVSReq;
    if (argc != 1)
    {
        shellprintf(" usage: HOZON_PP_SetRemoteVSReq <remote check VS req>\r\n");
        return -1;
    }

	sscanf(argv[0], "%u", &rmtVSReq);

	PP_VS_SetVSReq((uint8_t)rmtVSReq);
    sleep(1);
    return 0;
}

/******************************************************
*��������PP_shell_SetTboxid

*��  �Σ�����


*����ֵ��void

*��  ����

*��  ע��
******************************************************/
static int PP_shell_SetTboxid(int argc, const char **argv)
{
	uint32_t tboxid;
    if (argc != 1)
    {
        shellprintf(" usage: HOZON_PP_SetTboxid <set tboxid>\r\n");
        return -1;
    }

	sscanf(argv[0], "%d", &tboxid);

	PrvtPro_SettboxId(tboxid);
    sleep(1);
    return 0;
}

/******************************************************
*��������PP_shell_SetTmcuSw

*��  �Σ�����


*����ֵ��void

*��  ����

*��  ע��
******************************************************/
static int PP_shell_SetTmcuSw(int argc, const char **argv)
{
    if (argc != 1)
    {
        shellprintf(" usage: HOZON_PP_SetmcuSw <set mcuSw>\r\n");
        return -1;
    }

    PP_rmtCfg_SetmcuSw(argv[0]);
    sleep(1);
    return 0;
}

/******************************************************
*��������PP_shell_SetTmpuSw

*��  �Σ�����


*����ֵ��void

*��  ����

*��  ע��
******************************************************/
static int PP_shell_SetTmpuSw(int argc, const char **argv)
{
    if (argc != 1)
    {
        shellprintf(" usage: HOZON_PP_SetmpuSw <set mpuSw>\r\n");
        return -1;
    }

    PP_rmtCfg_SetmpuSw(argv[0]);
    sleep(1);
    return 0;
}

/******************************************************
*��������PP_shell_Seticcid

*��  �Σ�����


*����ֵ��void

*��  ����

*��  ע��
******************************************************/
static int PP_shell_Seticcid(int argc, const char **argv)
{
    if (argc != 1)
    {
        shellprintf(" usage: HOZON_PP_Seticcid <set iccid>\r\n");
        return -1;
    }

    PP_rmtCfg_Seticcid(argv[0]);
    sleep(1);
    return 0;
}

/******************************************************
*��������PP_shell_showremoteCfg

*��  �Σ�����


*����ֵ��void

*��  ����

*��  ע��
******************************************************/
static int PP_shell_showpara(int argc, const char **argv)
{
	PrvtPro_ShowPara();
    sleep(1);
    return 0;
}