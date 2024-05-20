#ifndef TAPE_H
#define TAPE_H

#include <fstream>
class Tape
{
public:
	Tape() = delete;
	Tape(std::fstream &, const unsigned int latency = 0);
	Tape(const Tape &) = delete;
	Tape(Tape &&) noexcept = delete;
	Tape &operator=(Tape &&) noexcept = delete;
	int readValue();
	void writeValue(int);
	void nextPosition();
	void previousPosition();
	void reset();
	bool isAtTheEnd();
	~Tape();

private:
	std::fstream &stream;
	int index;
	bool ended;
	const unsigned int latency;
	void simulateLatency();
};

#endif // !TAPE_H
