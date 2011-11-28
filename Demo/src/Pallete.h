#ifndef __PALLETE_H__
#define __PALLETE_H__

class Pallete : public Singleton<Pallete>, public scv::Panel {
friend class Singleton<Pallete>;
public:
   
protected:
   ///////////////////////////////////////////////////////////
   Pallete(void);
   virtual ~Pallete(void);
   ///////////////////////////////////////////////////////////

private:
};

#endif //__PALLETE_H__