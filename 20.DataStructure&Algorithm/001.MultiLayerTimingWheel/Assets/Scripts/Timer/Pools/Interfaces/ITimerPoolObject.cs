namespace Timers.Pools
{
    /// <summary>
    /// 池物件接口
    ///     只用來限制函數使用
    /// </summary>
    public interface ITimerPoolObject
    {
        void OnGet();       // 取得時
        void OnReturn();    // 回收時
    }
}
