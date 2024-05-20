#include "NaturalMergeTapeSort.h"
#include <iostream>

void NaturalMergeTapeSort::sort(Tape &inputTape)
{
	bool sorted = true;
	std::fstream outputTapeFile("output.txt", std::ios::out | std::ios::in | std::ios::trunc);

	Tape outputTape(outputTapeFile);

	// Копируем ленту в выходную, проверяем отсортирована ли она
	if (!inputTape.isAtTheEnd())
	{
		int prevValue = inputTape.readValue();
		while (!inputTape.isAtTheEnd())
		{
			int curValue = inputTape.readValue();
			if (curValue < prevValue)
			{
				sorted = false;
			}
			outputTape.writeValue(inputTape.readValue());
			inputTape.nextPosition();
			outputTape.nextPosition();
			prevValue = curValue;
		}
	}

	if (sorted)
	{
		return;
	}

	inputTape.reset();
	outputTape.reset();

	if (outputTape.isAtTheEnd()) // Пустой файл - отсортированный файл
	{
		return;
	}

	bool tapeSwitch = true;
	while (!sorted)
	{
		outputTape.reset();
		std::fstream firstTapeFile("./tmp/firstTape.txt", std::ios::out | std::ios::in | std::ios::trunc);
		std::fstream secondTapeFile("./tmp/secondTape.txt", std::ios::out | std::ios::in | std::ios::trunc);

		Tape firstTape(firstTapeFile), secondTape(secondTapeFile);

		int lastValue = outputTape.readValue();

		while (!outputTape.isAtTheEnd())
		{
			int value = outputTape.readValue();
			if (lastValue > value)
			{
				tapeSwitch = !tapeSwitch;
			}
			if (tapeSwitch)
			{
				firstTape.writeValue(value);
				outputTape.nextPosition();
				firstTape.nextPosition();
			}
			else
			{
				secondTape.writeValue(value);
				outputTape.nextPosition();
				secondTape.nextPosition();
			}
			lastValue = value;
		}

		sorted = mergeSeries(firstTape, secondTape, outputTape);
	}
}

// Возвращает true если на временных лентах находится по одной серии (после слияния последовательность оказывается отсортированной)
bool NaturalMergeTapeSort::mergeSeries(Tape &first, Tape &second, Tape &output)
{
	first.reset();
	second.reset();
	output.reset();
	bool sorted = true;
	int firstTapePrevValue = first.readValue(), secondTapePrevValue = second.readValue();
	bool firstTapeSeriesEnded = false, secondTapeSeriesEnded = false;
	while (!(first.isAtTheEnd() && second.isAtTheEnd()))
	{
		if (first.isAtTheEnd())
		{
			int secondTapeValue = second.readValue();
			if (secondTapeValue < secondTapePrevValue)
			{
				sorted = false;
			}
			output.writeValue(secondTapeValue);
			second.nextPosition();
			output.nextPosition();
			secondTapePrevValue = secondTapeValue;
			continue;
		}
		else if (second.isAtTheEnd())
		{
			int firstTapeValue = first.readValue();
			if (firstTapeValue < firstTapePrevValue)
			{
				sorted = false;
			}
			output.writeValue(first.readValue());
			first.nextPosition();
			output.nextPosition();
			firstTapePrevValue = firstTapeValue;
			continue;
		}

		int firstTapeValue = first.readValue(), secondTapeValue = second.readValue();
		if (firstTapeValue < firstTapePrevValue)
		{
			firstTapeSeriesEnded = true;
			sorted = false;
		}
		if (secondTapeValue < secondTapePrevValue)
		{
			secondTapeSeriesEnded = true;
			sorted = false;
		}

		if (firstTapeSeriesEnded && secondTapeSeriesEnded)
		{
			firstTapeSeriesEnded = false;
			firstTapePrevValue = firstTapeValue;
			secondTapeSeriesEnded = false;
			secondTapePrevValue = secondTapeValue;
		}

		if (firstTapeSeriesEnded)
		{
			output.writeValue(secondTapeValue);
			secondTapePrevValue = secondTapeValue;
			second.nextPosition();
		}
		else if (secondTapeSeriesEnded)
		{
			output.writeValue(firstTapeValue);
			firstTapePrevValue = firstTapeValue;
			first.nextPosition();
		}
		else if (firstTapeValue < secondTapeValue)
		{
			output.writeValue(firstTapeValue);
			firstTapePrevValue = firstTapeValue;
			first.nextPosition();
		}
		else
		{
			output.writeValue(secondTapeValue);
			secondTapePrevValue = secondTapeValue;
			second.nextPosition();
		}
		output.nextPosition();
	}
	return sorted;
}