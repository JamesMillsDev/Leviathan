namespace Leviathan.Mathematics
{
	// ReSharper disable once InconsistentNaming
	public struct Matrix2x2
	{
		public static Matrix2x2 FromAngle(float _theta) => 
			new(Leviamath.Cos(_theta), Leviamath.Sin(_theta), -Leviamath.Sin(_theta), Leviamath.Cos(_theta));

		public float m1;
		public float m2;
		public float m3;
		public float m4;

		public Matrix2x2()
		{
			m1 = 1;
			m2 = 0;
			m3 = 1;
			m4 = 0;
		}
		
		public Matrix2x2(float _m1, float _m2, float _m3, float _m4)
		{
			m1 = _m1;
			m2 = _m2;
			m3 = _m3;
			m4 = _m4;
		}

		public static implicit operator float[](Matrix2x2 _mat) => new[] { _mat.m1, _mat.m2, _mat.m3, _mat.m4 };
	}
}