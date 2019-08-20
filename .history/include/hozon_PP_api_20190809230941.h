#ifndef __HOZON_PP_API_H__
#define __HOZON_PP_API_H__

#define PP_RMTDIAG_FAILCODE_LEN 5

#define PP_CERTDL_CERTPATH			"/usrdata/pki/userAuth.cer"
#define PP_CERTDL_CERTPATH_UPDATE	"/usrdata/pki/update/userAuth.cer"
#define PP_CERTDL_CERTPATH_BKUP		"/usrdata/pki/bkup/userAuth.cer"

#define PP_CERTDL_TWOCERTKEYPATH			"/usrdata/pki/two_certreqmain.key"
#define PP_CERTDL_TWOCERTRKEYPATH_UPDATE	"/usrdata/pki/update/two_certreqmain.key"
#define PP_CERTDL_TWOCERTRKEYPATH_BKUP		"/usrdata/pki/bkup/two_certreqmain.key"

#define PP_CERTDL_TWOCERTCSRPATH			"/usrdata/pki/two_certreqmain.csr"
#define PP_CERTDL_TWOCERTRCSRPATH_UPDATE	"/usrdata/pki/update/two_certreqmain.csr"
#define PP_CERTDL_TWOCERTRCSRPATH_BKUP		"/usrdata/pki/bkup/two_certreqmain.csr"

/* diag struct */
typedef struct
{
	uint8_t	 diagcode[PP_RMTDIAG_FAILCODE_LEN];
	uint8_t	 faultCodeType;
	uint8_t	 lowByte;
	uint32_t diagTime;//ʱ���
}PP_rmtDiag_faultcode_t;

typedef struct
{
	uint8_t sueecss;
	uint8_t faultNum;//������
	PP_rmtDiag_faultcode_t faultcode[255];
}PP_rmtDiag_Fault_t;

typedef struct
{
	uint8_t tboxFault;
	uint8_t BMSMiss;
	uint8_t MCUMiss;
}PP_rmtDiag_NodeFault_t;

typedef enum
{
    PP_MSG_SOCKET = 1,//MPU_MID_GB32960,
    PP_MSG_BLE,
} pp_MSG_TYPE;

extern void PP_rmtDiag_queryInform_cb(void);

extern int PrvtProt_init(INIT_PHASE phase);
extern int PrvtProt_run(void);

extern void PrvtPro_SetHeartBeatPeriod(unsigned char period);
extern void PrvtPro_Setsuspend(unsigned char suspend);
extern void PrvtPro_SettboxId(unsigned int tboxid);
extern void PrvtPro_SetEcallReq(unsigned char req);
extern void PrvtPro_SetEcallResp(unsigned char resp);
extern void PP_rmtCfg_SetmcuSw(const char *mcuSw);
extern void PP_rmtCfg_SetmpuSw(const char *mpuSw);
extern void PP_rmtCfg_Seticcid(const char *iccid);
extern void PrvtProt_Settboxsn(const char *tboxsn);
extern void PrvtPro_ShowPara(void);
extern void PP_rmtCtrl_BluetoothCtrlReq(unsigned char obj, unsigned char cmd);
extern void PP_rmtCtrl_HuCtrlReq(unsigned char obj, void *cmdpara);

extern void SetPrvtProt_Awaken(void);
extern unsigned char GetPrvtProt_Sleep(void);
extern void Setsocketproxy_Awaken(void);
extern char sockproxy_Sleep(void);
extern void getPPrmtDiagCfg_NodeFault(PP_rmtDiag_NodeFault_t *rmtDiag_NodeFault);
extern unsigned char GetPP_ChargeCtrl_appointSt(void);
extern unsigned char GetPP_ChargeCtrl_appointHour(void);
extern unsigned char GetPP_ChargeCtrl_appointMin(void);

extern unsigned char GetPP_CertDL_CertValid(void);
extern void PP_CertDL_CertDLReset(void);
extern unsigned char GetPP_CertDL_CertUpdate(void);
extern unsigned char GetPP_CertDL_allowBDLink(void);
#endif