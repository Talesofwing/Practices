namespace DesignPattern.Bridge
{
	public class URPRenderer : Renderer
	{
		public URPRenderer(RenderAPI renderAPI) : base(renderAPI) { }

		public override void Render()
		{
			UnityEngine.Debug.Log("Render with URP");

			_renderAPI.Draw();
		}
	}
}
