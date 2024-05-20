#ifndef TAPE_H
#define TAPE_H

#include <fstream>
class Tape
{
public:
	Tape() = delete;
	Tape(std::fstream &);
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
	int index;
	std::fstream &stream;
	bool ended;
};

#endif // !TAPE_H
