#pragma once

namespace fw {
class UpdatableObject;
}

namespace ui {
class UIObjectAcc;
}

namespace minigame {
namespace tora {
namespace factory {

fw::UpdatableObject *create(ui::UIObjectAcc *parent);

} // namespace factory
} // namespace tora
} // namespace minigame
