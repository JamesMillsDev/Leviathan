using Leviathan.Mathematics;

namespace Leviathan.UI
{
	public struct ColorBlock
	{
		public Color normal;
		public Color hovered;
		public Color selected;
		public Color disabled;

		public ColorBlock()
		{
			normal = 0xffffffff;
			hovered = 0xeeeeeeff;
			selected = 0xaaaaaaff;
			disabled = 0xffffff99;
		}
	}
}