#pragma once
#include "ml/work_event.h"
#include "types.h"

namespace ml {

class WorkObj : public IWorkEvent {
public:
  WorkObj(const char *name, WorkObj *parent, int childNum);
  ~WorkObj() override;
  virtual bool wkStandby();
  virtual void wkUpdate();
  virtual void wkRender();
  virtual void wkRenderAfter();
  virtual void wkTail();
  virtual void wkFrameEnd();
  virtual bool wkStandbyLogin();
  virtual bool wkStandbyLogout();
  virtual bool wkStandbyExceptionRetry(u32 count);

  u8 _008[0x94 - 0x008];
  s32 m_childCount;
  u8 _098[0x1a8 - 0x098];
};

static_assert(sizeof(WorkObj) == 0x1a8, "");

} // namespace ml
