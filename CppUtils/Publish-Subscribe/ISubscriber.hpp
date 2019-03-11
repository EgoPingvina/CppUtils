#pragma once

/// <summary>
/// Подписчик
/// </summary>
template<typename T>
	struct ISubscriber
	{
		/// <summary>
		/// Получение новых данных (вызывается Publisher-ом)
		/// </summary>
		virtual void Update(const T& value) = 0;
	};