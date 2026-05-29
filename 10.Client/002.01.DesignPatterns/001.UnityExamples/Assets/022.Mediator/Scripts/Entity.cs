using System;

using UnityEngine;

namespace DesignPattern.Mediator
{
	public class Entity
	{
		public string Name;
		public Vector3 Position;
		public Action<Entity> Attack;

		public Entity(string name, Vector3 position, Action<Entity> attack)
		{
			Name = name;
			Position = position;
			Attack = attack;
		}

		public void PerformAttack()
		{
			Debug.Log(Name + " PerformAttack");
			
			Attack?.Invoke(this);
		}

		public void TakeDamage(int damage)
		{
			Debug.Log(Name + " TakeDamage: " + damage);
		}

		public override string ToString()
		{
			return $"[Entity] Name: {Name}, Position: {Position}";
		}
	}
}
