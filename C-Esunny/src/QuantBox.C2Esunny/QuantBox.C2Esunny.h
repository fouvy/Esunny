// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 QUANTBOXC2ESUNNY_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// QUANTBOXC2ESUNNY_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifndef _QUANTBOXC2ESUNNY_H_
#define _QUANTBOXC2ESUNNY_H_

#ifdef QUANTBOXC2ESUNNY_EXPORTS
#define QUANTBOXC2ESUNNY_API __declspec(dllexport)
#else
#define QUANTBOXC2ESUNNY_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "include\EsunnyQuotAPI\EsunnyQuot.h"

//连接状态枚举
enum ConnectionStatus
{
	E_uninit,		//未初始化
	E_inited,		//已经初始化
	E_unconnected,	//连接已经断开
	E_connecting,	//连接中
	E_connected,	//连接成功
	E_authing,		//授权中
	E_authed,		//授权成功
	E_logining,		//登录中
	E_logined,		//登录成功
	E_confirming,	//结算单确认中
	E_confirmed,	//已经确认
	E_conn_max		//最大值
};

enum MarketType
{
	CZCE = 1,
	DCE = 2,
	SHFE = 3,
	CFFEX = 5,
	MAX_MARKET_TYPE,
};

enum PeriodType
{
	min1 = 1,
	min5 = 2,
	min60 = 3,
	daily = 4,
	MAX_PERIOD_TYPE
};

//回调函数类型定义（为编写方便，按字母排序
typedef void (__stdcall *fnOnConnectionStatus)(void* pApi,int err,const char *errtext,ConnectionStatus result);//连接后的结果状态
typedef void (__stdcall *fnOnRspHistoryQuot)(void* pQuotApi,void* pBuffer,STKHISDATA *pHisData);
typedef void (__stdcall *fnOnRspMarketInfo)(void* pQuotApi,void* pBuffer,MarketInfo *pMarketInfo,int bLast);
typedef void (__stdcall *fnOnRspTraceData)(void* pQuotApi,void* pBuffer,STKTRACEDATA *pTraceData);
typedef void (__stdcall *fnOnStkQuot)(void* pQuotApi,void* pBuffer,STKDATA *pData);
//创建接收消息队列，支持响应行情和交易
QUANTBOXC2ESUNNY_API MarketType __stdcall ES_ConvetString2MarketType(const char *market);
QUANTBOXC2ESUNNY_API const char * __stdcall ES_ConvetMarketType2String(MarketType market);

QUANTBOXC2ESUNNY_API void* __stdcall ES_CreateMsgQueue();

//向消息队列注册回调函数
QUANTBOXC2ESUNNY_API void __stdcall ES_RegOnConnect(void* pMsgQueue,fnOnConnectionStatus pCallback);
QUANTBOXC2ESUNNY_API void __stdcall ES_RegOnDisconnect(void* pMsgQueue,fnOnConnectionStatus pCallback);
QUANTBOXC2ESUNNY_API void __stdcall ES_RegOnRspHistoryQuot(void* pMsgQueue,fnOnRspHistoryQuot pCallback);
QUANTBOXC2ESUNNY_API void __stdcall ES_RegOnRspMarketInfo(void* pMsgQueue,fnOnRspMarketInfo pCallback);
QUANTBOXC2ESUNNY_API void __stdcall ES_RegOnRspTraceData(void* pMsgQueue,fnOnRspTraceData pCallback);
QUANTBOXC2ESUNNY_API void __stdcall ES_RegOnStkQuot(void* pMsgQueue,fnOnStkQuot pCallback);

//释放消息队列
QUANTBOXC2ESUNNY_API void __stdcall ES_ReleaseMsgQueue(void* pMsgQueue);
//清空消息队列内容
QUANTBOXC2ESUNNY_API void __stdcall ES_ClearMsgQueue(void* pMsgQueue);

//处理消息队列第一条记录
QUANTBOXC2ESUNNY_API bool __stdcall ES_ProcessMsgQueue(void* pMsgQueue);
//开启队列回调主动推送线程
QUANTBOXC2ESUNNY_API void __stdcall ES_StartMsgQueue(void* pMsgQueue);
//停止队列回调主动推送线程
QUANTBOXC2ESUNNY_API void __stdcall ES_StopMsgQueue(void* pMsgQueue);

//行情接口=======================================

//创建行情接口
QUANTBOXC2ESUNNY_API void* __stdcall QT_CreateQuotApi();
//将消息队列注册到行情接口上
QUANTBOXC2ESUNNY_API void __stdcall QT_RegMsgQueue2QuotApi(void* pQuotApi,void* pMsgQueue);
//连接
QUANTBOXC2ESUNNY_API void __stdcall QT_Connect(
	void* pQuotApi,
	const char* szIP,
	int nPort,
	const char* szInvestorId,
	const char* szPassword);

//订阅合约
QUANTBOXC2ESUNNY_API void __stdcall QT_RequestQuot(void* pQuotApi,const char * market,const char *stk,int need);
QUANTBOXC2ESUNNY_API int __stdcall QT_RequestHistory(void* pQuotApi,const char * market,const char *stk,PeriodType period);
QUANTBOXC2ESUNNY_API int __stdcall QT_RequestTrace(void* pQuotApi,const char * market,const char *stk,const char *date);
QUANTBOXC2ESUNNY_API void __stdcall QT_AddReqStk(void* pQuotApi,const char * market,const char *stk,int need);
QUANTBOXC2ESUNNY_API void __stdcall QT_SendReqStk(void* pQuotApi);
QUANTBOXC2ESUNNY_API void __stdcall QT_GetStkData(void* pQuotApi,const char * market,const char *stk,struct STKDATA *pData);
//断开连接
QUANTBOXC2ESUNNY_API void __stdcall QT_Disconnect(void* pQuotApi);
//释放行情接口
QUANTBOXC2ESUNNY_API void __stdcall QT_ReleaseQuotApi(void* pQuotApi);

#ifdef __cplusplus
}
#endif


#endif//end of _QUANTBOXC2ESUNNY_H_