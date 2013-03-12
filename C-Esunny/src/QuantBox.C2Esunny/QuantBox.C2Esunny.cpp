// QuantBox.C2CTP.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "QuantBox.C2Esunny.h"

#include "QuotApi.h"
#include "EsunnyMsgQueue.h"

const char CZCE_CHINESE[] = "郑州商品";
const char DCE_CHINESE[] = "大连商品";
const char SHFE_CHINESE[] = "上海期货";
const char CFFEX_CHINESE[] = "中国金融";
const char MAX_MARKET_TYPE_CHINESE[] = "MAX_MARKET_TYPE";

inline CEsunnyMsgQueue* ES_GetQueue(void* pMsgQueue)
{
	return static_cast<CEsunnyMsgQueue*>(pMsgQueue);
}

inline CQuotApi* QT_GetApi(void* pQuotApi)
{
	return static_cast<CQuotApi*>(pQuotApi);
}

QUANTBOXC2ESUNNY_API MarketType __stdcall ES_ConvetString2MarketType(const char *market)
{
	if(0 == strcmp(market,CZCE_CHINESE))
		return CZCE;
	else if(0 == strcmp(market,DCE_CHINESE))
		return DCE;
	else if(0 == strcmp(market,SHFE_CHINESE))
		return SHFE;
	else if(0 == strcmp(market,CFFEX_CHINESE))
		return CFFEX;
	else
		return MAX_MARKET_TYPE;
}

QUANTBOXC2ESUNNY_API const char * __stdcall ES_ConvetMarketType2String(MarketType market)
{
	switch (market)
	{
	case CZCE:
		return CZCE_CHINESE;
	case DCE:
		return DCE_CHINESE;
	case SHFE:
		return SHFE_CHINESE;
	case CFFEX:
		return CFFEX_CHINESE;
	default:
		return MAX_MARKET_TYPE_CHINESE;
	}
}

QUANTBOXC2ESUNNY_API void* __stdcall ES_CreateMsgQueue()
{
	return new CEsunnyMsgQueue();
}

QUANTBOXC2ESUNNY_API void __stdcall ES_ReleaseMsgQueue(void* pMsgQueue)
{
	if(pMsgQueue)
	{
		delete ES_GetQueue(pMsgQueue);
	}
}

QUANTBOXC2ESUNNY_API void __stdcall ES_RegOnConnect(void* pMsgQueue,fnOnConnectionStatus pCallback)
{
	if(pMsgQueue)
	{
		ES_GetQueue(pMsgQueue)->RegisterCallback_OnConnect(pCallback);
	}
}

QUANTBOXC2ESUNNY_API void __stdcall ES_RegOnDisconnect(void* pMsgQueue,fnOnConnectionStatus pCallback)
{
	if(pMsgQueue)
	{
		ES_GetQueue(pMsgQueue)->RegisterCallback_OnDisconnect(pCallback);
	}
}

QUANTBOXC2ESUNNY_API void __stdcall ES_RegOnRspHistoryQuot(void* pMsgQueue,fnOnRspHistoryQuot pCallback)
{
	if(pMsgQueue)
	{
		ES_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2ESUNNY_API void __stdcall ES_RegOnRspMarketInfo(void* pMsgQueue,fnOnRspMarketInfo pCallback)
{
	if(pMsgQueue)
	{
		ES_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2ESUNNY_API void __stdcall ES_RegOnRspTraceData(void* pMsgQueue,fnOnRspTraceData pCallback)
{
	if(pMsgQueue)
	{
		ES_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2ESUNNY_API void __stdcall ES_RegOnStkQuot(void* pMsgQueue,fnOnStkQuot pCallback)
{
	if(pMsgQueue)
	{
		ES_GetQueue(pMsgQueue)->RegisterCallback(pCallback);
	}
}

QUANTBOXC2ESUNNY_API bool __stdcall ES_ProcessMsgQueue(void* pMsgQueue)
{
	if(pMsgQueue)
	{
		return ES_GetQueue(pMsgQueue)->Process();
	}
	return false;
}

QUANTBOXC2ESUNNY_API void __stdcall ES_ClearMsgQueue(void* pMsgQueue)
{
	if(pMsgQueue)
	{
		return ES_GetQueue(pMsgQueue)->Clear();
	}
}

QUANTBOXC2ESUNNY_API void __stdcall ES_StartMsgQueue(void* pMsgQueue)
{
	if(pMsgQueue)
	{
		return ES_GetQueue(pMsgQueue)->StartThread();
	}
}

QUANTBOXC2ESUNNY_API void __stdcall ES_StopMsgQueue(void* pMsgQueue)
{
	if(pMsgQueue)
	{
		return ES_GetQueue(pMsgQueue)->StopThread();
	}
}

QUANTBOXC2ESUNNY_API void* __stdcall QT_CreateQuotApi()
{
	return new CQuotApi();
}

QUANTBOXC2ESUNNY_API void __stdcall QT_RegMsgQueue2QuotApi(void* pQuotApi,void* pMsgQueue)
{
	if(pQuotApi)
	{
		QT_GetApi(pQuotApi)->RegisterMsgQueue((CEsunnyMsgQueue*)pMsgQueue);
	}
}

QUANTBOXC2ESUNNY_API void __stdcall QT_Connect(
	void* pQuotApi,
	const char* szIP,
	int nPort,
	const char* szInvestorId,
	const char* szPassword)
{
	if(pQuotApi
		&&szIP
		&&szInvestorId
		&&szPassword)
	{
		QT_GetApi(pQuotApi)->Connect(szIP,nPort,szInvestorId,szPassword);
	}
}

QUANTBOXC2ESUNNY_API void __stdcall QT_Disconnect(void* pQuotApi)
{
	if(pQuotApi)
	{
		QT_GetApi(pQuotApi)->Disconnect();
	}
}

QUANTBOXC2ESUNNY_API int __stdcall QT_RequestHistory(void* pQuotApi,const char * market,const char *stk,PeriodType period)
{
	if(pQuotApi)
	{
		return QT_GetApi(pQuotApi)->RequestHistory(market,stk,period);
	}
	return -3;
}

QUANTBOXC2ESUNNY_API int __stdcall QT_RequestTrace(void* pQuotApi,const char * market,const char *stk,const char *date)
{
	if(pQuotApi)
	{
		return QT_GetApi(pQuotApi)->RequestTrace(market,stk,date);
	}
	return -3;
}

QUANTBOXC2ESUNNY_API void __stdcall QT_ReleaseQuotApi(void* pQuotApi)
{
	if(pQuotApi)
	{
		delete QT_GetApi(pQuotApi);
	}
}