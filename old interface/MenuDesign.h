#ifndef __SCV_MENU_DESIGN_H__
#define __SCV_MENU_DESIGN_H__

class MenuDesign : public scv::ContextMenu {
public:
   MenuDesign(scv::MenuBar * menubar);
   ~MenuDesign(void) {/**/}

   void onMouseClick(const scv::MouseEvent &evt, const std::deque<std::string> &address);

private:
   scv::MenuBar *m_menu;
   int contMenu;
   //int contCheckbox, contLabel, contMenubar, contProgressBar, contRadioButton, contTextBox, contTextField, contTeggleButton, contWindow, contButton;
};


class MenuRename : public scv::ContextMenu {
public:
   MenuRename(scv::Label * component) : ContextMenu("Rename") {
      m_component = component;

      addMenu(new ContextMenu("Rename"));
      addMenu(new ContextMenu("Remove Component"));
   }
   ~MenuRename(){/**/}

   void onMouseClick(const scv::MouseEvent &evt, const std::deque<std::string> &address);

private:
   scv::Label * m_component;
};

class  RemoveComponent : public scv::ContextMenu {
public:
   RemoveComponent(scv::ComponentInterface * component) : ContextMenu("Remove Component") {
      m_component = component;

      addMenu(new ContextMenu("Remove Component"));
   }
   ~RemoveComponent(){/**/}

   void onMouseClick(const scv::MouseEvent &evt, const std::deque<std::string> &address);

private:
   scv::ComponentInterface * m_component;
};

#endif // __SCV_MENU_DESIGN_H__