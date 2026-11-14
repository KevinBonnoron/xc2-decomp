#pragma once
#include <stddef.h>

#include "ml/dev_perf.h"
#include "ml/work_infomation.h"

namespace ml {

class DevPerfNx : public unknown074, public IWorkInfomation {
public:
  DevPerfNx();
  ~DevPerfNx() override;
  void update() override;
  void changeOperationMode(DevPerfOperationMode mode) override;
  void changePerformanceMode(DevPerfMode mode) override;
  void resumeApplication() override;
  DevPerfOperationMode getOperationMode() const override;
  DevPerfMode getPerformanceMode() const override;
  int getFocusState() const override;
  void setPerfConfig(DevPerfMode mode, DevPerfConfig config) override;
  DevPerfConfig getPerfConfig(DevPerfMode mode) const override;

  DevPerfConfig m_perfConfig[DEV_PERF_MODE_UNKNOWN_3];
  DevPerfOperationMode m_operationMode;
  DevPerfMode m_performanceMode;
  int m_focusState;
};

static_assert(offsetof(DevPerfNx, m_perfConfig) == 0x10, "");
static_assert(offsetof(DevPerfNx, m_focusState) == 0x24, "");

} // namespace ml
