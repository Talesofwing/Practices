using System.Collections.Generic;
using System.Diagnostics;

using UnityEngine;

namespace DesignPattern.SpatialPartition
{
	public class SpatialPartitionUse : MonoBehaviour
	{
		[SerializeField]
		private GameObject _entityPrefab;

		[SerializeField]
		private int _gridSize = 100;

		[SerializeField]
		private int _entityCount = 100;

		[SerializeField]
		private Color _gridColor = Color.white;

		private List<Entity> _entities = new List<Entity>();

		private Grid _grid;
		private bool _useSpatialPartition = false;

		private void Start()
		{
			_grid = new Grid(_gridSize);

			for (int i = 0; i < _entityCount; ++i)
			{
				Entity entity = Instantiate(_entityPrefab).GetComponent<Entity>();
				entity.transform.position = new Vector3(Random.Range(0f, _gridSize), 0, Random.Range(0f, _gridSize));
				entity.Touch += OnEntityTouch;
				entity.MeshRenderer.material.color = Color.cyan;
				_entities.Add(entity);
				_grid.AddEntity(entity);
			}
		}

		private void Update()
		{
			if (Input.GetKeyDown(KeyCode.Space))
			{
				_useSpatialPartition = !_useSpatialPartition;
			}
		}

		private Entity FindTarget(Entity entity)
		{
			float nearestDistanceSqr = float.MaxValue;
			Entity nearestEntity = null;
			foreach (var e in _entities)
			{
				if (e == entity) continue;

				float sqrDistance = (e.Tf.position - entity.Tf.position).sqrMagnitude;
				if (sqrDistance < nearestDistanceSqr)
				{
					nearestDistanceSqr = sqrDistance;
					nearestEntity = e;
				}
			}
			return nearestEntity;
		}

		private void OnEntityTouch(Entity entity)
		{
			foreach (var e in _entities)
			{
				e.MeshRenderer.material.color = Color.cyan;
			}

			entity.MeshRenderer.material.color = Color.blue;

			if (_useSpatialPartition)
			{
				UnityEngine.Debug.Log("Spatial Partition Start");
				Stopwatch stopwatch = new Stopwatch();
				stopwatch.Start();
				Entity nearestEntity = _grid.FindTarget(entity);
				stopwatch.Stop();
				nearestEntity.MeshRenderer.material.color = Color.red;
				UnityEngine.Debug.Log("Elapsed time: " + stopwatch.ElapsedMilliseconds + "ms");
			}
			else
			{
				UnityEngine.Debug.Log("Non-Spatial Partition Start");
				Stopwatch stopwatch = new Stopwatch();
				stopwatch.Start();
				Entity nearestEntity2 = FindTarget(entity);
				stopwatch.Stop();
				nearestEntity2.MeshRenderer.material.color = Color.red;
				UnityEngine.Debug.Log("Elapsed time: " + stopwatch.ElapsedMilliseconds + "ms");
			}
		}

		private void OnDrawGizmos()
		{
			if (_grid == null)
				return;

			Gizmos.color = _gridColor;

			for (int x = 0; x <= _gridSize; x++)
			{
				Vector3 start = new Vector3(x, 0, 0);
				Vector3 end = new Vector3(x, 0, _gridSize);
				Gizmos.DrawLine(start, end);
			}

			for (int z = 0; z <= _gridSize; z++)
			{
				Vector3 start = new Vector3(0, 0, z);
				Vector3 end = new Vector3(_gridSize, 0, z);
				Gizmos.DrawLine(start, end);
			}
		}
	}
}
