using System.Collections.Generic;
using UnityEngine;

namespace DesignPattern.Memento
{
	/// <summary>
	/// Caretaker - responsible for storing and managing mementos
	/// Does not examine or modify the memento's content
	/// </summary>
	public class GameHistory
	{
		private Stack<IMemento> _history = new Stack<IMemento>();

		public void CreateSnapshot(GameManager gameManager)
		{
			IMemento memento = gameManager.CreateMemento();
			_history.Push(memento);

			Debug.Log($"[GameHistory] Snapshot saved. Total snapshots: {_history.Count}");
		}

		public bool RestoreSnapshot(GameManager gameManager)
		{
			if (_history.Count > 0)
			{
				IMemento memento = _history.Pop();
				gameManager.RestoreMemento(memento);
				return true;
			}

			Debug.Log("[GameHistory] No snapshots to restore!");

			return false;
		}

		public bool CanUndo => _history.Count > 0;
		public int SnapshotCount => _history.Count;
	}
}

