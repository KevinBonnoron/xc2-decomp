#pragma once

namespace ml {

class EventFileTh;
class EventView;

class IWorkEvent {
public:
  virtual ~IWorkEvent() {}
  virtual void OnSystemPause(unsigned int reason) {}
  virtual void OnShutdownForce() {}
  virtual bool IsShutdownForce() { return true; }
  virtual void OnPauseTrigger(bool isPause, const char *name) {}
  virtual void OnViewResize(EventView *event) {}
  virtual bool OnFileEvent(EventFileTh *event) { return false; }
};

} // namespace ml
