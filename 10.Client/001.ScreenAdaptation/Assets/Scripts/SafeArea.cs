using UnityEngine;

[RequireComponent(typeof(RectTransform))]
public class SafeArea : MonoBehaviour
{
	/*
		Generally, no need for switches.
	*/

	[SerializeField]
	private bool _left = true;
	[SerializeField]
	private bool _right = true;
	[SerializeField]
	private bool _top = true;
	[SerializeField]
	private bool _bottom = true;

	private RectTransform _panel;

	private void Awake()
	{
		_panel = GetComponent<RectTransform>();
		Rect area = Screen.safeArea;

		Vector2 min = area.position;
		Vector2 max = area.position + area.size;

		if (_left) min.x /= Screen.width;
		else min.x = 0;

		if (_right) max.x /= Screen.width;
		else max.x = 1;

		if (_top) min.y /= Screen.height;
		else min.y = 0;

		if (_bottom) max.y /= Screen.height;
		else max.y = 1;

		_panel.anchoredPosition = Vector2.zero;
		_panel.sizeDelta = Vector2.zero;

		_panel.anchorMin = min;
		_panel.anchorMax = max;
	}
}
