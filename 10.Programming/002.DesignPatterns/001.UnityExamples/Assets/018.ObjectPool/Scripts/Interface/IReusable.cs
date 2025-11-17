namespace DesignPattern.ObjectPool
{
	public interface IReusable
	{
		void OnGet();
		void OnReturn();
	}
}
