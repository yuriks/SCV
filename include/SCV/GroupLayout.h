#ifndef __SCV_GROUP_LAYOUT_H__
#define __SCV_GROUP_LAYOUT_H__

//http://download.oracle.com/javase/6/docs/api/javax/swing/GroupLayout.html

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
   ParallelGroup *createParallelGroup(void);
   ParallelGroup *createParallelGroup(Alignment alignment);

   SequentialGroup *createSequentialGroup(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setHorizontalGroup(Group *group);
   void setVerticalGroup(Group *group);
   ///////////////////////////////////////////////////////////

protected:
   
private:
};

} //namespace scv

#endif //__SCV_GROUP_LAYOUT_H__