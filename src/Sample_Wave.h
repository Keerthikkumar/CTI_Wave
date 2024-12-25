/*
 * Sample_Wave.h
 *
 *  Created on: 12-Dec-2024
 *      Author: cornet
 */

#ifndef SAMPLE_WAVE_H_
#define SAMPLE_WAVE_H_

int Total_Of_Samples(char *str,char *DelimitStr);
int _Find_Intex_Delimiter(char *str,char *find,int Index);
char *GetSampleData(char *StrBuffer);
char *SplitSampleData(char *StrData,int StartIndex,int StopIndex,char *Delimint);


int SplitDateTime(char *TimeStr);

#endif /* SAMPLE_WAVE_H_ */
