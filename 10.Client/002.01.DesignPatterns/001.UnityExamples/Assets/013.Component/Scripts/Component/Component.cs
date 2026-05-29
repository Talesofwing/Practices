namespace DesignPattern.Component
{
	public abstract class Component
	{
		public ObjectContainer Owner { get; private set; }

		public Component(ObjectContainer owner) => Owner = owner;

		public virtual void Init() { }
		public virtual void OnActive() { }
		public virtual void OnDeactive() { }
		public virtual void OnDestroy() { }
		public virtual void Update(float deltaTime) { }

		public virtual void OnMessage(string message) { }
	}
}
