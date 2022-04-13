#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "SelectionSort.h"
#include "SortingAlgorithm.h"

class SortingAlgorithmFactory {
 public:
  static auto of(const std::string key) noexcept(false)
      -> const SortingAlgorithm&;

  static auto getAlgorithmNames() -> const std::vector<std::string>;

 private:
  static const std::vector<std::string> algorithmNames;

  static const std::unordered_map<std::string, SortingAlgorithm>
      sortingAlgorithms;
};

const std::vector<std::string> SortingAlgorithmFactory::algorithmNames{
    "Selection Sort"};

const std::unordered_map<std::string, SortingAlgorithm>
    SortingAlgorithmFactory::sortingAlgorithms{
        {SortingAlgorithmFactory::algorithmNames.at(0), SelectionSort{}}};

auto SortingAlgorithmFactory::of(const std::string key)
    -> const SortingAlgorithm& {
  return sortingAlgorithms.at(key);
}

auto SortingAlgorithmFactory::getAlgorithmNames()
    -> const std::vector<std::string> {
  return algorithmNames;
}
