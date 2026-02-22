#include <iostream>

#include "Common.h"
#include "ShortTimeFFTInterface.h"

void run() {
  struct STFTConfigs configs = {
      .fft_configs.nfft = 512,
      .buffer_configs.initial_size = 512,
      .win_size = 512,
      .hop_size = 128,
      .buffer_type = BufferType::SIMPLE,
      .win_type = WindowType::HANN,
      .fft_type = FourierType::PFFFT,
  };

  auto pstft = ShortTimeFFTInterface::Create(STFTType::REALTIME, configs);

  std::vector<Real> x(configs.win_size * 5, 0.5);
  std::vector<Real> y;

  for (int i = 0; i < x.size(); i += configs.hop_size) {
    auto ibegin = x.begin() + i;
    auto iend = ibegin + configs.win_size;

    if (iend > x.end()) {
      break;
    }

    std::vector<Real> subx(ibegin, iend), voutput;
    std::vector<std::vector<Complex>> spectrum;

    pstft->STFT(subx, spectrum);
    pstft->iSTFT(spectrum, voutput);

    y.insert(y.end(), voutput.begin(), voutput.end());
  }

  for (auto& i : y) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  std::cout << x.size() << " " << y.size() << std::endl;
}

int main() { run(); }