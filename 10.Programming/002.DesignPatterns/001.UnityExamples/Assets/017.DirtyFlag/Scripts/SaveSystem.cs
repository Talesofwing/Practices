using UnityEngine;

namespace DesignPattern.DirtyFlag
{
	public class SaveSystem
	{
		private Player _player = null;

		private bool _isDirty = false;

		public void SetPlayer(Player player)
		{
			_player = player;
			SetDirty();
		}

		public void SetDirty()
		{
			_isDirty = true;
		}

		public void Save()
		{
			if (_isDirty)
			{
				Debug.Log("Save player: " + _player.Name + " at " + _player.Position);
				_isDirty = false;
			}
			else
			{
				Debug.Log("Player is not dirty, no need to save");
			}
		}

		public Player Load()
		{
			_player = new Player { Name = "Player", Position = new Vector3(0, 0, 0) };
			return _player;
		}
	}
}
