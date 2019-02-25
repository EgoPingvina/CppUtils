#pragma once

/// <summary>
/// Реализация Одиночки для вставки в любой другой класс
/// </summary>
/// <typeparam name="T">Класс, который будет обращён в Одиночку</typeparam>
/// <param name="Action">Действия, которые необходимо выполнить в конструкторе по умолчанию</typeparam>
#define Singleton(T, Action)				\
	protected:								\
		T() { (Action)(); }					\
		T(T const&) = delete;				\
		T& operator=(T const&) = delete;	\
		~T() = default;						\
	public:									\
		static T* Instance()				\
		{									\
			static T instance;				\
			return &instance;				\
		}									\
	private:								\
