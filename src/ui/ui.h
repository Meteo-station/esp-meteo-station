#pragma once

#include "../core/app.h"

namespace UI {

// Инициализация UI
void init();

// Рендер текущего состояния (только если dirty флаги установлены)
void render(AppState& state);

// Применить состояние подсветки
void applyBacklight(bool on);

} // namespace UI


