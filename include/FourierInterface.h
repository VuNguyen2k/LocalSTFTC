#pragma once

#include <vector>

#include "Common.h"

class FourierInterface {
 public:
  static std::unique_ptr<FourierInterface> Create(_In_ FourierType ftype,
                                                  _In_ FourierConfigs& configs);

  explicit FourierInterface(_In_ FourierConfigs& configs) : configs_(configs) {};
  virtual ~FourierInterface() {};

  const FourierConfigs& GetConfigs() { return configs_; }

  virtual void FFT(_In_ std::vector<Real>& wave,
                   _Out_ std::vector<Complex>& spectrum) = 0;
  virtual void iFFT(_In_ std::vector<Complex>& spectrum,
                    _Out_ std::vector<Real>& wave) = 0;

  FourierInterface(const FourierInterface&) = delete;
  FourierInterface& operator==(const FourierInterface&) = delete;

  FourierInterface(FourierInterface&&) = delete;
  FourierInterface& operator==(FourierInterface&&) = delete;

 private:
  struct FourierConfigs configs_;
};
