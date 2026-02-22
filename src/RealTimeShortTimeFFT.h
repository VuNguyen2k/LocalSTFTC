#pragma once

#include <memory>
#include <vector>

#include "Common.h"
#include "ShortTimeFFTInterface.h"

class RealTimeShortTimeFFT : public ShortTimeFFTInterface {
 public:
  explicit RealTimeShortTimeFFT(_In_ STFTConfigs& configs);
  ~RealTimeShortTimeFFT();

  void STFT(_In_ std::vector<Real>& wave,
            _Out_ std::vector<std::vector<Complex>>& spectrum) override;
  void iSTFT(_In_ std::vector<std::vector<Complex>>& spectrum,
             _Out_ std::vector<Real>& wave) override;

 private:
  std::vector<Real> cache_windowed_inputs_;
};
