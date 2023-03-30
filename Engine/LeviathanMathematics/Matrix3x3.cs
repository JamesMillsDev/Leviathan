namespace Leviathan.Mathematics
{
	// ReSharper disable once InconsistentNaming
	public struct Matrix3x3
	{
		public float m1, m2, m3, m4, m5, m6, m7, m8, m9;

		public Matrix3x3()
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

		public Matrix3x3(IReadOnlyList<float> _values)
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

		public Matrix3x3(float _m1, float _m4, float _m7, float _m2, float _m5, float _m8, float _m3, float _m6, float _m9)
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

		public static Matrix3x3 CreateTranslation(float _tx, float _ty)
		{
			return new Matrix3x3(
			                     1, 0, _tx,
			                     0, 1, _ty,
			                     0, 0, 1
			                    );
		}

		public static Matrix3x3 CreateTranslation(Vector2 _pos) => CreateTranslation(_pos.x, _pos.y);

		public static Matrix3x3 CreateScale(float _sx, float _sy)
		{
			return new Matrix3x3(
			                     _sx, 0, 0,
			                     0, _sy, 0,
			                     0, 0, 1
			                    );
		}

		public static Matrix3x3 CreateScale(Vector2 _scale) => CreateScale(_scale.x, _scale.y);

		public static Matrix3x3 CreateZRotation(float _rot)
		{
			float cos = MathF.Cos(_rot);
			float sin = MathF.Sin(_rot);

			return new Matrix3x3(
			                     cos, -sin, 0,
			                     sin, cos, 0,
			                     0, 0, 1
			                    );
		}

		public static Matrix3x3 CreateXRotation(float _rot)
		{
			float cos = MathF.Cos(_rot);
			float sin = MathF.Sin(_rot);

			return new Matrix3x3(
			                     // xa  ya  za
			                     1, 0, 0, // x
			                     0, cos, -sin, // y
			                     0, sin, cos // z
			                    );
		}

		public static Matrix3x3 CreateYRotation(float _rot)
		{
			float cos = MathF.Cos(_rot);
			float sin = MathF.Sin(_rot);

			return new Matrix3x3(
			                     //xa  ya  za
			                     cos, 0, sin, // x
			                     0, 1, 0, // y
			                     -sin, 0, cos // z
			                    );
		}

		public static Matrix3x3 CreateRotation(Vector3 _deg2Rad) => CreateXRotation(_deg2Rad.x) * CreateYRotation(_deg2Rad.y) * CreateZRotation(_deg2Rad.z);

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

		public Vector2 TransformPoint(Vector2 _point)
		{
			return new Vector2(
			                   _point.x * m1 + _point.y * m4 + m7,
			                   _point.x * m2 + _point.y * m5 + m8);
		}

		public Vector2 TransformVector(Vector2 _vec)
		{
			return new Vector2(
			                   _vec.x * m1 + _vec.y * m4,
			                   _vec.x * m2 + _vec.y * m5);
		}

		public Vector3 GetRotation() => new Vector3(GetRotationX() * LMath.RAD_2_DEG, GetRotationY() * LMath.RAD_2_DEG, GetRotationZ() * LMath.RAD_2_DEG);

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

		public Vector2 Translation
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

		public Vector2 GetScale()
		{
			float xALen = MathF.Sqrt(m1 * m1 + m2 * m2 + m3 * m3);
			float yALen = MathF.Sqrt(m4 * m4 + m5 * m5 + m6 * m6);

			return new Vector2(xALen, yALen);
		}

		public Vector2 Scale
		{
			get => GetScale();
			set => SetScale(value.x, value.y);
		}

		public static Matrix3x3 operator *(Matrix3x3 _lhs, Matrix3x3 _rhs)
		{
			return new Matrix3x3(
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

		public static Vector3 operator *(Vector3 _lhs, Matrix3x3 _rhs)
		{
			return new Vector3(
			                   _lhs.x * _rhs.m1 + _lhs.y * _rhs.m4 + _lhs.z * _rhs.m7,
			                   _lhs.x * _rhs.m2 + _lhs.y * _rhs.m5 + _lhs.z * _rhs.m8,
			                   _lhs.x * _rhs.m3 + _lhs.y * _rhs.m6 + _lhs.z * _rhs.m9
			                  );
		}

		public static Vector3 operator *(Matrix3x3 _lhs, Vector3 _rhs)
		{
			return new Vector3(
			                   _lhs.m1 * _rhs.x + _lhs.m2 * _rhs.y + _lhs.m3 * _rhs.z,
			                   _lhs.m4 * _rhs.x + _lhs.m5 * _rhs.y + _lhs.m6 * _rhs.z,
			                   _lhs.m7 * _rhs.x + _lhs.m8 * _rhs.y + _lhs.m9 * _rhs.z
			                  );
		}

		public static implicit operator Matrix3x3(float[] _mat) =>
			new(_mat[0], _mat[1], _mat[2],
			    _mat[3], _mat[4], _mat[5],
			    _mat[6], _mat[7], _mat[8]);

		public static implicit operator float[](Matrix3x3 _mat) => new[]
		{
			_mat.m1, _mat.m4, _mat.m7,
			_mat.m2, _mat.m5, _mat.m8,
			_mat.m3, _mat.m6, _mat.m9
		};
	}
}