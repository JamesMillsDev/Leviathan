using Leviathan.Mathematics;

using Newtonsoft.Json.Linq;

namespace Leviathan.Configuration.Converters.Math
{
	// ReSharper disable once InconsistentNaming
	public class Mat3Converter : IConfigConverter<Matrix3x3>
	{
		public Matrix3x3 Convert(JObject _jObject)
		{
			List<float> values = new();
			JToken? trans = _jObject.Value<JToken?>("transform");
			if(trans != null)
			{
				foreach(JToken? value in trans)
				{
					JProperty? v = value.Value<JProperty>();
					values.Add((float)v!.Value!);
				}
			}

			return new Matrix3x3(values);
		}
	}
}