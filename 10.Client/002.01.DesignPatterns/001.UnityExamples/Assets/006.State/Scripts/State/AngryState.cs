using UnityEngine;

namespace DesignPattern.State
{
	public class AngryState : BaseState
	{
		private float _timer = 0f;

		public AngryState(Boss boss) : base(boss) { }

		public override void OnEnter()
		{
			Debug.Log("AngryState Enter");

			_timer = 0f;
		}

		public override void OnUpdate()
		{
			Debug.Log("AngryState Update");

			_timer += Time.deltaTime;
			if (_timer >= 3f)
			{
				_owner.ChangeState(new NormalState(_owner));
			}
		}

		public override void OnExit()
		{
			Debug.Log("AngryState Exit");
		}

		public override void Attack()
		{
			// double attack
			Debug.Log("AngryState Attack: " + _owner.Atk * 2);
		}

		public override void TakeDamage(int damage)
		{
			// ignore damage
			Debug.Log("AngryState ignore damage");
		}

		public override void Move()
		{
			// double speed
			Debug.Log("AngryState Move: " + _owner.Speed * 2);
		}

		public override void Die()
		{
			// don't die
			Debug.Log("AngryState Don't Die");
		}
	}
}

