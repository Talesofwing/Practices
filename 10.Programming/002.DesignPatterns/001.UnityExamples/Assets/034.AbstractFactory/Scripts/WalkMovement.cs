namespace DesignPattern.AbstractFactory
{
	public class WalkMovement : BaseMovement
	{
		public WalkMovement(float speed) : base(speed) { }

		public override void Move()
		{
			UnityEngine.Debug.Log("WalkMovement Move: " + _speed);
		}
	}
}
