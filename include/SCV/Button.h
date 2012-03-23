#ifndef __SCV_BUTTON_H__
#define __SCV_BUTTON_H__

#include "Label.h"
#include "StaticLabel.h"
#include "ComponentTexture.h"

namespace scv {

class Button : public Label {
public:
   Button(const scv::Point &p1, const scv::Point &p2, const std::string &str);
   Button(const scv::Point &p, unsigned int width, const std::string &str);
   Button(const scv::Point &p, const std::string &str);
   virtual ~Button(void) {}

   virtual void display(void);


protected:
   void createTexture(void);
};

} // namespace scv

#endif // __SCV_BUTTON_H__