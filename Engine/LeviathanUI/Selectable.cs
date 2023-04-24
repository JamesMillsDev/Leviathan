using Leviathan.Mathematics;

using Raylib_CsLo;

using Color = Leviathan.Mathematics.Color;

namespace Leviathan.UI
{
	public abstract class Selectable : Widget
	{
		public enum SelectionState
		{
			Normal,
			Hovered,
			Selected,
			Disabled
		}

		public SelectionState State { get; private set; }

		public bool Interactable { get; set; } = true;

		private readonly ColorBlock colors;

		protected Selectable(Vector2 _pos, Vector2 _scale, ColorBlock _colors) : base(_pos, _scale)
		{
			colors = _colors;
		}

		public override void Tick(Vector2 _mousePos)
		{
			bool hovered = Raylib.CheckCollisionPointRec(_mousePos, Rect);
			bool clicked = Raylib.IsMouseButtonDown(MouseButton.MOUSE_BUTTON_LEFT);

			SelectionState oldState = State;

			if(State == SelectionState.Selected && !clicked)
			{
				State = hovered ? SelectionState.Hovered : SelectionState.Normal;
			}
			else if(clicked && hovered)
			{
				State = SelectionState.Selected;
			}
			else if(hovered)
			{
				State = SelectionState.Hovered;
			}
			else
			{
				State = SelectionState.Normal;
			}

			if(!Interactable)
				State = SelectionState.Disabled;

			if(State != oldState)
				OnStateChange(State, oldState);
		}

		protected abstract void OnStateChange(SelectionState _state, SelectionState _oldState);

		protected Color ColorFromState() => State switch
		{
			SelectionState.Normal => colors.normal,
			SelectionState.Hovered => colors.hovered,
			SelectionState.Selected => colors.selected,
			SelectionState.Disabled => colors.disabled,
			_ => Color.Black
		};
	}
}