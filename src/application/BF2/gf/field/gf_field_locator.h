#pragma once
#include <stddef.h>

#include "gf/game/quest/gf_quest_id.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gmk {
class AGmkBase;
class GmkEvent;
class GmkPrecious;
} // namespace gmk

namespace gf {

class AFieldLocator {
public:
  AFieldLocator() : unknown08{0, 0}, m_iconBdatId(-1), m_mapBdatId(-1) {}
  virtual ~AFieldLocator() {}
  virtual int getIconBdatId() const;
  virtual u32 getPosNum() const = 0;
  virtual const mm::Vec3 *getPos(u32 index) const = 0;
  virtual int getMapBdatId() const;
  virtual void update() = 0;

  // Inferred helper: sets the icon of a quest target icon type, or icon 0x19f when the type has none; original name unknown.
  void unknown001(u32 iconType) {
    int icon = gmk::getBdatIdOfQuestTargetIcon(iconType);
    if (icon < 0) {
      icon = 0x19f;
    }
    m_iconBdatId = icon;
  }

  QuestID unknown08; // Inferred role: quest; original member name unknown.
  int m_iconBdatId;
  int m_mapBdatId;
};

static_assert(offsetof(AFieldLocator, unknown08) == 0x08, "");
static_assert(offsetof(AFieldLocator, m_iconBdatId) == 0x0c, "");
static_assert(offsetof(AFieldLocator, m_mapBdatId) == 0x10, "");

// Inferred role: gimmick instance visitor of gmk::GmkManager::traverseGmkInst; original type name unknown.
class unknown134 {
public:
  virtual void onTraverse(const gmk::AGmkBase &gmk) = 0;
};

class LocatorBat_EnemyID : public AFieldLocator {
public:
  LocatorBat_EnemyID(QuestID quest, u16 enemyId);
  ~LocatorBat_EnemyID() override { dispose(); }
  u32 getPosNum() const override;
  const mm::Vec3 *getPos(u32 index) const override;
  void update() override;
  void create(QuestID quest, u16 enemyId);
  void dispose();

  u16 unknown14;                                    // Inferred role: enemy id; original member name unknown.
  int unknown18;                                    // Inferred role: gimmick set bdat id; original member name unknown.
  mm::mtl::FixedVector<gmk::GmkAcc, 16> unknown20;  // Inferred role: enemy gimmick accessors; original member name unknown.
  mm::mtl::FixedVector<gmk::GmkAcc, 16> unknown428; // Inferred role: routed enemy gimmick accessors; original member name unknown.
  mm::mtl::FixedVector<mm::Vec3, 16> m_pos;
};

static_assert(offsetof(LocatorBat_EnemyID, unknown14) == 0x14, "");
static_assert(offsetof(LocatorBat_EnemyID, unknown18) == 0x18, "");
static_assert(offsetof(LocatorBat_EnemyID, unknown20) == 0x20, "");
static_assert(offsetof(LocatorBat_EnemyID, unknown428) == 0x428, "");
static_assert(offsetof(LocatorBat_EnemyID, m_pos) == 0x830, "");
static_assert(sizeof(LocatorBat_EnemyID) == 0x940, "");

class LocatorBat_EnemyGroupID : public AFieldLocator {
public:
  LocatorBat_EnemyGroupID(QuestID quest, u16 enemyGroupId);
  ~LocatorBat_EnemyGroupID() override { dispose(); }
  u32 getPosNum() const override;
  const mm::Vec3 *getPos(u32 index) const override;
  void update() override;
  void create(QuestID quest, u16 enemyGroupId);
  void dispose();

  u16 unknown14;                          // Inferred role: enemy group id; original member name unknown.
  int unknown18;                          // Inferred role: gimmick set bdat id; original member name unknown.
  mm::mtl::FixedVector<u32, 8> unknown20; // Inferred role: enemy ids; original member name unknown.
  mm::mtl::FixedVector<u8, 8> unknown48;  // Inferred role: zone ids; original member name unknown.
  mm::mtl::FixedVector<mm::Vec3, 16> m_pos;
};

static_assert(offsetof(LocatorBat_EnemyGroupID, unknown14) == 0x14, "");
static_assert(offsetof(LocatorBat_EnemyGroupID, unknown18) == 0x18, "");
static_assert(offsetof(LocatorBat_EnemyGroupID, unknown20) == 0x20, "");
static_assert(offsetof(LocatorBat_EnemyGroupID, unknown48) == 0x48, "");
static_assert(offsetof(LocatorBat_EnemyGroupID, m_pos) == 0x60, "");
static_assert(sizeof(LocatorBat_EnemyGroupID) == 0x170, "");

class LocatorBat_EnemySpeciesID : public AFieldLocator {
public:
  LocatorBat_EnemySpeciesID(QuestID quest, u8 enemySpeciesId);
  ~LocatorBat_EnemySpeciesID() override { dispose(); }
  u32 getPosNum() const override { return m_pos.size(); }
  const mm::Vec3 *getPos(u32 index) const override { return &m_pos[index]; }
  void update() override;
  void create(QuestID quest, u8 enemySpeciesId);
  void dispose();

  u8 unknown14;  // Inferred role: enemy species id; original member name unknown.
  int unknown18; // Inferred role: gimmick set bdat id; original member name unknown.
  mm::mtl::FixedVector<mm::Vec3, 16> m_pos;
};

static_assert(offsetof(LocatorBat_EnemySpeciesID, unknown14) == 0x14, "");
static_assert(offsetof(LocatorBat_EnemySpeciesID, unknown18) == 0x18, "");
static_assert(offsetof(LocatorBat_EnemySpeciesID, m_pos) == 0x20, "");
static_assert(sizeof(LocatorBat_EnemySpeciesID) == 0x130, "");

class LocatorTalk_NpcID : public AFieldLocator {
public:
  explicit LocatorTalk_NpcID(QuestID quest = QuestID(), u16 mapId = 0, u16 npcId = 0);
  LocatorTalk_NpcID(QuestID quest, u8 *bdat, int id);
  ~LocatorTalk_NpcID() override { dispose(); }
  u32 getPosNum() const override { return m_posNum; }
  const mm::Vec3 *getPos(u32 index) const override { return &m_pos; }
  void update() override;
  void create(QuestID quest, u16 mapId, u16 npcId);
  void dispose();
  void createPreorder(u16 npcId);

  int unknown14; // Inferred role: gimmick set bdat id; original member name unknown.
  u16 unknown18; // Inferred role: npc id; original member name unknown.
  u8 m_posNum;
  mm::Vec3 m_pos;
};

static_assert(offsetof(LocatorTalk_NpcID, unknown14) == 0x14, "");
static_assert(offsetof(LocatorTalk_NpcID, unknown18) == 0x18, "");
static_assert(offsetof(LocatorTalk_NpcID, m_posNum) == 0x1a, "");
static_assert(offsetof(LocatorTalk_NpcID, m_pos) == 0x20, "");
static_assert(sizeof(LocatorTalk_NpcID) == 0x30, "");

class LocatorTalk_DummyGroup : public AFieldLocator {
public:
  LocatorTalk_DummyGroup(QuestID quest, u16 mapId, u16 npcId, u16 dummyGroup);
  ~LocatorTalk_DummyGroup() override { dispose(); }
  u32 getPosNum() const override { return m_pos.size(); }
  const mm::Vec3 *getPos(u32 index) const override { return &m_pos[index]; }
  void update() override;
  void create(QuestID quest, u16 mapId, u16 npcId, u16 dummyGroup);
  void dispose();

  int unknown14;                          // Inferred role: gimmick set bdat id; original member name unknown.
  u16 unknown18;                          // Inferred role: npc id; original member name unknown.
  u16 unknown1a;                          // Inferred role: dummy group; original member name unknown.
  mm::mtl::FixedVector<u16, 9> unknown20; // Inferred role: npc ids; original member name unknown.
  mm::mtl::FixedVector<mm::Vec3, 9> m_pos;
};

static_assert(offsetof(LocatorTalk_DummyGroup, unknown14) == 0x14, "");
static_assert(offsetof(LocatorTalk_DummyGroup, unknown18) == 0x18, "");
static_assert(offsetof(LocatorTalk_DummyGroup, unknown1a) == 0x1a, "");
static_assert(offsetof(LocatorTalk_DummyGroup, unknown20) == 0x20, "");
static_assert(offsetof(LocatorTalk_DummyGroup, m_pos) == 0x40, "");
static_assert(sizeof(LocatorTalk_DummyGroup) == 0xe0, "");

class LocatorReach : public AFieldLocator {
public:
  LocatorReach(QuestID quest, int reachId);
  ~LocatorReach() override { dispose(); }
  u32 getPosNum() const override { return m_posNum; }
  const mm::Vec3 *getPos(u32 index) const override { return &m_pos; }
  void update() override;
  void create(QuestID quest, int reachId);
  void dispose();

  u8 unknown14;  // Inferred role: category; original member name unknown.
  u16 unknown16; // Inferred role: place id; original member name unknown.
  u8 m_posNum;
  mm::Vec3 m_pos;
};

static_assert(offsetof(LocatorReach, unknown14) == 0x14, "");
static_assert(offsetof(LocatorReach, unknown16) == 0x16, "");
static_assert(offsetof(LocatorReach, m_posNum) == 0x18, "");
static_assert(offsetof(LocatorReach, m_pos) == 0x20, "");
static_assert(sizeof(LocatorReach) == 0x30, "");

class LocatorTbox : public AFieldLocator {
public:
  LocatorTbox(QuestID quest, u16 tboxId);
  ~LocatorTbox() override { dispose(); }
  u32 getPosNum() const override { return unknown18.isValid() ? m_posNum : 0; }
  const mm::Vec3 *getPos(u32 index) const override { return &m_pos; }
  void update() override;
  void create(QuestID quest, u16 tboxId);
  void dispose();

  u16 unknown14;         // Inferred role: tbox bdat id; original member name unknown.
  gmk::GmkAcc unknown18; // Inferred role: tbox gimmick accessor; original member name unknown.
  u8 m_posNum;
  mm::Vec3 m_pos;
};

static_assert(offsetof(LocatorTbox, unknown14) == 0x14, "");
static_assert(offsetof(LocatorTbox, unknown18) == 0x18, "");
static_assert(offsetof(LocatorTbox, m_posNum) == 0x58, "");
static_assert(offsetof(LocatorTbox, m_pos) == 0x60, "");
static_assert(sizeof(LocatorTbox) == 0x70, "");

class LocatorPrecious : public AFieldLocator, public unknown134 {
public:
  LocatorPrecious(QuestID quest, u16 itemId);
  ~LocatorPrecious() override { dispose(); }
  u32 getPosNum() const override;
  const mm::Vec3 *getPos(u32 index) const override;
  void update() override;
  void onTraverse(const gmk::AGmkBase &gmk) override;
  void create(QuestID quest, u16 itemId);
  void dispose();

  u16 unknown20;                                   // Inferred role: item id; original member name unknown.
  mm::mtl::FixedVector<gmk::GmkAcc, 16> unknown28; // Inferred role: precious gimmick accessors; original member name unknown.
  mm::mtl::FixedVector<mm::Vec3, 16> m_pos;
};

static_assert(offsetof(LocatorPrecious, unknown20) == 0x20, "");
static_assert(offsetof(LocatorPrecious, unknown28) == 0x28, "");
static_assert(offsetof(LocatorPrecious, m_pos) == 0x430, "");
static_assert(sizeof(LocatorPrecious) == 0x540, "");

class LocatorGimmick : public AFieldLocator {
public:
  LocatorGimmick(QuestID quest, u16 gimmickId);
  ~LocatorGimmick() override { dispose(); }
  u32 getPosNum() const override { return m_posNum; }
  const mm::Vec3 *getPos(u32 index) const override { return &m_pos; }
  void update() override;
  void create(QuestID quest, u16 gimmickId);
  void dispose();

  gmk::GmkType unknown14; // Inferred role: gimmick type; original member name unknown.
  u16 unknown18;          // Inferred role: gimmick bdat id; original member name unknown.
  u8 m_posNum;
  mm::Vec3 m_pos;
};

static_assert(offsetof(LocatorGimmick, unknown14) == 0x14, "");
static_assert(offsetof(LocatorGimmick, unknown18) == 0x18, "");
static_assert(offsetof(LocatorGimmick, m_posNum) == 0x1a, "");
static_assert(offsetof(LocatorGimmick, m_pos) == 0x20, "");
static_assert(sizeof(LocatorGimmick) == 0x30, "");

class LocatorEventPreorder : public AFieldLocator {
public:
  explicit LocatorEventPreorder(const gmk::GmkEvent *gmk);
  ~LocatorEventPreorder() override { dispose(); }
  u32 getPosNum() const override { return unknown18.isValid() ? m_posNum : 0; }
  const mm::Vec3 *getPos(u32 index) const override { return &m_pos; }
  void update() override;
  void create(const gmk::GmkEvent &gmk);
  void dispose();

  u16 unknown14;         // Inferred role: event bdat id; original member name unknown.
  gmk::GmkAcc unknown18; // Inferred role: event gimmick accessor; original member name unknown.
  u8 m_posNum;
  mm::Vec3 m_pos;
};

static_assert(offsetof(LocatorEventPreorder, unknown14) == 0x14, "");
static_assert(offsetof(LocatorEventPreorder, unknown18) == 0x18, "");
static_assert(offsetof(LocatorEventPreorder, m_posNum) == 0x58, "");
static_assert(offsetof(LocatorEventPreorder, m_pos) == 0x60, "");
static_assert(sizeof(LocatorEventPreorder) == 0x70, "");

class LocatorPreciousPreorder : public AFieldLocator {
public:
  explicit LocatorPreciousPreorder(const gmk::GmkPrecious *gmk);
  ~LocatorPreciousPreorder() override { dispose(); }
  u32 getPosNum() const override { return unknown18.isValid() ? m_posNum : 0; }
  const mm::Vec3 *getPos(u32 index) const override { return &m_pos; }
  void update() override;
  void create(const gmk::GmkPrecious &gmk);
  void dispose();

  u16 unknown14;         // Inferred role: precious bdat id; original member name unknown.
  gmk::GmkAcc unknown18; // Inferred role: precious gimmick accessor; original member name unknown.
  u8 m_posNum;
  mm::Vec3 m_pos;
};

static_assert(offsetof(LocatorPreciousPreorder, unknown14) == 0x14, "");
static_assert(offsetof(LocatorPreciousPreorder, unknown18) == 0x18, "");
static_assert(offsetof(LocatorPreciousPreorder, m_posNum) == 0x58, "");
static_assert(offsetof(LocatorPreciousPreorder, m_pos) == 0x60, "");
static_assert(sizeof(LocatorPreciousPreorder) == 0x70, "");

class GfFieldLocator {
public:
  struct CreateInfoByQuest {
    CreateInfoByQuest() : unknown00{0, 0}, unknown04(-1), unknown08(-1) {}

    QuestID unknown00; // Inferred role: quest; original member name unknown.
    int unknown04;     // Inferred role: task type; original member name unknown.
    int unknown08;     // Inferred role: task id; original member name unknown.
  };

  explicit GfFieldLocator(const CreateInfoByQuest *info);
  GfFieldLocator(const GfFieldLocator &other);
  virtual ~GfFieldLocator() { dispose(); }
  void createByQuest(const CreateInfoByQuest &info);
  void dispose();
  void createLocatorTalkPreorder(u16 npcId);
  void createLocatorEventPreorder(const gmk::GmkEvent &gmk);
  void createLocatorPreciousPreorder(const gmk::GmkPrecious &gmk);
  void update();
  bool isOtherMap() const;
  static bool isIconIdPreorder(int iconId);

  CreateInfoByQuest unknown08; // Inferred role: quest task; original member name unknown.
  AFieldLocator *unknown18;    // Inferred role: locator; original member name unknown.
};

static_assert(offsetof(GfFieldLocator, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldLocator, unknown18) == 0x18, "");
static_assert(sizeof(GfFieldLocator) == 0x20, "");

} // namespace gf
