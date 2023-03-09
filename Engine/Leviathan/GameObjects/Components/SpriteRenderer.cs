using Leviathan.Mathematics;
using Leviathan.Resources;

using Raylib_cs;

using Color = Leviathan.Mathematics.Color;

namespace Leviathan.GameObjects.Components
{
	public class SpriteRenderer : Component
	{
		public string? Sprite
		{
			get => sprite;
			set
			{
				sprite = value;
				texture = sprite != null ? ResourceManager.Find<TextureResource, Texture2D>($"textures/{sprite}") : null;
			}
		}

		public Color? tint;

		private string? sprite;

		private TextureResource? texture;

		public override void Start(params object[] _data)
		{
			sprite = (string) _data[0];
			tint = _data.Length > 1 ? (Color) _data[1] : new Raylib_cs.Color(255, 255, 255, 255);

			texture = ResourceManager.Find<TextureResource, Texture2D>($"textures/{sprite}");
		}

		public override void Render()
		{
			if(GameObject is { Transform: { } } && texture != null && tint != null)
			{
				Vec2? position = GameObject.Transform.Position;
				Vec3? rotation = GameObject.Transform.Rotation;
				Vec2? scale = GameObject.Transform.Scale;

				Rectangle src = new()
				{
					x = 0,
					y = 0,
					width = texture.Width,
					height = texture.Height
				};

				Rectangle dst = new()
				{
					x = position.Value.x,
					y = position.Value.y,
					width = scale.Value.x,
					height = scale.Value.y
				};

				Raylib.DrawTexturePro(texture, src, dst, new Vec2(dst.width * .5f, dst.height * .5f), rotation.Value.x, (Color) tint);
			}
		}
	}
}