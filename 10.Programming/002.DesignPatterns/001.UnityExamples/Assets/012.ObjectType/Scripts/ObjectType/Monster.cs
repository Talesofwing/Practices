using UnityEngine;

namespace DesignPattern.ObjectType
{
	public class Monster
	{
		public MonsterData Data { get; private set; }

		public Monster(MonsterData data)
		{
			Data = data;
		}

		public void Attack()
		{
			switch (Data.AttackType)
			{
				case 0:
					Debug.Log($"Monster {Data.Name} attacks with {Data.Atk} damage in Punch");
					break;
				case 1:
					Debug.Log($"Monster {Data.Name} attacks with {Data.Atk} damage in Kick");
					break;
				case 2:
					Debug.Log($"Monster {Data.Name} attacks with {Data.Atk} damage in Tail Whip");
					break;
				default:
					Debug.Log($"Monster {Data.Name} attacks with {Data.Atk} damage in Unknown Attack");
					break;
			}
		}
	}
}
