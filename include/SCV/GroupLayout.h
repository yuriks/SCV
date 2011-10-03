#ifndef __SCV_GROUP_LAYOUT_H__
#define __SCV_GROUP_LAYOUT_H__

//http://javasourcecode.org/html/open-source/jdk/jdk-6u23/javax/swing/GroupLayout.html

#include "Panel.h"

#include "ParallelGroup.h"
#include "SequentialGroup.h"

namespace scv {

class Group;

class GroupLayout {
public:
   enum Alignment {
      BASELINE, CENTER, LEADING, TRAILING
   };

   ///////////////////////////////////////////////////////////
   GroupLayout(Panel *host);
   virtual ~GroupLayout(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline void setAutoCreateGaps(bool autoCreatePadding);
   inline bool getAutoCreateGaps(void) const;

   inline void setAutoCreateContainerGaps(bool autoCreateContainerPadding);
   inline bool getAutoCreateContainerGaps(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   ParallelGroup *createParallelGroup(void);
   ParallelGroup *createParallelGroup(Alignment alignment);

   SequentialGroup *createSequentialGroup(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setHorizontalGroup(Group *group);
   void setVerticalGroup(Group *group);
   ///////////////////////////////////////////////////////////

protected:
   Panel *_host;

   bool _autoCreatePadding;
   bool _autoCreateContainerPadding;

   Group *_horizontalGroup;
   Group *_verticalGroup;
private:
};

///////////////////////////////////////////////////////////
void GroupLayout::setAutoCreateGaps(bool autoCreatePadding) {
   _autoCreatePadding = autoCreatePadding;
}

bool GroupLayout::getAutoCreateGaps(void) const {
   return _autoCreatePadding;
}

void GroupLayout::setAutoCreateContainerGaps(bool autoCreateContainerPadding) {
   _autoCreateContainerPadding = autoCreateContainerPadding;
}

bool GroupLayout::getAutoCreateContainerGaps(void) const {
   return _autoCreateContainerPadding;
}
///////////////////////////////////////////////////////////

} //namespace scv

#endif //__SCV_GROUP_LAYOUT_H__