#pragma once
#include <string.h>

#include "anm/anm_job.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/queue.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

struct JobEntry : public Job {
  JobEntry() : Job("JobEntry", 0x100, 0) {}
  explicit JobEntry(const Job &job) : Job("JobEntry", 0x100, 0) { memcpy(this, &job, job.unknown08); }

  u8 unknown10[0x100 - 0x10]; // Inferred role: job payload; original member name unknown.
};

static_assert(sizeof(JobEntry) == 0x100, "");

class JobQueue : public mm::mtl::Queue<JobEntry> {
public:
  static const u32 FUNC_MAX = 32;

  explicit JobQueue(mm::mtl::IAllocator *allocator) : Queue(allocator, 128) { memset(m_funcs, 0, sizeof(m_funcs)); }

  // __LINE__ must be 37 as in the original header: it is the line argument of the assert.
#line 36
  void registerJobExecuter(u32 index, void (*function)(Job &)) {
    MM_ASSERT(m_funcs[index] == nullptr);
    m_funcs[index] = function;
  }

  // Inferred helper: runs the function registered for a job; original name unknown.
#line 43
  void unknown002(Job &job) {
    MM_ASSERT(m_funcs[job.m_funcIndex]);
    m_funcs[job.m_funcIndex](job);
  }

  // Inferred helper: queues a copy of a job; original name unknown.
  void unknown001(const Job &job) { push_back(JobEntry(job)); }

  void (*m_funcs[FUNC_MAX])(Job &);
};

} // namespace anm
