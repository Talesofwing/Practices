using System.Collections.Generic;

namespace DesignPattern.Flyweight
{
	public static class EntityStateFactory
	{
		private static Dictionary<string, EntityState> _entityStates = new Dictionary<string, EntityState>();

		public static void AddState(string name, int hp, bool isReplace = true) => AddState(new EntityState(name, hp), isReplace);

		public static void AddState(EntityState entityState, bool isReplace = true)
		{
			if (_entityStates.ContainsKey(entityState.Name))
			{
				if (isReplace)
				{
					_entityStates[entityState.Name] = entityState;
				}
			}
			else
			{
				_entityStates.Add(entityState.Name, entityState);
			}
		}

		public static EntityState GetState(string key)
		{
			return _entityStates[key];
		}
	}
}
