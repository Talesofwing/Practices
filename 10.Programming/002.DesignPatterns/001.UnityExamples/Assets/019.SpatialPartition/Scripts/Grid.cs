using System.Collections.Generic;
using System.Linq;

using UnityEngine;

namespace DesignPattern.SpatialPartition
{
	public class Grid
	{
		private List<Entity>[] _entities;

		private int _size;

		public Grid(int size)
		{
			_size = size;

			_entities = new List<Entity>[_size * _size];
			for (int i = 0; i < _size * _size; i++)
			{
				_entities[i] = new List<Entity>();
			}
		}

		public void AddEntity(Entity entity)
		{
			int index = GetIndex(entity.transform.position);
			entity.GridIndex = index;
			_entities[index].Add(entity);
		}

		public void RemoveEntity(Entity entity)
		{
			int index = GetIndex(entity.transform.position);
			entity.GridIndex = -1;
			_entities[index].Remove(entity);
		}

		public void Refresh()
		{
			for (int i = 0; i < _size * _size; i++)
			{
				Entity[] entities = _entities[i].ToArray();
				foreach (var entity in entities)
				{
					int index = GetIndex(entity.transform.position);
					if (index != entity.GridIndex)
					{
						if (entity.GridIndex != -1)
						{
							_entities[entity.GridIndex].Remove(entity);
						}
						_entities[index].Add(entity);
					}
				}
			}
		}

		public Entity FindTarget(Entity entity)
		{
			int centerIndex = GetIndex(entity.Tf.position);
			int gridX = centerIndex / _size;
			int gridZ = centerIndex % _size;

			float nearestDistanceSqr = float.MaxValue;
			Entity nearestEntity = null;
			for (int dx = -1; dx <= 1; dx++)
			{
				for (int dz = -1; dz <= 1; dz++)
				{
					int x = gridX + dx;
					int z = gridZ + dz;

					if (x >= 0 && x < _size && z >= 0 && z < _size)
					{
						int index = x * _size + z;
						foreach (var e in _entities[index])
						{
							if (e == entity) continue;

							float sqrDistance = (entity.Tf.position - e.Tf.position).sqrMagnitude;
							if (sqrDistance < nearestDistanceSqr)
							{
								nearestDistanceSqr = sqrDistance;
								nearestEntity = e;
							}
						}
					}
				}
			}

			return nearestEntity;
		}

		private int GetIndex(Vector3 pos)
		{
			return (int)pos.x + (int)pos.z * _size;
		}
	}
}
