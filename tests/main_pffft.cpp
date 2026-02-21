#include <math.h>

#include <chrono>
#include <iostream>
#include <pffft.hpp>
#include <random>
#include <vector>

#include "utils.h"

Record run() {
  const int N = 1536;
  auto fft = pffft::Fft<float>(N);

  std::vector<float> window_func;
  std::vector<float> time_data, time_data1;
  std::vector<std::complex<float>> freq_domain;

  time_data.resize(N);
  time_data1.resize(N);
  window_func.resize(N);
  freq_domain.resize(N / 2 + 1);

  gen_input(time_data);
  gen_window(window_func);

  auto begin_forward = std::chrono::high_resolution_clock::now();
  // multiply input
  for (int i = 0; i < N; i++) time_data[i] *= window_func[i];

  fft.forward(time_data.data(), freq_domain.data());
  auto end_forward = std::chrono::high_resolution_clock::now();

  auto begin_backward = std::chrono::high_resolution_clock::now();
  // multiply input
  for (int i = 0; i < N; i++) time_data[i] *= window_func[i];

  fft.inverse(freq_domain.data(), time_data1.data());
  auto end_backward = std::chrono::high_resolution_clock::now();

  std::chrono::duration<float, std::milli> forward_duration =
      end_forward - begin_forward;
  std::chrono::duration<float, std::milli> backward_duration =
      end_backward - begin_backward;

  return Record(forward_duration.count(), backward_duration.count());
}

void summary(std::vector<Record>& records) {
  Info forward_info;
  Info backward_info;

  for (auto& record : records) {
    forward_info.data.push_back(record.forward_time);
    backward_info.data.push_back(record.backward_time);
  }

  std::cout << "forward: " << forward_info.mean() << "(" << forward_info.std() << ")"
            << std::endl;
  std::cout << "backward: " << backward_info.mean() << "(" << backward_info.std() << ")"
            << std::endl;
}

int main() {
  auto repeat_times = 0;
  std::cout << "Repeat? ";
  std::cin >> repeat_times;

  std::vector<Record> records;

  for (int i = 0; i < repeat_times; i++) {
    records.push_back(run());
  }

  summary(records);

  return 0;
}
