using Leviathan.Mathematics;

using Newtonsoft.Json.Linq;

namespace Leviathan.Configuration.Converters.Math
{
	// ReSharper disable once InconsistentNaming
	public class Mat3Converter : IConfigConverter<Mat3>
	{
		public Mat3 Convert(JObject _jObject)
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

			return new Mat3(values);
		}
	}
}