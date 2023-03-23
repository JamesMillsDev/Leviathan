using Leviathan.Mathematics;

using Newtonsoft.Json.Linq;

namespace Leviathan.Configuration.Converters.Math
{
	/// <summary>Converts <see cref="JObject"/> to <see cref="Vector2Int"/>.</summary>
	public class Int2Converter : IConfigConverter<Vector2Int>
	{
		public static Int2Converter Instance { get; } = new();

		public Vector2Int Convert(JObject _jObject) => new((int) _jObject["x"]!, (int) _jObject["y"]!);
	}
}