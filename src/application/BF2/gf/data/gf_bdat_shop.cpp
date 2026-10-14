#include "gf/data/gf_bdat_shop.h"
#include "bdat.h"

namespace gf {
namespace _gfbsh {

enum {
  ShopListName,
  ShopListShopIcon,
  ShopListShopType,
  ShopListTableID,
  ShopListDiscount1,
  ShopListDiscount2,
  ShopListDiscount3,
  ShopListDiscount4,
  ShopListDiscount5,
  ShopNormalDefItem1,
  ShopNormalDefItem2,
  ShopNormalDefItem3,
  ShopNormalDefItem4,
  ShopNormalDefItem5,
  ShopNormalDefItem6,
  ShopNormalDefItem7,
  ShopNormalDefItem8,
  ShopNormalDefItem9,
  ShopNormalDefItem10,
  ShopNormalAddtem1,
  ShopNormalAddCondition1,
  ShopNormalPrivilegeCheck1,
  ShopNormalAddtem2,
  ShopNormalAddCondition2,
  ShopNormalPrivilegeCheck2,
  ShopNormalAddtem3,
  ShopNormalAddCondition3,
  ShopNormalPrivilegeCheck3,
  ShopNormalAddtem4,
  ShopNormalAddCondition4,
  ShopNormalPrivilegeCheck4,
  ShopNormalAddtem5,
  ShopNormalAddCondition5,
  ShopNormalPrivilegeCheck5,
  ShopNormalPrivilegeFlag,
  ShopNormalPrivilegeItem,
  ShopInnPrice,
  ShopChangeDefTaskSet1,
  ShopChangeDefTaskSet2,
  ShopChangeDefTaskSet3,
  ShopChangeDefTaskSet4,
  ShopChangeDefTaskSet5,
  ShopChangeDefTaskSet6,
  ShopChangeDefTaskSet7,
  ShopChangeDefTaskSet8,
  ShopChangeAddTaskSet1,
  ShopChangeAddCondition1,
  ShopChangeAddTaskSet2,
  ShopChangeAddCondition2,
  ShopChangeAddTaskSet3,
  ShopChangeAddCondition3,
  ShopChangeAddTaskSet4,
  ShopChangeAddCondition4,
  ShopChangeAddTaskSet5,
  ShopChangeAddCondition5,
  ShopChangeAddTaskSet6,
  ShopChangeAddCondition6,
  ShopChangeAddTaskSet7,
  ShopChangeAddCondition7,
  ShopChangeAddTaskSet8,
  ShopChangeAddCondition8,
  ShopChangeLinkQuestTask,
  ShopChangeLinkQuestTaskID,
  ShopChangeUnitText,
  ShopChangeTaskSetItem1,
  ShopChangeTaskSetNumber1,
  ShopChangeTaskSetItem2,
  ShopChangeTaskSetNumber2,
  ShopChangeTaskSetItem3,
  ShopChangeTaskSetNumber3,
  ShopChangeTaskSetItem4,
  ShopChangeTaskSetNumber4,
  ShopChangeTaskSetItem5,
  ShopChangeTaskSetNumber5,
  ShopChangeTaskHideReward,
  ShopChangeTaskReward,
  ShopChangeTaskAddFlagValue,
  MNU_EventTheatertitle,
  MNU_EventTheaterevent_id,
  MNU_EventTheatercondition,
  MNU_EventTheaterthumbnail,
  MNU_EventTheatercategory,
  MNU_EventTheaterchapter,
  MNU_EventTheatermaincast,
  MNU_EventTheaterblade_id,
  MNU_EventTheaterflag_index,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initShopListName(const CBdatWrapper &wrapper) { s_members[ShopListName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getShopListName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListName], id, 2).valueU16;
}

void initShopListShopIcon(const CBdatWrapper &wrapper) { s_members[ShopListShopIcon] = Bdat::getMember(wrapper.data, "ShopIcon"); }

u32 getShopListShopIcon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListShopIcon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListShopIcon], id, 2).valueU16;
}

void initShopListShopType(const CBdatWrapper &wrapper) { s_members[ShopListShopType] = Bdat::getMember(wrapper.data, "ShopType"); }

u32 getShopListShopType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListShopType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListShopType], id, 1).valueU8;
}

void initShopListTableID(const CBdatWrapper &wrapper) { s_members[ShopListTableID] = Bdat::getMember(wrapper.data, "TableID"); }

u32 getShopListTableID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListTableID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListTableID], id, 2).valueU16;
}

void initShopListDiscount1(const CBdatWrapper &wrapper) { s_members[ShopListDiscount1] = Bdat::getMember(wrapper.data, "Discount1"); }

u32 getShopListDiscount1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListDiscount1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListDiscount1], id, 1).valueU8;
}

void initShopListDiscount2(const CBdatWrapper &wrapper) { s_members[ShopListDiscount2] = Bdat::getMember(wrapper.data, "Discount2"); }

u32 getShopListDiscount2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListDiscount2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListDiscount2], id, 1).valueU8;
}

void initShopListDiscount3(const CBdatWrapper &wrapper) { s_members[ShopListDiscount3] = Bdat::getMember(wrapper.data, "Discount3"); }

u32 getShopListDiscount3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListDiscount3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListDiscount3], id, 1).valueU8;
}

void initShopListDiscount4(const CBdatWrapper &wrapper) { s_members[ShopListDiscount4] = Bdat::getMember(wrapper.data, "Discount4"); }

u32 getShopListDiscount4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListDiscount4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListDiscount4], id, 1).valueU8;
}

void initShopListDiscount5(const CBdatWrapper &wrapper) { s_members[ShopListDiscount5] = Bdat::getMember(wrapper.data, "Discount5"); }

u32 getShopListDiscount5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopListDiscount5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopListDiscount5], id, 1).valueU8;
}

void initShopNormalDefItem1(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem1] = Bdat::getMember(wrapper.data, "DefItem1"); }

u32 getShopNormalDefItem1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem1], id, 2).valueU16;
}

void initShopNormalDefItem2(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem2] = Bdat::getMember(wrapper.data, "DefItem2"); }

u32 getShopNormalDefItem2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem2], id, 2).valueU16;
}

void initShopNormalDefItem3(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem3] = Bdat::getMember(wrapper.data, "DefItem3"); }

u32 getShopNormalDefItem3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem3], id, 2).valueU16;
}

void initShopNormalDefItem4(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem4] = Bdat::getMember(wrapper.data, "DefItem4"); }

u32 getShopNormalDefItem4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem4], id, 2).valueU16;
}

void initShopNormalDefItem5(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem5] = Bdat::getMember(wrapper.data, "DefItem5"); }

u32 getShopNormalDefItem5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem5], id, 2).valueU16;
}

void initShopNormalDefItem6(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem6] = Bdat::getMember(wrapper.data, "DefItem6"); }

u32 getShopNormalDefItem6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem6], id, 2).valueU16;
}

void initShopNormalDefItem7(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem7] = Bdat::getMember(wrapper.data, "DefItem7"); }

u32 getShopNormalDefItem7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem7], id, 2).valueU16;
}

void initShopNormalDefItem8(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem8] = Bdat::getMember(wrapper.data, "DefItem8"); }

u32 getShopNormalDefItem8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem8], id, 2).valueU16;
}

void initShopNormalDefItem9(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem9] = Bdat::getMember(wrapper.data, "DefItem9"); }

u32 getShopNormalDefItem9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem9], id, 2).valueU16;
}

void initShopNormalDefItem10(const CBdatWrapper &wrapper) { s_members[ShopNormalDefItem10] = Bdat::getMember(wrapper.data, "DefItem10"); }

u32 getShopNormalDefItem10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalDefItem10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalDefItem10], id, 2).valueU16;
}

void initShopNormalAddtem1(const CBdatWrapper &wrapper) { s_members[ShopNormalAddtem1] = Bdat::getMember(wrapper.data, "Addtem1"); }

u32 getShopNormalAddtem1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddtem1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddtem1], id, 2).valueU16;
}

void initShopNormalAddCondition1(const CBdatWrapper &wrapper) { s_members[ShopNormalAddCondition1] = Bdat::getMember(wrapper.data, "AddCondition1"); }

u32 getShopNormalAddCondition1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddCondition1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddCondition1], id, 2).valueU16;
}

void initShopNormalPrivilegeCheck1(const CBdatWrapper &wrapper) {
  s_members[ShopNormalPrivilegeCheck1] = Bdat::getMember(wrapper.data, "PrivilegeCheck1");
}

u32 getShopNormalPrivilegeCheck1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeCheck1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeCheck1], id, 1).valueU8;
}

void initShopNormalAddtem2(const CBdatWrapper &wrapper) { s_members[ShopNormalAddtem2] = Bdat::getMember(wrapper.data, "Addtem2"); }

u32 getShopNormalAddtem2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddtem2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddtem2], id, 2).valueU16;
}

void initShopNormalAddCondition2(const CBdatWrapper &wrapper) { s_members[ShopNormalAddCondition2] = Bdat::getMember(wrapper.data, "AddCondition2"); }

u32 getShopNormalAddCondition2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddCondition2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddCondition2], id, 2).valueU16;
}

void initShopNormalPrivilegeCheck2(const CBdatWrapper &wrapper) {
  s_members[ShopNormalPrivilegeCheck2] = Bdat::getMember(wrapper.data, "PrivilegeCheck2");
}

u32 getShopNormalPrivilegeCheck2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeCheck2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeCheck2], id, 1).valueU8;
}

void initShopNormalAddtem3(const CBdatWrapper &wrapper) { s_members[ShopNormalAddtem3] = Bdat::getMember(wrapper.data, "Addtem3"); }

u32 getShopNormalAddtem3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddtem3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddtem3], id, 2).valueU16;
}

void initShopNormalAddCondition3(const CBdatWrapper &wrapper) { s_members[ShopNormalAddCondition3] = Bdat::getMember(wrapper.data, "AddCondition3"); }

u32 getShopNormalAddCondition3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddCondition3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddCondition3], id, 2).valueU16;
}

void initShopNormalPrivilegeCheck3(const CBdatWrapper &wrapper) {
  s_members[ShopNormalPrivilegeCheck3] = Bdat::getMember(wrapper.data, "PrivilegeCheck3");
}

u32 getShopNormalPrivilegeCheck3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeCheck3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeCheck3], id, 1).valueU8;
}

void initShopNormalAddtem4(const CBdatWrapper &wrapper) { s_members[ShopNormalAddtem4] = Bdat::getMember(wrapper.data, "Addtem4"); }

u32 getShopNormalAddtem4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddtem4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddtem4], id, 2).valueU16;
}

void initShopNormalAddCondition4(const CBdatWrapper &wrapper) { s_members[ShopNormalAddCondition4] = Bdat::getMember(wrapper.data, "AddCondition4"); }

u32 getShopNormalAddCondition4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddCondition4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddCondition4], id, 2).valueU16;
}

void initShopNormalPrivilegeCheck4(const CBdatWrapper &wrapper) {
  s_members[ShopNormalPrivilegeCheck4] = Bdat::getMember(wrapper.data, "PrivilegeCheck4");
}

u32 getShopNormalPrivilegeCheck4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeCheck4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeCheck4], id, 1).valueU8;
}

void initShopNormalAddtem5(const CBdatWrapper &wrapper) { s_members[ShopNormalAddtem5] = Bdat::getMember(wrapper.data, "Addtem5"); }

u32 getShopNormalAddtem5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddtem5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddtem5], id, 2).valueU16;
}

void initShopNormalAddCondition5(const CBdatWrapper &wrapper) { s_members[ShopNormalAddCondition5] = Bdat::getMember(wrapper.data, "AddCondition5"); }

u32 getShopNormalAddCondition5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalAddCondition5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalAddCondition5], id, 2).valueU16;
}

void initShopNormalPrivilegeCheck5(const CBdatWrapper &wrapper) {
  s_members[ShopNormalPrivilegeCheck5] = Bdat::getMember(wrapper.data, "PrivilegeCheck5");
}

u32 getShopNormalPrivilegeCheck5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeCheck5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeCheck5], id, 1).valueU8;
}

void initShopNormalPrivilegeFlag(const CBdatWrapper &wrapper) { s_members[ShopNormalPrivilegeFlag] = Bdat::getMember(wrapper.data, "PrivilegeFlag"); }

u32 getShopNormalPrivilegeFlag(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeFlag], id, 2).valueU16;
}

void initShopNormalPrivilegeItem(const CBdatWrapper &wrapper) { s_members[ShopNormalPrivilegeItem] = Bdat::getMember(wrapper.data, "PrivilegeItem"); }

u32 getShopNormalPrivilegeItem(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopNormalPrivilegeItem] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopNormalPrivilegeItem], id, 2).valueU16;
}

void initShopInnPrice(const CBdatWrapper &wrapper) { s_members[ShopInnPrice] = Bdat::getMember(wrapper.data, "Price"); }

u32 getShopInnPrice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopInnPrice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopInnPrice], id, 2).valueU16;
}

void initShopChangeDefTaskSet1(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet1] = Bdat::getMember(wrapper.data, "DefTaskSet1"); }

u32 getShopChangeDefTaskSet1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet1], id, 2).valueU16;
}

void initShopChangeDefTaskSet2(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet2] = Bdat::getMember(wrapper.data, "DefTaskSet2"); }

u32 getShopChangeDefTaskSet2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet2], id, 2).valueU16;
}

void initShopChangeDefTaskSet3(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet3] = Bdat::getMember(wrapper.data, "DefTaskSet3"); }

u32 getShopChangeDefTaskSet3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet3], id, 2).valueU16;
}

void initShopChangeDefTaskSet4(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet4] = Bdat::getMember(wrapper.data, "DefTaskSet4"); }

u32 getShopChangeDefTaskSet4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet4], id, 2).valueU16;
}

void initShopChangeDefTaskSet5(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet5] = Bdat::getMember(wrapper.data, "DefTaskSet5"); }

u32 getShopChangeDefTaskSet5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet5], id, 2).valueU16;
}

void initShopChangeDefTaskSet6(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet6] = Bdat::getMember(wrapper.data, "DefTaskSet6"); }

u32 getShopChangeDefTaskSet6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet6], id, 2).valueU16;
}

void initShopChangeDefTaskSet7(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet7] = Bdat::getMember(wrapper.data, "DefTaskSet7"); }

u32 getShopChangeDefTaskSet7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet7], id, 2).valueU16;
}

void initShopChangeDefTaskSet8(const CBdatWrapper &wrapper) { s_members[ShopChangeDefTaskSet8] = Bdat::getMember(wrapper.data, "DefTaskSet8"); }

u32 getShopChangeDefTaskSet8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeDefTaskSet8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeDefTaskSet8], id, 2).valueU16;
}

void initShopChangeAddTaskSet1(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet1] = Bdat::getMember(wrapper.data, "AddTaskSet1"); }

u32 getShopChangeAddTaskSet1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet1], id, 2).valueU16;
}

void initShopChangeAddCondition1(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition1] = Bdat::getMember(wrapper.data, "AddCondition1"); }

u32 getShopChangeAddCondition1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition1], id, 2).valueU16;
}

void initShopChangeAddTaskSet2(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet2] = Bdat::getMember(wrapper.data, "AddTaskSet2"); }

u32 getShopChangeAddTaskSet2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet2], id, 2).valueU16;
}

void initShopChangeAddCondition2(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition2] = Bdat::getMember(wrapper.data, "AddCondition2"); }

u32 getShopChangeAddCondition2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition2], id, 2).valueU16;
}

void initShopChangeAddTaskSet3(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet3] = Bdat::getMember(wrapper.data, "AddTaskSet3"); }

u32 getShopChangeAddTaskSet3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet3], id, 2).valueU16;
}

void initShopChangeAddCondition3(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition3] = Bdat::getMember(wrapper.data, "AddCondition3"); }

u32 getShopChangeAddCondition3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition3], id, 2).valueU16;
}

void initShopChangeAddTaskSet4(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet4] = Bdat::getMember(wrapper.data, "AddTaskSet4"); }

u32 getShopChangeAddTaskSet4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet4], id, 2).valueU16;
}

void initShopChangeAddCondition4(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition4] = Bdat::getMember(wrapper.data, "AddCondition4"); }

u32 getShopChangeAddCondition4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition4], id, 2).valueU16;
}

void initShopChangeAddTaskSet5(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet5] = Bdat::getMember(wrapper.data, "AddTaskSet5"); }

u32 getShopChangeAddTaskSet5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet5], id, 2).valueU16;
}

void initShopChangeAddCondition5(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition5] = Bdat::getMember(wrapper.data, "AddCondition5"); }

u32 getShopChangeAddCondition5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition5], id, 2).valueU16;
}

void initShopChangeAddTaskSet6(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet6] = Bdat::getMember(wrapper.data, "AddTaskSet6"); }

u32 getShopChangeAddTaskSet6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet6], id, 2).valueU16;
}

void initShopChangeAddCondition6(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition6] = Bdat::getMember(wrapper.data, "AddCondition6"); }

u32 getShopChangeAddCondition6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition6], id, 2).valueU16;
}

void initShopChangeAddTaskSet7(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet7] = Bdat::getMember(wrapper.data, "AddTaskSet7"); }

u32 getShopChangeAddTaskSet7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet7], id, 2).valueU16;
}

void initShopChangeAddCondition7(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition7] = Bdat::getMember(wrapper.data, "AddCondition7"); }

u32 getShopChangeAddCondition7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition7], id, 2).valueU16;
}

void initShopChangeAddTaskSet8(const CBdatWrapper &wrapper) { s_members[ShopChangeAddTaskSet8] = Bdat::getMember(wrapper.data, "AddTaskSet8"); }

u32 getShopChangeAddTaskSet8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddTaskSet8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddTaskSet8], id, 2).valueU16;
}

void initShopChangeAddCondition8(const CBdatWrapper &wrapper) { s_members[ShopChangeAddCondition8] = Bdat::getMember(wrapper.data, "AddCondition8"); }

u32 getShopChangeAddCondition8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeAddCondition8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeAddCondition8], id, 2).valueU16;
}

void initShopChangeLinkQuestTask(const CBdatWrapper &wrapper) { s_members[ShopChangeLinkQuestTask] = Bdat::getMember(wrapper.data, "LinkQuestTask"); }

u32 getShopChangeLinkQuestTask(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeLinkQuestTask] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeLinkQuestTask], id, 2).valueU16;
}

void initShopChangeLinkQuestTaskID(const CBdatWrapper &wrapper) {
  s_members[ShopChangeLinkQuestTaskID] = Bdat::getMember(wrapper.data, "LinkQuestTaskID");
}

u32 getShopChangeLinkQuestTaskID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeLinkQuestTaskID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeLinkQuestTaskID], id, 2).valueU16;
}

void initShopChangeUnitText(const CBdatWrapper &wrapper) { s_members[ShopChangeUnitText] = Bdat::getMember(wrapper.data, "UnitText"); }

u32 getShopChangeUnitText(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeUnitText] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeUnitText], id, 2).valueU16;
}

void initShopChangeTaskSetItem1(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetItem1] = Bdat::getMember(wrapper.data, "SetItem1"); }

u32 getShopChangeTaskSetItem1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetItem1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetItem1], id, 2).valueU16;
}

void initShopChangeTaskSetNumber1(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetNumber1] = Bdat::getMember(wrapper.data, "SetNumber1"); }

u32 getShopChangeTaskSetNumber1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetNumber1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetNumber1], id, 2).valueU16;
}

void initShopChangeTaskSetItem2(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetItem2] = Bdat::getMember(wrapper.data, "SetItem2"); }

u32 getShopChangeTaskSetItem2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetItem2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetItem2], id, 2).valueU16;
}

void initShopChangeTaskSetNumber2(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetNumber2] = Bdat::getMember(wrapper.data, "SetNumber2"); }

u32 getShopChangeTaskSetNumber2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetNumber2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetNumber2], id, 2).valueU16;
}

void initShopChangeTaskSetItem3(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetItem3] = Bdat::getMember(wrapper.data, "SetItem3"); }

u32 getShopChangeTaskSetItem3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetItem3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetItem3], id, 2).valueU16;
}

void initShopChangeTaskSetNumber3(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetNumber3] = Bdat::getMember(wrapper.data, "SetNumber3"); }

u32 getShopChangeTaskSetNumber3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetNumber3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetNumber3], id, 2).valueU16;
}

void initShopChangeTaskSetItem4(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetItem4] = Bdat::getMember(wrapper.data, "SetItem4"); }

u32 getShopChangeTaskSetItem4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetItem4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetItem4], id, 2).valueU16;
}

void initShopChangeTaskSetNumber4(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetNumber4] = Bdat::getMember(wrapper.data, "SetNumber4"); }

u32 getShopChangeTaskSetNumber4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetNumber4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetNumber4], id, 2).valueU16;
}

void initShopChangeTaskSetItem5(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetItem5] = Bdat::getMember(wrapper.data, "SetItem5"); }

u32 getShopChangeTaskSetItem5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetItem5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetItem5], id, 2).valueU16;
}

void initShopChangeTaskSetNumber5(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskSetNumber5] = Bdat::getMember(wrapper.data, "SetNumber5"); }

u32 getShopChangeTaskSetNumber5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskSetNumber5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskSetNumber5], id, 2).valueU16;
}

void initShopChangeTaskHideReward(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskHideReward] = Bdat::getMember(wrapper.data, "HideReward"); }

u32 getShopChangeTaskHideReward(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskHideReward] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskHideReward], id, 2).valueU16;
}

void initShopChangeTaskReward(const CBdatWrapper &wrapper) { s_members[ShopChangeTaskReward] = Bdat::getMember(wrapper.data, "Reward"); }

u32 getShopChangeTaskReward(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskReward] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskReward], id, 2).valueU16;
}

void initShopChangeTaskAddFlagValue(const CBdatWrapper &wrapper) {
  s_members[ShopChangeTaskAddFlagValue] = Bdat::getMember(wrapper.data, "AddFlagValue");
}

u32 getShopChangeTaskAddFlagValue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ShopChangeTaskAddFlagValue] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ShopChangeTaskAddFlagValue], id, 1).valueU8;
}

void initMNU_EventTheatertitle(const CBdatWrapper &wrapper) { s_members[MNU_EventTheatertitle] = Bdat::getMember(wrapper.data, "title"); }

u32 getMNU_EventTheatertitle(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheatertitle] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheatertitle], id, 2).valueU16;
}

void initMNU_EventTheaterevent_id(const CBdatWrapper &wrapper) { s_members[MNU_EventTheaterevent_id] = Bdat::getMember(wrapper.data, "event_id"); }

u32 getMNU_EventTheaterevent_id(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheaterevent_id] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheaterevent_id], id, 2).valueU16;
}

void initMNU_EventTheatercondition(const CBdatWrapper &wrapper) { s_members[MNU_EventTheatercondition] = Bdat::getMember(wrapper.data, "condition"); }

u32 getMNU_EventTheatercondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheatercondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheatercondition], id, 2).valueU16;
}

void initMNU_EventTheaterthumbnail(const CBdatWrapper &wrapper) { s_members[MNU_EventTheaterthumbnail] = Bdat::getMember(wrapper.data, "thumbnail"); }

u32 getMNU_EventTheaterthumbnail(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheaterthumbnail] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheaterthumbnail], id, 2).valueU16;
}

void initMNU_EventTheatercategory(const CBdatWrapper &wrapper) { s_members[MNU_EventTheatercategory] = Bdat::getMember(wrapper.data, "category"); }

u32 getMNU_EventTheatercategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheatercategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheatercategory], id, 1).valueU8;
}

void initMNU_EventTheaterchapter(const CBdatWrapper &wrapper) { s_members[MNU_EventTheaterchapter] = Bdat::getMember(wrapper.data, "chapter"); }

u32 getMNU_EventTheaterchapter(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheaterchapter] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheaterchapter], id, 1).valueU8;
}

void initMNU_EventTheatermaincast(const CBdatWrapper &wrapper) { s_members[MNU_EventTheatermaincast] = Bdat::getMember(wrapper.data, "maincast"); }

u32 getMNU_EventTheatermaincast(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheatermaincast] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheatermaincast], id, 1).valueU8;
}

void initMNU_EventTheaterblade_id(const CBdatWrapper &wrapper) { s_members[MNU_EventTheaterblade_id] = Bdat::getMember(wrapper.data, "blade_id"); }

u32 getMNU_EventTheaterblade_id(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheaterblade_id] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheaterblade_id], id, 2).valueU16;
}

void initMNU_EventTheaterflag_index(const CBdatWrapper &wrapper) {
  s_members[MNU_EventTheaterflag_index] = Bdat::getMember(wrapper.data, "flag_index");
}

u32 getMNU_EventTheaterflag_index(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MNU_EventTheaterflag_index] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MNU_EventTheaterflag_index], id, 2).valueU16;
}

} // namespace _gfbsh

u32 GfBdatShop::getShopListStart() const { return Bdat::getIdTop(mShopList->data); }

u32 GfBdatShop::getShopListName(u32 id) const { return _gfbsh::getShopListName(*mShopList, id); }

u32 GfBdatShop::getShopListShopIcon(u32 id) const { return _gfbsh::getShopListShopIcon(*mShopList, id); }

u32 GfBdatShop::getShopListShopType(u32 id) const { return _gfbsh::getShopListShopType(*mShopList, id); }

u32 GfBdatShop::getShopListTableID(u32 id) const { return _gfbsh::getShopListTableID(*mShopList, id); }

u32 GfBdatShop::getShopListDiscount1(u32 id) const { return _gfbsh::getShopListDiscount1(*mShopList, id); }

u32 GfBdatShop::getShopListDiscount2(u32 id) const { return _gfbsh::getShopListDiscount2(*mShopList, id); }

u32 GfBdatShop::getShopListDiscount3(u32 id) const { return _gfbsh::getShopListDiscount3(*mShopList, id); }

u32 GfBdatShop::getShopListDiscount4(u32 id) const { return _gfbsh::getShopListDiscount4(*mShopList, id); }

u32 GfBdatShop::getShopListDiscount5(u32 id) const { return _gfbsh::getShopListDiscount5(*mShopList, id); }

u32 GfBdatShop::getShopNormalStart() const { return Bdat::getIdTop(mShopNormal->data); }

u32 GfBdatShop::getShopNormalDefItem1(u32 id) const { return _gfbsh::getShopNormalDefItem1(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem2(u32 id) const { return _gfbsh::getShopNormalDefItem2(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem3(u32 id) const { return _gfbsh::getShopNormalDefItem3(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem4(u32 id) const { return _gfbsh::getShopNormalDefItem4(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem5(u32 id) const { return _gfbsh::getShopNormalDefItem5(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem6(u32 id) const { return _gfbsh::getShopNormalDefItem6(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem7(u32 id) const { return _gfbsh::getShopNormalDefItem7(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem8(u32 id) const { return _gfbsh::getShopNormalDefItem8(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem9(u32 id) const { return _gfbsh::getShopNormalDefItem9(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalDefItem10(u32 id) const { return _gfbsh::getShopNormalDefItem10(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalAddtem1(u32 id) const { return _gfbsh::getShopNormalAddtem1(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalAddCondition1(u32 id) const { return _gfbsh::getShopNormalAddCondition1(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeCheck1(u32 id) const { return _gfbsh::getShopNormalPrivilegeCheck1(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalAddtem2(u32 id) const { return _gfbsh::getShopNormalAddtem2(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalAddCondition2(u32 id) const { return _gfbsh::getShopNormalAddCondition2(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeCheck2(u32 id) const { return _gfbsh::getShopNormalPrivilegeCheck2(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalAddtem3(u32 id) const { return _gfbsh::getShopNormalAddtem3(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalAddCondition3(u32 id) const { return _gfbsh::getShopNormalAddCondition3(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeCheck3(u32 id) const { return _gfbsh::getShopNormalPrivilegeCheck3(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalAddtem4(u32 id) const { return _gfbsh::getShopNormalAddtem4(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalAddCondition4(u32 id) const { return _gfbsh::getShopNormalAddCondition4(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeCheck4(u32 id) const { return _gfbsh::getShopNormalPrivilegeCheck4(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalAddtem5(u32 id) const { return _gfbsh::getShopNormalAddtem5(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalAddCondition5(u32 id) const { return _gfbsh::getShopNormalAddCondition5(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeCheck5(u32 id) const { return _gfbsh::getShopNormalPrivilegeCheck5(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeFlag(u32 id) const { return _gfbsh::getShopNormalPrivilegeFlag(*mShopNormal, id); }

u32 GfBdatShop::getShopNormalPrivilegeItem(u32 id) const { return _gfbsh::getShopNormalPrivilegeItem(*mShopNormal, id); }

u32 GfBdatShop::getShopInnStart() const { return Bdat::getIdTop(mShopInn->data); }

u32 GfBdatShop::getShopInnPrice(u32 id) const { return _gfbsh::getShopInnPrice(*mShopInn, id); }

u32 GfBdatShop::getShopChangeStart() const { return Bdat::getIdTop(mShopChange->data); }

u32 GfBdatShop::getShopChangeDefTaskSet1(u32 id) const { return _gfbsh::getShopChangeDefTaskSet1(*mShopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet2(u32 id) const { return _gfbsh::getShopChangeDefTaskSet2(*mShopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet3(u32 id) const { return _gfbsh::getShopChangeDefTaskSet3(*mShopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet4(u32 id) const { return _gfbsh::getShopChangeDefTaskSet4(*mShopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet5(u32 id) const { return _gfbsh::getShopChangeDefTaskSet5(*mShopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet6(u32 id) const { return _gfbsh::getShopChangeDefTaskSet6(*mShopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet7(u32 id) const { return _gfbsh::getShopChangeDefTaskSet7(*mShopChange, id); }

u32 GfBdatShop::getShopChangeDefTaskSet8(u32 id) const { return _gfbsh::getShopChangeDefTaskSet8(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet1(u32 id) const { return _gfbsh::getShopChangeAddTaskSet1(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition1(u32 id) const { return _gfbsh::getShopChangeAddCondition1(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet2(u32 id) const { return _gfbsh::getShopChangeAddTaskSet2(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition2(u32 id) const { return _gfbsh::getShopChangeAddCondition2(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet3(u32 id) const { return _gfbsh::getShopChangeAddTaskSet3(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition3(u32 id) const { return _gfbsh::getShopChangeAddCondition3(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet4(u32 id) const { return _gfbsh::getShopChangeAddTaskSet4(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition4(u32 id) const { return _gfbsh::getShopChangeAddCondition4(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet5(u32 id) const { return _gfbsh::getShopChangeAddTaskSet5(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition5(u32 id) const { return _gfbsh::getShopChangeAddCondition5(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet6(u32 id) const { return _gfbsh::getShopChangeAddTaskSet6(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition6(u32 id) const { return _gfbsh::getShopChangeAddCondition6(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet7(u32 id) const { return _gfbsh::getShopChangeAddTaskSet7(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition7(u32 id) const { return _gfbsh::getShopChangeAddCondition7(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddTaskSet8(u32 id) const { return _gfbsh::getShopChangeAddTaskSet8(*mShopChange, id); }

u32 GfBdatShop::getShopChangeAddCondition8(u32 id) const { return _gfbsh::getShopChangeAddCondition8(*mShopChange, id); }

u32 GfBdatShop::getShopChangeLinkQuestTask(u32 id) const { return _gfbsh::getShopChangeLinkQuestTask(*mShopChange, id); }

u32 GfBdatShop::getShopChangeLinkQuestTaskID(u32 id) const { return _gfbsh::getShopChangeLinkQuestTaskID(*mShopChange, id); }

u32 GfBdatShop::getShopChangeUnitText(u32 id) const { return _gfbsh::getShopChangeUnitText(*mShopChange, id); }

u32 GfBdatShop::getShopChangeTaskStart() const { return Bdat::getIdTop(mShopChangeTask->data); }

u32 GfBdatShop::getShopChangeTaskSetItem1(u32 id) const { return _gfbsh::getShopChangeTaskSetItem1(*mShopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetNumber1(u32 id) const { return _gfbsh::getShopChangeTaskSetNumber1(*mShopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetItem2(u32 id) const { return _gfbsh::getShopChangeTaskSetItem2(*mShopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetNumber2(u32 id) const { return _gfbsh::getShopChangeTaskSetNumber2(*mShopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetItem3(u32 id) const { return _gfbsh::getShopChangeTaskSetItem3(*mShopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetNumber3(u32 id) const { return _gfbsh::getShopChangeTaskSetNumber3(*mShopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetItem4(u32 id) const { return _gfbsh::getShopChangeTaskSetItem4(*mShopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetNumber4(u32 id) const { return _gfbsh::getShopChangeTaskSetNumber4(*mShopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetItem5(u32 id) const { return _gfbsh::getShopChangeTaskSetItem5(*mShopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskSetNumber5(u32 id) const { return _gfbsh::getShopChangeTaskSetNumber5(*mShopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskHideReward(u32 id) const { return _gfbsh::getShopChangeTaskHideReward(*mShopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskReward(u32 id) const { return _gfbsh::getShopChangeTaskReward(*mShopChangeTask, id); }

u32 GfBdatShop::getShopChangeTaskAddFlagValue(u32 id) const { return _gfbsh::getShopChangeTaskAddFlagValue(*mShopChangeTask, id); }

u32 GfBdatShop::getMNU_EventTheaterStart() const { return Bdat::getIdTop(mMNU_EventTheater->data); }

u32 GfBdatShop::getMNU_EventTheatertitle(u32 id) const { return _gfbsh::getMNU_EventTheatertitle(*mMNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheaterevent_id(u32 id) const { return _gfbsh::getMNU_EventTheaterevent_id(*mMNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheatercondition(u32 id) const { return _gfbsh::getMNU_EventTheatercondition(*mMNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheaterthumbnail(u32 id) const { return _gfbsh::getMNU_EventTheaterthumbnail(*mMNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheatercategory(u32 id) const { return _gfbsh::getMNU_EventTheatercategory(*mMNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheaterchapter(u32 id) const { return _gfbsh::getMNU_EventTheaterchapter(*mMNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheatermaincast(u32 id) const { return _gfbsh::getMNU_EventTheatermaincast(*mMNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheaterblade_id(u32 id) const { return _gfbsh::getMNU_EventTheaterblade_id(*mMNU_EventTheater, id); }

u32 GfBdatShop::getMNU_EventTheaterflag_index(u32 id) const { return _gfbsh::getMNU_EventTheaterflag_index(*mMNU_EventTheater, id); }

} // namespace gf
