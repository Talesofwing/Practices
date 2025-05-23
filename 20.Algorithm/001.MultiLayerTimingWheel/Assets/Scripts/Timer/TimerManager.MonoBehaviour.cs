using UnityEngine;

using Timers.TickHandlers;
using Timers.Pools;

namespace Timers
{
    /// <summary>
    /// 計時器管理 (幀率作為Tick，且使用MS)
    ///     處理MonoBehaviour事件
    /// </summary>
    public sealed partial class TimerManager
    {
        private void Awake()
        {
            s_Pool = new TimerPool(_defaultTimerPoolCount);

            // 每Tick間隔 (使用幀率)
            // ulong intervalMS = 1000 / (ulong)Application.targetFrameRate;        // Unity幀率作為tickInvervalMS
            s_TickHandler = new MultiLayerTimingWheelTickHandler(_tickIntervalMS);
            s_TickHandler.TimerCompleted += OnTimerCompleted;
        }

        private void Update()
        {
            if (IsRunning)
            {
                float dt = Time.deltaTime;
                ulong dtMS = (ulong)(dt * 1000);
                Tick(dtMS);
            }
        }
    }
}
