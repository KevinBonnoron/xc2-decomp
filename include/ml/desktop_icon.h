#pragma once

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {

class DesktopIcon {
public:
  static DesktopIcon *create(mtl::ALLOC_HANDLE handle, const char *name, void (*func)());
};

} // namespace ml
