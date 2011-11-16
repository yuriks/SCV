#ifndef __SCV_KERNEL_H__
#define __SCV_KERNEL_H__

///////////////////////////////////////////////////////////
#include "Singleton.h"
#include "FontTahoma.h"

#include "ComponentTexture.h"
#include "ComponentWithTexture.h"
#include "ComponentWithoutTexture.h"

#include "Panel.h"
#include "ScrollComponent.h"
#include "Scissor.h"

#include "ContextMenu.h"
#include "InternalFrame.h"

#include "Cursor.h"
#include "Timer.h"

#include "ColorScheme.h"

#include "FreeImage.h"
///////////////////////////////////////////////////////////

namespace scv {

class Kernel : public Singleton<Kernel>, public SCVCallbacks {
friend class Singleton<Kernel>;
public:
   ///////////////////////////////////////////////////////////
   enum Widgets {
      PANEL       , CONTEXTMENU, COLORPICKER , PROGRESSBAR,
      SCROLL      , SLIDER     , SPINNER     , BUTTON     ,
      CHECKBOX    , RADIOBOX   , TOGGLEBUTTON, TEXTFIELD  ,
      TEXTBOX     , SEPARATOR  , WINDOW      , MENUBAR    ,
      TABBEDPANE  , SCROLLPANE , COMBOBOX    , TREEVIEW   ,
      NOFWIDGETS
   };

   enum TextureFilter { LINEAR, NEAREST };
   ///////////////////////////////////////////////////////////

   //SCVCallbacks
   ///////////////////////////////////////////////////////////
   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold (const scv::MouseEvent &evt);
   virtual void onMouseOver (const scv::MouseEvent &evt);
   virtual void onMouseUp   (const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp     (const scv::KeyEvent &evt);

   virtual void onSizeChange(void);
   virtual void onPositionChange(void);
   ///////////////////////////////////////////////////////////
   
   void run(void);

   void showCopyrights(void);

   void OpenFile(void);

   ///////////////////////////////////////////////////////////
   inline void setFramesPerSecond(float fps);
   inline float getFramesPerSecond(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setWindowSize(unsigned int width, unsigned int height);
   void setWindowTitle(const std::string &title);

   inline int getWidth(void) const;
   inline int getHeight(void) const;

   void setFullScreen(bool full);
   void lockWindowSize(bool lock);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline TextureFilter getFilterType(void);
   inline void setFilterType(TextureFilter tex);
   ///////////////////////////////////////////////////////////
      
   ///////////////////////////////////////////////////////////
   bool lockMouseUse(Component* component);
   bool unlockMouseUse(Component* component);

   bool requestMouseUse(Component* component);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   bool requestComponentFocus(Component *component);
   inline Component *getFocusedComponent(void) const;
   ///////////////////////////////////////////////////////////

   bool willAppearOnScreen(Component* component);

   void applyDefaultTransformMatrix(void);

   ///////////////////////////////////////////////////////////
   std::string getClipBoardString(void) const;
   void setClipBoardString(const std::string str);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void addWindow(InternalFrame *window);
   void addComponent(Component *object);
   void removeComponent(Component *object);   
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline void setWidgetTexture(Kernel::Widgets widget, ComponentTexture *texture);
   inline ComponentTexture* getWidgetTexture(Kernel::Widgets widget);
   ///////////////////////////////////////////////////////////

protected:
   Kernel(void);
   ~Kernel(void);

   void initOpenGL(int argc, char* argv[]);

   void updateFramesPerSecond(void);

   //Mouse Callbacks
   ///////////////////////////////////////////////////////////
   static void cbMouseMotion(int x, int y);
   static void cbMouseClick(int button, int state, int x, int y);
   static void cbMouseWheel(int button, int dir, int x, int y);
   ///////////////////////////////////////////////////////////

   //Keyboard Callbacks
   ///////////////////////////////////////////////////////////
   static void cbKeySpecial(int key, int x, int y);
   static void cbKeySpecialUp(int key, int x, int y);
   static void cbKey(unsigned char key, int x, int y);
   static void cbKeyUp(unsigned char key, int x, int y);
   ///////////////////////////////////////////////////////////
      
   //Display
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
      MouseEvent::Button lastButton;

      bool clicked, locked;      
      Component *componentRequestUse;
   } Mouse;
   ///////////////////////////////////////////////////////////
   
   ComponentTexture *_loadedWidgets[NOFWIDGETS];

   std::string _windowTitle;

   TextureFilter _filterType;

   typedef std::list<Component*> ComponentsList;
   ComponentsList _objects;
   
   Component *_focusedComponent;

   bool _needReshapeWindow;
   bool _isActiveReshape;
      
   bool _componentRequestFocus;   
   ContextMenu *_contextMenu;
};

///////////////////////////////////////////////////////////
void Kernel::setFramesPerSecond(float fps) {
   FrameRate.fps = fps;
}

inline float Kernel::getFramesPerSecond(void) const {
   return FrameRate.currFps;
}

inline void Kernel::setWidgetTexture(Kernel::Widgets widget, ComponentTexture *texture) {
   _loadedWidgets[widget] = texture;
}

inline ComponentTexture* Kernel::getWidgetTexture(Kernel::Widgets widget) {
   return _loadedWidgets[widget];
}

Kernel::TextureFilter Kernel::getFilterType(void) {
   return _filterType;
}

void Kernel::setFilterType(TextureFilter tex) {
   _filterType = tex;
}

int Kernel::getWidth(void) const {
   return Display.currSize[0];
}

int Kernel::getHeight(void) const {
   return Display.currSize[1];
}

Component* Kernel::getFocusedComponent(void) const {
   return _focusedComponent;
}
///////////////////////////////////////////////////////////

} // namespace scv

#endif // __SCV_KERNEL_H__