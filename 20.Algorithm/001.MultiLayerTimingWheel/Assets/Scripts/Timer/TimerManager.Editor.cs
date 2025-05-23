using System.Diagnostics;
using Timers.TickHandlers;
using Debug = UnityEngine.Debug;

namespace Timers
{
    public partial class TimerManager
    {
        [Conditional("UNITY_EDITOR")]
        public static void Debug_PrintPool()
        {
            Debug.Log(s_Pool);
        }

        [Conditional("UNITY_EDITOR")]
        public static void Debug_Tick(ulong tickMS)
        {
            Tick(tickMS);
        }

#if UNITY_EDITOR
        public static int Layer1SlotIndex => ((MultiLayerTimingWheelTickHandler)s_TickHandler).Layer1SlotIndex;
        public static int Layer2SlotIndex => ((MultiLayerTimingWheelTickHandler)s_TickHandler).Layer2SlotIndex;
        public static int Layer3SlotIndex => ((MultiLayerTimingWheelTickHandler)s_TickHandler).Layer3SlotIndex;
        public static int Layer4SlotIndex => ((MultiLayerTimingWheelTickHandler)s_TickHandler).Layer4SlotIndex;
        public static int Layer5SlotIndex => ((MultiLayerTimingWheelTickHandler)s_TickHandler).Layer5SlotIndex;
#endif // UNITY_EDITOR
    }
}
