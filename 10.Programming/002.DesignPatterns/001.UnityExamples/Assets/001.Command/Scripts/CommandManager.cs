using System.Collections.Generic;

using UnityEngine;

namespace DesignPattern.Command
{
	public class CommandManager
	{
		#region Singleton

		private static CommandManager instance;
		public static CommandManager Instance
		{
			get
			{
				if (instance == null)
				{
					instance = new CommandManager();
				}

				return instance;
			}
		}

		private CommandManager() { }

		#endregion

		private List<ICommand> _commands = new List<ICommand>();

		private int _curIndex = -1;

		public void Do(ICommand command)
		{
			command.Execute();

			if (_commands.Count > _curIndex + 1)
			{
				_commands[++_curIndex] = command;
			}
			else
			{
				_curIndex++;
				_commands.Add(command);
			}
		}

		public void Redo()
		{
			if (_curIndex < _commands.Count - 1)
			{
				_commands[++_curIndex].Execute();
			}
			else
			{
				Debug.LogWarning("Redo Failed!");
			}
		}

		public void Undo()
		{
			if (_curIndex >= 0 && _commands.Count > 0)
			{
				_commands[_curIndex--].Undo();
			}
			else
			{
				Debug.LogWarning("Undo Failed!");
			}
		}

		public void Clear()
		{
			_commands.Clear();
			_commands.TrimExcess();

			Debug.Log("Clear!");
		}

		public override string ToString()
		{
			string result = $"[CommandManager]\n\tCount: {_commands.Count}\tCurIndex: {_curIndex}\n\tCommands\n\t\t";
			for (int i = 0; i < _commands.Count; ++i)
			{
				result += _commands[i].ToString();
				if (i < _commands.Count - 1)
				{
					result += "\n\t\t";
				}
			}

			return result;
		}
	}
}
