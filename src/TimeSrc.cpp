/*
 * TimeSrc.cpp
 *
 *  Created on: 17-Dec-2024
 *      Author: cornet
 */


#include "TimeSrc.h"

int TimeBase::ConvertEpochTime(int Hour,int Mins,int Sec,int Year ,int Month ,int Day)
{
	struct tm EpochTime;

	EpochTime.tm_hour = Hour;
	EpochTime.tm_min = Mins;
	EpochTime.tm_sec= Sec;

	EpochTime.tm_year= Year-1900;
	EpochTime.tm_mon= Month-1;
	EpochTime.tm_mday= Day;

	return mktime(&EpochTime);
}
