using System.Collections.Generic;

using UnityEngine;

namespace DesignPattern.ObjectPool
{
	public class ObjectPoolUse : MonoBehaviour
	{
		[SerializeField]
		private int _prewarmCount = 50;

		private List<Entity> _entities = new List<Entity>();

		private EntityPool _entityPool;

		private void Start()
		{
			_entityPool = new EntityPool();
			_entityPool.Prewarm(_prewarmCount);
		}

		private void Update()
		{
			if (Input.GetKeyDown(KeyCode.Space))
			{
				Entity entity = _entityPool.Get();
				_entities.Add(entity);
			}
			else if (Input.GetKeyDown(KeyCode.D))
			{
				if (_entities.Count == 0) return;

				Entity entity = _entities[0];
				_entities.RemoveAt(0);
				_entityPool.Return(entity);
			}
		}
	}
}
