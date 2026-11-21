#include "ml/micro_thread.h"

#include <string.h>

#include "ml/dev_clock.h"
#include "ml/ml_mem.h"
#include "ml/work_cpu.h"
#include "ml/work_util.h"
#include "mm_mtl/algorithm.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

MicroThreadNx::MicroThreadNx() {
  for (int i = 0; i < 16; i++) {
    unknown2c8[i].unknown58 = mtl::MemManager::allocate(WorkCpu::getMemStack(), 0x10000, 0x1000, false, "no name", 0);
  }
}

MicroThread::MicroThread() : unknown290(0), unknown294(0), unknown2c0(nullptr) {
  for (int i = 0; i < 16; i++) {
    unknown08[i] = nullptr;
  }
}

MicroThreadNx::~MicroThreadNx() { destroyAll(); }

void MicroThread::destroyAll() {
  for (MTHREAD **it = unknown88.begin(); it != unknown88.end(); ++it) {
    releaseThread((*it)->unknown38);
  }
  unknown88.clear();
  for (unknown001 **it = unknown08; it != unknown08 + 16; ++it) {
    if (*it != nullptr) {
      releaseGroup((*it)->unknown00);
    }
  }
}

MicroThread::~MicroThread() {}

bool MicroThreadNx::isExistThread(FiberParam *param) {
  if (param == nullptr) {
    return false;
  }
  for (int i = 0; i < 16; i++) {
    if (&unknown2c8[i] == param) {
      return param->unknown60 > 0;
    }
  }
  return false;
}

void MicroThreadNx::setupThread(MTHREAD *thread, nn::os::FiberFunction function) {
  FiberParam *param = nullptr;
  for (FiberParam *it = unknown2c8; it != unknown2c8 + 16; ++it) {
    if (it->unknown60 == 0) {
      param = it;
      break;
    }
  }
  nn::os::InitializeFiber(&param->unknown00, function, nullptr, param->unknown58, 0x10000, 0);
  param->unknown60++;
  thread->unknown10 = param;
}

void MicroThreadNx::destroyThread(MTHREAD *thread) {
  FiberParam *it = unknown2c8;
  FiberParam *param = static_cast<FiberParam *>(thread->unknown10);
  for (; it != unknown2c8 + 16; ++it) {
    if (it == param) {
      if (it->unknown60 > 0 && it->unknown60-- == 1) {
        nn::os::FinalizeFiber(&it->unknown00);
        thread->unknown10 = nullptr;
      }
      return;
    }
  }
}

void MicroThreadNx::switchThreadMain(MTHREAD *thread) { nn::os::SwitchToFiber(nullptr); }

void MicroThreadNx::switchThread(MTHREAD *current, MTHREAD *next) {
  FiberParam *param = static_cast<FiberParam *>(next->unknown10);
  if (isExistThread(param) && &param->unknown00 != nn::os::GetCurrentFiber()) {
    nn::os::SwitchToFiber(&param->unknown00);
  }
}

MicroThread *MicroThread::create() {
  MicroThread *thread = get();
  if (thread == nullptr) {
    thread = new (MlMem::getProductMem()) MicroThreadNx();
  }
  return thread;
}

void MicroThread::destroy() {
  MicroThread *thread = get();
  if (thread != nullptr) {
    delete thread;
  }
}

u64 MicroThread::createHandle(MLTHG *group, u32 index) {
  u64 handle = (reinterpret_cast<u64>(group) & 0xff) << 28 | (index & 0xff) << 16 | (unknown294 & 0xffff);
  unknown294++;
  return handle;
}

MLTHG *MicroThread::createGroup() {
  CS cs(unknown298);
  long index = -1;
  for (int i = 0; i < 16; i++) {
    if (unknown08[i] == nullptr) {
      index = i;
      break;
    }
  }
  unknown001 *group = new (WorkUtil::getWorkMem()) unknown001;
  memset(group->unknown10, 0, sizeof(group->unknown10));
  group->unknown08 = 0;
  group->unknown00 = reinterpret_cast<MLTHG *>(index);
  unknown08[index] = group;
  unknown290++;
  return group->unknown00;
}

u64 MicroThread::createThread(MLTHG *group, nn::os::FiberFunction function, void *userData) {
  if (group == reinterpret_cast<MLTHG *>(-1)) {
    return -1;
  }
  CS cs(unknown298);
  unknown001 *data = unknown08[reinterpret_cast<u64>(group)];
  u32 index = -1;
  for (u64 i = 0; i < 64; i++) {
    if (data->unknown10[i] == nullptr) {
      bool isUsed = false;
      // The game accumulates the flag over the iterations (orr w10, w10, w13 at 0x7100757538) and leaves the loop on the match itself (ccmp at 0x7100757530). Forms tried, all NO MATCH:
      // `if (match) { isUsed = true; break; }` and `isUsed |= match; if (isUsed) break;` (107 instructions, no accumulated flag), `it != end && !isUsed` with `isUsed = match` or `isUsed |= match`
      // (109, the flag is folded away).
      for (MTHREAD **it = unknown88.begin(); it != unknown88.end(); ++it) {
        bool isSame = (reinterpret_cast<u64>((*it)->unknown38) >> 16 & 0xff) == i;
        isUsed |= isSame;
        if (isSame) {
          break;
        }
      }
      if (!isUsed) {
        index = i;
        break;
      }
    }
  }
  MTHREAD *thread = new (WorkUtil::getWorkMem()) MTHREAD;
  // Store order found by trying the orders (1.0.0: 0x7100757588-0x71007575a0, str w8 [x24], stp xzr, xzr [x24, #8], strh, str, stp x23, xzr [x24, #24]): with the priority first the stp comes
  // after the strh, and in offset order the stores of 0x28..0x2d become one stur over 0x26..0x2d.
  thread->unknown08 = nullptr;
  thread->unknown10 = nullptr;
  thread->unknown00 = 50;
  thread->unknown2c = false;
  thread->unknown2d = false;
  thread->unknown28 = 0;
  thread->unknown18 = userData;
  thread->unknown20 = 0;
  thread->unknown30 = nn::os::GetCurrentThread();
  thread->unknown38 = reinterpret_cast<MLTH *>(createHandle(group, index));
  setupThread(thread, function);
  unknown88.push_back(thread);
  data->unknown08++;
  return reinterpret_cast<u64>(thread->unknown38);
}

void MicroThread::releaseGroup(MLTHG *group) {
  if (group == reinterpret_cast<MLTHG *>(-1)) {
    return;
  }
  CS cs(unknown298);
  unknown001 *&slot = unknown08[reinterpret_cast<u64>(group)];
  unknown001 *data = slot;
  for (int i = 0; i < 64; i++) {
    if (data->unknown10[i] != nullptr) {
      releaseThread(data->unknown10[i]->unknown38);
    }
  }
  if (slot != nullptr) {
    delete slot;
    slot = nullptr;
  }
  unknown290--;
}

void MicroThread::releaseThread(MLTH *handle) {
  if (handle == reinterpret_cast<MLTH *>(-1)) {
    return;
  }
  CS cs(unknown298);
  u64 value = reinterpret_cast<u64>(handle);
  u32 groupIndex = value >> 28 & 0xf;
  u32 threadIndex = value >> 16 & 0xff;
  unknown001 *group = unknown08[groupIndex];
  MTHREAD *&slot = group->unknown10[threadIndex];
  MTHREAD *thread = slot;
  if (thread == nullptr) {
    for (MTHREAD **it = unknown88.begin(); it != unknown88.end(); ++it) {
      MTHREAD *created = *it;
      if (created->unknown38 == handle) {
        unknown88.erase(it);
        if (created != nullptr) {
          destroyThread(created);
          delete created;
          group->unknown08--;
        }
        return;
      }
    }
  } else if (thread->unknown38 == handle) {
    destroyThread(thread);
    if (slot != nullptr) {
      delete slot;
      slot = nullptr;
    }
    group->unknown210.erase(mm::mtl::find(group->unknown210.begin(), group->unknown210.end(), thread));
    group->unknown08--;
  }
}

void MicroThread::sleep(unsigned int frame, bool isWait) {
  if (frame != 0) {
    DevClock::getClockNow(unknown2c0->unknown670->unknown20);
  } else {
    unknown2c0->unknown670->unknown20 = 0;
  }
  unknown2c0->unknown670->unknown28 = frame;
  unknown2c0->unknown670->unknown2d = isWait;
  mm::mtl::FixedList<MTHREAD *, 64>::iterator it = mm::mtl::find(unknown2c0->unknown210.begin(), unknown2c0->unknown210.end(), unknown2c0->unknown670);
  for (++it; it != unknown2c0->unknown210.end(); ++it) {
    MTHREAD *thread = *it;
    if (thread->unknown28 != 0) {
      if (thread->unknown2d) {
        continue;
      }
      f32 time;
      DevClock::getTimeNow(time, thread->unknown20);
      if (time < thread->unknown28 * 0.001f) {
        continue;
      }
    }
    MTHREAD *current = unknown2c0->unknown670;
    unknown2c0->unknown670 = thread;
    switchThread(current, thread);
    return;
  }
  MTHREAD *current = unknown2c0->unknown670;
  unknown2c0->unknown670 = nullptr;
  switchThreadMain(current);
}

void MicroThread::update(MLTHG *group) {
  if (group == reinterpret_cast<MLTHG *>(-1)) {
    return;
  }
  CriticalSection::enter(unknown298);
  unknown001 *data = unknown08[reinterpret_cast<u64>(group)];
  unknown2c0 = data;
  for (mm::mtl::FixedList<MTHREAD *, 64>::iterator it = data->unknown210.begin(); it != data->unknown210.end();) {
    mm::mtl::FixedList<MTHREAD *, 64>::iterator next = it;
    ++next;
    MTHREAD *thread = *it;
    if (thread->unknown2c) {
      releaseThread(thread->unknown38);
    }
    it = next;
  }
  if (data->unknown08 == 0) {
    unknown2c0 = nullptr;
    CriticalSection::leave(unknown298);
    return;
  }
  data->unknown670 = nullptr;
  for (mm::mtl::FixedList<MTHREAD *, 64>::iterator it = data->unknown210.begin(); it != data->unknown210.end(); ++it) {
    MTHREAD *thread = *it;
    if (thread->unknown28 != 0) {
      if (thread->unknown2d) {
        continue;
      }
      f32 time;
      DevClock::getTimeNow(time, thread->unknown20);
      if (time < thread->unknown28 * 0.001f) {
        continue;
      }
    }
    thread->unknown28 = 0;
    data->unknown670 = thread;
    break;
  }
  CriticalSection::leave(unknown298);
  if (data->unknown670 != nullptr) {
    switchThread(nullptr, data->unknown670);
  }
  for (mm::mtl::FixedList<MTHREAD *, 64>::iterator it = data->unknown210.begin(); it != data->unknown210.end(); ++it) {
    MTHREAD *thread = *it;
    if (thread->unknown2d && thread->unknown28 != 0) {
      thread->unknown28--;
    }
  }
  unknown2c0 = nullptr;
}

void MicroThread::tail() {
  if (unknown88.size() == 0) {
    return;
  }
  for (MTHREAD **it = unknown88.begin(); it != unknown88.end(); ++it) {
    MTHREAD *thread = *it;
    u64 value = reinterpret_cast<u64>(thread->unknown38);
    unknown001 *group = unknown08[value >> 28 & 0xf];
    group->unknown10[value >> 16 & 0xff] = thread;
    group->unknown210.push_back(thread);
  }
  unknown88.clear();
}

void *MicroThread::getCurrentUserData() { return unknown2c0->unknown670->unknown18; }

u64 MicroThread::getCurrentThreadID() {
  MicroThread *thread = get();
  if (thread == nullptr) {
    return 0;
  }
  unknown001 *context = thread->unknown2c0;
  if (context == nullptr) {
    return 0;
  }
  MTHREAD *current = context->unknown670;
  if (current == nullptr) {
    return 0;
  }
  return reinterpret_cast<u64>(current->unknown30);
}

void MicroThread::exit() {
  unknown2c0->unknown670->unknown2c = true;
  sleep(0, false);
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::MicroThread>::~PtrSingleton();
