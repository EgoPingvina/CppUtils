#pragma once

/// <summary>
/// ���������� �������� ��� ������� � ����� ������ �����
/// </summary>
/// <typeparam name="T">�����, ������� ����� ������� � ��������</typeparam>
/// <param name="Action">��������, ������� ���������� ��������� � ������������ �� ���������</typeparam>
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
