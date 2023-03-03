using Leviathan.Mathematics;

using Newtonsoft.Json.Linq;

namespace Leviathan.Configuration.Converters.Math
{
	/// <summary>Converts <see cref="JObject"/> to <see cref="Vec2"/>.</summary>
	public class Vec2Converter : IConfigConverter<Vec2>
	{
		public Vec2 Convert(JObject _jObject) => new((int) _jObject["x"]!, (int) _jObject["y"]!);
	}
}