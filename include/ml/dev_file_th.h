#pragma once
#include <stddef.h>

#include "ml/dev_base.h"
#include "ml/error_cb.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
union VAL64;
} // namespace mm

namespace ml {

class FileHandleTh;
class IWorkEvent;

enum CBM {};

class EventFileTh {
public:
  enum {
    TYPE_COMPLETE = 2,
    TYPE_VALID = 9,
  };

  EventFileTh(CBM cbm, FileHandleTh *handle);
  void setMemHandle(mtl::ALLOC_HANDLE handle);
  void *moveFileData();

  int type;
  FileHandleTh *unknown08;     // Inferred role: file handle; original member name unknown.
  mtl::ALLOC_HANDLE unknown10; // Inferred role: mem handle; original member name unknown.
  void *unknown18;             // Inferred role: file size; original member name unknown.
  const u8 *unknown20;         // Inferred role: path; original member name unknown.
  void *unknown28;             // Inferred role: file data; original member name unknown.
  s32 unknown30;               // Inferred role: read size; original member name unknown.
  void *unknown38;             // Inferred role: event; original member name unknown.
};

static_assert(offsetof(EventFileTh, unknown08) == 0x08, "");
static_assert(offsetof(EventFileTh, unknown10) == 0x10, "");
static_assert(offsetof(EventFileTh, unknown38) == 0x38, "");

struct DevFileParamTh {
  DevFileParamTh() : unknown00(nullptr), _08(), _10(0), unknown40(nullptr), unknown4c(0), unknown50(0), _54(0), _58(1), _5c(0), unknown60(nullptr), unknown68(10), _6c(true), _6d(false), _6e(false) {}

  const char *unknown00; // Inferred role: path; original member name unknown.
  mtl::ALLOC_HANDLE _08;
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

class DevFileTh : public DevBase, public mm::mtl::PtrSingleton<DevFileTh>, public IErrorCB {
public:
  class Impl {
  public:
    FileHandleTh *checkValidFile(const char *path, IWorkEvent *event);
    bool writeFileBlock(const char *path, const void *data, u32 size, int priority);
    FileHandleTh *readFile(const DevFileParamTh &param);
    FileHandleTh *rfOpen(const DevFileParamTh &param);
    bool rfClose(FileHandleTh *handle);
    bool rfIsBusy();
    void cancelRequest(FileHandleTh *handle);
    bool isValidHandle(FileHandleTh *handle);
  };

  static void normalizeDvdFileName(mm::mtl::FixStr<256> &fileName, const char *path);
  static FileHandleTh *checkValidFile(const char *path, IWorkEvent *event);
  static bool isInitialized();
  static bool writeFileBlock(const char *path, const void *data, u32 size, int priority);
  static FileHandleTh *rfOpen(const DevFileParamTh &param);
  static bool rfRead(FileHandleTh *handle, const DevFileParamTh &param);
  static bool rfIsBusy(FileHandleTh *handle);
  static bool rfClose(FileHandleTh *handle);
  static FileHandleTh *readFile(const DevFileParamTh &param);
  static void *readFileBlock(const DevFileParamTh &param, int *size, mm::VAL64 *fileSize);
  static void cancel(FileHandleTh *handle, bool isForce);
  static bool isValidHandle(FileHandleTh *handle);
  static bool rfIsBusy();
  static bool isNowSaving();
  static void setNowSaving(bool isSaving);
  static int getFileSize(const char *path, mm::VAL64 *size);
  static bool checkValidFileBlock(const char *path);
  static void sendCommand(const char *command, const char *argument);
  void wkTail() override;
  void wkUpdate() override;
  bool icbError(CERR_STRUCT *error) override;
  void icbDecide(CERR_STRUCT *error, ERR_DECIDE decide) override;

  mm::mtl::UniquePtr<Impl> unknown1c0; // Inferred role: implementation; original member name unknown.
  u8 _1c8;
  bool unknown1c9; // Inferred role: now saving; original member name unknown.
};

static_assert(offsetof(DevFileTh, unknown1c0) == 0x1c0, "");
static_assert(offsetof(DevFileTh, unknown1c9) == 0x1c9, "");

} // namespace ml
