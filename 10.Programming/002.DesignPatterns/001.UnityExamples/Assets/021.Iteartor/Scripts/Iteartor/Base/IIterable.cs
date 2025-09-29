namespace DesignPattern.Iterator
{
	public interface IIterable<T>
	{
		IIterator<T> GetIterator();
	}
}
