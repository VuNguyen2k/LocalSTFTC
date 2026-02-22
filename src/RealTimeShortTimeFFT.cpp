#include "RealTimeShortTimeFFT.h"

#include <fmt/core.h>

#include "Log.h"
#include "Utilities.h"

RealTimeShortTimeFFT::RealTimeShortTimeFFT(_In_ STFTConfigs& configs)
    : ShortTimeFFTInterface(configs) {}

RealTimeShortTimeFFT::~RealTimeShortTimeFFT() {}

void RealTimeShortTimeFFT::STFT(_In_ std::vector<Real>& wave,
                                _Out_ std::vector<std::vector<Complex>>& spectrum) {
  if (spectrum.size() > 0) {
    LOG_WARN("Spectrum contains some data, cleaning up");
    spectrum.clear();
  }

  if (wave.size() == 0) {
    LOG_ERROR("Empty wave data, exitting");
    return;
  }

  std::vector<Real> windowed_inputs;
  ApplyWindow(wave, window_, windowed_inputs);
  std::vector<Complex> frame_spectrum(GetSpectrumSize(configs_.fft_configs));
  pfft_->FFT(windowed_inputs, frame_spectrum);
  spectrum.push_back(frame_spectrum);
}

void RealTimeShortTimeFFT::iSTFT(_In_ std::vector<std::vector<Complex>>& spectrum,
                                 _Out_ std::vector<Real>& wave) {
  if (spectrum.size() == 0) {
    LOG_ERROR("Empty spectrum, exitting");
    return;
  }

  std::vector<Real> ifft_output(configs_.win_size);
  pfft_->iFFT(spectrum[0], ifft_output);

  std::vector<Real> windowed_modified_outputs;
  ApplyWindow(ifft_output, window_, windowed_modified_outputs);

  ola_.Step(windowed_modified_outputs, wave);
  Scale(wave, 1.f / win_norm_);
}
