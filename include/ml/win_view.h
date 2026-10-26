#pragma once
#include "ml/work_obj.h"

namespace ml {
class IWorkEvent;

class WinView : public WorkObj {
public:
  void attachWorkEvent(IWorkEvent *event, bool isFront);
  virtual void evtFocusOn();
  virtual void evtFocusOff();
  virtual void detachRenderWork(const WorkObj *work);
  virtual void detachWorkEvent(const IWorkEvent *event);
};

} // namespace ml
