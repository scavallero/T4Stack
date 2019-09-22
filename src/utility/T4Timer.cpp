#include "T4Timer.h"

// Select time function:
//static inline unsigned long elapsed() { return micros(); }
static inline unsigned long elapsed() { return millis(); }

T4Timer::T4Timer() {
  unsigned long current_millis = elapsed();

  for (int i = 0; i < MAX_TIMERS; i++) {
    enabled[i] = false;
    callbacks[i] = 0; // if the callback pointer is zero, the slot is free, i.e. doesn't "contain" any timer
    prev_millis[i] = current_millis;
    numRuns[i] = 0;
  }
  numTimers = 0;
}

void T4Timer::run() {
  int i;
  unsigned long current_millis;

  // get current time
  current_millis = elapsed();

  for (i = 0; i < MAX_TIMERS; i++) {
    toBeCalled[i] = DEFCALL_DONTRUN;

    // no callback == no timer, i.e. jump over empty slots
    if (callbacks[i] != 0) {

      // is it time to process this timer ?
      // see http://arduino.cc/forum/index.php/topic,124048.msg932592.html#msg932592

      if (current_millis - prev_millis[i] >= delays[i]) {
        // update time
        //prev_millis[i] = current_millis;
        prev_millis[i] += delays[i];

        // check if the timer callback has to be executed
        if (enabled[i] == true) {
          // "run forever" timers must always be executed
          if (maxNumRuns[i] == RUN_FOREVER) {
            toBeCalled[i] = DEFCALL_RUNONLY;
          }else if (numRuns[i] < maxNumRuns[i]) {
            // other timers get executed the specified number of times
            toBeCalled[i] = DEFCALL_RUNONLY;
            numRuns[i]++;
            // after the last run, delete the timer
            if (numRuns[i] >= maxNumRuns[i]) {
              toBeCalled[i] = DEFCALL_RUNANDDEL;
            }
          }
        }
      }
    }
  }
  for (i = 0; i < MAX_TIMERS; i++) {
    switch (toBeCalled[i]) {
      case DEFCALL_DONTRUN:
        break;

      case DEFCALL_RUNONLY:
        callbacks[i]();
        break;

      case DEFCALL_RUNANDDEL:
        callbacks[i]();
        deleteTimer(i);
        break;
    }
  }
}

// find the first available slot
// return -1 if none found
int T4Timer::findFirstFreeSlot() {
  int i;

  // all slots are used
  if (numTimers >= MAX_TIMERS) {
    return -1;
  }

  // return the first slot with no callback (i.e. free)
  for (i = 0; i < MAX_TIMERS; i++) {
    if (callbacks[i] == 0) {
      return i;
    }
  }
  // no free slots found
  return -1;
}

int T4Timer::setTimer(long d, timer_callback f, int n) {
  int freeTimer;

  freeTimer = findFirstFreeSlot();
  if (freeTimer < 0) {
    return -1;
  }

  if (f == NULL) {
    return -1;
  }

  delays[freeTimer] = d;
  callbacks[freeTimer] = f;
  maxNumRuns[freeTimer] = n;
  enabled[freeTimer] = true;
  prev_millis[freeTimer] = elapsed();

  numTimers++;

  return freeTimer;
}

int T4Timer::setInterval(long d, timer_callback f) {
  return setTimer(d, f, RUN_FOREVER);
}

int T4Timer::setTimeout(long d, timer_callback f) {
  return setTimer(d, f, RUN_ONCE);
}

void T4Timer::deleteTimer(int timerId) {
  if (timerId >= MAX_TIMERS) {
    return;
  }

  // nothing to delete if no timers are in use
  if (numTimers == 0) {
    return;
  }

  // don't decrease the number of timers if the
  // specified slot is already empty
  if (callbacks[timerId] != NULL) {
    callbacks[timerId] = 0;
    enabled[timerId] = false;
    toBeCalled[timerId] = DEFCALL_DONTRUN;
    delays[timerId] = 0;
    numRuns[timerId] = 0;

    // update number of timers
    numTimers--;
  }
}

// function contributed by code@rowansimms.com
void T4Timer::restartTimer(int numTimer) {
  if (numTimer >= MAX_TIMERS) {
    return;
  }

  prev_millis[numTimer] = elapsed();
}

boolean T4Timer::isEnabled(int numTimer) {
  if (numTimer >= MAX_TIMERS) {
    return false;
  }

  return enabled[numTimer];
}

void T4Timer::enable(int numTimer) {
  if (numTimer >= MAX_TIMERS) {
    return;
  }

  enabled[numTimer] = true;
}

void T4Timer::disable(int numTimer) {
  if (numTimer >= MAX_TIMERS) {
    return;
  }

  enabled[numTimer] = false;
}

void T4Timer::toggle(int numTimer) {
  if (numTimer >= MAX_TIMERS) {
    return;
  }

  enabled[numTimer] = !enabled[numTimer];
}

int T4Timer::getNumTimers() {
  return numTimers;
}
