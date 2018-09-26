#ifndef TIMERS_H_

#define TIMERS_H_


#include <ctime>

#include <sys/resource.h>


static inline double cpuTimeTotal(void){

	struct rusage ru;
	
	getrusage(RUSAGE_SELF,&ru);

	//cout<<"User time: "<<ru.ru_utime.tv_sec<<" Sys time: "<<ru.ru_stime.tv_sec<<endl;

	return (double) ru.ru_utime.tv_sec+(double) ru.ru_utime.tv_usec/1000000.0 + (double) ru.ru_stime.tv_sec+(double) ru.ru_stime.tv_usec/1000000.0;

}


#endif
