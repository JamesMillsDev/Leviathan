using System.Numerics;

namespace Leviathan.Mathematics
{
	public struct Vec2
	{
		public static Vec2 Zero { get; } = new(0, 0);
		public static Vec2 Half { get; } = new(0.5f, 0.5f);
		public static Vec2 One { get; } = new(1, 1);
		public static Vec2 Right { get; } = new(1, 0);
		public static Vec2 Left { get; } = new(-1, 0);
		public static Vec2 Up { get; } = new(0, 1);
		public static Vec2 Down { get; } = new(0, -1);
		public static Vec2 PositiveInfinity { get; } = new(float.PositiveInfinity, float.PositiveInfinity);
		public static Vec2 NegativeInfinity { get; } = new(float.NegativeInfinity, float.NegativeInfinity);

		public float Magnitude => MathF.Sqrt(SqrMagnitude);
		public float SqrMagnitude => x * x + y * y;
		public Vec2 Normalized
		{
			get
			{
				Vec2 copy = this;
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

		public Vec2()
		{
			x = 0;
			y = 0;
		}

		public Vec2(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

		public Vec2(Vector2 _vector2)
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

		public bool Equals(Vec2 _other) => x.Equals(_other.x) && y.Equals(_other.y);

		public override bool Equals(object? _obj) => _obj is Vec2 other && Equals(other);

		public override int GetHashCode() => HashCode.Combine(x, y);

		public override string ToString() => $"({x}, {y})";

		public static float Angle(Vec2 _vector) => MathF.Atan2(_vector.y, _vector.x);

		public static Vec2 ClampMagnitude(Vec2 _vector, float _maxMagnitude)
		{
			if(_vector.Magnitude <= _maxMagnitude)
				return _vector;

			_vector.Normalise();

			return _vector * _maxMagnitude;
		}

		//Distance
		public static float Distance(Vec2 _a, Vec2 _b) => (_a - _b).Magnitude;

		public static float Dot(Vec2 _lhs, Vec2 _rhs) => _lhs.x * _rhs.x + _lhs.y * _rhs.y;

		public static Vec2 Lerp(Vec2 _a, Vec2 _b, float _t)
		{
			_t = LMath.Clamp01(_t);

			return _a * (1 - _t) + _b * _t;
		}

		public static Vec2 LerpUnclamped(Vec2 _a, Vec2 _b, float _t) => _a * (1 - _t) + _b * _t;

		public static Vec2 Min(Vec2 _a, Vec2 _b) => new(LMath.Min(_a.x, _b.x), LMath.Min(_a.y, _b.y));
		public static Vec2 Max(Vec2 _a, Vec2 _b) => new(LMath.Max(_a.x, _b.x), LMath.Max(_a.y, _b.y));

		public static Vec2 Reflect(Vec2 _direction, Vec2 _normal)
		{
			float dot = Dot(_direction, _normal);
			
			return _direction - (2 * dot * _normal);
		}

		public static Vec2 Perpendicular(Vec2 _vector) => new(-_vector.y, _vector.x);

		public static Vec2 Rotate(Vec2 _vec, float _angle)
		{
			float angle = _angle * LMath.DEG_2_RAD;

			return new Vec2
			{
				x = _vec.x * MathF.Cos(angle) - _vec.y * MathF.Sin(angle),
				y = _vec.x * MathF.Sin(angle) + _vec.y * MathF.Cos(angle)
			};
		}

		public static Vec2 Scale(Vec2 _vec, float _scalar) => _vec * _scalar;

		public static float SignedAngle(Vec2 _vector) => MathF.Atan2(_vector.y, _vector.x) - 180f;

		/// <summary>
		/// This method allows an implicit conversion from System.Numerics.Vector2 to our Vec2 class.
		/// </summary>
		/// <param name="_vec"></param>
		public static implicit operator Vec2(Vector2 _vec) => new Vec2(_vec.X, _vec.Y);

		/// <summary>
		/// This method allows an implicit conversion from our Vec2 class to System.Numerics.Vector2.
		/// </summary>
		/// <param name="_v"></param>
		public static implicit operator Vector2(Vec2 _v) => new Vector2(_v.x, _v.y);

		/// <summary>
		/// This method allows an implicit conversion from our Vec2 class to System.Numerics.Vector2.
		/// </summary>
		/// <param name="_v"></param>
		public static implicit operator Vec3(Vec2 _v) => new Vec3(_v.x, _v.y, 1);

		/// <summary>
		/// This method allows an implicit conversion from our Vec2 class to System.Numerics.Vector2.
		/// </summary>
		/// <param name="_v"></param>
		public static implicit operator Vec2(Vec3 _v) => new Vec2(_v.x, _v.y);

		//Addition Operator Overload +
		public static Vec2 operator +(Vec2 _lhs, Vec2 _rhs) => new Vec2(_lhs.x + _rhs.x, _lhs.y + _rhs.y);

		//Subtraction Operator Overload - 
		public static Vec2 operator -(Vec2 _lhs, Vec2 _rhs) => new Vec2(_lhs.x - _rhs.x, _lhs.y - _rhs.y);

		public static bool operator ==(Vec2 _lhs, Vec2 _rhs) => _lhs.Equals(_rhs);

		public static bool operator !=(Vec2 _lhs, Vec2 _rhs) => !(_lhs == _rhs);

		public static Vec2 operator *(Vec2 _lhs, float _rhs) => new Vec2(_lhs.x * _rhs, _lhs.y * _rhs);

		public static Vec2 operator *(float _lhs, Vec2 _rhs) => new Vec2(_lhs * _rhs.x, _lhs * _rhs.y);

		public static Vec2 operator /(Vec2 _lhs, float _rhs) => new Vec2(_lhs.x / _rhs, _lhs.y / _rhs);
	}
}