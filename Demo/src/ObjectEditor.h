#ifndef __OBJECT_EDITOR_H__
#define __OBJECT_EDITOR_H__

class ObjectEditor : public Singleton<ObjectEditor>, public scv::ScrollComponent {
friend class Singleton<ObjectEditor>;
public:
   virtual void refreshContainerPosition(void);

protected:
   ///////////////////////////////////////////////////////////
   ObjectEditor(void);
   virtual ~ObjectEditor(void);
   ///////////////////////////////////////////////////////////
private:
};

#endif //__OBJECT_EDITOR_H__