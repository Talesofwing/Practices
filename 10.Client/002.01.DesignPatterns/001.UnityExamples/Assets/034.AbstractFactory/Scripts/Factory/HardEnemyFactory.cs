namespace DesignPattern.AbstractFactory
{
	public class HardEnemyFactory : IEnemyFactory
	{
		public BaseAI CreateAI()
		{
			return new HardAI();
		}

		public BaseMovement CreateMovement(float speed)
		{
			return new FlyMovement(speed);
		}
	}
}
