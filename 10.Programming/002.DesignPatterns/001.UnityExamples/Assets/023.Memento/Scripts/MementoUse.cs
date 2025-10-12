using UnityEngine;

namespace DesignPattern.Memento
{
	public class MementoUse : MonoBehaviour
	{
		[SerializeField]
		private GameManager _gameManager;

		private GameHistory _history;

		private void Start()
		{
			_history = new GameHistory();
		}

		private void Update()
		{
			if (Input.GetKeyDown(KeyCode.Space))
			{
				_history.CreateSnapshot(_gameManager);
			}
			else if (Input.GetKeyDown(KeyCode.U))
			{
				_gameManager.AddScore(10);
			}
			else if (Input.GetKeyDown(KeyCode.L))
			{
				_gameManager.LevelUp();
			}
			else if (Input.GetKeyDown(KeyCode.R))
			{
				_history.RestoreSnapshot(_gameManager);
			}
		}
	}
}
