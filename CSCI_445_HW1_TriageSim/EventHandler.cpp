#include "EventHandler.h"
#include "StatisticHandler.h"
#include <iostream>

using namespace Events;

void EventHandler::GetNextEvent(StatisticHandler &s)
{
	double min_event_time = 1.0e+29;

	if (s.time_next_event[0] < min_event_time)
	{
		min_event_time = s.time_next_event[0];
		next_event = ARR;
	}
	if (s.time_next_event[1] < min_event_time)
	{
		min_event_time = s.time_next_event[1];
		next_event = DEP;
	}

	s.sim_time = min_event_time;
}

void EventHandler::Arrival(StatisticHandler &s, double arr_time, double ser_time)
{
	//std::cout << "Arrival" << std::endl;

	double delay;
	s.time_next_event[0] = s.sim_time + arr_time;
	s.num_arrived++;
	s.accumulated_interarrival += arr_time;

	if (s.triage.isBusy)
	{
		s.queue.push_back(SickPerson::Patient());
		s.queue.back().time_of_arrival = s.sim_time;
	}
	else
	{
		delay = 0;
		s.total_of_delays += delay;
		s.num_patients_delayed++;
		s.triage.isBusy = true;

		s.time_next_event[1] = s.sim_time + ser_time;
		s.accumulated_interarrival += ser_time;
	}
}

void EventHandler::Departure(StatisticHandler &s, double ser_time)
{
	//std::cout << "Departure" << std::endl;

	double delay;
	s.num_departed++;

	if (s.queue.size() == 0)
	{
		s.triage.isBusy = false;
		s.time_next_event[1] = 1.0e+30;
	}
	else
	{
		delay = s.sim_time - s.queue[0].time_of_arrival;
		s.queue.erase(s.queue.begin());

		s.total_of_delays += delay;
		s.num_patients_delayed++;
		s.time_next_event[1] = s.sim_time + ser_time;
		s.accumulated_service += ser_time;
	}
}