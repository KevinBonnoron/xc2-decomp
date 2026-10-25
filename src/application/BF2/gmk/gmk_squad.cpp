#include "gmk/gmk_squad.h"

#include "gmk/gmk_set.h"

namespace gmk {

GmkType GmkSquadLeader::getGmkType() const { return GMK_TYPE; }

bool GmkSquadLeader::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkSquadLeader::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkSquadLeader::dispose() { AGmkBase::dispose(); }

void GmkSquadLeader::debugDraw() const {}

void GmkSquadLeader::debugUpdateMmf() {}

const IGmkList *GmkSquadLeader::getBindedSquadMemberList() const { return unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_SQUAD_MEMBER]; }

GmkType GmkSquadMember::getGmkType() const { return GMK_TYPE; }

bool GmkSquadMember::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkSquadMember::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkSquadMember::dispose() { AGmkBase::dispose(); }

void GmkSquadMember::debugUpdateMmf() {}

} // namespace gmk
