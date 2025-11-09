namespace DesignPattern.Proxy
{
	public class Authenticator : IAuthenticator
	{
		public void Authenticate(string username, string password)
		{
			UnityEngine.Debug.Log("Authenticating...");
		}
	}
}
