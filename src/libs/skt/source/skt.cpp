#include "skt/skt.h"

#include "mm/mm_std_base.h"

namespace skt {

void errorLog(u32 errorNo, const char *message, const char *file, int line) {
  mm::MMStdBase::mmPrint("file:%s line:%d\n", file, line);
  mm::MMStdBase::mmPrint("%s errNo:%d\n", message, errorNo);
}

} // namespace skt
