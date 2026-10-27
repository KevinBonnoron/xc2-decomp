#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_com_property_pc.h"

namespace gf {
namespace pc {

void GfPropertyField::resetStatus(const GfComPropertyPc &property) {
  if (property.unknown111_2) {
    unknown10_3 = true;
  }
  unknown12_1 = true;
}

void GfPropertyField::flushOwner(GfComPropertyPc &property) {
  if (unknown11_3) {
    property.unknown110_4 = true;
    property.unknown110_7 = true;
  }
}

void GfPropertyField::cleanup(const GfComPropertyPc &property) {}

} // namespace pc
} // namespace gf
