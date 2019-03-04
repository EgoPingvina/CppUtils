#pragma once

template<typename T>
	struct IObserver;

/// <summary>
/// Интерфейс подписчка
/// </summary>
template<typename T>
	struct IObserver<T*>
	{
		/// <summary>
		/// Реакция на получение данных
		/// </summary>
		virtual void OnNext(T* data) = 0;
	};