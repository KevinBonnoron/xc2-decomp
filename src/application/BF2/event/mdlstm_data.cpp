#include "event/mdlstm_data.h"

namespace event {

void MdlstmData::clear() { unknown08.clear(); }

void MdlstmData::addReplaceInfo(const Info &info) { unknown08.push_back(info); }

} // namespace event
