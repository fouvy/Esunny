#pragma once

#include "QuantBox.C2Esunny.h"
#include "include\EsunnyQuotAPI\EsunnyQuot.h"

#include <set>
#include <string>

using namespace std;

class CEsunnyMsgQueue;

class CQuotApi :
	public IEsunnyQuotNotify
{
public:
	CQuotApi(void);
	virtual ~CQuotApi(void);

	void RegisterMsgQueue(CEsunnyMsgQueue* pMsgQueue);

	void Connect(
		const string& szIP,
		int szPort,
		const string& szInvestorId,
		const string& szPassword);
	void Disconnect();

	int RequestHistory(const char *market,const char *stk,int period);
	int RequestTrace(const char *market,const char *stk,const char *date);

private:
	////订阅行情
	//void Subscribe(const set<string>& instrumentIDs);
	//登录请求
	void Login();


	int __cdecl OnRspLogin(int err,const char *errtext);
	int __cdecl OnChannelLost(int err,const char *errtext);
	int __cdecl OnStkQuot(struct STKDATA *pData);
	int __cdecl OnRspHistoryQuot(struct STKHISDATA *pHisData);
	int __cdecl OnRspTraceData(struct STKTRACEDATA *pTraceData);
	int __cdecl OnRspMarketInfo(struct MarketInfo *pMarketInfo,int bLast);

private:
	ConnectionStatus			m_status;				//连接状态
	
	set<string>					m_setInstrumentIDs;		//正在订阅的合约
	IEsunnyQuotClient*			m_pApi;					//行情API
	CEsunnyMsgQueue*			m_msgQueue;				//消息队列指针

	string						m_szIP;				//生成配置文件的路径
	int							m_nPort;
	string						m_szInvestorId;			//投资者ID
	string						m_szPassword;			//密码
};

