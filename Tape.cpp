#include <iostream>
#include <iomanip>
#include <exception>
#include <chrono>
#include <thread>
#include "Tape.h"

Tape::Tape(std::fstream &stream, const unsigned int latency /*= 0*/) : stream(stream), index(0), ended(false), latency(latency)
{
	stream.seekg(0, std::ios::end);
	if (stream.tellg() < 1)
	{
		ended = true;
	}
};

Tape::~Tape()
{
	stream.close();
};

int Tape::readValue()
{
	simulateLatency();
	stream.seekg(index, std::ios::beg);
	int value;
	stream >> value;
	if (stream.fail())
	{
		throw std::runtime_error("ERROR: Invalid input data");
	}
	stream.seekg(index, std::ios::beg);
	return value;
}

void Tape::writeValue(int newValue)
{
	simulateLatency();
	ended = false;
	stream.seekp(index, std::ios::beg);
	stream << std::left << std::setw(12) << std::setfill(' ') << newValue;
	stream.flush();
	stream.seekg(index, std::ios::beg);
}

void Tape::nextPosition()
{
	simulateLatency();
	if (ended)
	{
		throw std::out_of_range("ERROR: Position is out of range!");
	}
	index += 12;
	stream.seekg(index, std::ios::beg);
	int temp;
	stream >> temp;
	if (stream.eof())
	{
		stream.clear();
		ended = true;
		return;
	}
	if (stream.fail())
	{
		stream.seekg(index, std::ios::beg);
	}
}

void Tape::previousPosition()
{
	simulateLatency();
	if (index == 0)
	{
		throw std::out_of_range("ERROR: Position is out of range!1");
	}
	ended = false;
	index -= 12;
}

bool Tape::isAtTheEnd()
{
	return ended;
}

void Tape::reset()
{
	simulateLatency();
	stream.clear();
	index = 0;
	stream.seekg(0, std::ios::end);
	if (stream.tellg() < 1)
	{
		ended = true;
	}
	else
	{
		ended = false;
	}
}

void Tape::simulateLatency()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(latency));
}