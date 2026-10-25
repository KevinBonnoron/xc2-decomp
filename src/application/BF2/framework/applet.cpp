#include "framework/applet.h"

namespace fw {

void Applet::initializeResource(const Framework &framework) {}

bool Applet::isInitialized() { return true; }

void Applet::enter() {}

void Applet::preUpdate(const UpdateInfo &info) {}

void Applet::postUpdate(const UpdateInfo &info) {}

void Applet::tail(const UpdateInfo &info) {}

} // namespace fw
