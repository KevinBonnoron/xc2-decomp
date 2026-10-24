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
    u32 unknown00; // Inferred role: offset; original member name unknown.
    u32 unknown04; // Inferred role: size; original member name unknown.
    u8 _8[0x10 - 0x8];
    char unknown10[0x80]; // Inferred role: path; original member name unknown.
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

  bool isLoading() const { return unknown98 ? true : false; }

private:
  mtl::ALLOC_HANDLE unknown08;    // Inferred role: handle; original member name unknown.
  mm::mtl::FixStr<128> unknown0c; // Inferred role: path; original member name unknown.
  IResPackEvent *unknown90;       // Inferred role: event; original member name unknown.
  void (ResPack::*unknown98)();   // Inferred role: func; original member name unknown.
  fw::RenderResource *unknowna8;  // Inferred role: resource; original member name unknown.
};

static_assert(sizeof(ResPack) == 0xb0, "");

} // namespace event
