#include <stdlib.h>

void AdjustLaunchDlgCpp() {}

void DebugWindowBattleCpp() {}

namespace main_detail {

bool strToInt(const char *string, int &value) {
  char *end;
  value = strtol(string, &end, 0);
  return end != string;
}

} // namespace main_detail
