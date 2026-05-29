namespace DesignPattern.Proxy
{
	public interface IAuthenticator
	{
		void Authenticate(string username, string password);
	}
}
