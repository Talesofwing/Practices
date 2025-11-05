namespace DesignPattern.Component
{
	public abstract class MoveComponent : Component
	{
		protected float _speed;

		public MoveComponent(ObjectContainer owner, float speed) : base(owner)
		{
			_speed = speed;
		}

		public override void Update(float deltaTime) { }
	}
}
