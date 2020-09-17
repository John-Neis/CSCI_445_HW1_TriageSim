/* ***************************************************** */
/* Author: John Neis | ID: 8003486                       */
/*                                                       */
/* Compiled using: Visual Studio (Windows) | g++ (Linux) */
/*                                                       */
/* Goal: Create a hospital triage single server simulat- */
/* or. Program output will be stats of the simulation    */
/* run, command line args will be mean values for inter- */
/* arrival and service times. Execution will not proceed */
/* if these values are not given.                        */
/* ***************************************************** */

// let u = U(0, 1)
// x = -B * ln(u)
// where B is a mean value
// This is an idea for new interarrival times

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <ctime>
#include "Patient.h"
#include "Triage.h"
#include "StatisticHandler.h"
#include "EventHandler.h"

#ifdef _WIN32
#define PAUSE
#include <Windows.h>
void pause()
{
	system("pause");
}
#endif

#define SIM_END 10080.0

using std::cout;
using std::endl;
using std::cerr;

int main(int argc, char** argv)
{
	
	if (argc != 3)
	{
		cerr << "Error: Incorrect arguments given." << endl;
		cerr << "Usage: Triage_Sim <mean> <mean>"   << endl;
#ifdef PAUSE
		pause();
#endif
		return EXIT_FAILURE;
	}
	
	auto now = std::chrono::system_clock::now();
	time_t seed = std::chrono::system_clock::to_time_t(now);

	double dInterArrivalTimeMean = std::stod(argv[1]);
	double dServiceTimeMean = std::stod(argv[2]);

	std::default_random_engine gen((unsigned int)seed);
	std::exponential_distribution<double> dist_service(1.0 / dServiceTimeMean);
	std::exponential_distribution<double> dist_patient(1.0 / dInterArrivalTimeMean);

	std::vector<SickPerson::Patient> queue;

	////////////////////////////////////////////////////////////////////////////
	//                             Now the real fun begins                    //
	////////////////////////////////////////////////////////////////////////////
	Statistics::StatisticHandler s;
	Events::EventHandler e;

	s.time_next_event[0] = dist_patient(gen);

	while (s.sim_time < SIM_END)
	{
		e.GetNextEvent(s);

		s.UpdateStats();

		if (e.next_event == ARR)
		{
			e.Arrival(s, dist_patient(gen), dist_service(gen));
		}
		else
		{
			e.Departure(s, dist_service(gen));
		}

		//cout << "Simulation time: " << s.sim_time << endl;
	}
	
	cout << "<----------------------Statistics for this run:---------------------->" << endl;
	cout << "\t    Average inter-arrival time: " << s.accumulated_interarrival / s.num_arrived << endl;
	cout << "\t          Average service time: " << s.accumulated_interarrival / s.num_departed << endl;
	cout << "\t   Average wait time (minutes): " << (int)(s.total_of_delays / s.num_patients_delayed) << endl;
	cout << "\t     Average patients in queue: " << s.area_num_in_q / s.sim_time << endl;
	cout << "\tNumber patients through triage: " << s.num_departed << endl;
	cout << "\t Number patients still waiting: " << s.queue.size() << endl;
	cout << "<-------------------------------------------------------------------->" << endl;

#ifdef PAUSE
	pause();
#endif
	return 0;
}