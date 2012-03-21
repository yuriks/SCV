/*!
\file       Timer.h
\brief      Implementation of a Timer interface.
\author     SCV Team
*/

#ifndef __SCV_TIMER_H__
#define __SCV_TIMER_H__

namespace scv {

/*! Class for easy creation of timers.
 * \ingroup util
 */

class Timer {
public:

   Timer(void);

   void start(void);
   void pause(void);
   void unpause(void);
   void stop(void);

   /*! Basic Timer information.
   \return time in seconds of timer
   */
   int getSeconds(void);

   /*! Basic Timer information.
   \return time in milliseconds of timer
   */
   int getMilliseconds(void);

   /*! Basic Timer information.
   \return Timer state.
   */
   bool isRunning(void) const;

private:
   int _startTime, _currTime;
   bool _running;
};

} // namespace scv

#endif // __SCV_TIMER_H__