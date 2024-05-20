#include <gtest/gtest.h>
#include "NaturalMergeTapeSort.h"

bool isSorted(Tape &tape)
{
    if (tape.isAtTheEnd())
    {
        return true;
    }
    int prevValue = tape.readValue();
    while (!tape.isAtTheEnd())
    {
        int curValue = tape.readValue();
        if (curValue < prevValue)
        {
            return false;
        }
        prevValue = curValue;
        tape.nextPosition();
    }
    return true;
}

TEST(NaturalMergeTapeSortTest, InvalidInputData)
{
    std::fstream input("tapeInvalid.txt");
    Tape inputTape(input);

    try
    {
        NaturalMergeTapeSort::sort(inputTape);
    }
    catch (std::exception const &e)
    {
        EXPECT_STREQ("ERROR: Invalid input data", e.what());
    }
}

TEST(NaturalMergeTapeSortTest, 0ElementsSorting)
{
    std::fstream input("tape0.txt");
    Tape inputTape(input);

    NaturalMergeTapeSort::sort(inputTape);

    std::fstream outputFile("output.txt");
    Tape outputTape(outputFile);
    ASSERT_TRUE(isSorted(outputTape));
}

TEST(NaturalMergeTapeSortTest, 1ElementSorting)
{
    std::fstream input("tape1.txt");
    Tape inputTape(input);

    NaturalMergeTapeSort::sort(inputTape);

    std::fstream outputFile("output.txt");
    Tape outputTape(outputFile);
    ASSERT_TRUE(isSorted(outputTape));
}

TEST(NaturalMergeTapeSortTest, 5ElementSorting)
{
    std::fstream input("tape5.txt");
    Tape inputTape(input);

    NaturalMergeTapeSort::sort(inputTape);

    std::fstream outputFile("output.txt");
    Tape outputTape(outputFile);
    ASSERT_TRUE(isSorted(outputTape));
}

TEST(NaturalMergeTapeSortTest, 1000ElementSorting)
{
    std::fstream input("tape1000.txt");
    Tape inputTape(input);

    NaturalMergeTapeSort::sort(inputTape);

    std::fstream outputFile("output.txt");
    Tape outputTape(outputFile);
    ASSERT_TRUE(isSorted(outputTape));
}

// TEST(NaturalMergeTapeSortTest, 1000000ElementSorting)
// {
//     std::fstream input("tape1000000.txt");
//     Tape inputTape(input);

//     NaturalMergeTapeSort::sort(inputTape);

//     std::fstream outputFile("output.txt");
//     Tape outputTape(outputFile);
//     ASSERT_TRUE(isSorted(outputTape));
// }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}