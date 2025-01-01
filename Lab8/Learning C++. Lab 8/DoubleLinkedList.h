#pragma once

#include <iostream>
#include <iterator>
#include <cstddef>

/*
* Класс кастомного двусвязного списка
* 
* @param Node - класс звена
* @param first - указатель на первое звено
* @param last - указатель на последнее
* @param length - длина цепи
*/
template<typename T>
class DoubleLinkedList
{
protected:

	/*
	* 
	* Класс звена
	* 
	* @param value - значение, которое будет хранить звено
	* @param prev - указатель на предыдущее звено
	* @param next - указатель на следующее звено
	*/
	class Node
	{
	public:
		T value;
		Node* prev;
		Node* next;
		
		// Пустой конструктор
		Node() : prev(nullptr), next(nullptr) {}
	};

	Node* first = nullptr;
	Node* last = nullptr;

	int length = 0;

public:

	using iterator_category = std::bidirectional_iterator_tag;	// Категория итератора (двунаправленный)
	using difference_type = std::ptrdiff_t;						// Число типа рузультата вычитания двух указателей
	using value_type = T;										// Тип указателя
	using pointer = Node*;										// Указатель
	using reference = T&;										// Ссылка

	/*
	* Класс прямого итератора
	*	
	* @param m_ptr - указатель на звено 
	*/
	class Iterator
	{
	protected:
		pointer m_ptr;

	public:
		// Пустой конструктор
		Iterator() {}

		/*
		* Основной конструктор
		* 
		* @param ptr - указатель
		*/
		Iterator(pointer ptr) : m_ptr(ptr) { }

		// Перегрузка оператора разыменовыния 
		reference operator*() const	{ return m_ptr->value; }

		// Перегрузка оператора доступа к члену ->
		pointer operator->()		{ return m_ptr; }

		// Префиксный инкремент
		virtual Iterator& operator++()		{ m_ptr = m_ptr->next; return *this; }
		
		// Постфиксный инкремент
		virtual Iterator operator++(int)	{ Iterator temp = *this; m_ptr = m_ptr->next; return temp; }

		// Префиксный декремент
		virtual Iterator& operator--()		{ m_ptr = m_ptr->prev; return *this; }
		
		// Постфиксный декремент
		virtual Iterator operator--(int)	{ Iterator temp = *this; m_ptr = m_ptr->prev; return temp; }

		// Перегрузка операторов сравнения
		friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
		friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }
		
		// Перегрузка оператора вывода значения в поток по итератору
		friend std::ostream& operator<<(std::ostream& stream, const Iterator& a) { stream << a.m_ptr->value; return stream; }
	};

	/*
	* Класс обратного итератора, унаследованный от прямого итератора
	* 
	* @param m_rptr - указатель на звено
	*/
	class RIterator : public Iterator
	{
	public:

		RIterator(pointer ptr) : Iterator(ptr) { }

		// Префиксный инкремент
		Iterator& operator++()	override { this->m_ptr = this->m_ptr->prev; return *this; }

		// Постфиксный инкремент
		Iterator operator++(int) override { RIterator temp = *this; this->m_ptr = this->m_ptr->prev; return temp; }

		// Префиксный декремент
		Iterator& operator--() override { this->m_ptr = this->m_ptr->next; return *this; }

		// Постфиксный декремент
		Iterator operator--(int) override { RIterator temp = *this; this->m_ptr = this->m_ptr->next; return temp; }
	};

	// Прямой итератор-указатель на начало списка
	Iterator begin()	{ return Iterator(first); }
	
	// Прямой итератор-указатель на конец (следующий элемент после последнего) списка
	Iterator end()		{ return Iterator(last->next); }

	// Обратный итератор-указатель, начало будет с конца
	RIterator rbegin()	{ return RIterator(last); }

	// Обратный итератор-указатель, конец будет перед началом списка (элемент до первого в списке)
	RIterator rend()	{ return RIterator(first->prev); }
	
	// Пустой конструктор
	DoubleLinkedList() {}

	/*
	* 
	* Основной конструктор
	* 
	* @param size - размер списка
	* @param nuller - чем его сразу заполнить
	*/
	DoubleLinkedList(const int size, T nuller = 0)
		: length(size)
	{
		for (int i = 0; i < size; i++)
			push_back(nuller);
	}

	// Деструктор списка
	~DoubleLinkedList()
	{
		while (first)
		{
			last = first->next;
			delete first;
			first = last;
		}
	}

	/*
	* Получаем первый элемент в списке
	* 
	* @return значение первого звена в списке
	*/
	T& front()		{ return first->value; }
	
	/*
	* Получаем последний элемент в списке
	*
	* @return значение последнего звена в списке
	*/
	T& back()		{ return last->value; }

	/*
	* Пуст ли список
	*
	* @return true - если ничего нет, иначе false
	*/
	bool empty()	{ return length == 0; }

	/*
	* Получаем размер списка
	*
	* @return length - размер списка
	*/
	int size()		{ return length; }
	
	/*
	* Удаляем последний элемент в цепи
	*/
	void pop_back()
	{
		last->prev->next = nullptr;

		Node* temp = last->prev;

		delete last;

		last = temp;

		length--;
	}

	/*
	* Удаляем первый элемент в цепи
	*/
	void pop_front()
	{
		first->next->prev = nullptr;

		Node* temp = first->next;

		delete first;

		first = temp;

		length--;
	}

	/*
	* Добавляем элемент в конец списка
	* 
	* @param value - значение, которое нужно добавить
	*/
	void push_back(T value)
	{
		Node* temp = new Node;
		temp->next = nullptr;
		temp->value = value;

		// Если список не пуст
		if (first != nullptr)
		{
			temp->prev = last;
			last->next = temp;
			last = temp;
		}
		else
		{
			temp->prev = nullptr;
			first = last = temp;
		}

		length++;
	}

	/*
	* Добавляем элемент в начало списка
	*
	* @param value - значение, которое нужно добавить
	*/
	void push_front(T value)
	{
		Node* temp = new Node;
		temp->prev = nullptr;
		temp->value = value;

		// Если список не пуст
		if (first != nullptr)
		{
			temp->next = first;
			first->prev= temp;
			first = temp;
		}
		else
		{
			temp->prev = nullptr;
			first = last = temp;
		}

		length++;
	}
};
