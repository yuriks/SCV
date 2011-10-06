#ifndef __SCV_KEY_EVENT_H__
#define __SCV_KEY_EVENT_H__

namespace scv {

class KeyEvent {
public:
   enum State {
      UP, DOWN,
   };

   KeyEvent(int key, int mod, bool special, KeyEvent::State state);

   std::string getKeyString(void) const;
   int getKeyCode(void) const;
   int getModifier(void) const;
   KeyEvent::State getState(void) const;
   bool isSpecial(void) const;

   bool operator==(const KeyEvent& rhs);

private:
   const int _key;
   const bool _special;
   const int _modifiers;
   const KeyEvent::State _state;
};

} // namespace scv

#endif // __SCV_KEY_EVENT_H__