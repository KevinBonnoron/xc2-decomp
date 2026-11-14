#include "framework/debug/debug_commander.h"

#include <string.h>

#include "framework/debug/debug_draw.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/algorithm.h"

namespace fw {
namespace debug {

const char *DebugCommander::getName() const { return "DebugCommander"; }

void DebugCommander::onEnter() {}

void DebugCommander::onLeave() {}

void DebugCommander::enableDebugInput(bool enable) { unknownae8 = enable; }

bool CommandManager::sendCommand(const char *server, const char *command) { return skt::CommandManager::sendCommand(server, command); }

bool CommandManager::sendCommandHtcs(const char *server, const char *command) { return skt::CommandManager::sendCommandHtcs(server, command); }

bool CommandManager::openServer(const skt::PortRegistInfo &info) { return skt::CommandManager::openServer(info, static_cast<skt::SERVER_OPTION>(0)); }

void CommandManager::closeServer(const char *server) { skt::CommandManager::closeServer(server); }

bool CommandManager::isConnectedHtcs(const char *server) { return skt::CommandManager::isConnectedHtcs(server); }

bool CommandManager::setServerOption(const char *server, skt::SERVER_OPTION option) {
  bool isSet = skt::CommandManager::setServerOption(server, option);
  if (isSet) {
    DebugCommander *commander = DebugCommander::get();
    if (commander != nullptr) {
      commander->setServerOption(server, option);
    }
  }

  return isSet;
}

void DebugCommander::setServerOption(const char *server, skt::SERVER_OPTION option) { m_serverOption = option; }

skt::SERVER_OPTION CommandManager::getServerOption(const char *server) {
  DebugCommander *commander = DebugCommander::get();
  if (commander != nullptr) {
    return commander->getServerOption(server);
  }

  return static_cast<skt::SERVER_OPTION>(0);
}

skt::SERVER_OPTION DebugCommander::getServerOption(const char *server) const { return m_serverOption; }

DebugCommander::DebugCommander(mm::mtl::IAllocator *allocator, const char *name, u16 port, s8 unknown)
    : unknownab0(port), unknownab2(unknown), unknownab4(name), unknownad8(allocator), unknownae0(nullptr), unknownae8(false), m_serverOption(static_cast<skt::SERVER_OPTION>(0)) {}

DebugCommander::~DebugCommander() {
  if (unknownae0 != nullptr) {
    delete unknownae0;
    unknownae0 = nullptr;
  }
  finalize();
}

// Inferred role: "deb" command callback that parses every argument; original name unknown.
static bool unknown002(const skt::CommandParam &param) {
  for (u32 i = 0; i < param.unknown800.size(); i++) {
    int valueS32;
    param.getS32(i, valueS32);
    f32 valueF32;
    param.getF32(i, valueF32);
  }

  return true;
}

bool DebugCommander::initialize() {
  if (!isInitialized()) {
    initCommandLauncherReciever(this);
    registCallback("deb", unknown002);
  }

  return true;
}

void DebugCommander::registCallback(const char *name, bool (*callback)(const skt::CommandParam &)) {
  unknown001 entry(name, callback);
  if (mm::mtl::find(unknown28.begin(), unknown28.end(), entry) != unknown28.end()) {
    return;
  }

  unknown28.push_back(entry);
}

bool DebugCommander::finalize() {
  if (!isFinalized()) {
    finalCommandLauncherReciever();
    skt::CommandManager::closeServer(unknownab4.c_str());
  }

  return true;
}

void DebugCommander::update() {
  if (!isFinalized() && unknownae0 != nullptr && unknownae8) {
    unknownae0->unknown001(this);
    unknownae0->unknown002(mm::Rect<int>(16, 680, 512, 18));
  }
}

void DebugCommander::removeCallback(const char *name) {
  unknown001 entry(name, nullptr);
  unknown001 *it = mm::mtl::find(unknown28.begin(), unknown28.end(), entry);
  if (it != unknown28.end()) {
    unknown28.erase(it);
  }
}

void DebugCommander::OnRecv(const skt::CommandParam &param) {
  if (param.unknown800.size() != 0) {
    unknown001 entry(param.getStr(0).c_str(), nullptr);
    unknown001 *it = mm::mtl::find(unknown28.begin(), unknown28.end(), entry);
    if (it != unknown28.end() && it->unknown88.isValid()) {
      it->unknown88(param);
    }
  }
}

void DebugCommander::onDecide(const char *command) {
  if (command != nullptr && command[0] != '\0') {
    mm::mtl::FixStr<512> string;
    string.format("DLCmd,%s", command);
    skt::CommandParam param;
    strncpy(param.unknown000, string.c_str(), sizeof(param.unknown000) - 1);
    param.parseCommand(',');
    OnRecv(param);
  }
}

void DebugCommander::setDebugInput(IDebugInput *input) {
  if (unknownae0 != nullptr) {
    delete unknownae0;
    unknownae0 = nullptr;
  }
  unknownae0 = input;
  unknownae8 = input != nullptr;
}

} // namespace debug
} // namespace fw
