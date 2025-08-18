using System.Collections.Generic;

namespace DesignPattern.Prototype
{
	public static class EntityRegistry
	{
		private static Dictionary<string, Entity> _entities = new Dictionary<string, Entity>();

		public static void Register(string name, Entity entity)
		{
			_entities[name] = entity;
		}

		public static void Unregister(string name)
		{
			_entities.Remove(name);
		}

		public static Entity Create(string name)
		{
			UnityEngine.Debug.Log(_entities[name]);

			return _entities[name].Clone();
		}

		public static void Clear()
		{
			_entities.Clear();
		}

		public static int Count
		{
			get { return _entities.Count; }
		}
	}
}
