#include "stdafx.h"
#include "KeyEvent.h"

#include "util.h"

namespace scv {

KeyEvent::KeyEvent(int key, int mod, bool special, KeyEvent::State state) :
      _key(key), _modifiers(mod), _special(special), _state(state) {
}


KeyEvent::~KeyEvent(void) {
}

std::string KeyEvent::getKeyString(void) const {
   if (isSpecial()) {
      switch(_key) {
         case GLUT_KEY_F1:        return std::string("F1");            break;
         case GLUT_KEY_F2:        return std::string("F2");            break;
         case GLUT_KEY_F3:        return std::string("F3");            break;
         case GLUT_KEY_F4:        return std::string("F4");            break;
         case GLUT_KEY_F5:        return std::string("F5");            break;
         case GLUT_KEY_F6:        return std::string("F6");            break;
         case GLUT_KEY_F7:        return std::string("F7");            break;
         case GLUT_KEY_F8:        return std::string("F8");            break;
         case GLUT_KEY_F9:        return std::string("F9");            break;
         case GLUT_KEY_F10:       return std::string("F10");           break;
         case GLUT_KEY_F11:       return std::string("F11");           break;
         case GLUT_KEY_F12:       return std::string("F12");           break;
         case GLUT_KEY_LEFT:      return std::string("Left");          break;
         case GLUT_KEY_UP:        return std::string("Up");            break;
         case GLUT_KEY_RIGHT:     return std::string("Right");         break;
         case GLUT_KEY_DOWN:      return std::string("Down");          break;
         case GLUT_KEY_PAGE_UP:   return std::string("Page Up");       break;
         case GLUT_KEY_PAGE_DOWN: return std::string("Page Down");     break;
         case GLUT_KEY_HOME:      return std::string("Home");          break;
         case GLUT_KEY_END:       return std::string("End");           break;
         case GLUT_KEY_INSERT:    return std::string("Insert");        break;
         // freeglut ext
         case GLUT_KEY_NUM_LOCK:  return std::string("Num Lock");      break;
         case GLUT_KEY_BEGIN:     return std::string("Begin");         break;
         case GLUT_KEY_DELETE:    return std::string("Delete");        break;
         // default
         default:                 return std::string("ERROR");         break;
      }
   } else if (_key == 8) { return "Backspace";
   } else if (_key == 9) { return "Tab";
   } else if (_key == 13) { return "Enter";
   } else if (_key == 27) { return "Esc";
   } else if (_key == 32) { return "Space Bar";
   } else { return toString(_key);
   }
}

int KeyEvent::getKeyCode(void) const {
   return _key;
}

int KeyEvent::getModifier(void) const {
   return _modifiers;
}

KeyEvent::State KeyEvent::getState(void) const {
   return _state;
}

bool KeyEvent::isSpecial(void) const {
   return _special;
}

bool KeyEvent::operator==(const KeyEvent& rhs) {
   return (_key == rhs._key && _special == rhs._special &&
      _modifiers == rhs._modifiers && _state == rhs._state)? true : false;
}

} // namespace scv
