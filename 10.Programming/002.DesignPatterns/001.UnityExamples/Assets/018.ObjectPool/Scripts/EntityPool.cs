using System.Collections.Generic;

using UnityEngine;

namespace DesignPattern.ObjectPool
{
	public class EntityPool : IObjectPool<Entity>
	{
		private const int MAX_ENTITY_COUNT = 50;

		private Queue<Entity> _entities = new Queue<Entity>();

		public void Prewarm(int count)
		{
			count = Mathf.Min(count, MAX_ENTITY_COUNT);

			for (int i = 0; i < count; i++)
			{
				Entity entity = new Entity();
				entity.Init("Entity " + i);
				_entities.Enqueue(entity);
			}
		}

		public Entity Get()
		{
			Entity entity = null;
			if (_entities.Count > 0)
			{
				entity = _entities.Dequeue();
			}
			else
			{
				entity = new Entity();
				entity.Init("Entity " + _entities.Count);
			}

			entity.OnGet();
			return entity;
		}

		public void Return(Entity item)
		{
			item.OnReturn();

			if (_entities.Count < MAX_ENTITY_COUNT)
			{
				_entities.Enqueue(item);
			}
		}
	}
}
