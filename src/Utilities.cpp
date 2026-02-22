#include "Utilities.h"

#include <memory>
#include <vector>

#include "Common.h"

Real CalculateNorm(_In_ std::vector<Real>& v) {
  Real x = 0;
  for (auto& i : v) {
    x += (i * i);
  }
  return x;
}

void ApplyWindow(_In_ std::vector<Real>& vinput, _In_ std::vector<Real>& window,
                 _Out_ std::vector<Real>& voutput) {
  ASSERT(vinput.size() == window.size());
  size_t l = vinput.size();
  voutput.resize(l);

  for (size_t i = 0; i < l; i++) {
    voutput[i] = vinput[i] * window[i];
  }
}

void Scale(_InOut_ std::vector<Real>& v, Real factor) {
  for (size_t i = 0; i < v.size(); i++) {
    v[i] *= factor;
  }
}
