namespace Leviathan.Mathematics
{
	public struct Color
	{
		public byte Red
		{
			get => (byte) ((color >> 24) & 0xff);
			set => color = (color & 0x00ffffff) | ((uint) value << 24);
		}

		public byte Green
		{
			get => (byte) ((color >> 16) & 0xff);
			set => color = (color & 0xff00ffff) | ((uint) value << 16);
		}

		public byte Blue
		{
			get => (byte) ((color >> 8) & 0xff);
			set => color = (color & 0xffff00ff) | ((uint) value << 8);
		}

		public byte Alpha
		{
			get => (byte) ((color >> 0) & 0xff);
			set => color = (color & 0xffffff00) | ((uint) value << 0);
		}

		private uint color = 0xffffffff; // Defaults to white

		public Color(int _r, int _g, int _b, int _a) : this((byte) _r, (byte) _g, (byte) _b, (byte) _a) { }

		public Color(byte _r, byte _g, byte _b, byte _a)
		{
			Red = _r;
			Green = _g;
			Blue = _b;
			Alpha = _a;
		}

		public static implicit operator Raylib_CsLo.Color(Color _color) => new(_color.Red, _color.Green, _color.Blue, _color.Alpha);
		public static implicit operator Color(Raylib_CsLo.Color _color) => new(_color.r, _color.g, _color.b, _color.a);
	}
}