using System.Collections.Generic;

namespace DesignPattern.Iterator
{
	public class Collection<T> : IIterable<T>
	{
		private List<T> _items = new List<T>();

		public int Count => _items.Count;

		public T this[int index] => _items[index];

		public IIterator<T> GetIterator()
		{
			return new Iterator(this);
		}

		public void Add(T item)
		{
			_items.Add(item);
		}

		public void Remove(T item)
		{
			_items.Remove(item);
		}

		public void RemoveAt(int index)
		{
			_items.RemoveAt(index);
		}

		public void Clear()
		{
			_items.Clear();
		}

		public struct Iterator : IIterator<T>
		{
			private Collection<T> _collection;
			private int _index;

			public Iterator(Collection<T> collection)
			{
				this._collection = collection;
				_index = -1;
			}

			public T Current()
			{
				return _collection._items[_index];
			}

			public bool MoveNext()
			{
				_index++;
				return _index < _collection._items.Count;
			}

			public void Reset() => _index = -1;
		}
	}
}
