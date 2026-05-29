using UnityEngine;

namespace DesignPattern.DirtyFlag
{
	public class DirtyFlagUse : MonoBehaviour
	{
		[SerializeField]
		private float _saveInterval = 5f;

		private SaveSystem _saveSystem;

		private Player _player;

		private float _timer = 0f;

		private void Start()
		{
			_saveSystem = new SaveSystem();
			_player = _saveSystem.Load();
		}

		private void Update()
		{
			_timer += Time.deltaTime;
			if (_timer >= _saveInterval)
			{
				_saveSystem.Save();
				_timer = 0f;
			}

			if (Input.GetKeyDown(KeyCode.Space))
			{
				_player.Position += new Vector3(1, 0, 0);
				_saveSystem.SetPlayer(_player);
				Debug.Log("Player position: " + _player.Position);
			}
		}
	}
}
