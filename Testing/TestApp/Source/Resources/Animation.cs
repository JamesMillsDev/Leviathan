using Leviathan;
using Leviathan.Resources;

using Raylib_CsLo;

using System.Xml;

namespace TestApp.Resources
{
	public struct Animation
	{
		public struct Frame
		{
			public readonly string id;
			public readonly float time;

			private readonly Rectangle frameRect;

			public Frame(XmlElement _element, SpriteSheetResource? _resource)
			{
				frameRect = new Rectangle();

				XmlAttributeCollection attributes = _element.Attributes;
				
				XmlAttribute? idAttribute = attributes["id"];
				id = idAttribute != null ? idAttribute.Value : "";
				
				XmlAttribute? timeAttribute = attributes["time"];
				time = timeAttribute != null ? float.Parse(timeAttribute.Value) : 0;

				if(_resource != null)
					frameRect = _resource[$"frame_{id}"];
			}

			public static implicit operator Rectangle(Frame _frame) => _frame.frameRect;
		}

		private readonly float speed;
		private readonly List<Frame> frames;
		private readonly SpriteSheetResource? spriteSheet;

		private int currentFrame;
		private float time;

		public Animation(string _xmlFile)
		{
			XmlDocument xml = new XmlDocument();
			xml.LoadXml(File.ReadAllText(_xmlFile));
			
			speed = 0;
			frames = new List<Frame>();
			spriteSheet = null;

			currentFrame = 0;
			time = 0;

			XmlElement? element = xml.DocumentElement;
			if(element == null)
				return;

			XmlAttribute? speedAttribute = element.Attributes["speed"];
			if(speedAttribute != null)
				speed = float.Parse(speedAttribute.Value);

			XmlAttribute? spriteSheetAttribute = element.Attributes["spritesheet"];
			if(spriteSheetAttribute != null)
				spriteSheet = ResourceManager.Find<SpriteSheetResource, Texture>($"spritesheets/{spriteSheetAttribute.Value}");
			
			foreach(XmlElement frameElement in element.ChildNodes)
				frames.Add(new Frame(frameElement, spriteSheet));
		}

		public void Tick(out Rectangle _frame, out Texture? _texture)
		{
			time += Time.deltaTime * speed;

			Frame frame = frames[currentFrame];
			if(time >= frame.time)
			{
				time = 0;
				currentFrame++;
				
				if(currentFrame > frames.Count)
					currentFrame = 0;
			}

			_frame = frame;
			_texture = spriteSheet?.Value;
		}
	}
}