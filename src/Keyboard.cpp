#include "stdafx.h"
#include "Keyboard.h"

#include <algorithm>

namespace scv {

Keyboard::Keyboard(void) {
   //none
}

bool Keyboard::isEmpty(void) {
   return _keyPressed.empty();
}

std::deque<Keyboard::KeyboardControl> Keyboard::clear(void) {
   std::deque<Keyboard::KeyboardControl> keys = _keyPressed;
   _keyPressed.clear();
   return keys;
}

void Keyboard::pop(int key, bool special) {
   std::deque<KeyboardControl>::iterator it = std::find(_keyPressed.begin(), _keyPressed.end(), KeyboardControl(key, special));
   if (it != _keyPressed.end()) _keyPressed.erase(it);
}

void Keyboard::push(int key, bool special) {
   _keyPressed.push_back(Keyboard::KeyboardControl(key, special));
}

} // namespace scv