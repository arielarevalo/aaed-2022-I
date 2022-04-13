#pragma once
#include <string>
#include <vector>

class SortingAlgorithm {
 protected:
  virtual auto operator()(std::vector<int> vector) const
      -> std::vector<int> = 0;
};
