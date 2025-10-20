namespace DesignPattern.TemplateMethod
{
	public abstract class BaseLoader
	{
		public virtual void Save()
		{
			if (VertifyAccount())
			{
				SaveDatas();

				OnSaveSuccess();
			}
			else
			{
				OnSaveFailed();
			}
		}

		public virtual void Load()
		{
			if (VertifyAccount())
			{
				GetDatas();
				AnalyzeDatas();
				DistributeDatas();

				OnLoadSuccess();
			}
			else
			{
				OnLoadFailed();
			}
		}

		protected abstract void SaveDatas();
		// We need to put the data into the function, so that the subclass can override it.
		// But there is a example, so I will not put the data into the function.
		protected abstract void GetDatas();
		protected abstract void AnalyzeDatas();
		protected abstract void DistributeDatas();

		protected virtual bool VertifyAccount()
		{
			return true;
		}

		protected virtual void OnSaveSuccess()
		{
			UnityEngine.Debug.Log("Save Success");
		}

		protected virtual void OnSaveFailed()
		{
			UnityEngine.Debug.LogWarning("Save Failed");
		}

		protected virtual void OnLoadSuccess()
		{
			UnityEngine.Debug.Log("Load Success");
		}

		protected virtual void OnLoadFailed()
		{
			UnityEngine.Debug.LogWarning("Load Failed");
		}
	}
}
