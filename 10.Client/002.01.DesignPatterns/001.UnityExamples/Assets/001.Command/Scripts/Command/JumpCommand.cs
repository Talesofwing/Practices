using UnityEngine;

namespace DesignPattern.Command
{
	public class JumpCommand : ActionCommand
	{
		public override void Execute()
		{
			Debug.Log("Jump Executed!");
		}

		public override void Undo()
		{
			Debug.Log("Jump Undo!");
		}
	}
}
