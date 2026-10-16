#pragma once

namespace event {

class IResPackEvent {
public:
  struct PARAM;

  virtual void OnPackEvent(const PARAM &param) = 0;
};

} // namespace event
