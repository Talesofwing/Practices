using System;
using System.Collections.Generic;

namespace Timers.TickHandlers
{
	/// <summary>
	/// 多層結構時間輪計時處理器
	///  	Layer : 層
	/// 	Slot : 層裏的槽口
	/// </summary>
	public partial class MultiLayerTimingWheelTickHandler : BaseTimerTickHandler
	{
		private const int c_LayerCount = 5;                                 // 層數
		private const int c_HeadLayerSlotBit = 8;                           // 頭層位數 (第1層)
		private const int c_LayerSlotBit = 6;                               // 其他層位數 (第2層~第5層)
		private const int c_HeadLayerSlotCount = 1 << c_HeadLayerSlotBit;   // 頭層槽數 (第1層)
		private const int c_LayerSlotCount = 1 << c_LayerSlotBit;           // 其他層槽數 (第2層~第5層)
		private const int c_HeadLayerSlotMask = c_HeadLayerSlotCount - 1;   // 頭層遮罩 (第1層)
		private const int c_LayerSlotMask = c_LayerSlotCount - 1;           // 其他層遮罩 (第2層~第5層)

		private TimingWheel[] _multiLayerTimingWheel;

		// 因為Timer自身不知道自己是Node (為了能使用多種不同的TickHandler)
		// 所以由TickHandler額外管理Timer的Node
		private Dictionary<ulong, TimingWheelTimer> _activeTimingWheelTimers = new Dictionary<ulong, TimingWheelTimer>();

		public MultiLayerTimingWheelTickHandler(ulong tickIntervalMS) : base(tickIntervalMS)
		{
			// 初始化多層結構時間輪
			_multiLayerTimingWheel = new TimingWheel[c_LayerCount];
			for (int i = 0; i < c_LayerCount; ++i)
			{
				int slotCount = i == 0 ? c_HeadLayerSlotCount : c_LayerSlotCount;
				LinkedList<TimingWheelTimer>[] slots = new LinkedList<TimingWheelTimer>[slotCount];

				for (int j = 0; j < slotCount; ++j)
				{
					slots[j] = new LinkedList<TimingWheelTimer>();
				}

				_multiLayerTimingWheel[i] = new TimingWheel
				{
					SlotIndex = 0,
					Slots = slots
				};
			}
		}

		protected override void OnTick(ulong totalMS)
		{
			// 多層結構時間輪不需要使用具體時間
			// 計算Tick多少次
			uint totalTickCount = (uint)(totalMS / _tickIntervalMS - _currentTick);
			for (uint i = 0; i < totalTickCount; ++i)
			{
				// 執行第0層的Slot
				TimingWheel headLayer = _multiLayerTimingWheel[0];
				LinkedList<TimingWheelTimer> headLayerSlot = headLayer.Slots[headLayer.SlotIndex];
				ExpiredSlotHandler(headLayerSlot);

				_currentTick++;
				headLayer.SlotIndex = (headLayer.SlotIndex + 1) & c_HeadLayerSlotMask;  // mask為2次冪，所以可以使用&取代%
				if (headLayer.SlotIndex == 0)
				{
					// Cascade處理
					CascadeHandler();
				}
			}
		}
		protected virtual void ExpiredSlotHandler(LinkedList<TimingWheelTimer> slot)
		{
			LinkedListNode<TimingWheelTimer> node = slot.First;
			while (node != null)
			{
				TimingWheelTimer timingWheelTimer = node.Value;
				timingWheelTimer.Execute();

				node = node.Next;   // 要先獲取下一個Node

				if (timingWheelTimer.IsCompleted)
				{
					// 計時器已完成

					OnTimerCompleted(timingWheelTimer.Timer);
				}
				else
				{
					// 計時器未完成，進行循環計時器處理

					Insert(timingWheelTimer.Timer);
				}
			}
			slot.Clear();
		}

		protected virtual void CascadeHandler()
		{
			int layerIndex = 1;
			while (layerIndex < c_LayerCount)
			{
				// 從第2層開始，如果SlotIndex為0則進入下一層
				TimingWheel layer = _multiLayerTimingWheel[layerIndex];
				layer.SlotIndex = (layer.SlotIndex + 1) & c_LayerSlotMask;

				if (layer.SlotIndex == 0)
				{
					layerIndex++;
				}
				else
				{
					// 將Slot中的Timers全部下降一層
					LinkedList<TimingWheelTimer> slot = layer.Slots[layer.SlotIndex];
					LinkedListNode<TimingWheelTimer> node = slot.First;
					while (node != null)
					{
						TimingWheelTimer timingWheelTimer = node.Value;
						Insert(timingWheelTimer.Timer);
						node = node.Next;
					}
					slot.Clear();

					break;
				}
			}
		}

		protected override void OnInsert(Timer timer)
		{
			base.OnInsert(timer);

			TimingWheelTimer timingWheelTimer = null;
			if (_activeTimingWheelTimers.ContainsKey(timer.ID))
			{
				timingWheelTimer = _activeTimingWheelTimers[timer.ID];
			}
			else
			{
				timingWheelTimer = new TimingWheelTimer();
				_activeTimingWheelTimers.Add(timer.ID, timingWheelTimer);
			}
			timingWheelTimer.Setup(timer, _tickIntervalMS);

			// 將ms轉換為tick
			uint expireTick = (timingWheelTimer.ExpiredTick + timingWheelTimer.LoopedCount * timingWheelTimer.LoopIntervalTick);
			uint index = expireTick - _currentTick;

#if UNITY_EDITOR
			int layer = 0;
#endif // UNITY_EDITOR

			int slotIndex = 0;
			LinkedList<TimingWheelTimer> targetSlot;
			if (index < 1 << c_HeadLayerSlotBit)
			{
				// 第一層

				slotIndex = (int)(expireTick & c_HeadLayerSlotMask);
				targetSlot = _multiLayerTimingWheel[0].Slots[slotIndex];

#if UNITY_EDITOR
				layer = 1;
#endif // UNITY_EDITOR

			}
			else if (index < 1 << (c_HeadLayerSlotBit + c_LayerSlotBit))
			{
				// 第二層

				slotIndex = (int)((expireTick >> c_HeadLayerSlotBit) & c_LayerSlotMask);
				targetSlot = _multiLayerTimingWheel[1].Slots[slotIndex];

#if UNITY_EDITOR
				layer = 2;
#endif // UNITY_EDITOR

			}
			else if (index < 1 << (c_HeadLayerSlotBit + c_LayerSlotBit * 2))
			{
				// 第三層

				slotIndex = (int)((expireTick >> (c_HeadLayerSlotBit + c_LayerSlotBit)) & c_LayerSlotMask);
				targetSlot = _multiLayerTimingWheel[2].Slots[slotIndex];

#if UNITY_EDITOR
				layer = 3;
#endif // UNITY_EDITOR

			}
			else if (index < 1 << (c_HeadLayerSlotBit + c_LayerSlotBit * 3))
			{
				// 第四層

				slotIndex = (int)((expireTick >> (c_HeadLayerSlotBit + c_LayerSlotBit * 2)) & c_LayerSlotMask);
				targetSlot = _multiLayerTimingWheel[3].Slots[slotIndex];

#if UNITY_EDITOR
				layer = 4;
#endif // UNITY_EDITOR

			}
			else if ((int)index < 0)   // 位數問題，要先判斷ulong是否為負數
			{
				// 修改計時器的IntervalMS時(用於循環)，可能會導致Timer的ExpireMS小於當前的時間
				// 此時應立刻執行，因此放入到當前tick的slot中
				slotIndex = _multiLayerTimingWheel[0].SlotIndex;
				targetSlot = _multiLayerTimingWheel[0].Slots[slotIndex];

#if UNITY_EDITOR
				layer = 1;
#endif // UNITY_EDITOR

			}
			else if (index <= 0xffffffffUL)
			{
				// 第五層

				slotIndex = (int)((expireTick >> (c_HeadLayerSlotBit + c_LayerSlotBit * 3)) & c_LayerSlotMask);
				targetSlot = _multiLayerTimingWheel[4].Slots[slotIndex];

#if UNITY_EDITOR
				layer = 5;
#endif // UNITY_EDITOR

			}
			else
			{
				// 超出計時器範圍，放入第5層最後一個Slot
				slotIndex = c_LayerSlotCount - 1;
				targetSlot = _multiLayerTimingWheel[4].Slots[slotIndex];

#if UNITY_EDITOR
				layer = 5;
#endif // UNITY_EDITOR

			}

#if UNITY_EDITOR
			timer.Layer = layer;             // layer由1開始
			timer.SlotIndex = slotIndex + 1; // slot由0開始
			timer.ExpireTick = expireTick;
#endif // UNITY_EDITOR

			targetSlot.AddLast(timingWheelTimer);
			timingWheelTimer.Node = targetSlot.Last;
		}

		protected override void OnRefresh(Timer timer)
		{
			base.OnRefresh(timer);

			// Timer中的ExpireTick小於當前Tick的情況由Insert處理
			Remove(timer);
			Insert(timer);
		}

		protected override void OnRemove(Timer timer)
		{
			base.OnRemove(timer);

			TimingWheelTimer timingWheelTimer = _activeTimingWheelTimers[timer.ID];
			LinkedList<TimingWheelTimer> slot = timingWheelTimer.Node.List;
			slot.Remove(timingWheelTimer.Node);

			_activeTimingWheelTimers.Remove(timer.ID);
		}

		protected override void OnClear()
		{
			base.OnClear();

			for (int i = 0; i < c_LayerCount; ++i)
			{
				LinkedList<TimingWheelTimer>[] slots = _multiLayerTimingWheel[i].Slots;
				for (int j = 0; j < slots.Length; ++j)
				{
					slots[j].Clear();
				}
			}

			_activeTimingWheelTimers.Clear();
		}

		protected class TimingWheel
		{
			public int SlotIndex;       // 當前Slot索引
			public LinkedList<TimingWheelTimer>[] Slots;
		}

		/// <summary>
		/// Adapter Pattern
		///     專門用於TimingWheel的Timer
		///     如果只想使用ms/s進行計時，而不是通過TimingWheel進行計時的話，就可以直接使用Timer
		///     這樣可以在不污染Timer的情況下，進行TimingWheel的計時
		/// </summary>
		protected class TimingWheelTimer
		{
			public Timer Timer;

			// TimingWheel只支持32位數，所以Tick的最大值是2^32 - 1
			// 在Timer中，ExpireMS的最大值是2^64 - 1，可能會導致溢出
			// 所以需要抑制ExpireMS的最大值
			public uint ExpiredTick;
			public uint LoopIntervalTick;
			public LinkedListNode<TimingWheelTimer> Node;

			public uint LoopedCount => Timer.LoopedCount;
			public bool IsCompleted => Timer.IsCompleted;

			public void Setup(Timer timer, ulong tickIntervalMS)
			{
				Timer = timer;

				// 限制Tick最大值為2^32 - 1
				ExpiredTick = (uint)Math.Min(timer.ExpireMS / tickIntervalMS, uint.MaxValue);
				LoopIntervalTick = (uint)Math.Min(timer.LoopIntervalMS / tickIntervalMS, uint.MaxValue);
			}

			public void Execute()
			{
				Timer.Execute();
			}
		}

#if UNITY_EDITOR
		public int Layer1SlotIndex => _multiLayerTimingWheel[0].SlotIndex + 1;
		public int Layer2SlotIndex => _multiLayerTimingWheel[1].SlotIndex + 1;
		public int Layer3SlotIndex => _multiLayerTimingWheel[2].SlotIndex + 1;
		public int Layer4SlotIndex => _multiLayerTimingWheel[3].SlotIndex + 1;
		public int Layer5SlotIndex => _multiLayerTimingWheel[4].SlotIndex + 1;
#endif // UNITY_EDITOR
	}
}
