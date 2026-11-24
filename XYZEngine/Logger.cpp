#include "pch.h"
#include "Logger.h"
#include <iostream>

namespace XYZEngine
{
	namespace
	{
		std::string LogLevelToString(LogLevel level)
		{
			switch (level)
			{
			case LogLevel::INFO:
				return "[INFO]";
				
			case LogLevel::WARNING:
				return "[WARNING]";

			case LogLevel::ERROR:
				return "[ERROR]";

			default:
				return "[UNKNOWN]";
			}
		}
	}

	void ConsoleSink::Log(LogLevel level, const std::string& message)
	{
		std::cout << LogLevelToString(level) << " " << message << std::endl;
	}

	FileSink::FileSink(const std::string& filename)
	{
		logFile.open(filename, std::ios::app);
	}

	FileSink::~FileSink()
	{
		if (logFile.is_open())
		{
			logFile.close();
		}
	}

	void FileSink::Log(LogLevel level, const std::string& message)
	{
		if (logFile)
		{
			logFile << LogLevelToString(level) << " " << message << std::endl;
		}
	}

	void Logger::AddSink(std::shared_ptr<LogSink> sink)
	{
		sinks.push_back(sink);
	}

	void Logger::Log(LogLevel level, const std::string& message)
	{
		std::lock_guard<std::mutex> lock(logMutex);

		for (auto& sink : sinks)
		{
			sink->Log(level, message);
		}
	}

	void Logger::Info(const std::string& message)
	{
		Log(LogLevel::INFO, message);
	}

	void Logger::Warning(const std::string& message)
	{
		Log(LogLevel::WARNING, message);
	}

	void Logger::Error(const std::string& message)
	{
		Log(LogLevel::ERROR, message);
	}

	LoggerRegistry& LoggerRegistry::Instance()
	{
		static LoggerRegistry instance;
		return instance;
	}

	std::shared_ptr<Logger> LoggerRegistry::GetLogger(const std::string& name)
	{
		std::lock_guard<std::mutex> lock(registryMutex);

		auto logger = loggers.find(name);

		if (logger != loggers.end())
		{
			return logger->second;
		}

		return defaultLogger;
	}

	void LoggerRegistry::RegisterLogger(const std::string& name, std::shared_ptr<Logger> logger)
	{
		std::lock_guard<std::mutex> lock(registryMutex);

		loggers[name] = logger;
	}

	void LoggerRegistry::SetDefaultLogger(std::shared_ptr<Logger> logger)
	{
		defaultLogger = logger;
	}

	void SetupLogger()
	{
		auto logger = std::make_shared<Logger>();

		logger->AddSink(std::make_shared<ConsoleSink>());

		logger->AddSink(std::make_shared<FileSink>("log.txt"));

		LoggerRegistry::Instance().RegisterLogger("global", logger);

		LoggerRegistry::Instance().SetDefaultLogger(logger);
	}
}