/*!
\file       Kernel.h
\brief      Implementation of the SCV Kernel
\author     SCV Team
*/

#ifndef __SCV_KERNEL_H__
#define __SCV_KERNEL_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Singleton.h"
#include "FontTahoma.h"

#include "ComponentTexture.h"
#include "ComponentWithTexture.h"
#include "ComponentWithoutTexture.h"

#include "Panel.h"
#include "ScrollPane.h"
#include "Scissor.h"

#include "ContextMenu.h"
#include "InternalFrame.h"

#include "Cursor.h"
#include "Timer.h"

#include "ColorScheme.h"

#include "FreeImage.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! \defgroup util Util */
/*! \defgroup widgets Widgets */
/*! \defgroup internal Internal Classes */


/*! The main class of SCV
 *  This class controls all components, all interactions and all OpenGL interface.
 */

class Kernel : public Singleton<Kernel> {
friend class Singleton<Kernel>;
public:

   enum widgets {
      panel       , contextMenu,
      colorPicker , progressBar,
      scrool      , slider     ,
      spinner     , button     ,
      checkBox    , radioBox   ,
      toggleButton, textField  ,
      textBox     , separator  ,
      window      , menuBar    ,
      tabbedPane  , scrollPanel,
      comboBox    ,    TreeView,
      s_nOfWidgets
   };

   enum textureFilter {
      linear,
      nearest
   };

   void run(void);

   void showCopyrights(void);
   void generateCode(void);
   void OpenFile(void);

   void setFramesPerSecond(float fps);
   inline float getFramesPerSecond(void) const {
      return _currFramesPerSecond;
   }

   void setWindowSize(unsigned int width, unsigned int height);
   void setWindowTitle(const std::string &title);

   textureFilter getFilterType(void);
   void setFilterType(textureFilter tex);

   int getWidth(void) const;
   int getHeight(void) const;

   void setFullScreen(bool full);
   void lockWindowSize(bool lock);

   bool lockMouseUse(ComponentInterface* component);
   bool unlockMouseUse(ComponentInterface* component);

   bool requestMouseUse(ComponentInterface* component);

   bool requestComponentFocus(ComponentInterface *component);
   ComponentInterface* getFocusedComponent(void) const;

   void requestComponentLoad(ComponentWithTexture* component);
   void registerComponentWithoutTexture(ComponentWithoutTexture* component);
   void registerContextMenu(ContextMenu *contextMenu);

   bool scissorNeedRefresh(void);

   bool willAppearOnScreen(ComponentInterface* component);

   void applyDefaultTransformMatrix(void);

   std::string getClipBoardString(void) const;
   void setClipBoardString(const std::string str);

   void addComponent(ComponentInterface *component);
   void removeComponent(ComponentInterface *component);
   void addWindow(InternalFrame *window);

   inline void setWidgetTexture(Kernel::widgets widget, ComponentTexture *texture) {
      _loadedWidgets[widget] = texture;
   }

   inline ComponentTexture* getWidgetTexture(Kernel::widgets widget) {
      return _loadedWidgets[widget];
   }

   Panel * getPanel();

private:
   Kernel(void);
   ~Kernel(void) {/**/}

   void initOpenGL(int argc, char* argv[]);

   void updateFramesPerSecond(void);

   /************************************************************************/
   /* Mouse Callbacks                                                      */
   /************************************************************************/
   static void cbMouseMotion(int x, int y);
   static void cbMouseClick(int button, int state, int x, int y);
   static void cbMouseWheel(int button, int dir, int x, int y);

   /************************************************************************/
   /* Keyboard Callbacks                                                   */
   /************************************************************************/
   static void cbKeySpecial(int key, int x, int y);
   static void cbKeySpecialUp(int key, int x, int y);
   static void cbKey(unsigned char key, int x, int y);
   static void cbKeyUp(unsigned char key, int x, int y);

   /************************************************************************/
   /* Display                                                              */
   /************************************************************************/
   static void cbReshape(int w, int h);
   static void cbDisplay(void);

   std::string getComponentAttrib(ComponentInterface * it, bool isAtPanel, int panelValue = -1);
   int currentPanel;

   ComponentTexture *_loadedWidgets[s_nOfWidgets];

   static const std::string s_defaultTitle;
   static const unsigned int s_defaultWidth, s_defaultHeight;
   static const unsigned int s_defaultFramesPerSecond;

   bool isFullScreen;
   int _currScreenSize[2];
   int _userScreenSize[2];

   bool _scissorNeedRefresh;

   std::string _windowTitle;

   textureFilter _filterType;

   // frame rate
   int _frameCount, _currentTime, _previousTime, _baseTime;
   float _framesPerSecond, _currFramesPerSecond;

   std::deque<ComponentInterface*> _components;
   std::deque<ComponentWithTexture*> _componentsToLoad;
   std::deque<ComponentWithoutTexture*> _componentsToCallUpdate;
   ComponentInterface *_focusedComponent;

   // mouse
   int doubleClickTime;
   Point lastClickPosition;
   Timer lastTimeClicked;
   bool mouseClicked;
   MouseEvent::button lastButton;

   bool NeedRefreshReshape;
   bool isActiveReshape;

   bool _mouseLocked;
   bool anyComponentRequestFocus;
   ComponentInterface *componentRequestMouseUse;
   ContextMenu *_contextMenu;

   scv::Panel * mainPanel;
  
};

} // namespace scv

#endif // __SCV_KERNEL_H__