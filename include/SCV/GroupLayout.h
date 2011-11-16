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
   static ParallelGroup *createParallelGroup(void);
   static ParallelGroup *createParallelGroup(Spring::Alignment alignment);
   static ParallelGroup *createParallelGroup(Spring::Alignment alignment, bool resizable);

   static SequentialGroup *createSequentialGroup(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setHorizontalGroup(Group *group);
   Group *getHorizontalGroup(void) const;

   void setVerticalGroup(Group *group);
   Group *getVerticalGroup(void) const;
   ///////////////////////////////////////////////////////////

   void layoutContainer(void);

   ///////////////////////////////////////////////////////////
   int getMinimumSize(Spring::Axis axis);
   int getPreferredSize(Spring::Axis axis);
   int getMaximumSize(Spring::Axis axis);
   ///////////////////////////////////////////////////////////

protected:
   Panel *_host;
   Group *_horizontalGroup, *_verticalGroup;

private:
};


} //namespace scv

#endif //__SCV_GROUP_LAYOUT_H__