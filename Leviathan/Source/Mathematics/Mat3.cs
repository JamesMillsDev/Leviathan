namespace Leviathan.Mathematics
{
	public struct Mat3
	{
		public float m1, m2, m3, m4, m5, m6, m7, m8, m9;

		public Mat3()
		{
			m1 = 1;
			m2 = 0;
			m3 = 0;
			m4 = 0;
			m5 = 1;
			m6 = 0;
			m7 = 0;
			m8 = 0;
			m9 = 1;
		}

		public Mat3(IReadOnlyList<float> _values)
		{
			m1 = _values[0];
			m2 = _values[1];
			m3 = _values[2];
			m4 = _values[3];
			m5 = _values[4];
			m6 = _values[5];
			m7 = _values[6];
			m8 = _values[7];
			m9 = _values[8];
		}

		public Mat3(float _m1, float _m4, float _m7, float _m2, float _m5, float _m8, float _m3, float _m6, float _m9)
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
		}

		public static Mat3 CreateTranslation(float _tx, float _ty)
		{
			return new Mat3(
				1, 0, _tx,
				0, 1, _ty,
				0, 0, 1
			);
		}

		public static Mat3 CreateScale(float _sx, float _sy)
		{
			return new Mat3(
				_sx, 0, 0,
				0, _sy, 0,
				0, 0, 1
			);
		}

		public static Mat3 CreateScale(Vec2 _scale) => CreateScale(_scale.x, _scale.y);

		public static Mat3 CreateZRotation(float _rot)
		{
			float cos = MathF.Cos(_rot);
			float sin = MathF.Sin(_rot);

			return new Mat3(
				cos, -sin, 0,
				sin, cos, 0,
				0, 0, 1
			);
		}

		public static Mat3 CreateXRotation(float _rot)
		{
			float cos = MathF.Cos(_rot);
			float sin = MathF.Sin(_rot);

			return new Mat3(
				// xa  ya  za
				1, 0, 0, // x
				0, cos, -sin, // y
				0, sin, cos // z
			);
		}

		public static Mat3 CreateYRotation(float _rot)
		{
			float cos = MathF.Cos(_rot);
			float sin = MathF.Sin(_rot);

			return new Mat3(
				//xa  ya  za
				cos, 0, sin, // x
				0, 1, 0, // y
				-sin, 0, cos // z
			);
		}

		public static Mat3 CreateRotation(Vec3 _deg2Rad) => CreateXRotation(_deg2Rad.x) * CreateYRotation(_deg2Rad.y) * CreateZRotation(_deg2Rad.z);

		public void SetRotationX(float _xRot)
		{
			float yLen = MathF.Sqrt(m4 * m4 + m5 * m5 + m6 * m6);
			float zLen = MathF.Sqrt(m7 * m7 + m8 * m8 + m9 * m9);

			float cos = MathF.Cos(_xRot);
			float sin = MathF.Sin(_xRot);

			m5 = cos * yLen;
			m8 = -sin * zLen;
			m6 = sin * yLen;
			m9 = cos * zLen;
		}

		public void SetRotationY(float _yRot)
		{
			float zLen = MathF.Sqrt(m7 * m7 + m8 * m8 + m9 * m9);
			float xLen = MathF.Sqrt(m1 * m1 + m2 * m2 + m3 * m3);

			float cos = MathF.Cos(_yRot);
			float sin = MathF.Sin(_yRot);

			m1 = cos * xLen;
			m7 = sin * zLen;
			m3 = -sin * xLen;
			m9 = cos * zLen;
		}

		public void SetRotationZ(float _zRot)
		{
			float xLen = MathF.Sqrt(m1 * m1 + m2 * m2 + m3 * m3);
			float yLen = MathF.Sqrt(m4 * m4 + m5 * m5 + m6 * m6);

			float cos = MathF.Cos(_zRot);
			float sin = MathF.Sin(_zRot);

			m1 = cos * xLen;
			m4 = -sin * yLen;
			m2 = sin * xLen;
			m5 = cos * yLen;
		}

		public float GetRotationX()
		{
			return MathF.Atan2(m2, m1);
		}

		public float GetRotationY()
		{
			return MathF.Atan2(-m4, m5);
		}

		public float GetRotationZ()
		{
			return MathF.Atan2(m7, m9);
		}

		public Vec3 GetRotation() => new Vec3(GetRotationX() * Math.RAD2DEG, GetRotationY() * Math.RAD2DEG, GetRotationZ() * Math.RAD2DEG);

		public void SetTranslation(float _tx, float _ty)
		{
			m7 = _tx;
			m8 = _ty;
		}

		public void Translate(float _xAmount, float _yAmount)
		{
			m7 += _xAmount;
			m8 += _yAmount;
		}

		public Vec2 Translation
		{
			get => new(m7, m8);
			set
			{
				m7 = value.x;
				m8 = value.y;
			}
		}

		public void SetScale(float _sx, float _sy)
		{
			float xALen = MathF.Sqrt(m1 * m1 + m2 * m2 + m3 * m3);
			float yALen = MathF.Sqrt(m4 * m4 + m5 * m5 + m6 * m6);

			if(xALen > 0)
			{
				m1 = (m1 / xALen) * _sx;
				m2 = (m2 / xALen) * _sx;
				m3 = (m3 / xALen) * _sx;
			}

			if(yALen > 0)
			{
				m4 = (m4 / yALen) * _sy;
				m5 = (m5 / yALen) * _sy;
				m6 = (m6 / yALen) * _sy;
			}
		}

		public Vec2 GetScale()
		{
			float xALen = MathF.Sqrt(m1 * m1 + m2 * m2 + m3 * m3);
			float yALen = MathF.Sqrt(m4 * m4 + m5 * m5 + m6 * m6);
			return new Vec2(xALen, yALen);
		}

		public Vec2 Scale
		{
			get => GetScale();
			set => SetScale(value.x, value.y);
		}

		public static Mat3 operator *(Mat3 _lhs, Mat3 _rhs)
		{
			return new Mat3(
				_lhs.m1 * _rhs.m1 + _lhs.m2 * _rhs.m4 + _lhs.m3 * _rhs.m7,
				_lhs.m4 * _rhs.m1 + _lhs.m5 * _rhs.m4 + _lhs.m6 * _rhs.m7,
				_lhs.m7 * _rhs.m1 + _lhs.m8 * _rhs.m4 + _lhs.m9 * _rhs.m7,
				_lhs.m1 * _rhs.m2 + _lhs.m2 * _rhs.m5 + _lhs.m3 * _rhs.m8,
				_lhs.m4 * _rhs.m2 + _lhs.m5 * _rhs.m5 + _lhs.m6 * _rhs.m8,
				_lhs.m7 * _rhs.m2 + _lhs.m8 * _rhs.m5 + _lhs.m9 * _rhs.m8,
				_lhs.m1 * _rhs.m3 + _lhs.m2 * _rhs.m6 + _lhs.m3 * _rhs.m9,
				_lhs.m4 * _rhs.m3 + _lhs.m5 * _rhs.m6 + _lhs.m6 * _rhs.m9,
				_lhs.m7 * _rhs.m3 + _lhs.m8 * _rhs.m6 + _lhs.m9 * _rhs.m9
			);
		}

		public static Vec3 operator *(Vec3 _lhs, Mat3 _rhs)
		{
			return new Vec3(
				_lhs.x * _rhs.m1 + _lhs.y * _rhs.m4 + _lhs.z * _rhs.m7,
				_lhs.x * _rhs.m2 + _lhs.y * _rhs.m5 + _lhs.z * _rhs.m8,
				_lhs.x * _rhs.m3 + _lhs.y * _rhs.m6 + _lhs.z * _rhs.m9
			);
		}

		public static Vec3 operator *(Mat3 _lhs, Vec3 _rhs)
		{
			return new Vec3(
				_lhs.m1 * _rhs.x + _lhs.m2 * _rhs.y + _lhs.m3 * _rhs.z,
				_lhs.m4 * _rhs.x + _lhs.m5 * _rhs.y + _lhs.m6 * _rhs.z,
				_lhs.m7 * _rhs.x + _lhs.m8 * _rhs.y + _lhs.m9 * _rhs.z
			);
		}

		public Vec2 TransformPoint(Vec2 _point)
		{
			return new Vec2(
				_point.x * m1 + _point.y * m4 + m7,
				_point.x * m2 + _point.y * m5 + m8);
		}

		public Vec2 TransformVector(Vec2 _vec)
		{
			return new Vec2(
				_vec.x * m1 + _vec.y * m4,
				_vec.x * m2 + _vec.y * m5);
		}
	}
}