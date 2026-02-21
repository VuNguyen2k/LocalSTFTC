#include "Common.h"

#include <algorithm>
#include <functional>
#include <vector>

int GetSpectrumSize(_In_ FourierConfigs& configs) { return configs.nfft / 2 + 1; }

int GetMinimumWaveSize(_In_ FourierConfigs& configs) { return configs.nfft; }

void Complex2InterleavedRealVector(_In_ std::vector<Complex>& vinput,
                                   _Out_ std::vector<Real>& voutput) {}
void InterleavedReal2ComplexVector(_In_ std::vector<Real>& vinput,
                                   _Out_ std::vector<Complex>& voutput) {}

void InterleaveRealVector(_In_ std::vector<Real>& vinput_real,
                          _In_ std::vector<Real>& vinput_imag,
                          _Out_ std::vector<Real>& voutput) {
  ASSERT(voutput.size() == vinput_real.size() + vinput_imag.size());
  for (unsigned int i = 0; i < voutput.size(); i++) {
    auto idx = i / 2u;
    if (i % 2 == 0) {
      voutput[i] = vinput_real[idx];
    } else {
      voutput[i] = vinput_imag[idx];
    }
  }
}

void DeinterleaveRealVector(_In_ std::vector<Real>& vinput,
                            _Out_ std::vector<Real>& voutput_real,
                            _Out_ std::vector<Real>& voutput_imag) {
  ASSERT(vinput.size() == voutput_real.size() + voutput_imag.size());
  for (unsigned int i = 0; i < vinput.size(); i++) {
    auto idx = i / 2u;
    if (i % 2 == 0) {
      voutput_real[idx] = vinput[i];
    } else {
      voutput_imag[idx] = vinput[i];
    }
  }
}
