#include <iostream>
#include <thread>

#include "timer.h"

Timer::Timer(int cpuFrequency, int timersFrequency) :
  cpuFrequency_(cpuFrequency),
  timersFrequency_(timersFrequency),
  now_(std::chrono::system_clock::now()),
  last_(std::chrono::system_clock::now())
{
}

void Timer::delayCpu() {
  now_ = std::chrono::system_clock::now();

  std::chrono::duration<double, std::milli> work_time = now_ - last_;
  if(work_time.count() < 1/double(cpuFrequency_) * 1000) {
    std::chrono::duration<double, std::milli> delta_ms(3.00 -
        work_time.count());
    auto delta_ms_duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
    std::this_thread::sleep_for(
        std::chrono::milliseconds(delta_ms_duration.count()));
  }

  last_ = std::chrono::system_clock::now();

  std::chrono::duration<double, std::milli> sleep_time = last_ - now_;

  accumulatedTime_ = accumulatedTime_ + work_time + sleep_time;
}

bool Timer::mustUpdateCpuTimers() {
  if(accumulatedTime_.count() > 1/double(timersFrequency_) * 1000) {
    accumulatedTime_ = std::chrono::duration<double, std::milli>(0.0);
    return true;
  }
  return false;
}
