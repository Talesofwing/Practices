namespace Timers.Pools
{
    /// <summary>
    /// 計時器池接口
    /// </summary>
    public interface ITimerPool
    {
        void Prewarm(int count);
        Timer Get();
        void Recycle(Timer timer);
        void Clear();
    }
}
