#ifndef __SCV_WIDGET_LABEL_H__
#define __SCV_WIDGET_LABEL_H__

#include "ComponentWithTexture.h"
#include "FontTahoma.h"
#include "Color4f.h"
#include "ColorScheme.h"

namespace scv {

class Label : public ComponentWithTexture {
public:
   Label(const scv::Point &p1, const scv::Point &p2, const std::string& str);
   Label(const scv::Point &p, unsigned int width, const std::string& str);
   Label(const scv::Point &p, const std::string& str);

   virtual void onStringChange(void) {}

   inline const std::string &getString(void) const;
   virtual void setString(const std::string& str);
   
   inline virtual void setWidth(int width);
   inline virtual void setHeight(int height);

   virtual void display(void);

protected:
   virtual void createTexture(void) {}
   std::string _str;
};

inline const std::string& Label::getString(void) const {
   return _str;
}

inline void Label::setWidth(const int width) {
   Component::setWidth(width);
}

inline void Label::setHeight(const int height) {
   Component::setHeight(height);
}

} // namespace scv


#endif // __SCV_WIDGET_LABEL_H__