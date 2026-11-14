#pragma once
#include <stddef.h>

namespace ml {
class CriticalSection;
} // namespace ml

namespace _mlmisc {

ml::CriticalSection &getCriticalSection();

} // namespace _mlmisc

extern "C" {

bool mlSaveLog();
bool mlSaveSnap();
void mlSetLogTitleDir();
bool mlGetEnvVariable(size_t *length, char *buffer, size_t bufferSize);
bool mlGetCurrentPath(char *path);
bool mlGetModulePath(char *path);
}
