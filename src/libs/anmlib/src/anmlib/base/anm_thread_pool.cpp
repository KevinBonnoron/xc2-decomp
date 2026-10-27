#include "anm/anm_thread_pool.h"

#include "mm/mm_std_base.h"
#include "mm_thread/mm_thread.h"
#include "nn/os.h"
#include "nn/time_span.h"

namespace anm {

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
