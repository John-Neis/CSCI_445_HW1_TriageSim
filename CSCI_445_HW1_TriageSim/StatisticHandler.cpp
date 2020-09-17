#include "StatisticHandler.h"

using namespace Statistics;

StatisticHandler::StatisticHandler()
{
	time_next_event[0] = 0;
	time_next_event[1] = 1.0e+30;

	num_patients_delayed = 0;
	num_arrived = 0;
	num_departed = 0;

	area_num_in_q = 0;
	sim_time = 0;
	time_last_event = 0;
	total_of_delays = 0;
	accumulated_interarrival = 0;
	accumulated_service = 0;
}

void StatisticHandler::UpdateStats()
{
	double time_since_last = sim_time - time_last_event;
	time_last_event = sim_time;

	area_num_in_q += queue.size() * time_since_last;
}