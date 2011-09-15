/*!
\file       MouseEvent.h
\brief      Implementation of the Key Event.
\author     SCV Team
*/

#ifndef __SCV_KEY_EVENT_H__
#define __SCV_KEY_EVENT_H__

/*

GetKeyString() returns:

"F1"
"F2"
"F3"
"F4"
"F5"
"F6"
"F7"
"F8"
"F9"
"F10"
"F11"
"F12"
"Left"
"Up"
"Right"
"Down"
"Page Up"
"Page Down"
"Home"
"End"
"Insert"
"Num Lock"
"Begin"
"Delete"
"Space Bar"

*/


namespace scv {

/*! A class that store all interaction with the keyboard in a object.
 \ingroup internal
*/

class KeyEvent {
public:
   enum states {
      up,
      down,
   };

   KeyEvent(int key, int mod, bool special, KeyEvent::states state);

   std::string getKeyString(void) const;
   int getKeyCode(void) const;
   int getModifier(void) const;
   KeyEvent::states getState(void) const;
   bool isSpecial(void) const;

   bool operator==(const KeyEvent& rhs);

private:
   const int _key;
   const bool _special;
   const int _modifiers;
   const KeyEvent::states _state;
};

} // namespace scv

#endif // __SCV_KEY_EVENT_H__