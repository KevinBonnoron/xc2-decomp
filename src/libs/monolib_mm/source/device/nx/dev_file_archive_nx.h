#pragma once
#include <atomic>
#include <stddef.h>

#include "ml/critical_section.h"
#include "ml/dev_file_accessor.h"
#include "ml/dev_file_job_th.h"
#include "ml/dev_file_th.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/internal/fixed_object_allocator.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/tuple.h"
#include "mm_mtl/unique_ptr.h"
#include "mm_thread/mm_thread_csection.h"
#include "mtl/alloc_handle.h"
#include "nn/fs.h"
#include "types.h"

namespace ml {

class DevFileArchiveNx;
class Thread;
class FileHandleTh;

// Name from the symbols (FixedArray<ml::OpenReadParam, 13>::~FixedArray).
struct OpenReadParam {
  OpenReadParam()
      : unknown00(), unknown10c(false), unknown10d(false), unknown10e(false), unknown10f(false), unknown110(false), unknown118(nullptr), unknown120(), unknown190(0), unknown198(nullptr),
        unknown1a0(nullptr) {}

  nn::fs::FileHandle unknown00;            // Inferred role: file; original member name unknown.
  mm::mtl::FixStr<256> unknown08;          // Inferred role: media file name; original member name unknown.
  bool unknown10c;                         // Inferred role: used; original member name unknown.
  bool unknown10d;                         // Inferred role: reading; original member name unknown.
  bool unknown10e;                         // Role and original member name unknown.
  bool unknown10f;                         // Inferred role: read in progress, the close is deferred; original member name unknown.
  bool unknown110;                         // Inferred role: close requested; original member name unknown.
  FileHandleTh *unknown118;                // Inferred role: file handle of the request; original member name unknown.
  DevFileParamTh unknown120;               // Inferred role: parameters of the request; original member name unknown.
  u64 unknown190;                          // Inferred role: data offset in the archive; original member name unknown.
  Thread *unknown198;                      // Inferred role: loader thread; original member name unknown.
  DevFileArchiveNx *unknown1a0;            // Inferred role: owner; original member name unknown.
  mm::threading::ReadWriteLock unknown1a8; // Inferred role: lock; original member name unknown.
  u8 _1c8[0x1d8 - 0x1c8];
};

static_assert(offsetof(OpenReadParam, unknown08) == 0x08, "");
static_assert(offsetof(OpenReadParam, unknown10c) == 0x10c, "");
static_assert(offsetof(OpenReadParam, unknown110) == 0x110, "");
static_assert(offsetof(OpenReadParam, unknown118) == 0x118, "");
static_assert(offsetof(OpenReadParam, unknown120) == 0x120, "");
static_assert(offsetof(OpenReadParam, unknown190) == 0x190, "");
static_assert(offsetof(OpenReadParam, unknown198) == 0x198, "");
static_assert(offsetof(OpenReadParam, unknown1a0) == 0x1a0, "");
static_assert(offsetof(OpenReadParam, unknown1a8) == 0x1a8, "");
static_assert(sizeof(OpenReadParam) == 0x1d8, "");

class DevFileArchiveNx : public DevFileAccessor, public mm::mtl::PtrSingleton<DevFileArchiveNx> {
public:
  // Name from the symbols (DevFileArchiveNx::Param::finalize...).
  struct Param {
    // Inferred type: file opened by a thread (thread id, file, path); original type name unknown.
    typedef mm::mtl::Tuple<u64, nn::fs::FileHandle, mm::mtl::FixStr<256>> unknown002;
    typedef mm::mtl::FixedQueue<unknown002 *, 16> unknown003; // Inferred type: open thread files; original type name unknown.

    void finalize();
    unknown002 *findThreadFilehandle(u64 threadId, const mm::mtl::FixStr<256> &path);
    nn::fs::FileHandle *addThreadFilehandle(u64 threadId, const mm::mtl::FixStr<256> &path);
    void removeThreadFilehandle(u64 threadId, const mm::mtl::FixStr<256> &path);

    mm::mtl::FixedArray<OpenReadParam, 13> unknown0000; // Inferred role: channels; original member name unknown.
    std::atomic<bool> unknown17f8;                      // Inferred role: finalizing; original member name unknown.
    u8 _17f9[0x17fc - 0x17f9];
    std::atomic<s32> unknown17fc;                              // Inferred role: running loader threads; original member name unknown.
    CriticalSection unknown1800;                               // Inferred role: lock of the thread files; original member name unknown.
    mm::mtl::FixedObjectAllocator<unknown002, 16> unknown1828; // Inferred role: thread file pool; original member name unknown.
    unknown003 unknown29b8;                                    // Inferred role: open thread files; original member name unknown.
  };

  DevFileArchiveNx(mtl::ALLOC_HANDLE handle);
  ~DevFileArchiveNx() override;
  bool initialize() override;
  bool finalize() override;
  void tail() override;
  u32 addressAlignment() override;
  bool readBlockSlice(FileHandleTh *handle, const char *path, void *buffer, u32 size) override;
  int getFileSize(const char *path, mm::VAL64 *size, const char *archive) override;
  DevFileJobTh *createLoader(mtl::ALLOC_HANDLE handle) override;
  DevFileJobTh *createWriter(mtl::ALLOC_HANDLE handle) override;
  DevFileJobTh *createFileValid(mtl::ALLOC_HANDLE handle) override;
  bool rfOpen(FileHandleTh *handle, const char *path) override;
  bool rfRead(FileHandleTh *handle, const DevFileParamTh &param) override;
  bool rfIsBusy(FileHandleTh *handle) override;
  bool rfClose(FileHandleTh *handle) override;
  bool rfIsUsedChannel(u32 channel) override;
  bool getFilesBlock(char *&files, int &num, mtl::ALLOC_HANDLE handle, const char *path, const char *extension) override;
  const char *getMediaRootPath() const override;
  static u32 thFileLoader(void *argument);
  void thUpdate(void *argument);
  void normalizeFileName(mm::mtl::FixStr<256> &fileName);

  u8 _10[0x14 - 0x10];
  mtl::ALLOC_HANDLE unknown14; // Inferred role: memory; original member name unknown.
  s32 unknown18;               // Inferred role: state; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  mm::mtl::UniquePtr<Param> unknown20; // Inferred role: parameters; original member name unknown.
};

static_assert(offsetof(DevFileArchiveNx::Param, unknown17f8) == 0x17f8, "");
static_assert(offsetof(DevFileArchiveNx::Param, unknown17fc) == 0x17fc, "");
static_assert(offsetof(DevFileArchiveNx::Param, unknown1800) == 0x1800, "");
static_assert(offsetof(DevFileArchiveNx::Param, unknown1828) == 0x1828, "");
static_assert(offsetof(DevFileArchiveNx::Param, unknown29b8) == 0x29b8, "");
static_assert(sizeof(DevFileArchiveNx::Param) == 0x2a48, "");
static_assert(offsetof(DevFileArchiveNx, unknown14) == 0x14, "");
static_assert(offsetof(DevFileArchiveNx, unknown20) == 0x20, "");

class DevFileJobValidArcNxTh : public DevFileJobTh {
public:
  bool asyncUpdate() override;
};

} // namespace ml
