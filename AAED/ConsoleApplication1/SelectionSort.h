#pragma once

#include <vector>

#include "SortingAlgorithm.h"

class SelectionSort : public SortingAlgorithm {
 public:
  auto operator()(std::vector<int> vector) const -> std::vector<int> override;
};

auto SortingAlgorithm::operator()(std::vector<int> vector) const
    -> std::vector<int> {
  // do eet
  return std::vector<int>{};
}
