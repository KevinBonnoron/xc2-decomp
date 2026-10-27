#include "gf/field/gf_field_locator.h"

#include "gmk/gmk_manager.h"

namespace gf {

int AFieldLocator::getIconBdatId() const { return m_iconBdatId; }

int AFieldLocator::getMapBdatId() const { return m_mapBdatId; }

bool GfFieldLocator::isOtherMap() const { return unknown18->getMapBdatId() != gmk::getCurrentMapBdatId(); }

} // namespace gf
