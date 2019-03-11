#pragma once

#include <unordered_set>

#include "ISubscriber.hpp"
#include "IPublisher.hpp"

/// <summary>
/// Издатель (основанный на динамической коллекции)
/// </summary>
template<typename T, template<typename...> typename Collection = std::unordered_set>
	class PublisherDynamic : public IPublisher<T>
	{
	public:
		/// <summary>
		/// Оформление подписки
		/// </summary>
		void Subscribe(ISubscriber<T>* subscriber) override
		{
			this->subscribers.insert(subscriber);
		}
	
		/// <summary>
		/// Отписка
		/// </summary>
		void UnSubscribe(ISubscriber<T>* subscriber) override
		{
			this->subscribers.erase(subscriber);
		}
	
	protected:
		/// <summary>
		/// Оповещение всех подписчиков
		/// </summary>
		void Notify(const T& value) const override
		{
			for (auto subscriber : this->subscribers)
				subscriber->Update(value);
		}
	
	private:
		/// <summary>
		/// Коллекция подписчиков
		/// </summary>
		Collection<ISubscriber<T>*> subscribers;
	};