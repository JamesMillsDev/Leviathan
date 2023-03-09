namespace Leviathan.Mathematics
{
	public struct Int2
	{
		public float Magnitude => MathF.Sqrt(MagnitudeSqr);

		public float MagnitudeSqr => Dot(this, this);
		
		public int x;
		public int y;

		public int this[int _index] => _index switch
		{
			0 => x,
			1 => y,
			_ => throw new IndexOutOfRangeException("float2 only has 2 components.")
		};

		public Int2(int _x, int _y)
		{
			x = _x;
			y = _y;
		}

		public bool Equals(Int2 _other) => x.Equals(_other.x) && y.Equals(_other.y);

		public override bool Equals(object? _other) => _other is Int2 other && Equals(other);

		public override int GetHashCode() => HashCode.Combine(x, y);

		public override string ToString() => $"{x}, {y}";

		#region Global Operatos

		public static float Dot(Int2 _lhs, Int2 _rhs) => _lhs.x * _rhs.x + _lhs.y * _rhs.y;

		public static float Dist(Int2 _lhs, Int2 _rhs) => (_lhs - _rhs).Magnitude;
		
		public static Int2 Normalized(Int2 _vec) => _vec * (1f / _vec.Magnitude);

		#endregion

		#region Operators

		public static Int2 operator +(Int2 _lhs, Int2 _rhs) => new(_lhs.x + _rhs.x, _lhs.y + _rhs.y);
		public static Int2 operator -(Int2 _lhs, Int2 _rhs) => new(_lhs.x - _rhs.x, _lhs.y - _rhs.y);
		public static Int2 operator *(Int2 _lhs, Int2 _rhs) => new(_lhs.x * _rhs.x, _lhs.y * _rhs.y);
		public static Int2 operator *(Int2 _lhs, float _rhs) => new((int) (_lhs.x * _rhs), (int) (_lhs.y * _rhs));

		public static bool operator ==(Int2 _lhs, Int2 _rhs) => _lhs.Magnitude - _lhs.Magnitude < LMath.EPSILON && _lhs.Magnitude - _rhs.Magnitude > -LMath.EPSILON;
		public static bool operator !=(Int2 _lhs, Int2 _rhs) => !(_lhs == _rhs);
		public static bool operator >(Int2 _lhs, Int2 _rhs) => _lhs.Magnitude > _rhs.Magnitude;
		public static bool operator <(Int2 _lhs, Int2 _rhs) => _lhs.Magnitude < _rhs.Magnitude;
		public static bool operator >=(Int2 _lhs, Int2 _rhs) => _lhs.Magnitude >= _rhs.Magnitude;
		public static bool operator <=(Int2 _lhs, Int2 _rhs) => _lhs.Magnitude <= _rhs.Magnitude;

		#endregion
	}
}