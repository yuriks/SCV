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
   ///////////////////////////////////////////////////////////
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
      comboBox    , TreeView   ,
      s_nOfWidgets
   };

   enum textureFilter { linear, nearest };
   ///////////////////////////////////////////////////////////

   void run(void);

   void showCopyrights(void);

   void OpenFile(void);

   ///////////////////////////////////////////////////////////
   void setFramesPerSecond(float fps);
   inline float getFramesPerSecond(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setWindowSize(unsigned int width, unsigned int height);
   void setWindowTitle(const std::string &title);

   int getWidth(void) const;
   int getHeight(void) const;

   void setFullScreen(bool full);
   void lockWindowSize(bool lock);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   textureFilter getFilterType(void);
   void setFilterType(textureFilter tex);
   ///////////////////////////////////////////////////////////
      
   ///////////////////////////////////////////////////////////
   bool lockMouseUse(SCVObject* component);
   bool unlockMouseUse(SCVObject* component);

   bool requestMouseUse(SCVObject* component);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   bool requestComponentFocus(SCVObject *component);
   SCVObject* getFocusedComponent(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void requestComponentLoad(ComponentWithTexture* component);
   void registerContextMenu(ContextMenu *contextMenu);
   ///////////////////////////////////////////////////////////

   bool scissorNeedRefresh(void);

   bool willAppearOnScreen(SCVObject* component);

   void applyDefaultTransformMatrix(void);

   ///////////////////////////////////////////////////////////
   std::string getClipBoardString(void) const;
   void setClipBoardString(const std::string str);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void addWindow(InternalFrame *window);
   void addComponent(SCVObject::Ptr &object);
   void removeComponent(SCVObject *component);   
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline void setWidgetTexture(Kernel::widgets widget, ComponentTexture *texture);
   inline ComponentTexture* getWidgetTexture(Kernel::widgets widget);
   ///////////////////////////////////////////////////////////

private:
   Kernel(void);
   ~Kernel(void) {/**/}

   void initOpenGL(int argc, char* argv[]);

   void updateFramesPerSecond(void);

   /* Mouse Callbacks                                       */   
   ///////////////////////////////////////////////////////////
   static void cbMouseMotion(int x, int y);
   static void cbMouseClick(int button, int state, int x, int y);
   static void cbMouseWheel(int button, int dir, int x, int y);
   ///////////////////////////////////////////////////////////

   /* Keyboard Callbacks                                    */
   ///////////////////////////////////////////////////////////
   static void cbKeySpecial(int key, int x, int y);
   static void cbKeySpecialUp(int key, int x, int y);
   static void cbKey(unsigned char key, int x, int y);
   static void cbKeyUp(unsigned char key, int x, int y);
   ///////////////////////////////////////////////////////////
      
   /* Display                                               */   
   ///////////////////////////////////////////////////////////
   static void cbReshape(int w, int h);
   static void cbDisplay(void);
   ///////////////////////////////////////////////////////////

   static const std::string s_defaultTitle;
   static const unsigned int s_defaultWidth, s_defaultHeight;
   static const unsigned int s_defaultFramesPerSecond;

   ///////////////////////////////////////////////////////////
   struct {
      bool isFullScreen;
      int currSize[2], userSize[2];
   } Display;
   
   struct {
      int count, currTime, prevTime, baseTime;
      float fps, currFps;
   } FrameRate;   

   struct {
      int doubleClickTime;

      Point lastClickPosition;
      Timer lastTimeClicked;
      MouseEvent::button lastButton;

      bool clicked, locked;      
      SCVObject *componentRequestUse;
   } Mouse;
   ///////////////////////////////////////////////////////////
   
   ComponentTexture *_loadedWidgets[s_nOfWidgets];

   bool _scissorNeedRefresh;

   std::string _windowTitle;

   textureFilter _filterType;

   typedef std::list<std::shared_ptr<SCVObject>> ComponentsList;
   ComponentsList _objects;
   
   typedef std::list<ComponentWithTexture*> ComponentsToLoadList;
   ComponentsToLoadList _componentsToLoad;

   SCVObject *_focusedComponent;

   bool _needRefreshReshape;
   bool _isActiveReshape;
      
   bool _componentRequestFocus;   
   ContextMenu *_contextMenu;
};

inline float Kernel::getFramesPerSecond(void) const {
   return FrameRate.currFps;
}

inline void Kernel::setWidgetTexture(Kernel::widgets widget, ComponentTexture *texture) {
   _loadedWidgets[widget] = texture;
}

inline ComponentTexture* Kernel::getWidgetTexture(Kernel::widgets widget) {
   return _loadedWidgets[widget];
}

} // namespace scv

#endif // __SCV_KERNEL_H__