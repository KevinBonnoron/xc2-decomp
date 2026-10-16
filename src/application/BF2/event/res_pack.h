#pragma once
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace fw {
class RenderResource;
} // namespace fw

namespace event {

class IResPackEvent;

class ResPack {
public:
  struct File {
    u32 offset;
    u32 size;
    u8 _8[0x10 - 0x8];
    char path[0x80];
  };

  struct Data {
    u8 _0[0x4 - 0x0];
    u32 count;
    u8 _8[0x10 - 0x8];
    File files[1];
  };

  ResPack();
  virtual ~ResPack();
  void clear();
  void update();
  void draw();
  void load(mtl::ALLOC_HANDLE handle, const char *path, IResPackEvent *event);
  void func_loading();

  bool isLoading() const { return mFunc ? true : false; }

private:
  mtl::ALLOC_HANDLE handle;
  mm::mtl::FixStr<128> path;
  IResPackEvent *mEvent;
  void (ResPack::*mFunc)();
  fw::RenderResource *mResource;
};

static_assert(sizeof(ResPack) == 0xb0, "");

} // namespace event
