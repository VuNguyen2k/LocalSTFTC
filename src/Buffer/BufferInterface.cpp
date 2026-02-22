#include "BufferInterface.h"

#include <fmt/core.h>

#include <memory>

#include "Common.h"
#include "Simple.h"

std::unique_ptr<BufferInterface> BufferInterface::Create(_In_ BufferType wtype,
                                                         _In_ BufferConfigs& configs) {
  switch (wtype) {
    case BufferType::SIMPLE: {
      return std::make_unique<SimpleBuffer>(configs);
    }
    default:
      throw std::runtime_error(
          fmt::format("Window type {} is not a valid type", static_cast<int>(wtype)));
  }
}

void BufferInterface::PutRange(_In_ std::vector<Real>& v) {
  for (auto& i : v) {
    Put(i);
  }
}

std::vector<Real> BufferInterface::PopRange(_In_ size_t n) {
  std::vector<Real> v(n);
  for (size_t i = 0; i < v.size() && i < n; i++) {
    auto x = Get(0);
    v[i] = x;
    Pop();
  }
  return v;
}
