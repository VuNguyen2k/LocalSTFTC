#include "FourierInterface.h"

#include <fmt/core.h>

#include <memory>

#include "Dummy.h"
#include "PFFFT.h"

std::unique_ptr<FourierInterface> FourierInterface::Create(
    _In_ FourierType ftype, _In_ FourierConfigs& configs) {
  switch (ftype) {
    case FourierType::DUMMY: {
      return std::make_unique<Dummy>(configs);
    }
    case FourierType::PFFFT: {
      return std::make_unique<PFFFT>(configs);
    }
    default:
      throw std::runtime_error(
          fmt::format("Fourier type {} is not a valid type", static_cast<int>(ftype)));
  }
}
