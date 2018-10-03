#pragma once

class Sound {
public:
  virtual ~Sound() = default;

  virtual void playPitch() const = 0;
};
