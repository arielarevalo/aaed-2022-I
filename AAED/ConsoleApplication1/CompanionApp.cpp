#include <stdexcept>

#include "SortingAlgorithmFactory.h"
#include "SortingAlgorithmView.h"

static const SortingAlgorithmFactory sortingAlgorithmFactory;
static const SortingAlgorithmView sortingAlgorithmView{sortingAlgorithmFactory};

auto main() -> int {
  sortingAlgorithmFactory.of(sortingAlgorithmView.getInput());
}
