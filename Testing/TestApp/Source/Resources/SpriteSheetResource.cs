using Leviathan.Resources;

using Raylib_cs;

using System.Xml;

namespace TestApp.Resources
{
	public class SpriteSheetResource : Resource<Texture2D>
	{
		public int FullWidth => Value.width;
		public int FullHeight => Value.height;
		
		protected override bool IsLoaded => resource.width != 0;

		private readonly Dictionary<string, Sprite> sprites = new();

		public Rectangle this[string _id] => sprites[_id];
		
		public SpriteSheetResource(string _path) : base(Raylib.LoadTexture, Raylib.UnloadTexture, "")
		{
			path = FillSheet(_path);
		}

		private string FillSheet(string _xmlPath)
		{
			XmlDocument xml = new XmlDocument();
			xml.LoadXml(File.ReadAllText(_xmlPath));

			foreach(Sprite sprite in from XmlElement element in xml.DocumentElement!.ChildNodes select new Sprite(element))
			{
				sprites.Add(sprite.id, sprite);
			}
			
			return _xmlPath.Replace("xml", "png").Replace("spritesheets", "textures");
		}
	}
}