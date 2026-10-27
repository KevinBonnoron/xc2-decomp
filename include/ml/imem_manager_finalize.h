#pragma once

namespace ml {

class IMemManagerFinalize {
public:
  IMemManagerFinalize();
  virtual void notifyFinalize();
};

} // namespace ml
