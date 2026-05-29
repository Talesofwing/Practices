using UnityEngine;

namespace DesignPattern.Bridge
{
	public class BridgeUse : MonoBehaviour
	{
		private void Start()
		{
			// If you want to extend the renderer or compatible with other render APIs,
			// you can do it by creating a new renderer and render API easily.
			RenderAPI renderAPI = new OpenGLAPI();
			Renderer renderer = new URPRenderer(renderAPI);
			renderer.Render();
		}
	}
}
