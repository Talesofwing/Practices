using System.Collections.Generic;

using UnityEngine;

namespace DesignPattern.Mediator
{
	/// <summary>
	/// Ensure that entities do not interact with each other directly, and have the CombatSystem manage their interactions.
	/// The CombatSystem serves as an implementation of the Mediator pattern.
	/// </summary>
	public class CombatSystem
	{
		private static CombatSystem _instance;
		public static CombatSystem Instance
		{
			get
			{
				if (_instance == null)
				{
					_instance = new CombatSystem();
				}

				return _instance;
			}
		}

		private CombatSystem()
		{
			for (int i = 0; i < 10; ++i)
			{
				_entities.Add(new Entity("Player_" + i, new Vector3(i, i, i), OnEntityAttack));
			}
		}

		private List<Entity> _entities = new List<Entity>();

		public Entity GetRandomEntity()
		{
			return _entities[Random.Range(0, _entities.Count)];
		}

		private Entity FindNearestEntity(Entity entity)
		{
			float nearestDistance = float.MaxValue;
			Entity nearestEntity = null;

			foreach (var e in _entities)
			{
				if (e == entity) continue;

				float distance = Vector3.Distance(entity.Position, e.Position);
				if (distance < nearestDistance)
				{
					nearestDistance = distance;
					nearestEntity = e;
				}
			}

			return nearestEntity;
		}

		private void OnEntityAttack(Entity entity)
		{
			Entity nearestEntity = FindNearestEntity(entity);
			if (nearestEntity != null)
			{
				nearestEntity.TakeDamage(10);
			}
		}
	}
}
