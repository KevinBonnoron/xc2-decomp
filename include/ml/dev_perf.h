#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"

namespace ml {

enum DevPerfOperationMode {
  DEV_PERF_OPERATION_MODE_HANDHELD,
  DEV_PERF_OPERATION_MODE_CONSOLE,
};

enum DevPerfMode {
  DEV_PERF_MODE_NONE,
  DEV_PERF_MODE_NORMAL,
  DEV_PERF_MODE_BOOST,
  DEV_PERF_MODE_NUM,
};

enum DevPerfConfig {
  DEV_PERF_CONFIG_LOW,
  DEV_PERF_CONFIG_MIDDLE,
  DEV_PERF_CONFIG_HIGH,
};

class IDevPerf {
public:
  virtual ~IDevPerf() {}
  virtual void update() = 0;
  virtual DevPerfOperationMode getOperationMode() const = 0;
  virtual DevPerfMode getPerformanceMode() const = 0;
  virtual int getFocusState() const = 0;
  virtual void setPerfConfig(DevPerfMode mode, DevPerfConfig config) = 0;
  virtual DevPerfConfig getPerfConfig(DevPerfMode mode) const = 0;
};

class DevPerf : public WorkObj, public mm::mtl::PtrSingleton<DevPerf> {
public:
  DevPerf(const char *name, WorkObj *parent);
  static bool isInitialized();
  ~DevPerf() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  static void initialize();
  static void finalize();
  void wkUpdate() override;
  static DevPerfOperationMode getOperationMode();
  static DevPerfMode getPerformanceMode();
  static int getFocusState();
  static void setPerfConfig(DevPerfMode mode, DevPerfConfig config);
  static DevPerfConfig getPerfConfig(DevPerfMode mode);

  IDevPerf *unknown1b0; // Inferred role: impl; original member name unknown.
};

static_assert(offsetof(DevPerf, unknown1b0) == 0x1b0, "");

} // namespace ml
