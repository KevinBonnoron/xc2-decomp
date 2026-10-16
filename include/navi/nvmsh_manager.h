#pragma once

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {
class Scn;
class WinProc;
} // namespace ml

namespace navi {

class NvmshAcObj;

class NvmshManager {
public:
  NvmshManager(ml::Scn *scn, mtl::ALLOC_HANDLE handle);
  virtual ~NvmshManager();
  bool setupResource(const void *data, const char *name);
  void releaseResource();
  NvmshAcObj *createObj();
  void releaseObj(NvmshAcObj *object);
  void tail();
  void openDebugWindow(ml::WinProc *window);

  unsigned char _08[0x80 - 0x08];
};

} // namespace navi
