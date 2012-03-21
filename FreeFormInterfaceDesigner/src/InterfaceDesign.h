#ifndef __SCV_INTERFACE_DESIGN_H__
#define __SCV_INTERFACE_DESIGN_H__


class InterfaceDesign : public scv::ContextMenu {
public:
   //InterfaceDesign(scv::Panel *panel);
   InterfaceDesign(scv::Panel *panel, bool remove = false);
   ~InterfaceDesign(void) {/**/}

   void onMenuAccessed(const std::deque<std::string> &address);

private:
   scv::Panel *m_panel;
   int contCheckbox, contLabel, contMenubar, contProgressBar, contRadioButton, contTextBox, contTextField, contTeggleButton, contFrame, contButton;
};

#endif // __SCV_INTERFACE_DESIGN_H__
