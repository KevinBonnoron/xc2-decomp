#pragma once
#include <stddef.h>

#include "layer/layer_act_base.h"
#include "layer/layer_base.h"

namespace layer {

// Evidence: the vtable holds LayerActBase::updatePartsAction and the constructor clears unknown250 as LayerActBase does.
class LayerObjList : public LayerActBase {
public:
  LayerObjList();
  void workListRelease();
  void addListInfo();

  LayerBase::unknown001 unknown258;    // Inferred role: active list objects; original member name unknown.
  LayerBase::unknown001 unknown270[2]; // Inferred role: list objects to add per buffer; original member name unknown.
};

static_assert(offsetof(LayerObjList, unknown258) == 0x258, "");
static_assert(offsetof(LayerObjList, unknown270) == 0x270, "");
static_assert(sizeof(LayerObjList) == 0x2a0, "");

} // namespace layer
