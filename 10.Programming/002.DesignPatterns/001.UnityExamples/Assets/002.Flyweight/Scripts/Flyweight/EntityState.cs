namespace DesignPattern.Flyweight
{
	/// <summary>
	/// As intrinsic
	/// </summary>
	public class EntityState
	{
		public string Name { get; private set; }
		public int Hp { get; private set; }

		public EntityState(string name, int hp)
		{
			Name = name;
			Hp = hp;
		}
	}
}
