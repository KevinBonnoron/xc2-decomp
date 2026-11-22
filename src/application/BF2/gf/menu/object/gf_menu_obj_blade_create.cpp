#include "gf/menu/object/gf_menu_obj_blade_create.h"

#include <string.h>

#include "bdat.h"
#include "fw/fw_camera.h"
#include "fw/fw_pad.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_save.h"
#include "gf/data/gf_item_id.h"
#include "gf/game/blade/gf_blade_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/sequential_play/gf_play_command.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_model_view.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_blade_create_camera.h"
#include "gf/menu/object/gf_menu_obj_blade_name.h"
#include "gf/menu/object/gf_menu_obj_blade_set2.h"
#include "gf/menu/object/gf_menu_obj_cmn_status.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "gf/request/gf_req_scom.h"
#include "gf/sound/gf_sound.h"
#include "gf/util/gf_item_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
#include "scn/scn_render_dr_sys_parm_acc.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/ctrl/ui_ctrl_curve.h"
#include "ui/ctrl/ui_ctrl_radar_graph.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace gf {
struct GF_OBJ_HANDLE;

// Inferred role: full screen layer id; original name unknown.
constexpr u32 unknown001 = 0x14;

// Inferred role: names of the pages of the creation screen; original name unknown.
const char *const unknown002[6] = {"LAY_dr_select", "LAY_core_select", "LAY_bst_select", "LAY_confirm", "LAY_create", "LAY_result"};

// Inferred role: object type of the drivers in the model view; original name unknown.
constexpr u32 unknown003 = 3;

// Inferred role: object type of the crystals in the model view; original name unknown.
constexpr u32 unknown009 = 0xf;

// Inferred role: driver of each camera of the driver select page; original name unknown.
const u32 unknown004[16] = {1, 2, 6, 3, 0x15, 0x13, 0x15, 0x15, 0xb9, 0xba, 0xbb, 0xbc, 0x154, 0x151, 0xffffffff, 0x150};

// Inferred role: camera offset of each page of the creation screen; original name unknown.
const int unknown008[6] = {0, 1, 2, 3, 4, 4};

// Inferred role: camera motion of each driver of the creation screen, null for the drivers without one; original name unknown.
const char *const unknown012[6] = {"mnu_blade_create_rex_01", "mnu_blade_create_nia_01", "mnu_blade_create_sieg_01", nullptr, nullptr, "mnu_blade_create_melef_01"};

// Inferred role: effect names of each booster in the model view, the select effect and the use effect; original name unknown.
const char *const unknown016[4][2] = {{"bc_00_000", "bc_10_000"}, {"bc_01_000", "bc_11_000"}, {"bc_02_000", "bc_12_000"}, {"bc_03_000", "bc_13_000"}};

// Inferred role: sound effect of each booster; original name unknown.
const char *const unknown017[4] = {"se_fld_allmap_707", "se_fld_allmap_708", "se_fld_allmap_709", "se_fld_allmap_710"};

// Inferred role: sets the weapon type of a driver in the model view; original name unknown.
static void unknown006(GfMenuModelView *view, u32 driver, int weaponType) { view->setObjectCommandValue(view->findGfObj(unknown003, driver), "V_weaponselect", weaponType); }

// Inferred role: starts the blade arts animation of a driver in the model view; original name unknown.
static void unknown007(GfMenuModelView *view, u32 driver) { view->sendObjectCommand(view->findGfObj(unknown003, driver), "C_bladearts_01"); }

// Inferred role: gets a crystal object of the model view; original name unknown.
static GF_OBJ_HANDLE *unknown011(GfMenuModelView *view, u32 index) { return view->findGfObj(unknown009, view->getMapObjID(index)); }

// Inferred role: attaches a crystal object of the model view to the right hand of a driver; original name unknown.
static void unknown010(GfMenuModelView *view, u32 driver, u32 index) {
  GF_OBJ_HANDLE *driverObj = view->findGfObj(unknown003, driver);
  view->attachObject(unknown011(view, index), driverObj, "EX_wp_R");
}

// Inferred role: checks that a crystal object of the model view exists; original name unknown.
static bool unknown013(GfMenuModelView *view, u32 index) { return view->checkGfObj(unknown009, view->getMapObjID(index)); }

// Inferred role: starts the opening control of a page of the creation screen; original name unknown.
static void unknown014(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 1;
  param.unknown00 = 0.5f;
  param.unknown04 = 1;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

// Inferred role: starts the closing control of a page of the creation screen; original name unknown.
static void unknown015(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 2;
  param.unknown14 = 2;
  param.unknown00 = 0.25f;
  param.unknown04 = 2;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

// Inferred role: registers a listener on a page of the creation screen and drops the reference of its creation; original name unknown.
// The reference is taken before the page object is looked up: the game increments the count of the new listener without reloading it (0x71003f7000).
static void unknown018(GfMenuObjBladeCreate *menu, u32 page, ui::UIObjectListener *listener) {
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(menu->getPageObject(menu->unknown18, page, false), listener);
  if (listener != nullptr) {
    listener->release();
  }
}

// Inferred role: registers a listener on a UI object of the creation screen and drops the reference of its creation; original name unknown.
// Measured (ruling 8): the handle is read from the accessor inside the helper, after the reference is taken; passed as a value the handle is loaded first and the count of the new listener
// is reloaded (1444 instructions against the game's 1441).
static void unknown028(const ui::UIObjectAcc &acc, ui::UIObjectListener *listener) {
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(acc.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
}

// Inferred role: creates the select object list of a page of the creation screen; original name unknown.
static ui::UISelectObjList *unknown026() {
  ui::UISelectObjList::CreateParam createParam;
  createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  return ui::UISelectObjList::create(createParam);
}

// Inferred role: sets up the name of an item row of a select page of the creation screen and links its layer; original name unknown.
// Measured (ruling 8): the list is taken by reference to the member so that it is read after the name is formatted, as in the game; passed as a value it is read first (1443 instructions
// against the game's 1441).
static void unknown027(ui::UIObjectAcc &page, mm::mtl::FixStr<32> &name, const char *nameFormat, const char *layerFormat, GfMenuItemList *const &list, u32 index) {
  name.format(nameFormat, index + 1);
  GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(page.searchChild(name.c_str()), 0, list, index, false);
  if (adapter != nullptr) {
    name.format(layerFormat, index + 1);
    adapter->unknown24 = page.searchChild(name.c_str());
  }
}

// Inferred role: transforms a point by a matrix (row vector convention); original name unknown. Shared by GfMenuBladeCreateCamera::update (0x71003fddb0) and seqCreateBuildBlade
// (0x71003fc7e0). The same statements as GfMenuObjUtil::convViewSpace (another unit, on the view matrix of GfInfo; the gmk_base.h helpers build their own matrix). Measured (ruling 8, P4): a helper
// that returns the point (`position = unknown029(position, matrix)`, a returned `mm::Vec3(...)` or a returned local copied back) gives 217 instructions in update, the game's count but not its
// schedule of the fadds and fmuls (NO MATCH), and 296 in seqCreateBuildBlade (the game's 298); a helper that stores into the point matches both, only with the stores in the order z, x, y
// (`point = result` does not match in update).
static void unknown029(mm::Vec3 &point, const mm::Mat44 &matrix) {
  mm::Vec3 result;
  result.x = point.x * matrix.rows[0][0] + point.y * matrix.rows[1][0] + point.z * matrix.rows[2][0] + matrix.rows[3][0];
  result.y = point.x * matrix.rows[0][1] + point.y * matrix.rows[1][1] + point.z * matrix.rows[2][1] + matrix.rows[3][1];
  result.z = point.x * matrix.rows[0][2] + point.y * matrix.rows[1][2] + point.z * matrix.rows[2][2] + matrix.rows[3][2];
  point.z = result.z;
  point.x = result.x;
  point.y = result.y;
}

// The camera functions sit between the listeners of this unit in the game (setRotY at 0x71003f997c, constructor at 0x71003fdd00), and the listeners
// and the constructor of the menu object inline them, so the camera is defined in this file.
// Inferred role: camera priority of the blade creation; original name unknown.
static constexpr fw::CAMERA_PRIO CAMERA_PRIO_UNKNOWN_55 = static_cast<fw::CAMERA_PRIO>(55);

GfMenuBladeCreateCamera::GfMenuBladeCreateCamera()
    : fw::Camera(CAMERA_PRIO_UNKNOWN_55), unknownf0(0.0f), unknownf4(0.0f), m_rotOffsetY(0.0f), unknownfc(0.0f), unknown100(0.0f), unknown104(0.0f), unknown108(0) {}

GfMenuBladeCreateCamera::~GfMenuBladeCreateCamera() {}

const mm::mtl::RTTI *GfMenuBladeCreateCamera::getRTTI() const { return &m_rtti; }

const char *GfMenuBladeCreateCamera::getName() const { return "GfMenuBladeCreateCamera"; }

void GfMenuBladeCreateCamera::setRotY(f32 rot, u32 direction, f32 duration) {
  f32 current = unknownfc;
  if (direction == 0 && rot - current > 0.0f) {
    rot += -6.2831855f;
  } else if (direction == 1 && rot - current < 0.0f) {
    if (current + rot < 6.2831855f) {
      rot = 6.2831855f - rot;
    } else {
      rot += 6.2831855f;
    }
  }
  unknown100 = rot;
  unknown108 = direction;
  unknownf0 = duration;
  unknownf4 = 0.0f;
  if (duration == 0.0f) {
    unknownfc = rot;
    current = rot;
  }
  unknown104 = current;
}

void GfMenuBladeCreateCamera::setRotOffsetY(f32 offset) { m_rotOffsetY = offset; }

void GfMenuBladeCreateCamera::setDefault(const mm::Vec3 &position, const mm::Vec3 &target) {
  unknownb0 = position;
  unknownc0 = target;
}

void GfMenuBladeCreateCamera::getDefault(mm::Vec3 &position, mm::Vec3 &target) {
  position = unknownb0;
  target = unknownc0;
}

void GfMenuBladeCreateCamera::getCurrent(mm::Vec3 &position, mm::Vec3 &target) {
  position = unknownd0;
  target = unknowne0;
}

// Game address 0x71003fddb0. Advances the rotation of the camera (a sin90 curve between the start and target rotation, wrapped to one turn), turns the default position
// about the y axis and looks at the rotated target. Evidence for the forms (217 instructions, each measured):
// - The identity matrix is copied into a local before the rotation matrix is built, so its sixteen loads come before the sinf and cosf calls.
// - `if (time >= duration)` first: the game's branch is `b.ge` (ordered), where `time < duration` gives `b.pl`.
// - The lerp is `curve * (target - start) + start`: it gives the game's load order of the two rotations.
// - The transformation of the position is the shared helper unknown029 (the call forms measured there).
void GfMenuBladeCreateCamera::update(const fw::UpdateInfo &info) {
  mm::Vec3 position = unknownb0;
  mm::Vec3 rotation = unknownc0;
  if (unknownf4 != unknownf0) {
    unknownf4 += info.unknown04;
    if (unknownf4 >= unknownf0) {
      unknownf4 = unknownf0;
      unknownfc = unknown100;
    } else {
      unknownfc = ui::UIUtil::getCurve(ui::CURVE_TYPE_SIN90)->calc(unknownf4, 0.0f, 1.0f, unknownf0) * (unknown100 - unknown104) + unknown104;
    }
    if (unknownfc < 0.0f) {
      unknownfc += 6.2831855f;
    } else if (unknownfc >= 6.2831855f) {
      unknownfc -= 6.2831855f;
    }
  }
  f32 angle = unknownfc + m_rotOffsetY;
  mm::Mat44 matrix = mm::Mat44::identity;
  mm::Mat44 rotationMatrix;
  rotationMatrix.setRotY(angle);
  matrix = matrix * rotationMatrix;
  unknown029(position, matrix);
  rotation.y += angle;
  updateLookAt(position, rotation);
  unknownd0 = position;
  unknowne0 = rotation;
}

// Game address 0x71003fe114. Looks from `position` along the forward axis turned by the euler angles `rotation`. Evidence for the forms (210 instructions, each measured):
// - The identity quaternion is copied into a local before the euler quaternion is built: its four loads come before the first sinf call (0x71003fe134 ldp), the plain
//   `mm::Quat::mul(mm::Quat::identity, ...)` has 206 instructions (the loads follow the calls).
// - The quaternion is mm::unknown005 (x, y, z, w with the product of the cosines first in the w sum): the other statement orders and sum orders (96 forms) schedule the eight products
//   differently.
// - The vector is rotated in place by mm::unknown010: `target = quat.rotate(target)` has 210 instructions but adds `position` before the rotated component in the x and y sums.
void GfMenuBladeCreateCamera::updateLookAt(const mm::Vec3 &position, const mm::Vec3 &rotation) {
  mm::Vec3 target(0.0f, 0.0f, 1.0f);
  mm::Quat current = mm::Quat::identity;
  mm::Quat quat = mm::Quat::mul(current, mm::unknown005(rotation));
  mm::unknown010(quat, target);
  target += position;
  setLookAt(position, target, 0.0f);
}

GfMenuObjBladeCreate::GfMenuObjBladeCreate(u32 handle)
    : GfMenuObject(handle), m_pageContext(), unknownaf8(this), m_sequentialPlaySignal(nullptr), unknown1120(false), unknown1128(), unknown1140(4), unknown1144(0), unknown1170(0), unknown1174(),
      unknown1188(), m_menuBladeCreateCamera(nullptr), unknown1198(-1), unknown11a0(0), unknown11a8(nullptr), unknown11b0(0), unknown11b4(false), unknown11b8(0), unknown11c0(0), unknown11c4() {
  unknown1188 = unknown160();
  // Evidence: the game zeroes the sound handles in the member initialisers and stores them again after the camera (0x71003f5db4).
// __LINE__ must be 169 as in the original file: it is the line argument of operator new.
#line 169
  m_menuBladeCreateCamera = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuBladeCreateCamera();
  unknown11c4[0] = 0;
  unknown11c4[1] = 0;
  unknown11c4[2] = 0;
}

// Evidence: the game clears 0x1190 (the camera) without deleting it and releases the lists and cursors of the pages by hand (0x71003f5dcc).
GfMenuObjBladeCreate::~GfMenuObjBladeCreate() {
  m_menuBladeCreateCamera = nullptr;
  unknown1188 = nullptr;
  mm::mtl::safeRelease(unknown1160);
  mm::mtl::safeRelease(unknown1168);
  mm::mtl::safeRelease(unknown1150);
  mm::mtl::safeRelease(unknown1158);
  mm::mtl::safeRelease(unknown11a8);
}

// Evidence: the page listeners are 0x30 bytes (owner and page state), the model view 0xab8 bytes, the layer parameter of the event gives the limited item (BDAT_MNU_BLADE_CREATE), and the
// game builds and destroys an UIObjectAcc on the creation page (0x71003f81c8) without using it, kept as the local `creation`.
// The `{}` blocks around the layer parameter, the party setup, the cursor setting of the booster page and the radar graph setting are each measured: without one of them the stack slots of the
// later objects move and the function does not match (the cursor setting of the crystal page needs none and has none). The listeners are passed as created: the same function with a local for each
// matches too (1441 instructions), so the locals are not kept (P2).
void GfMenuObjBladeCreate::initialize() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  if (acc.isValid()) {
    acc.setDispChild(false, "TXT_guide");
    {
      GfMenuTypes::Param layerParam;
      if (getFSLayerParam(unknown20, layerParam)) {
        u8 *bdat = GfDataBdat::getFP(BDAT_MNU_BLADE_CREATE);
        if (bdat != nullptr) {
          u32 event = layerParam.get<OpenParam>().unknown00;
          if (event != 0) {
            unknown11b8 = Bdat::getVal(bdat, "limited_item", event).valueU16;
            unknown11bc = Bdat::getVal(bdat, "after_pt_in", event).valueU8 == 1;
          }
        }
        unknown11b4 = true;
        removeFSLayerParam(unknown20);
      }
    }
    m_pageContext.unknown00 = 0xff;
    m_pageContext.unknown04 = 0xff;
// __LINE__ must be 629 as in the original file: it is the line argument of operator new.
#line 629
    unknown028(acc, new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this, &m_pageContext));
// __LINE__ must be 630 as in the original file: it is the line argument of operator new.
#line 630
    unknown018(this, 0, new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DriverSelectListener(this, &m_pageContext));
// __LINE__ must be 631 as in the original file: it is the line argument of operator new.
#line 631
    unknown018(this, 1, new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) CrystalSelectListener(this, &m_pageContext));
// __LINE__ must be 632 as in the original file: it is the line argument of operator new.
#line 632
    unknown018(this, 2, new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) BoosterSelectListener(this, &m_pageContext));
// __LINE__ must be 633 as in the original file: it is the line argument of operator new.
#line 633
    unknown018(this, 3, new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ConfirmListener(this, &m_pageContext));
// __LINE__ must be 634 as in the original file: it is the line argument of operator new.
#line 634
    unknown018(this, 4, new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) CreationListener(this, &m_pageContext));
// __LINE__ must be 635 as in the original file: it is the line argument of operator new.
#line 635
    unknown018(this, 5, new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ResultListener(this, &m_pageContext));
    setFSInputObject(0, getPageObject(unknown18, 0, false));
    setFSInputObject(1, getPageObject(unknown18, 1, false));
    setFSInputObject(2, getPageObject(unknown18, 2, false));
    setFSInputObject(5, getPageObject(unknown18, 5, false));
// __LINE__ must be 643 as in the original file: it is the line argument of operator new.
#line 643
    m_pageContext.m_menuModelView = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuModelView(acc.searchChild("SCR_mdl_view"), 1);
    {
      GfMenuDriverList::PartySetup partySetup;
      partySetup.unknown14 = GfPartySelect::LIST_TYPE_UNKNOWN_2;
      partySetup.unknown18 = true;
      partySetup.m_setupParam.unknown08 = 4;
      m_pageContext.unknown40 = GfMenuDriverList::create();
      if (m_pageContext.unknown40 != nullptr) {
        if (unknown11b4) {
          MenuDriverInfo info;
          info.unknown00 = 1;
          m_pageContext.unknown40->setup(getAllocator(ALLOCATOR_UNKNOWN_0), partySetup.m_setupParam);
          m_pageContext.unknown40->addContents(info);
          GfMenuObjOperationInfo::open(0, 0, 0, 0);
        } else {
          m_pageContext.unknown40->setupFromParty(partySetup);
          for (u32 i = 0; i < m_pageContext.unknown40->getSize();) {
            if (m_pageContext.unknown40->getContents(i).unknown00 == 1 || m_pageContext.unknown40->getContents(i).unknown00 == 2 || m_pageContext.unknown40->getContents(i).unknown00 == 3 ||
                m_pageContext.unknown40->getContents(i).unknown00 == 6) {
              i++;
            } else {
              GfMenuDriverList *list = m_pageContext.unknown40;
              list->contents.erase(list->contents.begin() + i);
              list->subSize(1);
              list->contentsChanged = true;
            }
          }
          if (m_pageContext.unknown40->getSize() != 0) {
            m_pageContext.unknown40->setIndex(0);
            unknown11a0 = getDriverCameraIndex(m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00) * 5;
          }
        }
      }
    }
    m_pageContext.unknown48 = GfMenuItemList::create();
    m_pageContext.unknown50 = GfMenuItemList::create();
    {
      ui::UIObjectAcc driverSelect(getPageObject(unknown18, 0, false));
      GfMenuCharDataAdapter::createFromReferenceDriver(driverSelect.searchChild("TXT_dr_select_name"), 2, 0, false);
    }
    {
      ui::UIObjectAcc crystalSelect(getPageObject(unknown18, 1, false));
      mm::mtl::FixStr<32> name;
      unknown1150 = unknown026();
      unknown1150->pickupObject(crystalSelect.unknown10, "LAY_core_select_base@%02d", 1);
      ui::UICtrlCursorSelect::CursorSetting setting;
      setting.setType(0);
      setting.unknown18 = 0;
      unknown1158 = ui::UICtrlCursorSelect::create(crystalSelect.searchChild("IMG_core_select_cursor"), setting, unknown1150);
      GfMenuAdapterManager::beginAddAfter();
      for (u32 i = 0; i < unknown1150->getSize(); i++) {
        unknown027(crystalSelect, name, "TXT_core_sel_item_name@%02d", "LAY_core_sel_item@%02d", m_pageContext.unknown48, i);
        name.format("TXT_core_sel_item_num@%02d", i + 1);
        GfMenuItemAdapter::createFromList(crystalSelect.searchChild(name.c_str()), 3, m_pageContext.unknown48, i, true);
        name.format("TXT_core_sel_item_max@%02d", i + 1);
        GfMenuItemAdapter::createFromList(crystalSelect.searchChild(name.c_str()), 4, m_pageContext.unknown48, i, true);
        name.format("IMG_core_sel_item_icon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(crystalSelect.searchChild(name.c_str()), 2, m_pageContext.unknown48, i, true);
      }
      GfMenuAdapterManager::endAddAfter();
      GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_core_sel_scroll_bar"), m_pageContext.unknown48, "IMG_core_sel_scroll_base", true);
    }
    {
      ui::UIObjectAcc boosterSelect(getPageObject(unknown18, 2, false));
      mm::mtl::FixStr<32> name;
      unknown1160 = unknown026();
      unknown1160->pickupObject(boosterSelect.unknown10, "LAY_bst_select_base@%02d", 1);
      {
        ui::UICtrlCursorSelect::CursorSetting setting;
        setting.setType(0);
        setting.unknown18 = 0;
        unknown1168 = ui::UICtrlCursorSelect::create(boosterSelect.searchChild("IMG_bst_select_cursor"), setting, unknown1160);
      }
      for (u32 i = 0; i < unknown1160->getSize(); i++) {
        unknown027(boosterSelect, name, "TXT_bst_sel_item_name@%02d", "LAY_bst_sel_item@%02d", m_pageContext.unknown50, i);
        name.format("TXT_bst_sel_item_num@%02d", i + 1);
        GfMenuItemAdapter::createFromList(boosterSelect.searchChild(name.c_str()), 3, m_pageContext.unknown50, i, true);
        name.format("TXT_bst_sel_item_max@%02d", i + 1);
        GfMenuItemAdapter::createFromList(boosterSelect.searchChild(name.c_str()), 4, m_pageContext.unknown50, i, false);
        name.format("IMG_bst_sel_item_icon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(boosterSelect.searchChild(name.c_str()), 2, m_pageContext.unknown50, i, false);
      }
      GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_bst_sel_scroll_bar"), m_pageContext.unknown50, "IMG_bst_sel_scroll_base", true);
      ui::UIObjectAcc dialog(boosterSelect.unknown10, "LAY_bst_select_dialog");
      GfMenuReferenceAdapter::create(dialog.searchChild("TXT_bst_select_dialog_num"), unknown1188, true);
      setFSInputObject(6, dialog.unknown10);
// __LINE__ must be 838 as in the original file: it is the line argument of operator new.
#line 838
      unknown028(dialog, new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) BoosterNumListener(this));
    }
    {
      ui::UIObjectAcc idea(acc.unknown10, "LAY_dr_idea");
      mm::mtl::FixStr<32> name;
      {
        ui::UICtrlRadarGraph::Setting graphSetting = {};
        unknown11a8 = ui::UICtrlRadarGraph::create(idea.searchChild("POL_dr_idea_graph"), graphSetting);
      }
      for (u32 i = 0; i < 4; i++) {
        name.format("TXT_dr_idea_lv_num@%02d", i + 1);
        GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromReferenceDriver(idea.searchChild(name.c_str()), 0x22, 0, true);
        if (adapter != nullptr) {
          adapter->unknown79 = true;
          adapter->unknown80 = i;
        }
        unknown11a8->setNumberPlugin(i, idea.searchChild(name.c_str()));
        name.format("TXT_dr_idea_lv_category@%02d", i + 1);
        ui::UIObjectAcc category(idea.unknown10, name.c_str());
        if (category.isValid()) {
          category.setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_IDEACOLLAR_MS), i + 1));
        }
      }
// __LINE__ must be 885 as in the original file: it is the line argument of operator new.
#line 885
      unknown028(idea, new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) IdeagramListener(this));
    }
    {
      ui::UIObjectAcc result(acc.unknown10, "LAY_result");
      GfMenuCharDataAdapter::createFromReferenceBlade(result.searchChild("IMG_result_bl_img"), 0x36, 0, false);
    }
    {
      ui::UIObjectAcc creation(getPageObject(unknown18, 4, false));
    }
    disableFSInput();
    unknownaf8.unknown004(2);
    unknownaf8.unknown002(&GfMenuObjBladeCreate::seqStart);
    unknownaf8.unknown002(&GfMenuObjBladeCreate::seqWaitLoading);
    unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateDriverObj);
    unknownaf8.unknown002(&GfMenuObjBladeCreate::seqWaitLoading);
    unknownaf8.unknown002(&GfMenuObjBladeCreate::seqSetupDriverObj);
    unknownaf8.unknown002(&GfMenuObjBladeCreate::seqEnd);
    m_pageContext.m_menuCallContext = GfMenuCallContext::create();
    m_pageContext.unknown2c = false;
    GfMenuObject::initialize();
    if (!unknown11b4) {
      GfMenuObjMainMenu2::setCloseKeyEnable(false);
    }
  }
}

void GfMenuObjBladeCreate::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(unknown001, layerParam);
}

void GfMenuObjBladeCreate::openCreatedBladeName(GfMenuCallContext *context) { GfMenuObjBladeName::open(context); }

u32 GfMenuObjBladeCreate::getPageObject(u32 handle, u32 page, bool isSibling) {
  u32 object = 0;
  if (handle != 0 && page < 6) {
    ui::UIObjectAcc acc(handle);
    if (isSibling) {
      object = acc.searchSibiling(unknown002[page]);
    } else {
      object = acc.searchChild(unknown002[page]);
    }
  }
  return object;
}

void GfMenuObjBladeCreate::changePage(u32 handle, PageContext *context, u32 page, bool isSibling, bool isReturn) {
  ui::UIObjectAcc oldPage(getPageObject(handle, context->unknown00, isSibling));
  ui::UIObjectAcc newPage(getPageObject(handle, page, isSibling));
  ui::EventData event;
  if (newPage.isValid()) {
    event.unknown00 = 0x22;
    ui::UIManager::get()->requestObjectEvent(oldPage.unknown10, event, 0.0f);
    if (newPage.isValid()) {
      event.unknown00 = 0x21;
      ui::UIManager::get()->requestObjectEvent(newPage.unknown10, event, 0.0f);
    }
    context->unknown04 = context->unknown00;
    context->unknown00 = page;
    disableFSInput();
    if (isReturn) {
      context->m_menuModelView->popCamera(0.5f);
    }
    if (page == 0) {
      context->m_menuModelView->resetCamera(unknown1198, 0.0f);
    } else {
      context->m_menuModelView->pushCamera(unknown008[page] + unknown11a0, 0.5f);
    }
  }
}

u32 GfMenuObjBladeCreate::getDriverCameraIndex(u32 driver) {
  u32 index = 0;
  while (unknown004[index] != driver) {
    index++;
  }
  return index;
}

void GfMenuObjBladeCreate::nextPage(u32 handle, PageContext *context, bool isSibling) {
  u32 page = 0;
  switch (context->unknown00) {
  case 0:
    page = 1;
    break;
  case 1:
    page = 2;
    if (context->unknown2c) {
      page = 3;
    }
    break;
  case 2:
    page = 3;
    break;
  case 3:
    page = 4;
    break;
  case 4:
    page = 5;
    break;
  case 5:
    break;
  default:
    if (context->unknown00 != 0xff) {
      return;
    }
    break;
  }
  changePage(handle, context, page, isSibling, false);
}

void GfMenuObjBladeCreate::returnPage(u32 handle, PageContext *context, bool isSibling) {
  u32 page = 0;
  switch (context->unknown00) {
  case 1:
    break;
  case 2:
    page = 1;
    break;
  case 3:
    page = 1;
    if (!context->unknown2c) {
      page = 2;
    }
    break;
  case 4:
    page = 3;
    break;
  default:
    return;
  }
  changePage(handle, context, page, true, true);
}

void GfMenuObjBladeCreate::finalize() {
  if (m_pageContext.m_menuModelView != nullptr) {
    delete m_pageContext.m_menuModelView;
    m_pageContext.m_menuModelView = nullptr;
  }
  mm::mtl::safeRelease(m_pageContext.unknown40);
  mm::mtl::safeRelease(m_pageContext.unknown50);
  mm::mtl::safeRelease(m_pageContext.unknown48);
  mm::mtl::safeRelease(m_pageContext.unknown30);
  mm::mtl::safeRelease(m_pageContext.m_menuCallContext);
  GfMenuObject::finalize();
}

void GfMenuObjBladeCreate::update() {
  unknownaf8.unknown003();
  if (m_pageContext.m_menuModelView != nullptr) {
    m_pageContext.m_menuModelView->update();
  }
  GfMenuObject::update();
}

bool GfMenuObjBladeCreate::seqSetupCrystal() {
  u32 driver = m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00;
  unknown010(m_pageContext.m_menuModelView, driver, 1);
  unknown010(m_pageContext.m_menuModelView, driver, 2);
  mm::Vec3 scale;
  scale.z = 0.7f;
  scale.y = 0.7f;
  scale.x = 0.7f;
  GfMenuModelView::setObjectScale(unknown011(m_pageContext.m_menuModelView, 1), scale);
  GfMenuModelView::setObjectScale(unknown011(m_pageContext.m_menuModelView, 2), scale);
  GfMenuModelView::setObjectDisp(unknown011(m_pageContext.m_menuModelView, 2), false);
  unknown11c4[1] = GfMenuObjUtil::playSE("se_fld_allmap_706");
  refreshCrystalList();
  return true;
}

void GfMenuObjBladeCreate::refreshCrystalList() {
  if (unknown1150 != nullptr) {
    GfMenuItemList *crystals = m_pageContext.unknown48;
    if (crystals != nullptr) {
      for (u32 i = 0; i < unknown1150->getSize(); i++) {
        u32 item = crystals->getContents(crystals->getPageIndex(i)).unknown04;
        if (item != 0) {
          mm::mtl::FixStr<32> name;
          name.format("TXT_core_sel_item_name@%02d", i + 1);
          ui::UIObjectAcc acc(unknown18, name.c_str());
          if (!isValidCrystal(item)) {
            GfMenuObjUtil::setColMulandAdd(acc.unknown10, "txt_disable");
            acc.setBorderWeight(1.0f);
            name.format("TXT_core_sel_item_num@%02d", i + 1);
            ui::UIObjectAcc(unknown18, name.c_str()).setBorderWeight(1.0f);
            name.format("TXT_core_sel_item_max@%02d", i + 1);
            ui::UIObjectAcc(unknown18, name.c_str()).setBorderWeight(1.0f);
            name.format("TXT_core_sel_item_slash@%02d", i + 1);
            ui::UIObjectAcc(unknown18, name.c_str()).setBorderWeight(1.0f);
          } else {
            GfMenuObjUtil::setColDefault(acc.unknown10);
            acc.setBorderWeight(-0.5f);
            name.format("TXT_core_sel_item_num@%02d", i + 1);
            ui::UIObjectAcc(unknown18, name.c_str()).setBorderWeight(-0.5f);
            name.format("TXT_core_sel_item_max@%02d", i + 1);
            ui::UIObjectAcc(unknown18, name.c_str()).setBorderWeight(-0.5f);
            name.format("TXT_core_sel_item_slash@%02d", i + 1);
            ui::UIObjectAcc(unknown18, name.c_str()).setBorderWeight(-0.5f);
          }
        }
      }
      if (unknown013(m_pageContext.m_menuModelView, 1) && unknown013(m_pageContext.m_menuModelView, 2)) {
        if (!isValidCrystal(crystals->getContents(crystals->getIndex(false)).unknown04)) {
          {
            GfMenuModelView::CtrlParam param(unknown011(m_pageContext.m_menuModelView, 1), 0.1f, false);
            param.setMoveAlpha(0.0f);
            m_pageContext.m_menuModelView->startObjectCtrl(param);
          }
          {
            GfMenuModelView::CtrlParam param(unknown011(m_pageContext.m_menuModelView, 2), 0.1f, false);
            param.setMoveAlpha(1.0f);
            m_pageContext.m_menuModelView->startObjectCtrl(param);
          }
        } else {
          {
            GfMenuModelView::CtrlParam param(unknown011(m_pageContext.m_menuModelView, 1), 0.1f, false);
            param.setMoveAlpha(1.0f);
            m_pageContext.m_menuModelView->startObjectCtrl(param);
          }
          {
            GfMenuModelView::CtrlParam param(unknown011(m_pageContext.m_menuModelView, 2), 0.1f, false);
            param.setMoveAlpha(0.0f);
            m_pageContext.m_menuModelView->startObjectCtrl(param);
          }
        }
      }
    }
  }
}

void GfMenuObjBladeCreate::stopAllSound() {
  for (int i = 0; i < 3; i++) {
    if (unknown11c4[i] != 0) {
      GfMenuObjUtil::stopSE(unknown11c4[i], 0.0f);
    }
  }
}

bool GfMenuObjBladeCreate::seqStart() {
  ml::ScnRenderDrSysParmAcc acc;
  if (!acc.isSeamMapRead()) {
    unknown1120 = false;
    GfMenuSoundManager::fadeOutFieldBgm(0.5f);
    return true;
  }
  return false;
}

bool GfMenuObjBladeCreate::seqWaitLoading() { return !m_pageContext.m_menuModelView->isLoading(); }

bool GfMenuObjBladeCreate::seqEnd() {
  enableFSInput(m_pageContext.unknown00);
  return true;
}

bool GfMenuObjBladeCreate::seqSave() {
  unknown11b0 = GfReqCommand::reqSave(SAVESLOT_UNKNOWN_22);
  GfMenuObjFade::dispSaving(true, 0);
  return true;
}

bool GfMenuObjBladeCreate::seqSaveWait() {
  if (!GfReqManager::isValid(unknown11b0)) {
    GfMenuObjFade::dispSaving(false, 0);
    unknown11b0 = -1;
    return true;
  }
  return false;
}

bool GfMenuObjBladeCreate::seqResultStart() {
  unknown1120 = false;
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqResultConfirm);
  return true;
}

bool GfMenuObjBladeCreate::seqCreateStartSE() {
  if (unknown11c4[1] != 0) {
    GfMenuObjUtil::stopSE(unknown11c4[1], 0.0f);
    unknown11c4[1] = 0;
  }
  unknown11c4[2] = GfMenuObjUtil::playSE("se_fld_allmap_715");
  return true;
}

bool GfMenuObjBladeCreate::seqCreatePlayJingle() {
  GfMenuObjUtil::stopBGM(unknown11c0, 1.0f);
  unknown11c0 = 0;
  return true;
}

// Game address 0x71003f8544. Spreads the drivers of the creation on a circle (the angle between two drivers is 360 / count degrees), turns the five cameras of each driver by the same angle
// and sets the default camera of the page from the first driver. Evidence for the forms (483 instructions, each measured):
// - `count` is read once before the loop (0x71003f85a8 stores the result of the second getSize, 0x71003f8678 compares the reloaded value with 2 in every iteration); inline in the
//   condition the loop calls getSize again (482 instructions).
// - The transform starts as {Vec3::zero, Quat::identity} before the loop (0x71003f85ac..85d8). Per driver the quaternion identity is stored first (0x71003f86c8), then the point
//   (0, 0, 1) (0x71003f86d0..86d4), before the first sinf call (0x71003f8718): with the stores after the matrix the point folds to constants (474 instructions).
// - The matrix is the identity copied into a local first, then `matrix = matrix * rotationMatrix` (`Mat44::identity * rotationMatrix` gives 457 instructions), the point goes through
//   the shared helper unknown029 and the quaternion is mm::unknown005 (the same forms as seqCreateBuildBlade and GfMenuBladeCreateCamera::update).
// - The camera index is the inlined getDriverCameraIndex (search loop 0x71003f8970..8988). Its result is compared with -1 before the camera loop (`cbz w8` at 0x71003f898c on the
//   trip count of the search loop, which skips the loop): without the guard it has 478 instructions, and with `camera = index * 5` before the guard the game's three counters of the
//   loop (w21 = -j, w27 = running camera, w20 = first camera) do not come out (483 instructions, other spill slots).
// - The first camera of a driver reads the position and rotation of camera 0 (0x71003f89f0..8a18: getCameraPos/getCameraRot with a zero argument), the others their own
//   (0x71003f89ac..89d4); the camera that is written is the driver's own in both cases (`target`, a select of w20 and w27 that the game keeps). The own camera is `camera + j`
//   (a running `current++` next to j gives 476 instructions).
// - `position` and `rotation` are locals of the loop body; declared before the loop (together with `for (u32 j ...)`) the loop does not match (483 instructions, one spill slot of
//   the matrix elements differs).
// - The default camera of the page is read from the first driver (getContents(0), without getIndex, 0x71003f8b64..8b94) in a block that ends after setDefault: the temporaries
//   then share the stack slots of the loop (frame 304 bytes, 320 without the block).
bool GfMenuObjBladeCreate::seqCreateDriverObj() {
  unknown119c = 360.0f / m_pageContext.unknown40->getSize() * mm::DEG_TO_RAD;
  u32 count = m_pageContext.unknown40->getSize();
  fw::Transform transform;
  transform.unknown00 = mm::Vec3::zero;
  transform.unknown10 = mm::Quat::identity;
  for (u32 i = 0; i < m_pageContext.unknown40->getSize(); i++) {
    u32 driver = m_pageContext.unknown40->getContents(i).unknown00;
    if (count > 1) {
      f32 angle = i * unknown119c;
      transform.unknown10 = mm::Quat::identity;
      transform.unknown00.x = 0.0f;
      transform.unknown00.y = 0.0f;
      transform.unknown00.z = 1.0f;
      mm::Mat44 matrix = mm::Mat44::identity;
      mm::Mat44 rotationMatrix;
      rotationMatrix.setRotY(angle);
      matrix = matrix * rotationMatrix;
      unknown029(transform.unknown00, matrix);
      mm::unknown005(transform.unknown10, mm::Vec3(0.0f, angle, 0.0f));
      u32 index = getDriverCameraIndex(driver);
      if (index != 0xffffffff) {
        u32 camera = index * 5;
        for (u32 j = 0; j < 5; j++) {
          mm::Vec3 position;
          mm::Vec3 rotation;
          u32 target;
          if (j == 0) {
            target = camera;
            position = m_pageContext.m_menuModelView->getCameraPos(0);
            rotation = m_pageContext.m_menuModelView->getCameraRot(0);
          } else {
            target = camera + j;
            position = m_pageContext.m_menuModelView->getCameraPos(target);
            rotation = m_pageContext.m_menuModelView->getCameraRot(target);
          }
          position.z += 1.0f;
          unknown029(position, matrix);
          m_pageContext.m_menuModelView->setCameraPos(target, position);
          m_pageContext.m_menuModelView->setCameraRotY(target, angle + rotation.y);
        }
      }
    }
    m_pageContext.m_menuModelView->addDriverObject(driver, transform);
  }
  {
    u32 driver = m_pageContext.unknown40->getContents(0).unknown00;
    u32 camera = getDriverCameraIndex(driver) * 5;
    mm::Vec3 position = m_pageContext.m_menuModelView->getCameraPos(camera);
    mm::Vec3 rotation = m_pageContext.m_menuModelView->getCameraRot(camera);
    if (m_pageContext.unknown40->getSize() == 2) {
      m_menuBladeCreateCamera->setRotOffsetY(-8.0f * mm::DEG_TO_RAD);
      position.x += 0.1f;
    }
    m_menuBladeCreateCamera->setDefault(position, rotation);
  }
  unknown1198 = m_pageContext.m_menuModelView->addCamera(m_menuBladeCreateCamera);
  m_pageContext.m_menuModelView->pushCamera(unknown1198, 0.0f);
  ui::UIObjectAcc acc(unknown18, "LAY_dr_select_arrow");
  acc.setDisp(m_pageContext.unknown40->getSize() > 1);
  return true;
}

bool GfMenuObjBladeCreate::seqSetupDriverObj() {
  {
    ui::UIObjectAcc main(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    GfMenuObjUtil::startCtrl(main.unknown10, param, nullptr);
  }
  changePage(unknown18, &m_pageContext, 0, false, false);
  m_pageContext.m_menuModelView->playEffect(8, "bc_30_000", mm::Vec3(0.0f, 0.0f, 0.0f), reinterpret_cast<GF_OBJ_HANDLE *>(-1));
  unknown11c4[0] = GfMenuObjUtil::playSE("se_fld_allmap_701");
  return true;
}

bool GfMenuObjBladeCreate::seqResultBladeFull() {
  if (!unknown1120) {
    GfMenuManager::openCommonWindow(8);
    unknown1120 = true;
  }
  if (!GfMenuManager::isOpenCommonWindow()) {
    unknownaf8.unknown002(&GfMenuObjBladeCreate::seqResultEnd);
    if (m_pageContext.m_menuCallContext != nullptr) {
      m_pageContext.m_menuCallContext->release();
      m_pageContext.m_menuCallContext = nullptr;
    }
    return true;
  }
  return false;
}
bool GfMenuObjBladeCreate::seqResultConfirm() {
  if (!unknown1120) {
    if (unknown11b4 && unknown11bc) {
      u32 driver = m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00;
      SCOM_PARTY_ADD::addBlade(m_pageContext.unknown28, driver, 1);
      if (!unknown11b4) {
        GfMenuObjMainMenu2::setCloseKeyEnable(true);
      }
      GfMenuObjOperationInfo::close();
      GfMenuObject::returnFSSubLayer(this);
      return true;
    }
    GfMenuManager::openCommonWindow(7);
    unknown1120 = true;
  }
  if (GfMenuManager::isOpenCommonWindow()) {
    return false;
  }
  s16 result = GfMenuManager::getCommonWindowResult();
  if (result != 0) {
    if (!unknown11b4) {
      unknownaf8.unknown002(&GfMenuObjBladeCreate::seqResultEnd);
    } else {
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
      GfMenuObjOperationInfo::close();
      GfMenuObject::returnFSSubLayer(this);
    }
    unknown1120 = false;
    return true;
  }
  if (!unknown11b4 || unknown11b8 == 0) {
    GfMenuObjBladeSet2::setCloseToReturn();
  } else {
    GfMenuObjBladeSet2::setCloseToFSClose();
  }
  if (unknown11b4) {
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
  }
  GfMenuObject::changeFSSubLayer(unknown18, GfMenuFullScreen::getLayerGroup(unknown20), GfMenuObject::getMenuLayerID(0x1e), true);
  return true;
}

bool GfMenuObjBladeCreate::seqCreateCtrlBlade() {
  u32 blade = unknown1128.front();
  switch (unknown1144) {
  case 0: {
    m_pageContext.m_menuModelView->setObjectVanishRatio(m_pageContext.m_menuModelView->findGfObj(4, blade), 1.0f);
    m_pageContext.m_menuModelView->setObjectVanishParam(m_pageContext.m_menuModelView->findGfObj(4, blade), 9);
    GfMenuModelView::CtrlParam param(m_pageContext.m_menuModelView->findGfObj(4, blade), 0.3f, false);
    param.setAddPosY(0.2f);
    if (unknown1128.size() == 1) {
      param.setMoveVanish(0.5f);
    } else {
      param.setMoveVanish(0.7f);
    }
    m_pageContext.m_menuModelView->startObjectCtrl(param);
    GF_OBJ_HANDLE *driver = m_pageContext.m_menuModelView->findGfObj(unknown003, m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00);
    if (unknown1148 == 0) {
      m_pageContext.m_menuModelView->playEffectFromCAS(1, "bc_20_010", driver);
      unknown1148++;
    } else if (unknown1128.size() > 1) {
      m_pageContext.m_menuModelView->playEffectFromCAS(unknown1148 + 1, "bc_20_010", driver);
      unknown1148++;
    } else {
      GF_OBJ_HANDLE *bladeObj = m_pageContext.m_menuModelView->findGfObj(4, blade);
      m_pageContext.m_menuModelView->playEffectFromCAS(5, "bc_20_020", driver);
      m_pageContext.m_menuModelView->playEffectFromCAS(7, "bc_20_040", bladeObj);
    }
    GfMenuObjUtil::playVibration(fw::VIBRATION_ID_UNKNOWN_16, 1.0f);
    GfMenuObjUtil::playSE("se_fld_allmap_712");
    unknown114c = 15;
    break;
  }
  case 1: {
    GfMenuModelView::CtrlParam param(m_pageContext.m_menuModelView->findGfObj(4, blade), 0.4f, false);
    param.setAddPosY(0.2f);
    m_pageContext.m_menuModelView->startObjectCtrl(param);
    break;
  }
  case 2: {
    GfMenuModelView::CtrlParam param(m_pageContext.m_menuModelView->findGfObj(4, blade), 0.3f, false);
    if (unknown1128.size() == 1) {
      param.setAddPosY(-0.5f);
      param.setMoveSclX(0.001f);
      param.setMoveSclZ(0.001f);
    } else {
      param.setAddPosY(0.2f);
      param.setMoveVanish(1.0f);
      GfMenuObjUtil::playSE("se_fld_allmap_713");
    }
    m_pageContext.m_menuModelView->startObjectCtrl(param);
    break;
  }
  }
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateWaitBlade);
  return true;
}

bool GfMenuObjBladeCreate::seqCreateWaitBlade() {
  u32 blade = unknown1128.front();
  GfMenuModelView *view = m_pageContext.m_menuModelView;
  if (view->isObjectCtrlBusy(view->findGfObj(4, blade))) {
    return false;
  }
  if (unknown1144 < 2) {
    unknown1144++;
    unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateCtrlBlade);
  } else {
    m_pageContext.m_menuModelView->delGfObj(4, blade);
    unknown1128.erase(unknown1128.begin());
    if (!unknown1128.empty()) {
      unknown1144 = 0;
      unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateBuildBlade);
    } else {
      GfMenuFade::setFade(2, 60, mm::Col4::white);
      GfMenuObjUtil::playSE("se_fld_allmap_714");
      unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateWaitFade);
      unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreatePlayJingle);
      unknownaf8.unknown004(30);
      unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreatePlayBgmAfter);
      unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateStartEvent);
      unknown1128.clear();
    }
  }
  return true;
}

bool GfMenuObjBladeCreate::seqCreateStart() {
  GF_OBJ_HANDLE *driverObj = m_pageContext.m_menuModelView->findGfObj(unknown003, m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00);
  GfMenuModelView *view = m_pageContext.m_menuModelView;
  {
    mm::Vec3 position(0.0f, 0.0f, 0.0f);
    view->playEffect(6, "bc_20_030", position, unknown011(view, 1));
  }
  m_pageContext.m_menuModelView->playEffectFromCAS(0, "bc_20_000", driverObj);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateSetup);
  int driver = m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00;
  for (u32 i = 0; i < m_pageContext.unknown40->getSize(); i++) {
    if (driver != m_pageContext.unknown40->getContents(i).unknown00) {
      GfObjAcc acc(m_pageContext.m_menuModelView->findGfObj(unknown003, m_pageContext.unknown40->getContents(i).unknown00));
      acc.setDisp(OBJDISP_UNKNOWN_0, false);
    }
  }
  const char *motion = nullptr;
  if (driver >= 1 && driver <= 6) {
    motion = unknown012[driver - 1];
  }
  if (motion != nullptr) {
    fw::Transform &transform = GfMenuModelView::getObjectTransform(m_pageContext.m_menuModelView->findGfObj(unknown003, driver));
    mm::Vec3 rotation = mm::quatToEuler(transform.unknown10);
    m_pageContext.m_menuModelView->playCameraMotion(motion, transform.unknown00, rotation.y);
  }
  return true;
}

bool GfMenuObjBladeCreate::seqCreateStartEvent() {
  for (u32 i = 0; i < m_pageContext.unknown40->getSize(); i++) {
    u32 id = m_pageContext.unknown40->getContents(i).unknown00;
    GfObjAcc(m_pageContext.m_menuModelView->findGfObj(unknown003, id)).setDisp(OBJDISP_UNKNOWN_0, false);
  }
  u32 event = GfDataBlade::getCreateEvent(m_pageContext.unknown28);
#line 2938
  m_sequentialPlaySignal = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfSequentialPlaySignal();
  GfPlayFactory::createBlEvent(event, 1, m_pageContext.unknown28, m_sequentialPlaySignal);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateWaitEvent);
  m_pageContext.m_menuModelView->delGfObj(unknown009, m_pageContext.m_menuModelView->getMapObjID(1));
  m_pageContext.m_menuModelView->delGfObj(unknown009, m_pageContext.m_menuModelView->getMapObjID(2));
  m_pageContext.m_menuModelView->stopEffect(6);
  m_pageContext.m_menuModelView->stopEffect(7);
  m_pageContext.m_menuModelView->stopEffect(0);
  m_pageContext.m_menuModelView->stopEffect(unknown1148 + 1);
  if (unknown11c4[2] != 0) {
    GfMenuObjUtil::stopSE(unknown11c4[2], 0.0f);
    unknown11c4[2] = 0;
  }
  return true;
}

bool GfMenuObjBladeCreate::seqCreateWaitEvent() {
  if (m_sequentialPlaySignal->isActive) {
    return false;
  }
  if (m_sequentialPlaySignal != nullptr) {
    delete m_sequentialPlaySignal;
    m_sequentialPlaySignal = nullptr;
  }
  GfMenuObjBladeName::close();
  nextPage(unknown18, &m_pageContext, false);
  return true;
}

void GfMenuObjBladeCreate::setGuideText(u32 id) {
  ui::UIObjectAcc acc(unknown18, "TXT_guide");
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
}

bool GfMenuObjBladeCreate::seqCreatePlayBgmAfter() { return true; }

bool GfMenuObjBladeCreate::isValidCrystal(u32 item) {
  int driver = m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00;
  return GfItemUtil::isValidCrystal(item) && (item != ITEM_UNKNOWN_45005 || driver == 6);
}

u32 GfMenuObjBladeCreate::getInvalidCrystalMsgID(u32 item) {
  int driver = m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00;
  u32 message;
  if (item == ITEM_UNKNOWN_45005 && driver != 6) {
    message = 0xd4;
  } else {
    message = 0;
    if (!GfItemUtil::isValidCrystal(item)) {
      message = 0xa9;
    }
  }
  return message;
}

void GfMenuObjBladeCreate::dispGuideText(bool isDisp) {
  ui::UIObjectAcc acc(unknown18, "LAY_guide");
  acc.setDisp(isDisp);
}

bool GfMenuObjBladeCreate::seqCreateSetup() {
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateStartDriver);
  unknownaf8.unknown004(120);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateStartSE);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateWaitDriver);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateWaitFade);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateBuildBlade);
  unknown1148 = 0;
  return true;
}

bool GfMenuObjBladeCreate::seqCreateStartDriver() {
  GfMenuModelView *view = m_pageContext.m_menuModelView;
  GF_OBJ_HANDLE *driver = view->findGfObj(unknown003, m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00);
  view->sendObjectCommand(driver, "C_hold_00");
  GfMenuObjUtil::playSE("se_fld_allmap_711");
  return true;
}

bool GfMenuObjBladeCreate::seqCreateWaitDriver() {
  u32 id = m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00;
  GfMenuModelView *view = m_pageContext.m_menuModelView;
  GF_OBJ_HANDLE *driver = view->findGfObj(unknown003, id);
  if (strcmp(view->getObjectAnimationState(driver), "S_hold_01") == 0) {
    GfMenuFade::setFade(2, 30, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
    return true;
  }
  return false;
}

bool GfMenuObjBladeCreate::seqCreateWaitFade() { return !GfMenuManager::isFading(); }

// Game address 0x71003fc7e0. The blade appears at the effect point EFP_SYS_050 of the driver, rotated by the driver's rotation.
// Evidence for the forms (298 instructions, each measured):
// - The identity matrix is copied into a local before the quaternion matrix is built: its loads then rank before the quaternion loads, which gives the
//   game's operand order (identity element on the left, `t3 + (t2 + (t1 + t0))`); `Mat44::identity * rotation` gives the other order (315 instructions).
// - The offset is stored component by component in both arms (SimplifyCFG sinks the equal x and y stores): a `Vec3(0, 0, select)` temporary turns the
//   select into an integer select (303 instructions).
// - The point goes through the shared helper unknown029 (the call forms measured there).
// - The first store of the quaternion is the identity (0x71003fc89c, P3), then the driver's quaternion (0x71003fc8a4).
// - Single-use locals (P2, each measured inline): `driver` is read before the model view is loaded (0x71003fc87c then 0x71003fc880), inline in the findGfObj call it gives 299 instructions;
//   `driverTransform` is the result of the call at 0x71003fc88c, read after the identity copy (0x71003fc8a4), inline it does not match (298 instructions, other schedule); `blade` is loaded
//   right after that call (0x71003fc894), inline at addBladeObject it gives 297 instructions; `driver2` is read before the model view is loaded (0x71003fc948 then 0x71003fc94c), inline
//   it gives 301 instructions.
bool GfMenuObjBladeCreate::seqCreateBuildBlade() {
  u32 driver = m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00;
  fw::Transform &driverTransform = GfMenuModelView::getObjectTransform(m_pageContext.m_menuModelView->findGfObj(unknown003, driver));
  u32 blade = unknown1128.front();
  fw::Transform transform;
  transform.unknown10 = mm::Quat::identity;
  transform.unknown10 = driverTransform.unknown10;
  if (m_pageContext.unknown40->getSize() == 1) {
    transform.unknown00.x = 0.0f;
    transform.unknown00.y = 0.0f;
    transform.unknown00.z = 0.0f;
  } else {
    transform.unknown00.x = 0.0f;
    transform.unknown00.y = 0.0f;
    transform.unknown00.z = 1.0f;
  }
  mm::Vec3 point;
  u32 driver2 = m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00;
  if (GfMenuModelView::getObjectEffectPoint(m_pageContext.m_menuModelView->findGfObj(unknown003, driver2), "EFP_SYS_050", point)) {
    transform.unknown00 += point;
  }
  mm::Mat44 matrix = mm::Mat44::identity;
  mm::Mat44 rotation;
  mm::unknown001(rotation, transform.unknown10);
  matrix = matrix * rotation;
  unknown029(transform.unknown00, matrix);
  m_pageContext.m_menuModelView->addBladeObject(blade, transform);
  unknown1144 = 0;
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqWaitLoading);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateCtrlBlade);
  return true;
}

void GfMenuObjBladeCreate::updateIdea(bool isSave) {
  int levels[4] = {};
  GfMenuReference::resetDriverAddIdeaLv();
  if (m_pageContext.unknown00 > 1 && unknown1188->unknown0c > 0) {
    int idea = m_pageContext.unknown50->getContents(m_pageContext.unknown50->getIndex(false)).unknown04;
    int index = idea - Bdat::getIdTop(GfDataBdat::getFP(BDAT_ITM_BOOSTER_LIST));
    int level = unknown1188->unknown0c;
    levels[index] = level;
    if (isSave) {
      int slot = m_pageContext.unknown50->getIndex(false);
      unknown1174[slot] = level;
    }
  }
  for (u32 i = 0; i < 4; i++) {
    GfMenuReference::setDriverAddIdeaLv(i, levels[i]);
  }
}

bool GfMenuObjBladeCreate::seqResultAppearBlade() {
  u32 driver = m_pageContext.unknown40->getContents(m_pageContext.unknown40->getIndex(false)).unknown00;
  u32 blade = m_pageContext.unknown28;
  GfMenuModelView::getObjectTransform(m_pageContext.m_menuModelView->findGfObj(4, blade)).unknown00.z = -1.0f;
  GfMenuModelView::CtrlParam param(m_pageContext.m_menuModelView->findGfObj(4, blade), 0.5f, false);
  param.setMovePosX(-1.0f, 1.0f);
  m_pageContext.m_menuModelView->startObjectCtrl(param);
  unknown006(m_pageContext.m_menuModelView, driver, GfDataBlade::getBladeWpnType(blade));
  unknown007(m_pageContext.m_menuModelView, driver);
  return true;
}

bool GfMenuObjBladeCreate::seqResultEnd() {
  u32 blade = m_pageContext.unknown28;
  m_pageContext.m_menuModelView->delGfObj(4, blade);
  m_pageContext.m_menuModelView->stopCameraMotion();
  nextPage(unknown18, &m_pageContext, false);
  for (u32 i = 0; i < m_pageContext.unknown40->getSize(); i++) {
    u32 id = m_pageContext.unknown40->getContents(i).unknown00;
    GfObjAcc(m_pageContext.m_menuModelView->findGfObj(unknown003, id)).setDisp(OBJDISP_UNKNOWN_0, true);
  }
  return true;
}

void GfMenuObjBladeCreate::DriverSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case 6: {
    // Locals placing the loads of the event fields (ruling of 2026-11-13, member reads): the game reads the three before setIndex; at their use the loads move (measured).
    int index = event.unknown08;
    u32 prev = event.unknown0c;
    u8 direction = event.unknown10;
    m_pageContext->unknown40->setIndex(index);
    GfMenuReference::setReferenceDriverID(0, m_pageContext->unknown40->getContents(m_pageContext->unknown40->getIndex(false)).unknown00);
    if (index == -1 || prev == -1) {
      break;
    }
    m_menuObjBladeCreate->unknown11a0 = getDriverCameraIndex(m_pageContext->unknown40->getContents(m_pageContext->unknown40->getIndex(false)).unknown00) * 5;
    if (index == prev) {
      break;
    }
    m_menuObjBladeCreate->m_menuBladeCreateCamera->setRotY(m_menuObjBladeCreate->unknown119c * index, direction, 0.25f);
    GfMenuObjUtil::playSECommonTab();
    break;
  }
  case 0x22:
    unknown015(acc.unknown10);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(0);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
      if (m_menuObjBladeCreate->unknown11b4) {
        GfMenuObject::setInputActionEnable(acc.unknown10, 2, false);
      }
      GfMenuObject::setupInputSelectionFromList(acc.unknown10, *m_pageContext->unknown40);
    }
    break;
  case 8:
    if (event.unknown0c == 1) {
      m_menuObjBladeCreate->nextPage(acc.unknown10, m_pageContext, true);
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      m_pageContext->m_menuModelView->sendObjectCommand(
          m_pageContext->m_menuModelView->findGfObj(unknown003, m_pageContext->unknown40->getContents(m_pageContext->unknown40->getIndex(false)).unknown00), "C_reachout_00");
      switch (m_pageContext->unknown40->getContents(m_pageContext->unknown40->getIndex(false)).unknown00) {
      case 1:
        GfMenuObjUtil::playSE("se_fld_allmap_702");
        break;
      case 2:
        GfMenuObjUtil::playSE("se_fld_allmap_703");
        break;
      case 3:
        GfMenuObjUtil::playSE("se_fld_allmap_705");
        break;
      case 6:
        GfMenuObjUtil::playSE("se_fld_allmap_704");
        break;
      }
      GfMenuItemList::ItemBoxSetup setup;
      setup.unknown14 = ItemType::ITEM_TYPE_UNKNOWN_11;
      setup.m_setupParam.unknown08 = m_menuObjBladeCreate->unknown1150->getSize();
      setup.m_setupParam.unknown10 = true;
      if (m_menuObjBladeCreate->unknown11b8 == 0) {
        m_pageContext->unknown48->setupFromBox(setup);
        m_pageContext->unknown48->setIndex(0);
      } else {
        MenuItemInfo info;
        info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_11;
        info.unknown04 = m_menuObjBladeCreate->unknown11b8;
        info.unknown08 = 1;
        m_pageContext->unknown48->setup(getAllocator(ALLOCATOR_UNKNOWN_0), setup.m_setupParam);
        m_pageContext->unknown48->addItem(info, false);
      }
    } else if (event.unknown0c == 2) {
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      GfMenuObject::returnFSSubLayer(m_menuObjBladeCreate);
    }
    GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    break;
  case 0x21:
    GfMenuReference::setReferenceDriverID(0, m_pageContext->unknown40->getContents(m_pageContext->unknown40->getIndex(false)).unknown00);
    GfMenuReference::setReferenceBladeID(0, 0);
    m_menuObjBladeCreate->setGuideText(0x27);
    {
      ui::UIObjectAcc guide(m_menuObjBladeCreate->unknown18, "LAY_guide");
      guide.setDisp(true);
    }
    unknown014(acc.unknown10);
    if (!m_menuObjBladeCreate->unknown11b4) {
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
    }
    m_pageContext->m_menuModelView->sendObjectCommand(m_pageContext->m_menuModelView->findGfObj(unknown003, m_pageContext->unknown40->getContents(m_pageContext->unknown40->getIndex(false)).unknown00),
                                                      "C_idle");
    if (m_menuObjBladeCreate->unknown11c0 == 0) {
      m_menuObjBladeCreate->unknown11c0 = GfMenuObjUtil::playBGM(0x14, false, CATEGORY_MENU_BGM);
    }
    break;
  }
}

void GfMenuObjBladeCreate::CrystalSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(1);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    }
    break;
  case 6: {
    // Locals placing the loads of the event fields (ruling of 2026-11-13, member reads): the game reads both before setIndex; at their use the loads move (measured).
    u32 index = event.unknown08;
    u32 prev = event.unknown0c;
    m_pageContext->unknown48->setIndex(index);
    m_menuObjBladeCreate->unknown1150->setIndex(m_pageContext->unknown48->getIndex(true));
    m_menuObjBladeCreate->refreshCrystalList();
    if (prev != 0xffffffff && index != prev) {
      GfMenuObjUtil::playSECommonCursor();
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      if (event.unknown08 == 0xffffffff) {
        GfMenuObjUtil::playSECommon(2);
        break;
      }
      u32 item = m_pageContext->unknown48->getContents(m_pageContext->unknown48->getIndex(false)).unknown04;
      if (!m_menuObjBladeCreate->isValidCrystal(item)) {
        u32 message = m_menuObjBladeCreate->getInvalidCrystalMsgID(item);
        if (message != 0) {
          GfMenuManager::openCommonWindow(message);
        } else {
          GfMenuObjUtil::playSECommon(2);
        }
      } else {
        m_pageContext->unknown2c = false;
        if (!GfBladeManager::isBindRareBladeCrystal(item)) {
          if (GfDataBlade::getEnableCountForCreateBlade() == 0) {
            GfMenuObjUtil::playSECommon(2);
            GfMenuManager::openCommonWindow(0xbe);
            break;
          }
        } else {
          m_pageContext->unknown2c = true;
        }
        GfMenuItemList::ItemBoxSetup setup;
        setup.unknown14 = ItemType::ITEM_TYPE_UNKNOWN_12;
        setup.m_setupParam.unknown08 = m_menuObjBladeCreate->unknown1160->getSize();
        m_pageContext->unknown50->setupFromBox(setup);
        m_pageContext->unknown50->setIndex(0);
        m_pageContext->unknown50->sort(3, true);
        if (m_pageContext->unknown50->getSize() == 0) {
          m_pageContext->unknown2c = true;
        }
        m_menuObjBladeCreate->nextPage(acc.unknown10, m_pageContext, true);
        GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      }
    } else if (event.unknown0c == 2) {
      m_pageContext->m_menuModelView->delGfObj(unknown009, m_pageContext->m_menuModelView->getMapObjID(1));
      m_pageContext->m_menuModelView->delGfObj(unknown009, m_pageContext->m_menuModelView->getMapObjID(2));
      if (m_menuObjBladeCreate->unknown11c4[1] != 0) {
        GfMenuObjUtil::stopSE(m_menuObjBladeCreate->unknown11c4[1], 0.0f);
        m_menuObjBladeCreate->unknown11c4[1] = 0;
      }
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      m_menuObjBladeCreate->returnPage(acc.unknown10, m_pageContext, true);
    }
    GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    break;
  case 0x21:
    if (m_pageContext->unknown48->getSize() == 0) {
      GfMenuObject::setupInputSelection(acc.unknown10, -1, 0);
      acc.setDispChild(false, "IMG_core_select_cursor");
    } else {
      acc.setDispChild(true, "IMG_core_select_cursor");
      if (m_pageContext->unknown04 == 0) {
        GfMenuObject::resetInputSelection(acc.unknown10);
      }
      GfMenuObject::setupInputSelectionFromList(acc.unknown10, *m_pageContext->unknown48);
      m_menuObjBladeCreate->refreshCrystalList();
      if (!unknown013(m_pageContext->m_menuModelView, 1)) {
        m_pageContext->m_menuModelView->addMapObjObject(1);
        m_pageContext->m_menuModelView->addMapObjObject(2);
        m_menuObjBladeCreate->unknownaf8.unknown005();
        m_menuObjBladeCreate->unknownaf8.unknown002(&GfMenuObjBladeCreate::seqWaitLoading);
        m_menuObjBladeCreate->unknownaf8.unknown002(&GfMenuObjBladeCreate::seqSetupCrystal);
      }
    }
    unknown014(acc.unknown10);
    m_menuObjBladeCreate->setGuideText(0x28);
    break;
  case 0x22:
    unknown015(acc.unknown10);
    break;
  }
}

void GfMenuObjBladeCreate::BoosterSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(2);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      u32 prev = event.unknown0c;
      m_menuObjBladeCreate->unknown1160->setIndex(index);
      if (static_cast<int>(index) < static_cast<int>(m_pageContext->unknown50->getSize())) {
        m_pageContext->unknown50->setIndex(index);
        // The game calls getRowOffset and discards the result (0x71003fa540).
        m_pageContext->unknown50->getRowOffset();
        int booster = m_pageContext->unknown50->getContents(m_pageContext->unknown50->getIndex(false)).unknown04 - Bdat::getIdTop(GfDataBdat::getFP(BDAT_ITM_BOOSTER_LIST));
        if (booster >= 0 && booster < 4) {
          if (prev != 0xffffffff) {
            m_pageContext->m_menuModelView->removeEffect(prev + 9);
          }
          GfMenuModelView *view = m_pageContext->m_menuModelView;
          // Single-use locals (ruling of 2026-11-13): the game (0x71003faa4c) loads the effect name and computes index + 9 before it clears the position; inline, the order differs (measured).
          const char *name = unknown016[booster][0];
          u32 effect = index + 9;
          mm::Vec3 position(0.0f, 0.0f, 0.0f);
          view->playEffect(effect, name, position, view->findGfObj(unknown009, view->getMapObjID(1)));
        }
      } else {
        m_pageContext->m_menuModelView->removeEffect(prev + 9);
      }
      if (prev != 0xffffffff && index != prev) {
        GfMenuObjUtil::playSECommonCursor();
      }
    }
    break;
  }
  case 8: {
    int index = event.unknown08;
    if (event.unknown0c == 1) {
      if (index != -1) {
        if (index < static_cast<int>(m_pageContext->unknown50->getSize())) {
          GfMenuObject::sendOpenEvent(acc.searchChild("LAY_bst_select_dialog"), 0, 0.0f);
        } else {
          ui::EventData next;
          next.unknown00 = GfMenuTypes::unknown003_257;
          GfMenuObject::sendEvent(acc.unknown10, next, 0.0f);
        }
        GfMenuObject::disableFSInput();
        GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      }
    } else if (event.unknown0c == 2) {
      if (index < static_cast<int>(m_pageContext->unknown50->getSize())) {
        m_pageContext->m_menuModelView->stopEffect(index + 9);
      }
      GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_dr_idea"), 0, 0.0f);
      m_menuObjBladeCreate->returnPage(acc.unknown10, m_pageContext, true);
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    }
    GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    break;
  }
  case 0x21:
    if (m_pageContext->unknown50->getSize() == 0) {
      GfMenuObject::setupInputSelection(acc.unknown10, -1, 0);
    } else if (m_pageContext->unknown04 == 1) {
      GfMenuObject::resetInputSelection(acc.unknown10);
      GfMenuObject::setupInputSelection(acc.unknown10, 0, m_pageContext->unknown50->getSize() + 1);
      ui::UIObjectAcc skip(acc.unknown10, "LAY_bst_sel_item_skip");
      mm::mtl::FixStr<32> name;
      name.format("item_%d", m_pageContext->unknown50->getSize() + 1);
      acc.setLayout(skip.unknown10, name.c_str());
    }
    m_menuObjBladeCreate->unknown1174[0] = 0;
    m_menuObjBladeCreate->unknown1174[1] = 0;
    m_menuObjBladeCreate->unknown1174[2] = 0;
    m_menuObjBladeCreate->unknown1174[3] = 0;
    m_menuObjBladeCreate->unknown1170 = 0;
    unknown014(acc.unknown10);
    m_menuObjBladeCreate->setGuideText(0x29);
    GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_dr_idea"), 0, 0.0f);
    m_menuObjBladeCreate->unknown1188->unknown0c = 0;
    m_menuObjBladeCreate->updateIdea(false);
    break;
  case 0x22:
    unknown015(acc.unknown10);
    break;
  case GfMenuTypes::unknown003_257:
    GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_dr_idea"), 0, 0.0f);
    m_menuObjBladeCreate->nextPage(acc.unknown10, m_pageContext, true);
    break;
  case GfMenuTypes::unknown003_258: {
    // Single-use local (ruling of 2026-11-13): the game calls getIndex (0x71003fa75c) before it loads the model view (0x71003fa764); inline in the argument the load comes first (measured).
    int index = m_menuObjBladeCreate->unknown1160->getIndex(false);
    m_pageContext->m_menuModelView->stopEffect(index + 9);
    GfMenuObjUtil::playVibration(fw::VIBRATION_ID_UNKNOWN_11, 1.0f);
    ui::EventData next;
    next.unknown00 = GfMenuTypes::unknown003_257;
    GfMenuObject::sendEvent(acc.unknown10, next, 0.44f);
    break;
  }
  case GfMenuTypes::unknown003_259:
    if (event.unknown08 == 1) {
      // The game calls getIndex on the booster select list and discards the result (0x71003fa450).
      m_menuObjBladeCreate->unknown1160->getIndex(false);
      int booster = m_pageContext->unknown50->getContents(m_pageContext->unknown50->getIndex(false)).unknown04 - Bdat::getIdTop(GfDataBdat::getFP(BDAT_ITM_BOOSTER_LIST));
      // `view` is read once, before the calls of its arguments: written out at each use the order differs (measured).
      GfMenuModelView *view = m_pageContext->m_menuModelView;
      {
        mm::Vec3 position(0.0f, 0.0f, 0.0f);
        view->playEffect(13, unknown016[booster][1], position, view->findGfObj(unknown009, view->getMapObjID(1)));
      }
      GfMenuObjUtil::playSE(unknown017[booster]);
      ui::EventData next;
      next.unknown00 = GfMenuTypes::unknown003_258;
      GfMenuObject::sendEvent(acc.unknown10, next, 0.56f);
    } else {
      GfMenuObject::enableFSInput(2);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
      m_menuObjBladeCreate->setGuideText(0x29);
    }
    break;
  }
}

void GfMenuObjBladeCreate::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::setGuideDisp(false);
    acc.setDisp(false);
    break;
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown14 = 1;
    param.unknown00 = 0.5f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObjOperationInfo::setGuideDisp(true);
    GfMenuObjMainMenu2::dispCloseButton();
    if (GfSound::get() != nullptr) {
      GfMenuSoundManager::fadeFieldBgm(1.0f, 0.5f);
      GfMenuObjUtil::stopBGM(m_menuObjBladeCreate->unknown11c0, 1.0f);
      m_menuObjBladeCreate->unknown11c0 = 0;
      m_menuObjBladeCreate->stopAllSound();
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBladeCreate::ResultListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(5);
      GfMenuObjOperationInfo::open(acc.unknown10, 0, 0, 0);
      GfMenuObjOperationInfo::setGuideDisp(false);
      m_menuObjBladeCreate->unknown11c0 = GfMenuObjUtil::playBGM(0x14, false, CATEGORY_MENU_BGM);
    }
    break;
  case 8:
    if (event.unknown0c == 1) {
      m_menuObjBladeCreate->unknownaf8.unknown002(&GfMenuObjBladeCreate::seqResultStart);
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      GfMenuObject::disableFSInput();
    }
    break;
  case GfMenuTypes::unknown003_33:
    unknown014(acc.unknown10);
    GfMenuObjCmnStatus::openBlStatus(2, -1);
    {
      ui::UIObjectAcc image(acc.unknown10, "IMG_result_bl_img");
      u32 blade = GfMenuReference::getReferenceBladeID(0);
      acc.setLayout(image.unknown10, "blade");
      GfMenuObjUtil::ImageParam imageParam;
      if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
        mm::Vec2 scale;
        image.getScale(scale);
        scale.x = imageParam.unknown04 * scale.x;
        scale.y = imageParam.unknown04 * scale.y;
        image.setScale(scale);
        GfMenuObjUtil::addPos(image.unknown10, imageParam.unknown00, imageParam.unknown02);
      }
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_in_r");
      param.unknown04 = 1;
      param.unknown14 = 8;
      GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    }
    GfMenuObjUtil::playJingle(GfDataBlade::isCommonBlade(GfMenuReference::getReferenceBladeID(0)) ? 0xd : 0xc);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObjCmnStatus::closeBlStatus();
    unknown015(acc.unknown10);
    break;
  }
}

void GfMenuObjBladeCreate::BoosterNumListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = 0;
    unknown10 = 1;
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(6);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    } else if (event.unknown08 == 2) {
      ui::EventData end;
      end.unknown0c = 0;
      end.unknown00 = GfMenuTypes::unknown003_259;
      end.unknown08 = unknown10;
      GfMenuObject::sendEvent(acc.getParentHandle(), end, 0.0f);
    }
    break;
  case 6: {
    int index = event.unknown08;
    int prev = event.unknown0c;
    if (index != -1) {
      m_menuObjBladeCreate->unknown1188->unknown162(index + 1);
      m_menuObjBladeCreate->updateIdea(false);
    }
    if (prev != -1 && index != prev) {
      GfMenuObjUtil::playSE(0x19);
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      m_menuObjBladeCreate->updateIdea(true);
      unknown10 = 1;
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
    } else if (event.unknown0c == 2) {
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
      m_menuObjBladeCreate->unknown1188->unknown162(0);
      m_menuObjBladeCreate->updateIdea(false);
    }
    GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    break;
  case GfMenuTypes::unknown003_33:
    if (unknown0c == 0) {
      unknown014(acc.unknown10);
      unknown0c = 1;
      unknown10 = 0;
      const MenuItemInfo &idea = m_menuObjBladeCreate->m_pageContext.unknown50->getContents(m_menuObjBladeCreate->m_pageContext.unknown50->getIndex(false));
      u32 level = idea.unknown08;
      if (level > 5) {
        level = 5;
      }
      m_menuObjBladeCreate->unknown1188->unknown10 = 1;
      m_menuObjBladeCreate->unknown1188->unknown14 = level;
      m_menuObjBladeCreate->unknown1188->unknown162(1);
      GfMenuObject::resetInputSelection(acc.unknown10);
      GfMenuObject::setupInputSelection(acc.unknown10, 0, level);
    }
    m_menuObjBladeCreate->setGuideText(0x39);
    break;
  case GfMenuTypes::unknown003_34:
    if (unknown0c == 1) {
      GfMenuObject::disableFSInput();
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      unknown015(acc.unknown10);
      unknown0c = 0;
    }
    break;
  }
}

void GfMenuObjBladeCreate::IdeagramListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = 0;
    break;
  case GfMenuTypes::unknown003_33:
    if (unknown0c == 0) {
      unknown014(acc.unknown10);
      unknown0c = 1;
    }
    break;
  case GfMenuTypes::unknown003_34:
    if (unknown0c == 1) {
      unknown015(acc.unknown10);
      unknown0c = 0;
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBladeCreate::ConfirmListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case GfMenuTypes::unknown003_33:
    m_pageContext->m_menuCallContext->reset();
    // The game (0x71003fabd0) keeps the branch on the flag and calls open in each arm; a ternary argument gives a csel.
    if (!m_menuObjBladeCreate->unknown11b4) {
      GfMenuObjCommonText::open(m_pageContext->m_menuCallContext, 0x46, 0);
    } else {
      GfMenuObjCommonText::open(m_pageContext->m_menuCallContext, 0xc4, 0);
    }
    GfMenuObject::setCallContextEventHandler(m_pageContext->m_menuCallContext, acc.unknown10);
    GfMenuObjOperationInfo::setDisp(false);
    m_menuObjBladeCreate->dispGuideText(false);
    if (!m_menuObjBladeCreate->unknown11b4) {
      GfMenuObjMainMenu2::setCloseKeyEnable(false);
    }
    break;
  case GfMenuTypes::unknown003_34:
    break;
  case 0x41: {
    // Ruling 2: the game (0x71003fabf4) loads the id of the event before the id of the context.
    u32 callId = event.unknown08;
    if (m_pageContext->m_menuCallContext->unknown0c != callId) {
      break;
    }
    if (event.unknown10 == 0) {
      ui::EventData closeEvent;
      closeEvent.unknown00 = GfMenuTypes::unknown003_34;
      GfMenuObject::sendEvent(acc.searchSibiling("LAY_dr_idea"), closeEvent, 0.0f);
      m_menuObjBladeCreate->nextPage(acc.unknown10, m_pageContext, true);
    } else {
      GfMenuObjOperationInfo::setDisp(true);
      m_menuObjBladeCreate->dispGuideText(true);
      m_menuObjBladeCreate->returnPage(acc.unknown10, m_pageContext, true);
      if (!m_menuObjBladeCreate->unknown11b4) {
        GfMenuObjMainMenu2::setCloseKeyEnable(true);
      }
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBladeCreate::CreationListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
  case GfMenuTypes::unknown003_34:
    acc.setDisp(false);
    break;
  case 3:
    // The game (0x71003fae58) terminates the call context and then runs the base handler.
    GfMenuObject::termCallContext(acc.unknown10);
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case GfMenuTypes::unknown003_33: {
    // Single-use locals (P2): the game (0x71003fae74) reads the driver before it clears the blade, and (0x71003faf94) the crystal before it loads the page state of the call; inline in the
    // arguments the driver gives 455 instructions (the game's 456) and the crystal 456 with another schedule (measured).
    u32 driver = unknown28->unknown40->getContents(unknown28->unknown40->getIndex(false)).unknown00;
    unknown28->unknown58.clear();
    unknown28->unknown58.setupDriver(driver);
    u32 crystal = unknown28->unknown48->getContents(unknown28->unknown48->getIndex(false)).unknown04;
    unknown28->unknown58.setupCoreCrystal(crystal);
    unknown28->unknown48->decItem(unknown28->unknown48->getIndex(false), 1, true);
    for (u32 i = 0; i < 4; i++) {
      if (unknown20->unknown1174[i] != 0) {
        // The game (0x71003fb000) fetches the booster once, before the loop of its counts.
        const MenuItemInfo &booster = unknown28->unknown50->getContents(i);
        for (u32 j = 0; j < unknown20->unknown1174[i]; j++) {
          unknown28->unknown58.setupAddBooster(booster.unknown04);
        }
        unknown28->unknown50->decItem(i, unknown20->unknown1174[i], true);
      }
    }
    unknown28->unknown58.createBladeNewVersion();
    SDataBlade blade;
    unknown28->unknown58.getResultBlade(blade);
    unknown28->unknown28 = 0;
    if (unknown28->unknown58.unknown244) {
      unknown28->unknown28 = GfGameUtil::execAddRareBlade(blade);
    } else {
      unknown28->unknown28 = GfGameUtil::execAddCommonBlade(blade);
    }
    // The created blade ids stay in a local copy until the reference blade is set: the game (0x71003fb284) destroys it after setReferenceBladeID.
    {
      mm::mtl::FixedVector<u32, 2> created(unknown28->unknown58.unknown258);
      for (u32 i = 0; i < created.size(); i++) {
        unknown20->unknown1128.push_back(created[i]);
      }
      unknown20->unknown1128.push_back(unknown28->unknown28);
      GfMenuReference::setReferenceBladeID(0, unknown28->unknown28);
    }
    if (!unknown20->unknown11b4) {
      unknown20->unknownaf8.unknown004(1);
      unknown20->unknownaf8.unknown002(&GfMenuObjBladeCreate::seqSave);
      unknown20->unknownaf8.unknown004(30);
      unknown20->unknownaf8.unknown002(&GfMenuObjBladeCreate::seqSaveWait);
    }
    unknown20->unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateStart);
    break;
  }
  }
}

} // namespace gf
