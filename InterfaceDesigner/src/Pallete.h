#ifndef __PALLETE_H__
#define __PALLETE_H__

class Pallete : public Singleton<Pallete>, public scv::Panel {
friend class Singleton<Pallete>;
public:
    void setGroupPanelsWraper(GroupPanelWrapper*, GroupPanelWrapper*);
protected:
   ///////////////////////////////////////////////////////////
   Pallete(void);
   virtual ~Pallete(void);
   ///////////////////////////////////////////////////////////

   void display(void);

   scv::Label *_title;
private:
   GroupPanelWrapper* _hGP;
   GroupPanelWrapper* _vGP;
};

#endif //__PALLETE_H__