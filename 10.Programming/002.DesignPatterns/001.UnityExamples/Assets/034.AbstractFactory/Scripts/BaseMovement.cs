namespace DesignPattern.AbstractFactory
{
	public abstract class BaseMovement
	{
		protected float _speed;

		public BaseMovement(float speed) { _speed = speed; }

		public abstract void Move();
	}
}
