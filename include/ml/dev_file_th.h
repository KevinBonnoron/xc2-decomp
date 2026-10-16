#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ml {

class FileHandleTh;
class IWorkEvent;

class EventFileTh {
public:
  enum {
    TYPE_COMPLETE = 2,
  };

  int type;
};

struct DevFileParamTh {
  DevFileParamTh()
      : path(nullptr), _08(0), _10(0), buffer(nullptr), offset(0), readSize(0), _54(0), _58(1), _5c(0), event(nullptr), priority(10), _6c(true),
        _6d(false), _6e(false) {}

  const char *path;
  u32 _08;
  u64 _10;
  mm::mtl::FixedVector<u64, 4> _18;
  void *buffer;
  u32 size;
  u32 offset;
  u32 readSize;
  u32 _54;
  u32 _58;
  u32 _5c;
  IWorkEvent *event;
  u32 priority;
  bool _6c;
  bool _6d;
  bool _6e;
};

static_assert(sizeof(DevFileParamTh) == 0x70, "");

class DevFileTh {
public:
  static FileHandleTh *rfOpen(const DevFileParamTh &param);
  static bool rfRead(FileHandleTh *handle, const DevFileParamTh &param);
  static bool rfIsBusy(FileHandleTh *handle);
  static void rfClose(FileHandleTh *handle);
};

} // namespace ml
