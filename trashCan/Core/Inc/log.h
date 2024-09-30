#ifndef __LOG_H_
#define __LOG_H_

#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG 
#define LOG(message,output)            if(message) printf("ERROR:%s,%d\n%s",__FILE__,__LINE__,output)

#else
#define LOG(message,output)            (void)(message)
#endif

#endif
