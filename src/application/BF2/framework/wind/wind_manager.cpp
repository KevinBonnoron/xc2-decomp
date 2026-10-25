#include "framework/wind/wind_manager.h"

namespace fw {

const char *WindManager::getName() const { return "WindManager"; }

bool WindManager::isDebugMode() { return false; }

void WindManager::activateDebugWindow(ml::WinProc *window) {}

} // namespace fw
