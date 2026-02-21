#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

class Record {
 public:
  double forward_time, backward_time;
  Record(float forward_time, float backward_time)
      : forward_time(forward_time), backward_time(backward_time) {};
};

class Info {
 public:
  std::vector<double> data;

  double mean() {
    return std::accumulate(data.begin(), data.end(), 0.f,
                           [](double init, double first) { return init + first; }) /
           static_cast<double>(data.size());
  }

  double std() {
    auto m = mean();
    return sqrt(std::accumulate(data.begin(), data.end(), 0.f,
                                [m](double init, double first) {
                                  auto val = first - m;
                                  return init + val * val;
                                }) /
                static_cast<double>(data.size()));
  }
};

void gen_input(std::vector<float>& data) {
  for (int i = 0; i < data.size(); i++) {
    data[i] = 0.5;
  }
}

void gen_window(std::vector<float>& data) {
  const int N = data.size();
  auto window_func = [N](int n) {
    return sqrt(1.f / 2.f *
                (1 - cosf(2 * M_PI * static_cast<float>(n) / static_cast<float>(N))));
  };

  for (int i = 0; i < N; i++) data[i] = window_func(i);
}
