using Leviathan.Mathematics;
using Leviathan.Resources;

using Raylib_cs;

using System.Numerics;

using Color = Leviathan.Mathematics.Color;

namespace Leviathan.UI
{
	public class ImageWidget : Widget
	{
		private readonly TextureResource? image;
		
		public ImageWidget(Vec2 _position, Vec2 _size, string _imageId) : base(_position, _size)
		{
			image = ResourceManager.Find<TextureResource, Texture2D>($"Textures/{_imageId}");
		}

		public override void Render()
		{
			if(image == null)
				return;
			
			Raylib.DrawTexturePro(image, new Rectangle(0, 0, image.Width, image.Height), Rect, Vector2.Zero, 0, Raylib_cs.Color.WHITE);
		}
	}
}