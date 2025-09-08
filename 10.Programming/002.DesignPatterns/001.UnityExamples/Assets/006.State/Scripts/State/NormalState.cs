using UnityEngine;

namespace DesignPattern.State
{
	public class NormalState : BaseState
	{
		public NormalState(Boss boss) : base(boss) { }

		public override void OnEnter()
		{
			Debug.Log("NormalState Enter");
		}

		public override void OnUpdate()
		{
			Debug.Log("NormalState Update");
		}

		public override void OnExit()
		{
			Debug.Log("NormalState Update");
		}

		public override void Attack()
		{
			Debug.Log("NormalState Attack");
		}

		public override void TakeDamage(int damage)
		{
			Debug.Log("NormalState TakeDamage: " + damage);

			_owner.Hp -= damage;
			if (_owner.Hp <= 50 && !_owner.AlreadyAngry)
			{
				_owner.AlreadyAngry = true;
				_owner.ChangeState(new AngryState(_owner));
			}
			else if (_owner.Hp <= 0)
			{
				_owner.Die();
			}
		}

		public override void Move()
		{
			Debug.Log("NormalState Move: " + _owner.Speed);
		}

		public override void Die()
		{
			Debug.Log("NormalState Die: " + _owner.Hp);
		}
	}
}

