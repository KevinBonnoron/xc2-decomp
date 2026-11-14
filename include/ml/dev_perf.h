#pragma once
#include <stddef.h>

#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"

namespace ml {

enum DevPerfOperationMode {
  DEV_PERF_OPERATION_MODE_UNKNOWN_0, // Inferred role: handheld; original name unknown.
  DEV_PERF_OPERATION_MODE_UNKNOWN_1, // Inferred role: console; original name unknown.
};

enum DevPerfMode {
  DEV_PERF_MODE_UNKNOWN_0, // Inferred role: none; original name unknown.
  DEV_PERF_MODE_UNKNOWN_1, // Inferred role: normal; original name unknown.
  DEV_PERF_MODE_UNKNOWN_2, // Inferred role: boost; original name unknown.
  DEV_PERF_MODE_UNKNOWN_3, // Inferred role: number of performance modes; original name unknown.
};

enum DevPerfConfig {
  DEV_PERF_CONFIG_UNKNOWN_0, // Inferred role: low; original name unknown.
  DEV_PERF_CONFIG_UNKNOWN_1, // Inferred role: middle; original name unknown.
  DEV_PERF_CONFIG_UNKNOWN_2, // Inferred role: high; original name unknown.
};

// Inferred role: device interface perf; original type name unknown.
class unknown074 {
public:
  virtual ~unknown074() {}
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

  unknown074 *unknown1b0; // Inferred role: impl; original member name unknown.
};

static_assert(offsetof(DevPerf, unknown1b0) == 0x1b0, "");

} // namespace ml
