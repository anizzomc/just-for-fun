#ifndef _JFFCONFIG_H_
#define _JFFCONFIG_H_

// All method names goes here
typedef enum {
  new = 0,
  init,
  getClass,
  toString,
  equals,
  lenght,
  _dummyMethod //This should be always defined last
} Invoke_t;

#endif