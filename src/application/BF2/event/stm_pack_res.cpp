#include "event/stm_pack_res.h"

namespace event {

StmPackRes::StmPackRes()
    : unknown00(0), unknown04(0), unknown08(2), unknown10(nullptr), unknown18(0), unknown20(0), unknown28(0), unknown30(0), unknown38(0), unknown40(0), unknown48(0), unknown50(0) {}

StmPackRes::StmPackRes(void *buffer, size_t size, size_t dataOfs, size_t firstFile, size_t lastFile, size_t firstPage, size_t lastPage, int prio, int cut, size_t stream)
    : unknown00(0), unknown08(2), unknown10(buffer), unknown18(size), unknown20(dataOfs), unknown28(firstFile), unknown30(lastFile), unknown38(firstPage), unknown40(lastPage), unknown48(prio),
      unknown4c(cut), unknown50(stream) {
  unknown04 = FLAG_UNKNOWN_0;
}

bool StmPackRes::isLoading() const { return (unknown04 & FLAG_UNKNOWN_0) != 0; }

void StmPackRes::loadCompleate() { unknown04 &= ~FLAG_UNKNOWN_0; }

void *StmPackRes::getFileAdr(size_t dataOfs) const { return reinterpret_cast<void *>((dataOfs - unknown20) + reinterpret_cast<size_t>(unknown10)); }

} // namespace event
