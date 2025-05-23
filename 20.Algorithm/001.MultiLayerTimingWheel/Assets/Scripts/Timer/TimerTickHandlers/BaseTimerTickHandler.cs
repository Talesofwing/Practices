using System;

namespace Timers.TickHandlers
{
    /// <summary>
    /// 計時處理器基類
    /// </summary>
    public abstract class BaseTimerTickHandler
    {
        protected ulong _tickIntervalMS = 0;
        protected uint _currentTick = 0;

        public ulong CurrentTick => _currentTick;

        public event Action<Timer> TimerCompleted;          // 當計時器結束時觸發

        public BaseTimerTickHandler(ulong tickIntervalMS)
        {
            _tickIntervalMS = tickIntervalMS;
        }

        public void Tick(ulong totalMS)
        {
            OnTick(totalMS);
        }
        protected abstract void OnTick(ulong totalMS);

        public void Insert(Timer timer)
        {
            OnInsert(timer);
        }
        protected virtual void OnInsert(Timer timer) { }

        /// <summary>
        /// 刷新
        ///     當計時器結束時間發生變化時使用
        /// </summary>
        public void Refresh(Timer timer)
        {
            OnRefresh(timer);
        }
        protected virtual void OnRefresh(Timer timer) { }

        public void Remove(Timer timer)
        {
            OnRemove(timer);
        }
        protected virtual void OnRemove(Timer timer) { }

        public void Clear()
        {
            OnClear();
        }
        protected virtual void OnClear() { }

        /// <summary>
        /// 計時器完成時調用
        /// </summary>
        protected virtual void OnTimerCompleted(Timer timer)
        {
            Remove(timer);

            TimerCompleted?.Invoke(timer);
        }
    }
}
