using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Assertions;

namespace DesignPattern.EventQueue
{
	public class AudioSystem
	{
		private const int MAX_EVENT_COUNT = 10;

		// Here we use a simple List to implement the event queue
		// Using a circular buffer instead could improve efficiency
		private class PlayEvent
		{
			public string SoundId;
			public float Volume;

			public PlayEvent(string soundId, float volume)
			{
				SoundId = soundId;
				Volume = volume;
			}
		}

		private readonly List<PlayEvent> _playEventQueue = new List<PlayEvent>();

		public void PlaySound(string soundId, float volume)
		{
			Assert.IsTrue(_playEventQueue.Count < MAX_EVENT_COUNT);

			foreach (var e in _playEventQueue)
			{
				if (e.SoundId == soundId)
				{
					e.Volume = Mathf.Max(e.Volume, volume);
					break;
				}
			}

			_playEventQueue.Add(new PlayEvent(soundId, volume));
		}

		public void Update()
		{
			foreach (var e in _playEventQueue)
			{
				Debug.Log("PlaySound: " + e.SoundId + " " + e.Volume);
			}

			_playEventQueue.Clear();
		}
	}
}
