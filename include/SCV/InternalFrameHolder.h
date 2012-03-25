/*!
\file       InternalFrameHolder.h
\brief      Implementation of a InternalFrameHolder.
\author     SCV Team
*/


#ifndef __SCV_WINDOW_HOLDER_H__
#define __SCV_WINDOW_HOLDER_H__

#include "Singleton.h"
#include "MouseEvent.h"
#include "KeyEvent.h"

namespace scv {

class InternalFrame;

class InternalFrameHolder : public Singleton<InternalFrameHolder> {
friend class Singleton<InternalFrameHolder>;
public:
   void display(void);

   bool processMouse(const scv::MouseEvent &evt);
   bool processKey(const scv::KeyEvent &evt);

   void closeAllWindows(void);

   void registerFrame(InternalFrame *frame);

protected:
   std::deque<InternalFrame*> _framesDeque;
};

} // namespace scv

#endif // __SCV_WINDOW_HOLDER_H__