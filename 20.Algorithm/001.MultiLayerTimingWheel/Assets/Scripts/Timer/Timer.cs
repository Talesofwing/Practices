using System.Collections.Generic;

using Timers.Events;
using Timers.Pools;

namespace Timers
{
    /// <summary>
    /// 計時器 (無法繼承)
    ///     不保存LinkedListNode，實際應用時應該記錄
    ///     這次保留了可以加入多種TimerTickHandler的方式，所以不進行污染
    ///
    /// NOTE: 感覺可以將保存ms改為保存Tick
    /// </summary>
    public sealed class Timer : ITimerPoolObject
    {
        private static ulong s_IdCounter = 0;

        private ExpiredEventArgs _expiredEventArgs;
        private TimerArgs _timerArgs;

        public ulong ID { get; private set; }               // 計時器ID
        public ulong ExpireMS { get; set; }                 // 到期時間(MS)
        public int LoopCount { get; set; }                  // 循環次數 (<= 0: 無窮)
        public uint LoopedCount { get; set; }               // 已循環次數
        public ulong LoopIntervalMS { get; private set; }   // 循環間隔

        public bool IsCompleted => LoopedCount >= LoopCount;

        public event ExpiredEventHandler Expired;       // 到期事件

        /// <summary>
        /// 初始化
        /// </summary>
        public void Setup(ulong expireMS, int loopCount, ulong loopIntervalMS, TimerArgs args, ExpiredEventHandler expiredHandler)
        {
            ID = s_IdCounter++;

            ExpireMS = expireMS;
            LoopCount = loopCount + 1;      // 至少執行1次
            LoopIntervalMS = loopIntervalMS;

            _timerArgs = args;
            Expired += expiredHandler;

            LoopedCount = 0;
        }

        public void Execute()
        {
            LoopedCount++;

            Expired?.Invoke(this, _expiredEventArgs, _timerArgs);
        }

        #region ITimerPoolObject Implementation

        void ITimerPoolObject.OnGet()
        {
            _expiredEventArgs = GetExpiredEventArgs();
        }

        void ITimerPoolObject.OnReturn()
        {
            ReturnExpiredEventArgs(_expiredEventArgs);

            // 取出的計時器，必須進行Setup，所以這裏不需要進行多餘的重置

            // _expiredEventArgs = null;
            // _timerArgs = null;
            // LoopedCount = 0;
        }

        #endregion Implementation of Pool

        #region Simple EventArgs Pool

        private static int s_EventArgMaxCount = 1000;
        private static Queue<ExpiredEventArgs> s_ExpiredEventArgs = new Queue<ExpiredEventArgs>(s_EventArgMaxCount);

        private static ExpiredEventArgs GetExpiredEventArgs()
        {
            if (s_ExpiredEventArgs.Count > 0)
            {
                return s_ExpiredEventArgs.Dequeue();
            }
            else
            {
                return new ExpiredEventArgs();
            }
        }

        private static void ReturnExpiredEventArgs(ExpiredEventArgs args)
        {
            if (s_ExpiredEventArgs.Count < s_EventArgMaxCount)
            {
                s_ExpiredEventArgs.Enqueue(args);
            }
        }

        #endregion Simple EventArgs Pool

#if UNITY_EDITOR
        // Debug用
        public int Layer;
        public int SlotIndex;
        public ulong ExpireTick;
#endif
    }
}
