#ifndef __SCV_GROUP_LAYOUT_H__
#define __SCV_GROUP_LAYOUT_H__

#include "Panel.h"

#include "ParallelGroup.h"
#include "SequentialGroup.h"

namespace scv {

class Group;

class GroupLayout {
public:
   ///////////////////////////////////////////////////////////
   GroupLayout(Panel *host);
   virtual ~GroupLayout(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   ParallelGroup *createParallelGroup(void);
   ParallelGroup *createParallelGroup(Spring::Alignment alignment);
   ParallelGroup *createParallelGroup(Spring::Alignment alignment, bool resizable);

   SequentialGroup *createSequentialGroup(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setHorizontalGroup(Group *group);
   void setVerticalGroup(Group *group);
   ///////////////////////////////////////////////////////////

   void layoutContainer(void);

protected:
   Panel *_host;

   bool _autoCreatePadding;
   bool _autoCreateContainerPadding;

   Group *_horizontalGroup;
   Group *_verticalGroup;
private:
};


} //namespace scv

#endif //__SCV_GROUP_LAYOUT_H__