namespace DesignPattern.Bridge
{
	public class OpenGLAPI : RenderAPI
	{
		public override void Draw()
		{
			UnityEngine.Debug.Log("Draw with OpenGL");
		}
	}
}
