using Leviathan.Mathematics;

using Newtonsoft.Json.Linq;

namespace Leviathan.Configuration.Converters.Math
{
	/// <summary>Converts <see cref="JObject"/> to <see cref="Vector2"/>.</summary>
	public class Vec2Converter : IConfigConverter<Vector2>
	{
		public Vector2 Convert(JObject _jObject) => new((int) _jObject["x"]!, (int) _jObject["y"]!);
	}
}