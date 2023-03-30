using Raylib_cs;

using System.Xml;

namespace TestApp.Resources
{
	public struct Sprite
	{
		public string id;
		public int x;
		public int y;
		public int width;
		public int height;

		public Sprite(XmlElement _element)
		{
			id = "";
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			
			foreach(XmlAttribute attribute in _element.Attributes)
			{
				string name = attribute.Name;
				string value = attribute.Value;

				if(int.TryParse(value, out int iVal))
				{
					switch(name)
					{
						case nameof(x):
							x = iVal;
							break;
						case nameof(y):
							y = iVal;
							break;
						case nameof(width):
							width = iVal;
							break;
						case nameof(height):
							height = iVal;
							break;
					}
				}
				else
				{
					id = value;
				}
			}
		}

		public static implicit operator Rectangle(Sprite _sprite) => new(_sprite.x, _sprite.y, _sprite.width, _sprite.height);
	}
}