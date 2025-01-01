#include "Logger.h"

#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>

void Logger::writeToFile(std::string message, std::string file_name)
{
	std::ofstream out(file_name, std::ios_base::app); // Открываем файл на дозапись
	out << message;
	out.close();
}

std::string Logger::getCurrentTime()
{
	std::time_t t = std::time(0);
	std::tm cur_time;
	localtime_s(&cur_time, &t);
	
	std::stringstream ss;

	ss << "[" << cur_time.tm_hour << ":" << cur_time.tm_min << ":" << cur_time.tm_sec << " ";
	ss << cur_time.tm_mday << "/" << cur_time.tm_mon << "/" << cur_time.tm_year + 1900 << "]";

	return ss.str();
}

void Logger::information(std::string message)
{
	std::stringstream ss;
	ss << getCurrentTime() << "[INFO]: " << message << "\n";
	std::cout << ss.str();
	writeToFile(ss.str(), "info.txt");
}

void Logger::warning(std::string message)
{
	std::stringstream ss;
	ss << getCurrentTime() << "[WARN]: " << message;
	std::cout << "\x1b[33;1m" << ss.str() << "\x1b[0m" << "\n";
	writeToFile(ss.str() + "\n", "warn.txt");
}

void Logger::error(std::string message)
{
	std::stringstream ss;
	ss << getCurrentTime() << "[ERROR]: " << message;
	std::cout << "\x1b[31;1m" << ss.str() << "\x1b[0m" << "\n";
	writeToFile(ss.str() + "\n", "error.txt");
}