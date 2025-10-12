using UnityEngine;

namespace DesignPattern.Memento
{
	/// <summary>
	/// Originator - creates and restores mementos of its internal state
	/// </summary>
	public class GameManager : MonoBehaviour
	{
		private int _score = 0;
		private int _level = 1;

		public int Score => _score;
		public int Level => _level;

		public void AddScore(int score)
		{
			_score += score;

			Debug.Log($"[GameManager] Add score - Score: {_score}");
		}

		public void LevelUp()
		{
			_level++;

			Debug.Log($"[GameManager] Level up - Level: {_level}");
		}

		public IMemento CreateMemento()
		{
			Debug.Log($"[GameManager] Creating memento - Score: {_score}, Level: {_level}");

			return new Memento(_score, _level);
		}

		public void RestoreMemento(IMemento memento)
		{
			if (memento is Memento snapshot)
			{
				_score = snapshot.Score;
				_level = snapshot.Level;
				Debug.Log($"[GameManager] State restored - Score: {_score}, Level: {_level}");
			}
		}

		/// <summary>
		/// Snapshot - concrete memento implementation
		/// Private nested class to prevent external access to state
		/// </summary>
		private class Memento : IMemento
		{
			public int Score { get; }
			public int Level { get; }

			public Memento(int score, int level)
			{
				Score = score;
				Level = level;
			}
		}
	}
}
