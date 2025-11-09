using UnityEngine;

namespace DesignPattern.Proxy
{
	public class ProxyUse : MonoBehaviour
	{
		private void Start()
		{
			IAuthenticator authenticator = new AuthenticatorProxy();
			authenticator.Authenticate("admin", "123456");
		}
	}
}
