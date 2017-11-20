#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef INFO_DEBUG
#define INFO(...) fprintf (stderr, __VA_ARGS__)
#else
#define INFO(...) 
#endif

#endif
