#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "SortingAlgorithmFactory.h"

class SortingAlgorithmView {
 public:
  auto getInput() const -> const std::string;

  SortingAlgorithmView(const SortingAlgorithmFactory sortingAlgorithmFactory);

 private:
  static const std::string prompt;

  auto getOption() const -> const int;

  const std::vector<std::string> algorithmNames;
};

const std::string SortingAlgorithmView::prompt{
    "Please select which algorithm to use:"};

SortingAlgorithmView::SortingAlgorithmView(
    const SortingAlgorithmFactory sortingAlgorithmFactory)
    : algorithmNames{sortingAlgorithmFactory.getAlgorithmNames()} {}

auto SortingAlgorithmView::getInput() const -> const std::string {
  bool cont{true};
  int option{-1};

  do {
    std::cout << prompt << std::endl;

    for (size_t i{0}; i < algorithmNames.size(); ++i) {
      std::cout << i << ". " << algorithmNames.at(i) << std::endl;
    }

    try {
      option = getOption();
      cont = true;
    } catch (std::out_of_range err) {
      std::cout << err.what();
      cont = false;
    }
  } while (cont);

  return algorithmNames.at(option);
}

auto SortingAlgorithmView::getOption() const -> const int {
  int option{-1};
  std::cin >> option;

  if (!std::cin) {
    throw std::out_of_range{"Input is not a number."};
  }

  if (!(option > -1 && option < (int) algorithmNames.size())) {
    throw std::out_of_range{"Input is not in selection range."};
  }

  return option;
}
