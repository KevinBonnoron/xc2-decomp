#pragma once
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct SDataPouch;

class GfPouchUtil {
public:
  static SDataPouch *getPouch(u32 driver, u32 slot);
  static void setPouch(u32 driver, u32 slot, const SDataPouch &pouch);
  static void updatePouch(u32 driver, u32 slot, const SDataPouch &pouch, const fw::UpdateInfo &info);
  static void execOpen(u32 driver);
  static bool isEnableOpen(u32 driver);
  static u8 getOpenCount(u32 driver);
  static void setTimeUpForDebug(u32 driver, u32 slot);
  static bool isExistOpenItem();
};

} // namespace gf
