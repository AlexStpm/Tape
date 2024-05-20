#include <iostream>
#include <chrono>
#include "Tape.h"
#include "NaturalMergeTapeSort.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: ./main [file_name]" << std::endl;
		return 1;
	}

	std::string fileName = argv[1];

	int latency = 0;
	std::fstream config("config.txt");
	if (!config.is_open())
	{
		std::cout << "Config file is not found. Default latency is set to 0" << std::endl;
	}

	config >> latency;

	if (config.fail() || latency < 0)
	{
		std::cout << "Invalid data in config file. Default latency is set to 0" << std::endl;
		config.close();
		config.open("config.txt", std::ios::out | std::ios::trunc);
        config << 0;
        config.flush();
	}
	else
	{

		std::cout << "Latency is set to " << latency << "ms" << std::endl;
	}

	config.close();

	std::fstream input(fileName);
	if (!input.is_open())
	{
		std::cerr << "Error: File " << fileName << " not found" << std::endl;
		return 1;
	}

	Tape tape(input, latency);

	try
	{
		auto start = std::chrono::high_resolution_clock::now();
		NaturalMergeTapeSort::sort(tape);
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "Result is saved in output.txt" << std::endl;
		std::cout << "Elapsed time " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
