#pragma once

extern "C" {

void vmUnlink(void *vm);
int vmLink(void *vm);
void vmStart(void *vm);
int vmThreadIsFinish(void *vm);
void vmThreadSleepAll(void *vm);
void vmThreadWakeupAll(void *vm);
}
