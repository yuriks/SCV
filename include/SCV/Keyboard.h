#ifndef __SCV_KEYBOARD_H__
#define __SCV_KEYBOARD_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Singleton.h"
#include "KeyEvent.h"
#include <deque>
#endif // DOXYGEN_SKIP_THIS

#define GLUT_KEY_BACK_SPACE	  8
#define GLUT_KEY_TAB          9
#define GLUT_KEY_ENTER		  13
#define GLUT_KEY_ESC		  27
#define GLUT_KEY_SPACE	      32
#define GLUT_KEY_DEL		  127

namespace scv {

/*! A class that controls the keyboard.
 * \ingroup internal
 */

class Keyboard : public Singleton<Keyboard> {
friend class Singleton<Keyboard>;
public:

   /*! A class that controls the input keyboard.
   * \ingroup internal
    */

   class KeyboardControl {
   public:
      KeyboardControl(int key, bool special) {
         this->key = key; this->special = special;
      }
      bool operator==(const KeyboardControl& rhs) const {
         return (key == rhs.key && special == rhs.special)? true : false;
      }
      int key;
      bool special;
   };

   bool isEmpty(void);

   std::deque<KeyboardControl> clear(void);
   void pop(int key, bool special);
   void push(int key, bool special);

protected:
   Keyboard(void);

private:
   std::deque<KeyboardControl> _keyPressed;
};

} // namespace scv

#endif // __SCV_KEYBOARD_H__