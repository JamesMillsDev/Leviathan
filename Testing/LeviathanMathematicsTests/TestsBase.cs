using Leviathan.Mathematics;

namespace LeviathanMathematics.Tests
{
	public class TestsBase
	{
		// const float DEFAULT_TOLERANCE = float.Epsilon;
		protected const float DEFAULT_TOLERANCE = 0.00001f;

		protected static bool Compare(float _a, float _b)
		{
			return LMath.Approximately(_a, _b);
		}

		protected static bool Compare(Color _a, Color _b) => Compare((float)_a.R, _b.R) && Compare((float)_a.G, _b.G) && Compare((float)_a.B, _b.B) && Compare((float)_a.A, _b.A);
        
		protected static bool Compare(Vector2 _a, Vector2 _b) => Compare(_a.x, _b.x) && Compare(_a.y, _b.y);

		protected static bool Compare(Vector3 _a, Vector3 _b) => Compare(_a.x, _b.x) && Compare(_a.y, _b.y) && Compare(_a.z, _b.z);

		protected static bool Compare(Vector4 _a, Vector4 _b) => Compare(_a.x, _b.x) && Compare(_a.y, _b.y) && Compare(_a.z, _b.z) && Compare(_a.w, _b.w);

		protected static bool Compare(Matrix3x3 _a, Matrix3x3 _b)
		{
		    return
		        Compare(_a.m1, _b.m1) && Compare(_a.m2, _b.m2) && Compare(_a.m3, _b.m3) &&
		        Compare(_a.m4, _b.m4) && Compare(_a.m5, _b.m5) && Compare(_a.m6, _b.m6) &&
		        Compare(_a.m7, _b.m7) && Compare(_a.m8, _b.m8) && Compare(_a.m9, _b.m9);
		}

		protected static bool Compare(Matrix4x4 _a, Matrix4x4 _b)
		{
		    return
		        Compare(_a.m1, _b.m1) &&   Compare(_a.m2, _b.m2) &&   Compare(_a.m3, _b.m3) &&   Compare(_a.m4, _b.m4)   &&
		        Compare(_a.m5, _b.m5) &&   Compare(_a.m6, _b.m6) &&   Compare(_a.m7, _b.m7) &&   Compare(_a.m8, _b.m8)   &&
		        Compare(_a.m9, _b.m9) &&   Compare(_a.m10, _b.m10) && Compare(_a.m11, _b.m11) && Compare(_a.m12, _b.m12) &&
		        Compare(_a.m13, _b.m13) && Compare(_a.m14, _b.m14) && Compare(_a.m15, _b.m15) && Compare(_a.m16, _b.m16);
		}
		
		// ReSharper disable once InconsistentNaming
		protected static void RandomValue(out float _val, float _min = -100, float _max = 100)
		{
			Random rand = new(DateTime.Now.Millisecond);

			_val = LMath.Remap(rand.NextSingle(), 0, 1, _min, _max);
		}
		
		// ReSharper disable once InconsistentNaming
		protected static void RandomXY(out float _x, out float _y)
		{
			Random rand = new(DateTime.Now.Millisecond);

			_x = LMath.Remap(rand.NextSingle(), 0, 1, -100, 100);
			_y = LMath.Remap(rand.NextSingle(), 0, 1, -100, 100);
		}
		
		// ReSharper disable once InconsistentNaming
		protected static void RandomXYZ(out float _x, out float _y, out float _z)
		{
			Random rand = new(DateTime.Now.Millisecond);

			_x = LMath.Remap(rand.NextSingle(), 0, 1, -100, 100);
			_y = LMath.Remap(rand.NextSingle(), 0, 1, -100, 100);
			_z = LMath.Remap(rand.NextSingle(), 0, 1, -100, 100);
		}

		protected static Vector2 RandomVector2()
		{
			RandomXY(out float x, out float y);

			return new Vector2(x, y);
		}

		protected static Vector3 RandomVector3()
		{
			RandomXYZ(out float x, out float y, out float z);

			return new Vector3(x, y, z);
		}
	}
}