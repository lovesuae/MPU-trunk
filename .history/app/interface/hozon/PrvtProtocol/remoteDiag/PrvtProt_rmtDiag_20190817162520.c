/******************************************************
鏂囦欢鍚嶏細	PrvtProt_rmtDiag.c

鎻忚堪锛�	浼佷笟绉佹湁鍗忚锛堟禉姹熷悎浼楋級

Data			Vasion			author

2018/1/10		V1.0			liujian
*******************************************************/

/*******************************************************

description锛� include the header file

*******************************************************/
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include  <errno.h>
#include <sys/times.h>
#include <sys/time.h>
#include "timer.h"
#include <sys/prctl.h>
#include <sys/types.h>
#include <sysexits.h>	/* for EX_* exit codes */
#include <assert.h>	/* for assert(3) */
#include "constr_TYPE.h"
#include "asn_codecs.h"
#include "asn_application.h"
#include "asn_internal.h"	/* for _ASN_DEFAULT_STACK_MAX */
#include "XcallReqinfo.h"
#include "Bodyinfo.h"
#include "per_encoder.h"
#include "per_decoder.h"
#include "dev_api.h"
#include "init.h"
#include "log.h"
#include "list.h"
#include "../../sockproxy/sockproxy_txdata.h"
#include "../../../support/protocol.h"
#include "cfg_api.h"
#include "gb32960_api.h"
#include "hozon_PP_api.h"
#include "hozon_SP_api.h"
#include "shell_api.h"
#include "../PrvtProt_shell.h"
#include "../PrvtProt_queue.h"
#include "../PrvtProt_EcDc.h"
#include "../PrvtProt_cfg.h"
#include "../PrvtProt.h"
#include "tbox_ivi_api.h"

#include "PP_rmtDiag_cfg.h"

#include "PrvtProt_rmtDiag.h"

/*******************************************************
description锛� global variable definitions
*******************************************************/


/*******************************************************
description锛� static variable definitions
*******************************************************/
typedef struct
{
	PrvtProt_pack_Header_t	Header;
	PrvtProt_DisptrBody_t	DisBody;
}__attribute__((packed))  PrvtProt_rmtDiag_pack_t; /**/

typedef struct
{
	PrvtProt_rmtDiag_pack_t 	pack;
	PrvtProt_rmtDiagSt_t	 	state;
}__attribute__((packed))  PrvtProt_rmtDiag_t; /*缁撴瀯浣�*/


static PrvtProt_pack_t 			PP_rmtDiag_Pack;
static PrvtProt_rmtDiag_t		PP_rmtDiag;
static PP_App_rmtDiag_t 		AppData_rmtDiag;

static PP_rmtDiag_Fault_t		PP_rmtDiag_Fault;
typedef struct
{
	PP_rmtDiag_Fault_t	 		code[PP_DIAG_MAXECU];
	uint8_t 					currdiagtype;//当前诊断类型
	uint8_t 					rptfaultcnt[PP_DIAG_MAXECU];//当前诊断的ecu上报的故障码计数
	uint8_t						totalfaultCnt;
}__attribute__((packed))  PP_rmtDiag_allFault_t;
static PP_rmtDiag_allFault_t	PP_rmtDiag_allFault;

//static PrvtProt_TxInform_t 		diag_TxInform[PP_RMTDIAG_MAX_RESP];
static PP_rmtDiag_datetime_t 	rmtDiag_datetime;
static PP_rmtDiag_weekmask_t rmtDiag_weekmask[7] =
{
	{0,0x80},//星期天
	{1,0x40},//星期1
	{2,0x20},//星期2
	{3,0x10},//星期3
	{4,0x08},//星期4
	{5,0x04},//星期5
	{6,0x02},//星期6
};
/*******************************************************
description锛� function declaration
*******************************************************/
/*Global function declaration*/


/*Static function declaration*/
static int PP_rmtDiag_do_checksock(PrvtProt_task_t *task);
static int PP_rmtDiag_do_rcvMsg(PrvtProt_task_t *task);
static void PP_rmtDiag_RxMsgHandle(PrvtProt_task_t *task,PrvtProt_pack_t* rxPack,int len);
static int PP_rmtDiag_do_wait(PrvtProt_task_t *task);
static int PP_rmtDiag_do_checkrmtDiag(PrvtProt_task_t *task);
static int PP_rmtDiag_do_checkrmtImageReq(PrvtProt_task_t *task);
static int PP_rmtDiag_do_checkrmtLogReq(PrvtProt_task_t *task);

static int PP_rmtDiag_DiagResponse(PrvtProt_task_t *task,PrvtProt_rmtDiag_t *rmtDiag,PP_rmtDiag_Fault_t *rmtDiag_Fault);
static int PP_remotDiagnosticStatus(PrvtProt_task_t *task,PrvtProt_rmtDiag_t *rmtDiag);
static int PP_rmtDiag_do_DiagActiveReport(PrvtProt_task_t *task);
//static int PP_remotImageAcquisitionReq(PrvtProt_task_t *task,PrvtProt_rmtDiag_t *rmtDiag);
static void PP_rmtDiag_send_cb(void * para);
/******************************************************
description锛� function code
******************************************************/

/******************************************************
*鍑芥暟鍚嶏細PP_rmtDiag_init

*褰�  鍙傦細void

*杩斿洖鍊硷細void

*鎻�  杩帮細鍒濆鍖�

*澶�  娉細
******************************************************/
void PP_rmtDiag_init(void)
{
	unsigned int cfglen;
	memset(&PP_rmtDiag,0 , sizeof(PrvtProt_rmtDiag_t));
	memset(&AppData_rmtDiag,0 , sizeof(PP_App_rmtDiag_t));
	memset(&PP_rmtDiag_Fault,0 , sizeof(PP_rmtDiag_Fault_t));

	PP_rmtDiag.state.diagrespSt = PP_DIAGRESP_IDLE;
	PP_rmtDiag.state.ImageAcqRespSt = PP_IMAGEACQRESP_IDLE;
	PP_rmtDiag.state.activeDiagSt = PP_ACTIVEDIAG_PWRON;
	PP_rmtDiag.state.LogAcqRespSt = PP_LOGACQRESP_IDLE;

	cfglen = 4;
	cfg_get_para(CFG_ITEM_HOZON_TSP_DIAGDATE,&rmtDiag_datetime.datetime,&cfglen);//读取诊断日期标志
	cfglen = 1;
	cfg_get_para(CFG_ITEM_HOZON_TSP_DIAGFLAG,&rmtDiag_datetime.diagflag,&cfglen);//读取诊断日期标志
}



/******************************************************
*鍑芥暟鍚嶏細PP_rmtDiag_mainfunction

*褰�  鍙傦細void

*杩斿洖鍊硷細void

*鎻�  杩帮細涓讳换鍔″嚱鏁�

*澶�  娉細
******************************************************/
int PP_rmtDiag_mainfunction(void *task)
{
	int res;

	if(!dev_get_KL15_signal())
	{
		PP_rmtDiag.state.diagrespSt = PP_DIAGRESP_IDLE;
		PP_rmtDiag.state.ImageAcqRespSt = PP_IMAGEACQRESP_IDLE;
		PP_rmtDiag.state.activeDiagSt = PP_ACTIVEDIAG_PWRON;
		PP_rmtDiag.state.LogAcqRespSt = PP_LOGACQRESP_IDLE;
		PP_rmtDiag.state.diagReq = 0;
		PP_rmtDiag.state.ImageAcquisitionReq = 0;
		PP_rmtDiag.state.LogAcquisitionReq = 0;
		return 0;
	}

	res = 		PP_rmtDiag_do_checksock((PrvtProt_task_t*)task) ||
				PP_rmtDiag_do_rcvMsg((PrvtProt_task_t*)task) 	||
				PP_rmtDiag_do_wait((PrvtProt_task_t*)task) 		||
				PP_rmtDiag_do_checkrmtDiag((PrvtProt_task_t*)task) ||
				PP_rmtDiag_do_checkrmtImageReq((PrvtProt_task_t*)task) ||
				PP_rmtDiag_do_checkrmtLogReq((PrvtProt_task_t*)task);

	if(1 == sockproxy_socketState())//socket open
	{
		PP_rmtDiag_do_DiagActiveReport((PrvtProt_task_t*)task);//主动诊断上报
	}

	return res;
}

/******************************************************
*鍑芥暟鍚嶏細PP_rmtDiag_do_checksock

*褰�  鍙傦細void

*杩斿洖鍊硷細void

*鎻�  杩帮細妫�鏌ocket杩炴帴

*澶�  娉細
******************************************************/
static int PP_rmtDiag_do_checksock(PrvtProt_task_t *task)
{
	if(1 == sockproxy_socketState())//socket open
	{
		return 0;
	}

	return -1;
}



/******************************************************
*鍑芥暟鍚嶏細PP_rmtDiag_do_rcvMsg

*褰�  鍙傦細void

*杩斿洖鍊硷細void

*鎻�  杩帮細鎺ユ敹鏁版嵁鍑芥暟

*澶�  娉細
******************************************************/
static int PP_rmtDiag_do_rcvMsg(PrvtProt_task_t *task)
{
	int rlen = 0;
	PrvtProt_pack_t rcv_pack;

	memset(&rcv_pack,0 , sizeof(PrvtProt_pack_t));
	if ((rlen = RdPP_queue(PP_REMOTE_DIAG,rcv_pack.Header.sign,sizeof(PrvtProt_pack_t))) <= 0)
    {
		return 0;
	}

	log_i(LOG_HOZON, "receive diag message");
	protocol_dump(LOG_HOZON, "PRVT_PROT", rcv_pack.Header.sign, rlen, 0);
	if((rcv_pack.Header.sign[0] != 0x2A) || (rcv_pack.Header.sign[1] != 0x2A) || \
			(rlen <= 18))//鍒ゆ柇鏁版嵁甯уご鏈夎鎴栬�呮暟鎹暱搴︿笉瀵�
	{
		return 0;
	}

	if(rlen > (18 + PP_MSG_DATA_LEN))//鎺ユ敹鏁版嵁闀垮害瓒呭嚭缂撳瓨buffer闀垮害
	{
		return 0;
	}

	PP_rmtDiag_RxMsgHandle(task,&rcv_pack,rlen);

	return 0;
}


/******************************************************
*鍑芥暟鍚嶏細PP_rmtDiag_RxMsgHandle

*褰�  鍙傦細void

*杩斿洖鍊硷細void

*鎻�  杩帮細鎺ユ敹鏁版嵁澶勭悊

*澶�  娉細
******************************************************/
static void PP_rmtDiag_RxMsgHandle(PrvtProt_task_t *task,PrvtProt_pack_t* rxPack,int len)
{
	int aid;

	if(PP_OPERATETYPE_NGTP != rxPack->Header.opera)
	{
		log_e(LOG_HOZON, "unknow package");
		return;
	}

	PrvtProt_DisptrBody_t MsgDataBody;
	PP_App_rmtDiag_t Appdata;
	PrvtPro_decodeMsgData(rxPack->msgdata,(len - 18),&MsgDataBody,&Appdata);
	aid = (MsgDataBody.aID[0] - 0x30)*100 +  (MsgDataBody.aID[1] - 0x30)*10 + \
			  (MsgDataBody.aID[2] - 0x30);
	if(PP_AID_DIAG != aid)
	{
		log_e(LOG_HOZON, "aid unmatch\n");
		return;
	}

	switch(MsgDataBody.mID)
	{
		case PP_MID_DIAG_REQ://
		{
			if((0 == PP_rmtDiag.state.diagReq) && (PP_DIAGRESP_IDLE == PP_rmtDiag.state.diagrespSt))
			{
				log_i(LOG_HOZON, "receive remote diag request\n");
				PP_rmtDiag.state.diagReq 	 = 1;
				PP_rmtDiag.state.diagType 	 = Appdata.DiagnosticReq.diagType;
				PP_rmtDiag.state.diageventId = MsgDataBody.eventId;
				PP_rmtDiag.state.diagexpTime = MsgDataBody.expTime;
			}
			else
			{
				log_e(LOG_HOZON, "repeat diag request\n");
			}
		}
		break;
		case PP_MID_DIAG_IMAGEACQREQ://
		{
			if(PP_IMAGEACQRESP_IDLE == PP_rmtDiag.state.ImageAcqRespSt)
			{
				log_i(LOG_HOZON, "receive remote ImageAcquisition request\n");
				PP_rmtDiag.state.ImageAcquisitionReq = 1;
				PP_rmtDiag.state.dataType    = Appdata.ImageAcquisitionReq.dataType;
				PP_rmtDiag.state.cameraName  =  Appdata.ImageAcquisitionReq.cameraName;
				PP_rmtDiag.state.effectiveTime = Appdata.ImageAcquisitionReq.effectiveTime;
				PP_rmtDiag.state.sizeLimit   =  Appdata.ImageAcquisitionReq.sizeLimit;
				PP_rmtDiag.state.imagereqeventId = MsgDataBody.eventId;
			}
			else
			{
				log_e(LOG_HOZON, "repeat ImageAcq request\n");
			}
		}
		break;
		case PP_MID_DIAG_LOGACQRESP://tsp请求 log
		{
			if(PP_LOGACQRESP_IDLE == PP_rmtDiag.state.LogAcqRespSt)
			{
				log_i(LOG_HOZON, "receive remote LogAcquisition request\n");
				PP_rmtDiag.state.LogAcquisitionReq = 1;
				PP_rmtDiag.state.logType    	=  Appdata.LogAcquisitionResp.logType;
				PP_rmtDiag.state.logLevel  		=  Appdata.LogAcquisitionResp.logLevel;
				PP_rmtDiag.state.startTime 		=  Appdata.LogAcquisitionResp.startTime;
				PP_rmtDiag.state.durationTime   =  Appdata.LogAcquisitionResp.durationTime;
				PP_rmtDiag.state.logeventId 	=  MsgDataBody.eventId;
			}
			else
			{
				log_e(LOG_HOZON, "repeat logAcq request\n");
			}
		}
		break;
		default:
		break;
	}
}

/******************************************************
*鍑芥暟鍚嶏細PP_rmtDiag_do_wait

*褰�  鍙傦細void

*杩斿洖鍊硷細void

*鎻�  杩帮細妫�鏌ユ槸鍚︽湁浜嬩欢绛夊緟搴旂瓟

*澶�  娉細
******************************************************/
static int PP_rmtDiag_do_wait(PrvtProt_task_t *task)
{
	return 0;
}


/******************************************************
*鍑芥暟鍚嶏細PP_rmtDiag_do_checkrmtDiag

*褰�  鍙傦細

*杩斿洖鍊硷細

*鎻�  杩帮細

*澶�  娉細
******************************************************/
static int PP_rmtDiag_do_checkrmtDiag(PrvtProt_task_t *task)
{
	int ret = 0;
	int idlenode;
	switch(PP_rmtDiag.state.diagrespSt)
	{
		case PP_DIAGRESP_IDLE:
		{
			if(1 == PP_rmtDiag.state.diagReq)//杩滅▼璇婃柇璇锋眰
			{
				log_i(LOG_HOZON, "start remote diag\n");
				PP_rmtDiag.state.diagrespSt = PP_DIAGRESP_QUERYFAILREQ;
				PP_rmtDiag.state.diagReq = 0;
			}
		}
		break;
		case PP_DIAGRESP_QUERYFAILREQ:
		{
			PP_rmtDiag.state.faultquerySt = 0;
			log_i(LOG_HOZON, "diagType = %d\n",PP_rmtDiag.state.diagType);
			setPPrmtDiagCfg_QueryFaultReq(PP_rmtDiag.state.diagType);
			memset(&PP_rmtDiag_Fault,0 , sizeof(PP_rmtDiag_Fault_t));
			PP_rmtDiag.state.waittime = tm_get_time();
			PP_rmtDiag.state.diagrespSt = PP_DIAGRESP_QUERYWAIT;
		}
		break;
		case PP_DIAGRESP_QUERYWAIT:
		{
			if((tm_get_time() - PP_rmtDiag.state.waittime) <= PP_DIAGQUERY_WAITTIME)
			{
				if(1 == PP_rmtDiag.state.faultquerySt)//查询完成
				{
					getPPrmtDiagCfg_Faultcode(PP_rmtDiag.state.diagType,&PP_rmtDiag_Fault);//读取故障码
					log_i(LOG_HOZON, "PP_rmtDiag.state.diagType = %d and PP_rmtDiag_Fault.failNum = %d\n",PP_rmtDiag.state.diagType,PP_rmtDiag_Fault.faultNum);
					PP_rmtDiag.state.result = PP_rmtDiag_Fault.sueecss;
					PP_rmtDiag.state.failureType = PP_RMTDIAG_ERROR_NONE;
					PP_rmtDiag.state.diagrespSt = PP_DIAGRESP_QUERYUPLOAD;
				}
			}
			else//超时
			{
				PP_rmtDiag.state.result = 0;
				PP_rmtDiag.state.failureType = PP_RMTDIAG_ERROR_NONE;
				PP_rmtDiag.state.diagrespSt = PP_DIAGRESP_QUERYUPLOAD;
			}
		}
		break;
		case PP_DIAGRESP_QUERYUPLOAD:
		{
			ret = PP_rmtDiag_DiagResponse(task,&PP_rmtDiag,&PP_rmtDiag_Fault);
			if(ret >= 0)
			{
				idlenode = PP_getIdleNode();
				memset(&PP_TxInform[idlenode],0,sizeof(PrvtProt_TxInform_t));
				PP_TxInform[idlenode].aid = PP_AID_DIAG;
				PP_TxInform[idlenode].mid = PP_MID_DIAG_RESP;
				PP_TxInform[idlenode].pakgtype = PP_TXPAKG_SIGTIME;
				PP_TxInform[idlenode].eventtime = tm_get_time();
				SP_data_write(PP_rmtDiag_Pack.Header.sign, \
						PP_rmtDiag_Pack.totallen,PP_rmtDiag_send_cb,&PP_TxInform[idlenode]);
				protocol_dump(LOG_HOZON, "diag_req_response", PP_rmtDiag_Pack.Header.sign,PP_rmtDiag_Pack.totallen,1);

				if(1 == ret)//上报完成
				{
					log_i(LOG_HOZON, "fault report finish\n");
					PP_rmtDiag.state.diagrespSt = PP_DIAGRESP_END;
				}
			}
			else
			{
				PP_rmtDiag.state.diagrespSt = PP_DIAGRESP_END;
			}
		}
		break;
		case PP_DIAGRESP_END:
		{
			PP_rmtDiag.state.diagrespSt = PP_DIAGRESP_IDLE;
		}
		break;
		default:
		break;
	}

	return 0;
}

/******************************************************
*鍑芥暟鍚嶏細:PP_rmtDiag_do_checkrmtImageReq

*褰�  鍙傦細

*杩斿洖鍊硷細

*鎻�  杩帮細

*澶�  娉細
******************************************************/
static int PP_rmtDiag_do_checkrmtImageReq(PrvtProt_task_t *task)
{
	switch(PP_rmtDiag.state.ImageAcqRespSt)
	{
		case PP_IMAGEACQRESP_IDLE:
		{
			if(1 == PP_rmtDiag.state.ImageAcquisitionReq)
			{
				log_i(LOG_HOZON, "start remote ImageAcquisition\n");
				PP_rmtDiag.state.ImageAcquisitionReq = 0;
				PP_rmtDiag.state.ImageAcqRespSt = PP_IMAGEACQRESP_INFORM_HU;
			}
		}
		break;
		case PP_IMAGEACQRESP_INFORM_HU://閫氱煡HU
		{
			ivi_remotediagnos tspInformHU;
			tspInformHU.aid = PP_AID_DIAG;
			tspInformHU.mid = PP_MID_DIAG_IMAGEACQREQ;
			tspInformHU.eventid = PP_rmtDiag.state.imagereqeventId;
			tspInformHU.datatype = PP_rmtDiag.state.dataType;
			tspInformHU.cameraname = PP_rmtDiag.state.cameraName;
			tspInformHU.effectivetime = PP_rmtDiag.state.effectiveTime;
			tspInformHU.sizelimit = PP_rmtDiag.state.sizeLimit;
			tbox_ivi_set_tspInformHU(&tspInformHU);
			PP_rmtDiag.state.ImageAcqRespSt = PP_IMAGEACQRESP_IDLE;
		}
		break;
		default:
		break;
	}

	return 0;
}

/******************************************************
*鍑芥暟鍚嶏細:PP_rmtDiag_do_checkrmtLogReq

*褰�  鍙傦細

*杩斿洖鍊硷細

*鎻�  杩帮細

*澶�  娉細
******************************************************/
static int PP_rmtDiag_do_checkrmtLogReq(PrvtProt_task_t *task)
{
	switch(PP_rmtDiag.state.LogAcqRespSt)
	{
		case PP_LOGACQRESP_IDLE:
		{
			if(1 == PP_rmtDiag.state.LogAcquisitionReq)
			{
				log_i(LOG_HOZON, "start remote LogAcquisition\n");
				PP_rmtDiag.state.LogAcquisitionReq = 0;
				PP_rmtDiag.state.LogAcqRespSt = PP_LOGACQRESP_INFORM_UPLOADLOG;
			}
		}
		break;
		case PP_LOGACQRESP_INFORM_UPLOADLOG://通知上传log
		{
			if(PP_LOG_TBOX == PP_rmtDiag.state.logType)
			{//tbox上传log

			}
			else if(PP_LOG_HU == PP_rmtDiag.state.logType)
			{//通知HU 上传log
				log_i(LOG_HOZON, "inform HU upload log\n");
				ivi_logfile appointchargeSt;
				appointchargeSt.aid = PP_AID_DIAG;
				appointchargeSt.mid = PP_MID_DIAG_LOGACQRESP;
				appointchargeSt.eventid = PP_rmtDiag.state.logeventId;
				appointchargeSt.timestamp = PrvtPro_getTimestamp();
				appointchargeSt.level = PP_rmtDiag.state.logLevel;
				appointchargeSt.starttime = PP_rmtDiag.state.startTime;
				appointchargeSt.durationtime = PP_rmtDiag.state.durationTime;
				tbox_ivi_set_tsplogfile_InformHU(&appointchargeSt);
			}
			else
			{}

			PP_rmtDiag.state.LogAcqRespSt = PP_LOGACQRESP_IDLE;
		}
		break;
		default:
		break;
	}

	return 0;
}


/******************************************************
*鍑芥暟鍚嶏細:PP_rmtDiag_do_DiagActiveReport

*褰�  鍙傦細

*杩斿洖鍊硷細

*鎻�  杩帮細

*澶�  娉細:每天仅成功上报1次
******************************************************/
static int PP_rmtDiag_do_DiagActiveReport(PrvtProt_task_t *task)
{
	static uint8_t tm_wday;
	static uint32_t tm_datetime;
	int i;
	int ret;
	int idlenode;

	switch(PP_rmtDiag.state.activeDiagSt)
	{
		case PP_ACTIVEDIAG_PWRON:
		{
			PP_rmtDiag.state.activeDiagSt = PP_ACTIVEDIAG_CHECKREPORTST;
			PP_rmtDiag.state.activeDiagdelaytime = tm_get_time();
		}
		break;
		case PP_ACTIVEDIAG_CHECKREPORTST:
		{
			char *wday[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
			time_t timep;
			struct tm *localdatetime;

			time(&timep);
			localdatetime = localtime(&timep);//取得当地时间
			log_i(LOG_HOZON,"%d-%d-%d ",(1900+localdatetime->tm_year), \
					(1 +localdatetime->tm_mon), localdatetime->tm_mday);
			log_i(LOG_HOZON,"%s %d:%d:%d\n", wday[localdatetime->tm_wday], \
					localdatetime->tm_hour, localdatetime->tm_min, localdatetime->tm_sec);
			tm_wday = localdatetime->tm_wday;
			tm_datetime = (1900+localdatetime->tm_year) * 10000 + (1 +localdatetime->tm_mon) * 100 + localdatetime->tm_mday;
			if((rmtDiag_datetime.diagflag & rmtDiag_weekmask[tm_wday].mask) && \
					(rmtDiag_datetime.datetime == tm_datetime))
			{//已上传过故障码
				PP_rmtDiag.state.activeDiagSt = PP_ACTIVEDIAG_END;
				log_i(LOG_HOZON,"The fault code has been uploaded today\n");
				log_i(LOG_HOZON,"uploaded date : %d\n",rmtDiag_datetime.datetime);
			}
			else
			{
				log_i(LOG_HOZON,"start to daig report\n");
				PP_rmtDiag.state.activeDiagSt = PP_ACTIVEDIAG_CHECKVEHICOND;
			}
		}
		break;
		case PP_ACTIVEDIAG_CHECKVEHICOND:
		{
			if((tm_get_time() - PP_rmtDiag.state.activeDiagdelaytime) >= PP_DIAGPWRON_WAITTIME)//延时5s
			{
				if(gb_data_vehicleSpeed() <= 50)//判断车速<=5km/h,满足诊断条件
				{
					log_i(LOG_HOZON,"vehicle speed <= 5km/h,start diag\n");
					PP_rmtDiag.state.faultquerySt = 0;
					setPPrmtDiagCfg_QueryFaultReq(PP_DIAG_ALL);//请求查询所有故障码
					memset(&PP_rmtDiag_allFault,0 , sizeof(PP_rmtDiag_allFault_t));
					PP_rmtDiag.state.activeDiagdelaytime = tm_get_time();
					PP_rmtDiag.state.activeDiagSt = PP_ACTIVEDIAG_QUREYWAIT;
				}
				else
				{
					log_e(LOG_HOZON,"vehicle speed > 5km/h,exit acyive diag\n");
					PP_rmtDiag.state.activeDiagSt = PP_ACTIVEDIAG_END;
				}
			}
		}
		break;
		case PP_ACTIVEDIAG_QUREYWAIT:
		{
			if((tm_get_time() - PP_rmtDiag.state.activeDiagdelaytime) <= PP_DIAGQUERYALL_WAITTIME)//
			{
				if(1 == PP_rmtDiag.state.faultquerySt)//查询完成
				{
					for(i=1;i <= PP_DIAG_MAXECU;i++)
					{
						getPPrmtDiagCfg_Faultcode(i,&PP_rmtDiag_allFault.code[i-1]);//读取故障码
						log_i(LOG_HOZON, "PP_rmtDiag_allFault.code[%d].sueecss = %d\n",i-1,PP_rmtDiag_allFault.code[i-1].sueecss);
						log_i(LOG_HOZON, "PP_rmtDiag_allFault.code[%d].faultNum = %d\n",i-1,PP_rmtDiag_allFault.code[i-1].faultNum);
					}
					PP_rmtDiag_allFault.currdiagtype = PP_DIAG_VCU;
					PP_rmtDiag.state.result = 1;
					PP_rmtDiag.state.failureType = PP_RMTDIAG_ERROR_NONE;
					PP_rmtDiag.state.activeDiagdelaytime = tm_get_time();
					PP_rmtDiag.state.activeDiagSt = PP_ACTIVEDIAG_QUERYUPLOAD;
				}
			}
			else//超时
			{
				log_e(LOG_HOZON, "diag active report is timeout\n");
				PP_rmtDiag.state.result = 0;
				PP_rmtDiag.state.failureType  = PP_RMTDIAG_ERROR_NONE;
				PP_rmtDiag.state.activeDiagdelaytime = tm_get_time();
				PP_rmtDiag.state.activeDiagSt = PP_ACTIVEDIAG_QUERYUPLOAD;
			}
		}
		break;
		case PP_ACTIVEDIAG_QUERYUPLOAD:
		{
			if((tm_get_time() - PP_rmtDiag.state.activeDiagdelaytime) <	50)//延时50ms
			{
				return 0;
			}

			ret = PP_remotDiagnosticStatus(task,&PP_rmtDiag);
			if(ret >= 0)
			{
				PP_rmtDiag.state.activeDiagdelaytime = tm_get_time();
				idlenode = PP_getIdleNode();
				memset(&PP_TxInform[idlenode],0,sizeof(PrvtProt_TxInform_t));
				PP_TxInform[idlenode].aid = PP_AID_DIAG;
				PP_TxInform[idlenode].mid = PP_MID_DIAG_STATUS;
				PP_TxInform[idlenode].pakgtype = PP_TXPAKG_SIGTIME;
				PP_TxInform[idlenode].eventtime = tm_get_time();
				SP_data_write(PP_rmtDiag_Pack.Header.sign,PP_rmtDiag_Pack.totallen, \
						PP_rmtDiag_send_cb,&PP_TxInform[idlenode]);
				protocol_dump(LOG_HOZON, "diag_status_response", PP_rmtDiag_Pack.Header.sign,PP_rmtDiag_Pack.totallen,1);

				if(ret ==1)//all数据打包发送完成
				{
					if(1 == PP_rmtDiag.state.result)//诊断成功
					{
						rmtDiag_datetime.diagflag = rmtDiag_weekmask[tm_wday].mask;
						if(cfg_set_para(CFG_ITEM_HOZON_TSP_DIAGFLAG, &rmtDiag_datetime.diagflag, 1))
						{
							log_e(LOG_GB32960, "save rmtDiag_datetime.diagflag failed\n");
						}

						rmtDiag_datetime.datetime = tm_datetime;
						if(cfg_set_para(CFG_ITEM_HOZON_TSP_DIAGDATE, &rmtDiag_datetime.datetime, 4))
						{
							log_e(LOG_GB32960, "save rmtDiag_datetime.datetime failed\n");
						}
					}
					PP_rmtDiag.state.activeDiagSt = PP_ACTIVEDIAG_END;
				}
			}
			else
			{
				PP_rmtDiag.state.activeDiagSt = PP_ACTIVEDIAG_END;
			}
		}
		break;
		case PP_ACTIVEDIAG_END:
		{

		}
		break;
		default:
		break;
	}

	return 0;
}
/******************************************************
*鍑芥暟鍚嶏細PP_rmtDiag_DiagResponse

*褰�  鍙傦細

*杩斿洖鍊硷細

*鎻�  杩帮細diag response

*澶�  娉細
******************************************************/
static int PP_rmtDiag_DiagResponse(PrvtProt_task_t *task,PrvtProt_rmtDiag_t *rmtDiag,PP_rmtDiag_Fault_t *rmtDiag_Fault)
{
	int msgdatalen;
	int i;
	int ret = 0;
	static uint8_t faultUpdataCnt = 0;

	memset(&PP_rmtDiag_Pack,0 , sizeof(PrvtProt_pack_t));
	/* header */
	memcpy(PP_rmtDiag.pack.Header.sign,"**",2);
	PP_rmtDiag.pack.Header.commtype.Byte = 0xe1;
	PP_rmtDiag.pack.Header.ver.Byte = 0x30;
	PP_rmtDiag.pack.Header.opera = 0x02;
	PP_rmtDiag.pack.Header.ver.Byte = task->version;
	PP_rmtDiag.pack.Header.nonce  = PrvtPro_BSEndianReverse((uint32_t)task->nonce);
	PP_rmtDiag.pack.Header.tboxid = PrvtPro_BSEndianReverse((uint32_t)task->tboxid);
	memcpy(&PP_rmtDiag_Pack, &PP_rmtDiag.pack.Header, sizeof(PrvtProt_pack_Header_t));

	/* disbody */
	memcpy(PP_rmtDiag.pack.DisBody.aID,"140",3);
	PP_rmtDiag.pack.DisBody.mID = PP_MID_DIAG_RESP;
	PP_rmtDiag.pack.DisBody.eventTime = PrvtPro_getTimestamp();
	PP_rmtDiag.pack.DisBody.eventId = rmtDiag->state.diageventId;
	PP_rmtDiag.pack.DisBody.expTime = rmtDiag->state.diagexpTime;
	PP_rmtDiag.pack.DisBody.ulMsgCnt++;	/* OPTIONAL */
	PP_rmtDiag.pack.DisBody.appDataProVer = 256;
	PP_rmtDiag.pack.DisBody.testFlag = 1;

	/*appdata*/
	memset(&AppData_rmtDiag.DiagnosticResp,0,sizeof(PP_DiagnosticResp_t));
	AppData_rmtDiag.DiagnosticResp.diagType = rmtDiag->state.diagType;
	AppData_rmtDiag.DiagnosticResp.result = rmtDiag->state.result;
	AppData_rmtDiag.DiagnosticResp.failureType = rmtDiag->state.failureType;
	if((1 == AppData_rmtDiag.DiagnosticResp.result) && (rmtDiag_Fault->faultNum > 0))
	{
		for(i = 0;i < PP_DIAG_MAX_REPORT;i++)
		{
			memcpy(AppData_rmtDiag.DiagnosticResp.diagCode[i].diagCode,rmtDiag_Fault->faultcode[faultUpdataCnt].diagcode,5);
			AppData_rmtDiag.DiagnosticResp.diagCode[i].diagCodelen = 5;
			AppData_rmtDiag.DiagnosticResp.diagCode[i].faultCodeType  = rmtDiag_Fault->faultcode[faultUpdataCnt].faultCodeType;
			AppData_rmtDiag.DiagnosticResp.diagCode[i].lowByte = rmtDiag_Fault->faultcode[faultUpdataCnt].lowByte;
			AppData_rmtDiag.DiagnosticResp.diagCode[i].diagTime = rmtDiag_Fault->faultcode[faultUpdataCnt].diagTime;
			AppData_rmtDiag.DiagnosticResp.diagcodenum++;
			faultUpdataCnt++;

			if(faultUpdataCnt == rmtDiag_Fault->faultNum)
			{
				faultUpdataCnt = 0;
				ret = 1;
				break;
			}
		}
	}
	else
	{
		ret = 1;
		faultUpdataCnt = 0;
		AppData_rmtDiag.DiagnosticResp.diagcodenum = 0;
	}

	if(0 != PrvtPro_msgPackageEncoding(ECDC_RMTDIAG_RESP,PP_rmtDiag_Pack.msgdata,&msgdatalen,\
									   &PP_rmtDiag.pack.DisBody,&AppData_rmtDiag.DiagnosticResp))//鏁版嵁缂栫爜鎵撳寘鏄惁瀹屾垚
	{
		log_e(LOG_HOZON, "encode error\n");
		faultUpdataCnt = 0;
		return -1;
	}

	PP_rmtDiag_Pack.totallen = 18 + msgdatalen;
	PP_rmtDiag_Pack.Header.msglen = PrvtPro_BSEndianReverse((long)(18 + msgdatalen));

	return ret;
}

/******************************************************
*函数名：

*形  参：

*返回值：

*描  述：远程诊断( MID=3)

*备  注：
******************************************************/
static int PP_remotDiagnosticStatus(PrvtProt_task_t *task,PrvtProt_rmtDiag_t *rmtDiag)
{
	int msgdatalen;
	int ret = 0;

	memset(&PP_rmtDiag_Pack,0 , sizeof(PrvtProt_pack_t));
	/* header */
	memcpy(PP_rmtDiag.pack.Header.sign,"**",2);
	PP_rmtDiag.pack.Header.commtype.Byte = 0xe1;
	PP_rmtDiag.pack.Header.ver.Byte = 0x30;
	PP_rmtDiag.pack.Header.opera = 0x02;
	PP_rmtDiag.pack.Header.ver.Byte = task->version;
	PP_rmtDiag.pack.Header.nonce  = PrvtPro_BSEndianReverse((uint32_t)task->nonce);
	PP_rmtDiag.pack.Header.tboxid = PrvtPro_BSEndianReverse((uint32_t)task->tboxid);
	memcpy(&PP_rmtDiag_Pack, &PP_rmtDiag.pack.Header, sizeof(PrvtProt_pack_Header_t));

	/* disbody */
	memcpy(PP_rmtDiag.pack.DisBody.aID,"140",3);
	PP_rmtDiag.pack.DisBody.mID = PP_MID_DIAG_STATUS;
	PP_rmtDiag.pack.DisBody.eventTime = PrvtPro_getTimestamp();
	PP_rmtDiag.pack.DisBody.eventId = 0;//tsp未指定eventid，传0，已沟通
	PP_rmtDiag.pack.DisBody.expTime = PrvtPro_getTimestamp();
	PP_rmtDiag.pack.DisBody.ulMsgCnt++;	/* OPTIONAL */
	PP_rmtDiag.pack.DisBody.appDataProVer = 256;
	PP_rmtDiag.pack.DisBody.testFlag = 1;

	/*app data*/
	memset(&AppData_rmtDiag.DiagnosticSt,0,sizeof(PP_DiagnosticStatus_t));
	uint8_t index_i = 0;
	uint8_t index_j = 0;
	uint8_t diagType;
	for(diagType = PP_rmtDiag_allFault.currdiagtype;diagType <= PP_DIAG_MAXECU;diagType++)
	{
		AppData_rmtDiag.DiagnosticSt.diagobjnum++;
		AppData_rmtDiag.DiagnosticSt.diagStatus[index_i].diagType = diagType;//
		AppData_rmtDiag.DiagnosticSt.diagStatus[index_i].result = PP_rmtDiag_allFault.code[diagType-1].sueecss;
		AppData_rmtDiag.DiagnosticSt.diagStatus[index_i].failureType = PP_rmtDiag.state.failureType;
		if((1 == PP_rmtDiag.state.result) && (PP_rmtDiag_allFault.code[diagType-1].faultNum > 0))
		{
			for(index_j = 0;index_j < 255;index_j++)
			{
				memcpy(AppData_rmtDiag.DiagnosticSt.diagStatus[index_i].diagCode[index_j].diagCode, \
						PP_rmtDiag_allFault.code[diagType-1].faultcode[PP_rmtDiag_allFault.rptfaultcnt[diagType-1]].diagcode,5);
				AppData_rmtDiag.DiagnosticSt.diagStatus[index_i].diagCode[index_j].diagCodelen = 5;

				AppData_rmtDiag.DiagnosticSt.diagStatus[index_i].diagCode[index_j].faultCodeType = \
						PP_rmtDiag_allFault.code[diagType-1].faultcode[PP_rmtDiag_allFault.rptfaultcnt[diagType-1]].faultCodeType;

				AppData_rmtDiag.DiagnosticSt.diagStatus[index_i].diagCode[index_j].lowByte  = \
						PP_rmtDiag_allFault.code[diagType-1].faultcode[PP_rmtDiag_allFault.rptfaultcnt[diagType-1]].lowByte;

				AppData_rmtDiag.DiagnosticSt.diagStatus[index_i].diagCode[index_j].diagTime = \
						PP_rmtDiag_allFault.code[diagType-1].faultcode[PP_rmtDiag_allFault.rptfaultcnt[diagType-1]].diagTime;

				PP_rmtDiag_allFault.rptfaultcnt[diagType-1]++;
				PP_rmtDiag_allFault.totalfaultCnt++;
				AppData_rmtDiag.DiagnosticSt.diagStatus[index_i].diagcodenum++;
				if(PP_rmtDiag_allFault.totalfaultCnt < PP_DIAG_MAX_REPORT)
				{
					if(PP_rmtDiag_allFault.rptfaultcnt[diagType-1] == PP_rmtDiag_allFault.code[diagType-1].faultNum)
					{
						break;
					}
				}
				else
				{//数据量大时，分多次上报，当前待上报数据打包完
					PP_rmtDiag_allFault.totalfaultCnt = 0;
					//PP_rmtDiag_allFault.currdiagtype = diagType;
					if(PP_rmtDiag_allFault.rptfaultcnt[diagType-1] < PP_rmtDiag_allFault.code[diagType-1].faultNum)
					{
						PP_rmtDiag_allFault.currdiagtype = diagType;
					}
					else
					{
						PP_rmtDiag_allFault.currdiagtype = diagType + 1;
					}

					if(PP_rmtDiag_allFault.currdiagtype > PP_DIAG_MAXECU)
					{
						ret = 1;//all数据处理完
					}
					goto rmtDiagStDataPacking;
				}
			}
		}
		else
		{
			AppData_rmtDiag.DiagnosticSt.diagStatus[index_i].diagcodenum = 0;
		}

		index_i++;

		if(diagType >= PP_DIAG_MAXECU)//
		{
			ret = 1;//all数据处理完
			goto rmtDiagStDataPacking;
		}
	}


rmtDiagStDataPacking:
	{
		if(0 != PrvtPro_msgPackageEncoding(ECDC_RMTDIAG_STATUS,PP_rmtDiag_Pack.msgdata,&msgdatalen,\
										   &PP_rmtDiag.pack.DisBody,&AppData_rmtDiag.DiagnosticSt))//鏁版嵁缂栫爜鎵撳寘鏄惁瀹屾垚
		{
			log_e(LOG_HOZON, "encode error\n");
			return -1;
		}

		PP_rmtDiag_Pack.totallen = 18 + msgdatalen;
		PP_rmtDiag_Pack.Header.msglen = PrvtPro_BSEndianReverse((long)(18 + msgdatalen));
	}

	return ret;
}

/******************************************************
*鍑芥暟鍚嶏細PP_rmtDiag_send_cb

*褰�  鍙傦細

*杩斿洖鍊硷細

*鎻�  杩帮細remote diag status response

*澶�  娉細
******************************************************/
static void PP_rmtDiag_send_cb(void * para)
{
	PrvtProt_TxInform_t *TxInform_ptr =  (PrvtProt_TxInform_t*)para;

	switch(TxInform_ptr->mid)
	{
		case PP_MID_DIAG_RESP:
		{
			//PP_rmtDiag.state.diagReq = 0;
			log_i(LOG_HOZON, "send remote diag response ok\n");
		}
		break;
		case PP_MID_DIAG_STATUS:
		{
			if(PP_TXPAKG_SUCCESS != TxInform_ptr->successflg)
			{
				rmtDiag_datetime.diagflag = 0;
				if(cfg_set_para(CFG_ITEM_HOZON_TSP_DIAGFLAG, &rmtDiag_datetime.diagflag, 1))
				{
					log_e(LOG_GB32960, "save rmtDiag_datetime.diagflag failed\n");
				}

				rmtDiag_datetime.datetime = 0;
				if(cfg_set_para(CFG_ITEM_HOZON_TSP_DIAGDATE, &rmtDiag_datetime.datetime, 4))
				{
					log_e(LOG_GB32960, "save rmtDiag_datetime.datetime failed\n");
				}
			}
		}
		break;
		default:
		break;
	}
	TxInform_ptr->idleflag = 0;
}

/******************************************************
*鍑芥暟鍚嶏細PP_diag_SetdiagReq

*褰�  鍙傦細

*杩斿洖鍊硷細

*鎻�  杩帮細璁剧疆璇锋眰

*澶�  娉細
******************************************************/
void PP_diag_SetdiagReq(unsigned char diagType,unsigned char reqtype)
{
	if(0 == reqtype)
	{
		log_i(LOG_HOZON, "receive remote diag request\n");
		PP_rmtDiag.state.diagReq = 1;
		PP_rmtDiag.state.diagType = diagType;
		PP_rmtDiag.state.diageventId = 100;
		PP_rmtDiag.state.result = 1;
		PP_rmtDiag.state.failureType = 0;

	}
	else//主动上报所有故障码
	{
		log_i(LOG_HOZON, " diag fault code active report request\n");
		PP_rmtDiag.state.activeDiagSt = PP_ACTIVEDIAG_PWRON;
		rmtDiag_datetime.diagflag = 0;
		if(cfg_set_para(CFG_ITEM_HOZON_TSP_DIAGFLAG, &rmtDiag_datetime.diagflag, 1))
		{
			log_e(LOG_GB32960, "save rmtDiag_datetime.diagflag failed\n");
		}

		rmtDiag_datetime.datetime = 0;
		if(cfg_set_para(CFG_ITEM_HOZON_TSP_DIAGDATE, &rmtDiag_datetime.datetime, 4))
		{
			log_e(LOG_GB32960, "save rmtDiag_datetime.datetime failed\n");
		}
	}
}

/******************************************************
*鍑芥暟鍚嶏細PP_rmtDiag_queryInform_cb

*褰�  鍙傦細

*杩斿洖鍊硷細

*鎻�  杩帮細

*澶�  娉細
******************************************************/
void PP_rmtDiag_queryInform_cb(void)
{
	PP_rmtDiag.state.faultquerySt = 1;
}