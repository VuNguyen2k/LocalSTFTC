#pragma once

#include <vector>

#include "Common.h"
#include "FourierInterface.h"

class Dummy : public FourierInterface {
 public:
  explicit Dummy(_In_ FourierConfigs& configs);
  ~Dummy();

  void FFT(_In_ std::vector<Real>& wave, _Out_ std::vector<Complex>& spectrum) override;
  void iFFT(_In_ std::vector<Complex>& spectrum,
            _Out_ std::vector<Real>& wave) override;

 private:
};
