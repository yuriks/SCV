#include "stdafx.h"
#include "Timer.h"

namespace scv {

Timer::Timer(void) {
   _running = false;
}

void Timer::start(void) {
   _running = true;
   _startTime = _currTime = glutGet(GLUT_ELAPSED_TIME);
}

void Timer::pause(void) {
   _running = false;
   _currTime = glutGet(GLUT_ELAPSED_TIME);
}

void Timer::unpause(void) {
   if (_running == false) {
      _startTime += glutGet(GLUT_ELAPSED_TIME) - _currTime;
      _currTime = glutGet(GLUT_ELAPSED_TIME);
   }
   _running = true;
}

void Timer::stop(void) {
   _running = false;
   _startTime = _currTime = 0;
}

int Timer::getSeconds(void) {
   if (_running) _currTime = glutGet(GLUT_ELAPSED_TIME);
   return (_currTime - _startTime) / 1000;
}

int Timer::getMilliseconds(void) {
   if (_running) _currTime = glutGet(GLUT_ELAPSED_TIME);
   return _currTime - _startTime;
}

bool Timer::isRunning(void) const {
   return _running;
}

} // namespace scv