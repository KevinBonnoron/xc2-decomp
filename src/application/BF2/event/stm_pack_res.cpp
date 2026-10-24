#include "event/stm_pack_res.h"

namespace event {

StmPackRes::StmPackRes()
    : unknown00(0), unknown04(0), unknown08(2), unknown10(nullptr), unknown18(0), unknown20(0), unknown28(0), unknown30(0), unknown38(0), unknown40(0), unknown48(0), unknown50(0) {}

bool StmPackRes::isLoading() const { return (unknown04 & FLAG_LOADING) != 0; }

void StmPackRes::loadCompleate() { unknown04 &= ~FLAG_LOADING; }

void *StmPackRes::getFileAdr(size_t dataOfs) const { return reinterpret_cast<void *>((dataOfs - unknown20) + reinterpret_cast<size_t>(unknown10)); }

} // namespace event
