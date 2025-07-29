using UnityEngine;

namespace DesignPattern.Observer
{
	public class Observer : MonoBehaviour
	{
		private bool _isSubscribed = false;

		private void Update()
		{
			if (Input.GetKeyDown(KeyCode.S))
			{
				if (_isSubscribed)
				{
					EventBus.Unsubscribe<LogEvent>(OnLogEvent);
					_isSubscribed = false;

					Debug.Log("Unsubscribed!");
				}
				else
				{
					EventBus.Subscribe<LogEvent>(OnLogEvent);
					_isSubscribed = true;

					Debug.Log("Subscribed!");
				}
			}
		}

		private void OnLogEvent(in LogEvent e)
		{
			Debug.Log(e.Message);
		}
	}
}
