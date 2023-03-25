using Leviathan.Mathematics;
using Leviathan.Resources;

using Raylib_cs;

using Color = Leviathan.Mathematics.Color;

namespace Leviathan.UI
{
	public class Button : Selectable
	{
		public delegate void OnClickEvent();

		public class RenderSettings
		{
			public ColorBlock colors = new ColorBlock()
			{
				disabled = new Color(255, 255, 255, 128),
				hovered = Raylib_cs.Color.DARKGRAY,
				normal = Raylib_cs.Color.LIGHTGRAY,
				selected = Raylib_cs.Color.BLACK
			};

			public int fontSize;
			public Color textColor;
			public float roundedness = 0.1f;
			public float fontSpacing = 1f;
			public string? fontId = null;

			public RenderSettings(int _fontSize, Color _textColor)
			{
				fontSize = _fontSize;
				textColor = _textColor;
			}
		}

		private readonly float roundednesss;
		private readonly string text;
		private readonly int fontSize;
		private readonly float fontSpacing;

		private readonly Font font;
		private readonly Color textColor;
		private readonly Vector2 textSize;

		private OnClickEvent? onClick;

		public Button(Vector2 _position, string _text, RenderSettings _settings)
			: base(_position, Vector2.One, _settings.colors)
		{
			roundednesss = _settings.roundedness;
			text = _text;
			fontSize = _settings.fontSize;
			fontSpacing = _settings.fontSpacing;

			font = string.IsNullOrEmpty(_settings.fontId) ? Raylib.GetFontDefault() : ResourceManager.Find<FontResource, Font>(_settings.fontId)!;
			textColor = _settings.textColor;

			//Raylib function that creates a bounding box around the font based on its size and spacing
			textSize = Raylib.MeasureTextEx(font, text, fontSize, fontSpacing);
			Transform!.LocalScale = textSize;
		}

		public Button(Vector2 _position, Vector2 _buttonSize, string _text, RenderSettings _settings)
			: base(_position, _buttonSize, _settings.colors)
		{
			roundednesss = _settings.roundedness;
			text = _text;
			fontSize = _settings.fontSize;
			fontSpacing = _settings.fontSpacing;

			font = string.IsNullOrEmpty(_settings.fontId) ? Raylib.GetFontDefault() : ResourceManager.Find<FontResource, Font>(_settings.fontId)!;
			textColor = _settings.textColor;

			//Raylib function that creates a bounding box around the font based on its size and spacing
			textSize = Raylib.MeasureTextEx(font, text, fontSize, fontSpacing);
			Transform!.Scale = _buttonSize;
		}

		public void AddListener(OnClickEvent _event)
		{
			if(onClick == null)
				onClick = _event;
			else
				onClick += _event;
		}

		public void RemoveListener(OnClickEvent _event)
		{
			if(onClick != null)
				onClick -= _event;
		}

		public override void Render()
		{
			if(Transform == null)
				return;

			Raylib.DrawRectangleRounded(Rect, roundednesss, 5, ColorFromState());
			Vector2 p = Transform.Scale - textSize;
			Raylib.DrawTextPro(font, text, new Vector2(Transform.Position.x + p.y * 0.5f, Transform.Position.y + p.y * 0.5f), Vector2.Zero, 0f, fontSize, fontSpacing, textColor);
		}

		protected override void OnStateChange(SelectionState _state, SelectionState _oldState)
		{
			if(_state != SelectionState.Selected && _oldState == SelectionState.Selected)
			{
				// The button is no longer being clicked, so do the event
				onClick?.Invoke();
			}
		}
	}
}