namespace DesignPattern.Component
{
	public abstract class AttackComponent : Component
	{
		protected float _atk;
		protected float _cooldown;

		protected float _timer;

		public AttackComponent(ObjectContainer owner, float atk, float cooldown) : base(owner)
		{
			_atk = atk;
			_cooldown = cooldown;
			_timer = 0f;
		}

		public override void Update(float deltaTime)
		{
			_timer += deltaTime;
			if (_timer >= _cooldown)
			{
				_timer -= _cooldown;

				OnAttack();
			}
		}

		protected virtual void OnAttack() { }
	}
}
