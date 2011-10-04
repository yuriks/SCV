#ifndef __SCV_SPRING_H__
#define __SCV_SPRING_H__

namespace scv {

class Spring {
public:
   ///////////////////////////////////////////////////////////
   enum Alignment {
      BASELINE, CENTER, LEADING, TRAILING, NONE
   };

   enum Size {
      UNSET = INT_MIN,
      DEFAULT_SIZE = -1,
      PREFERRED_SIZE = -2
   };

   enum Axis {
      HORIZONTAL, VERTICAL
   };
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   Spring(void);
   virtual ~Spring(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual int calculateMinimumSize(Axis axis) = 0;
   virtual int calculatePreferredSize(Axis axis) = 0;
   virtual int calculateMaximumSize(Axis axis) = 0;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   int getMinimumSize(Axis axis);
   int getPreferredSize(Axis axis);
   int getMaximumSize(Axis axis);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual inline void setAlignment(Alignment alignment);
   virtual inline Alignment getAlignment(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual inline void setSize(Axis axis, int origin, int size);
   virtual inline void unset(void);
   virtual inline int getSize(void) const;
   ///////////////////////////////////////////////////////////

protected:
   inline int constrain(int value);
   bool isResizable(Axis axis);

   Alignment _alignment;
   int _size, _min, _max, _pref;
private:
};

///////////////////////////////////////////////////////////
void Spring::setAlignment(Spring::Alignment alignment) {
   _alignment = alignment;
}

Spring::Alignment Spring::getAlignment(void) const {
   return _alignment;
}

void Spring::setSize(Axis axis, int origin, int size) {
   _size = size;
   if (size == UNSET) {
      unset();
   }
}

void Spring::unset(void) {
   _size = _min = _pref = _max = UNSET;
}

int Spring::getSize(void) const {
   return _size;
}

int Spring::constrain(int value) {
   return std::min(value, INT_MAX);   
}
///////////////////////////////////////////////////////////

} //namespace scv

#endif //__SCV_SPRING_H__