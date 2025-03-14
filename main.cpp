#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

const size_t MAX_WEIGHT = 100;

struct Item
{
  std::string name;
  size_t number;
  size_t weight;
  size_t value;
};

using Backpack = std::vector<Item>;

int main()
{
  Backpack backpack;

  std::string fileName;
  std::cin >> fileName;

  std::ifstream file(fileName);

  if (!file.is_open())
  {
    std::cout << "Неправильное имя файла" << std::endl;
    return 1;
  }

  std::string line;
  size_t numberItems = 0;

  while (std::getline(file, line) && !line.empty())
  {
    std::stringstream ss(line);
    Item item;

    ss >> item.name >> item.weight >> item.value;
    item.number = backpack.size() + 1;

    backpack.push_back(item);
    numberItems++;
  }

  std::vector<size_t> permutations = {};

  for (size_t i = 0; i < numberItems; i++)
  {
    permutations.push_back(i + 1);
  }

  size_t value = 0;
  Backpack copies;

  do
  {
    size_t amountWeight = 0;
    size_t amountValue = 0;
    size_t amountOfItems = 0;

    for (size_t i = 0; i < numberItems - 1 && amountWeight < (MAX_WEIGHT - backpack[permutations[i] - 1].weight); i++)
    {
      amountWeight += backpack[permutations[i] - 1].weight;
      amountValue += backpack[permutations[i] - 1].value;
      amountOfItems++;
    }

    if (amountValue > value)
    {
      copies.clear();
      for (size_t i = 0; i < amountOfItems; i++)
      {
        copies.push_back(backpack[permutations[i] - 1]);
      }
    }

    value = std::max(value, amountValue);
  } while (std::next_permutation(permutations.begin(), permutations.end()));

  std::cout << "Максимальная ценность: " << value << std::endl;

  std::cout << "Содержимое рюкзака: " << std::endl;

  for (size_t i = 0; i < copies.size(); i++)
  {
    std::cout << "|" << copies[i].name << "|" << std::endl;
  }

  return 0;
}