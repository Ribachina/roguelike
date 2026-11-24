#pragma once
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

#define LOG_INFO(message) XYZEngine::LoggerRegistry::Instance().GetLogger("global")->Info(message)
#define LOG_WARNING(message) XYZEngine::LoggerRegistry::Instance().GetLogger("global")->Warning(message)
#define LOG_ERROR(message) XYZEngine::LoggerRegistry::Instance().GetLogger("global")->Error(message)

namespace XYZEngine
{
	enum class LogLevel
	{
		INFO,
		WARNING,
		ERROR
	};

	class LogSink
	{
	public:
		virtual void Log(LogLevel level, const std::string& message) = 0;

		virtual ~LogSink() = default;
	};

	class ConsoleSink : public LogSink
	{
	public:
		void Log(LogLevel level, const std::string& message) override;
	};

	class FileSink : public LogSink
	{
	public:
		FileSink(const std::string& filename);

		void Log(LogLevel level, const std::string& message) override;

		~FileSink();

	private:
		std::ofstream logFile;
	};

	class Logger
	{
	public:
		void AddSink(std::shared_ptr<LogSink> sink);

		void Log(LogLevel level, const std::string& message);

		void Info(const std::string& message);
		void Warning(const std::string& message);
		void Error(const std::string& message);

	private:
		std::vector<std::shared_ptr<LogSink>> sinks;
		std::mutex logMutex;
	};

	class LoggerRegistry
	{
	public:
		static LoggerRegistry& Instance();

		std::shared_ptr<Logger> GetLogger(const std::string& name);

		void RegisterLogger(const std::string& name, std::shared_ptr<Logger> logger);

		void SetDefaultLogger(std::shared_ptr<Logger> logger);

	private:
		LoggerRegistry() = default;

		std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;

		std::shared_ptr<Logger> defaultLogger = nullptr;

		std::mutex registryMutex;
	};

	void SetupLogger();
}
