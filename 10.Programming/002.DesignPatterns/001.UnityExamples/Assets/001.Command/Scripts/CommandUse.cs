using UnityEngine;

namespace DesignPattern.Command
{
	/// <summary>
	/// As client & invoker
	/// </summary>
	public class CommandUse : MonoBehaviour
	{
		private bool _isJump = false;


		private void Start()
		{
			GenerateCommand();
		}

		private void Update()
		{
			if (Input.GetKeyDown(KeyCode.Space))
			{
				_isJump = !_isJump;

				Debug.Log("Switch Command: " + (_isJump ? "Jump" : "Attack"));
			}
			else if (Input.GetKeyDown(KeyCode.E))
			{
				CommandManager.Instance.Do(GenerateCommand());
			}
			else if (Input.GetKeyDown(KeyCode.U))
			{
				CommandManager.Instance.Undo();
			}
			else if (Input.GetKeyDown(KeyCode.R))
			{
				CommandManager.Instance.Redo();
			}
			else if (Input.GetKeyDown(KeyCode.C))
			{
				CommandManager.Instance.Clear();
			}
			else if (Input.GetKeyDown(KeyCode.D))
			{
				Debug.Log(CommandManager.Instance);
			}
		}

		private ICommand GenerateCommand()
		{
			if (_isJump)
			{
				return new JumpCommand();
			}
			else
			{
				return new AttackCommand();
			}
		}
	}
}
