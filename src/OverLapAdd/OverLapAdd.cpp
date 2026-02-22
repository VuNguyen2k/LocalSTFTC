#include "OverLapAdd.h"

OverLapAdd::OverLapAdd(_In_ STFTConfigs& configs) : configs_(configs) {
  pbuffer_ =
      BufferInterface::Create(GetConfigs().buffer_type, GetConfigs().buffer_configs);

  {
    std::vector<Real> dummy(GetConfigs().hop_size, 0);
    for (int i = 0; i < GetConfigs().win_size; i += GetConfigs().hop_size) {
      pbuffer_->PutRange(dummy);
    }
  }
}

OverLapAdd::~OverLapAdd() {}

void OverLapAdd::Step(_In_ std::vector<Real>& vinput,
                      _Out_ std::vector<Real>& voutput) {
  voutput = pbuffer_->PopRange(GetConfigs().hop_size);

  {
    std::vector<Real> dummy(GetConfigs().hop_size, 0);
    pbuffer_->PutRange(dummy);
  }

  for (size_t i = 0; i < pbuffer_->Size(); i++) {
    auto& x = pbuffer_->Get(i);
    x += vinput[i];
  }
}
