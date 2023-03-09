namespace Leviathan.Mathematics
{
	public struct Mat4
	{
		public float m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16;

		public Mat4()
		{
			m1 = 1;
			m2 = 0;
			m3 = 0;
			m4 = 0;
			m5 = 0;
			m6 = 1;
			m7 = 0;
			m8 = 0;
			m9 = 0;
			m10 = 0;
			m11 = 1;
			m12 = 0;
			m13 = 0;
			m14 = 0;
			m15 = 0;
			m16 = 1;
		}

		public Mat4(float _m1, float _m5, float _m9, float _m13, float _m2, float _m6, float _m10, float _m14, float _m3,
			float _m7, float _m11, float _m15, float _m4, float _m8, float _m12, float _m16)
		{
			m1 = _m1;
			m2 = _m2;
			m3 = _m3;
			m4 = _m4;
			m5 = _m5;
			m6 = _m6;
			m7 = _m7;
			m8 = _m8;
			m9 = _m9;
			m10 = _m10;
			m11 = _m11;
			m12 = _m12;
			m13 = _m13;
			m14 = _m14;
			m15 = _m15;
			m16 = _m16;
		}

		public static Mat4 operator *(Mat4 _lhs, Mat4 _rhs)
		{
			return new Mat4(
				_lhs.m1 * _rhs.m1 + _lhs.m2 * _rhs.m5 + _lhs.m3 * _rhs.m9 + _lhs.m4 * _rhs.m13,
				_lhs.m5 * _rhs.m1 + _lhs.m6 * _rhs.m5 + _lhs.m7 * _rhs.m9 + _lhs.m8 * _rhs.m13,
				_lhs.m9 * _rhs.m1 + _lhs.m10 * _rhs.m5 + _lhs.m11 * _rhs.m9 + _lhs.m12 * _rhs.m13,
				_lhs.m13 * _rhs.m1 + _lhs.m14 * _rhs.m5 + _lhs.m15 * _rhs.m9 + _lhs.m16 * _rhs.m13,
				_lhs.m1 * _rhs.m2 + _lhs.m2 * _rhs.m6 + _lhs.m3 * _rhs.m10 + _lhs.m4 * _rhs.m14,
				_lhs.m5 * _rhs.m2 + _lhs.m6 * _rhs.m6 + _lhs.m7 * _rhs.m10 + _lhs.m8 * _rhs.m14,
				_lhs.m9 * _rhs.m2 + _lhs.m10 * _rhs.m6 + _lhs.m11 * _rhs.m10 + _lhs.m12 * _rhs.m14,
				_lhs.m13 * _rhs.m2 + _lhs.m14 * _rhs.m6 + _lhs.m15 * _rhs.m10 + _lhs.m16 * _rhs.m14,
				_lhs.m1 * _rhs.m3 + _lhs.m2 * _rhs.m7 + _lhs.m3 * _rhs.m11 + _lhs.m4 * _rhs.m15,
				_lhs.m5 * _rhs.m3 + _lhs.m6 * _rhs.m7 + _lhs.m7 * _rhs.m11 + _lhs.m8 * _rhs.m15,
				_lhs.m9 * _rhs.m3 + _lhs.m10 * _rhs.m7 + _lhs.m11 * _rhs.m11 + _lhs.m12 * _rhs.m15,
				_lhs.m13 * _rhs.m3 + _lhs.m14 * _rhs.m7 + _lhs.m15 * _rhs.m11 + _lhs.m16 * _rhs.m15,
				_lhs.m1 * _rhs.m4 + _lhs.m2 * _rhs.m8 + _lhs.m3 * _rhs.m12 + _lhs.m4 * _rhs.m16,
				_lhs.m5 * _rhs.m4 + _lhs.m6 * _rhs.m8 + _lhs.m7 * _rhs.m12 + _lhs.m8 * _rhs.m16,
				_lhs.m9 * _rhs.m4 + _lhs.m10 * _rhs.m8 + _lhs.m11 * _rhs.m12 + _lhs.m12 * _rhs.m16,
				_lhs.m13 * _rhs.m4 + _lhs.m14 * _rhs.m8 + _lhs.m15 * _rhs.m12 + _lhs.m16 * _rhs.m16
			);
		}

		public static Vec4 operator *(Vec4 _lhs, Mat4 _rhs)
		{
			return new Vec4(
				_lhs.x * _rhs.m1 + _lhs.y * _rhs.m5 + _lhs.z * _rhs.m9 + _lhs.w * _rhs.m13,
				_lhs.x * _rhs.m2 + _lhs.y * _rhs.m6 + _lhs.z * _rhs.m10 + _lhs.w * _rhs.m14,
				_lhs.x * _rhs.m3 + _lhs.y * _rhs.m7 + _lhs.z * _rhs.m11 + _lhs.w * _rhs.m15,
				_lhs.x * _rhs.m4 + _lhs.y * _rhs.m8 + _lhs.z * _rhs.m12 + _lhs.w * _rhs.m16
			);
		}

		public static Vec4 operator *(Mat4 _lhs, Vec4 _rhs)
		{
			return new Vec4(
				_lhs.m1 * _rhs.x + _lhs.m2 * _rhs.y + _lhs.m3 * _rhs.z + _lhs.m4 * _rhs.w,
				_lhs.m5 * _rhs.x + _lhs.m6 * _rhs.y + _lhs.m7 * _rhs.z + _lhs.m8 * _rhs.w,
				_lhs.m9 * _rhs.x + _lhs.m10 * _rhs.y + _lhs.m11 * _rhs.z + _lhs.m12 * _rhs.w,
				_lhs.m13 * _rhs.x + _lhs.m14 * _rhs.y + _lhs.m15 * _rhs.z + _lhs.m16 * _rhs.w
			);
		}

		public void SetRotationX(float _xRot)
		{
			float yLen = MathF.Sqrt(m5 * m5 + m6 * m6 + m7 * m7 + m8 * m8);
			float zLen = MathF.Sqrt(m9 * m9 + m10 * m10 + m11 * m11 + m12 * m12);

			float cos = MathF.Cos(_xRot);
			float sin = MathF.Sin(_xRot);

			m6 = cos * yLen;
			m10 = sin * zLen;
			m7 = -sin * yLen;
			m11 = cos * zLen;
		}

		public void SetRotationY(float _yRot)
		{
			float zLen = MathF.Sqrt(m9 * m9 + m10 * m10 + m11 * m11 + m12 * m12);
			float xLen = MathF.Sqrt(m1 * m1 + m2 * m2 + m3 * m3 + m4 * m4);

			float cos = MathF.Cos(_yRot);
			float sin = MathF.Sin(_yRot);

			m1 = cos * xLen;
			m9 = -sin * zLen;
			m3 = sin * xLen;
			m11 = cos * zLen;
		}

		public void SetRotationZ(float _zRot)
		{
			float xLen = MathF.Sqrt(m1 * m1 + m2 * m2 + m3 * m3 + m4 * m4);
			float yLen = MathF.Sqrt(m5 * m5 + m6 * m6 + m7 * m7 + m8 * m8);

			float cos = MathF.Cos(_zRot);
			float sin = MathF.Sin(_zRot);

			m1 = cos * xLen;
			m5 = sin * yLen;
			m2 = -sin * xLen;
			m6 = cos * yLen;
		}
	}
}