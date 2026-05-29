namespace DesignPattern.Bridge
{
	public abstract class Renderer
	{
		protected RenderAPI _renderAPI;

		public Renderer(RenderAPI renderAPI)
		{
			_renderAPI = renderAPI;
		}

		public abstract void Render();
	}
}
