using UnityEngine;

namespace DesignPattern.Iterator
{
	public class IteratorUse : MonoBehaviour
	{
		private Collection<int> _collection = new Collection<int>();

		private void Update()
		{
			if (Input.GetKeyDown(KeyCode.A))
			{
				int random = Random.Range(0, 100);
				Debug.Log("Add: " + random);

				_collection.Add(random);
			}
			else if (Input.GetKeyDown(KeyCode.D))
			{
				if (_collection.Count == 0) return;

				Debug.Log("Remove: " + _collection[0]);

				_collection.RemoveAt(0);
			}
			else if (Input.GetKeyDown(KeyCode.Space))
			{
				var iteartor = _collection.GetIterator();
				string log = "Iterator: ";
				while (iteartor.MoveNext())
				{
					log += iteartor.Current() + " ";
				}
				Debug.Log(log);
			}
		}
	}
}
