namespace DesignPattern.AbstractFactory
{
	public class FlyMovement : BaseMovement
	{
		public FlyMovement(float speed) : base(speed) { }

		public override void Move()
		{
			UnityEngine.Debug.Log("FlyMovement Move: " + _speed * 2);
		}
	}
}
