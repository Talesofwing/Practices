using UnityEngine;

namespace DesignPattern.Command
{
	public class AttackCommand : ActionCommand
	{
		public override void Execute()
		{
			Debug.Log("Attack Executed!");
		}

		public override void Undo()
		{
			Debug.Log("Attack Undo!");
		}
	}
}
