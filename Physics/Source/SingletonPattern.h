#pragma once
#include <iostream>

template <typename T>

class SingletonPattern
{
private:
	static T* instance;

public:
	static T* GetInstance(void)
	{
		if (instance == nullptr)
		{
			instance = new T();
		}
		return instance;
	}

	static void DestroyInstance(void)
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
};

template <typename T>
T* SingletonPattern<T>::instance = nullptr;