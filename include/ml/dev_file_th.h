#pragma once
#include <stddef.h>

#include "ml/critical_section.h"
#include "ml/dev_base.h"
#include "ml/error_cb.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
union VAL64;
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ml {

class DevFileAccessor;
class DevFileJobTh;
class DevFileJob;
class FileHandleTh;
class IDevFileEvent;
class IWorkEvent;

enum CBM : int {
  CBM_UNKNOWN_2 = 2,
  CBM_UNKNOWN_4 = 4,
  CBM_UNKNOWN_5 = 5,
  CBM_UNKNOWN_6 = 6,
};
enum MEDIA {
  MEDIA_UNKNOWN_0 = 0, // Inferred role: path without media prefix.
  MEDIA_UNKNOWN_8 = 8, // Inferred role: media count, unset media of a DevFileArchiver list.
};

namespace dvfl_detail {
// Inferred type: load media parameter; the original type name is unknown.
struct LoadMediaParam {
  MEDIA unknown00; // Inferred role: media; original member name unknown.
  u8 _04[0x08 - 0x04];
  mm::mtl::FixStr<128> unknown08; // Inferred role: archive name; original member name unknown.
};

static_assert(offsetof(LoadMediaParam, unknown08) == 0x08, "");
static_assert(sizeof(LoadMediaParam) == 0x8c, "");

// Archive registered by DevFileTh::registArchive before the archiver exists.
struct ReserveArchiveParam {
  MEDIA unknown00;                 // Inferred role: media; original member name unknown.
  mm::mtl::FixStr<128> unknown04;  // Inferred role: archive path; original member name unknown.
  mm::mtl::FixStr<128> unknown88;  // Inferred role: second registArchive name; original member name unknown.
  mm::mtl::FixStr<128> unknown10c; // Inferred role: third registArchive name; original member name unknown.
};

static_assert(offsetof(ReserveArchiveParam, unknown04) == 0x04, "");
static_assert(offsetof(ReserveArchiveParam, unknown88) == 0x88, "");
static_assert(offsetof(ReserveArchiveParam, unknown10c) == 0x10c, "");
static_assert(sizeof(ReserveArchiveParam) == 0x190, "");

void clearLoadMedia();
void addMediaPath(MEDIA media, const char *path, int priority);
} // namespace dvfl_detail

class EventFileTh {
public:
  enum {
    TYPE_UNKNOWN_2 = 2, // Inferred role: complete; original name unknown.
    TYPE_UNKNOWN_9 = 9, // Inferred role: valid; original name unknown.
  };

  EventFileTh(CBM cbm, FileHandleTh *handle);
  void setMemHandle(mtl::ALLOC_HANDLE handle);
  void *moveFileData();

  int type;
  FileHandleTh *unknown08; // Inferred role: file handle; original member name unknown.
  mtl::ALLOC_HANDLE m_memHandle;
  void *unknown18;       // Inferred role: file size; original member name unknown.
  const char *unknown20; // Inferred role: path; original member name unknown.
  void *unknown28;       // Inferred role: file data; original member name unknown.
  s32 unknown30;         // Inferred role: read size; original member name unknown.
  void *unknown38;       // Inferred role: event; original member name unknown.
};

static_assert(offsetof(EventFileTh, unknown08) == 0x08, "");
static_assert(offsetof(EventFileTh, m_memHandle) == 0x10, "");
static_assert(offsetof(EventFileTh, unknown38) == 0x38, "");

struct DevFileParamTh {
  DevFileParamTh()
      : unknown00(nullptr), _08(), _10(nullptr), unknown40(nullptr), unknown4c(0), unknown50(0), _54(0), _58(1), _5c(0), unknown60(nullptr), unknown68(10), _6c(true), _6d(false), _6e(false) {}

  const char *unknown00; // Inferred role: path; original member name unknown.
  mtl::ALLOC_HANDLE _08;
  mm::mtl::IAllocator *_10;
  mm::mtl::FixedVector<mtl::ALLOC_HANDLE, 8> _18;
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
    ~Impl();
    FileHandleTh *checkValidFile(const char *path, IWorkEvent *event);
    bool writeFileBlock(const char *path, const void *data, u32 size, int priority);
    FileHandleTh *writeFile(const char *path, IWorkEvent *event, const void *data, int size, int priority);
    FileHandleTh *readFile(const DevFileParamTh &param);
    FileHandleTh *rfOpen(const DevFileParamTh &param);
    bool rfRead(FileHandleTh *handle, const DevFileParamTh &param);
    bool rfIsBusy(FileHandleTh *handle);
    bool rfClose(FileHandleTh *handle);
    bool rfIsBusy();
    void cancelRequest(FileHandleTh *handle);
    bool isValidHandle(FileHandleTh *handle);
    void suspendThread();
    bool isSuspendThread();
    void resumeThread();
    static void setSuspend(bool suspend);
    bool isSuspend() const;
    bool isInitialized();
    bool initialize();
    bool finalize();
    bool getReadingInfo(mm::mtl::FixStr<256> &name, f32 &ratio);
    bool getWritingInfo(mm::mtl::FixStr<256> &name, f32 &ratio);
    void registAccessor(MEDIA media, DevFileAccessor *accessor);
    void removeAccessor(MEDIA media);
    void registArchiveAccessor(MEDIA media, DevFileAccessor *accessor);
    void removeArchiveAccessor(MEDIA media);
    int getFileSize(const char *path, mm::VAL64 *size, const dvfl_detail::LoadMediaParam &param);
    int getArchiveFileSize(const char *path, mm::VAL64 *size, const dvfl_detail::LoadMediaParam &param);
    bool getFilesBlock(char *&files, int &num, mtl::ALLOC_HANDLE handle, const char *path, const char *extension);
    bool deleteFileBlock(const char *path);
    void rfCancel(FileHandleTh *handle);
    bool isBusy();
    bool isLoading(FileHandleTh *handle);
    bool isLapTimeForDebug() { return false; }
    static void enableLapTimeForDebug(bool enable) {}

    // Inferred role: accessor of the media of a file handle, the archive accessor first for media 0; original name unknown.
    DevFileAccessor *unknown005(MEDIA media) const {
      if (media == 0 && unknown588f0[0] != nullptr) {
        return unknown588f0[0];
      }
      return unknown588b0[media];
    }

    mm::mtl::FixedList<DevFileJobTh *, 640> unknown00000; // Inferred role: waiting jobs; original member name unknown.
    mm::mtl::FixedList<DevFileJobTh *, 640> unknown02d20; // Inferred role: loading jobs; original member name unknown.
    mm::mtl::FixedList<DevFileJobTh *, 640> unknown05a40; // Inferred role: finished jobs; original member name unknown.
    u8 _08760[0x588b0 - 0x8760];
    DevFileAccessor *unknown588b0[8]; // Inferred role: accessor per media; original member name unknown.
    DevFileAccessor *unknown588f0[8]; // Inferred role: archive accessor per media; original member name unknown.
    u8 _58930[0x58934 - 0x58930];
    bool m_initialized;
    u8 _58935[0x5a348 - 0x58935];
    IWorkEvent *unknown5a348;     // Inferred role: registered event callback; original member name unknown.
    CriticalSection unknown5a350; // Inferred role: job lock; original member name unknown.
    CriticalSection unknown5a378; // Inferred role: read lock; original member name unknown.
  };

  ~DevFileTh() override;

  static const int INVALID_FILE_CHANNEL; // Name from the game symbol _ZN2ml9DevFileTh20INVALID_FILE_CHANNELE; also in torna and xc1de.
  static void normalizeDvdFileName(mm::mtl::FixStr<256> &fileName, const char *path);
  static void makeMediaFileName(mm::mtl::FixStr<256> &fileName, const char *directory, const char *path);
  static FileHandleTh *checkValidFile(const char *path, IWorkEvent *event);
  static const char *getDvdRoot();
  static MEDIA getMediaType(const char *path);
  static bool isInitialized();
  static bool writeFileBlock(const char *path, const void *data, u32 size, int priority);
  static FileHandleTh *writeFile(const char *path, IWorkEvent *event, const void *data, int size, int priority);
  static void flushSave();
  static FileHandleTh *rfOpen(const DevFileParamTh &param);
  static bool rfRead(FileHandleTh *handle, const DevFileParamTh &param);
  static bool rfIsBusy(FileHandleTh *handle);
  static bool rfClose(FileHandleTh *handle);
  static FileHandleTh *readFile(const DevFileParamTh &param);
  static void *readFileBlock(const DevFileParamTh &param, int *size, mm::VAL64 *fileSize);
  static void cancel(FileHandleTh *handle, bool isForce);
  static bool isValidHandle(FileHandleTh *handle);
  static bool isLoading(FileHandleTh *handle);
  static bool rfIsBusy();
  static void registAccessor(MEDIA media, DevFileAccessor *accessor);
  static bool isBusy();
  static void rfCancel(FileHandleTh *handle);
  static bool getFilesBlock(char *&files, int &num, mtl::ALLOC_HANDLE handle, const char *path, const char *extension);
  static bool deleteFileBlock(const char *path);
  static void removeAccessor(MEDIA media);
  static void registArchiveAccessor(MEDIA media, DevFileAccessor *accessor);
  static void removeArchiveAccessor(MEDIA media);
  static bool initialize();
  static bool finalize();
  static void initializeEnv(const char *path);
  static void initializePath(const char *path, bool flag);
  static void addMediaPath(MEDIA media, const char *path, int priority);
  static bool removeFileJob(DevFileJob *job);
  static bool getReadingInfo(mm::mtl::FixStr<256> &name, f32 &ratio);
  static bool getWritingInfo(mm::mtl::FixStr<256> &name, f32 &ratio);
  static void enableLapTimeForDebug(bool enable);
  static bool isLapTimeForDebug();
  static bool entryCb(IWorkEvent *event);
  static bool removeCb(IWorkEvent *event);
  static void addEventListener(IDevFileEvent *listener);
  static void removeEventListener(IDevFileEvent *listener);
  static bool isSuspend();
  static bool setSuspend(bool suspend);
  static bool isNowSaving();
  static void setNowSaving(bool isSaving);
  static int getFileSize(const char *path, mm::VAL64 *size);
  static bool checkValidFileBlock(const char *path);
  static void sendCommand(const char *command, const char *argument);
  bool wkStandbyLogout() override;
  bool wkStandbyLogin() override;
  void wkTail() override;
  void wkUpdate() override;
  bool icbError(CERR_STRUCT *error) override;
  void icbDecide(CERR_STRUCT *error, ERR_DECIDE decide) override;

  mm::mtl::UniquePtr<Impl> unknown1c0; // Inferred role: implementation; original member name unknown.
  u8 _1c8;
  bool unknown1c9; // Inferred role: now saving; original member name unknown.
};

static_assert(offsetof(DevFileTh::Impl, unknown02d20) == 0x2d20, "");
static_assert(offsetof(DevFileTh::Impl, unknown05a40) == 0x5a40, "");
static_assert(offsetof(DevFileTh::Impl, unknown588b0) == 0x588b0, "");
static_assert(offsetof(DevFileTh::Impl, unknown588f0) == 0x588f0, "");
static_assert(offsetof(DevFileTh::Impl, m_initialized) == 0x58934, "");
static_assert(offsetof(DevFileTh::Impl, unknown5a348) == 0x5a348, "");
static_assert(offsetof(DevFileTh::Impl, unknown5a350) == 0x5a350, "");
static_assert(offsetof(DevFileTh::Impl, unknown5a378) == 0x5a378, "");
static_assert(offsetof(DevFileTh, unknown1c0) == 0x1c0, "");
static_assert(offsetof(DevFileTh, unknown1c9) == 0x1c9, "");

} // namespace ml
