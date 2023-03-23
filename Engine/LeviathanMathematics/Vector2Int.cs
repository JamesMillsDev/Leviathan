namespace Leviathan.Mathematics
{
	public struct Vector2Int
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

		public Vector2Int(int _x, int _y)
		{
			x = _x;
			y = _y;
		}

		public bool Equals(Vector2Int _other) => x.Equals(_other.x) && y.Equals(_other.y);

		public override bool Equals(object? _other) => _other is Vector2Int other && Equals(other);

		public override int GetHashCode() => HashCode.Combine(x, y);

		public override string ToString() => $"{x}, {y}";

		#region Global Operatos

		public static float Dot(Vector2Int _lhs, Vector2Int _rhs) => _lhs.x * _rhs.x + _lhs.y * _rhs.y;

		public static float Distance(Vector2Int _lhs, Vector2Int _rhs) => (_lhs - _rhs).Magnitude;
		
		public static Vector2Int Normalized(Vector2Int _vec) => _vec * (1f / _vec.Magnitude);

		#endregion

		#region Operators

		public static Vector2Int operator +(Vector2Int _lhs, Vector2Int _rhs) => new(_lhs.x + _rhs.x, _lhs.y + _rhs.y);
		public static Vector2Int operator -(Vector2Int _lhs, Vector2Int _rhs) => new(_lhs.x - _rhs.x, _lhs.y - _rhs.y);
		public static Vector2Int operator *(Vector2Int _lhs, Vector2Int _rhs) => new(_lhs.x * _rhs.x, _lhs.y * _rhs.y);
		public static Vector2Int operator *(Vector2Int _lhs, float _rhs) => new((int) (_lhs.x * _rhs), (int) (_lhs.y * _rhs));

		public static bool operator ==(Vector2Int _lhs, Vector2Int _rhs) => _lhs.Magnitude - _lhs.Magnitude < LMath.EPSILON && _lhs.Magnitude - _rhs.Magnitude > -LMath.EPSILON;
		public static bool operator !=(Vector2Int _lhs, Vector2Int _rhs) => !(_lhs == _rhs);
		public static bool operator >(Vector2Int _lhs, Vector2Int _rhs) => _lhs.Magnitude > _rhs.Magnitude;
		public static bool operator <(Vector2Int _lhs, Vector2Int _rhs) => _lhs.Magnitude < _rhs.Magnitude;
		public static bool operator >=(Vector2Int _lhs, Vector2Int _rhs) => _lhs.Magnitude >= _rhs.Magnitude;
		public static bool operator <=(Vector2Int _lhs, Vector2Int _rhs) => _lhs.Magnitude <= _rhs.Magnitude;

		#endregion
	}
}