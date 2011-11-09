#ifndef __GROUP_OBJECT_WRAPPER_H__
#define __GROUP_OBJECT_WRAPPER_H__

class GroupObjectWrapper : public scv::Panel {
public:
   GroupObjectWrapper(scv::Component *objet);
   virtual ~GroupObjectWrapper(void);

   void display(void);

protected:
   
private:
};

#endif //__GROUP_OBJECT_WRAPPER_H__