using System;

namespace QuantBox.CSharp2Esunny
{
    public delegate void fnOnConnectionStatus(IntPtr pQuotApi,int err, string errtext, ConnectionStatus result);
    public delegate void fnOnRspHistoryQuot(IntPtr pQuotApi, IntPtr pBuffer, ref STKHISDATA pHisData);
    public delegate void fnOnRspMarketInfo(IntPtr pQuotApi, IntPtr pBuffer, ref MarketInfo pMarketInfo, int bLast);
    public delegate void fnOnRspTraceData(IntPtr pQuotApi, IntPtr pBuffer, ref STKTRACEDATA pTraceData);
    public delegate void fnOnStkQuot(IntPtr pQuotApi, IntPtr pBuffer, ref STKDATA pData);
}
