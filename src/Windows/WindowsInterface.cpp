#include "WindowsInterface.h"

#define __USE_MATH_DEFINES
#include <fmt/core.h>
#include <math.h>

#include <functional>

static float HannFunc(int win_sample, int win_length) {
  return 1.f / 2.f *
         (1.f - cosf(2 * M_PI * static_cast<float>(win_sample) /
                     (static_cast<float>(win_length))));
}

static float SqrtHannFunc(int win_sample, int win_length) {
  return sqrt(HannFunc(win_sample, win_length));
}

std::vector<Real> CreateWindow(_In_ std::function<Real(int, int)> func,
                               _In_ int wsize) {
  std::vector<Real> window(wsize, 0);
  for (int i = 0; i < window.size(); i++) {
    window[i] = func(i, window.size());
  }
  return window;
}

std::vector<Real> WindowsInterface::Create(_In_ WindowType wtype, _In_ int wsize) {
  switch (wtype) {
    case WindowType::HANN: {
      return CreateWindow(HannFunc, wsize);
    }
    case WindowType::SQRT_HANN: {
      return CreateWindow(SqrtHannFunc, wsize);
    }
    default:
      throw std::runtime_error(
          fmt::format("Window type {} is not a valid type", static_cast<int>(wtype)));
  }
}