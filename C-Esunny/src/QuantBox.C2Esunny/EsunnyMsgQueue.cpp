#include "StdAfx.h"
#include "EsunnyMsgQueue.h"

void CEsunnyMsgQueue::Clear()
{
	SMsgItem* pItem = NULL;
	//清空队列
	while(m_queue.dequeue(pItem))
	{
		_Output(pItem);
		delete pItem;
	}
}

bool CEsunnyMsgQueue::Process()
{
	SMsgItem* pItem = NULL;
	if(m_queue.dequeue(pItem))
	{
		_Output(pItem);
		delete pItem;
		return true;
	}
	return false;
}

void CEsunnyMsgQueue::StartThread()
{
	if (NULL == m_hThread)
	{
		m_bRunning = true;
		m_hThread = CreateThread(NULL,0,ProcessThread,this,0,NULL); 
	}
}

void CEsunnyMsgQueue::StopThread()
{
	//停止线程
	m_bRunning = false;
	WaitForSingleObject(m_hThread,INFINITE);
	CloseHandle(m_hThread);
	m_hThread = NULL;
}

DWORD WINAPI ProcessThread(LPVOID lpParam)
{
	CEsunnyMsgQueue* pMsgQueue = reinterpret_cast<CEsunnyMsgQueue *>(lpParam);
	if (pMsgQueue)
		pMsgQueue->RunInThread();
	return 0;
}

void CEsunnyMsgQueue::RunInThread()
{
	m_nSleep = 1;
	while (m_bRunning)
	{
		if(Process())
		{
			//成功处理了一个
			m_nSleep = 1;
		}
		else
		{
			//失败表示队列为空，等待一会再来取为好
			m_nSleep *= 2;
			m_nSleep %= 255;//不超过N毫秒,不能用2的N次方，会导致Sleep(0)占用CPU
			Sleep(m_nSleep);
		}
	}

	//清理线程
	CloseHandle(m_hThread);
	m_hThread = NULL;
	m_bRunning = false;
}

void CEsunnyMsgQueue::_Input(SMsgItem* pMsgItem)
{
	//由于只内部调用，所以不再检查指针是否有效
	m_queue.enqueue(pMsgItem);
}

void CEsunnyMsgQueue::_Output(SMsgItem* pMsgItem)
{
	//内部调用，不判断指针是否有效
	switch(pMsgItem->type)
	{
	case E_fnOnConnect:
		Output_OnConnect(pMsgItem);
		break;
	case E_fnOnDisconnect:
		Output_OnDisconnect(pMsgItem);
		break;
	case E_fnOnStkQuot:
		Output_OnStkQuot(pMsgItem);
		break;
	case E_fnOnRspHistoryQuot:
		Output_OnRspHistoryQuot(pMsgItem);
		break;
	case E_fnOnRspTraceData:
		Output_OnRspTraceData(pMsgItem);
		break;
	case E_fnOnRspMarketInfo:
		Output_OnRspMarketInfo(pMsgItem);
		break;
	default:
		_ASSERT(false);
		break;
	}
}

void CEsunnyMsgQueue::Input_OnConnect(void* pQuotApi,int err,const char *errtext,ConnectionStatus result)
{
	if(NULL==errtext)
		return;

	int bufLen = strlen(errtext)+1;
	int totelLen = sizeof(SMsgItem)+bufLen;
	SMsgItem* pItem = (SMsgItem*)new char[totelLen];
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnConnect;
		pItem->pApi = pQuotApi;
		pItem->err = err;
		strncpy(pItem->buffer,errtext,bufLen);
		pItem->pBuffer = (void *)result;

		_Input(pItem);
	}
}

void CEsunnyMsgQueue::Input_OnDisconnect(void* pQuotApi,int err,const char *errtext,ConnectionStatus step)
{
	if(NULL==errtext)
		return;

	int bufLen = strlen(errtext)+1;
	int totelLen = sizeof(SMsgItem)+bufLen;
	SMsgItem* pItem = (SMsgItem*)new char[totelLen];
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnDisconnect;
		pItem->pApi = pQuotApi;
		pItem->err = err;
		strncpy(pItem->buffer,errtext,bufLen);
		pItem->pBuffer = (void *)step;

		_Input(pItem);
	}
}

void CEsunnyMsgQueue::Input_OnRspHistoryQuot(void* pQuotApi,STKHISDATA *pHisData)
{
	if(NULL==pHisData)
		return;

	int bufLen = sizeof(STKHISDATA)+pHisData->nCount*sizeof(pHisData->HisData);
	int totelLen = sizeof(SMsgItem)+bufLen;
	SMsgItem* pItem = (SMsgItem*)new char[totelLen];
	if(pItem)
	{
		memset(pItem,0,sizeof(SMsgItem));
		pItem->type = E_fnOnRspHistoryQuot;
		pItem->pApi = pQuotApi;
		pItem->pBuffer = pItem->buffer;
		memcpy(pItem->buffer,pHisData,bufLen);

		_Input(pItem);
	}
}

void CEsunnyMsgQueue::Input_OnRspMarketInfo(void* pQuotApi,MarketInfo *pMarketInfo,int bLast)
{
	if(NULL == pMarketInfo)
		return;

	int bufLen = sizeof(MarketInfo)+pMarketInfo->stocknum*sizeof(pMarketInfo->stockdata);
	int totelLen = sizeof(SMsgItem)+bufLen;
	SMsgItem* pItem = (SMsgItem*)new char[totelLen];
	if(pItem)
	{
		memset(pItem,0,totelLen);
		pItem->type = E_fnOnRspMarketInfo;
		pItem->pApi = pQuotApi;
		pItem->err = bLast;
		pItem->pBuffer = pItem->buffer;
		memcpy(pItem->buffer,pMarketInfo,bufLen);

		_Input(pItem);
	}
}

void CEsunnyMsgQueue::Input_OnRspTraceData(void* pQuotApi,STKTRACEDATA *pTraceData)
{
	if(NULL == pTraceData)
		return;

	int bufLen = sizeof(STKTRACEDATA)+pTraceData->nCount*sizeof(pTraceData->TraceData);
	int totelLen = sizeof(SMsgItem)+bufLen;
	SMsgItem* pItem = (SMsgItem*)new char[totelLen];
	if(pItem)
	{
		memset(pItem,0,totelLen);
		pItem->type = E_fnOnRspTraceData;
		pItem->pApi = pQuotApi;
		pItem->pBuffer = pItem->buffer;
		memcpy(pItem->buffer,pTraceData,bufLen);

		_Input(pItem);
	}
}

void CEsunnyMsgQueue::Input_OnStkQuot(void* pQuotApi,STKDATA *pData)
{
	if(NULL == pData)
		return;

	int bufLen = sizeof(STKDATA);
	int totelLen = sizeof(SMsgItem)+bufLen;
	SMsgItem* pItem = (SMsgItem*)new char[totelLen];
	if(pItem)
	{
		memset(pItem,0,totelLen);
		pItem->type = E_fnOnStkQuot;
		pItem->pApi = pQuotApi;
		pItem->pBuffer = pItem->buffer;
		memcpy(pItem->buffer,pData,bufLen);

		_Input(pItem);
	}
}