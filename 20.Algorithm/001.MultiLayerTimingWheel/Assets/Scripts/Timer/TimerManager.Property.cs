using System.Collections.Generic;
using System.Collections.ObjectModel;

using UnityEngine;

using Timers.TickHandlers;
using Timers.Pools;

namespace Timers
{
    /// <summary>
    /// 計時器管理 (幀率作為Tick，且使用MS)
    ///     保存各種參數
    /// </summary>
    public sealed partial class TimerManager
    {
        [SerializeField]
        private int _defaultTimerPoolCount = 100000;
        [SerializeField]
        private ulong _tickIntervalMS = 15;                     // 每Tick間隔

        private static ulong s_CurrentMS;                       // 當前Tick

        private static TimerPool s_Pool;                        // 計時器池
        public static BaseTimerTickHandler s_TickHandler;       // 計時處理器

        private static Dictionary<ulong, Timer> s_ActiveTimers = new Dictionary<ulong, Timer>();    // 當前執行中計時器

        public static bool IsRunning { get; set; } = true;      // 默認啟動

        // 測試用
        public static ulong CurrentMS => s_CurrentMS;
        public static ulong CurrentTick => s_TickHandler.CurrentTick;
        public static ReadOnlyDictionary<ulong, Timer> ActiveTimers => new ReadOnlyDictionary<ulong, Timer>(s_ActiveTimers);
    }
}
