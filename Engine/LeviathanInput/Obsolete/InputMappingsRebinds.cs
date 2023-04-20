using Raylib_cs;

namespace Leviathan.Input.Obsolete
{
	[Obsolete("Rebuilding in favour of new SharpX version")]
	public enum GamepadAxis
	{
		None = -1,
		LeftStick,
		RightStick,
		RightTrigger,
		LeftTrigger
	}

	[Obsolete("Rebuilding in favour of new SharpX version")]
	public enum GamepadButton
	{
		None = -1,
		North = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_UP,
		East = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,
		South = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_DOWN,
		West = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_LEFT,
		DPadUp = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_UP,
		DPadRight = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_RIGHT,
		DPadDown = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_DOWN,
		DPadLeft = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_LEFT,
		RightStick = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_THUMB,
		LeftStick = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_THUMB,
		RightBumper = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_TRIGGER_1,
		LeftBumper = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_TRIGGER_1,
		RightTrigger = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_TRIGGER_2,
		LeftTrigger = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_TRIGGER_2,
		Select = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_MIDDLE_LEFT,
		Pause = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_MIDDLE_RIGHT,
		Center = Raylib_cs.GamepadButton.GAMEPAD_BUTTON_MIDDLE
	}

	[Obsolete("Rebuilding in favour of new SharpX version")]
	public enum KeyCode
	{
		None = -1,
		Null = KeyboardKey.KEY_NULL,
		Back = KeyboardKey.KEY_BACK,
		VolumeUp = KeyboardKey.KEY_VOLUME_UP,
		VolumeDown = KeyboardKey.KEY_VOLUME_DOWN,
		Space = KeyboardKey.KEY_SPACE,
		Apostrophe = KeyboardKey.KEY_APOSTROPHE,
		Comma = KeyboardKey.KEY_COMMA,
		Minus = KeyboardKey.KEY_MINUS,
		Period = KeyboardKey.KEY_PERIOD,
		Slash = KeyboardKey.KEY_SLASH,
		NumZero = KeyboardKey.KEY_ZERO,
		NumOne = KeyboardKey.KEY_ONE,
		NumTwo = KeyboardKey.KEY_TWO,
		NumThree = KeyboardKey.KEY_THREE,
		NumFour = KeyboardKey.KEY_FOUR,
		NumFive = KeyboardKey.KEY_FIVE,
		NumSix = KeyboardKey.KEY_SIX,
		NumSeven = KeyboardKey.KEY_SEVEN,
		NumEight = KeyboardKey.KEY_EIGHT,
		NumNine = KeyboardKey.KEY_NINE,
		Semicolon = KeyboardKey.KEY_SEMICOLON,
		Equal = KeyboardKey.KEY_EQUAL,
		A = KeyboardKey.KEY_A,
		B = KeyboardKey.KEY_B,
		C = KeyboardKey.KEY_C,
		D = KeyboardKey.KEY_D,
		E = KeyboardKey.KEY_E,
		F = KeyboardKey.KEY_F,
		G = KeyboardKey.KEY_G,
		H = KeyboardKey.KEY_H,
		I = KeyboardKey.KEY_I,
		J = KeyboardKey.KEY_J,
		K = KeyboardKey.KEY_K,
		L = KeyboardKey.KEY_L,
		M = KeyboardKey.KEY_M,
		N = KeyboardKey.KEY_N,
		O = KeyboardKey.KEY_O,
		P = KeyboardKey.KEY_P,
		Q = KeyboardKey.KEY_Q,
		R = KeyboardKey.KEY_R,
		S = KeyboardKey.KEY_S,
		T = KeyboardKey.KEY_T,
		U = KeyboardKey.KEY_U,
		V = KeyboardKey.KEY_V,
		W = KeyboardKey.KEY_W,
		X = KeyboardKey.KEY_X,
		Y = KeyboardKey.KEY_Y,
		Z = KeyboardKey.KEY_Z,
		LeftBracket = KeyboardKey.KEY_LEFT_BRACKET,
		Backslash = KeyboardKey.KEY_BACKSLASH,
		RightBracket = KeyboardKey.KEY_RIGHT_BRACKET,
		Grave = KeyboardKey.KEY_GRAVE,
		Escape = KeyboardKey.KEY_ESCAPE,
		Enter = KeyboardKey.KEY_ENTER,
		Tab = KeyboardKey.KEY_TAB,
		Backspace = KeyboardKey.KEY_BACKSPACE,
		Insert = KeyboardKey.KEY_INSERT,
		Delete = KeyboardKey.KEY_DELETE,
		RightArrow = KeyboardKey.KEY_RIGHT,
		LeftArrow = KeyboardKey.KEY_LEFT,
		DownArrow = KeyboardKey.KEY_DOWN,
		UpArrow = KeyboardKey.KEY_UP,
		PageUp = KeyboardKey.KEY_PAGE_UP,
		PageDown = KeyboardKey.KEY_PAGE_DOWN,
		Home = KeyboardKey.KEY_HOME,
		End = KeyboardKey.KEY_END,
		CapsLock = KeyboardKey.KEY_CAPS_LOCK,
		ScrollLock = KeyboardKey.KEY_SCROLL_LOCK,
		NumLock = KeyboardKey.KEY_NUM_LOCK,
		PrintScreen = KeyboardKey.KEY_PRINT_SCREEN,
		Pause = KeyboardKey.KEY_PAUSE,
		F1 = KeyboardKey.KEY_F1,
		F2 = KeyboardKey.KEY_F2,
		F3 = KeyboardKey.KEY_F3,
		F4 = KeyboardKey.KEY_F4,
		F5 = KeyboardKey.KEY_F5,
		F6 = KeyboardKey.KEY_F6,
		F7 = KeyboardKey.KEY_F7,
		F8 = KeyboardKey.KEY_F8,
		F9 = KeyboardKey.KEY_F9,
		F10 = KeyboardKey.KEY_F10,
		F11 = KeyboardKey.KEY_F11,
		F12 = KeyboardKey.KEY_F12,
		Numpad0 = KeyboardKey.KEY_KP_0,
		Numpad1 = KeyboardKey.KEY_KP_1,
		Numpad2 = KeyboardKey.KEY_KP_2,
		Numpad3 = KeyboardKey.KEY_KP_3,
		Numpad4 = KeyboardKey.KEY_KP_4,
		Numpad5 = KeyboardKey.KEY_KP_5,
		Numpad6 = KeyboardKey.KEY_KP_6,
		Numpad7 = KeyboardKey.KEY_KP_7,
		Numpad8 = KeyboardKey.KEY_KP_8,
		Numpad9 = KeyboardKey.KEY_KP_9,
		NumpadDecimal = KeyboardKey.KEY_KP_DECIMAL,
		NumpadDivide = KeyboardKey.KEY_KP_DIVIDE,
		NumpadMultiply = KeyboardKey.KEY_KP_MULTIPLY,
		NumpadSubtract = KeyboardKey.KEY_KP_SUBTRACT,
		NumpadAdd = KeyboardKey.KEY_KP_ADD,
		NumpadEnter = KeyboardKey.KEY_KP_ENTER,
		NumpadEqual = KeyboardKey.KEY_KP_EQUAL,
		LeftShift = KeyboardKey.KEY_LEFT_SHIFT,
		LeftControl = KeyboardKey.KEY_LEFT_CONTROL,
		LeftAlt = KeyboardKey.KEY_LEFT_ALT,
		LeftSuper = KeyboardKey.KEY_LEFT_SUPER,
		RightShift = KeyboardKey.KEY_RIGHT_SHIFT,
		RightControl = KeyboardKey.KEY_RIGHT_CONTROL,
		RightAlt = KeyboardKey.KEY_RIGHT_ALT,
		RightSuper = KeyboardKey.KEY_RIGHT_SUPER,
		KeyboardMenu = KeyboardKey.KEY_KB_MENU
	}

	[Obsolete("Rebuilding in favour of new SharpX version")]
	public enum MouseButton
	{
		None = -1,
		Left = Raylib_cs.MouseButton.MOUSE_BUTTON_LEFT,
		Right = Raylib_cs.MouseButton.MOUSE_BUTTON_RIGHT,
		Middle = Raylib_cs.MouseButton.MOUSE_BUTTON_MIDDLE,
		Side = Raylib_cs.MouseButton.MOUSE_BUTTON_SIDE,
		Extra = Raylib_cs.MouseButton.MOUSE_BUTTON_EXTRA,
		Forward = Raylib_cs.MouseButton.MOUSE_BUTTON_FORWARD,
		Back = Raylib_cs.MouseButton.MOUSE_BUTTON_BACK
	}

	[Obsolete("Rebuilding in favour of new SharpX version")]
	public enum MouseAxis
	{
		None = -1,
		X,
		Y,
		Scroll
	}
}