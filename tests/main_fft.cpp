#include "FourierInterface.h"
#include "utils.h"

void run() {
  FourierConfigs configs = {.nfft = 512};
  std::unique_ptr<FourierInterface> pfft =
      FourierInterface::Create(FourierType::PFFFT, configs);

  std::vector<float> vin(GetMinimumWaveSize(pfft->GetConfigs()), 0.5);
  std::vector<std::complex<float>> vout(GetSpectrumSize(pfft->GetConfigs()), 0);
  pfft->FFT(vin, vout);

  for (auto& i : vout) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  memset(vin.data(), 0, vin.size());
  pfft->iFFT(vout, vin);

  for (auto& i : vin) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int main() { run(); }