#pragma once

namespace ml {

class DrEnvColiObj {
public:
  void release();
  void setPause(bool isPause);
  bool isPause() const;
};

} // namespace ml
