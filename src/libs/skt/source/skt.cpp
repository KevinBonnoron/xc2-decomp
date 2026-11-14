#include "skt/skt.h"

#include "mm/mm_std_base.h"

namespace skt {

void errorLog(u32 errorNo, const char *message, const char *file, int line) {
  mm::MMStdBase::mmPrint("file:%s line:%d\n", file, line);
  mm::MMStdBase::mmPrint("%s errNo:%d\n", message, errorNo);
}

} // namespace skt

// The game builds util.cpp in the same unit, after errorLog: errorLog (0x7100984b68) sits inside the util block (0x71009849e8 to 0x7100984c1c), before strToInt(const char *) (0x7100984bac). The two
// util functions before it (0x71009849e8 and 0x7100984aac) sit among the CommandParam functions.
#include "util.cpp"
