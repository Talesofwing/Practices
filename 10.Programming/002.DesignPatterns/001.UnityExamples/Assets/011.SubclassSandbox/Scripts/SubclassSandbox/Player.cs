using UnityEngine;

namespace DesignPattern.SubclassSandbox
{
	/// <summary>
	/// Implements the sandbox method and controls the execution flow.
	/// </summary>
	public class Player : BaseEntity
	{
		public override void Attack()
		{
			Debug.Log("Player Attack");

			PlayEffect("PlayerAttack");
			PlaySound("PlayerAttack");
			PlayAnimation("PlayerAttack");
		}

		public override void TakeDamage(int damage)
		{
			Debug.Log("Player TakeDamage: " + damage);

			PlayEffect("PlayerTakeDamage");
			PlaySound("PlayerTakeDamage");
			PlayAnimation("PlayerTakeDamage");
		}
	}
}
