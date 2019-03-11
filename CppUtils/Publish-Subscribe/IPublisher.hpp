#pragma once

#include "ISubscriber.hpp"

/// <summary>
/// Издатель
/// </summary>
template<typename T>
	class IPublisher 
	{
	public:
		/// <summary>
		/// Оформление подписки
		/// </summary>
		virtual void Subscribe(ISubscriber<T>* subscriber) = 0;

		/// <summary>
		/// Отписка
		/// </summary>
		virtual void UnSubscribe(ISubscriber<T>* subscriber) = 0;

	protected:
		/// <summary>
		/// Оповещение всех подписчиков
		/// </summary>
		virtual void Notify(const T& value) const = 0;
	};