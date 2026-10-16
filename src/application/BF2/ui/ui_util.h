#pragma once
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ui {

class UIImageObject;
class UIObject;

class UIUtil {
public:
  static mm::mtl::IAllocator *getProgAllocator();
  static u32 registObject(UIObject *object);
  static UIObject *getObject(u32 handle);
  static UIImageObject *getImageObject(u32 handle);
  static u32 searchChild(u32 handle, const char *name);
  static void setDispChild(u32 handle, bool disp, const char *name);
  static bool isValid(u32 handle);
};

} // namespace ui
