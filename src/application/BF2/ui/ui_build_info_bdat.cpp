#include "ui/ui_build_info_bdat.h"

#include "bdat.h"

namespace ui {

UIBuildInfoBdat::UIBuildInfoBdat(const char *name) : m_name(name) { Bdat::getFP(m_name); }

UIBuildInfoBdat::~UIBuildInfoBdat() { ; }

const char *UIBuildInfoBdat::getName() const { return m_name; }

u32 UIBuildInfoBdat::getObjectNum() const { return Bdat::getIdCount(Bdat::getFP(m_name)); }

} // namespace ui
