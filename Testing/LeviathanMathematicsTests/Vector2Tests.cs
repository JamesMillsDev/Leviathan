namespace Leviathan.Mathematics.Tests
{
	[TestClass]
	public class Vector2Tests : TestsBase
	{
		[TestMethod]
		public void Magnitude()
		{
			Vector2 vec = RandomVector2();

			float expected = MathF.Sqrt(MathF.Pow(vec.x, 2) + MathF.Pow(vec.y, 2));

			Assert.IsTrue(Leviamath.Approximately(vec.Magnitude, expected));
		}

		[TestMethod]
		public void SqrMagnitude()
		{
			Vector2 vec = RandomVector2();

			float expected = MathF.Pow(vec.x, 2) + MathF.Pow(vec.y, 2);

			Assert.IsTrue(Leviamath.Approximately(vec.SqrMagnitude, expected));
		}

		[TestMethod]
		public void Normalized()
		{
			Vector2 vec = RandomVector2();

			System.Numerics.Vector2 expected = System.Numerics.Vector2.Normalize(new System.Numerics.Vector2(vec.x, vec.y));
			vec = vec.Normalized;

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void Indexer()
		{
			Vector2 vec = RandomVector2();

			Assert.IsTrue(Compare(vec[0], vec.x) && Compare(vec[1], vec.y));
		}

		[TestMethod]
		public void XValue()
		{
			RandomXY(out float x, out float y);

			// ReSharper disable once UseObjectOrCollectionInitializer
			Vector2 vec = new(0, y);
			vec.x = x;

			Vector2 expected = new(x, y);

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void YValue()
		{
			RandomXY(out float x, out float y);

			// ReSharper disable once UseObjectOrCollectionInitializer
			Vector2 vec = new(x, 0);
			vec.y = y;

			Vector2 expected = new(x, y);

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void DefaultConstructor()
		{
			Vector2 vec = new();
			System.Numerics.Vector2 expected = new();

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void FloatConstructor()
		{
			RandomXY(out float x, out float y);

			Vector2 vec = new(x, y);
			System.Numerics.Vector2 expected = new(x, y);

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void VectorConstructor()
		{
			RandomXY(out float x, out float y);

			Vector2 vec = new(new System.Numerics.Vector2(x, y));
			System.Numerics.Vector2 expected = new(x, y);

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void Normalize()
		{
			Vector2 vec = RandomVector2();
			System.Numerics.Vector2 expected = new(vec.x, vec.y);

			vec.Normalise();
			expected = System.Numerics.Vector2.Normalize(expected);

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void Set()
		{
			RandomXY(out float x, out float y);

			Vector2 vec = new();
			System.Numerics.Vector2 expected = new(x, y);

			vec.Set(x, y);

			Assert.IsTrue(Compare(vec, expected));
		}

		[TestMethod]
		public void Equals()
		{
			RandomXY(out float x, out float y);

			Vector2 a = new(x, y);
			Vector2 b = new(x, y);

			Assert.IsTrue(a.Equals(b));
		}

		[TestMethod]
		public void Angle()
		{
			RandomXY(out float x, out float y);

			Vector2 vec = new(x, y);

			float output = Vector2.Angle(vec);
			float expected = MathF.Atan2(y, x);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void ClampMagnitude()
		{
			const float MAG_CLAMP = 30f;

			// Scale the vector way up to ensure it won't be below the clamp value
			Vector2 vec = RandomVector2() * 10000;
			vec = Vector2.ClampMagnitude(vec, MAG_CLAMP);

			Assert.IsTrue(Compare(vec.Magnitude, MAG_CLAMP));
		}

		[TestMethod]
		public void Distance()
		{
			Vector2 mlA = RandomVector2();
			System.Numerics.Vector2 snA = new(mlA.x, mlA.y);

			Vector2 mlB = RandomVector2();
			System.Numerics.Vector2 snB = new(mlB.x, mlB.y);

			float output = Vector2.Distance(mlA, mlB);
			float expected = System.Numerics.Vector2.Distance(snA, snB);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void Dot()
		{
			Vector2 mlA = RandomVector2();
			System.Numerics.Vector2 snA = new(mlA.x, mlA.y);

			Vector2 mlB = RandomVector2();
			System.Numerics.Vector2 snB = new(mlB.x, mlB.y);

			float output = Vector2.Dot(mlA, mlB);
			float expected = System.Numerics.Vector2.Dot(snA, snB);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void Lerp()
		{
			Vector2 mlA = RandomVector2();
			System.Numerics.Vector2 snA = new(mlA.x, mlA.y);

			Vector2 mlB = RandomVector2();
			System.Numerics.Vector2 snB = new(mlB.x, mlB.y);

			RandomValue(out float t, 0, 1);

			Vector2 output = Vector2.Lerp(mlA, mlB, t);
			System.Numerics.Vector2 expected = System.Numerics.Vector2.Lerp(snA, snB, t);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void LerpUnclamped()
		{
			Vector2 mlA = RandomVector2();
			System.Numerics.Vector2 snA = new(mlA.x, mlA.y);

			Vector2 mlB = RandomVector2();
			System.Numerics.Vector2 snB = new(mlB.x, mlB.y);

			RandomValue(out float t);

			Vector2 output = Vector2.LerpUnclamped(mlA, mlB, t);
			System.Numerics.Vector2 expected = System.Numerics.Vector2.Lerp(snA, snB, t);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void Min()
		{
			Vector2 mlA = RandomVector2();
			System.Numerics.Vector2 snA = new(mlA.x, mlA.y);

			Vector2 mlB = RandomVector2();
			System.Numerics.Vector2 snB = new(mlB.x, mlB.y);

			Vector2 output = Vector2.Min(mlA, mlB);
			System.Numerics.Vector2 expected = System.Numerics.Vector2.Min(snA, snB);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void Max()
		{
			Vector2 mlA = RandomVector2();
			System.Numerics.Vector2 snA = new(mlA.x, mlA.y);

			Vector2 mlB = RandomVector2();
			System.Numerics.Vector2 snB = new(mlB.x, mlB.y);

			Vector2 output = Vector2.Max(mlA, mlB);
			System.Numerics.Vector2 expected = System.Numerics.Vector2.Max(snA, snB);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void Reflect()
		{
			Vector2 mlDir = RandomVector2();
			System.Numerics.Vector2 snDir = new(mlDir.x, mlDir.y);

			Vector2 mlNorm = RandomVector2().Normalized;
			System.Numerics.Vector2 snNorm = System.Numerics.Vector2.Normalize(new System.Numerics.Vector2(mlNorm.x, mlNorm.y));

			Vector2 output = Vector2.Reflect(mlDir, mlNorm);
			System.Numerics.Vector2 expected = System.Numerics.Vector2.Reflect(snDir, snNorm);

			Assert.IsTrue(Compare(output, expected), $"Output: {output} - Expected: {expected}");
		}

		[TestMethod]
		public void Perpendicular()
		{
			Vector2 mlVec = RandomVector2();
			System.Numerics.Vector2 snVec = new(mlVec.x, mlVec.y);

			Vector2 output = Vector2.Perpendicular(mlVec);
			System.Numerics.Vector2 expected = new(-snVec.Y, snVec.X);

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void Scale()
		{
			Vector2 mlVec = RandomVector2();
			System.Numerics.Vector2 snVec = new(mlVec.x, mlVec.y);

			RandomValue(out float scalar);

			Vector2 output = Vector2.Scale(mlVec, scalar);
			System.Numerics.Vector2 expected = snVec * scalar;

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void SignedAngle()
		{
			RandomXY(out float x, out float y);

			Vector2 vec = new(x, y);
			float angle = Vector2.SignedAngle(vec);

			float expected = MathF.Atan2(y, x) - 180f;

			Assert.IsTrue(Compare(angle, expected));
		}

		[TestMethod]
		public void ImplicitVec2ToVector2Cast()
		{
			Vector2 vec = RandomVector2();
			System.Numerics.Vector2 casted = vec;

			Assert.AreEqual(new System.Numerics.Vector2(vec.x, vec.y), casted);
		}

		[TestMethod]
		public void ImplicitVector2ToVec2Cast()
		{
			RandomXY(out float x, out float y);

			System.Numerics.Vector2 vec = new System.Numerics.Vector2(x, y);
			Vector2 casted = vec;

			Assert.AreEqual(new Vector2(vec.X, vec.Y), casted);
		}

		[TestMethod]
		public void ImplicitVec3ToVec2Cast()
		{
			Vector3 vec = RandomVector3();
			Vector2 casted = vec;

			Assert.AreEqual(new Vector2(vec.x, vec.y), casted);
		}

		[TestMethod]
		public void ImplicitVec2ToVec3Cast()
		{
			Vector2 vec = RandomVector2();
			Vector3 casted = vec;

			Assert.AreEqual(new Vector3(vec.x, vec.y, 1), casted);
		}

		[TestMethod]
		public void AddOperator()
		{
			Vector2 mlA = RandomVector2();
			System.Numerics.Vector2 snA = new(mlA.x, mlA.y);

			Vector2 mlB = RandomVector2();
			System.Numerics.Vector2 snB = new(mlB.x, mlB.y);

			Vector2 output = mlA + mlB;
			System.Numerics.Vector2 expected = snA + snB;

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void SubtractOperator()
		{
			Vector2 mlA = RandomVector2();
			System.Numerics.Vector2 snA = new(mlA.x, mlA.y);

			Vector2 mlB = RandomVector2();
			System.Numerics.Vector2 snB = new(mlB.x, mlB.y);

			Vector2 output = mlA - mlB;
			System.Numerics.Vector2 expected = snA - snB;

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void EqualsOperator()
		{
			Vector2 mlA = RandomVector2();
			System.Numerics.Vector2 snA = new(mlA.x, mlA.y);

			Vector2 mlB = new(mlA.x, mlA.y);
			System.Numerics.Vector2 snB = new(snA.X, snA.Y);

			bool output = mlA == mlB;
			bool expected = snA == snB;

			Assert.AreEqual(output, expected);
		}

		[TestMethod]
		public void NotEqualsOperator()
		{
			Vector2 mlA = RandomVector2();
			System.Numerics.Vector2 snA = new(mlA.x, mlA.y);

			Vector2 mlB = RandomVector2();
			System.Numerics.Vector2 snB = new(mlB.x, mlB.y);

			bool output = mlA != mlB;
			bool expected = snA != snB;

			Assert.AreEqual(output, expected);
		}

		[TestMethod]
		public void PreScaleOperator()
		{
			RandomValue(out float scalar);

			Vector2 mlVec = RandomVector2();
			System.Numerics.Vector2 snVec = new(mlVec.x, mlVec.y);

			Vector2 output = scalar * mlVec;
			System.Numerics.Vector2 expected = scalar * snVec;

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void PostScaleOperator()
		{
			RandomValue(out float scalar);

			Vector2 mlVec = RandomVector2();
			System.Numerics.Vector2 snVec = new(mlVec.x, mlVec.y);

			Vector2 output = mlVec * scalar;
			System.Numerics.Vector2 expected = snVec * scalar;

			Assert.IsTrue(Compare(output, expected));
		}

		[TestMethod]
		public void DivideOperator()
		{
			RandomValue(out float scalar);

			Vector2 mlVec = RandomVector2();
			System.Numerics.Vector2 snVec = new(mlVec.x, mlVec.y);

			Vector2 output = mlVec / scalar;
			System.Numerics.Vector2 expected = snVec / scalar;

			Assert.IsTrue(Compare(output, expected));
		}
	}
}