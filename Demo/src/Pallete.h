#ifndef __PALLETE_H__
#define __PALLETE_H__

class Pallete : public Singleton<Pallete>, public scv::Panel {
friend class Singleton<Pallete>;
protected:
   ///////////////////////////////////////////////////////////
   Pallete(void);
   virtual ~Pallete(void);
   ///////////////////////////////////////////////////////////

   void display(void);

   scv::Label *_title;
};

#endif //__PALLETE_H__