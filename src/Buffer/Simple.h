#pragma once

#include <vector>

#include "BufferInterface.h"

class SimpleBuffer : public BufferInterface {
 public:
  explicit SimpleBuffer(_In_ BufferConfigs& configs);
  ~SimpleBuffer();

  void Put(_In_ Real v) override;
  Real& Get(_In_ size_t idx) override;
  Real Pop() override;
  size_t Size() override;

 private:
  std::vector<Real> queue_;
};
