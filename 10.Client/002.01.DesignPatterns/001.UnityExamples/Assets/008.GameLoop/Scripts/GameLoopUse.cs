using UnityEngine;

namespace DesignPattern.GameLoop
{
	public class GameLoopUse : MonoBehaviour
	{
		[SerializeField]
		private float _fixedDeltaTimer = 0.02f;

		private double _fixedTime = 0;

		private void Update()
		{
			double current = Time.time;
			HandleInput();
			_fixedTime += Time.deltaTime;
			while (_fixedTime >= _fixedDeltaTimer)
			{
				UpdateGame(_fixedDeltaTimer);
				_fixedTime -= _fixedDeltaTimer;
			}
			Render(_fixedTime / _fixedDeltaTimer);
		}

		private void HandleInput()
		{
			Debug.Log("HandleInput");
		}

		private void UpdateGame(double fixedDeltaTime)
		{
			Debug.Log("UpdateGame: " + fixedDeltaTime);
		}

		private void Render(double deltaTime)
		{
			Debug.Log("Render: " + deltaTime);
		}
	}
}
