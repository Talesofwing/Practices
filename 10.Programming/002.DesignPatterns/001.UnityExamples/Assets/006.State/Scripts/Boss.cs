using UnityEngine;

namespace DesignPattern.State
{
	public class Boss : MonoBehaviour
	{
		public int Hp;
		public int Atk;
		public int Speed;

		public bool AlreadyAngry = false;

		private BaseState _currentState;

		private void Start()
		{
			ChangeState(new NormalState(this));
		}

		public void Update()
		{
			_currentState.OnUpdate();
		}

		public void Attack()
		{
			_currentState.Attack();
		}

		public void TakeDamage(int damage)
		{
			_currentState.TakeDamage(damage);
		}

		public void Move()
		{
			_currentState.Move();
		}

		public void Die()
		{
			_currentState.Die();
		}

		public void ChangeState(BaseState state)
		{
			if (state == null)
			{
				return;
			}

			if (_currentState != null)
			{
				_currentState.OnExit();
			}

			_currentState = state;
			_currentState.OnEnter();
		}
	}
}
