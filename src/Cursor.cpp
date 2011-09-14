#include "stdafx.h"
#include "Cursor.h"
#include "Kernel.h"

namespace scv {

Cursor::Cursor(void) {
   _cursorTexture = NULL;

   _requestedCursorChange = false;

#ifdef _WIN32
   _blinkTime = GetCaretBlinkTime();
#else
   _blinkTime = 700;
#endif // _WIN32

   _timebase = _time = glutGet(GLUT_ELAPSED_TIME);
   _isShowingCursor = true;
   _cursorInMovement = false;

   _insert = false;

   genTexture();
}

void Cursor::refreshMouse(void)  {
   static Kernel *kernel = Kernel::getInstance();
   _time = glutGet(GLUT_ELAPSED_TIME);
   if ((_time - _timebase) >= _blinkTime) {
      _timebase = _time;
      if (_cursorInMovement == false) {
         _isShowingCursor = !_isShowingCursor;
      } else {
         _cursorInMovement = false;
      }
   }
}

void Cursor::genTexture(void) {
   _cursorTexture = new ComponentTexture(2, 2);
   _cursorTexture->setTextureEnvMode(GL_MODULATE);

   _cursorTexture->addTexture(Point(0,0), MatrixTemplate<ColorRGBA>(1, 1, ColorRGBA(255, 255, 255, 255)));
}

} // namespace scv