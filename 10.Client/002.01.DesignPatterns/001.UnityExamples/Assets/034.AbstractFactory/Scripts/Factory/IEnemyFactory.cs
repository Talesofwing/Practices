namespace DesignPattern.AbstractFactory
{
	public interface IEnemyFactory
	{
		BaseAI CreateAI();
		BaseMovement CreateMovement(float speed);
	}
}
