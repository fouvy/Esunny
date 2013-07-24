using System;
using System.Runtime.InteropServices;

namespace QuantBox.CSharp2Esunny
{
    /// <summary>
    /// 即时数据结构
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct STKDATA
    {
        /// <summary>
        /// 市场中文名
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string Market;
        /// <summary>
        /// 合约代码
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public float Code;
        /// <summary>
        /// 昨收盘
        /// </summary>
        public float YClose;
        /// <summary>
        /// 昨结算
        /// </summary>
        public float YSettle;
        /// <summary>
        /// 开盘价
        /// </summary>
        public float Open;
        /// <summary>
        /// 最高价
        /// </summary>
        public float High;
        /// <summary>
        /// 最低价
        /// </summary>
        public float Low;
        /// <summary>
        /// 最新价
        /// </summary>
        public float New;
        /// <summary>
        /// 涨跌
        /// </summary>
        public float NetChg;
        /// <summary>
        /// 涨跌幅
        /// </summary>
        public float Markup;
        /// <summary>
        /// 振幅
        /// </summary>
        public float Swing;
        /// <summary>
        /// 结算价
        /// </summary>
        public float Settle;
        /// <summary>
        /// 成交量
        /// </summary>
        public float Volume;
        /// <summary>
        /// 持仓量
        /// </summary>
        public float Amount;
        /// <summary>
        /// 申卖价
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
        public float[] Ask;
        /// <summary>
        /// 申卖量
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
        public float[] AskVol;
        /// <summary>
        /// 申买价
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
        public float[] Bid;
        /// <summary>
        /// 申买量
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
        public float[] BidVol;
        /// <summary>
        /// 平均价
        /// </summary>
        public float AvgPrice;
        /// <summary>
        /// 涨停板
        /// </summary>
        public float LimitUp;
        /// <summary>
        /// 跌停板
        /// </summary>
        public float LimitDown;
        /// <summary>
        /// 合约最高
        /// </summary>
        public float HistoryHigh;
        /// <summary>
        /// 合约最低
        /// </summary>
        public float HistoryLow;
        /// <summary>
        /// 昨持仓
        /// </summary>
        public int YOPI;
        /// <summary>
        /// 昨虚实度
        /// </summary>
        public float ZXSD;
        /// <summary>
        /// 今虚实度
        /// </summary>
        public float JXSD;
        /// <summary>
        /// 成交金额
        /// </summary>
        public float CJJE;
    }

    /// <summary>
    /// 历史数据
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct HISTORYDATA
    {
        /// <summary>
        /// 时间,形如：2009-06-01 08:00:00
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        public string time;
        /// <summary>
        /// 开盘
        /// </summary>
        public float fOpen;
        /// <summary>
        /// 最高
        /// </summary>
        public float fHigh;
        /// <summary>
        /// 最低
        /// </summary>
        public float fLow;
        /// <summary>
        /// 收盘
        /// </summary>
        public float fClose;
        /// <summary>
        /// 成交量(手)
        /// </summary>
        public float fVolume;
        /// <summary>
        /// 成交额(元)
        /// </summary>
        public float fAmount;
    }

    /// <summary>
    /// 品种历史数据
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct STKHISDATA
    {
        /// <summary>
        /// 市场中文名
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string Market;
        /// <summary>
        /// 品种代码
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string Code;
        /// <summary>
        /// 周期
        /// </summary>
        public short nPeriod;
        /// <summary>
        /// 历史数据数目
        /// </summary>
        public short nCount;
        /// <summary>
        /// 
        /// </summary>
        //public HISTORYDATA	HisData;
    }

    /// <summary>
    /// 成交明细
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct STOCKTRACEDATA
    {
        /// <summary>
        /// 时间,形如：2009-06-01 08:00:00
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        public string time;
        /// <summary>
        /// 最新价
        /// </summary>
        public float m_NewPrice;
        /// <summary>
        /// 总量
        /// </summary>
        public float m_Volume;
        /// <summary>
        /// 持仓
        /// </summary>
        public float m_Amount;
        /// <summary>
        /// 委买价
        /// </summary>
        public float m_BuyPrice;
        /// <summary>
        /// 委卖价
        /// </summary>
        public float m_SellPrice;
        /// <summary>
        /// 申买量
        /// </summary>
        public float m_BuyVol;
        /// <summary>
        /// 申卖量
        /// </summary>
        public float m_SellVol;
    }

    /// <summary>
    /// 品种明细
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct STKTRACEDATA
    {
        /// <summary>
        /// 市场中文名
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string Market;
        /// <summary>
        /// 品种代码
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string Code;
        /// <summary>
        /// 记录数目
        /// </summary>
        public ushort nCount;
        /// <summary>
        /// 
        /// </summary>
        //public STOCKTRACEDATA	TraceData;
    }

    /// <summary>
    /// 合约信息
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct StockInfo
    {
        /// <summary>
        /// 中文名
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string szName;
        /// <summary>
        /// 合约代码
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string szCode;
    }

    /// <summary>
    /// 单个市场的合约信息
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct MarketInfo
    {
        /// <summary>
        /// 市场中文名
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string Market;
        /// <summary>
        /// 合约数目
        /// </summary>
        public ushort stocknum;
        /// <summary>
        /// 合约信息数据
        /// </summary>
        //public StockInfo stockdata;
    }
}
