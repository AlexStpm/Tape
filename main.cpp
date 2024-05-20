#include <iostream>
#include "Tape.h"
#include "NaturalMergeTapeSort.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: ./main [file_name]\n";
		return 1;
	}

	std::string fileName = argv[1];

	std::fstream input(fileName);
	if (!input.is_open())
	{
		std::cerr << "Error: File " << fileName << " not found\n";
		return 1;
	}

	Tape tape(input);

	try
	{
		NaturalMergeTapeSort::sort(tape);
		std::cout<<"Result is saved in output.txt" << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
