#pragma once
#include <stddef.h>

#include "ml/work_event.h"

namespace fw {

class Framework;
struct UpdateInfo;

class Applet : public ml::IWorkEvent {
public:
  virtual void initializeResource(const Framework &framework);
  virtual void initialize(const Framework &framework) = 0;
  virtual void finalize(const Framework &framework) = 0;
  virtual bool isInitialized();
  virtual void enter();
  virtual void preUpdate(const UpdateInfo &info);
  virtual void update(const UpdateInfo &info) = 0;
  virtual void postUpdate(const UpdateInfo &info);
  virtual void tail(const UpdateInfo &info);

  bool closed;
};

static_assert(offsetof(Applet, closed) == 0x08, "");

} // namespace fw
