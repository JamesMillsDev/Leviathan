using System.Numerics;

namespace Leviathan.Mathematics
{
	public struct Vec4
	{
		public float Magnitude => MathF.Sqrt(x * x + y * y + z * z + w * w);
		
		public float x;
		public float y;
		public float z;
		public float w;

		public Vec4(float _x, float _y, float _z, float _w)
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}
		
		//Normalisation - Non Static
		public void Normalise()
		{
			float length = Magnitude;
			if(length == 0)
			{
				x = 0;
				y = 0;
				z = 0;
				w = 0;
			}
			else
			{
				x /= length;
				y /= length;
				z /= length;
				w /= length;
			}
		}

		//Dot
		public float Dot(Vec4 _rhs) => x * _rhs.x + y * _rhs.y + z * _rhs.z + w * _rhs.w;
		
		public bool Equals(Vec4 _other) => x.Equals(_other.x) && y.Equals(_other.y) && z.Equals(_other.z) && w.Equals(_other.w);

		public override bool Equals(object? _obj) => _obj is Vec4 other && Equals(other);

		public override int GetHashCode() => HashCode.Combine(x, y, z, w);

		//Normalisation - Static
		public static Vec4 Normalise(Vec4 _vec)
		{
			float len = _vec.Magnitude;
			return len == 0 ? new Vec4(0, 0, 0, 0) : new Vec4(_vec.x / len, _vec.y / len, _vec.z / len, _vec.w / len);
		}
		
		public static float Dot(Vec4 _lhs, Vec4 _rhs) => _lhs.x * _rhs.x + _lhs.y * _rhs.y + _lhs.z * _rhs.z + _lhs.w * _rhs.w;

		/// <summary>
		/// This method allows an implicit conversion from System.Numerics.Vector2 to our Vec4 class.
		/// </summary>
		/// <param name="_vec"></param>
		public static implicit operator Vec4(Vector4 _vec) => new Vec4(_vec.X, _vec.Y, _vec.Z, _vec.W);

		/// <summary>
		/// This method allows an implicit conversion from our Vec3 class to System.Numerics.Vector2.
		/// </summary>
		/// <param name="_v"></param>
		public static implicit operator Vector4(Vec4 _v) => new Vector4(_v.x, _v.y, _v.z, _v.w);

		public static bool operator ==(Vec4 _lhs, Vec4 _rhs) => _lhs.Magnitude - _lhs.Magnitude < Math.EPSILON && _lhs.Magnitude - _rhs.Magnitude > -Math.EPSILON;
		
		public static bool operator !=(Vec4 _lhs, Vec4 _rhs) => !(_lhs == _rhs);

		//Addition Operator Overload +
		public static Vec4 operator +(Vec4 _lhs, Vec4 _rhs) => new Vec4(_lhs.x + _rhs.x, _lhs.y + _rhs.y, _lhs.z + _rhs.z, _lhs.w + _rhs.w);

		//Subtraction Operator Overload - 
		public static Vec4 operator -(Vec4 _lhs, Vec4 _rhs) => new Vec4(_lhs.x - _rhs.x, _lhs.y - _rhs.y, _lhs.z - _rhs.z, _lhs.w - _rhs.w);

		//PreScale Operator Overload 
		public static Vec4 operator *(float _lhs, Vec4 _rhs) => new Vec4(_lhs * _rhs.x, _lhs * _rhs.y, _lhs * _rhs.z, _lhs * _rhs.w);

		//PostScale Operator Overload
		public static Vec4 operator *(Vec4 _lhs, float _rhs) => new Vec4(_lhs.x * _rhs, _lhs.y * _rhs, _lhs.z * _rhs, _lhs.w * _rhs);
	}
}