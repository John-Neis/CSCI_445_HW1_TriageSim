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
#include "Patient.h"
#include "Triage.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cerr << "Error: Incorrect arguments given." << std::endl;
		std::cerr << "Usage: Triage_Sim <mean> <mean>" << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}
	
	Server::Triage server;
	std::vector<SickPerson::Patient> queue;

	return 0;
}