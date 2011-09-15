/*!
\file       InternalFrameHolder.h
\brief      Internal Frames Controller.
\author     SCV Team
*/

#ifndef __SCV_WINDOW_HOLDER_H__
#define __SCV_WINDOW_HOLDER_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Singleton.h"
#include "MouseEvent.h"
#include "KeyEvent.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

class InternalFrame;

/*! A class that controls the Internal Frames.
 * \ingroup internal
 */

class InternalFrameHolder : public Singleton<InternalFrameHolder> {
friend class Singleton<InternalFrameHolder>;
public:

   void display(void);
   bool processMouse(const scv::MouseEvent &evt);
   bool processKey(const scv::KeyEvent &evt);
   void closeAllWindows(void);
   void registerFrame(InternalFrame *frame);

protected:

private:
   std::deque<InternalFrame*> _framesDeque;

};

} // namespace scv


#endif // __SCV_WINDOW_HOLDER_H__