#pragma once

#include <chrono>

class Timer {
public:
  explicit Timer(int cpuFrequency = 540, int timersFrequency = 60);

  void delayCpu();
  bool mustUpdateCpuTimers();

private:
  int cpuFrequency_;
  int timersFrequency_;

  std::chrono::system_clock::time_point now_;
  std::chrono::system_clock::time_point last_;

  std::chrono::duration<double, std::milli> accumulatedTime_;
};
