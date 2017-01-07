#ifndef _CLASSLOADERS_H_
#define _CLASSLOADERS_H_

//Class To be loaded
typedef void (*ClassLoader_t)(void);
extern ClassLoader_t classLoaders[];

void objectClassLoad();
void stringClassLoad();
void integerClassLoad();
void entityClassLoad();

ClassLoader_t classLoaders[] = {
  objectClassLoad,
  stringClassLoad,
  integerClassLoad,
  entityClassLoad
};

#endif