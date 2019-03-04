#pragma once

#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <mutex>

#include "Singleton.hpp"
#include "CallbackT.h"
#include "IObserver.h"

using namespace std;

/// <summary>
/// Механизм оповещения о появлении новых данных
/// </summary>
class DataStorage
{
	typedef unordered_set<IObserver<void*>*> observersCollection;
	
	typedef pair<type_index, observersCollection> observerPair;
	
	Singleton(DataStorage, [](){})
		
private:
	
	/// <summary>
    /// Подписчики (тип получаемых данных - действие при получении новых данных)
    /// </summary>
	unordered_map<type_index, observersCollection> observers;
	
	/// <summary>
    /// Элемент потокобезопасности работы с коллекцией подписчиков
    /// </summary>
	mutex mutex;
		
public:

	/// <summary>
    /// Добавление подписчика
    /// </summary>
    /// <typeparam name="T">Тип данных, на который формируется подписка</typeparam>
    /// <param name="observer">Подписчик</param>
	template<typename T>
		void Add(IObserver<T*> * observer);

	/// <summary>
	/// Удаление подписчика
	/// </summary>
	/// <typeparam name="T">Тип данных, на который была оформлена подписка</typeparam>
	/// <param name="observer">Подписчик</param>
	template<typename T>
		void Remove(IObserver<T*> * observer);

	/// <summary>
	/// Оповещение подписчиков
	/// </summary>
	/// <typeparam name="T">Тип, который изменился</typeparam>
	/// <param name="data">Новые данные типа T</param>
	template<typename T>
		void Notify(T* data);

	template<typename T>
		class Observer;
	
	/// <summary>
    /// Реализация внешнего подписчика
    /// </summary>
	template<typename T>
		class Observer<T*> : public IObserver<T*>
		{
		private:
			/// <summary>
			/// Действие, выполняемое при получении новых данных типа <see cref="T"/>
			/// </summary>
			Action<T*> update;
	
		public:
			/// <summary>
			/// Конструктор с передачей ссылки на реакцию по получению новых данных
			/// </summary>
			Observer(Action<T*> update);
	
			/// <summary>
			/// Реакция на получение данных
			/// (вызывает переданный в конструктор Action<T> с передачей в него data)
			/// </summary>
			void OnNext(T* data) override;
		};
};

#pragma region Observer

template<typename T>
	DataStorage::Observer<T*>::Observer(Action<T*> update)
	{
		this->update = update;
	}

template<typename T>
	void DataStorage::Observer<T*>::OnNext(T* data)
	{
		this->update.Call(data);
	}

#pragma endregion	

template<typename T>
	void DataStorage::Add(IObserver<T*> * observer)
	{
		this->mutex.lock();
				
		// Если на указанный тип данных T ещё не было подписок - инициализируем список подписчиков на него
		if (this->observers.find(type_index(typeid(T))) == this->observers.end())
			this->observers.insert(
				observerPair(
					type_index(typeid(T)),
					observersCollection()));

		// Т.к. элемент является множеством, можно не боятся за появление повторяющихся подписок
		(*this->observers.find(type_index(typeid(T)))).second.insert(reinterpret_cast<IObserver<void*> *>(observer));
		
		this->mutex.unlock();
	}

template<typename T>
	void DataStorage::Remove(IObserver<T*> * observer)
	{
		this->mutex.lock();
				
		auto observersToT = this->observers.find(type_index(typeid(T)));
	
		// Если на указанный тип данных T нет подписок, значит нечего удалять => выходим
		if (observersToT == this->observers.end())
			return;
	
		auto temp = (*observersToT).second;
	
		// Пытаемся получить в списке подписчиков того, кого нужно удалить
		auto removableObserver = temp.find(observer);
	
		// Если переданный подписчик есть в коллекции - удаляем
		if (removableObserver != temp.end())
			temp.erase(observer);
		
		this->mutex.unlock();
	}

template<typename T>
	void DataStorage::Notify(T* data)
	{	
		this->mutex.lock();
				
		auto observersToT = this->observers.find(type_index(typeid(T)));
		
		if (observersToT == this->observers.end())
			return;
		
		for (const auto observer : (*observersToT).second)
			observer->OnNext(data);
		
		this->mutex.unlock();
	}