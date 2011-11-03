#include "stdafx.h"
#include "Kernel.h"

#include "FontTahoma.h"

#include "MenuHolder.h"
#include "InternalFrameHolder.h"
#include "Component.h"

#include "Keyboard.h"
#include "GlslShader.h"

#include "util.h"

#include "FileOpen.h"

#include "Mathematic.h"

namespace scv {

const std::string Kernel::s_defaultTitle = "SCV - Simple Components for Visual - http://www-usr.inf.ufsm.br/~pozzer/scv/";
const unsigned int Kernel::s_defaultWidth  = 1280;
const unsigned int Kernel::s_defaultHeight = 720;
const unsigned int Kernel::s_defaultFramesPerSecond = 30;

Kernel::Kernel(void) {
   std::memset(_loadedWidgets, NULL, sizeof(ComponentTexture*) * NOFWIDGETS);

   _filterType = NEAREST;

   Mouse.locked = false;

   _needReshapeWindow = true;
   _isActiveReshape = true;
   _windowTitle = s_defaultTitle;
   FrameRate.fps = s_defaultFramesPerSecond;
   FrameRate.currFps = s_defaultFramesPerSecond;

   Display.currSize[0] = s_defaultWidth;
   Display.currSize[1] = s_defaultHeight;

   memcpy(Display.userSize, Display.currSize, sizeof(unsigned int) * 2);

   Display.isFullScreen = false;

   Mouse.clicked = false;
   Mouse.lastButton = MouseEvent::NBUTTON;

   _focusedComponent = NULL;
   _contextMenu = NULL;
   Mouse.lastClickPosition = Point(-1, -1);

   #ifdef _WIN32
      Mouse.doubleClickTime = GetDoubleClickTime();
   #else
      doubleClickTime = 500;
   #endif // _WIN32

   Keyboard::getInstance();

   showCopyrights();

   initOpenGL(0, NULL);
   GlslShader::init();

   FrameRate.baseTime = FrameRate.prevTime = FrameRate.currTime = glutGet(GLUT_ELAPSED_TIME);
   FrameRate.count = 0;

   _componentRequestFocus = false;
   Mouse.componentRequestUse = NULL;

   srand((int)time(NULL));
}

Kernel::~Kernel(void) {

}

void Kernel::onMouseClick(const scv::MouseEvent &evt) {}
void Kernel::onMouseHold(const scv::MouseEvent &evt) {}
void Kernel::onMouseOver(const scv::MouseEvent &evt) {}
void Kernel::onMouseUp(const scv::MouseEvent &evt) {}
void Kernel::onMouseWheel(const scv::MouseEvent &evt) {}

void Kernel::onKeyPressed(const scv::KeyEvent &evt) {}
void Kernel::onKeyUp(const scv::KeyEvent &evt) {}

void Kernel::onSizeChange(void) {}
void Kernel::onPositionChange(void) {}

std::string Kernel::getClipBoardString(void) const {
   #ifdef _WIN32
      if (OpenClipboard(NULL)) {
         HANDLE clip = GetClipboardData(CF_TEXT);
         GlobalLock(clip);
         CloseClipboard();
         if (clip == NULL) return std::string("");
         std::string clipBoard = std::string(static_cast<char*>(clip));
         size_t found;
         while (true) {
            found = clipBoard.find((char)(13));
            if (found != std::string::npos) clipBoard.erase(found,1);
            else break;
         }
         return clipBoard;
      } else {
         return std::string("null");
      }
   #else // UNIX
      return std::string("null");
   #endif // _WIN32
}

void Kernel::setClipBoardString(const std::string strData) {
   #ifdef _WIN32
      if (OpenClipboard(NULL)) {
         EmptyClipboard();
         HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, strData.size() + 1);
         char *pchData = static_cast<char*>(GlobalLock(hClipboardData));
         strcpy(pchData, LPCSTR(strData.c_str()));
         GlobalUnlock(hClipboardData);
         SetClipboardData(CF_TEXT, hClipboardData);
         CloseClipboard();
      }
   #else // UNIX
   #endif // _WIN32
}

void Kernel::initOpenGL(int argc, char* argv[]) {
   glutInit(&argc, argv);

   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowPosition (0, 0);
   glutCreateWindow (_windowTitle.c_str());

   // mouse
   glutPassiveMotionFunc(cbMouseMotion);
   glutMotionFunc(cbMouseMotion);
   glutMouseFunc(cbMouseClick);
   glutMouseWheelFunc(cbMouseWheel);

   // keyboard
   glutSpecialFunc(cbKeySpecial);
   glutSpecialUpFunc(cbKeySpecialUp);
   glutKeyboardFunc(cbKey);
   glutKeyboardUpFunc(cbKeyUp);

   glutReshapeFunc(cbReshape);
   glutDisplayFunc(cbDisplay);

   glutIdleFunc(cbDisplay);

   FontTahoma::getInstance();
   Cursor::getInstance();
}

void Kernel::run(void) {
   glutInitWindowSize(Display.currSize[0], Display.currSize[1]);
   glutMainLoop();
}

void Kernel::setWindowSize(unsigned int width, unsigned int height) {
   Display.userSize[0] = width;
   Display.userSize[1] = height;   
   glutReshapeWindow(width, height);
}

void Kernel::setFullScreen(bool full) {
   if (full == true && Display.isFullScreen == false) {
      Display.userSize[0] = Display.currSize[0];
      Display.userSize[1] = Display.currSize[1];
      glutFullScreen();
   } else if (full == false && Display.isFullScreen == true) {
      glutFullScreenToggle();
      glutPositionWindow(0,0);
      glutReshapeWindow(Display.userSize[0], Display.userSize[1]);
   }
   Display.isFullScreen = full;
}


void Kernel::updateFramesPerSecond(void) {
   FrameRate.count++;
   FrameRate.currTime = glutGet(GLUT_ELAPSED_TIME);

   int timeInterval;
      
   timeInterval = FrameRate.currTime - FrameRate.prevTime;
   if (timeInterval > 500.f) {
      FrameRate.currFps = FrameRate.count * 1000.f / (timeInterval);
      FrameRate.prevTime = FrameRate.currTime;
      FrameRate.count = 0;
   }

   timeInterval = FrameRate.currTime - FrameRate.baseTime;
   if (timeInterval < (1000.f / FrameRate.fps)) {
      #ifdef _WIN32
         Sleep((DWORD)(1000.f / FrameRate.fps) - timeInterval);
      #else // UNIX
         usleep(((1000.f / fps) - timeInterval) * 1000.f);
      #endif // _WIN32
      FrameRate.baseTime = glutGet(GLUT_ELAPSED_TIME);
   } else {
      FrameRate.baseTime = FrameRate.currTime;
   }
}

void Kernel::cbMouseMotion(int x, int y) {
   static Kernel *kernel = Kernel::getInstance();
   static Cursor *cursor = Cursor::getInstance();
   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->_componentRequestFocus = false;
   if (!kernel->Mouse.locked) {
      kernel->Mouse.componentRequestUse = NULL;
   }

   MouseEvent evt;
   if (kernel->Mouse.clicked) {
      evt = MouseEvent(kernel->Mouse.lastButton, MouseEvent::HOLD, Point(x, y));
   } else {
      evt = MouseEvent(MouseEvent::NBUTTON, MouseEvent::MOTION, Point(x, y));
   }

   if (menu->processMouse(evt) == false && window->processMouse(evt) == false) {
      //kernel callback
      if (evt.getState() == MouseEvent::HOLD) {
         kernel->onMouseHold(evt);
      } else if (evt.getState() == MouseEvent::MOTION) {
         kernel->onMouseOver(evt);
      }
      for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
         if ((*iter)->isVisible() && (*iter)->getCallbacksStatus()) {
            (*iter)->processMouse(evt);
         }
      }
   }

   cursor->setDefaultCursor();
}

void Kernel::cbMouseClick(int button, int state, int x, int y) {
   static Kernel *kernel = Kernel::getInstance();
   static Cursor *cursor = Cursor::getInstance();
   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->_componentRequestFocus = false;
   if (!kernel->Mouse.locked) {
      kernel->Mouse.componentRequestUse = NULL;
   }

   MouseEvent evt;
   if (kernel->Mouse.lastClickPosition == Point(x, y) && kernel->Mouse.lastTimeClicked.isRunning() &&
         kernel->Mouse.lastTimeClicked.getMilliseconds() <= kernel->Mouse.doubleClickTime && kernel->Mouse.lastButton == button &&
         static_cast<MouseEvent::State>(state) == MouseEvent::CLICK) {

      kernel->Mouse.lastTimeClicked.stop();
      kernel->Mouse.lastButton = static_cast<MouseEvent::Button>(button);
      evt = MouseEvent (kernel->Mouse.lastButton, MouseEvent::CLICK, Point(x, y), true);

   } else {
      if (static_cast<MouseEvent::State>(state) == MouseEvent::CLICK) {
         kernel->Mouse.lastTimeClicked.start();
         kernel->Mouse.lastClickPosition = Point(x, y);
      }
      kernel->Mouse.lastButton = static_cast<MouseEvent::Button>(button);
      evt = MouseEvent(kernel->Mouse.lastButton, static_cast<MouseEvent::State>(state), Point(x, y));
   }

   if (evt.getState() == MouseEvent::UP) {
      kernel->Mouse.clicked = false;
      if (menu->processMouse(evt) == false) {
         if (window->processMouse(evt) == false) {
            //kernel callback
            kernel->onMouseUp(evt);
            for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
               if ((*iter)->isVisible() && (*iter)->getCallbacksStatus())
                  (*iter)->processMouse(evt);
            }            
         }
      }
   } else {
      kernel->Mouse.clicked = true;

      Component *focusedComponent = kernel->getFocusedComponent();
      ComponentsList::reverse_iterator itUp = kernel->_objects.rbegin();

      if (menu->processMouse(evt) == false) {
         menu->closeAllMenus();
         if (window->processMouse(evt) == false) {
            //kernel callback
            kernel->onMouseClick(evt);
            for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
               if ((*iter)->isVisible() && (*iter)->getCallbacksStatus()) {
                  (*iter)->processMouse(evt);
                  if (focusedComponent != kernel->getFocusedComponent()) {
                     focusedComponent = kernel->getFocusedComponent();
                     itUp = iter;
                  }
               }
            }
            
            if (kernel->Mouse.componentRequestUse == NULL && kernel->_contextMenu != NULL && kernel->requestMouseUse(NULL) && evt.getButton() == MouseEvent::RIGHT)
               menu->activeMenu(kernel->_contextMenu, evt.getPosition());

            // swap clicked component to end
            if (itUp != kernel->_objects.rbegin() && (*itUp)->isDragging()) {
               kernel->_objects.splice(kernel->_objects.end(), kernel->_objects, (++itUp).base());
            }
         }
      }
   }

   if (evt.getState() == MouseEvent::CLICK && kernel->_componentRequestFocus == false) {
      kernel->Mouse.componentRequestUse = NULL;
      kernel->_focusedComponent = NULL;
      kernel->Mouse.locked = false;
   }

   cursor->setDefaultCursor();
}

void Kernel::cbMouseWheel(int button, int dir, int x, int y) {
   static Kernel* kernel = Kernel::getInstance();
   static Cursor *cursor = Cursor::getInstance();
   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->_componentRequestFocus = false;
   if (!kernel->Mouse.locked) {
      kernel->Mouse.componentRequestUse = NULL;
   }

   MouseEvent evt;
   if (dir == 1) {
      evt = MouseEvent(MouseEvent::NBUTTON, MouseEvent::WHELLUP, Point(x, y));
   } else {
      evt = MouseEvent(MouseEvent::NBUTTON, MouseEvent::WHEELDOWN, Point(x, y));
   }

   if (menu->processMouse(evt) == false && window->processMouse(evt) == false) {
      //kernel callback
      kernel->onMouseWheel(evt);
      for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
         if ((*iter)->isVisible() && (*iter)->getCallbacksStatus()) {
            (*iter)->processMouse(evt);
         }
      }      
   }
   cursor->setDefaultCursor();
}


void Kernel::cbKeySpecial(int key, int x, int y) {
   static Kernel* kernel = Kernel::getInstance();
   static Cursor* cursor = Cursor::getInstance();
   static Keyboard *keyboard = Keyboard::getInstance();

   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->_componentRequestFocus = false;

   // insert
   if (key == 108) cursor->swapInsertState();

   KeyEvent evt(key, glutGetModifiers(), true, KeyEvent::DOWN);

   if (menu->processKey(evt) == false && window->processKey(evt) == false) {
      //kernel callback
      kernel->onKeyPressed(evt);
      keyboard->push(key, true);
      for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
         if ((*iter)->isVisible() && (*iter)->getCallbacksStatus()) {
            (*iter)->processKey(KeyEvent(key, glutGetModifiers(), true, KeyEvent::DOWN));
         }
      }
   }
}

void Kernel::cbKeySpecialUp(int key, int x, int y) {
   static Kernel* kernel = Kernel::getInstance();
   static Keyboard *keyboard = Keyboard::getInstance();

   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->_componentRequestFocus = false;

   KeyEvent evt(key, glutGetModifiers(), true, KeyEvent::UP);

   if (menu->processKey(evt) == false && window->processKey(evt) == false) {
      //kernel callback
      kernel->onKeyUp(evt);
      keyboard->pop(key, true);
      for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
         if ((*iter)->isVisible() && (*iter)->getCallbacksStatus()) {
            (*iter)->processKey(KeyEvent(key, glutGetModifiers(), true, KeyEvent::UP));
         }
         
      }      
   }
}

void Kernel::cbKey(unsigned char key, int x, int y) {
   static Kernel* kernel = Kernel::getInstance();
   static Keyboard *keyboard = Keyboard::getInstance();

   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->_componentRequestFocus = false;

   KeyEvent evt(key, glutGetModifiers(), false, KeyEvent::DOWN);

   if (menu->processKey(evt) == false && window->processKey(evt) == false) {
      //kernel callback
      kernel->onKeyPressed(evt);
      keyboard->push(key, false);
      for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
         if ((*iter)->isVisible() && (*iter)->getCallbacksStatus()) {
            (*iter)->processKey(KeyEvent(key, glutGetModifiers(), false, KeyEvent::DOWN));
         }
      }      
   }
}

void Kernel::cbKeyUp(unsigned char key, int x, int y) {
   static Kernel* kernel = Kernel::getInstance();
   static Keyboard *keyboard = Keyboard::getInstance();

   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->_componentRequestFocus = false;

   KeyEvent evt(key, glutGetModifiers(), false, KeyEvent::UP);

   if (menu->processKey(evt) == false && window->processKey(evt) == false) {
      //kernel callback
      kernel->onKeyUp(evt);
      keyboard->pop(key, false);
      for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
         if ((*iter)->isVisible() && (*iter)->getCallbacksStatus()) {
            (*iter)->processKey(KeyEvent(key, glutGetModifiers(), false, KeyEvent::UP));
         }
      }      
   }
}

void Kernel::cbReshape(int w, int h) {
   static Kernel* kernel = Kernel::getInstance();

   if (!kernel->_isActiveReshape && (w != kernel->Display.currSize[0] || h != kernel->Display.currSize[1]))
      kernel->_needReshapeWindow = true;

   kernel->Display.currSize[0] = w;
   kernel->Display.currSize[1] = h;
   kernel->Display.userSize[0] = w;
   kernel->Display.userSize[1] = h;

   kernel->onSizeChange();
}

void Kernel::cbDisplay(void) {
   static Kernel* kernel = Kernel::getInstance();
   static Cursor* cursor = Cursor::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   if (kernel->_needReshapeWindow) {
      glutReshapeWindow(kernel->Display.userSize[0],kernel->Display.userSize[1]);
      kernel->_needReshapeWindow = false;
   }

   kernel->updateFramesPerSecond();

   cursor->requestResetCursor();
   cursor->refreshMouse();

   scheme->applyColor(ColorScheme::BACKGROUND);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   kernel->applyDefaultTransformMatrix();

   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);

   for (ComponentsList::iterator iter = kernel->_objects.begin(); iter != kernel->_objects.end(); ++iter) {
      if (kernel->willAppearOnScreen(*iter))
         (*iter)->display();
   }

   window->display();
   menu->display();

   glDisable(GL_BLEND);
   glutSwapBuffers();
}

void Kernel::addComponent(Component *object) {
   if (std::find(Kernel::getInstance()->_objects.begin(), Kernel::getInstance()->_objects.end(), object) == Kernel::getInstance()->_objects.end()
         && object->getParent() == NULL) {
      _objects.push_back(object);
   }
}

void Kernel::removeComponent(Component *object) {
   if (std::find(Kernel::getInstance()->_objects.begin(), Kernel::getInstance()->_objects.end(), object) != Kernel::getInstance()->_objects.end()) {
      Kernel::getInstance()->_objects.remove(object);      
   } else if (object->getParent() != NULL) {
      object->getParent()->removeChild(object);
   }
}

bool Kernel::requestComponentFocus(Component* component) {
   if (component == NULL) false;

   static Keyboard *keyboard = Keyboard::getInstance();

   if (_componentRequestFocus == false) {
      if (_focusedComponent != NULL && _focusedComponent != component && keyboard->isEmpty() == false) {
         std::deque<Keyboard::KeyboardControl> keys = keyboard->clear();
         for (int i = 0; i < keys.size(); i++)
            _focusedComponent->processKey(KeyEvent(keys[i].key, glutGetModifiers(), keys[i].special, KeyEvent::UP));
      }
      _focusedComponent = component;
      _componentRequestFocus = true;
      return true;
   } else {
      return false;
   }
}

void Kernel::applyDefaultTransformMatrix(void) {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, Display.currSize[0], Display.currSize[1], 0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glViewport(0, 0, Display.currSize[0], Display.currSize[1]);
}

void Kernel::showCopyrights(void) {
   // free image credits
   std::cout << FreeImage_GetCopyrightMessage() << std::endl;
}

void Kernel::setWindowTitle(const std::string &title) {
   glutSetWindowTitle(title.c_str());
}

void Kernel::addWindow(InternalFrame *window) {
   static InternalFrameHolder *winHolder = InternalFrameHolder::getInstance();
   winHolder->registerFrame(window);
}


bool Kernel::lockMouseUse(Component* component) {
   if (!Mouse.locked || component == Mouse.componentRequestUse) {
      Mouse.locked = true;
      Mouse.componentRequestUse = component;
      return true;
   } else {
      return false;
   }
}

bool Kernel::unlockMouseUse(Component* component) {
   if (component == Mouse.componentRequestUse) {
      Mouse.locked = false;
      return true;
   } else {
      return false;
   }
}

bool Kernel::requestMouseUse(Component* component) {
   if (Mouse.componentRequestUse == NULL) {
      Mouse.componentRequestUse = component;
      return true;
   } else if (Mouse.componentRequestUse == component) {
      return true;
   } else {
      return false;
   }
}

bool Kernel::willAppearOnScreen(Component* component) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();

   if (component->isVisible()) {
      Point absPosition = component->getAbsolutePosition();
      Point invPosition = absPosition.inverse();
      if (absPosition.x > Display.currSize[0] || absPosition.y > Display.currSize[1] ||             
            (absPosition.x + component->getWidth()) < 0 || (absPosition.y + component->getHeight()) < 0 ||
            !math::isInside(Point(scissor->currentScissor().x, scissor->currentScissor().y).inverse() - Point(0, scissor->currentScissor().height), Point(scissor->currentScissor().width, scissor->currentScissor().height), absPosition, component->getSize())) {
         return false;
      } else {
         return true;
      }
   } else {
      return false;
   }
}

void Kernel::lockWindowSize(bool lock) {
   _isActiveReshape = !lock;
}

void Kernel::OpenFile(void) {
   static FileOpen *fileOp = FileOpen::getInstance();
   fileOp->getItem();
}

} // namespace scv