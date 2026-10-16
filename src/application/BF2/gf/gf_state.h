#pragma once

#define GF_STATE_CLASS(name, Owner)                                                                                                                  \
public:                                                                                                                                              \
  static ai::State *create(void *buffer) { return new (buffer) name; }                                                                               \
  const char *getName() const override { return #name; }                                                                                             \
  void onEnter(void *owner, ai::State *previous) override { enter(static_cast<Owner *>(owner), previous); }                                          \
  void onLeave(void *owner, ai::State *next) override { leave(static_cast<Owner *>(owner), next); }                                                  \
  void onStep(void *owner, const void *param) override { update(static_cast<Owner *>(owner), *static_cast<const fw::UpdateInfo *>(param)); }
