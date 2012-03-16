#ifndef __SCV_ABSTRACT_WINDOW_H__
#define __SCV_ABSTRACT_WINDOW_H__

class AbstractWindow;
class InputText : public scv::TextField {
public:
   InputText(AbstractWindow * window);
   ~InputText(void){}

   void onKeyPressed(const scv::KeyEvent &evt);

private:
   AbstractWindow * m_window;
};

class CancelButton : public scv::Button {
public:
   CancelButton(AbstractWindow * window);
   ~CancelButton(void){}

   void onMouseUp(const scv::MouseEvent &evt);


private:
   AbstractWindow * m_window;
};


class AcceptButton : public scv::Button {
public:
   AcceptButton(AbstractWindow * window);
   ~AcceptButton(void){}

   void onMouseUp(const scv::MouseEvent &evt);
   void accept(void);
private:
   AbstractWindow * m_window;
};


class AbstractWindow : public scv::InternalFrame {
public:
   AbstractWindow(scv::Label * component);
   ~AbstractWindow(void) {/**/}

   scv::Label *m_component;
   AcceptButton *m_ok;
   CancelButton *m_cancel;
   InputText *m_input;
};

#endif // __SCV_ABSTRACT_WINDOW_H__