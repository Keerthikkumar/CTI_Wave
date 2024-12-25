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
	char TimeStamp[64];
	float Yaw[1024];
	float Pitch[1024];
	float Roll[1024];
}Wave_CSV;

int	file_read_str(FILE *fp)
{
	struct stat CSV_Info;
	char *FileStr = NULL;
	int Ret = 0;

	Wave_CSV *Get_Sample_data = NULL;

	int Ret_Fstat = fstat(fileno(fp),&CSV_Info);

	if(Ret_Fstat < 0)
	{
		printf("Cannot Find File\n");
		return Ret_Fstat;
	}

	FileStr = (char*)malloc(CSV_Info.st_size);

	if((FileStr == NULL))
	{
		printf("Failed To Allocate Memory\n");
		return Ret=1;
	}
	if(fp != NULL)
	{
		fread(FileStr ,1,CSV_Info.st_size,fp);
		int NoOfSample = 1;

		char Delimit[] = {"\n"};
		NoOfSample = Total_Of_Samples(FileStr,Delimit);
		char TmpSamRec[NoOfSample*1024] = {};

		Get_Sample_data = (Wave_CSV *)malloc(sizeof(Wave_CSV)*NoOfSample);

		int SampleIndex = 0;
		do
		{
			size_t SampleLen = strcspn(FileStr, "\n");
			snprintf(TmpSamRec,sizeof(TmpSamRec)-1, "%.*s", (int) SampleLen, FileStr);
			if(SampleIndex != 0)
			{
				char Buffer[64] = {};
				int BufferIndex = 0;
				int YawIndex = 0;
				int PitchIndex = 0;
				int RollIndex = 0;
				char *Sample_Buffer = TmpSamRec;
				char delimit[]  = {','};
				{
					do
					{
					size_t SampleLen = strcspn(Sample_Buffer, delimit);
					snprintf(Buffer,sizeof(Buffer)-1, "%.*s", (int) SampleLen, Sample_Buffer);
					if(BufferIndex == 0)
					{
						snprintf(Get_Sample_data[SampleIndex].TimeStamp,sizeof(Get_Sample_data[SampleIndex].TimeStamp),"%s",Buffer);
					}
					else if(BufferIndex < 1025) Get_Sample_data[SampleIndex].Yaw[YawIndex++] = atof(Buffer);
					else if(BufferIndex < 2049) Get_Sample_data[SampleIndex].Pitch[PitchIndex++] = atof(Buffer);
					else if(BufferIndex < 3073) Get_Sample_data[SampleIndex].Roll[RollIndex++] = atof(Buffer);
					Sample_Buffer+= SampleLen;
					BufferIndex++;

					} while (*Sample_Buffer++);
				}
			}
			FileStr += SampleLen;
			SampleIndex++;
		} while (*FileStr++);
//		for(int i = 0 ; i < 1/*NoOfSample*/ ; i++)
		int Chice = 0;
		printf("Total Number of Sample : %d \n",NoOfSample);
		printf("Which Sample you want ?\n");
		scanf("%d",&Chice);
		{
			for(int j = 0 ; j < 1024 ; j++)
				printf("%d - Time : %s\t Compass : %f\t Pitch : %f\t Roll : %f\n",j,Get_Sample_data[Chice].TimeStamp,Get_Sample_data[Chice].Yaw[j],Get_Sample_data[Chice].Pitch[j],Get_Sample_data[Chice].Roll[j]);
		}
	}
	free(Get_Sample_data);
	free(FileStr);
	return Ret;
}


int Open_CSV_File()
{
	int Ret = 0;

	FILE *fb = NULL;

	fb = fopen("/home/cornet/NIOT/AD06_HDD_WAVE_D1_CSV.csv","r");

	if(fb != NULL)
	{
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
