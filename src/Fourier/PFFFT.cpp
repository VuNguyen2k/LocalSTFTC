#include "PFFFT.h"

#include "Common.h"

PFFFT::PFFFT(_In_ FourierConfigs& configs)
    : FourierInterface(configs), pffft_core_(pffft::Fft<Real>(GetConfigs().nfft)) {};

PFFFT::~PFFFT() {};

void PFFFT::FFT(_In_ std::vector<Real>& wave, _Out_ std::vector<Complex>& spectrum) {
  ASSERT(CHECK_SPECTRUM_SIZE(GetConfigs(), spectrum.size()));
  pffft_core_.forward(wave.data(), spectrum.data());
}
void PFFFT::iFFT(_In_ std::vector<Complex>& spectrum, _Out_ std::vector<Real>& wave) {
  ASSERT(CHECK_SPECTRUM_SIZE(GetConfigs(), spectrum.size()));
  pffft_core_.inverse(spectrum.data(), wave.data());
}