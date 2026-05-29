using UnityEngine;

namespace DesignPattern.Observer
{
	public class Publisher : MonoBehaviour
	{
		private void Update()
		{
			if (Input.GetKeyDown(KeyCode.Space))
			{
				Debug.Log("Publish");

				LogEvent e = new LogEvent("Log Event");
				EventBus.Publish(e);
			}
		}
	}
}
