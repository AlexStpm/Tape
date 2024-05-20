#include <fstream>
#include <iomanip>
#include <random>

int main(int argc, char* argv[])
{
  if (argc < 2)
    return 1;

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<int> dist(INT32_MIN, INT32_MAX);

  int numOfElements = std::stoi(argv[1]);
  std::ofstream tapeStream("tape" + std::string(argv[1]) + ".txt", std::ios::trunc);

  for (int i = 0; i < numOfElements; i++)
  {
    tapeStream << std::left << std::setw(12) << std::setfill(' ')<< dist(rng);
  }

  tapeStream.close();
}