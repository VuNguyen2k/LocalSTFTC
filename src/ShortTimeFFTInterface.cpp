#include "ShortTimeFFTInterface.h"

#include <fmt/core.h>

#include "RealTimeShortTimeFFT.h"
#include "Utilities.h"

std::unique_ptr<ShortTimeFFTInterface> ShortTimeFFTInterface::Create(
    _In_ STFTType stft_type, _In_ STFTConfigs& configs) {
  switch (stft_type) {
    case STFTType::REALTIME: {
      return std::make_unique<RealTimeShortTimeFFT>(configs);
    }
    default:
      throw std::runtime_error(
          fmt::format("STFT type {} is not a valid type", static_cast<int>(stft_type)));
  }
}

ShortTimeFFTInterface::ShortTimeFFTInterface(_In_ STFTConfigs& configs)
    : configs_(configs),
      window_(WindowsInterface::Create(configs.win_type, configs.win_size)),
      pfft_(FourierInterface::Create(configs.fft_type, configs.fft_configs)),
      ola_(configs),
      win_norm_(CalculateNorm(window_) * static_cast<Real>(configs.fft_configs.nfft) /
                static_cast<Real>(configs.hop_size)) {}

ShortTimeFFTInterface::~ShortTimeFFTInterface() {}
