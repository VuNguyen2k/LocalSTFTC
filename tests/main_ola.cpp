#include <iostream>

#include "Common.h"
#include "FourierInterface.h"
#include "OverLapAdd.h"
#include "Utilities.h"
#include "WindowsInterface.h"

void run() {
  struct STFTConfigs configs = {
      .fft_configs = {.nfft = 512},
      .buffer_configs = {.initial_size = 512},
      .win_size = 512,
      .hop_size = 128,
      .win_type = WindowType::HANN,
      .buffer_type = BufferType::SIMPLE,
      .fft_type = FourierType::PFFFT,
  };

  auto window = WindowsInterface::Create(configs.win_type, configs.win_size);
  auto win_norm = CalculateNorm(window) * static_cast<Real>(configs.fft_configs.nfft) /
                  static_cast<Real>(configs.hop_size);

  auto fft = FourierInterface::Create(configs.fft_type, configs.fft_configs);

  OverLapAdd ola(configs);

  std::vector<Real> x(configs.win_size * 5, 0.5);
  std::vector<Real> y;
  for (int i = 0; i < x.size(); i += configs.hop_size) {
    auto ibegin = x.begin() + i;
    auto iend = ibegin + configs.win_size;

    if (iend > x.end()) {
      break;
    }

    std::vector<Real> subx(ibegin, iend);

    std::vector<Real> windowed_inputs;
    ApplyWindow(subx, window, windowed_inputs);

    std::vector<Complex> spectrum(GetSpectrumSize(configs.fft_configs));
    fft->FFT(windowed_inputs, spectrum);

    std::vector<Real> ifft_output(configs.win_size);
    fft->iFFT(spectrum, ifft_output);

    std::vector<Real> windowed_modified_outputs;
    ApplyWindow(ifft_output, window, windowed_modified_outputs);

    std::vector<Real> voutput;
    ola.Step(windowed_modified_outputs, voutput);
    Scale(voutput, 1.f / win_norm);

    y.insert(y.end(), voutput.begin(), voutput.end());
  }

  for (auto& i : y) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  std::cout << x.size() << " " << y.size() << std::endl;
}

int main() { run(); }