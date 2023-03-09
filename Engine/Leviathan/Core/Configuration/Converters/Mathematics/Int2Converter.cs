using Leviathan.Mathematics;

using Newtonsoft.Json.Linq;

namespace Leviathan.Configuration.Converters.Math
{
	/// <summary>Converts <see cref="JObject"/> to <see cref="Int2"/>.</summary>
	public class Int2Converter : IConfigConverter<Int2>
	{
		public static Int2Converter Instance { get; } = new();

		public Int2 Convert(JObject _jObject) => new((int) _jObject["x"]!, (int) _jObject["y"]!);
	}
}