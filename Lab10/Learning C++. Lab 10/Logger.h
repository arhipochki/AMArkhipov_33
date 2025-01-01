#pragma once

#include <string>

/**
 * @brief Класс логгера
 * 
 */
class Logger
{
private:
	/**
	 * @brief Метод записи текста в файл
	 * 
	 * @param message - сообщение, которое нужно записать
	 * @param file_name - название файла, куда будет записано сообщение
	 */
	void writeToFile(std::string message, std::string file_name);
	
	/**
	 * @brief Получаем текущее время и дату
	 * 
	 * @return Отформатированное время в виде строки 
	 */
	std::string getCurrentTime();
public:
	// Основной конструктор
	Logger() {}

	/**
	 * @brief Метод вывода сообщения с пометкой info
	 * 
	 * @param message - сообщение, которое требуется вывести
	 */
	void information(std::string message);

	/**
	 * @brief Метод вывода сообщения с пометкой warn
	 * 
	 * @param message - сообщение, которое требуется вывести
	 */
	void warning(std::string message);

	/**
	 * @brief Метод вывода сообщения с пометкой error
	 * 
	 * @param message - сообщение, которое требуется вывести
	 */
	void error(std::string message);
};

