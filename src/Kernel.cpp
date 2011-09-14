#include "stdafx.h"
#include "Kernel.h"

#include "FontTahoma.h"

#include "MenuHolder.h"
#include "InternalFrameHolder.h"
#include "ComponentInterface.h"
#include "SCVObject.h"

#include "Keyboard.h"
#include "GlslShader.h"

#include "CodeGenerator.h"
#include "util.h"

#include "FileOpen.h"

#include "DynamicCastIterator.h"
#include "SCVObject.h"

#include "Mathematic.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <GL/glew.h>
#include <GL/freeglut.h>

namespace scv {

const std::string Kernel::s_defaultTitle = "SCV Demo Version 3.0a";
const unsigned int Kernel::s_defaultWidth  = 1280;
const unsigned int Kernel::s_defaultHeight = 720;
const unsigned int Kernel::s_defaultFramesPerSecond = 45;

Kernel::Kernel(void) : mainPanel(NULL) {
   std::memset(_loadedWidgets, NULL, sizeof(ComponentTexture*) * s_nOfWidgets);

   _filterType = nearest;

   _mouseLocked = false;

   NeedRefreshReshape = true;
   isActiveReshape = true;
   _windowTitle = s_defaultTitle;
   _framesPerSecond = s_defaultFramesPerSecond;
   _currFramesPerSecond = s_defaultFramesPerSecond;

   _currScreenSize[0] = s_defaultWidth;
   _currScreenSize[1] = s_defaultHeight;

   memcpy(_userScreenSize, _currScreenSize, sizeof(unsigned int) * 2);

   isFullScreen = false;

   _scissorNeedRefresh = true;

   mouseClicked = false;
   lastButton = MouseEvent::none;

   _focusedComponent = NULL;
   _contextMenu = NULL;
   lastClickPosition = Point(-1, -1);

   #ifdef _WIN32
      doubleClickTime = GetDoubleClickTime();
   #else
      doubleClickTime = 500;
   #endif // _WIN32

   Keyboard::getInstance();

   showCopyrights();

   initOpenGL(0, NULL);
   GlslShader::init();

   _baseTime = _previousTime = _currentTime = glutGet(GLUT_ELAPSED_TIME);
   _frameCount = 0;

   anyComponentRequestFocus = false;
   componentRequestMouseUse = NULL;

   srand((int)time(NULL));
   currentPanel = -1;
}



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
   #else // linux
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
   #else // linux
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
   glutInitWindowSize(_currScreenSize[0], _currScreenSize[1]);
   glutMainLoop();
}

void Kernel::setWindowSize(unsigned int width, unsigned int height) {
   _userScreenSize[0] = width;
   _userScreenSize[1] = height;
   glutReshapeWindow(width, height);
}

void Kernel::setFullScreen(bool full) {
   if (full == true && isFullScreen == false) {
      _userScreenSize[0] = _currScreenSize[0];
      _userScreenSize[1] = _currScreenSize[1];
      glutFullScreen();
   } else if (full == false && isFullScreen == true) {
      glutFullScreenToggle();
      glutPositionWindow(0,0);
      glutReshapeWindow(_userScreenSize[0], _userScreenSize[1]);
   }
   isFullScreen = full;
}


void Kernel::setFramesPerSecond(float fps) {
   _framesPerSecond = fps;
}

void Kernel::updateFramesPerSecond(void) {
   _frameCount++;
   _currentTime = glutGet(GLUT_ELAPSED_TIME);

   int timeInterval;

   /*
      frames per half a second, is this right? =D
   */
   timeInterval = _currentTime - _previousTime;
   if (timeInterval > 500.f) {
      _currFramesPerSecond = _frameCount * 1000.f / (timeInterval);
      _previousTime = _currentTime;
      _frameCount = 0;
   }

   timeInterval = _currentTime - _baseTime;
   if (timeInterval < (1000.f / _framesPerSecond)) {
      #ifdef _WIN32
         Sleep((DWORD)(1000.f / _framesPerSecond) - timeInterval);
      #else // linux
         usleep(((1000.f / _framesPerSecond) - timeInterval) * 1000.f);
      #endif // _WIN32
      _baseTime = glutGet(GLUT_ELAPSED_TIME);
   } else {
      _baseTime = _currentTime;
   }
}

void Kernel::cbMouseMotion(int x, int y) {
   static Kernel *kernel = Kernel::getInstance();
   static Cursor *cursor = Cursor::getInstance();
   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->anyComponentRequestFocus = false;
   if (!kernel->_mouseLocked) {
      kernel->componentRequestMouseUse = NULL;
   }

   MouseEvent evt;
   if (kernel->mouseClicked) {
      evt = MouseEvent(kernel->lastButton, MouseEvent::hold, Point(x, y));
   } else {
      evt = MouseEvent(MouseEvent::none, MouseEvent::motion, Point(x, y));
   }

   if (menu->processMouse(evt) == false && window->processMouse(evt) == false) {
      for (std::deque<ComponentInterface*>::reverse_iterator it = kernel->_components.rbegin(); it < kernel->_components.rend(); it++) {
            (*it)->processMouse(evt);
      }
   }

   cursor->setDefaultCursor();
   kernel->_scissorNeedRefresh = false;

}

void Kernel::cbMouseClick(int button, int state, int x, int y) {
   static Kernel *kernel = Kernel::getInstance();
   static Cursor *cursor = Cursor::getInstance();
   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->anyComponentRequestFocus = false;
   if (!kernel->_mouseLocked) {
      kernel->componentRequestMouseUse = NULL;
   }

   MouseEvent evt;
   if (kernel->lastClickPosition == Point(x, y) && kernel->lastTimeClicked.isRunning() &&
         kernel->lastTimeClicked.getMilliseconds() <= kernel->doubleClickTime && kernel->lastButton == button &&
         static_cast<MouseEvent::state>(state) == MouseEvent::click) {

      kernel->lastTimeClicked.stop();
      kernel->lastButton = static_cast<MouseEvent::button>(button);
      evt = MouseEvent (kernel->lastButton, MouseEvent::click, Point(x, y), true);

   } else {
      if (static_cast<MouseEvent::state>(state) == MouseEvent::click) {
         kernel->lastTimeClicked.start();
         kernel->lastClickPosition = Point(x, y);
      }
      kernel->lastButton = static_cast<MouseEvent::button>(button);
      evt = MouseEvent(kernel->lastButton, static_cast<MouseEvent::state>(state), Point(x, y));
   }

   if (evt.getState() == MouseEvent::up) {

      kernel->mouseClicked = false;
      if (menu->processMouse(evt) == false) {
         if (window->processMouse(evt) == false) {
            for (std::deque<ComponentInterface*>::reverse_iterator it = kernel->_components.rbegin(); it < kernel->_components.rend(); it++) {
                  (*it)->processMouse(evt);
            }
         }
      }
   } else {
      kernel->mouseClicked = true;

      ComponentInterface *focusedComponent = kernel->getFocusedComponent();
      std::deque<ComponentInterface*>::reverse_iterator itUp = kernel->_components.rbegin();

      if (menu->processMouse(evt) == false) {
         menu->closeAllMenus();
         if (window->processMouse(evt) == false) {
            for (std::deque<ComponentInterface*>::reverse_iterator it = kernel->_components.rbegin(); it < kernel->_components.rend(); it++) {
                  (*it)->processMouse(evt);
                  if (focusedComponent != kernel->getFocusedComponent()) {
                     focusedComponent = kernel->getFocusedComponent();
                     itUp = it;
                  }
            }

            if (kernel->componentRequestMouseUse == NULL && kernel->_contextMenu != NULL && kernel->requestMouseUse(NULL) && evt.getButton() == MouseEvent::right)
               menu->activeMenu(kernel->_contextMenu, evt.getPosition());

            // swap clicked component to top
            if (itUp != kernel->_components.rbegin() && (*itUp)->isDragging()) {
               ComponentInterface *component = *itUp;
               kernel->_components.erase(itUp.base() - 1);
               kernel->_components.push_back(component);
            }
         }
      }
   }

   if (evt.getState() == MouseEvent::click && kernel->anyComponentRequestFocus == false) {
      kernel->componentRequestMouseUse = NULL;
      kernel->_focusedComponent       = NULL;
      kernel->_mouseLocked            = false;
   }

   cursor->setDefaultCursor();
   kernel->_scissorNeedRefresh = false;
}

void Kernel::cbMouseWheel(int button, int dir, int x, int y) {
   static Kernel* kernel = Kernel::getInstance();
   static Cursor *cursor = Cursor::getInstance();
   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->anyComponentRequestFocus = false;
   if (!kernel->_mouseLocked) {
      kernel->componentRequestMouseUse = NULL;
   }

   MouseEvent evt;
   if (dir == 1) {
      evt = MouseEvent(MouseEvent::none, MouseEvent::wheelup, Point(x, y));
   } else {
      evt = MouseEvent(MouseEvent::none, MouseEvent::wheeldown, Point(x, y));
   }

   if (menu->processMouse(evt) == false && window->processMouse(evt) == false) {
      for (std::deque<ComponentInterface*>::reverse_iterator it = kernel->_components.rbegin(); it < kernel->_components.rend(); it++) {
            (*it)->processMouse(evt);
      }
   }
   cursor->setDefaultCursor();
   kernel->_scissorNeedRefresh = false;
}


void Kernel::cbKeySpecial(int key, int x, int y) {
   static Kernel* kernel = Kernel::getInstance();
   static Cursor* cursor = Cursor::getInstance();
   static Keyboard *keyboard = Keyboard::getInstance();

   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->anyComponentRequestFocus = false;

   // insert
   if (key == 108) cursor->swapInsertState();

   KeyEvent evt(key, glutGetModifiers(), true, KeyEvent::down);

   if (menu->processKey(evt) == false && window->processKey(evt) == false) {
      keyboard->push(key, true);
      for (int index = kernel->_components.size() - 1;  index >= 0; --index) {
            kernel->_components[index]->processKey(KeyEvent(key, glutGetModifiers(), true, KeyEvent::down));
      }
   }
}

void Kernel::cbKeySpecialUp(int key, int x, int y) {
   static Kernel* kernel = Kernel::getInstance();
   static Keyboard *keyboard = Keyboard::getInstance();

   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->anyComponentRequestFocus = false;

   KeyEvent evt(key, glutGetModifiers(), true, KeyEvent::up);

   if (menu->processKey(evt) == false && window->processKey(evt) == false) {
      keyboard->pop(key, true);
      for (int index = kernel->_components.size() - 1;  index >= 0; --index) {
            kernel->_components[index]->processKey(KeyEvent(key, glutGetModifiers(), true, KeyEvent::up));
      }
   }
}

void Kernel::cbKey(unsigned char key, int x, int y) {
   static Kernel* kernel = Kernel::getInstance();
   static Keyboard *keyboard = Keyboard::getInstance();

   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->anyComponentRequestFocus = false;

   KeyEvent evt(key, glutGetModifiers(), false, KeyEvent::down);

   if (menu->processKey(evt) == false && window->processKey(evt) == false) {
      keyboard->push(key, false);
      for (int index = kernel->_components.size() - 1;  index >= 0; --index) {
            kernel->_components[index]->processKey(KeyEvent(key, glutGetModifiers(), false, KeyEvent::down));
      }
   }
}

void Kernel::cbKeyUp(unsigned char key, int x, int y) {
   static Kernel* kernel = Kernel::getInstance();
   static Keyboard *keyboard = Keyboard::getInstance();

   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   kernel->anyComponentRequestFocus = false;

   KeyEvent evt(key, glutGetModifiers(), false, KeyEvent::up);

   if (menu->processKey(evt) == false && window->processKey(evt) == false) {
      keyboard->pop(key, false);
      for (int index = kernel->_components.size() - 1;  index >= 0; --index) {
            kernel->_components[index]->processKey(KeyEvent(key, glutGetModifiers(), false, KeyEvent::up));
      }
   }
}

void Kernel::cbReshape(int w, int h) {
   static Kernel* kernel = Kernel::getInstance();
   static int _w = w;
   static int _h = h;
   if (!kernel->isActiveReshape && (w != kernel->_currScreenSize[0] || h != kernel->_currScreenSize[1]))
      kernel->NeedRefreshReshape = true;

   kernel->_currScreenSize[0] = w;
   kernel->_currScreenSize[1] = h;
   kernel->_userScreenSize[0] = w;
   kernel->_userScreenSize[1] = h;
   kernel->_scissorNeedRefresh = true;

   kernel->mainPanel->setWidth(w);
   kernel->mainPanel->setHeight(h);

   /*
   kernel->mainPanel->_isResizing = true;
   if(_h != h)
      kernel->mainPanel->_resizing[3] = true;
   if(_w != w)
      kernel->mainPanel->_resizing[1] = true;
   MouseEvent evt = MouseEvent(MouseEvent::left, MouseEvent::hold, Point(w, h));
   kernel->mainPanel->processMouse(evt);
   kernel->mainPanel->_resizing[3] = false;
   kernel->mainPanel->_resizing[1] = false;
   kernel->mainPanel->_isResizing = false;
   _w = w;
   _h = h;
   */
}

void Kernel::cbDisplay(void) {

   static Kernel* kernel = Kernel::getInstance();
   static Cursor* cursor = Cursor::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   static MenuHolder *menu = MenuHolder::getInstance();
   static InternalFrameHolder *window = InternalFrameHolder::getInstance();

   if (kernel->NeedRefreshReshape) {
      glutReshapeWindow(kernel->_userScreenSize[0],kernel->_userScreenSize[1]);
      kernel->NeedRefreshReshape = false;
   }

   kernel->updateFramesPerSecond();

   cursor->requestResetCursor();
   cursor->refreshMouse();

   if (kernel->_componentsToLoad.size()) {
      for (int i = 0; i < kernel->_componentsToLoad.size(); i++) {
         kernel->_componentsToLoad[i]->createTexture();
      }
      kernel->_componentsToLoad.clear();
   }

   for (int i = 0; i < kernel->_componentsToCallUpdate.size(); i++)
      kernel->_componentsToCallUpdate[i]->update();

   scheme->applyColor(ColorScheme::background);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   kernel->applyDefaultTransformMatrix();

   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);


   for (int i = 0; i < kernel->_components.size(); i++) {
      if (kernel->willAppearOnScreen(kernel->_components[i]))
         kernel->_components[i]->display();
   }

   window->display();
   menu->display();

   glDisable(GL_BLEND);
   glutSwapBuffers();
}

void Kernel::addComponent(ComponentInterface *component) {
   if (component != NULL) _components.push_back(component);
}

void Kernel::removeComponent(ComponentInterface *component) {
   component->setParent(NULL);
}

bool Kernel::requestComponentFocus(ComponentInterface *component) {
   if (component == NULL) false;

   static Keyboard *keyboard = Keyboard::getInstance();

   if (anyComponentRequestFocus == false) {
      if (_focusedComponent != NULL && _focusedComponent != component && keyboard->isEmpty() == false) {
         std::deque<Keyboard::KeyboardControl> keys = keyboard->clear();
         for (int i = 0; i < keys.size(); i++)
            _focusedComponent->processKey(KeyEvent(keys[i].key, glutGetModifiers(), keys[i].special, KeyEvent::up));
      }
      _focusedComponent = component;
      anyComponentRequestFocus = true;
      return true;
   } else {
      return false;
   }
}

ComponentInterface* Kernel::getFocusedComponent(void) const {
   return _focusedComponent;
}

void Kernel::requestComponentLoad(ComponentWithTexture* component) {
   _componentsToLoad.push_back(component);
}

void Kernel::applyDefaultTransformMatrix(void) {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, _currScreenSize[0], _currScreenSize[1], 0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glViewport(0, 0, _currScreenSize[0], _currScreenSize[1]);
}

void Kernel::registerComponentWithoutTexture(ComponentWithoutTexture* component) {
   _componentsToCallUpdate.push_back(component);
}

void Kernel::showCopyrights(void) {
   // free image credits
   std::cout << FreeImage_GetCopyrightMessage() << std::endl;

   // scv credits
   std::cout
      << std::endl <<
      " Cicero Augusto de Lara Pahins   Developer    Documentation"  << std::endl <<
      " Frederico Artur Limberger       Developer    Documentation"  << std::endl <<
      " Leonardo Quatrin Campagnolo     Contributor  Documentation  Support" << std::endl <<
      " Yuri Schlesner                  Contributor  Documentation  Support"  << std::endl <<
      " Bernardo Henz                   Tester                     " << std::endl;

   // scv logo and verison
   std::cout << std::endl <<
      " ##############################################################################" << std::endl <<
      " ############################  ################################################" << std::endl <<
      " ###########################  ##############  #################################" << std::endl <<
      " ##############              ##############  ##################################" << std::endl <<
      " #############    ########  #####           ##################  ###############" << std::endl <<
      " ##############   #######  ####    ######  ####################  ##############" << std::endl <<
      " ###############   ##########    #######  ######################  #############" << std::endl <<
      " ################   ########    #######  ###  ##################   ############" << std::endl <<
      " #################   #######   ############  ##################     ###########" << std::endl <<
      " ##################   ######   ###########   #################   ##  ##########" << std::endl <<
      " ###################   #####   ##########     ###############   ####  #########" << std::endl <<
      " ####################   ####   #########  ##   #############   ################" << std::endl <<
      " #####################   ###   ########  ####   ###########   #################" << std::endl <<
      " ######################   ###   ##############   #########   ##################" << std::endl <<
      " #######################   ###   #########  ###   #######   ###################" << std::endl <<
      " #############  #########   ###    ########  ###   #####   ####################" << std::endl <<
      " ############  ##########    ###              ###   ###   #####################" << std::endl <<
      " ###########                  #####            ###   #   ######################" << std::endl <<
      " ##########                  #################  ###     #######################" << std::endl <<
      " #########  ###################################  ###   #######              ###" << std::endl <<
      " ########  ################################################### Version 3.0a ###" << std::endl <<
      " #############################################################              ###" << std::endl <<
      " ##############################################################################"
      << std::endl;
}

void Kernel::setWindowTitle(const std::string &title) {
   glutSetWindowTitle(title.c_str());
}

void Kernel::addWindow(InternalFrame *window) {
   static InternalFrameHolder *winHolder = InternalFrameHolder::getInstance();
   winHolder->registerFrame(window);
}

bool Kernel::scissorNeedRefresh(void) {
   return _scissorNeedRefresh;
}

bool Kernel::lockMouseUse(ComponentInterface* component) {
   if (!_mouseLocked || component == componentRequestMouseUse) {
      _mouseLocked = true;
      componentRequestMouseUse = component;
      return true;
   } else return false;
}

bool Kernel::unlockMouseUse(ComponentInterface* component) {
   if (component == componentRequestMouseUse) {
      _mouseLocked = false;
      return true;
   } else return false;
}

bool Kernel::requestMouseUse(ComponentInterface* component) {
   if (componentRequestMouseUse == NULL) {
      componentRequestMouseUse = component;
      return true;
   } else if (componentRequestMouseUse == component) {
      return true;
   } else return false;
}

void Kernel::registerContextMenu(ContextMenu *contextMenu) {
   static MenuHolder *menu = MenuHolder::getInstance();
   _contextMenu = contextMenu;
   menu->registerParentMenu(_contextMenu);
}


void Kernel::generateCode() {
   static CodeGenerator *code = CodeGenerator::getInstance();
   static Kernel* kernel = Kernel::getInstance();
   kernel->currentPanel = -1;
   std::string str = "";
   std::string mainInstances = "";
   str += "#include <SCV/SCV.h>\n\n   /* Codes SCV Generator 1.0 \n      SCV Team\n      For more information visit:\n      www.inf.ufsm.br/~pozzer/scv */\n\n";

   for (std::deque<ComponentInterface*>::iterator it = kernel->_components.begin(); it < kernel->_components.end(); it++) {
      str += getComponentAttrib(*it,false,kernel->currentPanel);
   }

   str += code->generateMainProgram();

   std::ofstream outputFile("../interface.cpp");
   outputFile << str;
   outputFile.close();

}


std::string Kernel::getComponentAttrib(ComponentInterface * it, bool isAtPanel, int panelValue) {

   static Kernel* kernel = Kernel::getInstance();
   std::string str = "";

   static CodeGenerator *code = CodeGenerator::getInstance();

   if ((it)->getType() == ComponentInterface::button) {
      return code->includeButton(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::canvas) {
      return code->includeCanvas(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::checkBox) {
      return code->includeCheckBox(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::colorPicker) {
      return code->includeColorPicker(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::comboBox) {
      return code->includeComboBox(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::label) {
      return code->includeLabel(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::menuBar) {
      return code->includeMenuBar(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::panel) {

      str += code->includePanel(it,isAtPanel);
      for (DynamicCastIterator<ComponentInterface, Panel::ObjectList::const_iterator> i (it->getChildren()); i.valid(); ++i) {
         str += getComponentAttrib(*i, true);
      }
      return str;

   } else if (it->getType() == ComponentInterface::progressBar) {
      return code->includeProgressBar(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::radioButton) {
      return code->includeRadioButton(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::scrollPane) {

      ScrollPane * scroll = static_cast<ScrollPane*>(it);
      str += code->includeScrollPane(it,isAtPanel);
      for (DynamicCastIterator<ComponentInterface, Panel::ObjectList::const_iterator> i (scroll->getPanel()->getChildren()); i.valid(); ++i) {
         str += getComponentAttrib(*i, true);
      }
      return str;

   } else if (it->getType() == ComponentInterface::slider) {
      return code->includeSlider(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::spinner) {
      return code->includeSpinner(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::separator) {
      return code->includeSeparator(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::tabbedPane) {
      return code->includeTabbedPane(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::textField) {
      return code->includeTextField(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::textBox) {
      return code->includeTextBox(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::toggleButton) {
      return code->includeToggleButton(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::window) {
      return code->includeInternalFrame(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::table) {
      return code->includeTable(it,isAtPanel);
   } else if (it->getType() == ComponentInterface::image) {

      str += code->includeImage(it,isAtPanel);
      for (DynamicCastIterator<ComponentInterface, Panel::ObjectList::const_iterator> i (it->getChildren()); i.valid(); ++i) {
         str += getComponentAttrib(*i, true);
      }
      return str;

   } else if (it->getType() == ComponentInterface::treeView) {
      return code->includeTreeView(it,isAtPanel);
      
   }


   return str;

}

bool Kernel::willAppearOnScreen(ComponentInterface* component) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   Point absPosition = component->getAbsolutePosition();
   Point invPosition = absPosition.inverse();
   if ((absPosition.x > _currScreenSize[0]) || absPosition.y > _currScreenSize[1] ||
      (absPosition.x + component->getWidth() < 0) || (absPosition.y + component->getHeight() < 0) ||
      !math::isInside(Point(scissor->currentScissor().mx,scissor->currentScissor().my).inverse() - Point(0,scissor->currentScissor().mheight), Point(scissor->currentScissor().mwidth,scissor->currentScissor().mheight),absPosition,component->getSize())) {
         return false;
   } else {
      return true;
   }
}

Kernel::textureFilter Kernel::getFilterType(void) {
   return _filterType;
}

void Kernel::setFilterType(textureFilter tex) {
   _filterType = tex;
}

int Kernel::getWidth(void) const {
   return _currScreenSize[0];
}

int Kernel::getHeight(void) const {
   return _currScreenSize[1];
}

void Kernel::lockWindowSize(bool lock) {
   isActiveReshape = !lock;
}

void Kernel::OpenFile(void) {
   static FileOpen *fileOp = FileOpen::getInstance();
   static Kernel* kernel = Kernel::getInstance();
   fileOp->getItem();
}

Panel * Kernel::getPanel() {
   if (mainPanel == NULL) {
      mainPanel = new scv::Panel(Point(0, 0), 1050, 860);

      mainPanel->setDraggable(false);
      mainPanel->setResizable(true);

      addComponent(mainPanel);
   }

   return mainPanel;
}

} // namespace scv