namespace DesignPattern.ObjectPool
{
	public class Entity : IReusable
	{
		private string _name;

		public string Name => _name;

		public void Init(string name)
		{
			_name = name;
		}

		public void OnGet()
		{
			UnityEngine.Debug.Log("Get: " + _name);
		}

		public void OnReturn()
		{
			UnityEngine.Debug.Log("Return: " + _name);
		}
	}
}
