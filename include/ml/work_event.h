#pragma once

namespace ml {

class EventFileTh;
class EventView;

class IWorkEvent {
public:
  virtual ~IWorkEvent();
  virtual void OnSystemPause(unsigned int reason);
  virtual void OnShutdownForce();
  virtual bool IsShutdownForce();
  virtual void OnPauseTrigger(bool isPause, const char *name);
  virtual void OnViewResize(EventView *event);
  virtual bool OnFileEvent(EventFileTh *event);
};

class IWorkBackground {
public:
  virtual ~IWorkBackground();
  virtual void bkgHomeMenu(bool isOpen);
  virtual void bkgHomeMenuDenied();
};

} // namespace ml
