#pragma once
#include <vector>
#include "Observer.h"
class Observable
{
	std::vector <Observer*> _observers;
public:
	virtual ~Observable() {}
	void addObserver(Observer *observer)
	{
		_observers.push_back(observer);
	}
	void notifyUpdate()
	{
		size_t size = _observers.size();
		for (size_t i = 0; i < size; i++)
		{
			_observers[i]->update();
		}
	}
};

