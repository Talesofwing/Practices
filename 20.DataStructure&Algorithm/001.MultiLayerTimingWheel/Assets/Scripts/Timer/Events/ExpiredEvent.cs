using System;

namespace Timers.Events
{
    /// <summary>
    /// 計時器到期事件參數
    /// </summary>
    public sealed class ExpiredEventArgs : EventArgs { }

    /// <summary>
    /// 計時器到期事件
    /// </summary>
    public delegate void ExpiredEventHandler(Timer sender, ExpiredEventArgs e, TimerArgs args);

    /// <summary>
    /// 計時器參數 (由用戶傳遞給Timer，並在Expired中使用)
    /// </summary>
    public abstract class TimerArgs { }
}
