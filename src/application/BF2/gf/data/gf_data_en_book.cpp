#include "gf/data/gf_data_en_book.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  FLAG_EN_BOOK_ATTACK_ORDER = 0x764,
  FLAG_EN_BOOK_ATTACK_ORDER_END = 0xb4c,
  FLAG_EN_BOOK_ATTACK = 0xbdce,
  FLAG_EN_BOOK_DEFEAT_NUM = 0x142,
  FLAG_EN_BOOK_DEAD_NUM = 0x52b,
  FLAG_EN_BOOK_CLEAR_NAMED_TIME = 0x914,
};

constexpr u32 COUNTER_MAX = 0xffffffff;

u32 GfDataEnBook::getEnBoolId(u32 enemy) {
  if (enemy == 0) {
    return 0;
  }

  return GfBdatChrEnArrange::get()->getChrEnArrangeBookID(enemy);
}

bool GfDataEnBook::isBook(u32 enemy) { return getEnBoolId(enemy) != 0; }

bool GfDataEnBook::isNamed(u32 enemy) {
  if (GfBdatChrEnArrange::get() == nullptr) {
    return false;
  }

  return GfBdatChrEnArrange::get()->isChrEnArrangeFlagNamed(enemy);
}

bool GfDataEnBook::isAttackFlag(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return false;
  }

  return GfGameFlag::getLocal(1, FLAG_EN_BOOK_ATTACK + book) != 0;
}

void GfDataEnBook::setAttackFlag(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0 || GfGameFlag::getLocal(1, FLAG_EN_BOOK_ATTACK + book) != 0) {
    return;
  }

  GfGameFlag::setLocal(1, FLAG_EN_BOOK_ATTACK + book, 1);
  for (u32 flag = FLAG_EN_BOOK_ATTACK_ORDER; flag < FLAG_EN_BOOK_ATTACK_ORDER_END; flag++) {
    if (GfGameFlag::getLocal(16, flag) == 0) {
      GfGameFlag::setLocal(16, flag, static_cast<u16>(enemy));
      return;
    }
  }
}

u32 GfDataEnBook::getDefeatNum(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return 0;
  }

  return GfGameFlag::getLocal(32, FLAG_EN_BOOK_DEFEAT_NUM + book);
}

void GfDataEnBook::incDefeatNum(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return;
  }

  u32 defeatNum = GfGameFlag::getLocal(32, FLAG_EN_BOOK_DEFEAT_NUM + book);
  if (defeatNum != COUNTER_MAX) {
    GfGameFlag::setLocal(32, FLAG_EN_BOOK_DEFEAT_NUM + book, defeatNum + 1);
  }
}

u32 GfDataEnBook::getDeadNum(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return 0;
  }

  return GfGameFlag::getLocal(32, FLAG_EN_BOOK_DEAD_NUM + book);
}

void GfDataEnBook::incDeadNum(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return;
  }

  u32 deadNum = GfGameFlag::getLocal(32, FLAG_EN_BOOK_DEAD_NUM + book);
  if (deadNum != COUNTER_MAX) {
    GfGameFlag::setLocal(32, FLAG_EN_BOOK_DEAD_NUM + book, deadNum + 1);
  }
}

u32 GfDataEnBook::getClearNamedTime(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return 0;
  }

  return GfGameFlag::getLocal(32, FLAG_EN_BOOK_CLEAR_NAMED_TIME + book);
}

void GfDataEnBook::setClearNamedTime(u32 enemy, u32 clearNamedTime) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return;
  }

  if (GfGameFlag::getLocal(32, FLAG_EN_BOOK_CLEAR_NAMED_TIME + book) == 0) {
    GfGameFlag::setLocal(32, FLAG_EN_BOOK_CLEAR_NAMED_TIME + book, clearNamedTime);
  }
}

u32 GfDataEnBook::getBaseEnemy(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return 0;
  }

  return GfBdatChrEnArrange::get()->getBTL_EnBookBaseEnemyID(book);
}

u32 GfDataEnBook::getPopTime(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return 0;
  }

  return GfBdatChrEnArrange::get()->getBTL_EnBookBOOK_POP_TIME(book);
}

u32 GfDataEnBook::getPopWeather(u32 enemy) {
  u32 book = getEnBoolId(enemy);
  if (book == 0) {
    return 0;
  }

  return GfBdatChrEnArrange::get()->getBTL_EnBookBOOK_popWeather(book);
}

} // namespace gf
