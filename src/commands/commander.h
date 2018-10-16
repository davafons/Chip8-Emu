#pragma once

class Commander
{
public:
  Commander(Cpu& cpu, Memory& memory);

  // General
  bool shouldExit();
  void exit();
  void reset();

  // Cpu
  void togglePause();
  void doubleSpeed();
  void halfSpeed();

  // Memory
  void loadRom();

private:
  Cpu &cpu_;
  Memory &memory_;

  bool quit_{false};
};
