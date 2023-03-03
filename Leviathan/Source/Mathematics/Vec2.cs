using System.Numerics;

namespace Leviathan.Mathematics
{
	public struct Vec2
	{
		public static readonly Vec2 zero = new(0, 0);
		public static readonly Vec2 half = new(0.5f, 0.5f);
		public static readonly Vec2 one = new(1, 1);

		public float Magnitude => MathF.Sqrt(x * x + y * y);
		
		public float Rotation => MathF.Atan2(y, x);
		
		public float x = 0.0f;
		public float y = 0.0f;

		public Vec2(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

		//Normalisation - Non Static
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

		public void Rotate(float _amount)
		{
			float xRotated = x * MathF.Cos(_amount) - y * MathF.Sin(_amount);
			float yRotated = x * MathF.Sin(_amount) + y * MathF.Cos(_amount);

			x = xRotated;
			y = yRotated;
		}

		public void RotateAround(Vec2 _pivotPoint, float _amount)
		{
			x -= _pivotPoint.x;
			y -= _pivotPoint.y;

			Rotate(_amount);

			x += _pivotPoint.x;
			y += _pivotPoint.y;
		}

		public bool Equals(Vec2 _other) => x.Equals(_other.x) && y.Equals(_other.y);

		public override bool Equals(object? _obj) => _obj is Vec2 other && Equals(other);

		public override int GetHashCode() => HashCode.Combine(x, y);

		//Normalisation - Static
		public static Vec2 Normalise(Vec2 _vec)
		{
			float len = _vec.Magnitude;
			return len == 0 ? new Vec2(0, 0) : new Vec2(_vec.x / len, _vec.y / len);
		}

		//Distance
		public static float Distance(Vec2 _a, Vec2 _b) => (_a - _b).Magnitude;

		public static float Dot(Vec2 _lhs, Vec2 _rhs) => _lhs.x * _rhs.x + _lhs.y * _rhs.y;

		//Rotation
		public static Vec2 CreateRotationVector(float _radians) => new Vec2(MathF.Cos(_radians), MathF.Sin(_radians));

		public static Vec2 Rotate(Vec2 _vec, float _angle)
		{
			float angle = _angle * Math.DEG2RAD;

			return new Vec2
			{
				x = _vec.x * MathF.Cos(angle) - _vec.y * MathF.Sin(angle),
				y = _vec.x * MathF.Sin(angle) + _vec.y * MathF.Cos(angle)
			};
		}

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

		//Addition Operator Overload +
		public static Vec2 operator +(Vec2 _lhs, Vec2 _rhs) => new Vec2(_lhs.x + _rhs.x, _lhs.y + _rhs.y);

		//Subtraction Operator Overload - 
		public static Vec2 operator -(Vec2 _lhs, Vec2 _rhs) => new Vec2(_lhs.x - _rhs.x, _lhs.y - _rhs.y);

		public static bool operator ==(Vec2 _lhs, Vec2 _rhs) => _lhs.Magnitude - _lhs.Magnitude < Math.EPSILON && _lhs.Magnitude - _rhs.Magnitude > -Math.EPSILON;

		public static bool operator !=(Vec2 _lhs, Vec2 _rhs) => !(_lhs == _rhs);

		//PreScale Operator Overload 
		public static Vec2 operator *(float _lhs, Vec2 _rhs) => new Vec2(_lhs * _rhs.x, _lhs * _rhs.y);

		//PostScale Operator Overload
		public static Vec2 operator *(Vec2 _lhs, float _rhs) => new Vec2(_lhs.x * _rhs, _lhs.y * _rhs);

		public static Vec2 operator *(Vec2 _lhs, Vec2 _rhs) => new Vec2(_lhs.x * _rhs.x, _lhs.y * _rhs.y);
	}
}