#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mm_thread/mm_thread_csection.h"
#include "mm_thread/mm_thread_util.h"
#include "types.h"

namespace ml {
class Thread;
} // namespace ml

namespace gf {

struct GfSetupParam;

class GfFileSizePool : public mm::mtl::PtrSingleton<GfFileSizePool> {
public:
  // Inferred role: file size request, kept in the pool and in the request queues; original type name unknown.
  struct unknown001 {
    u64 unknown00;                   // Inferred role: handle; original member name unknown.
    mm::mtl::FixStr<128> *unknown08; // Inferred role: file name; original member name unknown.
    s32 unknown10;                   // Inferred role: file size, -2 until the job has run; original member name unknown.
    u32 unknown14;                   // Inferred role: index in the pool; original member name unknown.
  };

  GfFileSizePool(const GfSetupParam &param);
  ~GfFileSizePool();
  static void build(const GfSetupParam &param);
  static void destroy();
  void initialize(const GfSetupParam &param);
  void finalize();
  void createThread();
  void destroyThread();
  u32 getFileSizeByHandle(u64 handle) const;
  static u32 getPoolIndex(u64 handle);
  bool isRequestByHandle(u64 handle) const;
  static u64 getHandleFromFileName(u32 index, const char *path);
  static u64 getHash(const char *path);
  static u64 getHashFromHandle(u64 handle);
  u64 requestFileSize(const char *path);
  void recalcFileSizeCache(u64 handle, const char *path);
  bool getFileSize(int &size, u64 handle) const;
  bool getFileSize(int &size, const char *path) const;
  static u32 fnThread(void *argument);
  void wakeupThread();
  void update();
  void copyPoolFromRequest();
  void execFileSizeJob(u32 count);

  bool unknown08;                                    // Inferred role: initialized; original member name unknown.
  bool unknown09;                                    // Inferred role: finalizing; original member name unknown.
  mm::mtl::FixedVector<unknown001, 4096> unknown10;  // Inferred role: pool; original member name unknown.
  mm::mtl::FixedQueue<unknown001, 512> unknown18018; // Inferred role: pool entries to finish; original member name unknown.
  mm::mtl::FixedQueue<unknown001, 512> unknown1b028; // Inferred role: request queue; original member name unknown.
  ml::Thread *unknown1e038;                          // Inferred role: thread; original member name unknown.
  mm::threading::EventWait unknown1e040;             // Inferred role: thread wake event; original member name unknown.
  mm::threading::CriticalSection unknown1e0a0;       // Inferred role: queue lock; original member name unknown.
  bool unknown1e0c8;                                 // Inferred role: thread waiting; original member name unknown.
  f32 unknown1e0cc;                                  // Inferred role: time spent in the jobs; original member name unknown.
};

static_assert(offsetof(GfFileSizePool, unknown10) == 0x10, "");
static_assert(offsetof(GfFileSizePool, unknown18018) == 0x18018, "");
static_assert(offsetof(GfFileSizePool, unknown1b028) == 0x1b028, "");
static_assert(offsetof(GfFileSizePool, unknown1e038) == 0x1e038, "");
static_assert(offsetof(GfFileSizePool, unknown1e040) == 0x1e040, "");
static_assert(offsetof(GfFileSizePool, unknown1e0a0) == 0x1e0a0, "");
static_assert(offsetof(GfFileSizePool, unknown1e0c8) == 0x1e0c8, "");
static_assert(sizeof(GfFileSizePool) == 0x1e0d0, "");

} // namespace gf
