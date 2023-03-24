using Leviathan.Mathematics;

namespace Leviathan.Mathematics.Tests
{
	[TestClass]
	public class ColorTests : TestsBase
	{
		[TestMethod]
		public void DefaultConstructor()
		{
			Color color = new();

			Assert.IsTrue(Compare(color, 0x00000000));
		}
		
		[TestMethod]
		public void ConstructorByteInt()
		{
			Color color = new(255, 255, 0, 255);

			Assert.IsTrue(Compare(color, 0xffff00ff));
		}
		
		[TestMethod]
		public void ConstructorUInt()
		{
			Color color = new(0xffff00ff);

			Assert.IsTrue(Compare(color, 0xffff00ff));
		}

		[TestMethod]
		public void GetRed()
		{
			Color color = new(0xa1ffffff);
			
			Assert.IsTrue(Compare(color.R, 161f));
		}

		[TestMethod]
		public void GetGreen()
		{
			Color color = new(0xffa1ffff);
			
			Assert.IsTrue(Compare(color.G, 161f));
		}

		[TestMethod]
		public void GetBlue()
		{
			Color color = new(0xffffa1ff);
			
			Assert.IsTrue(Compare(color.B, 161f));
		}

		[TestMethod]
		public void SetRed()
		{
			Color color = new(0x000000ff);
			color.R = 255;
			
			Assert.IsTrue(Compare(color, 0xff0000ff));
		}

		[TestMethod]
		public void SetGreen()
		{
			Color color = new(0x000000ff);
			color.G = 255;
			
			Assert.IsTrue(Compare(color, 0x00ff00ff));
		}

		[TestMethod]
		public void SetBlue()
		{
			Color color = new(0x000000ff);
			color.B = 255;
			
			Assert.IsTrue(Compare(color, 0x0000ffff));
		}

		[TestMethod]
		public void RaylibImplicitCast()
		{
			Color color = new(0xffffffff);
			Raylib_cs.Color rayColor = new(255, 255, 255, 255);
			
			Assert.IsTrue(Compare(color, rayColor));
		}

		[TestMethod]
		public void UIntImplicitCast()
		{
			Color color = new(0xffffffff);
			
			Assert.IsTrue(Compare(color, 0xffffffff));
		}
	}
}