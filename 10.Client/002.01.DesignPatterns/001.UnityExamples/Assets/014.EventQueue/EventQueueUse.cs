using UnityEngine;

namespace DesignPattern.EventQueue
{
	public class EventQueueUse : MonoBehaviour
	{
		private AudioSystem _audioSystem;

		private void Start()
		{
			_audioSystem = new AudioSystem();
		}

		private void Update()
		{
			if (Input.GetKeyDown(KeyCode.Space))
			{
				_audioSystem.PlaySound("Sound1", Random.Range(0.5f, 1.0f));
			}

			_audioSystem.Update();
		}
	}
}
