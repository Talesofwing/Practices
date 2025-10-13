using UnityEngine;

namespace DesignPattern.Strategy
{
	public class RangedAttack : BaseAttack
	{
		public override void Attack()
		{
			Debug.Log("RangedAttack");
		}
	}
}
