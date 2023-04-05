namespace Leviathan.Mathematics
{
	public struct Vector2
	{
		public static Vector2 Zero { get; } = new(0, 0);
		public static Vector2 Half { get; } = new(0.5f, 0.5f);
		public static Vector2 One { get; } = new(1, 1);
		public static Vector2 Right { get; } = new(1, 0);
		public static Vector2 Left { get; } = new(-1, 0);
		public static Vector2 Up { get; } = new(0, 1);
		public static Vector2 Down { get; } = new(0, -1);
		public static Vector2 PositiveInfinity { get; } = new(float.PositiveInfinity, float.PositiveInfinity);
		public static Vector2 NegativeInfinity { get; } = new(float.NegativeInfinity, float.NegativeInfinity);

		public float Magnitude => MathF.Sqrt(SqrMagnitude);
		public float SqrMagnitude => x * x + y * y;
		public Vector2 Normalized
		{
			get
			{
				Vector2 copy = this;
				copy.Normalise();
				
				return copy;
			}
		}

		public float this[int _index] => _index switch
		{
			0 => x,
			1 => y,
			_ => throw new IndexOutOfRangeException("Vec2 only has 2 components")
		};

		public float x = 0.0f;
		public float y = 0.0f;

		public Vector2()
		{
			x = 0;
			y = 0;
		}

		public Vector2(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

		public Vector2(System.Numerics.Vector2 _vector2)
		{
			x = _vector2.X;
			y = _vector2.Y;
		}

		public void Normalise()
		{
			float length = Magnitude;
			if(length == 0)
			{
				x = 0;
				y = 0;
			}
			else
			{
				x /= length;
				y /= length;
			}
		}

		public void Set(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

		public bool Equals(Vector2 _other) => x.Equals(_other.x) && y.Equals(_other.y);

		public override bool Equals(object? _obj) => _obj is Vector2 other && Equals(other);

		public override int GetHashCode() => HashCode.Combine(x, y);

		public override string ToString() => $"({x}, {y})";

		public static float Angle(Vector2 _vector) => MathF.Atan2(_vector.y, _vector.x);

		public static Vector2 ClampMagnitude(Vector2 _vector, float _maxMagnitude)
		{
			if(_vector.Magnitude <= _maxMagnitude)
				return _vector;

			_vector.Normalise();

			return _vector * _maxMagnitude;
		}

		//Distance
		public static float Distance(Vector2 _a, Vector2 _b) => (_a - _b).Magnitude;

		public static float Dot(Vector2 _lhs, Vector2 _rhs) => _lhs.x * _rhs.x + _lhs.y * _rhs.y;

		public static Vector2 Lerp(Vector2 _a, Vector2 _b, float _t)
		{
			_t = Leviamath.Clamp01(_t);

			return _a * (1 - _t) + _b * _t;
		}

		public static Vector2 LerpUnclamped(Vector2 _a, Vector2 _b, float _t) => _a * (1 - _t) + _b * _t;

		public static Vector2 Min(Vector2 _a, Vector2 _b) => new(Leviamath.Min(_a.x, _b.x), Leviamath.Min(_a.y, _b.y));
		public static Vector2 Max(Vector2 _a, Vector2 _b) => new(Leviamath.Max(_a.x, _b.x), Leviamath.Max(_a.y, _b.y));

		public static Vector2 Reflect(Vector2 _direction, Vector2 _normal)
		{
			float dot = Dot(_direction, _normal);
			
			return _direction - (2 * dot * _normal);
		}

		public static Vector2 Perpendicular(Vector2 _vector) => new(-_vector.y, _vector.x);

		public static Vector2 Rotate(Vector2 _vec, float _angle)
		{
			float angle = _angle * Leviamath.DEG_2_RAD;

			return new Vector2
			{
				x = _vec.x * MathF.Cos(angle) - _vec.y * MathF.Sin(angle),
				y = _vec.x * MathF.Sin(angle) + _vec.y * MathF.Cos(angle)
			};
		}

		public static Vector2 Scale(Vector2 _vec, float _scalar) => _vec * _scalar;

		public static float SignedAngle(Vector2 _vector) => MathF.Atan2(_vector.y, _vector.x) - 180f;

		/// <summary>
		/// This method allows an implicit conversion from System.Numerics.Vector2 to our Vec2 class.
		/// </summary>
		/// <param name="_vec"></param>
		public static implicit operator Vector2(System.Numerics.Vector2 _vec) => new Vector2(_vec.X, _vec.Y);

		/// <summary>
		/// This method allows an implicit conversion from our Vec2 class to System.Numerics.Vector2.
		/// </summary>
		/// <param name="_v"></param>
		public static implicit operator System.Numerics.Vector2(Vector2 _v) => new System.Numerics.Vector2(_v.x, _v.y);

		/// <summary>
		/// This method allows an implicit conversion from our Vec2 class to System.Numerics.Vector2.
		/// </summary>
		/// <param name="_v"></param>
		public static implicit operator Vector3(Vector2 _v) => new Vector3(_v.x, _v.y, 1);

		/// <summary>
		/// This method allows an implicit conversion from our Vec2 class to System.Numerics.Vector2.
		/// </summary>
		/// <param name="_v"></param>
		public static implicit operator Vector2(Vector3 _v) => new Vector2(_v.x, _v.y);
		
		/// <summary>
		/// </summary>
		/// <param name="_v"></param>
		public static implicit operator float[](Vector2 _v) => new [] { _v.x, _v.y };
		
		/// <summary>
		/// </summary>
		/// <param name="_v"></param>
		public static implicit operator Vector2(float[] _v) => new Vector2(_v[0], _v[1]);

		//Addition Operator Overload +
		public static Vector2 operator +(Vector2 _lhs, Vector2 _rhs) => new Vector2(_lhs.x + _rhs.x, _lhs.y + _rhs.y);

		//Subtraction Operator Overload - 
		public static Vector2 operator -(Vector2 _lhs, Vector2 _rhs) => new Vector2(_lhs.x - _rhs.x, _lhs.y - _rhs.y);

		public static bool operator ==(Vector2 _lhs, Vector2 _rhs) => _lhs.Equals(_rhs);

		public static bool operator !=(Vector2 _lhs, Vector2 _rhs) => !(_lhs == _rhs);

		public static Vector2 operator *(Vector2 _lhs, Vector2 _rhs) => new Vector2(_lhs.x * _rhs.x, _lhs.y * _rhs.y);
		
		public static Vector2 operator *(Vector2 _lhs, float _rhs) => new Vector2(_lhs.x * _rhs, _lhs.y * _rhs);

		public static Vector2 operator *(float _lhs, Vector2 _rhs) => new Vector2(_lhs * _rhs.x, _lhs * _rhs.y);

		public static Vector2 operator /(Vector2 _lhs, float _rhs) => new Vector2(_lhs.x / _rhs, _lhs.y / _rhs);
	}
}