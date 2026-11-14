#pragma once
#include "ml/device.h"

namespace ml {
class WorkObj;

class DeviceNx : public Device {
public:
  DeviceNx(const char *name, WorkObj *parent) : Device(name, parent) {}
  ~DeviceNx() override;
  bool createDevice() override;
  void createDevicePort(const char *name) override;
  static void initializeSDK(const InitParam &param);
  static void finalizeSDK();
};

} // namespace ml
