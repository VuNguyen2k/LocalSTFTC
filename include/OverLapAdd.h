#pragma once

#include "BufferInterface.h"
#include "Common.h"

class OverLapAdd {
 public:
  explicit OverLapAdd(_In_ STFTConfigs& configs);
  ~OverLapAdd();

  const STFTConfigs& GetConfigs() { return configs_; }

  void Step(_In_ std::vector<Real>& vinput, _Out_ std::vector<Real>& voutput);
  void ResetInternalState();

 private:
  struct STFTConfigs configs_;
  std::unique_ptr<BufferInterface> pbuffer_;
};
