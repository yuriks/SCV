#ifndef __OBJECT_EDITOR_H__
#define __OBJECT_EDITOR_H__

class ObjectEditor : public Singleton<ObjectEditor>, public scv::Panel {
friend class Singleton<ObjectEditor>;
public:
   void setComponent(scv::Component *object);

   void update(void);

protected:
   ///////////////////////////////////////////////////////////
   ObjectEditor(void);
   virtual ~ObjectEditor(void);
   ///////////////////////////////////////////////////////////

   scv::Component *_currObject;
private:
};

#endif //__OBJECT_EDITOR_H__