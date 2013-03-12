#pragma once

#include "QuantBox.C2Esunny.h"
#include "include\LockFreeQ.h"

class CEsunnyMsgQueue
{
	//响应队列中可能出现的消息类型（按字母排序）
	enum EnumMsgType
	{
		E_fnOnConnect,	
		E_fnOnDisconnect,
		E_fnOnRspHistoryQuot,
		E_fnOnRspTraceData,
		E_fnOnRspMarketInfo,
		E_fnOnStkQuot,
	};

	struct SMsgItem
	{
		EnumMsgType			type;			//消息类型
		void*				pApi;			//指向类对象的指针	
		int					err;
		void*				pBuffer;		//指向Buf的指针	
		char				buffer[1];		//buf的起点
	};

public:
	CEsunnyMsgQueue(void)
	{
		m_nSleep = 1;
		m_hThread = NULL;
		m_bRunning = false;

		//回调函数地址指针
		m_fnOnConnect = NULL;
		m_fnOnDisconnect = NULL;
		m_fnOnStkQuot = NULL;
		m_fnOnRspHistoryQuot = NULL;
		m_fnOnRspTraceData = NULL;
		m_fnOnRspMarketInfo = NULL;
	}
	virtual ~CEsunnyMsgQueue(void)
	{
		StopThread();
		Clear();
	}

public:
	//清空队列
	void Clear();

	//可以由外部发起，顺序处理队列触发回调函数
	bool Process();

	//由内部启动线程，内部主动调用Process触发回调
	void StartThread();
	void StopThread();

	//将外部的函数地址注册到队列(按字母排序)
	void RegisterCallback_OnConnect(fnOnConnectionStatus pCallback){m_fnOnConnect = pCallback;}
	void RegisterCallback_OnDisconnect(fnOnConnectionStatus pCallback){m_fnOnDisconnect = pCallback;}
	void RegisterCallback(fnOnRspHistoryQuot pCallback){m_fnOnRspHistoryQuot = pCallback;}
	void RegisterCallback(fnOnRspMarketInfo pCallback){m_fnOnRspMarketInfo = pCallback;}
	void RegisterCallback(fnOnRspTraceData pCallback){m_fnOnRspTraceData = pCallback;}
	void RegisterCallback(fnOnStkQuot pCallback){m_fnOnStkQuot = pCallback;}

	//响应结果处理后入队列(按字母排序)
	void Input_OnConnect(void* pQuotApi,int err,const char *errtext,ConnectionStatus result);
	void Input_OnDisconnect(void* pQuotApi,int err,const char *errtext,ConnectionStatus step);
	void Input_OnRspHistoryQuot(void* pQuotApi,STKHISDATA *pHisData);
	void Input_OnRspMarketInfo(void* pQuotApi,MarketInfo *pMarketInfo,int bLast);
	void Input_OnRspTraceData(void* pQuotApi,STKTRACEDATA *pTraceData);
	void Input_OnStkQuot(void* pQuotApi,STKDATA *pData);
private:
	friend DWORD WINAPI ProcessThread(LPVOID lpParam);
	void RunInThread();

	//响应结果直接入队列
	void _Input(SMsgItem* pMsgItem);
	//队列中的消息判断分发
	void _Output(SMsgItem* pMsgItem);

	//响应输出
	void Output_OnConnect(SMsgItem* pItem)
	{
		if(m_fnOnConnect)
			(*m_fnOnConnect)(pItem->pApi,pItem->err,pItem->buffer,(ConnectionStatus)(int)pItem->pBuffer);
	}
	void Output_OnDisconnect(SMsgItem* pItem)
	{
		if(m_fnOnConnect)
			(*m_fnOnConnect)(pItem->pApi,pItem->err,pItem->buffer,(ConnectionStatus)(int)pItem->pBuffer);
	}
	void Output_OnRspHistoryQuot(SMsgItem* pItem)
	{
		if(m_fnOnRspHistoryQuot)
			(*m_fnOnRspHistoryQuot)(pItem->pApi,pItem->pBuffer,(STKHISDATA *)pItem->buffer);
	}
	void Output_OnRspMarketInfo(SMsgItem* pItem)
	{
		if(m_fnOnRspMarketInfo)
			(*m_fnOnRspMarketInfo)(pItem->pApi,pItem->pBuffer,(MarketInfo *)pItem->buffer,pItem->err);
	}
	void Output_OnRspTraceData(SMsgItem* pItem)
	{
		if(m_fnOnRspTraceData)
			(*m_fnOnRspTraceData)(pItem->pApi,pItem->pBuffer,(STKTRACEDATA *)pItem->buffer);
	}
	void Output_OnStkQuot(SMsgItem* pItem)
	{
		if(m_fnOnStkQuot)
			(*m_fnOnStkQuot)(pItem->pApi,pItem->pBuffer,(STKDATA *)pItem->buffer);
	}

private:
	int							m_nSleep;
	volatile bool				m_bRunning;
	HANDLE						m_hThread;

	MSQueue<SMsgItem*>			m_queue;			//响应队列

	//回调函数指针（按字母排序）
	fnOnConnectionStatus		m_fnOnConnect;
	fnOnConnectionStatus		m_fnOnDisconnect;
	fnOnRspHistoryQuot			m_fnOnRspHistoryQuot;
	fnOnRspMarketInfo			m_fnOnRspMarketInfo;
	fnOnRspTraceData			m_fnOnRspTraceData;
	fnOnStkQuot					m_fnOnStkQuot;
};

