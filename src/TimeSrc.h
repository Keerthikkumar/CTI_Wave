/*
 * TimeSrc.h
 *
 *  Created on: 17-Dec-2024
 *      Author: cornet
 */

#ifndef TIMESRC_H_
#define TIMESRC_H_

#include <time.h>

class TimeBase
{
	public:
		int ConvertEpochTime(int Hour,int Mins,int Sec,int Year ,int Month ,int Day);
};



#endif /* TIMESRC_H_ */
