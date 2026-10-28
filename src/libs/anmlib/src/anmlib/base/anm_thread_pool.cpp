#include "anm/anm_thread_pool.h"

#include "anm/anm_job_queue.h"
#include "mm/mm_std_base.h"
#include "mm_thread/mm_thread.h"
#include "nn/os.h"
#include "nn/time_span.h"

namespace anm {

// Inferred argument of a worker thread: the pool and the index of the worker; original name unknown.
struct unknown001 {
  ThreadPool *unknown00;
  u32 unknown08;
};

ThreadPool::ThreadPool(const TreadPoolInfo &info, mm::mtl::IAllocator &allocator)
    : unknown20{{false, true}, {false, true}, {false, true}}, unknown144(0), unknown148{{false, true}, {false, true}, {false, true}} {
  unknown268 = info;
  m_pJobQueue = nullptr;
  unknown08[1] = nullptr;
  unknown08[2] = nullptr;
  unknown08[0] = nullptr;
  unknown148[0].setSignal(false);
  unknown148[1].setSignal(false);
  unknown148[2].setSignal(false);
  unknown20[0].setSignal(false);
  unknown20[1].setSignal(false);
  unknown20[2].setSignal(false);
  initialize(info, allocator);
}

ThreadPool::~ThreadPool() { finalize(); }

void ThreadPool::initialize(const TreadPoolInfo &info, mm::mtl::IAllocator &allocator) {
  unknown001 arguments[3] = {{this, 0}, {this, 1}, {this, 2}};
  if ((info.unknown00 & 1) != 0) {
    unknown08[0] = mm::threading::Thread::create(&allocator, "WorkerThread0", threadFunc, &arguments[0], 0x40000, mm::threading::CPUID_CORE_0, info.unknown04);
    unknown08[0]->resume();
  }
  if ((info.unknown00 & 2) != 0) {
    unknown08[1] = mm::threading::Thread::create(&allocator, "WorkerThread1", threadFunc, &arguments[1], 0x40000, mm::threading::CPUID_CORE_1, info.unknown04);
    unknown08[1]->resume();
  }
  if ((info.unknown00 & 4) != 0) {
    unknown08[2] = mm::threading::Thread::create(&allocator, "WorkerThread2", threadFunc, &arguments[2], 0x40000, mm::threading::CPUID_CORE_2, info.unknown04);
    unknown08[2]->resume();
  }
  if (unknown08[0] != nullptr) {
    unknown148[0].waitSignal(0);
  }
  if (unknown08[1] != nullptr) {
    unknown148[1].waitSignal(0);
  }
  if (unknown08[2] != nullptr) {
    unknown148[2].waitSignal(0);
  }
  unknown144 = 1;
}

u32 ThreadPool::threadFunc(void *argument) {
  unknown001 *arguments = static_cast<unknown001 *>(argument);
  ThreadPool *pool = arguments->unknown00;
  u32 index = arguments->unknown08;
  JobEntry jobs[512];
  pool->unknown148[index].setSignal(true);
  while (pool->unknown144 == 0) {
    nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(1));
  }
  pool->unknown20[index].waitSignal(0);
  if (pool->unknown144 != 2) {
    do {
      JobQueue *queue = pool->m_pJobQueue;
      if (queue != nullptr) {
        while (queue->size() != 0) {
          pool->unknown140.lock(0.0f);
          u32 size = queue->size();
          u32 limit = pool->unknown268.unknown08;
          u32 count = size < limit ? size : limit;
          for (u32 i = 0; i < count; i++) {
            if (!queue->empty()) {
              jobs[i] = queue->front();
              queue->pop_front();
            }
          }
          pool->unknown140.unlock();
          for (u32 i = 0; i < count; i++) {
            queue->unknown002(jobs[i]);
          }
        }
      }
      pool->unknown148[index].setSignal(true);
      pool->unknown20[index].waitSignal(0);
    } while (pool->unknown144 != 2);
  }
  return 0;
}

void ThreadPool::processAllJob(JobQueue &queue) {
  MM_ASSERT(m_pJobQueue == nullptr);
  m_pJobQueue = &queue;
  unknown20[1].setSignal(true);
  unknown20[2].setSignal(true);
  unknown20[0].setSignal(true);
}

void ThreadPool::waitForCompletion() {
  if (m_pJobQueue != nullptr) {
    if (unknown08[0] != nullptr) {
      unknown148[0].waitSignal(0);
    }
    if (unknown08[1] != nullptr) {
      unknown148[1].waitSignal(0);
    }
    if (unknown08[2] != nullptr) {
      unknown148[2].waitSignal(0);
    }
    m_pJobQueue = nullptr;
  }
}

void ThreadPool::finalize() {
  unknown144 = 2;
  unknown20[0].setSignal(true);
  unknown20[1].setSignal(true);
  unknown20[2].setSignal(true);
  for (u32 i = 0; i < 3; i++) {
    if (unknown08[i] != nullptr) {
      while (!unknown08[i]->isTerminated()) {
        nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(1));
      }
      if (unknown08[i] != nullptr) {
        unknown08[i]->release();
        unknown08[i] = nullptr;
      }
    }
  }
}

} // namespace anm
