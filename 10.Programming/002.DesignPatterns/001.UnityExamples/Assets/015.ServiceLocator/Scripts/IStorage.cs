namespace DesignPattern.ServiceLocator
{
	public interface IStorage
	{
		void Save(string data);
		string Load();
	}
}
