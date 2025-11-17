using System;

using UnityEngine;
using UnityEngine.EventSystems;

namespace DesignPattern.SpatialPartition
{
	public class Entity : MonoBehaviour, IPointerDownHandler
	{
		public Transform Tf;
		public MeshRenderer MeshRenderer;
		public int GridIndex;

		public Action<Entity> Touch;

		public void OnPointerDown(PointerEventData eventData)
		{
			Touch?.Invoke(this);
		}
	}
}
