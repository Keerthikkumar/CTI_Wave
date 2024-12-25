//============================================================================
// Name        : CTI_Wave.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <string.h>
#include <unistd.h>

#include "Sample_Wave.h"

#define SAMPLE_BUFFER_SIZE 32*1024
#define READ_SAMPLE_DATA_SIZE 100*1024*1024

using namespace std;

typedef struct _Wave_CSV_
{
	char *TimeStamp;
	float Yaw[1024];
	float Pitch[1024];
	float Roll[1024];
}Wave_CSV;

int Load_Wave_Data(char *SampleBuffer)
{
	int Ret = 0;
	int CompassIndex = 0;
	int RollIndex = 0;
	int PitchIndex = 0;

	Wave_CSV *Set_Sample_Data = NULL;
	int SampleIndex = 0;
	char *Data = NULL;
	Data = strtok(SampleBuffer ,",");

	Set_Sample_Data = (Wave_CSV*)malloc(sizeof(Wave_CSV));
//	Set_Sample_Data->TimeStamp = (char*)malloc(sizeof(char));

//	memset(Set_Sample_Data ,0,sizeof(Wave_CSV));
	while(Data != NULL)
	{
		if(SampleIndex == 0)
		{
//			strcpy(Set_Sample_Data->TimeStamp,Data);
//			memcpy(Set_Sample_Data->TimeStamp,Data,32);

		}
		else if(SampleIndex-1 < 1024)
		{
			Set_Sample_Data->Yaw[CompassIndex] = atof(Data);
			CompassIndex++;
		}
		else if(SampleIndex-1 < 2048)
		{
			Set_Sample_Data->Pitch[PitchIndex] = atof(Data);
			PitchIndex++;
		}
		else if(SampleIndex-1 < 3096)
		{
			Set_Sample_Data->Roll[RollIndex] = atof(Data);
			RollIndex++;
		}
		SampleIndex++;
		Data = strtok(NULL,",");
	}

	for(int i = 0 ; i < 1024 ; i++)
	{
		printf("Index %d\t Compass : %f\t Pitch : %f\t Roll : %f\n",i,Set_Sample_Data->Yaw[i],
																		Set_Sample_Data->Pitch[i],Set_Sample_Data->Roll[i]);
	}
//	free(Set_Sample_Data->TimeStamp);
	free(Set_Sample_Data);
	Set_Sample_Data = NULL;
	return Ret;
}

int	Create_Sample_BinFile(FILE *fp ,char *buffer,int FileIndex)
{
	int Ret = 0;

	char FileName [32]= {};
	FILE *fp_bin = NULL;
	sprintf(FileName,"Sample_data_%d.bin",FileIndex);
	fp_bin = fopen(FileName,"wb");
	if(fp_bin != NULL)
	{

		if(FileIndex == 2)
		{
			Ret = fwrite(buffer,1,SAMPLE_BUFFER_SIZE,fp_bin);
			Load_Wave_Data(buffer);
		}
	}
	fclose(fp_bin);
	return Ret;
}

int	file_read_str(FILE *fp)
{
	struct stat CSV_Info;
	char *Str = NULL;
	char *Buffer = NULL;
	int Ret = 0;
	int Intex = 0;
	int Ret_Fstat = fstat(fileno(fp),&CSV_Info);

	if(Ret_Fstat < 0)
	{
		printf("File Cannot find\n");
		return Ret_Fstat;
	}

	Str = (char*)malloc(CSV_Info.st_size);

	if(Str == NULL)
	{
		printf("Memory Allocate Fail\n");
		return Ret=1;
	}
	if(fp != NULL)
	{
		fread(Str,1,CSV_Info.st_size,fp);

		int NoOfSample = Find_Buffer_Intex(Str);

		Buffer = strtok(Str,"\n");

		printf("NO of Sample : %d\n",NoOfSample);

		while(Buffer != NULL)
		{
			Create_Sample_BinFile(fp ,Buffer,Intex);
			Buffer = strtok(NULL,"\n");

			Intex++;
		}

	}
	free(Str);
	return Ret;
}


int Open_CSV_File()
{
	int Ret = 0;

	FILE *fb = NULL;

	fb = fopen("/home/cornet/NIOT/AD06_HDD_WAVE_D1_CSV.csv","r");

	if(fb != NULL)
	{
		printf("File Opend \n");

		file_read_str(fb);
	}
	else printf("File Not open\n");

	fclose(fb);

	return Ret;
}

int main()
{
	Open_CSV_File();
	return 0;
}
