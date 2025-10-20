namespace DesignPattern.TemplateMethod
{
	public class LocalLoader : BaseLoader
	{
		protected override void SaveDatas()
		{
			UnityEngine.Debug.Log("Save Datas to Local");
		}

		protected override void GetDatas()
		{
			UnityEngine.Debug.Log("Get Datas from Local");
		}

		protected override void AnalyzeDatas()
		{
			UnityEngine.Debug.Log("Analyze Datas from Local");
		}

		protected override void DistributeDatas()
		{
			UnityEngine.Debug.Log("Distribute Datas to Local");
		}
	}
}
