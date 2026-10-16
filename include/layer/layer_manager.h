#pragma once

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {
class Scn;
class WinProc;
} // namespace ml

namespace layer {

class LayerManager {
public:
  LayerManager(ml::Scn *scn, mtl::ALLOC_HANDLE handle, unsigned int size);
  virtual ~LayerManager();
  void tail();
  void openDebugWindow(ml::WinProc *window);

  unsigned char _08[0xb0 - 0x08];
};

} // namespace layer
