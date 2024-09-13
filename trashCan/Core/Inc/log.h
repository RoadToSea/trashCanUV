#ifndef __LOG_H_
#define __LOG_H_

#define DEBUG 1

#ifdef DEBUG 
#define LOG(message)            if(message==0) printf("ERROR:%s,%d",__FILE__,__LINE__);

#endif

#endif
