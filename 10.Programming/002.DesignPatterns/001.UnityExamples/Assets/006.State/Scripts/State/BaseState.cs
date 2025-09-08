namespace DesignPattern.State
{
	public abstract class BaseState
	{
		protected Boss _owner;

		public BaseState(Boss boss) => _owner = boss;

		public abstract void OnEnter();
		public abstract void OnUpdate();
		public abstract void OnExit();

		public abstract void Attack();
		public abstract void TakeDamage(int damage);
		public abstract void Move();
		public abstract void Die();
	}
}

