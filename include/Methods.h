#ifndef _JSFFCONFIG_H_
#define _JSFFCONFIG_H_

// All method names goes here
typedef enum {
  new = 0,
  init,
  dealloc,
  getClass,
  toString,
  equals,
  length,
  toCharArray,
  nextID,
  getId,
  test,
  retain,
  release,
  isNull,
  add,
  get,
  delete,
  respondsTo,
  _dummyMethod //This should be always defined last
} Invoke_t;

#endif