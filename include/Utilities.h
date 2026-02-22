#pragma once

#include <memory>
#include <vector>

#include "Common.h"

Real CalculateNorm(_In_ std::vector<Real>& v);
void ApplyWindow(_In_ std::vector<Real>& vinput, _In_ std::vector<Real>& window,
                 _Out_ std::vector<Real>& voutput);
void Scale(_InOut_ std::vector<Real>& v, Real factor);
