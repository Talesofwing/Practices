using System.Collections.Generic;

namespace Timers.Pools
{
    /// <summary>
    /// 計時器池實例
    /// </summary>
    public class TimerPool : ITimerPool
    {
        private const int c_MaxTimerCount = 1000000;

        private Queue<Timer> _pool;

        public TimerPool(int defaultCount)
        {
            _pool = new Queue<Timer>(defaultCount);

            Prewarm(defaultCount);
        }

        public void Prewarm(int count)
        {
            if (_pool.Count + count >= c_MaxTimerCount)
            {
                count = c_MaxTimerCount - _pool.Count;
            }

            for (int i = 0; i < count; i++)
            {
                _pool.Enqueue(new Timer());
            }
        }

        public Timer Get()
        {
            if (_pool.Count > 0)
            {
                Timer timer = _pool.Dequeue();
                ((ITimerPoolObject)timer).OnGet();
                return timer;
            }
            else
            {
                return new Timer();
            }
        }

        public void Recycle(Timer timer)
        {
            if (_pool.Count < c_MaxTimerCount)
            {
                ((ITimerPoolObject)timer).OnReturn();

                _pool.Enqueue(timer);
            }
        }

        public void Clear()
        {
            _pool.Clear();
        }

        public override string ToString()
        {
            return $"PoolCount: " + _pool.Count;
        }
    }
}
