using System.Text;

namespace Leviathan.Debugging
{
	public class Logger
	{
		private enum Level
		{
			Debug = -1,
			Info,
			Warning,
			Error,
			Exception
		}

		private static readonly Dictionary<Level, ConsoleColor> levelColors = new()
		{
			{ Level.Debug, ConsoleColor.White },
			{ Level.Info, ConsoleColor.White },
			{ Level.Warning, ConsoleColor.Yellow },
			{ Level.Error, ConsoleColor.Red },
			{ Level.Exception, ConsoleColor.Magenta },
		};

		// ReSharper disable once InconsistentNaming
		public string ID { get; }

		private readonly StringBuilder builder;

		public Logger(string _id)
		{
			ID = _id;
			builder = new StringBuilder();
		}

		public void LogDebug(string _message) => LogMessage(_message, Level.Debug);
		public void LogInfo(string _message) => LogMessage(_message, Level.Info);
		public void LogWarn(string _message) => LogMessage(_message, Level.Warning);
		public void LogError(string _message)
		{
			Console.ForegroundColor = levelColors[Level.Error];
			Console.WriteLine(BuildMessage(_message, Level.Error));
			Console.Write($"{GetStacktrace()}");
		}

		public void LogExceptionWithMessage(string _message, Exception _exception)
		{
			Console.ForegroundColor = levelColors[Level.Exception];
			Console.WriteLine(BuildMessage(_message, Level.Exception));
			Console.Write($"{_exception}\n{GetStacktrace()}");
		}

		public void LogException(Exception _exception)
		{
			Console.ForegroundColor = levelColors[Level.Exception];
			Console.Write($"{_exception}\n{GetStacktrace()}");
		}

		private void LogMessage(string _message, Level _level)
		{
			Console.ForegroundColor = levelColors[_level];
			Console.WriteLine(BuildMessage(_message, _level));
		}
		
		private string BuildMessage(string _message, Level _level)
		{
			builder.Clear();

			builder.Append($"[{DateTime.Now:HH:mm:ss}][{ID}|{_level.ToString().ToUpper()}] {_message}");

			return builder.ToString();
		}

		private string GetStacktrace()
		{
			string stacktrace = Environment.StackTrace;
			string[] stack = stacktrace.Split('\n');

			builder.Clear();
			for(int i = 3; i < stack.Length; i++)
			{
				builder.AppendLine(stack[i]);
			}

			return builder.ToString();
		}
	}
}