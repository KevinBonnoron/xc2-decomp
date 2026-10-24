#include "idcoli/idcoli.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace idcoli {

IDColiParmsBone::IDColiParmsBone(IDColiObj *object) : m_data(static_cast<IDColiObjData *>(object)) {}

int IDColiParmsBone::getBoneMax() const { return m_data->unknown1f8; }

const char *IDColiParmsBone::getBoneName(int index) const { return m_data->getBoneName(index); }

int IDColiParmsBone::getBoneIdx(const char *name) { return m_data->getBoneIdx(name); }

void IDColiParmsBone::setBoneMatrix(int index, const mm::Mat44 &matrix) { m_data->setBoneMatrix(index, matrix); }

const mm::Mat44 &IDColiParmsBone::getBoneMatrix(int index) const { return m_data->getBoneMatrix(index); }

mm::Mat44 *IDColiParmsBone::getBoneMatrixTbl() { return m_data->unknown1f0; }

} // namespace idcoli
