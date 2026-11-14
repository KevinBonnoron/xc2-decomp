#include "device/nx/dev_font_nx.h"

#include "ml/work_util.h" // IWYU pragma: keep

namespace ml {

bool DevFontNx::createFont() { return true; }

void DevFontNx::wkUpdate() { DevFont::wkUpdate(); }

} // namespace ml

template ml::DevFontNx *ml::WorkUtil::createWork<ml::DevFontNx>(const char *, ml::WorkObj *, bool);
