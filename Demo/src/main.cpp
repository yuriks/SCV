#include "stdafx.h"

#include "InterfaceDesign.h"


class Dummy : public std::enable_shared_from_this<Dummy> {
public:
   Dummy() {
      string = "print";
   }
   void print() {
      std::cout << string << std::endl;
   }

   virtual ~Dummy() {
      std::cout << "~Dummy" << std::endl;
   }
protected:
   
private:
   std::string string;
};

class AnotherDummy : public Dummy {
public:
   AnotherDummy() : Dummy() {

   }

   ~AnotherDummy() {
      std::cout << "~AnotherDummy" << std::endl;
   }
protected:
   
private:
};

int main(int argc, char* argv[]) {
   /*
   using namespace scv;
   static Kernel *kernel = Kernel::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();
   
   scheme->loadScheme(ColorScheme::osx);
   kernel->setWindowSize(1280, 720);
   
   
   scv::Panel *panel = new scv::Panel(scv::Point(10,10), scv::Point(220,220));
   kernel->addObject(SCVObject::Ptr(panel));

   for (int i = 0; i < 10000; i++) {
      panel->addObject(SCVObject::Ptr(new scv::Panel(scv::Point(10,10), scv::Point(220,220))));
   }

   kernel->deleteObject(panel->shared_from_this());

   kernel->registerContextMenu(new InterfaceDesign(NULL));
   //////////////////////////
   kernel->run();
   */
   Dummy *a = new AnotherDummy();
   delete a;

   return 0;
}
