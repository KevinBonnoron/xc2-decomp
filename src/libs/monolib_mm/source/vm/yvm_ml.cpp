#include "vm/vm.h"

// Hooks of the script VM (yvm2.c) that the game compiled to empty bodies: the assertion and message output of the
// Windows build were stripped from the Switch build.
extern "C" {

void vmMlAssert(const char *, const char *, int) {}

void vmMlOutputMsg(int, const char *, ...) {}
}
