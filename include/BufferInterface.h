#pragma once

#include <vector>

#include "Common.h"

class BufferInterface {
 public:
  static std::unique_ptr<BufferInterface> Create(_In_ BufferType wtype,
                                                 _In_ BufferConfigs& configs);

  explicit BufferInterface(_In_ BufferConfigs& configs) : configs_(configs) {}
  virtual ~BufferInterface() {}

  const BufferConfigs& GetConfigs() { return configs_; }

  virtual void Put(_In_ Real v) = 0;
  virtual Real& Get(_In_ size_t idx) = 0;
  virtual Real Pop() = 0;
  virtual size_t Size() = 0;

  virtual void PutRange(_In_ std::vector<Real>& v);
  virtual std::vector<Real> PopRange(_In_ size_t n);

  BufferInterface(const BufferInterface&) = delete;
  BufferInterface& operator==(const BufferInterface&) = delete;

  BufferInterface(BufferInterface&&) = delete;
  BufferInterface& operator==(BufferInterface&&) = delete;

 private:
  struct BufferConfigs configs_;
};
