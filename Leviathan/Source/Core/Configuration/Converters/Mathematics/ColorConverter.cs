using Leviathan.Mathematics;

using Newtonsoft.Json.Linq;

namespace Leviathan.Configuration.Converters.Math
{
	/// <summary>Converts <see cref="JObject"/> to <see cref="Color"/>.</summary>
	public class ColorConverter : IConfigConverter<Color>
	{
		public static ColorConverter Instance { get; } = new();
			
		public Color Convert(JObject _jObject) => new((int) _jObject["r"]!, (int) _jObject["g"]!, (int) _jObject["b"]!, (int) _jObject["a"]!);
	}
}