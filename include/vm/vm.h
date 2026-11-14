#pragma once

extern "C" {

int vmUnlink(void *vm);
int vmLink(void *vm);
void vmStart(void *vm);
int vmThreadIsFinish(void *vm);
void vmThreadSleepAll(void *vm);
void vmThreadWakeupAll(void *vm);
void vmMlAssert(const char *message, const char *file, int line);
void vmMlOutputMsg(int level, const char *format, ...);
void splitFixed(float value, int *sign, int *integer, int *fraction);
const char *getScTypeName(int type);
}
