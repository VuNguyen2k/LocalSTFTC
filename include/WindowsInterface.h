#pragma once

#include <vector>

#include "Common.h"

enum class WindowType { HANN = 0, SQRT_HANN };

class WindowsInterface {
 public:
  static std::vector<Real> Create(_In_ WindowType wtype, _In_ int wsize);
};
