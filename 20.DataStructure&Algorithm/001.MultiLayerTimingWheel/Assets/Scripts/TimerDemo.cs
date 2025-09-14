using System.Collections.Generic;

using UnityEngine;
using UnityEngine.UI;

using Sirenix.OdinInspector;

using Timers;
using Timers.Events;

public class TimerDemo : MonoBehaviour
{
    // 快速轉換(ms <-> s); 1:ms, 1000:s
    private const int c_TimeFactor = 1000;

    [SerializeField, PropertyOrder(-10000)]
    private UI _ui = null;
    [SerializeField, PropertyOrder(-10000)]
    private bool _blockRefresh = false;         // 在Debug的情況下，如果Timer數量過多，每次Refresh對性能有影響

    private void Update()
    {
        _ui.TimerMSText.text = TimerManager.CurrentMS.ToString();
        _ui.TimerSText.text = (TimerManager.CurrentMS / 1000f).ToString();
        _ui.TickText.text = TimerManager.CurrentTick.ToString();
        _ui.Layer1SlotText.text = TimerManager.Layer1SlotIndex.ToString();
        _ui.Layer2SlotText.text = TimerManager.Layer2SlotIndex.ToString();
        _ui.Layer3SlotText.text = TimerManager.Layer3SlotIndex.ToString();
        _ui.Layer4SlotText.text = TimerManager.Layer4SlotIndex.ToString();
        _ui.Layer5SlotText.text = TimerManager.Layer5SlotIndex.ToString();

        if (!_blockRefresh)
        {
            RefreshInfos();
        }
    }

    #region Debug

    [SerializeField, PropertyOrder(-100), FoldoutGroup("Debug"), ReadOnly]
    private List<TimerInfo> _timerInfos = new List<TimerInfo>();

    private void RefreshInfos()
    {
        foreach (TimerInfo timerInfo in _timerInfos)
        {
            timerInfo.Refresh();
        }
    }

    [SerializeField, FoldoutGroup("Debug"), FoldoutGroup("Debug/Start - End Timer")]
    private string _name = "Timer";
    [SerializeField, FoldoutGroup("Debug"), FoldoutGroup("Debug/Start - End Timer")]
    private float _expireTimeS;
    [SerializeField, FoldoutGroup("Debug"), FoldoutGroup("Debug/Start - End Timer")]
    private int _loopCount;
    [SerializeField, FoldoutGroup("Debug"), FoldoutGroup("Debug/Start - End Timer")]
    private float _loopIntervalS;

    [Button, PropertyOrder(1), FoldoutGroup("Debug"), FoldoutGroup("Debug/Start - End Timer")]
    private void StartTimer()
    {
        if (!CommonCheck())
        {
            return;
        }

        if (_expireTimeS < 0)
        {
            Debug.LogWarning("[StartTimer] ExpireTime must be greater than or equal to 0.");

            return;
        }

        CustomizeTimerArgs customizeTimerArgs = new CustomizeTimerArgs { Name = _name + $"({_expireTimeS})" };
        ulong expireMS = (ulong)(_expireTimeS * c_TimeFactor);
        ulong loopIntervalMS = (ulong)(_loopIntervalS * c_TimeFactor);
        ulong id = TimerManager.StartTimer(expireMS, _loopCount, loopIntervalMS, customizeTimerArgs, OnTimerExpired);

        _timerInfos.Add(new TimerInfo(TimerManager.ActiveTimers[id]));
    }

    [SerializeField, PropertyOrder(2), FoldoutGroup("Debug"), FoldoutGroup("Debug/Start - End Timer")]
    private ulong _timerID = 0;
    [SerializeField, PropertyOrder(3), FoldoutGroup("Debug"), FoldoutGroup("Debug/Start - End Timer")]
    private bool _isRunExpiredEvent = true;

    [Button, PropertyOrder(4), FoldoutGroup("Debug"), FoldoutGroup("Debug/Start - End Timer")]
    private void EndTimer()
    {
        if (!CommonCheck())
        {
            return;
        }

        TimerManager.EndTimer(_timerID, _isRunExpiredEvent);

        _timerInfos.Remove(_timerInfos.Find(timerInfo => timerInfo.ID == _timerID));
    }

    [Button, PropertyOrder(4), FoldoutGroup("Debug"), FoldoutGroup("Debug/Start - End Timer")]
    private void EndAllTimers()
    {
        if (!CommonCheck())
        {
            return;
        }

        TimerManager.EndAllTimers(_isRunExpiredEvent);

        _timerInfos.Clear();
    }

    [SerializeField, FoldoutGroup("Debug"), FoldoutGroup("Debug/Tick")]
    private float _tickS = 0;

    [Button, FoldoutGroup("Debug"), FoldoutGroup("Debug/Tick")]
    private void Tick()
    {
        if (!CommonCheck())
        {
            return;
        }

        TimerManager.Debug_Tick((ulong)(_tickS * c_TimeFactor));
    }

    [SerializeField, FoldoutGroup("Debug"), FoldoutGroup("Debug/Reset")]
    private ulong _resetTimerID;
    [SerializeField, FoldoutGroup("Debug"), FoldoutGroup("Debug/Reset")]
    private int _resetLoopCount;
    [SerializeField, FoldoutGroup("Debug"), FoldoutGroup("Debug/Reset")]
    private bool _isResetLoopedCount = false;
    [SerializeField, FoldoutGroup("Debug"), FoldoutGroup("Debug/Reset")]
    private long _extraExpireS = 0;

    [Button, FoldoutGroup("Debug"), FoldoutGroup("Debug/Reset")]
    private void ResetLoopCount()
    {
        if (!CommonCheck())
        {
            return;
        }

        TimerManager.SetTimerLoopCount(_resetTimerID, _resetLoopCount, _isResetLoopedCount);
    }

    [Button, FoldoutGroup("Debug"), FoldoutGroup("Debug/Reset")]
    private void AddExpireTime()
    {
        if (!CommonCheck())
        {
            return;
        }

        TimerManager.AddTimerExpireTick(_resetTimerID, (ulong)(_extraExpireS * c_TimeFactor));
    }

    private void OnTimerExpired(Timer sender, ExpiredEventArgs args, TimerArgs timerArgs)
    {
        if (timerArgs is CustomizeTimerArgs customizeTimerArgs)
        {
            Debug.Log($"Timer Expired: {customizeTimerArgs.Name}");
        }

        if (sender.IsCompleted)
        {
            _timerInfos.Remove(_timerInfos.Find(timerInfo => timerInfo.ID == sender.ID));
        }
    }

    private bool CommonCheck()
    {
        if (Application.isPlaying)
        {
            return true;
        }
        else
        {
            Debug.LogWarning("Please play the game.");

            return false;
        }
    }

    [System.Serializable]
    private class TimerInfo
    {
        // 因為Timer不能序列化
        // 額外創建TimerInfo進行序列化

        public Timer Timer;

        // 顯示用
        public ulong ID;
        public ulong ExpireMS;
        public int LoopCount;
        public uint LoopedCount;
        public ulong LoopIntervalMS;
        public int Layer;
        public int SlotIndex;
        public ulong ExpireTick;

        public TimerInfo(Timer timer)
        {
            Timer = timer;

            ID = timer.ID;
            ExpireMS = timer.ExpireMS;
            LoopCount = timer.LoopCount;
            LoopedCount = timer.LoopedCount;
            LoopIntervalMS = timer.LoopIntervalMS;
            Layer = timer.Layer;
            SlotIndex = timer.SlotIndex;
            ExpireTick = timer.ExpireTick;
        }

        public void Refresh()
        {
            ID = Timer.ID;
            ExpireMS = Timer.ExpireMS;
            LoopCount = Timer.LoopCount;
            LoopedCount = Timer.LoopedCount;
            LoopIntervalMS = Timer.LoopIntervalMS;
            Layer = Timer.Layer;
            SlotIndex = Timer.SlotIndex;
            ExpireTick = Timer.ExpireTick;
        }
    }

    #endregion
}
