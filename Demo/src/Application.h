#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Properties.h"
#include "GroupPanelWrapper.h"
#include "ComponentSelector.h"

#include "CodeGenerator.h"

#include "ObjectEditor.h"
#include "CodeViewer.h"
#include <vector>

class CodeViewerTabbedPane : public scv::TabbedPane {
public:
    ///////////////////////////////////////////////////////////
    CodeViewerTabbedPane(std::vector<CodeViewer*>);
    virtual ~CodeViewerTabbedPane(void);
    ///////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////
    void onTabChange(void);
    ///////////////////////////////////////////////////////////
private:
    std::vector<CodeViewer*> _vCodeViewer;
};
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
class MainTabbedPane : public scv::TabbedPane {
public:
   ///////////////////////////////////////////////////////////
   MainTabbedPane(CodeViewerTabbedPane*);
   virtual ~MainTabbedPane(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void onTabChange(void);
   ///////////////////////////////////////////////////////////
private:
    CodeViewerTabbedPane* _cvt;
};
///////////////////////////////////////////////////////////

class Application : public scv::Kernel {
public:
   ///////////////////////////////////////////////////////////
   static const int s_defaultWindowWidth = 800;
   static const int s_defaultWindowHeight = 600;

   static const int s_defaultGap = 10;
   static const int s_defaultRightPanelWidth = 250;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   Application(void);
   virtual ~Application(void);
   ///////////////////////////////////////////////////////////

   void init(void);

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

   virtual void onDisplay(void);
   ///////////////////////////////////////////////////////////

   void addComponentFromPalette(std::string component);
   
   std::string getLayoutCode(const std::string &panelName) const;

   void openComponentSelector(GroupPanel *group);

   void createPreview(void);

   inline void setMainTabbedPaneIndex(int index);
   ///////////////////////////////////////////////////////////
   
protected:
   scv::Panel *_mainPanel;

   MainTabbedPane *_mainTabbedPane;
   scv::TabbedPane *_designPreviewTabbedPane;
   CodeViewerTabbedPane *_codeViewerTabbedPane;
   ComponentSelector *_componentSelector;

   GroupPanel *currGroup;

   GroupPanelWrapper *_hPanelWrapper, *_vPanelWrapper;
   CodeViewer *_mainCodeViewer, *_AppHCodeViewer, *_AppCppCodeViewer, *_WdgHCodeViewer, *_WdgCppCodeViewer;
};

///////////////////////////////////////////////////////////

void Application::setMainTabbedPaneIndex(int index) {
   _mainTabbedPane->setCurrTabIndex(index);
}

///////////////////////////////////////////////////////////

#endif //__APPLICATION_H__