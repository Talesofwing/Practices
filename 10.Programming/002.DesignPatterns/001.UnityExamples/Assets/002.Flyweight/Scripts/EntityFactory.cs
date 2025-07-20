using System.Collections.Generic;

namespace DesignPattern.Flyweight
{
	public static class EntityFactory
	{
		public static Entity Create(string name)
		{
			Entity e = new Entity();
			e.Init(EntityStateFactory.GetState(name));
			return e;
		}
	}
}
