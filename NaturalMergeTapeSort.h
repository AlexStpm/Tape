#ifndef NATURAL_MERGE_TAPE_SORT_H
#define NATURAL_MERGE_TAPE_SORT_H

#include "Tape.h"
class NaturalMergeTapeSort
{
public:
	static void sort(Tape &);

private:
	static bool mergeSeries(Tape &, Tape &, Tape &);
};

#endif // !NATURALMERGETAPESORT_H
