/*
 * Sample_Wave.cpp
 *
 *  Created on: 12-Dec-2024
 *      Author: cornet
 */

#include <stdio.h>
#include <sys/types.h>
#include <string.h>


#include <cstdlib>
#include "Sample_Wave.h"

int Total_Of_Samples(char *str,char *DelimitStr)
{
	int DelimitIndex = 0;

    int strLen = strlen(str);

    for (int i = 0; i<strLen; i++)   if ((str[i] == *DelimitStr))   DelimitIndex ++;

    return DelimitIndex;
}

int _Find_Intex_Delimiter(char *str,char *find,int Index)
{
	int Occurence = 0;

    int strLen = strlen(str);

    for (int i = 0; i<strLen; i++)
    {
    	if ((str[i] == *find))
    	{
    		Occurence ++;
    	}
    }
    return Occurence;
}

char *SplitSampleData(char *StrData,int StartIndex,int StopIndex,char *Delimint)
{
	char *Data = NULL;
	int TotalLen = strlen(StrData);

	for(int i = StartIndex ; i<TotalLen ; i++)
	{
		if(StrData[i] == *Delimint)
		{
			StopIndex = i;
			break;
		}
	}

	StartIndex = StopIndex;

	return Data;

}

int SplitDateTime(char *TimeStr)
{
	//22.06.2013 03:00:00
	int EpochTime = 0;
	int Hour = 0 ,Min = 0 ,Sec = 0 ,Year = 0 ,Mon = 0 ,Day = 0;
	char TimeDelimit[] = {':'};
	char DateDelimit[] = {'.'};
	int StrIndex = 0,StrLen = 0;
	int postion = 0;
	char *TmpTimeStr = NULL;

	StrLen = strlen(TimeStr);

	for(int i = 0 ; i < StrLen ; i++)
	{
		if(TimeStr[i] == *DateDelimit)
		{
			TmpTimeStr = TimeStr - ( StrLen - i);
			if(StrIndex == 0) printf("%s",TmpTimeStr);
			StrIndex ++;
		}
	}
	return EpochTime;
}
