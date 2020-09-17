#pragma once
#include "Triage.h"
#include "Patient.h"
#include <vector>

namespace Statistics
{
	class StatisticHandler
	{
	public:
		StatisticHandler();
		void UpdateStats();

	public:
		int num_patients_delayed,
			num_arrived,
			num_departed;

		double area_num_in_q,
			accumulated_interarrival,
			accumulated_service,
			sim_time,
			time_last_event,
			time_next_event[2],
			total_of_delays;

		Server::Triage triage;
		std::vector<SickPerson::Patient> queue;
		std::vector<double> time_arrival;
	};
}