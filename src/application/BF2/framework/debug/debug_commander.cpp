#include "framework/debug/debug_commander.h"

#include "skt/command_manager.h"

namespace fw {
namespace debug {

bool CommandManager::sendCommand(const char *server, const char *command) { return skt::CommandManager::sendCommand(server, command); }

bool CommandManager::sendCommandHtcs(const char *server, const char *command) { return skt::CommandManager::sendCommandHtcs(server, command); }

bool CommandManager::openServer(const skt::PortRegistInfo &info) { return skt::CommandManager::openServer(info, static_cast<skt::SERVER_OPTION>(0)); }

bool CommandManager::closeServer(const char *server) { return skt::CommandManager::closeServer(server); }

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

} // namespace debug
} // namespace fw
