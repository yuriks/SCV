/*!
\file       Cursor.h
\brief      Implementation of the SCV Cursor.
\author     SCV Team
*/

#ifndef __SCV_CURSOR_H__
#define __SCV_CURSOR_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Singleton.h"
#include "Point.h"

#include "ColorScheme.h"
#include "ComponentTexture.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

class Kernel;

/*! Cursor Class
 * \ingroup internal
 */

class Cursor : public Singleton<Cursor> {
friend class Singleton<Cursor>;
friend class Kernel;
public:

   inline void requestResetCursor(void) {
      _requestedCursorChange = false;
   }

   inline void setDefaultCursor(void) {
      if (_requestedCursorChange == false)
         glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
   }

   inline void requestDefaultCursor(void) {
      glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
      _requestedCursorChange = true;
   }

   inline void setGlutCursor(int cursor) {
      if (_requestedCursorChange == false)
         glutSetCursor(cursor);
      _requestedCursorChange = true;
   }

   inline void forceGlutCursor(int cursor) {
      glutSetCursor(cursor);
      _requestedCursorChange = true;
   }

   inline bool isInsertActive(void) const {
      return _insert;
   }

   inline void swapInsertState(void) {
      _insert =! _insert;
   }

   inline void cursorInMovement(void) {
      _isShowingCursor = true;
      _cursorInMovement = true;
   }

   inline void display(const Point &p) {
      static ColorScheme *scheme = ColorScheme::getInstance();
      if (_isShowingCursor) {
         _cursorTexture->enable();
         scheme->applyColor(ColorScheme::CURSOR);
         _cursorTexture->display(Point(p.x,p.y+2), 0, Point(1, 14));
         _cursorTexture->disable();
      }
   }

private:
   Cursor(void);

   void genTexture(void);

   void refreshMouse(void);

   bool _requestedCursorChange;
   bool _insert;
   bool _isShowingCursor;
   bool _cursorInMovement;

   int _time, _timebase;
   unsigned int _blinkTime;

   ComponentTexture *_cursorTexture;
};

} // namespace scv

#endif // __SCV_CURSOR_H__