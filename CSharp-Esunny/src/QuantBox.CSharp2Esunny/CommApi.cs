using System;
using System.Runtime.InteropServices;

namespace QuantBox.CSharp2Esunny
{
    public class CommApi
    {
        public const string DllFileName = "QuantBox.C2Esunny.dll";

        [DllImport(CommApi.DllFileName, EntryPoint = "ES_ConvetString2MarketType")]
        public static extern MarketType ES_ConvetString2MarketType(string market);

        [DllImport(CommApi.DllFileName, EntryPoint = "ES_ConvetMarketType2String")]
        public static extern string ES_ConvetString2MarketType(MarketType market);

        // -------------------------------------------------------------

        [DllImport(CommApi.DllFileName, EntryPoint = "ES_CreateMsgQueue")]
        public static extern IntPtr ES_CreateMsgQueue();

        [DllImport(CommApi.DllFileName, EntryPoint = "ES_ProcessMsgQueue")]
        public static extern bool ES_ProcessMsgQueue(IntPtr pMsgQueue);

        [DllImport(CommApi.DllFileName, EntryPoint = "ES_ReleaseMsgQueue")]
        public static extern void ES_ReleaseMsgQueue(IntPtr pMsgQueue);

        [DllImport(CommApi.DllFileName, EntryPoint = "ES_ClearMsgQueue")]
        public static extern void ES_ClearMsgQueue(IntPtr pMsgQueue);

        [DllImport(CommApi.DllFileName, EntryPoint = "ES_StartMsgQueue")]
        public static extern void ES_StartMsgQueue(IntPtr pMsgQueue);

        [DllImport(CommApi.DllFileName, EntryPoint = "ES_StopMsgQueue")]
        public static extern void ES_StopMsgQueue(IntPtr pMsgQueue);

        // -------------------------------------------------------------

        [DllImport(CommApi.DllFileName, EntryPoint = "ES_RegOnConnect")]
        public static extern void ES_RegOnConnect(IntPtr pMsgQueue, fnOnConnectionStatus pCallback);

        [DllImport(CommApi.DllFileName, EntryPoint = "ES_RegOnDisconnect")]
        public static extern void ES_RegOnDisconnect(IntPtr pMsgQueue, fnOnConnectionStatus pCallback);
    }
}
