#pragma once
#include <stddef.h>

#include "ml/work_event.h"
#include "types.h"

namespace fw {

class Framework;
struct UpdateInfo;

class Applet : public ml::IWorkEvent {
public:
  Applet() : unknown08(false), unknown0c(false), unknownb0(nullptr) {
    for (u32 i = 0; i < 8; i++) {
      unknown8c[i] = 0;
    }
  }

  virtual void initializeResource(const Framework &framework);
  virtual void initialize(const Framework &framework) = 0;
  virtual void finalize(const Framework &framework) = 0;
  virtual bool isInitialized();
  virtual void enter();
  virtual void preUpdate(const UpdateInfo &info);
  virtual void update(const UpdateInfo &info) = 0;
  virtual void postUpdate(const UpdateInfo &info);
  virtual void tail(const UpdateInfo &info);

  bool unknown08; // Inferred role: closed; original member name unknown.
  u8 _09[0x0c - 0x09];
  bool unknown0c; // Role and original member name unknown.
  u8 _0d[0x8c - 0x0d];
  u32 unknown8c[8]; // Role and original member name unknown.
  u8 _ac[0xb0 - 0xac];
  void *unknownb0; // Role and original member name unknown.
};

static_assert(offsetof(Applet, unknown08) == 0x08, "");
static_assert(offsetof(Applet, unknown0c) == 0x0c, "");
static_assert(offsetof(Applet, unknown8c) == 0x8c, "");
static_assert(offsetof(Applet, unknownb0) == 0xb0, "");
static_assert(sizeof(Applet) == 0xb8, "");

} // namespace fw
