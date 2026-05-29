using UnityEngine;

namespace DesignPattern.Component
{
	public class MagicAttackComponent : AttackComponent
	{
		public MagicAttackComponent(ObjectContainer owner, float atk, float cooldown) : base(owner, atk, cooldown) { }

		protected override void OnAttack()
		{
			Debug.Log("MagicAttackComponent OnAttack");
		}
	}
}
