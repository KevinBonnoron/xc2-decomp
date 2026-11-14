#pragma once
#include <stddef.h>

#include "device/nx/dev_file_archive_nx.h"
#include "ml/critical_section.h"
#include "ml/dev_file_accessor.h"
#include "ml/dev_file_job_th.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace nn {
namespace account {
class UserHandle;
} // namespace account
} // namespace nn

namespace ml {

class DevFileNxTh : public DevFileAccessor, public mm::mtl::PtrSingleton<DevFileNxTh> {
public:
  // Inferred type: file channels with their state; the original type name is unknown.
  struct unknown001 {
    mm::mtl::FixedArray<OpenReadParam, 13> unknown00; // Inferred role: channels; original member name unknown.
    bool unknown17f8;                                 // Inferred role: finalizing; original member name unknown.
    s32 unknown17fc;                                  // Inferred role: running loader threads; original member name unknown.
    CriticalSection unknown1800;                      // Inferred role: write lock; original member name unknown.
  };

  static bool m_mountRom;
  static bool m_mountSave;
  static bool m_validuser;
  static nn::account::UserHandle m_appuser;
  static mm::mtl::FixStr<256> m_rootPath;

  DevFileNxTh(mtl::ALLOC_HANDLE handle);
  ~DevFileNxTh() override;
  bool initialize() override;
  bool finalize() override;
  void tail() override;
  u32 addressAlignment() override;
  bool readBlock(FileHandleTh *handle, const char *path) override;
  bool readBlockSlice(FileHandleTh *handle, const char *path, void *buffer, u32 size) override;
  int getFileSize(const char *path, mm::VAL64 *size, const char *archive) override;
  bool writeBlock(FileHandleTh *handle, DevFileResult &result) override;
  DevFileJobTh *createLoader(mtl::ALLOC_HANDLE handle) override;
  DevFileJobTh *createWriter(mtl::ALLOC_HANDLE handle) override;
  DevFileJobTh *createFileValid(mtl::ALLOC_HANDLE handle) override;
  bool rfOpen(FileHandleTh *handle, const char *path) override;
  bool rfRead(FileHandleTh *handle, const DevFileParamTh &param) override;
  bool rfIsBusy(FileHandleTh *handle) override;
  static void setMediaRootPath(const char *path);
  static void flushSave();
  static void finalizeSDK();
  static CriticalSection &getLocker();
  static CriticalSection &getWriteLock();
  static void *allocate(size_t size);
  static void deallocate(void *pointer, size_t size);
  bool rfClose(FileHandleTh *handle) override;
  bool getFilesBlock(char *&files, int &num, mtl::ALLOC_HANDLE handle, const char *path, const char *extension) override;
  bool deleteFileBlock(const char *path) override;
  const char *getMediaRootPath() const override;
  bool rfIsUsedChannel(u32 channel) override;
  static u32 thFileLoader(void *argument);
  void thUpdate(void *argument);

  u8 _10[0x14 - 0x10];
  mtl::ALLOC_HANDLE unknown14; // Inferred role: memory; original member name unknown.
  s32 unknown18;               // Inferred role: state; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  mm::mtl::UniquePtr<unknown001> unknown20; // Inferred role: channels; original member name unknown.
};

static_assert(offsetof(DevFileNxTh::unknown001, unknown17f8) == 0x17f8, "");
static_assert(offsetof(DevFileNxTh::unknown001, unknown17fc) == 0x17fc, "");
static_assert(offsetof(DevFileNxTh::unknown001, unknown1800) == 0x1800, "");
static_assert(sizeof(DevFileNxTh::unknown001) == 0x1828, "");
static_assert(offsetof(DevFileNxTh, unknown14) == 0x14, "");
static_assert(offsetof(DevFileNxTh, unknown20) == 0x20, "");

class DevFileJobValidNxTh : public DevFileJobTh {
public:
  bool asyncUpdate() override;
};

class DevFileWriterNx : public DevFileWriterTh {
public:
  bool asyncUpdate() override;
};

class DevFileBlackListNxTh : public mm::mtl::PtrSingleton<DevFileBlackListNxTh> {
public:
  DevFileBlackListNxTh(mtl::ALLOC_HANDLE handle);
  ~DevFileBlackListNxTh() override;
  bool check(const char *path);

  char *unknown08; // Inferred role: list of NUL terminated path patterns ended by an empty one; original member name unknown.
};

static_assert(offsetof(DevFileBlackListNxTh, unknown08) == 0x08, "");

} // namespace ml
