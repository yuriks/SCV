#ifndef __SCV_KEY_EVENT_H__
#define __SCV_KEY_EVENT_H__

namespace scv {

//! Contains information about a keyboard event.
struct KeyEvent {
   enum State { UP, DOWN };

   KeyEvent(int key, int mod, bool special, KeyEvent::State state);

   std::string getKeyString() const;
   bool operator==(const KeyEvent& rhs);

   //! If true, key is a special function key (arrow, Fn, etc.)
   const bool special;
   //! The key pressed. If \c special is true then it is one of the \c GLUT_KEY_ constants in the GLUT header, else it is an ASCII code.
   const int keycode;
   //! OR-ed mask of \c GLUT_ACTIVE_ constants indicating the modifier keys held when the key was pressed.
   const int modifiers;
   //! Indicates if the key is being pressed or released.
   const KeyEvent::State state;
};

} // namespace scv

#endif // __SCV_KEY_EVENT_H__