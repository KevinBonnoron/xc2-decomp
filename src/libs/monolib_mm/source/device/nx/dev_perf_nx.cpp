#include "device/nx/dev_perf_nx.h"

#include "ml/work_cpu.h"
#include "nn/oe.h"

namespace ml {

DevPerfNx::DevPerfNx() {
  m_operationMode = nn::oe::GetOperationMode() != nn::oe::OperationMode_Handheld ? DEV_PERF_OPERATION_MODE_CONSOLE : DEV_PERF_OPERATION_MODE_HANDHELD;
  m_performanceMode = nn::oe::GetPerformanceMode() == nn::oe::PerformanceMode_Boost ? DEV_PERF_MODE_BOOST : DEV_PERF_MODE_NORMAL;
  unknown10[DEV_PERF_MODE_NONE] = DEV_PERF_CONFIG_LOW;
  unknown10[DEV_PERF_MODE_NORMAL] = DEV_PERF_CONFIG_LOW;
  unknown10[DEV_PERF_MODE_BOOST] = DEV_PERF_CONFIG_HIGH;
  WorkCpu::addSystemInfoListener(this);
  nn::oe::SetOperationModeChangedNotificationEnabled(true);
  nn::oe::SetPerformanceModeChangedNotificationEnabled(true);
  nn::oe::SetResumeNotificationEnabled(true);
  nn::oe::EnterExitRequestHandlingSection();
}

DevPerfNx::~DevPerfNx() { WorkCpu::removeSystemInfoListener(this); }

void DevPerfNx::update() {
  int focusState;
  switch (nn::oe::GetCurrentFocusState()) {
  case nn::oe::FocusState_InFocus:
    focusState = nn::oe::FocusState_InFocus;
    break;
  case nn::oe::FocusState_OutOfFocus:
    focusState = nn::oe::FocusState_OutOfFocus;
    break;
  case nn::oe::FocusState_Background:
    focusState = nn::oe::FocusState_Background;
    break;
  default:
    focusState = 0;
    break;
  }
  m_focusState = focusState;
}

void DevPerfNx::changeOperationMode(DevPerfOperationMode mode) { m_operationMode = mode; }

void DevPerfNx::changePerformanceMode(DevPerfMode mode) { m_performanceMode = mode; }

void DevPerfNx::resumeApplication() {}

DevPerfOperationMode DevPerfNx::getOperationMode() const { return m_operationMode; }

DevPerfMode DevPerfNx::getPerformanceMode() const { return m_performanceMode; }

int DevPerfNx::getFocusState() const { return m_focusState; }

void DevPerfNx::setPerfConfig(DevPerfMode mode, DevPerfConfig config) {
  int configuration = config == DEV_PERF_CONFIG_HIGH ? 0x10001 : config == DEV_PERF_CONFIG_MIDDLE ? 0x20004 : 0x20003;
  nn::oe::PerformanceMode performanceMode = mode == DEV_PERF_MODE_NORMAL  ? nn::oe::PerformanceMode_Normal
                                            : mode == DEV_PERF_MODE_BOOST ? nn::oe::PerformanceMode_Boost
                                                                          : nn::oe::PerformanceMode_Invalid;
  nn::oe::SetPerformanceConfiguration(performanceMode, configuration);
  unknown10[mode] = config;
}

DevPerfConfig DevPerfNx::getPerfConfig(DevPerfMode mode) const { return unknown10[mode]; }

} // namespace ml
