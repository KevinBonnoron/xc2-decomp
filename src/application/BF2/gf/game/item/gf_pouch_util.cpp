#include "gf/game/item/gf_pouch_util.h"

#include "gf/data/gf_item_id.h"
#include "gf/game/item/gf_item_box.h"

namespace gf {

bool GfPouchUtil::isExistOpenItem() { return GfItemBox::get()->countItem(ITEM_UNKNOWN_62D9) != 0; }

} // namespace gf
