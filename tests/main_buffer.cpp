#include "BufferInterface.h"
#include "Common.h"

void run() {
  struct BufferConfigs configs = {
      .initial_size = 512,
  };
  auto pbuffer = BufferInterface::Create(BufferType::SIMPLE, configs);

  pbuffer->Put(10);
  ASSERT(pbuffer->Size() == 1u);
  ASSERT(pbuffer->Get(0) == 10);
  ASSERT(pbuffer->Pop() == 10);
  ASSERT(pbuffer->Size() == 0u);

  std::vector<Real> x = {100, 99, 98};
  pbuffer->PutRange(x);

  ASSERT(pbuffer->Size() == 3u);

  for (int i = 0; i < pbuffer->Size(); i++) {
    ASSERT(x[i] == pbuffer->Get(i));
  }

  auto& a = pbuffer->Get(2);
  a += 3;
  ASSERT(pbuffer->Get(2) == 101);

  std::vector<Real> y = pbuffer->PopRange(pbuffer->Size());
  ASSERT(pbuffer->Size() == 0u);

  for (int i = 0; i < x.size() - 1; i++) {
    ASSERT(x[i] == y[i]);
  }
}

int main() { run(); }