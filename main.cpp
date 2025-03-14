#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

const int numberTop = 10;
const int maxWeight = 10;

long double factorial(long double num)
{
  size_t f = 1;
  for (size_t i = 1; i <= num; i++)
  {
    f = f * i;
  }

  return f;
}

void timerProg(double dur, long double factor)
{
  std::cout << dur * (factorial(factor) / factorial(numberTop)) << " секунд" << std::endl;
  std::cout << dur * (factorial(factor) / factorial(numberTop)) / 60 << " минут" << std::endl;
  std::cout << dur * (factorial(factor) / factorial(numberTop)) / 60 / 60 << " часов" << std::endl;
  std::cout << dur * (factorial(factor) / factorial(numberTop)) / 60 / 60 / 24 << " дней" << std::endl;
  std::cout << dur * (factorial(factor) / factorial(numberTop)) / 60 / 60 / 24 / 365 << " лет" << std::endl;
}

int main()
{

  srand(time(0));

  auto start = std::chrono::high_resolution_clock::now();

  size_t sumMatrix = 0;

  size_t matrix[numberTop][numberTop];

  for (size_t j = 0; j < numberTop; j++)
  {
    for (size_t i = 0; i < numberTop; i++)
    {
      if (i == j)
      {
        matrix[i][j] = 0;
      }
      else
      {
        matrix[i][j] = rand() % (0 - maxWeight);
        sumMatrix += matrix[i][j];
      }
    }
  }

  std::string space = " ";

  for (size_t j = 0; j < numberTop; j++)
  {
    for (size_t i = 0; i < numberTop; i++)
    {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::vector<size_t> permutations = {};

  std::vector<size_t> copies = {};

  for (size_t i = 0; i < numberTop; i++)
  {
    permutations.push_back(i + 1);
  }

  for (size_t j = 0; j < numberTop; j++)
  {
    for (size_t i = 0; i < numberTop; i++)
    {
      if (matrix[i][j] == 0)
      {
        matrix[i][j] == sumMatrix;
      }
    }
  }

  size_t amount = __INT_MAX__;

  do
  {
    size_t am = 0;

    for (size_t i = 0; i < numberTop - 1; i++)
    {
      am += matrix[permutations[i] - 1][permutations[i + 1] - 1];
    }

    am += matrix[permutations[numberTop - 1] - 1][permutations[0] - 1];

    if (am < amount)
    {
      copies.clear();
      for (size_t i = 0; i < numberTop; i++)
      {
        copies.push_back(permutations[i]);
      }
    }

    amount = std::min(amount, am);
  } while (std::next_permutation(permutations.begin(), permutations.end()));

  std::cout << std::endl;

  std::cout << "Последовательность вершин для гамильтонова цикла: ";

  for (size_t i = 0; i < numberTop; i++)
  {
    std::cout << copies[i] << " ";
  }

  std::cout << std::endl;

  std::cout << "Наименьший вес: " << amount << std::endl;

  auto end = std::chrono::high_resolution_clock::now();

  auto dur = end - start;

  std::cout << "Время: " << std::chrono::duration<double>(dur).count() << " секунд" << std::endl;

  timerProg(std::chrono::duration<double>(dur).count(), 50);

  return 0;
}