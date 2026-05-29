namespace DesignPattern.Proxy
{
	public class AuthenticatorProxy : IAuthenticator
	{
		private IAuthenticator _authenticator;

		public AuthenticatorProxy()
		{
			_authenticator = new Authenticator();
		}

		public void Authenticate(string username, string password)
		{
			_authenticator.Authenticate(username, password);

			if (username == "admin" && password == "123456")
			{
				UnityEngine.Debug.Log("Admin authenticated");
			}
		}
	}
}
