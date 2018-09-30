#pragma once

class Impl {
public:
  virtual ~Impl() = default;

  virtual void fetch() = 0;
  virtual void execute() = 0;
  virtual void reset() = 0;

  virtual bool mustDraw() const = 0;
  virtual bool mustSound() const = 0;
};
