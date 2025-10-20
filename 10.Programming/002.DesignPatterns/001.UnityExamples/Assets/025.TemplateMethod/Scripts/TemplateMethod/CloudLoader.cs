namespace DesignPattern.TemplateMethod
{
	public class CloudLoader : BaseLoader
	{
		public string Account { get; set; }

		protected override bool VertifyAccount()
		{
			return Account == "admin";
		}

		protected override void SaveDatas()
		{
			UnityEngine.Debug.Log("Save Datas to Cloud");
		}

		protected override void GetDatas()
		{
			UnityEngine.Debug.Log("Get Datas from Cloud");
		}

		protected override void AnalyzeDatas()
		{
			UnityEngine.Debug.Log("Analyze Datas from Cloud");
		}

		protected override void DistributeDatas()
		{
			UnityEngine.Debug.Log("Distribute Datas to Cloud");
		}
	}
}
