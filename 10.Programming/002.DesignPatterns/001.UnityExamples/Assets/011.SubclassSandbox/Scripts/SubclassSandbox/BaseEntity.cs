using UnityEngine;

namespace DesignPattern.SubclassSandbox
{
	/// <summary>
	/// Provides a large number of sandbox methods.
	/// The base class does not handle specific logic flow; it only provides utility functions.
	/// This is just an example, so only a few are shown.
	/// </summary>
	public abstract class BaseEntity
	{
		public abstract void Attack();
		public abstract void TakeDamage(int damage);

		protected void PlayEffect(string effectName)
		{
			Debug.Log("PlayEffect: " + effectName);
		}

		protected void PlaySound(string soundName)
		{
			Debug.Log("PlaySound: " + soundName);
		}

		protected void PlayAnimation(string animationName)
		{
			Debug.Log("PlayAnimation: " + animationName);
		}
	}
}
