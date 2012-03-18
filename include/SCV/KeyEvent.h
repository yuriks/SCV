#ifndef __SCV_KEY_EVENT_H__
#define __SCV_KEY_EVENT_H__

namespace scv {

struct KeyEvent {
   enum State { UP, DOWN };

   KeyEvent(int key, int mod, bool special, KeyEvent::State state);

   std::string getKeyString() const;
   bool operator==(const KeyEvent& rhs);

   const int keycode;
   const bool special;
   const int modifiers;
   const KeyEvent::State state;
};

} // namespace scv

#endif // __SCV_KEY_EVENT_H__