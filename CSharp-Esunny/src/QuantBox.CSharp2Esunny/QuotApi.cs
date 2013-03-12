using System;
using System.Runtime.InteropServices;

namespace QuantBox.CSharp2Esunny
{
    public class QuotApi
    {
        [DllImport(CommApi.DllFileName, EntryPoint = "ES_RegOnRspMarketInfo")]
        public static extern void ES_RegOnRspMarketInfo(IntPtr pMsgQueue, fnOnRspMarketInfo pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "ES_RegOnRspHistoryQuot")]
        public static extern void ES_RegOnRspHistoryQuot(IntPtr pMsgQueue, fnOnRspHistoryQuot pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "ES_RegOnRspTraceData")]
        public static extern void ES_RegOnRspTraceData(IntPtr pMsgQueue, fnOnRspTraceData pCallback);

        // ----------------------------------------------------------------

        [DllImport(CommApi.DllFileName, EntryPoint = "QT_CreateQuotApi")]
        public static extern IntPtr QT_CreateQuotApi();

        [DllImport(CommApi.DllFileName, EntryPoint = "QT_RegMsgQueue2QuotApi")]
        public static extern void QT_RegMsgQueue2QuotApi(IntPtr pQuotApi, IntPtr pMsgQueue);

        [DllImport(CommApi.DllFileName, EntryPoint = "QT_Connect")]
        public static extern void QT_Connect(IntPtr pQuotApi, string szIP, int nPort, string szInvestorId, string szPassword);

        [DllImport(CommApi.DllFileName, EntryPoint = "QT_ReleaseQuotApi")]
        public static extern void QT_ReleaseQuotApi(IntPtr pQuotApi);

        [DllImport(CommApi.DllFileName, EntryPoint = "QT_RequestHistory")]
        public static extern int QT_RequestHistory(IntPtr pQuotApi, string market, string stk, PeriodType period);

        [DllImport(CommApi.DllFileName, EntryPoint = "QT_RequestTrace")]
        public static extern int QT_RequestTrace(IntPtr pQuotApi, string market, string stk, string date);
    }
}
