namespace DesignPattern.ObjectPool
{
	public interface IObjectPool<T> where T : IReusable
	{
		T Get();
		void Return(T item);
	}
}
