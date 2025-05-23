using System.Collections.Generic;

using UnityEngine;

using Timers.Events;

namespace Timers
{
    /// <summary>
    /// 計時器管理 (幀率作為Tick，且使用MS)
    ///     用來管理計時器
    ///     只提供static函數 (但使用Singleton)
    /// </summary>
    public sealed partial class TimerManager : MonoBehaviour
    {
        private static void Tick(ulong tickMS)
        {
            s_CurrentMS += tickMS;

            s_TickHandler.Tick(s_CurrentMS);
        }

        public static void Run()
        {
            IsRunning = true;
        }

        public static void Stop()
        {
            IsRunning = false;
        }

        public static ulong StartTimer(ulong expireMS, ExpiredEventHandler expiredHandler)
        {
            return StartTimer(expireMS, 0, 0, null, expiredHandler);
        }

        public static ulong StartTimer(ulong expireMS, TimerArgs args, ExpiredEventHandler expiredHandler)
        {
            return StartTimer(expireMS, 0, 0, args, expiredHandler);
        }

        public static ulong StartTimer(ulong expireMS, int loopCount, ulong loopIntervalMS, TimerArgs args, ExpiredEventHandler expiredHandler)
        {
            Timer timer = s_Pool.Get();
            timer.Setup(expireMS + s_CurrentMS, loopCount, loopIntervalMS, args, expiredHandler);

            s_TickHandler.Insert(timer);

            s_ActiveTimers.Add(timer.ID, timer);

            return timer.ID;
        }

        /// <summary>
        /// 追加結束時間
        /// </summary>
        public static void AddTimerExpireTick(ulong id, ulong delay)
        {
            if (s_ActiveTimers.ContainsKey(id))
            {
                Timer timer = s_ActiveTimers[id];
                timer.ExpireMS += delay;
                s_TickHandler.Refresh(timer);
            }
        }

        /// <summary>
        /// 設定循環次數
        /// </summary>
        public static void SetTimerLoopCount(ulong id, int loopCount, bool resetLoopedCount)
        {
            if (s_ActiveTimers.ContainsKey(id))
            {
                Timer timer = s_ActiveTimers[id];
                timer.LoopCount = loopCount + 1;
                if (resetLoopedCount)
                {
                    timer.LoopedCount = 0;
                }

                if (timer.LoopCount <= timer.LoopedCount)
                {
                    // 如果當前計時器已經執行完，結束計時器

                    EndTimer(id, false);
                }
            }
        }

        /// <summary>
        /// 結束計時器
        /// </summary>
        public static void EndTimer(ulong id, bool isRunExpiredEvent)
        {
            if (TryGetTimer(id, out Timer timer))
            {
                if (isRunExpiredEvent)
                {
                    timer.Execute();
                }

                s_TickHandler.Remove(timer);

                RemoveTimer(id);
            }
        }

        /// <summary>
        /// 結束所有計時器
        /// </summary>
        public static void EndAllTimers(bool isRunExpiredEvent)
        {
            s_TickHandler.Clear();

            foreach (KeyValuePair<ulong, Timer> kp in s_ActiveTimers)
            {
                Timer timer = kp.Value;
                if (isRunExpiredEvent)
                {
                    timer.Execute();
                }
                s_Pool.Recycle(timer);
            }

            s_ActiveTimers.Clear();
        }

        private static bool TryGetTimer(ulong id, out Timer timer)
        {
            if (s_ActiveTimers.ContainsKey(id))
            {
                timer = s_ActiveTimers[id];

                return true;
            }

            timer = null;

            return false;
        }

        /// <summary>
        /// 移除計時器 (與結束計時器不同)
        ///     只負責回數計時器以及將其從Active列表移除
        /// </summary>
        private static void RemoveTimer(ulong id)
        {
            Timer timer = s_ActiveTimers[id];

            s_ActiveTimers.Remove(id);

            s_Pool.Recycle(timer);
        }

        /// <summary>
        /// 當Timer完成時 (Loop也結束)
        ///     由TickHandler調用
        /// </summary>
        private static void OnTimerCompleted(Timer timer)
        {
            RemoveTimer(timer.ID);
        }
    }
}
