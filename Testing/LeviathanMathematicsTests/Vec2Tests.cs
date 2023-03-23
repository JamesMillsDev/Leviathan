using Leviathan.Mathematics;

using System.Numerics;

namespace LeviathanMathematics.Tests
{
	[TestClass]
	public class Vec2Tests : TestsBase
	{
		[TestMethod]
		public void Magnitude()
		{
			Vec2 vec = RandomVector2();

			float expected = MathF.Sqrt(MathF.Pow(vec.x, 2) + MathF.Pow(vec.y, 2));

			Assert.IsTrue(LMath.Approximately(vec.Magnitude, expected));
		}

		[TestMethod]
		public void SqrMagnitude()
		{
			Vec2 vec = RandomVector2();

			float expected = MathF.Pow(vec.x, 2) + MathF.Pow(vec.y, 2);

			Assert.IsTrue(LMath.Approximately(vec.SqrMagnitude, expected));
		}

		[TestMethod]
		public void Normalized()
		{
			Vec2 vec = RandomVector2();

			Vector2 expected = Vector2.Normalize(new Vector2(vec.x, vec.y));
			vec = vec.Normalized;

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void Indexer()
		{
			Vec2 vec = RandomVector2();

			Assert.IsTrue(Compare(vec[0], vec.x) && Compare(vec[1], vec.y));
		}

		[TestMethod]
		public void XValue()
		{
			RandomXY(out float x, out float y);

			// ReSharper disable once UseObjectOrCollectionInitializer
			Vec2 vec = new(0, y);
			vec.x = x;

			Vec2 expected = new(x, y);

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void YValue()
		{
			RandomXY(out float x, out float y);

			// ReSharper disable once UseObjectOrCollectionInitializer
			Vec2 vec = new(x, 0);
			vec.y = y;

			Vec2 expected = new(x, y);

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void DefaultConstructor()
		{
			Vec2 vec = new();
			Vector2 expected = new();

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void FloatConstructor()
		{
			RandomXY(out float x, out float y);

			Vec2 vec = new(x, y);
			Vector2 expected = new(x, y);

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void VectorConstructor()
		{
			RandomXY(out float x, out float y);

			Vec2 vec = new(new Vector2(x, y));
			Vector2 expected = new(x, y);

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void Normalize()
		{
			Vec2 vec = RandomVector2();
			Vector2 expected = new(vec.x, vec.y);

			vec.Normalise();
			expected = Vector2.Normalize(expected);

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void Set()
		{
			RandomXY(out float x, out float y);

			Vec2 vec = new();
			Vector2 expected = new(x, y);

			vec.Set(x, y);

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void Equals()
		{
			RandomXY(out float x, out float y);

			Vec2 a = new(x, y);
			Vec2 b = new(x, y);

			Assert.IsTrue(a.Equals(b));
		}

		[TestMethod]
		public void Angle()
		{
			RandomXY(out float x, out float y);

			Vec2 vec = new(x, y);

			float output = Vec2.Angle(vec);
			float expected = MathF.Atan2(y, x);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void ClampMagnitude()
		{
			const float MAG_CLAMP = 30f;

			// Scale the vector way up to ensure it won't be below the clamp value
			Vec2 vec = RandomVector2() * 10000;
			vec = Vec2.ClampMagnitude(vec, MAG_CLAMP);

			Assert.IsTrue(Compare(vec.Magnitude, MAG_CLAMP));
		}

		[TestMethod]
		public void Distance()
		{
			Vec2 mlA = RandomVector2();
			Vector2 snA = new(mlA.x, mlA.y);

			Vec2 mlB = RandomVector2();
			Vector2 snB = new(mlB.x, mlB.y);

			float output = Vec2.Distance(mlA, mlB);
			float expected = Vector2.Distance(snA, snB);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void Dot()
		{
			Vec2 mlA = RandomVector2();
			Vector2 snA = new(mlA.x, mlA.y);

			Vec2 mlB = RandomVector2();
			Vector2 snB = new(mlB.x, mlB.y);

			float output = Vec2.Dot(mlA, mlB);
			float expected = Vector2.Dot(snA, snB);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void Lerp()
		{
			Vec2 mlA = RandomVector2();
			Vector2 snA = new(mlA.x, mlA.y);

			Vec2 mlB = RandomVector2();
			Vector2 snB = new(mlB.x, mlB.y);

			RandomValue(out float t, 0, 1);

			Vec2 output = Vec2.Lerp(mlA, mlB, t);
			Vector2 expected = Vector2.Lerp(snA, snB, t);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void LerpUnclamped()
		{
			Vec2 mlA = RandomVector2();
			Vector2 snA = new(mlA.x, mlA.y);

			Vec2 mlB = RandomVector2();
			Vector2 snB = new(mlB.x, mlB.y);

			RandomValue(out float t);

			Vec2 output = Vec2.LerpUnclamped(mlA, mlB, t);
			Vector2 expected = Vector2.Lerp(snA, snB, t);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void Min()
		{
			Vec2 mlA = RandomVector2();
			Vector2 snA = new(mlA.x, mlA.y);

			Vec2 mlB = RandomVector2();
			Vector2 snB = new(mlB.x, mlB.y);

			Vec2 output = Vec2.Min(mlA, mlB);
			Vector2 expected = Vector2.Min(snA, snB);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void Max()
		{
			Vec2 mlA = RandomVector2();
			Vector2 snA = new(mlA.x, mlA.y);

			Vec2 mlB = RandomVector2();
			Vector2 snB = new(mlB.x, mlB.y);

			Vec2 output = Vec2.Max(mlA, mlB);
			Vector2 expected = Vector2.Max(snA, snB);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void Reflect()
		{
			Vec2 mlDir = RandomVector2();
			Vector2 snDir = new(mlDir.x, mlDir.y);

			Vec2 mlNorm = RandomVector2().Normalized;
			Vector2 snNorm = Vector2.Normalize(new Vector2(mlNorm.x, mlNorm.y));

			Vec2 output = Vec2.Reflect(mlDir, mlNorm);
			Vector2 expected = Vector2.Reflect(snDir, snNorm);

			Assert.IsTrue(Compare(output, expected), $"Output: {output} - Expected: {expected}");
		}

		[TestMethod]
		public void Perpendicular()
		{
			Vec2 mlVec = RandomVector2();
			Vector2 snVec = new(mlVec.x, mlVec.y);

			Vec2 output = Vec2.Perpendicular(mlVec);
			Vector2 expected = new(-snVec.Y, snVec.X);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void Scale()
		{
			Vec2 mlVec = RandomVector2();
			Vector2 snVec = new(mlVec.x, mlVec.y);

			RandomValue(out float scalar);

			Vec2 output = Vec2.Scale(mlVec, scalar);
			Vector2 expected = snVec * scalar;

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void SignedAngle()
		{
			RandomXY(out float x, out float y);

			Vec2 vec = new(x, y);
			float angle = Vec2.SignedAngle(vec);

			float expected = MathF.Atan2(y, x) - 180f;

			Assert.IsTrue(Compare(angle, expected));
		}

		[TestMethod]
		public void ImplicitVec2ToVector2Cast()
		{
			Vec2 vec = RandomVector2();
			Vector2 casted = vec;

			Assert.AreEqual(new Vector2(vec.x, vec.y), casted);
		}

		[TestMethod]
		public void ImplicitVector2ToVec2Cast()
		{
			RandomXY(out float x, out float y);

			Vector2 vec = new Vector2(x, y);
			Vec2 casted = vec;

			Assert.AreEqual(new Vec2(vec.X, vec.Y), casted);
		}

		[TestMethod]
		public void ImplicitVec3ToVec2Cast()
		{
			Vec3 vec = RandomVector3();
			Vec2 casted = vec;

			Assert.AreEqual(new Vec2(vec.x, vec.y), casted);
		}

		[TestMethod]
		public void ImplicitVec2ToVec3Cast()
		{
			Vec2 vec = RandomVector2();
			Vec3 casted = vec;

			Assert.AreEqual(new Vec3(vec.x, vec.y, 1), casted);
		}

		[TestMethod]
		public void AddOperator()
		{
			Vec2 mlA = RandomVector2();
			Vector2 snA = new(mlA.x, mlA.y);

			Vec2 mlB = RandomVector2();
			Vector2 snB = new(mlB.x, mlB.y);

			Vec2 output = mlA + mlB;
			Vector2 expected = snA + snB;

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void SubtractOperator()
		{
			Vec2 mlA = RandomVector2();
			Vector2 snA = new(mlA.x, mlA.y);

			Vec2 mlB = RandomVector2();
			Vector2 snB = new(mlB.x, mlB.y);

			Vec2 output = mlA - mlB;
			Vector2 expected = snA - snB;

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void EqualsOperator()
		{
			Vec2 mlA = RandomVector2();
			Vector2 snA = new(mlA.x, mlA.y);

			Vec2 mlB = new(mlA.x, mlA.y);
			Vector2 snB = new(snA.X, snA.Y);

			bool output = mlA == mlB;
			bool expected = snA == snB;

			Assert.AreEqual(output, expected);
		}

		[TestMethod]
		public void NotEqualsOperator()
		{
			Vec2 mlA = RandomVector2();
			Vector2 snA = new(mlA.x, mlA.y);

			Vec2 mlB = RandomVector2();
			Vector2 snB = new(mlB.x, mlB.y);

			bool output = mlA != mlB;
			bool expected = snA != snB;

			Assert.AreEqual(output, expected);
		}

		[TestMethod]
		public void PreScaleOperator()
		{
			RandomValue(out float scalar);

			Vec2 mlVec = RandomVector2();
			Vector2 snVec = new(mlVec.x, mlVec.y);

			Vec2 output = scalar * mlVec;
			Vector2 expected = scalar * snVec;

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void PostScaleOperator()
		{
			RandomValue(out float scalar);

			Vec2 mlVec = RandomVector2();
			Vector2 snVec = new(mlVec.x, mlVec.y);

			Vec2 output = mlVec * scalar;
			Vector2 expected = snVec * scalar;

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void DivideOperator()
		{
			RandomValue(out float scalar);

			Vec2 mlVec = RandomVector2();
			Vector2 snVec = new(mlVec.x, mlVec.y);

			Vec2 output = mlVec / scalar;
			Vector2 expected = snVec / scalar;

			Assert.IsTrue(Compare(output, expected));
		}
	}
}