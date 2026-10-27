#pragma once
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class JobQueue;

struct TreadPoolInfo {
  u32 unknown00; // Inferred role: unknown; original member name unknown.
  u32 unknown04; // Inferred role: unknown; original member name unknown.
  u32 unknown08; // Inferred role: unknown; original member name unknown.
};

static_assert(sizeof(TreadPoolInfo) == 0x0c, "");

class ThreadPool {
public:
  ThreadPool(const TreadPoolInfo &info, mm::mtl::IAllocator &allocator);
  virtual ~ThreadPool() {}
  virtual void processAllJob(JobQueue &queue);
  virtual void waitForCompletion();
  virtual void initialize(const TreadPoolInfo &info, mm::mtl::IAllocator &allocator);
  virtual void finalize();

  u8 unknown08[0x280 - 0x08]; // Inferred role: thread pool state; original member names unknown.
};

static_assert(sizeof(ThreadPool) == 0x280, "");

} // namespace anm
