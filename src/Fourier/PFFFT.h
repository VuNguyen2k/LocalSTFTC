#pragma once

#include <pffft.hpp>
#include <vector>

#include "Common.h"
#include "FourierInterface.h"

class PFFFT : public FourierInterface {
 public:
  explicit PFFFT(_In_ FourierConfigs& configs);
  ~PFFFT();

  void FFT(_In_ std::vector<Real>& wave, _Out_ std::vector<Complex>& spectrum) override;
  void iFFT(_In_ std::vector<Complex>& spectrum,
            _Out_ std::vector<Real>& wave) override;

 private:
  pffft::Fft<Real> pffft_core_;
};
