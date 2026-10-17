#pragma once

namespace nn {
namespace oe {

enum OperationMode {
  OperationMode_Handheld,
  OperationMode_Console,
};

enum PerformanceMode {
  PerformanceMode_Invalid = -1,
  PerformanceMode_Normal,
  PerformanceMode_Boost,
};

enum FocusState {
  FocusState_InFocus = 1,
  FocusState_OutOfFocus,
  FocusState_Background,
};

void EnableScreenShot();
void DisableScreenShot();
OperationMode GetOperationMode();
PerformanceMode GetPerformanceMode();
void SetOperationModeChangedNotificationEnabled(bool isEnabled);
void SetPerformanceModeChangedNotificationEnabled(bool isEnabled);
void SetResumeNotificationEnabled(bool isEnabled);
FocusState GetCurrentFocusState();
void SetPerformanceConfiguration(PerformanceMode mode, int configuration);
void EnterExitRequestHandlingSection();

} // namespace oe
} // namespace nn
