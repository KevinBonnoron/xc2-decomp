#include "gf/menu/object/gf_menu_obj_shop.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_item_handle.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/gf_game_util_shop.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/game/sequential_play/gf_sequential_play.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_exc_task_adapter.h"
#include "gf/menu/adapter/gf_menu_game_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/adapter/gf_menu_shop_adapter.h"
#include "gf/menu/adapter/gf_menu_zone_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_bl_weapon2.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_sort.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gf/util/gf_item_util.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x77;
// Inferred role: active adapter category; original name unknown.
constexpr u32 unknown002 = 1;
// Inferred role: common window shown for orb error 1; original name unknown.
constexpr u16 unknown003 = 0xaf;
// Inferred role: common window shown for orb error 2; original name unknown.
constexpr u16 unknown004 = 0xb0;
// Inferred role: pause bits requested while sleeping at the inn; original name unknown.
constexpr u32 unknown005 = 0x59;
// Inferred role: achievement statistics id counting inn stays; original name unknown.
constexpr u32 unknown006 = 0x23;
// Inferred role: common window asking to create the selected orb; original name unknown.
constexpr u16 unknown007 = 0xa3;
GfMenuObjShop::GfMenuObjShop(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown34(0), unknown38(0), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(false), unknown59(false), unknown60(), unknownc0(0),
      unknownc8(nullptr), unknownd0(0), unknownd8(nullptr), unknowne0(nullptr), unknowne8(nullptr), unknownf8(), unknown130(), unknown148(0), unknown14c(0), unknown168(), unknown238(),
      unknown248(this), unknown4dc(false), unknown4f0(nullptr), unknown504(-1), unknown548(QuestID(), 0, 0, TASK_STATE_UNKNOWN_0), unknown568(0), unknown570(nullptr), unknown578(nullptr) {
  unknown130.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
  for (u32 i = 0; i < 8; i++) {
    unknown508[i] = nullptr;
  }
  unknown578 = GfMenuCallContext::create();
}

GfMenuObjShop::~GfMenuObjShop() {
  unknown238 = nullptr;
  for (u32 i = 0; i < 26; i++) {
    unknown168[i] = nullptr;
  }
  mm::mtl::safeRelease(unknown150);
  mm::mtl::safeRelease(unknown158);
  mm::mtl::safeRelease(unknown160);
  mm::mtl::safeRelease(unknownf0);
  mm::mtl::safeRelease(unknowne8);
  mm::mtl::safeRelease(unknowne0);
  mm::mtl::safeRelease(unknownd8);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknownc8);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown4e8);
  mm::mtl::safeRelease(unknown4f0);
  for (u32 i = 0; i < 8; i++) {
    mm::mtl::safeRelease(unknown508[i]);
  }
  mm::mtl::safeRelease(unknown570);
  mm::mtl::safeRelease(unknown578);
}

void GfMenuObjShop::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    mm::mtl::FixStr<32> name;
    attachExternalCall(unknown001, main.unknown10);
    main.setSuspend(true);
// __LINE__ must be 254 as in the original file: it is the line argument of operator new.
#line 254
    MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
    if (mainListener != nullptr) {
      mainListener->release();
    }
// __LINE__ must be 257 as in the original file: it is the line argument of operator new.
#line 257
    SubListener *storeSubListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SubListener(this);
    storeSubListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_store"), storeSubListener);
    if (storeSubListener != nullptr) {
      storeSubListener->release();
    }
// __LINE__ must be 258 as in the original file: it is the line argument of operator new.
#line 258
    SubListener *innSubListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SubListener(this);
    innSubListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_inn"), innSubListener);
    if (innSubListener != nullptr) {
      innSubListener->release();
    }
// __LINE__ must be 259 as in the original file: it is the line argument of operator new.
#line 259
    SubListener *orbSubListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SubListener(this);
    orbSubListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_orb"), orbSubListener);
    if (orbSubListener != nullptr) {
      orbSubListener->release();
    }
// __LINE__ must be 260 as in the original file: it is the line argument of operator new.
#line 260
    SubListener *exchangeSubListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SubListener(this);
    exchangeSubListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_exchange"), exchangeSubListener);
    if (exchangeSubListener != nullptr) {
      exchangeSubListener->release();
    }
    for (u32 i = 0; i < 26; i++) {
      unknown168[i] = gf::unknown160();
    }
    unknown238 = GfMenuReferenceItem::unknown001();
    GfMenuAdapterManager::beginCategory(unknown002);
    {
      ui::UIObjectAcc common(main.unknown10, "LAY_common");
// __LINE__ must be 279 as in the original file: it is the line argument of operator new.
#line 279
      CommonListener *commonListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) CommonListener(this);
      commonListener->addRef();
      ui::UIEventManager::get()->registObjectListener(common.unknown10, commonListener);
      if (commonListener != nullptr) {
        commonListener->release();
      }
      GfMenuShopAdapter::createFromReference(common.searchChild("TXT_shop_name"), 0, unknown168[0], false);
      GfMenuShopAdapter::createFromReference(common.searchChild("TXT_shop_name_quest"), 0, unknown168[0], false);
      GfMenuShopAdapter::createFromReference(common.searchChild("TXT_index"), 1, unknown168[0], false);
      GfMenuShopAdapter::createFromReference(common.searchChild("IMG_index_icon"), 2, unknown168[0], false);
      GfMenuShopAdapter::createFromReference(common.searchChild("IMG_index_category"), 3, unknown168[0], false);
      GfMenuGameAdapter::create(common.searchChild("TXT_index_money"), 1, true);
      GfMenuZoneAdapter::createFromReference(common.searchChild("TXT_location_name"), 0, unknown168[1], true);
      GfMenuZoneAdapter::createFromReference(common.searchChild("IMG_location_icon"), 2, unknown168[1], true);
      GfMenuZoneAdapter::createFromReference(common.searchChild("IMG_location_lv_icon"), 3, unknown168[1], true);
    }
    {
      // Braced scope (ruling 3 of 2026-11-13): the game keeps this parameter at frame offset x29-168, the slot it later
      // reuses for the UIObjectAcc of the store layer, so its lifetime ends before that object. The game zeroes the slot
      // (stur xzr, [x29, #-168] at 0x71004cafac, before the getAllocator call) and then stores the allocator over it: the
      // `= {}` is written (P3 of 2026-11-14), without it the function has one instruction less.
      ui::UISelectObjList::CreateParam createParam = {};
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown48 = GfMenuItemList::create();
      unknowne8 = GfMenuItemList::create();
      unknownf0 = GfMenuItemList::create();
      unknown158 = GfMenuItemList::create();
      unknown160 = GfMenuItemList::create();
      unknown150 = GfMenuIDList::create();
      unknown40 = ui::UISelectObjList::create(createParam);
      unknown50 = ui::UISelectObjList::create(createParam);
      unknownd8 = ui::UISelectObjList::create(createParam);
      unknown4e8 = ui::UISelectObjList::create(createParam);
    }
    {
      ui::UIObjectAcc store(main.searchChild("LAY_store"));
      GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(store.searchChild("TXT_store_item_info_nrm"), 9, unknown48, -1, false);
      if (adapter != nullptr) {
        adapter->unknown24 = store.searchChild("LAY_store_item_info_nrm2");
      }
      adapter = GfMenuItemAdapter::createFromList(store.searchChild("TXT_sell_item_info_nrm"), 9, unknown48, -1, false);
      if (adapter != nullptr) {
        adapter->unknown24 = store.searchChild("LAY_store_sell_info_txt");
      }
      unknown50->pickupObject(store.unknown10, "LAY_store_item@%02d", 1);
      for (u32 i = 0; i < unknown50->getSize(); i++) {
        ui::UIObjectAcc item(unknown50->getObject(i));
        name.format("IMG_store_item_icon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 2, unknown48, i, false);
        name.format("TXT_store_item_name@%02d", i + 1);
        adapter = GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 0, unknown48, i, false);
        if (adapter != nullptr) {
          name.format("LAY_store_item_contents@%02d", i + 1);
          adapter->unknown24 = item.searchChild(name.c_str());
        }
        name.format("IMG_store_item_rare@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 7, unknown48, i, false);
        name.format("TXT_store_item_price@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 5, unknown48, i, true);
        name.format("TXT_store_item_num@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 3, unknown48, i, true);
        name.format("TXT_store_item_max@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 4, unknown48, i, true);
      }
      unknown50->clear();
      unknown50->pickupObject(store.unknown10, "LAY_store_sell_item@%02d", 1);
      for (u32 i = 0; i < unknown50->getSize(); i++) {
        ui::UIObjectAcc item(unknown50->getObject(i));
        name.format("IMG_sell_item_icon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 2, unknown48, i, false);
        name.format("TXT_sell_item_name@%02d", i + 1);
        adapter = GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 0, unknown48, i, false);
        if (adapter != nullptr) {
          name.format("LAY_store_sell_item_contents@%02d", i + 1);
          adapter->unknown24 = item.searchChild(name.c_str());
        }
        name.format("IMG_sell_item_rare@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 7, unknown48, i, false);
        name.format("TXT_sell_item_price@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 6, unknown48, i, true);
        name.format("TXT_sell_item_num@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 3, unknown48, i, true);
        name.format("TXT_sell_item_max@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 4, unknown48, i, true);
      }
      unknown50->clear();
      GfMenuObjUtil::createVScrollBarPlugin(main.searchChild("IMG_store_scroll_bar"), unknown48, "IMG_store_scroll_base", true);
      GfMenuObjUtil::createVScrollBarPlugin(main.searchChild("IMG_store_sell_scroll_bar"), unknown48, "IMG_store_sell_scroll_base", true);
      name.format("TXT_store_sell_getarea@%02d", 1);
      adapter = GfMenuItemAdapter::createFromList(main.searchChild(name.c_str()), 0xb, unknown48, -1, false);
      if (adapter != nullptr) {
        adapter->unknown24 = main.searchChild("LAY_store_sell_getinfo");
      }
      adapter->unknown70 = 0;
      name.format("TXT_store_sell_getarea@%02d", 2);
      adapter = GfMenuItemAdapter::createFromList(main.searchChild(name.c_str()), 0xb, unknown48, -1, false);
      adapter->unknown70 = 1;
      name.format("TXT_store_item_info_fav_eff@%02d", 1);
      adapter = GfMenuItemAdapter::createFromList(store.searchChild(name.c_str()), 0xe, unknown48, -1, false);
      if (adapter != nullptr) {
        adapter->unknown70 = 0;
      }
      name.format("TXT_sell_item_info_fav_eff@%02d", 1);
      adapter = GfMenuItemAdapter::createFromList(store.searchChild(name.c_str()), 0xe, unknown48, -1, false);
      if (adapter != nullptr) {
        adapter->unknown70 = 0;
      }
      name.format("TXT_store_item_info_fav_eff@%02d", 2);
      adapter = GfMenuItemAdapter::createFromList(store.searchChild(name.c_str()), 0xe, unknown48, -1, false);
      if (adapter != nullptr) {
        adapter->unknown70 = 1;
      }
      name.format("TXT_sell_item_info_fav_eff@%02d", 2);
      adapter = GfMenuItemAdapter::createFromList(store.searchChild(name.c_str()), 0xe, unknown48, -1, false);
      if (adapter != nullptr) {
        adapter->unknown70 = 1;
      }
      name.format("TXT_store_item_info_fav_eff@%02d", 3);
      adapter = GfMenuItemAdapter::createFromList(store.searchChild(name.c_str()), 0xe, unknown48, -1, false);
      if (adapter != nullptr) {
        adapter->unknown70 = 2;
      }
      name.format("TXT_sell_item_info_fav_eff@%02d", 3);
      adapter = GfMenuItemAdapter::createFromList(store.searchChild(name.c_str()), 0xe, unknown48, -1, false);
      if (adapter != nullptr) {
        adapter->unknown70 = 2;
      }
      GfMenuItemAdapter::createFromList(store.searchChild("TXT_store_item_info_fav_time"), 0xd, unknown48, -1, false);
      GfMenuItemAdapter::createFromList(store.searchChild("TXT_sell_item_info_fav_time"), 0xd, unknown48, -1, false);
// __LINE__ must be 507 as in the original file: it is the line argument of operator new.
#line 507
      StoreActListener *actListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) StoreActListener(this);
      actListener->addRef();
      ui::UIEventManager::get()->registObjectListener(store.searchChild("LAY_store_action"), actListener);
      if (actListener != nullptr) {
        actListener->release();
      }
// __LINE__ must be 508 as in the original file: it is the line argument of operator new.
#line 508
      StoreListListener *listListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) StoreListListener(this);
      listListener->addRef();
      ui::UIEventManager::get()->registObjectListener(store.searchChild("LAY_store_list"), listListener);
      if (listListener != nullptr) {
        listListener->release();
      }
// __LINE__ must be 509 as in the original file: it is the line argument of operator new.
#line 509
      SellListListener *sellListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SellListListener(this);
      sellListListener->addRef();
      ui::UIEventManager::get()->registObjectListener(store.searchChild("LAY_store_sell"), sellListListener);
      if (sellListListener != nullptr) {
        sellListListener->release();
      }
// __LINE__ must be 510 as in the original file: it is the line argument of operator new.
#line 510
      SellFilterListener *sellFilterListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SellFilterListener(this);
      sellFilterListener->addRef();
      ui::UIEventManager::get()->registObjectListener(store.searchChild("LAY_store_sell_filter"), sellFilterListener);
      if (sellFilterListener != nullptr) {
        sellFilterListener->release();
      }
    }
    {
      ui::UIObjectAcc inn(main.searchChild("LAY_inn"));
// __LINE__ must be 520 as in the original file: it is the line argument of operator new.
#line 520
      InnActListener *innActListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) InnActListener(this);
      innActListener->addRef();
      ui::UIEventManager::get()->registObjectListener(inn.searchChild("LAY_inn_action"), innActListener);
      if (innActListener != nullptr) {
        innActListener->release();
      }
      GfMenuReferenceAdapter::create(inn.searchChild("TXT_inn_action_money@01"), unknown168[3], true);
      GfMenuReferenceAdapter::create(inn.searchChild("TXT_inn_action_money@02"), unknown168[4], true);
      GfMenuObjUtil::createSyncPlugin(inn.searchSibiling("IMG_inn_action_cursor_base"), inn.searchSibiling("LAY_inn_action_cursor"), 0x22);
      GfMenuObjUtil::FitOption option;
      option.unknown00 = true;
      option.unknown01 = true;
      GfMenuObjUtil::createFitPlugin(inn.searchChild("IMG_inn_bg"), inn.searchChild("LAY_inn_action"), 0, 0, option);
    }
    {
      ui::UIObjectAcc orb(main.searchChild("LAY_orb"));
      unknown50->pickupObject(orb.unknown10, "LAY_orb_item@%02d", 1);
      for (u32 i = 0; i < unknown50->getSize(); i++) {
        ui::UIObjectAcc item(unknown50->getObject(i));
        name.format("TXT_orb_item_name@%02d", i + 1);
        GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 0, unknowne8, i, false);
        if (adapter != nullptr) {
          name.format("LAY_orb_item_contents@%02d", i + 1);
          adapter->unknown24 = item.searchChild(name.c_str());
        }
        name.format("IMG_orb_item_icon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 2, unknowne8, i, false);
        name.format("IMG_orb_item_rare@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 7, unknowne8, i, false);
        name.format("TXT_orb_item_num@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 3, unknowne8, i, false);
        name.format("TXT_orb_item_max@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 4, unknowne8, i, false);
      }
      GfMenuObjUtil::createVScrollBarPlugin(orb.searchChild("IMG_orb_item_scroll_bar"), unknowne8, "IMG_orb_item_scroll_base", true);
      unknown50->clear();
      {
        ui::UIObjectAcc itemList(orb.unknown10, "LAY_orb_item_list");
        GfMenuItemAdapter::createFromList(itemList.searchChild("TXT_orb_item_info"), 9, unknowne8, -1, false);
      }
      {
        ui::UIObjectAcc recipe(orb.unknown10, "LAY_orb_rcp");
        unknown50->pickupObject(recipe.unknown10, "LAY_orb_rcp_item@%02d", 1);
        for (u32 i = 0; i < unknown50->getSize(); i++) {
          ui::UIObjectAcc item(unknown50->getObject(i));
          name.format("TXT_orb_rcp_item_name@%02d", i + 1);
          GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 0, unknownf0, i, false);
          if (adapter != nullptr) {
            name.format("LAY_orb_rcp_item_contents@%02d", i + 1);
            adapter->unknown24 = item.searchChild(name.c_str());
          }
          name.format("IMG_orb_rcp_item_icon@%02d", i + 1);
          GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 2, unknownf0, i, false);
          name.format("IMG_orb_rcp_item_rare@%02d", i + 1);
          GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 7, unknownf0, i, false);
          name.format("TXT_orb_rcp_item_set_stock@%02d", i + 1);
          GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 3, unknownf0, i, false);
          name.format("TXT_orb_rcp_item_set_num@%02d", i + 1);
          GfMenuReferenceAdapter::create(item.searchChild(name.c_str()), unknown168[i + 8], false);
          name.format("TXT_orb_rcp_item_id_num@%02d", i + 1);
          GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 3, unknownf0, i, false);
          name.format("TXT_orb_rcp_item_id_max@%02d", i + 1);
          GfMenuReferenceAdapter::create(item.searchChild(name.c_str()), unknown168[i + 8], false);
        }
        GfMenuObjUtil::createVScrollBarPlugin(orb.searchChild("IMG_orb_rcp_scroll_bar"), unknownf0, "IMG_orb_rcp_scroll_base", true);
        GfMenuReferenceAdapter::create(orb.searchChild("TXT_orb_rcp_rest_num"), unknown168[6], true);
        {
          ui::UIObjectAcc gauge(orb.unknown10, "IMG_orb_rcp_rest_gauge");
          GfMenuReferenceAdapter::create(gauge.unknown10, unknown168[6], false);
          gauge.setExtType(1);
        }
        GfMenuReferenceAdapter::create(orb.searchChild("TXT_orb_rcp_rest_max"), unknown168[7], false);
        unknown50->clear();
      }
// __LINE__ must be 666 as in the original file: it is the line argument of operator new.
#line 666
      OrbListListener *orbListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) OrbListListener(this);
      orbListListener->addRef();
      ui::UIEventManager::get()->registObjectListener(orb.searchChild("LAY_orb_item_list"), orbListListener);
      if (orbListListener != nullptr) {
        orbListListener->release();
      }
// __LINE__ must be 667 as in the original file: it is the line argument of operator new.
#line 667
      OrbRecipeListener *orbRecipeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) OrbRecipeListener(this);
      orbRecipeListener->addRef();
      ui::UIEventManager::get()->registObjectListener(orb.searchChild("LAY_orb_rcp"), orbRecipeListener);
      if (orbRecipeListener != nullptr) {
        orbRecipeListener->release();
      }
    }
    {
      ui::UIObjectAcc exchange(main.searchChild("LAY_exchange"));
      unknown50->pickupObject(exchange.unknown10, "LAY_exc_task@%02d", 1);
      for (u32 i = 0; i < unknown50->getSize(); i++) {
        ui::UIObjectAcc item(unknown50->getObject(i));
        name.format("TXT_exc_task_name@%02d", i + 1);
        GfMenuExcTaskAdapter *adapter = GfMenuExcTaskAdapter::createFromList(item.searchChild(name.c_str()), 0, unknown150, i, false);
        if (adapter != nullptr) {
          name.format("LAY_exc_task_contents@%02d", i + 1);
          adapter->unknown24 = item.searchChild(name.c_str());
        }
      }
      GfMenuObjUtil::createVScrollBarPlugin(exchange.searchChild("IMG_exc_task_scroll_bar"), unknown150, "IMG_exc_task_scroll_base", true);
      unknown50->clear();
      {
        ui::UIObjectAcc objective(exchange.unknown10, "LAY_exc_objective");
        unknown50->pickupObject(objective.unknown10, "LAY_exc_obj_item@%02d", 1);
        for (u32 i = 0; i < unknown50->getSize(); i++) {
          ui::UIObjectAcc item(unknown50->getObject(i));
          name.format("TXT_exc_obj_item_name@%02d", i + 1);
          GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 0, unknown158, i, false);
          if (adapter != nullptr) {
            name.format("LAY_exc_obj_item_contents@%02d", i + 1);
            adapter->unknown24 = item.searchChild(name.c_str());
          }
          name.format("IMG_exc_obj_item_icon@%02d", i + 1);
          GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 2, unknown158, i, false);
          name.format("TXT_exc_obj_item_stock@%02d", i + 1);
          GfMenuReferenceAdapter::create(item.searchChild(name.c_str()), unknown168[i + 0x11], false);
          name.format("TXT_exc_obj_item_cost@%02d", i + 1);
          GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 3, unknown158, i, false);
          name.format("IMG_exc_obj_item_rare@%02d", i + 1);
          GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 7, unknown158, i, false);
        }
        unknown50->clear();
      }
      {
        ui::UIObjectAcc reward(exchange.unknown10, "LAY_exc_reward");
        unknown168[23]->unknown162(0);
        unknown168[23]->unknown165(0);
        unknown168[23]->unknown166(999999999);
        GfMenuReferenceAdapter::create(reward.searchChild("TXT_exc_reward_money_num"), unknown168[23], false);
        unknown50->pickupObject(reward.unknown10, "LAY_exc_reward_item@%02d", 1);
        for (u32 i = 0; i < unknown50->getSize(); i++) {
          ui::UIObjectAcc item(unknown50->getObject(i));
          name.format("TXT_exc_reward_item_name@%02d", i + 1);
          // The game loads the item handle after createFromList (0x71004ccfe0: ldr w8, [sp, #152]; str w8, [x0, #36]); the single-use local gives that order (P2).
          GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 0, unknown160, i, false);
          adapter->unknown24 = item.unknown10;
          name.format("TXT_exc_reward_item_num@%02d", i + 1);
          GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 3, unknown160, i, false);
        }
      }
      GfMenuReferenceAdapter::create(exchange.searchChild("TXT_exc_obj_rest_num"), unknown168[6], true);
      {
        ui::UIObjectAcc gauge(exchange.unknown10, "IMG_exc_obj_rest_gauge");
        GfMenuReferenceAdapter::create(gauge.unknown10, unknown168[6], false);
        gauge.setExtType(1);
      }
      GfMenuReferenceAdapter::create(exchange.searchChild("TXT_exc_obj_rest_max"), unknown168[7], false);
      {
        ui::UIObjectAcc questGauge(exchange.unknown10, "IMG_exc_reward_quest_gauge");
        GfMenuAdapter *adapter = GfMenuReferenceAdapter::create(questGauge.unknown10, unknown168[24], false);
        if (adapter != nullptr) {
          adapter->setNumberInterpolateMode(0.2f);
        }
        questGauge.setExtType(1);
        adapter = GfMenuReferenceAdapter::create(exchange.searchChild("TXT_exc_reward_quest_num"), unknown168[24], false);
        if (adapter != nullptr) {
          adapter->setNumberInterpolateMode(0.2f);
        }
        adapter = GfMenuReferenceAdapter::create(exchange.searchChild("TXT_exc_reward_quest_max"), unknown168[25], false);
        if (adapter != nullptr) {
          adapter->setNumberInterpolateMode(0.2f);
        }
      }
// __LINE__ must be 804 as in the original file: it is the line argument of operator new.
#line 804
      ExcTaskListListener *excTaskListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ExcTaskListListener(this);
      excTaskListListener->addRef();
      ui::UIEventManager::get()->registObjectListener(exchange.searchChild("LAY_exc_task_list"), excTaskListListener);
      if (excTaskListListener != nullptr) {
        excTaskListListener->release();
      }
    }
    {
      ui::UIObjectAcc numSelect(main.searchChild("LAY_num_select"));
      GfMenuReferenceAdapter::create(numSelect.searchChild("TXT_num_select_value"), unknown168[2], true);
      GfMenuReferenceAdapter::create(numSelect.searchChild("TXT_num_select_total_price"), unknown168[3], true);
// __LINE__ must be 820 as in the original file: it is the line argument of operator new.
#line 820
      NumSelectListener *numSelectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) NumSelectListener(this);
      numSelectListener->addRef();
      ui::UIEventManager::get()->registObjectListener(numSelect.unknown10, numSelectListener);
      if (numSelectListener != nullptr) {
        numSelectListener->release();
      }
    }
    GfMenuCharDataAdapter::createFromReferenceBlade(main.searchChild("IMG_char_bl"), 0x36, 0, false);
    GfMenuAdapterManager::endCategory();
    unknown570 = GfMenuCallContext::create();
    GfMenuObject::initialize();
  }
}

u32 GfMenuObjShop::getSellItemTypeMax() { return 0xd; }

void GfMenuObjShop::open(GfMenuCallContext *context, const OpenParam &param) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCStart(context)) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08_u16 = param.unknown00;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
    GfMenuAdapterManager::addActiveCategory(unknown002);
  }
}

void GfMenuObjShop::close(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::UIObjectAcc acc(context->unknown14);
    if (acc.isValid()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
      GfMenuAdapterManager::delActiveCategory(unknown002);
    }
  }
}

void GfMenuObjShop::dispBlade(bool isDisp) { gf::unknown150(unknown001, 0x46, isDisp); }

void GfMenuObjShop::openOrbError(u32 error) {
  switch (error) {
  case 1:
    GfMenuManager::openCommonWindow(unknown003);
    break;
  case 2:
    GfMenuManager::openCommonWindow(unknown004);
    break;
  }
}

bool GfMenuObjShop::seqWaitFSClose() { return !GfMenuManager::isOpenFullScreen(); }

void GfMenuObjShop::sendEnableEvent(u32 handle) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown00 = 0x40;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendExitEvent(u32 handle) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown00 = 0x41;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendCloseEvent(u32 handle) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown00 = 0x22;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendOpenEvent(u32 handle, int value) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = value;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_33;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendReturnEvent(u32 handle, int value) {
  if (handle != 0) {
    ui::EventData event;
    event.unknown08 = value;
    event.unknown0c = 0;
    event.unknown00 = 0x42;
    GfMenuObject::sendEvent(handle, event, 0.0f);
  }
}

void GfMenuObjShop::addCallContextResult(u32 type, u32 value) {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  GfMenuObject::addResultCallContext(main.unknown10, type, value);
}

void GfMenuObjShop::reqRefreshItemList() { unknown59 = true; }

void GfMenuObjShop::finalize() {
  for (u32 i = 0; i < 26; i++) {
    unknown168[i] = nullptr;
  }
  GfMenuObject::finalize();
}

void GfMenuObjShop::update() {
  unknown248.unknown003();
  if (unknown59) {
    refreshItemList();
    unknown59 = false;
  }
  GfMenuObject::update();
}

bool GfMenuObjShop::seqEndDialog() {
  if (unknown4f8 != 0) {
    ui::EventData event;
    event.unknown00 = 0x42;
    GfMenuObject::sendEvent(unknown4f8, event, 0.0f);
  }
  return true;
}

bool GfMenuObjShop::seqIntervalSleep() {
  if (unknown4d8 == 0) {
    unknown4d8 = 1;
  }
  return --unknown4d8 == 0;
}

bool GfMenuObjShop::seqWaitLoadBlWeapon() {
  unknown570->reset();
  if (GfMenuObjBlWeapon2::attach(unknown570)) {
    unknown248.unknown002(&GfMenuObjShop::seqWaitEndBlWeapon);
    return true;
  }
  return false;
}

bool GfMenuObjShop::seqWaitEndBlWeapon() {
  if (!unknown570->isTerm()) {
    return false;
  }
  ui::UIObjectAcc main(unknown18, "LAY_main");
  sendEnableEvent(main.searchChild("LAY_store_action"));
  return true;
}

u32 GfMenuObjShop::getShopSubLayer(u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (unknown28) {
  case 0:
    return acc.searchChild("LAY_store");
  case 1:
    return acc.searchChild("LAY_exchange");
  case 2:
    return acc.searchChild("LAY_inn");
  case 3:
    return acc.searchChild("LAY_orb");
  }
  return 0;
}

u32 GfMenuObjShop::getShopSubActLayer(u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (unknown28) {
  case 0:
    return acc.searchChild("LAY_store_action");
  case 1:
    return acc.searchChild("LAY_exc_task_list");
  case 2:
    return acc.searchChild("LAY_inn_action");
  case 3:
    return acc.searchChild("LAY_orb_item_list");
  }
  return 0;
}

int GfMenuObjShop::getSpecialShop(u32 shop) {
  if (shop != 0) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SPECIAL_SHOP);
    if (bdat != nullptr) {
      u16 scenarioFlag = GfDataUtil::getScenarioFlag();
      int top = Bdat::getIdTop(bdat);
      for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
        int id = top + i;
        u16 flag = Bdat::getVal(bdat, "scenario_flag", id).valueU16;
        if (flag == 0 || scenarioFlag == flag) {
          u16 shopId = Bdat::getVal(bdat, "shop_id", id).valueU16;
          if (shopId != 0 && shopId == shop) {
            return id;
          }
        }
      }
    }
  }
  return 0;
}

bool GfMenuObjShop::isShopWeapon(u32 shop) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_LIST);
  if (Bdat::getVal(bdat, "ShopType", shop).valueS8 == 0 && Bdat::getVal(bdat, "ShopIcon", shop).valueU16 == 0x1ae) {
    return true;
  }
  return false;
}

bool GfMenuObjShop::seqStartSleepFade() {
  GfSequentialPlay::pauseOn(unknown005);
  SCOM_ACHIEV_INC::addTotalCount(unknown006, 1);
  SCOM_ACHIEV_INC::create(unknown006, 1, 0);
  SCOM_FIELD_VOICE::createExitInn();
  SCOM_RANDOM_INN::setRandom();
  unknown248.unknown002(&GfMenuObjShop::seqWaitSleepFade);
  unknown248.unknown002(&GfMenuObjShop::seqIntervalSleep);
  unknown248.unknown002(&GfMenuObjShop::seqStartLevelUp);
  unknown4d8 = 0;
  unknown4dc = false;
  return true;
}

bool GfMenuObjShop::seqWaitSleepFade() {
  if (!unknown4dc) {
    GfMenuFade::setFade(2, 30, mm::Col4::black);
    unknown4dc = true;
    return false;
  }
  return !GfMenuManager::isFading();
}

void GfMenuObjShop::openNumSelect(u32 owner, u32 value, bool isFlag) {
  ui::UIObjectAcc acc(unknown18, "LAY_num_select");
  unknownd0 = owner;
  ui::EventData event;
  event.unknown00 = 0x21;
  event.unknown08 = value;
  event.unknown0c = 0x280;
  event.unknown10 = 0x1e0;
  event.unknown14 = isFlag;
  GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
}

bool GfMenuObjShop::seqStartLevelUp() {
  if (unknown240) {
    GfGameUtilCloudSea::setInnCloudSea(static_cast<CLOUD_SEA>(GfGameUtilCloudSea::getCloudSea() == 0));
    unknown240 = false;
  }
  GfMenuManager::openFullScreen(5, true, true);
  unknown248.unknown002(&GfMenuObjShop::seqWaitFSClose);
  unknown248.unknown002(&GfMenuObjShop::seqEnd);
  return true;
}

void GfMenuObjShop::refreshFilterIcon() {
  ui::UIObjectAcc filter(unknown18, "LAY_store_sell_filter");
  mm::mtl::FixStr<32> name;
  if (unknown60.size() != 0) {
    u32 i = 0;
    do {
      u32 selected = unknownc0;
      name.format("IMG_store_sell_filter_icon@%02d", i + 1);
      ui::UIObjectAcc icon(filter.searchChild(name.c_str()));
      if (i == selected) {
        icon.setMulColor("sys_select");
      } else {
        icon.loadDefColor();
      }
      i++;
    } while (i < unknown60.size());
  }
}

bool GfMenuObjShop::seqEnd() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  GfSequentialPlay::pauseOff();
  if (unknown4e0 != 0) {
    addCallContextResult(unknown4e0, unknown4e4);
  }
  GfMenuObject::termCallContext(main.unknown10);
  return true;
}

bool GfMenuObjShop::getExcTaskQuestAdditionalValue(u32 id, u32 &value) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_CHANGE_TASK);
  if (bdat != nullptr && GfMenuBdat::isValidBdatID(bdat, id)) {
    value = Bdat::getVal(bdat, "AddFlagValue", id).valueU8;
    return true;
  }
  return false;
}

void GfMenuObjShop::setFilterIndex() {
  u32 filter = unknown60[unknownc0];
  ui::UIObjectAcc acc(unknown18, "TXT_store_sell_index");
  if (acc.isValid()) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MENU_FILTER_CATEGORY);
    ui::UIStr text(bdat, GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_ITEM_LIST_FILTER, filter + 1));
    acc.setText(text);
  }
}

bool GfMenuObjShop::seqEndRecipeIndexOpen() {
  ui::UIObjectAcc acc(unknown18, "LAY_orb_rcp");
  switch (unknownf8.unknown04) {
  case 0:
    acc.setDispChild(true, "TXT_orb_rcp_type_rare_index");
    break;
  case 1:
    acc.setDispChild(true, "TXT_orb_rcp_type_cate_index");
    break;
  default:
    acc.setDispChild(false, "TXT_orb_rcp_type_rare_index");
    acc.setDispChild(false, "TXT_orb_rcp_type_cate_index");
    break;
  }
  return true;
}

void GfMenuObjShop::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case GfMenuTypes::unknown003_33: {
    unknown20->unknown24 = event.unknown08;
    unknown20->unknown34 = getSpecialShop(unknown20->unknown24);
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_LIST);
    if (bdat == nullptr) {
      return;
    }
    unknown20->unknown28 = Bdat::getVal(bdat, "ShopType", unknown20->unknown24).valueU8;
    unknown20->unknown30 = Bdat::getVal(bdat, "TableID", unknown20->unknown24).valueU16;
    unknown20->unknown2c = Bdat::getVal(bdat, "ShopIcon", unknown20->unknown24).valueU16;
    GfMenuReference::setReferenceShopID(unknown20->unknown24);
    if (unknown20->unknown28 == 1 || unknown20->unknown28 == 3) {
      GfMenuObjUtil::setChildDisp(handle, "LAY_location", false);
      GfMenuObjUtil::setChildDisp(handle, "LAY_index_money", false);
    } else {
      GfMenuObjUtil::setChildDisp(handle, "LAY_location", true);
      GfMenuObjUtil::setChildDisp(handle, "LAY_index_money", true);
    }
    unknown20->unknown4e0 = 0;
    unknown20->unknown4e4 = 0;
    acc.setDispChild(false, "TXT_common_guide");
    unknown20->unknown38 = 0;
    int isQuest = 0;
    if (unknown20->unknown28 == 2) {
      u32 price = GfGameUtilShop::getNeedMoneyForInn(unknown20->unknown24);
      if (price != 0) {
        unknown20->unknown168[3]->unknown162(price);
        unknown20->unknown168[4]->unknown162(price * 2);
        u32 money = GfDataUtil::getMoney();
        u32 need = unknown20->unknown168[3]->unknown0c;
        u32 text = acc.searchChild("TXT_inn_action@01");
        if (money < need) {
          GfMenuObjUtil::setColMulandAdd(text, "txt_disable");
        } else {
          GfMenuObjUtil::setColDefault(text);
        }
        money = GfDataUtil::getMoney();
        need = unknown20->unknown168[4]->unknown0c;
        text = acc.searchChild("TXT_inn_action@02");
        if (money < need) {
          GfMenuObjUtil::setColMulandAdd(text, "txt_disable");
        } else {
          GfMenuObjUtil::setColDefault(text);
        }
      } else {
        unknown20->unknown248.unknown005();
        unknown20->unknown248.unknown002(&GfMenuObjShop::seqStartSleepFade);
        unknown20->unknown4e0 = 1;
        unknown20->unknown4e4 = 0;
        acc.setSuspend(false);
        break;
      }
    } else if (unknown20->unknown28 == 3) {
      GfMenuObjSort::setSortLabelText(GfMenuObjSort::getSortID(8, 0), acc.searchChild("TXT_orb_item_sort_label"));
      unknown20->unknown14c = 0;
    } else if (unknown20->unknown28 == 1) {
      ui::UIListInfoBase::SetupParam param;
      param.unknown08 = 8;
      param.unknown10 = true;
      acc.setDispChild(false, "TXT_exc_task_index");
      acc.setDispChild(false, "TXT_exc_task_index_quest");
      acc.setDispChild(false, "TXT_exc_task_index_cook");
      acc.setDispChild(false, "TXT_exc_task_index_craft");
      unknown20->unknown150->setupExcTaskListFromShop(param, unknown20->unknown24);
      unknown20->unknown150->setIndex(0);
      int taskType;
      if (unknown20->unknown150->getSize() != 0) {
        u8 *changeBdat = GfDataBdat::getFP(BDAT_MNU_SHOP_CHANGE);
        if (changeBdat == nullptr) {
          return;
        }
        u32 purpose = Bdat::getVal(changeBdat, "LinkQuestTask", unknown20->unknown30).valueU16;
        if (purpose != 0) {
          u32 taskIndex = Bdat::getVal(changeBdat, "LinkQuestTaskID", unknown20->unknown30).valueU16;
          u8 *logBdat = nullptr;
          u32 logId = 0;
          GfQuestInfo::getTaskLog(logBdat, logId, purpose, taskIndex);
          if (logBdat != nullptr && logId != 0) {
            ui::UIObjectAcc(acc.unknown10, "TXT_exc_reward_quest_task").setText(ui::UIStr(logBdat, logId));
          }
          QuestID quest = GfQuestManager::getOrderQuestId(purpose);
          unknown20->unknown548 = QuestTaskParam(quest, taskIndex, purpose, TASK_STATE_UNKNOWN_0);
          isQuest = 1;
          acc.setDispChild(true, "TXT_exc_task_index_quest");
          taskType = 1;
        }
      }
      if (!isQuest) {
        taskType = 0;
        if (unknown20->unknown2c == 0x1aa) {
          acc.setDispChild(true, "TXT_exc_task_index_cook");
          taskType = 2;
        } else if (unknown20->unknown2c == 0x1ab) {
          acc.setDispChild(true, "TXT_exc_task_index_craft");
          taskType = 3;
        } else if (unknown20->unknown2c == 0x1a4) {
          acc.setDispChild(true, "TXT_exc_task_index_quest");
          taskType = 1;
        }
      }
      unknown20->unknown168[24]->unknown10 = 0;
      unknown20->unknown168[24]->unknown14 = 999;
      unknown20->unknown168[25]->unknown10 = 0;
      unknown20->unknown168[25]->unknown14 = 999;
      unknown20->unknown568 = taskType;
      if (unknown20->unknown568 == 0) {
        acc.setDispChild(true, "TXT_exc_task_index");
      }
      unknown20->setupExcItem();
    }
    GfMenuObjOperationInfo::open(0, 0, 0, 0);
    GfMenuObjOperationInfo::setGuideDisp(false);
    unknown20->unknown168[0]->unknown162(unknown20->unknown24);
    unknown20->unknown168[1]->unknown162(GfGameManager::getMapZoneID());
    GfMenuObject::sendOpenEvent(acc.searchChild("LAY_common"), 0, 0.06666667f);
    GfMenuObject::sendOpenEvent(unknown20->getShopSubLayer(acc.unknown10), 0, 0.06666667f);
    ui::UIObjectAcc(acc.unknown10, "LAY_index_normal").setDisp(!isQuest);
    ui::UIObjectAcc(acc.unknown10, "LAY_index_quest").setDisp(isQuest);
    acc.setSuspend(false);
    break;
  }
  case GfMenuTypes::unknown003_34:
    unknown20->sendCloseEvent(acc.searchChild("LAY_common"));
    unknown20->sendCloseEvent(unknown20->getShopSubLayer(acc.unknown10));
    GfMenuObjOperationInfo::close();
    break;
  case 0x41:
    GfMenuReference::setReferenceShopID(0);
    if (unknown20->unknown4e0 != 0) {
      unknown20->addCallContextResult(unknown20->unknown4e0, unknown20->unknown4e4);
    }
    if (unknown20->unknown248.unknown00.empty()) {
      GfMenuObject::termCallContext(acc.unknown10);
      acc.setSuspend(true);
    }
    break;
  case 0x46: {
    u32 isFadeIn = event.unknown08;
    ui::UIObjectAcc layer(acc.searchChild("LAY_char"));
    if (isFadeIn == 0) {
      GfMenuObjUtil::setCommonFadeOut(layer.unknown10, 2, false);
    } else {
      GfMenuObjUtil::setCommonFadeIn(layer.unknown10, 2, false);
    }
    return;
  }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjShop::CommonListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    GfMenuObject::disableInput(acc.unknown10);
    unknown0c = -1;
    break;
  case 3:
    if (event.unknown08 == 2) {
      unknown20->sendExitEvent(0);
      acc.setDisp(false);
    }
    break;
  case GfMenuTypes::unknown003_33: {
    acc.setDisp(true);
    {
      ui::UIObjectAcc bg(acc.unknown10, "IMG_common_bg");
      bg.startAnimation("fade_in", false);
    }
    acc.setDispChild(true, "LAY_index");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "cmn_fade_motion_up_down";
    param.unknown58 = "fade_in_up";
    param.unknown11 = true;
    param.unknown14 = 8;
    param.unknown04 = 1;
    int ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, "LAY_index");
    GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    unknown0c = ctrl;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    {
      ui::UIObjectAcc bg(acc.unknown10, "IMG_common_bg");
      bg.startAnimation("fade_out", false);
    }
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "cmn_fade_motion_up_down";
    param.unknown58 = "fade_out_up";
    param.unknown11 = true;
    param.unknown14 = 10;
    param.unknown04 = 2;
    int ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, "LAY_index");
    GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    unknown0c = ctrl;
    break;
  }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjShop::OrbListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      u32 previous = event.unknown0c;
      unknown20->unknowne8->setIndex(index);
      u32 page = unknown20->unknowne8->getIndex(true);
      unknown20->unknown50->setIndex(page);
      u32 orb = GfRecipeOrbUtil::getEquipOrb(unknown20->unknowne8->getContents(unknown20->unknowne8->getIndex(false)).unknown04);
      MenuItemInfo &item = unknown20->unknown238->unknown0c;
      item.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_3;
      item.unknown04 = orb;
      item.unknown08 = 1;
      item.unknown0c = GfItemHandle(0);
      unknown20->updateOrbRecipe();
      unknown20->unknown59 = true;
      if (previous != 0xffffffff && index != previous) {
        GfMenuObjUtil::playSECommonCursor();
      }
    }
    return;
  }
  case 8: {
    int type = event.unknown0c;
    bool isClose;
    if (type == 1) {
      u32 error = GfMenuItemUtil::canCreateOrb(unknown20->unknowne8->getContents(unknown20->unknowne8->getIndex(false)).unknown04);
      if (error != 0) {
        GfMenuObjUtil::playSECommon(2);
        if (error == 1) {
          GfMenuManager::openCommonWindow(unknown003);
        } else if (error == 2) {
          GfMenuManager::openCommonWindow(unknown004);
        }
        return;
      }
      switch (unknown20->unknownf8.unknown04) {
      case 0: {
        u32 recipe = acc.searchSibiling("LAY_orb_rcp");
        GfMenuObjUtil::playSECommonDecide();
        if (recipe != 0) {
          if (unknown20->unknownf0->getSize() != 0) {
            unknown20->unknownf0->setIndex(0);
          }
          unknown20->sendEnableEvent(recipe);
        }
        break;
      }
      case 1: {
        u32 recipe = acc.searchSibiling("LAY_orb_rcp");
        GfMenuObjUtil::playSECommonDecide();
        if (recipe != 0) {
          if (unknown20->unknownf0->getSize() != 0) {
            unknown20->unknownf0->setIndex(0);
          }
          unknown20->sendEnableEvent(recipe);
        }
        break;
      }
      case 2:
        GfMenuManager::openCommonWindow(unknown007);
        unknown20->unknown4f8 = acc.unknown10;
        unknown20->unknown248.unknown005();
        unknown20->unknown248.unknown002(&GfMenuObjShop::seqWaitOrbCreate);
        unknown20->unknown248.unknown002(&GfMenuObjShop::seqItemGet);
        unknown20->unknown248.unknown002(&GfMenuObjShop::seqEndDialog);
        GfMenuObjUtil::playSECommonDecide();
        break;
      default:
        GfMenuObjUtil::playSECommonDecide();
        return;
      }
      isClose = false;
    } else if (type == 2) {
      if (unknown20->unknown34 == 2) {
        return;
      }
      GfMenuObjUtil::playSECommonCancel();
      isClose = true;
    } else if (type == 0x11) {
      GfMenuObjSort::open(acc.unknown10, acc.searchChild("TXT_orb_item_sort_label"), 8, unknown20->unknown14c);
      isClose = false;
    } else {
      return;
    }
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    if (unknown20->unknownc8 != nullptr) {
      unknown20->unknownc8->release();
      unknown20->unknownc8 = nullptr;
    }
    acc.setDispChild(false, "IMG_orb_item_cursor");
    if (isClose) {
      unknown20->sendCloseEvent(0);
    }
    return;
  }
  case 0x40: {
    GfMenuObject::enableInput(acc.unknown10);
    GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    unknown20->setGuideText(0x3f);
    unknown20->updateOrbRecipe();
    unknown20->unknown59 = true;
    unknown20->sendOpenEvent(acc.searchSibiling("LAY_orb_rcp"), 0);
    GfMenuObjOperationInfo::setActionEnable(acc.unknown10, 2, unknown20->unknown34 != 2);
    break;
  }
  case 0x42:
    GfMenuObject::enableInput(acc.unknown10);
    GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    GfMenuObjOperationInfo::setActionEnable(acc.unknown10, 2, unknown20->unknown34 != 2);
    return;
  case 0x148:
    GfMenuObject::enableInput(handle);
    GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    if (unknown20->unknown14c != event.unknown08) {
      u16 sort = GfMenuObjSort::getSortID(8, event.unknown08);
      unknown20->unknowne8->sort(sort, false);
      unknown20->unknown14c = event.unknown08;
    }
    GfMenuObject::resetInputSelection(acc.unknown10);
    GfMenuObject::setupInputSelectionFromList(acc.unknown10, *unknown20->unknowne8);
    return;
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjShop::SellFilterListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    if (unknown20->unknownc0 != index) {
      unknown20->unknownc0 = index;
      ui::EventData notify;
      notify.unknown00 = 0x45;
      GfMenuObject::sendEvent(acc.getParentHandle(), notify, 0.0f);
    }
    unknown20->refreshFilterIcon();
    if (previous != 0xffffffff && index != previous) {
      GfMenuObjUtil::playSECommonTab();
    }
    break;
  }
  case 0x21:
    GfMenuObject::resetInputSelection(acc.unknown10);
    GfMenuObject::setupInputSelection(acc.unknown10, unknown20->unknownc0, unknown20->unknown60.size());
    GfMenuObject::enableInput(acc.unknown10);
    break;
  case 0x22:
    // Measured (clang 3.9.1): with `case 1: case 0x22:` as grouped labels the default arm is laid out after case 0x21 (game: before it);
    // two separate bodies leave the game's order. The game's case 1 and case 0x22 are one block (0x71004d1c54): the tail merge joins them.
    GfMenuObject::disableInput(acc.unknown10);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjShop::setGuideText(u32 id) {
  if (unknown38 != id) {
    ui::UIObjectAcc acc(unknown18, "TXT_common_guide");
    {
      u32 name = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MSG_OPERATION_GUIDE), "name", id).valueU16;
      ui::UIStr text(GfDataBdat::getFP(BDAT_MENU_OPERATION_GUIDE), name);
      acc.setText(text);
    }
    acc.setDisp(true);
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l");
    param.unknown14 = 8;
    param.unknown11 = true;
    param.unknown00 = 0.2f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    unknown38 = id;
  }
}

void GfMenuObjShop::setupExcItem() {
  ui::UIObjectAcc acc(unknown18, "LAY_exc_objective");
  mm::mtl::FixStr<32> name;
  GfMenuItemList::ItemShopExcSetup setup;
  setup.unknown14 = unknown150->getContents(unknown150->getIndex(false)).unknown00;
  setup.unknown00.unknown08 = 5;
  unknown158->clear();
  unknown158->setupFromShopExcTask(setup);
  u32 have = 0;
  u32 total = 0;
  for (u32 i = 0; i < unknown158->getSize(); i++) {
    MenuItemInfo &info = unknown158->getContents(i);
    unknown168[17 + i]->unknown162(GfMenuItemUtil::getItemNum(info.unknown00, info.unknown04));
    unknown168[17 + i]->unknown10 = 0;
    unknown168[17 + i]->unknown14 = 999;
    int number = unknown168[17 + i]->unknown0c;
    s16 need = info.unknown08;
    number = number < need ? number : need;
    total += need;
    have += number;
    name.format("TXT_exc_obj_item_cost@%02d", i + 1);
    ui::UIObjectAcc cost(acc.unknown10, name.c_str());
    if (cost.isValid()) {
      if (unknown168[17 + i]->unknown0c < info.unknown08) {
        GfMenuObjUtil::setColMulandAdd(cost.unknown10, "txt_warning");
      } else {
        GfMenuObjUtil::setColDefault(cost.unknown10);
      }
    }
  }
  u32 remain = total;
  if (have <= total) {
    remain = have;
  }
  unknown168[6]->unknown14 = total;
  unknown168[6]->unknown0c = remain;
  unknown168[7]->unknown0c = total;
}

void GfMenuObjShop::refreshExcReward() {
  if (unknown150 != nullptr) {
    ui::UIObjectAcc item(unknown18, "LAY_exc_reward_item");
    ui::UIObjectAcc quest(unknown18, "LAY_exc_reward_quest");
    u32 task = unknown150->getContents(unknown150->getIndex(false)).unknown00;
    u32 value;
    bool isHide = false;
    if (!getExcTaskReward(task, value, unknown160, isHide)) {
      if (!getExcTaskQuestAdditionalValue(task, value)) {
        item.setDisp(false);
        quest.setDisp(false);
      } else {
        item.setDisp(false);
        quest.setDisp(!isHide);
        u32 limit;
        u32 count;
        u32 questItem;
        u32 category;
        if (!unknown548.unknown04.empty() && GfQuestTask::getTaskCount(unknown548, limit, count, questItem, category)) {
          unknown168[24]->unknown166(limit);
          unknown168[24]->unknown162(count);
          unknown168[25]->unknown162(limit);
        }
      }
    } else {
      unknown168[23]->unknown162(value);
      item.setDisp(!isHide);
      quest.setDisp(false);
    }
    ui::UIObjectAcc(unknown18, "TXT_exc_reward_quest_index").setDisp(quest.isDisp());
    ui::UIObjectAcc(unknown18, "TXT_exc_reward_item_index").setDisp(item.isDisp());
    ui::UIObjectAcc(unknown18, "LAY_exc_reward_secret").setDisp(isHide);
  }
}

bool GfMenuObjShop::seqWaitExchange() {
  if (GfMenuManager::isOpenCommonWindow()) {
    return false;
  }
  s16 result = GfMenuManager::getCommonWindowResult();
  if (result == 0) {
    unknown4e0 = 1;
    unknown4e4 = 0;
    GfGameUtilShop::execChangeItem(unknown150->getContents(unknown150->getIndex(false)).unknown00, unknown30);
    setupExcItem();
    unknown59 = true;
    refreshExcReward();
    unknown500 = 1;
  } else {
    unknown500 = 2;
  }
  unknown4dc = false;
  return true;
}

bool GfMenuObjShop::seqStartRecipeIndexOpen() {
  ui::UIObjectAcc acc(unknown18, "LAY_orb_rcp");
  acc.setDispChild(false, "LAY_orb_rcp_index_rare");
  acc.setDispChild(false, "LAY_orb_rcp_index_cate");
  switch (unknownf8.unknown04) {
  case 0:
    acc.setDispChild(true, "LAY_orb_rcp_index_rare");
    acc.setDispChild(false, "TXT_orb_rcp_type_rare_index");
    break;
  case 1:
    acc.setDispChild(true, "LAY_orb_rcp_index_cate");
    acc.setDispChild(false, "TXT_orb_rcp_type_cate_index");
    break;
  }
  unknown248.addAnimJob(acc.searchChild("IMG_orb_rcp_index_base"), "fadein");
  unknown248.unknown002(&GfMenuObjShop::seqEndRecipeIndexOpen);
  return true;
}

bool GfMenuObjShop::seqItemGet() {
  if (unknown500 != 1) {
    return true;
  }
  if (!unknown4dc) {
    unknown578->reset();
    switch (unknown28) {
    case 3:
      if (unknown148 != 0) {
        ui::UIListInfoBase::SetupParam param;
        unknown160->setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
        MenuItemInfo info;
        info.unknown04 = unknown148;
        info.unknown00 = GfItemUtil::getType(info.unknown04);
        info.unknown08 = 1;
        unknown160->addItem(info, false);
        unknown578->reset();
        GfMenuObjCommonText::openGetItem(unknown578, unknown160);
        unknown148 = 0;
      }
      break;
    case 1:
      if (unknown160->getSize() != 0) {
        unknown578->reset();
        GfMenuObjCommonText::openGetItem(unknown578, unknown160);
      }
      break;
    }
    if (!unknown578->isActive()) {
      unknown4dc = false;
      return true;
    }
    GfMenuObjUtil::playSE(10);
    unknown4dc = true;
  }
  if (!unknown578->isTerm()) {
    return false;
  }
  unknown4dc = false;
  return true;
}

bool GfMenuObjShop::canGetExcTaskReward(u32 id) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_CHANGE_TASK);
  if (bdat == nullptr || !GfMenuBdat::isValidBdatID(bdat, id)) {
    return false;
  }
  u16 rewardSet = Bdat::getVal(bdat, "Reward", id).valueU16;
  if (!rewardSet) {
    return true;
  }
  GfQuestReward reward;
  if (!GfQuestUtil::getReward(reward, rewardSet, false)) {
    return true;
  }
  for (u32 i = QUEST_REWARD_UNKNOWN_8; i < sizeof(reward.unknown00) / sizeof(reward.unknown00[0]); i++) {
    if (reward.unknown00[i].unknown44 != 0 && !GfItemUtil::isEnableAddItemBox(reward.unknown00[i].unknown44, reward.unknown00[i].m_developZone)) {
      return false;
    }
  }
  return true;
}

bool GfMenuObjShop::getExcTaskReward(u32 id, u32 &value, GfMenuItemList *list, bool &isHide) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_CHANGE_TASK);
  if (bdat != nullptr && GfMenuBdat::isValidBdatID(bdat, id)) {
    isHide = Bdat::getVal(bdat, "HideReward", id).valueS16 != 0;
    list->clear();
    u16 rewardSet = Bdat::getVal(bdat, "Reward", id).valueU16;
    if (rewardSet) {
      {
        GfMenuItemList::QuestRewardSetup setup;
        setup.unknown00.unknown08 = 4;
        setup.unknown14 = rewardSet;
        list->setupFromQuestReward(setup);
      }
      GfQuestReward reward;
      if (GfQuestUtil::getReward(reward, rewardSet, false)) {
        value = reward.unknown00[QUEST_REWARD_UNKNOWN_0].unknown44_u32;
        if (value != 0) {
          return true;
        }
        return list->getSize() != 0;
      }
    }
  }
  return false;
}

void GfMenuObjShop::setupIndex(u32 handle, const char *name, u32 count) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    mm::mtl::FixStr<32> path;
    for (u32 i = 0; i < count; i++) {
      path.format("TXT_%s_index@%02d", name, i + 1);
      u32 text = acc.searchChild(path.c_str());
      if (text == 0) {
        break;
      }
      path.format("IMG_%s_index_l@%02d", name, i + 1);
      {
        ui::UIObjectAcc left(handle, path.c_str());
        if (!left.isValid()) {
          break;
        }
        GfMenuObjUtil::setDockPos(left.unknown10, text, 1, false);
        GfMenuObjUtil::addPos(left.unknown10, -8, 0);
      }
      path.format("IMG_%s_index_r@%02d", name, i + 1);
      ui::UIObjectAcc right(handle, path.c_str());
      if (!right.isValid()) {
        break;
      }
      GfMenuObjUtil::setDockPos(right.unknown10, text, 2, false);
      GfMenuObjUtil::addPos(right.unknown10, 8, 0);
    }
  }
}

bool GfMenuObjShop::seqWaitOrbCreate() {
  if (GfMenuManager::isOpenCommonWindow()) {
    return false;
  }
  s16 result = GfMenuManager::getCommonWindowResult();
  if (result != 0) {
    unknown500 = 2;
  } else {
    u32 item = unknowne8->getContents(unknowne8->getIndex(false)).unknown04;
    mm::mtl::FixedVector<OrbRecipe, 128> items;
    bool canCreate;
    if (unknownf8.unknown04 == 2) {
      canCreate = GfRecipeOrbUtil::isEnableRecipe(unknownf8.unknown00);
      if (canCreate) {
        const mm::mtl::FixedVector<OrbRecipe, 8> *results = unknownf8.getResultItems();
        for (u32 i = 0; i < results->size(); i++) {
          OrbRecipe recipe;
          recipe.unknown00 = (*results)[i].unknown00;
          recipe.unknown02 = (*results)[i].unknown02;
          items.push_back(recipe);
        }
      }
    } else {
      for (u32 i = 0; i < unknownf0->getSize(); i++) {
        if (unknown130[i] != 0) {
          OrbRecipe recipe;
          recipe.unknown00 = unknownf0->getContents(i).unknown04;
          recipe.unknown02 = unknown130[i];
          items.push_back(recipe);
        }
      }
      canCreate = GfRecipeOrbUtil::isEnabaleOrbRecipe(unknownf8.unknown00, items);
    }
    if (canCreate) {
      GfRecipeOrbUtil::execOrbRecipe(item, &items);
      MenuItemInfo info = unknowne8->getContents(unknowne8->getIndex(false));
      info.unknown08 = 1;
      unknown148 = GfRecipeOrbUtil::getEquipOrb(info.unknown04);
      unknowne8->decItem(info, false);
      {
        ui::UIObjectAcc acc(unknown18, "LAY_orb_item_list");
        GfMenuObject::resetInputSelection(acc.unknown10);
        GfMenuObject::setupInputSelectionFromList(acc.unknown10, *unknowne8);
      }
      unknown4e0 = 1;
      unknown4e4 = 0;
      GfMenuObjUtil::playSE(0x1a);
    }
    unknown500 = 1;
  }
  unknown4dc = false;
  return true;
}

void GfMenuObjShop::updateOrbRecipe() {
  ui::UIObjectAcc acc(unknown18, "LAY_orb");
  unknownf8.unknown001();
  if (unknowne8->getSize() != 0) {
    u32 recipe = GfRecipeOrbUtil::getRecipeID(unknowne8->getContents(unknowne8->getIndex(false)).unknown04);
    if (recipe != 0) {
      RecipeInfo info;
      if (GfRecipeOrbUtil::getRecipeInfo(info, recipe)) {
        unknownf8 = info;
      }
    }
  }
  ui::EventData event;
  event.unknown00 = 0x43;
  GfMenuObject::sendEvent(acc.searchSibiling("LAY_orb_rcp"), event, 0.0f);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjShop, 8>>(const mm::mtl::Delegate<bool()> *);
