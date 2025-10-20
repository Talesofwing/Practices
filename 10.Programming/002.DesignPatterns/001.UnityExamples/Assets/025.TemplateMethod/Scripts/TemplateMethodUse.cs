using UnityEngine;

namespace DesignPattern.TemplateMethod
{
	public class TemplateMethodUse : MonoBehaviour
	{
		[SerializeField]
		private bool _useCloud = false;

		[SerializeField]
		private string _account = "admin";

		private BaseLoader _loader;

		private void Start()
		{
			if (_useCloud)
			{
				_loader = new CloudLoader { Account = _account };
				_loader.Save();
				_loader.Load();
			}
			else
			{
				_loader = new LocalLoader();
				_loader.Save();
				_loader.Load();
			}
		}
	}
}
