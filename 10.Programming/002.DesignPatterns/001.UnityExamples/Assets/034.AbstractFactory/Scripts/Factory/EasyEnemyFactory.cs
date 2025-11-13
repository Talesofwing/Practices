namespace DesignPattern.AbstractFactory
{
	public class EasyEnemyFactory : IEnemyFactory
	{
		public BaseAI CreateAI()
		{
			return new EasyAI();
		}

		public BaseMovement CreateMovement(float speed)
		{
			return new WalkMovement(speed);
		}
	}
}
