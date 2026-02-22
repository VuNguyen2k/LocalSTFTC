#pragma once

#include <memory>
#include <vector>

#include "Common.h"
#include "FourierInterface.h"
#include "OverLapAdd.h"
#include "WindowsInterface.h"

class ShortTimeFFTInterface {
 public:
  static std::unique_ptr<ShortTimeFFTInterface> Create(_In_ STFTType stft_type,
                                                       _In_ STFTConfigs& configs);

  explicit ShortTimeFFTInterface(_In_ STFTConfigs& configs);
  virtual ~ShortTimeFFTInterface();

  virtual void STFT(_In_ std::vector<Real>& wave,
                    _Out_ std::vector<std::vector<Complex>>& spectrum) = 0;
  virtual void iSTFT(_In_ std::vector<std::vector<Complex>>& spectrum,
                     _Out_ std::vector<Real>& wave) = 0;

 protected:
  struct STFTConfigs configs_;
  const std::vector<Real> window_;
  const Real win_norm_;
  OverLapAdd ola_;
  std::unique_ptr<FourierInterface> pfft_;
};
