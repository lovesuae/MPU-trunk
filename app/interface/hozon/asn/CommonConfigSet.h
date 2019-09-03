/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "HOZON"
 * 	found in "HOZON_PRIV_v1.0.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_CommonConfigSet_H_
#define	_CommonConfigSet_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BOOLEAN.h>
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CommonConfigSet */
typedef struct CommonConfigSet {
	BOOLEAN_t	 actived;
	BOOLEAN_t	 rcEnabled;
	BOOLEAN_t	 svtEnabled;
	BOOLEAN_t	 vsEnabled;
	BOOLEAN_t	 iCallEnabled;
	BOOLEAN_t	 bCallEnabled;
	BOOLEAN_t	 eCallEnabled;
	BOOLEAN_t	 dcEnabled;
	BOOLEAN_t	 dtcEnabled;
	BOOLEAN_t	 journeysEnabled;
	BOOLEAN_t	 onlineInfEnabled;
	BOOLEAN_t	 rChargeEnabled;
	BOOLEAN_t	 btKeyEntryEnabled;
	BOOLEAN_t	 carEmpowerEnabled;
	BOOLEAN_t	 eventReportEnabled;
	BOOLEAN_t	 carAlarmEnabled;
	long	 heartbeatTimeout;
	long	 dormancyHeartbeatTimeout;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CommonConfigSet_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CommonConfigSet;

#ifdef __cplusplus
}
#endif

#endif	/* _CommonConfigSet_H_ */
#include <asn_internal.h>
