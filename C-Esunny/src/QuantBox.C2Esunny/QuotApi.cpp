#include "StdAfx.h"
#include "QuotApi.h"
#include "EsunnyMsgQueue.h"

#include <iostream>
using namespace std;

CQuotApi::CQuotApi(void)
{
	m_msgQueue = NULL;
	m_status = E_uninit;

	m_hThread = NULL;
	m_bRunning = false;
}

CQuotApi::~CQuotApi(void)
{
	Disconnect();
}

void CQuotApi::RegisterMsgQueue(CEsunnyMsgQueue* pMsgQueue)
{
	m_msgQueue = pMsgQueue;
}

void CQuotApi::Connect(
		const string& szIP,
		int nPort,
		const string& szInvestorId,
		const string& szPassword)
{
	m_szIP = szIP;
	m_nPort = nPort;
	m_szInvestorId = szInvestorId;
	m_szPassword = szPassword;

	m_pApi = CreateEsunnyQuotClient(this);

	m_status = E_inited;
	if(m_msgQueue)
		m_msgQueue->Input_OnConnect(this,0,"",m_status);

	if (NULL == m_hThread)
	{
		m_bRunning = true;
		m_hThread = CreateThread(NULL,0,ConnectThread,this,0,NULL); 
	}
}

DWORD WINAPI ConnectThread(LPVOID lpParam)
{
	CQuotApi* pQuot = reinterpret_cast<CQuotApi *>(lpParam);
	if (pQuot)
		pQuot->ConnectInThread();
	return 0;
}

void CQuotApi::ConnectInThread()
{
	int iRet = -1;
	int i = 0;

	m_nSleep = 1;

	while (m_bRunning)
	{
		++i;
		char buf[1024] = {0};
		sprintf(buf,"正在尝试第 %d 次连接......",i);
		m_status = E_connecting;
		if(m_msgQueue)
			m_msgQueue->Input_OnConnect(this,NULL,buf,m_status);
		
		if (m_pApi)
		{
			iRet = m_pApi->Connect(m_szIP.c_str(),m_nPort);
		}
		else
		{
			break;
		}

		if (0 == iRet)
		{
			Login();
			break;
		}
		else
		{
			//失败，按4的幂进行延时，但不超过1s
			m_nSleep *= 4;
			m_nSleep %= (1024*8-1);
			Sleep(m_nSleep);
		}
	}

	//清理线程
	CloseHandle(m_hThread);
	m_hThread = NULL;
	m_bRunning = false;
}

void CQuotApi::StopThread()
{
	//停止发送线程
	m_bRunning = false;
	WaitForSingleObject(m_hThread,INFINITE);
	CloseHandle(m_hThread);
	m_hThread = NULL;
}

void CQuotApi::Login()
{
	if (NULL == m_pApi)
		return;
	
	int nRet = m_pApi->Login(m_szInvestorId.c_str(),m_szPassword.c_str());
	m_status = E_logining;
	if(m_msgQueue)
		m_msgQueue->Input_OnConnect(this,NULL,"",m_status);
}

void CQuotApi::Disconnect()
{
	StopThread();

	m_status = E_unconnected;
	if(m_pApi)
	{
		m_pApi->DisConnect();
		DelEsunnyQuotClient(m_pApi);
		m_pApi = NULL;

		if(m_msgQueue)
			m_msgQueue->Input_OnDisconnect(this,NULL,"",m_status);
	}
}

int CQuotApi::RequestHistory(const char *market,const char *stk,int period)
{
	if(m_pApi)
	{
		return m_pApi->RequestHistory(market,stk,period);
	}
	return -2;
}

int CQuotApi::RequestTrace(const char *market,const char *stk,const char *date)
{
	if(m_pApi)
	{
		return m_pApi->RequestTrace(market,stk,date);
	}
	return -2;
}

int CQuotApi::OnRspLogin(int err,const char *errtext)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnConnect(this,err,errtext,err==0?E_logined:E_connected);
	return 0;
}

int CQuotApi::OnChannelLost(int err,const char *errtext)
{
	if (NULL == m_hThread)
	{
		m_bRunning = true;
		m_hThread = CreateThread(NULL,0,ConnectThread,this,0,NULL); 
	}

	if(m_msgQueue)
		m_msgQueue->Input_OnDisconnect(this,err,errtext,E_unconnected);
	return 0;
}

int CQuotApi::OnStkQuot(struct STKDATA *pData)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnStkQuot(this,pData);
	return 0;
}

int CQuotApi::OnRspHistoryQuot(struct STKHISDATA *pHisData)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnRspHistoryQuot(this,pHisData);
	return 0;
}

int CQuotApi::OnRspTraceData(struct STKTRACEDATA *pTraceData)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnRspTraceData(this,pTraceData);
	return 0;
}

int CQuotApi::OnRspMarketInfo(struct MarketInfo *pMarketInfo,int bLast)
{
	if(m_msgQueue)
		m_msgQueue->Input_OnRspMarketInfo(this,pMarketInfo,bLast);
	return 0;
}