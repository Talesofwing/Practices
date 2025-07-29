using System;
using System.Collections.Generic;

using UnityEngine;

namespace DesignPattern.Observer
{
	/// <summary>
	/// Manage observers and notify them (Mediator + Observer)
	/// </summary>
	public static class EventBus
	{
		private static Dictionary<Type, List<Delegate>> _observers = new();

		public delegate void InAction<T>(in T e) where T : struct, IEvent;

		public static void Subscribe<T>(InAction<T> action) where T : struct, IEvent
		{
			if (!_observers.ContainsKey(typeof(T)))
			{
				_observers[typeof(T)] = new List<Delegate>();
			}

			_observers[typeof(T)].Add(action);
		}

		public static void Unsubscribe<T>(InAction<T> action) where T : struct, IEvent
		{
			if (_observers.ContainsKey(typeof(T)))
			{
				_observers[typeof(T)].Remove(action);
			}
		}

		public static void Publish<T>(T e) where T : struct, IEvent
		{
			if (_observers.ContainsKey(typeof(T)))
			{
				foreach (var action in _observers[typeof(T)])
				{
					((InAction<T>)action)(e);
				}
			}
		}

		public static void Clear()
		{
			_observers.Clear();
		}
	}
}
