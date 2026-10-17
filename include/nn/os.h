#pragma once
#include <stddef.h>

#include "nn/result.h"
#include "nn/time_span.h"
#include "types.h"

namespace nn {
namespace os {

struct alignas(8) MutexType {
  u8 _00[0x20];
};

struct alignas(8) EventType {
  u8 _00[0x28];
};

struct alignas(8) ReaderWriterLockType {
  u8 _00[0x20];
};

struct alignas(8) ThreadType {
  u8 _00[0x1c0];
};

typedef void (*ThreadFunction)(void *argument);

const int HighestThreadPriority = 0;
const int DefaultThreadPriority = 16;
const int LowestThreadPriority = 31;

enum EventClearMode {
  EventClearMode_ManualClear,
  EventClearMode_AutoClear,
};

class Tick {
public:
  Tick() {}
  explicit Tick(s64 value) : value(value) {}
  s64 GetInt64Value() const { return value; }

private:
  s64 value;
};

void InitializeMutex(MutexType *mutex, bool recursive, int lockLevel);
void FinalizeMutex(MutexType *mutex);
void LockMutex(MutexType *mutex);
bool TryLockMutex(MutexType *mutex);
void UnlockMutex(MutexType *mutex);
bool IsMutexLockedByCurrentThread(const MutexType *mutex);

void InitializeReaderWriterLock(ReaderWriterLockType *lock);
void FinalizeReaderWriterLock(ReaderWriterLockType *lock);
void AcquireReadLock(ReaderWriterLockType *lock);
void ReleaseReadLock(ReaderWriterLockType *lock);
void AcquireWriteLock(ReaderWriterLockType *lock);
void ReleaseWriteLock(ReaderWriterLockType *lock);
bool IsReadLockHeld(const ReaderWriterLockType *lock);
bool IsWriteLockHeldByCurrentThread(const ReaderWriterLockType *lock);

void InitializeEvent(EventType *event, bool initiallySignaled, EventClearMode clearMode);
void FinalizeEvent(EventType *event);
void SignalEvent(EventType *event);
void WaitEvent(EventType *event);
bool TimedWaitEvent(EventType *event, TimeSpan timeout);
void ClearEvent(EventType *event);

Tick GetSystemTick();
TimeSpan ConvertToTimeSpan(Tick tick);
Tick ConvertToTick(TimeSpan span);

Result CreateThread(ThreadType *thread, ThreadFunction function, void *argument, void *stack, size_t stackSize, int priority, int idealCore);
Result CreateThread(ThreadType *thread, ThreadFunction function, void *argument, void *stack, size_t stackSize, int priority);
void DestroyThread(ThreadType *thread);
void StartThread(ThreadType *thread);
void SetThreadName(ThreadType *thread, const char *name);
void YieldThread();
ThreadType *GetCurrentThread();
int GetCurrentCoreNumber();
const char *GetThreadNamePointer(const ThreadType *thread);
void SetThreadCoreMask(ThreadType *thread, int idealCore, u64 affinityMask);
u64 GetThreadAvailableCoreMask();

void FlushDataCache(const void *address, size_t size);

} // namespace os
} // namespace nn
