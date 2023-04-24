namespace Leviathan.Mathematics
{
	public struct Color
	{
		public static Color LightGray => 0xc8c8c8ff;
		public static Color Gray => 0x828282ff;
		public static Color DarkGray => 0x505050ff;
		public static Color Yellow => 0xfdf900ff;
		public static Color Gold => 0xffcc00ff;
		public static Color Orange => 0xffa200ff;
		public static Color Pink => 0xff6dc2ff;
		public static Color Red => 0xe62936ff;
		public static Color Maroon => 0xbe2136ff;
		public static Color Green => 0x00e431ff;
		public static Color Lime => 0x009e2fff;
		public static Color DarkGreen => 0x00752dff;
		public static Color SkyBlue => 0x66bfffff;
		public static Color Blue => 0x0078f1ff;
		public static Color DarkBlue => 0x0053acff;
		public static Color Purple => 0xc87affff;
		public static Color Violet => 0x883cbeff;
		public static Color DarkPurple => 0x701f7eff;
		public static Color Beige => 0xd3b083ff;
		public static Color Brown => 0x7f6a4fff;
		public static Color DarkBrown => 0x4c3f2fff;
		public static Color White => 0xffffffff;
		public static Color Black => 0x000000ff;
		public static Color Clear => 0x00000000;
		public static Color Magenta => 0xff00ffff;

		public byte R
		{
			get => (byte) ((color >> 24) & 0xff);
			set => color = (color & 0x00ffffff) | ((uint) value << 24);
		}

		public byte G
		{
			get => (byte) ((color >> 16) & 0xff);
			set => color = (color & 0xff00ffff) | ((uint) value << 16);
		}

		public byte B
		{
			get => (byte) ((color >> 8) & 0xff);
			set => color = (color & 0xffff00ff) | ((uint) value << 8);
		}

		public byte A
		{
			get => (byte) ((color >> 0) & 0xff);
			set => color = (color & 0xffffff00) | ((uint) value << 0);
		}

		private uint color = 0xffffffff; // Defaults to white

		public Color(int _r, int _g, int _b, int _a) : this((byte) _r, (byte) _g, (byte) _b, (byte) _a) { }

		public Color(byte _r, byte _g, byte _b, byte _a)
		{
			R = _r;
			G = _g;
			B = _b;
			A = _a;
		}

		public Color(uint _color) => color = _color;

		public bool Equals(Color _other) => color == _other.color;

		public override bool Equals(object? _obj) => _obj is Color other && Equals(other);

		public override int GetHashCode() => (int) color;

		public static bool operator ==(Color _lhs, Color _rhs) => _lhs.color == _rhs.color;
		public static bool operator !=(Color _lhs, Color _rhs) => !(_lhs == _rhs);

		public static implicit operator Raylib_CsLo.Color(Color _color) => new(_color.R, _color.G, _color.B, _color.A);
		public static implicit operator Color(Raylib_CsLo.Color _color) => new(_color.r, _color.g, _color.b, _color.a);

		public static implicit operator Color(uint _color) => new(_color);
	}
}