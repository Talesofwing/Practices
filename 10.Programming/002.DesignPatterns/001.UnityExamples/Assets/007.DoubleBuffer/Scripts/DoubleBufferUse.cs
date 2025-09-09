using System.Collections.Generic;

using UnityEngine;

namespace DesignPattern.DoubleBuffer
{
	public class DoubleBufferUse : MonoBehaviour
	{
		[SerializeField]
		private int _actorCount = 3;

		private List<Actor> _actors = new List<Actor>();

		private void Awake()
		{
			for (int i = 0; i < _actorCount; ++i)
			{
				_actors.Add(new Actor($"Actor {i}"));
			}

			for (int i = 0; i < _actorCount; ++i)
			{
				_actors[i].SetFacing(_actors[(i + 1) % _actorCount]);
			}
		}

		private void Start()
		{
			_actors[0].Slap();
		}

		private void Update()
		{
			foreach (var actor in _actors)
			{
				actor.Update();
			}

			Debug.Log("===== Swap Before =====");
			foreach (var actor in _actors)
			{
				Debug.Log(actor);
			}

			foreach (var actor in _actors)
			{
				actor.Swap();
			}

			Debug.Log("===== Swap After =====");
			foreach (var actor in _actors)
			{
				Debug.Log(actor);
			}
		}
	}
}
