#pragma once

#include <vector>

#include "Common.h"

class WindowsInterface {
 public:
  static std::vector<Real> Create(_In_ WindowType wtype, _In_ int wsize);
};
