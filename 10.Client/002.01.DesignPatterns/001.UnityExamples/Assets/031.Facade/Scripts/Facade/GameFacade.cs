namespace DesignPattern.Facade
{
	public static class GameFacade
	{
		public static void SaveGame(string savedata)
		{
			string analyzedCode = Analyzer.Analyze(savedata);
			SaveSystem.Save(analyzedCode);
		}
	}
}
