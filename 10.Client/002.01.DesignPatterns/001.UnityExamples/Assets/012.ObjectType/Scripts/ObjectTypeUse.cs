using UnityEngine;

namespace DesignPattern.ObjectType
{
	public class ObjectTypeUse : MonoBehaviour
	{
		private void Start()
		{
			// In general, it is usually defined in a `.csv` file.
			MonsterData data = new MonsterData()
			{
				Name = "Monster 1",
				Atk = 10,
				AttackType = 0,
			};

			MonsterData data2 = new MonsterData()
			{
				Name = "Monster 2",
				Atk = 20,
				AttackType = 1,
			};

			MonsterData data3 = new MonsterData()
			{
				Name = "Monster 3",
				Atk = 30,
				AttackType = 2,
			};

			Monster monster = new Monster(data);
			Monster monster2 = new Monster(data2);
			Monster monster3 = new Monster(data3);

			monster.Attack();
			monster2.Attack();
			monster3.Attack();
		}
	}
}
