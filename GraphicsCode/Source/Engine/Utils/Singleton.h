#pragma once

namespace FanshaweGameEngine
{
	template<class T>
	class Singleton
	{
	public:

		static T& GetInstance()
		{
			if (instance == nullptr)
			{
				instance = new T();
			}

			return *instance;
		}

		static bool Release()
		{
			if (instance)
			{
				delete instance;
				instance = nullptr;
			}
		}

	protected:

		Singleton() {};
		~Singleton() {};

		static T* instance;
	};

	template <class T>
	T* Singleton<T>::instance = nullptr;
}