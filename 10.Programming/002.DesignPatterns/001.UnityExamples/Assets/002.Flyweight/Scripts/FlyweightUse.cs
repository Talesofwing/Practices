using System.Collections.Generic;

using UnityEngine;

namespace DesignPattern.Flyweight
{
	public class FlyweightUse : MonoBehaviour
	{
		[SerializeField]
		private Entity _prefab;

		private List<Entity> _entities = new List<Entity>();

		private void Awake()
		{
			EntityStateFactory.AddState("Entity 1", 100);
			EntityStateFactory.AddState("Entity 2", 200);
			EntityStateFactory.AddState("Entity 3", 300);
		}

		private void Update()
		{
			if (Input.GetKeyDown(KeyCode.Alpha1))
			{
				Entity e = EntityFactory.Create("Entity 1");
				_entities.Add(e);

				Debug.Log("Create a new entity: " + e.Name + " !");
			}
			else if (Input.GetKeyDown(KeyCode.Alpha2))
			{
				Entity e = EntityFactory.Create("Entity 2");
				_entities.Add(e);

				Debug.Log("Create a new entity: " + e.Name + " !");
			}
			else if (Input.GetKeyDown(KeyCode.Alpha3))
			{
				Entity e = EntityFactory.Create("Entity 3");
				_entities.Add(e);

				Debug.Log("Create a new entity: " + e.Name + " !");
			}
			else if (Input.GetKeyDown(KeyCode.C))
			{
				Debug.Log("Clear!");
			}
			else if (Input.GetKeyDown(KeyCode.L))
			{
				Log();
			}
		}

		private void Log()
		{
			Debug.Log("Entity Count: " + _entities.Count);

			for (int i = 0; i < _entities.Count; ++i)
			{
				Debug.Log(_entities[i]);
			}
		}
	}
}
