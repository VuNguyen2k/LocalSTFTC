#pragma once

#include <cassert>
#include <complex>
#include <exception>
#include <vector>

#define _In_ const
#define _Out_
#define _InOut_

using Complex = std::complex<float>;
using Real = float;

enum class FourierType { DUMMY = 0, PFFFT };
enum class BufferType { SIMPLE = 0 };
enum class WindowType { HANN = 0, SQRT_HANN };

struct FourierConfigs {
  int nfft;
};

struct BufferConfigs {
  int initial_size;
};

struct STFTConfigs {
  struct FourierConfigs fft_configs;
  struct BufferConfigs buffer_configs;

  int win_size;
  int hop_size;

  WindowType win_type;
  BufferType buffer_type;
  FourierType fft_type;
};

int GetSpectrumSize(_In_ FourierConfigs& configs);
int GetMinimumWaveSize(_In_ FourierConfigs& configs);

#define CHECK_SPECTRUM_SIZE(configs, spectrum_size) \
  (spectrum_size == GetSpectrumSize(configs))

#define CHECK_MINIMUM_WAVE_SIZE(configs, wave_size) \
  (wave_size >= GetMinimumWaveSize(configs))

#define ASSERT(exp) assert(exp)

void Complex2InterleavedRealVector(_In_ std::vector<Complex>& vinput,
                                   _Out_ std::vector<Real>& voutput);
void InterleavedReal2ComplexVector(_In_ std::vector<Real>& vinput,
                                   _Out_ std::vector<Complex>& voutput);

void InterleaveRealVector(_In_ std::vector<Real>& vinput_real,
                          _In_ std::vector<Real>& vinput_imag,
                          _Out_ std::vector<Real>& voutput);
void DeinterleaveRealVector(_In_ std::vector<Real>& vinput,
                            _Out_ std::vector<Real>& voutput_real,
                            _Out_ std::vector<Real>& voutput_imag);
