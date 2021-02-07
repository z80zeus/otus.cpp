#include "widget.h"

using namespace std;
using namespace z80;

void
widget::draw() {
  if (!isVisible()) return;
  for (const auto& child: children)
    child->draw();
}

void
widget::show() {
  visible = true;
}

void
widget::hide() {
  visible = false;
}

bool
widget::isVisible() {
  return visible;
}
