#include "event/rand_calc.h"

#include <stdio.h>

#include "bdat.h"
#include "event/rand_util.h"
#include "ml/rand.h"
#include "mm_mtl/fixed_vector.h"

namespace event {

int RandCalc::calc(int type) {
  mm::mtl::FixedVector<int, TALK_COUNT> talks;
  mm::mtl::FixedVector<int, TALK_COUNT> typeTalks;
  listup(talks);
  if (talks.empty()) {
    return -1;
  }
  listupType(typeTalks, talks, type);
  if (typeTalks.empty()) {
    return -1;
  }
  listupParty(talks, typeTalks);
  if (talks.empty()) {
    return -1;
  }
  listupRand(typeTalks, talks);
  return typeTalks[0];
}

void RandCalc::listup(mm::mtl::FixedVector<int, TALK_COUNT> &list) {
  unsigned char *bdat = Bdat::getFP("FLD_randomTalk");
  int top = Bdat::getIdTop(bdat);
  u32 count = Bdat::getIdCount(bdat);
  list.clear();
  for (u32 i = 0; i < count; i++) {
    list.push_back(top + i);
  }
}

void RandCalc::listupType(mm::mtl::FixedVector<int, TALK_COUNT> &list, mm::mtl::FixedVector<int, TALK_COUNT> &source, int type) {
  unsigned char *bdat = Bdat::getFP("FLD_randomTalk");
  list.clear();
  for (size_t i = 0; i < source.size(); i++) {
    int id = source[i];
    if (Bdat::getVal(bdat, "type", id).valueS8 == type) {
      list.push_back(id);
    }
  }
}

void RandCalc::listupParty(mm::mtl::FixedVector<int, TALK_COUNT> &list, mm::mtl::FixedVector<int, TALK_COUNT> &source) {
  unsigned char *bdat = Bdat::getFP("FLD_randomTalk");
  list.clear();
  for (size_t i = 0; i < source.size(); i++) {
    int id = source[i];
    s16 talker = Bdat::getVal(bdat, "talk0", id).valueS16;
    if (talker > 0 && RandUtil::searchByID(talker) == nullptr) {
      continue;
    }
    talker = Bdat::getVal(bdat, "talk1", id).valueS16;
    if (talker > 0 && RandUtil::searchByID(talker) == nullptr) {
      continue;
    }
    list.push_back(id);
  }
}

void RandCalc::listupRand(mm::mtl::FixedVector<int, TALK_COUNT> &list, mm::mtl::FixedVector<int, TALK_COUNT> &source) {
  int id = source[ml::mtRand(source.size())];
  list.clear();
  list.push_back(id);
}

bool RandCalc::exist(int id) { return RandUtil::searchByID(id) != nullptr; }

void RandCalc::dump(mm::mtl::FixedVector<int, TALK_COUNT> &list) {
  char text[512] = {};
  char number[512] = {};
  __builtin_strcat(text, "[ev]");
  for (size_t i = 0; i < list.size(); i++) {
    snprintf(number, sizeof(number), "%d", list[i]);
    __builtin_strcat(text, number);
    __builtin_strcat(text, " ");
  }
}

} // namespace event
