using UnityEngine;

namespace DesignPattern.Strategy
{
	public class NoAttack : BaseAttack
	{
		public override void Attack()
		{
			Debug.Log("NoAttack");
		}
	}
}
