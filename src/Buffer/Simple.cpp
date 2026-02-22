#include "Simple.h"

#include "Common.h"

SimpleBuffer::SimpleBuffer(_In_ BufferConfigs& configs) : BufferInterface(configs) {}
SimpleBuffer::~SimpleBuffer() {}

void SimpleBuffer::Put(_In_ Real v) { queue_.push_back(v); }

Real SimpleBuffer::Pop() {
  Real x = 0;
  if (queue_.size() > 0) {
    x = Get(0);
    queue_.erase(queue_.begin());
  }
  return x;
}

Real& SimpleBuffer::Get(_In_ size_t idx) {
  ASSERT(queue_.size() > 0);
  return queue_.at(idx);
}

size_t SimpleBuffer::Size() { return queue_.size(); }
