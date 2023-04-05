namespace Leviathan.Mathematics
{
	public static class MatrixMath
	{
		public static bool Multiply(out float[]? _output, float[] _matA, int _aRows, int _aCols, float[] _matB, int _bRows, int _bCols)
		{
			_output = null;

			if(_aCols != _bRows)
				return false;

			List<float> output = new();

			for(int i = 0; i < _aRows; i++)
			{
				for(int j = 0; j < _bCols; j++)
				{
					output.Add(0f);
					for(int k = 0; k < _bRows; k++)
					{
						int a = _aCols * i + j;
						int b = _bCols * k + j;
						output[_bCols * i + j] += _matA[a] * _matB[b];
					}
				}
			}

			_output = output.ToArray();
			
			return true;
		}
	}
}