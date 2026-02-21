#include "Dummy.h"

#include "Common.h"

Dummy::Dummy(_In_ FourierConfigs& configs) : FourierInterface(configs) {};

Dummy::~Dummy() {};

void Dummy::FFT(_In_ std::vector<Real>& wave, _Out_ std::vector<Complex>& spectrum) {
  ASSERT(CHECK_SPECTRUM_SIZE(GetConfigs(), spectrum.size()));
  for (auto& i : spectrum) {
    i.real(0);
    i.imag(0);
  }
}
void Dummy::iFFT(_In_ std::vector<Complex>& spectrum, _Out_ std::vector<Real>& wave) {
  ASSERT(CHECK_SPECTRUM_SIZE(GetConfigs(), spectrum.size()));
  memset(wave.data(), 0, wave.size());
}