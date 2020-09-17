#pragma once
#include "StatisticHandler.h"

#define ARR 1
#define DEP 0
#define EVENT int

namespace Events
{
	class EventHandler
	{
	public:
		EVENT next_event;
	public:
		void GetNextEvent(StatisticHandler& s);
		void Arrival(StatisticHandler& s, double arr_time, double ser_time);
		void Departure(StatisticHandler& s, double ser_time);
	};
}


