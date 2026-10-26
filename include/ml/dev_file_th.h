#pragma once
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {

class FileHandleTh;
class IWorkEvent;

class EventFileTh {
public:
  enum {
    TYPE_COMPLETE = 2,
    TYPE_VALID = 9,
  };

  int type;
};

struct DevFileParamTh {
  DevFileParamTh() : unknown00(nullptr), _08(0), _10(0), unknown40(nullptr), unknown4c(0), unknown50(0), _54(0), _58(1), _5c(0), unknown60(nullptr), unknown68(10), _6c(true), _6d(false), _6e(false) {}

  const char *unknown00; // Inferred role: path; original member name unknown.
  u32 _08;
  u64 _10;
  mm::mtl::FixedVector<u64, 4> _18;
  void *unknown40; // Inferred role: buffer; original member name unknown.
  u32 unknown48;   // Inferred role: size; original member name unknown.
  u32 unknown4c;   // Inferred role: offset; original member name unknown.
  u32 unknown50;   // Inferred role: read size; original member name unknown.
  u32 _54;
  u32 _58;
  u32 _5c;
  IWorkEvent *unknown60; // Inferred role: event; original member name unknown.
  u32 unknown68;         // Inferred role: priority; original member name unknown.
  bool _6c;
  bool _6d;
  bool _6e;
};

static_assert(sizeof(DevFileParamTh) == 0x70, "");

class DevFileTh {
public:
  static void normalizeDvdFileName(mm::mtl::FixStr<256> &fileName, const char *path);
  static void checkValidFile(const char *path, IWorkEvent *event);
  static bool isInitialized();
  static bool writeFileBlock(const char *path, const void *data, u32 size, int priority);
  static FileHandleTh *rfOpen(const DevFileParamTh &param);
  static bool rfRead(FileHandleTh *handle, const DevFileParamTh &param);
  static bool rfIsBusy(FileHandleTh *handle);
  static void rfClose(FileHandleTh *handle);
  static FileHandleTh *readFile(const DevFileParamTh &param);
  static void cancel(FileHandleTh *handle, bool isForce);
};

} // namespace ml
