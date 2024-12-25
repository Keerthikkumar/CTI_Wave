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

using namespace std;

#define TOTAL_SAMPEL_PER_REC 1024

typedef struct _Wave_CSV_
{
	char TimeStamp[32];
	float Yaw[TOTAL_SAMPEL_PER_REC];
	float Pitch[TOTAL_SAMPEL_PER_REC];
	float Roll[TOTAL_SAMPEL_PER_REC];
}Wave_CSV;

Wave_CSV Set_Wave_Data(char *Sample_Buffer)
{
	char *Buffer = (char *)malloc(32);
	int BufferIndex = 0;
	char SampleDelimit[]  = {','};
	Wave_CSV WaveData = {};

#if 0
	size_t SampleLen = strcspn(Sample_Buffer, SampleDelimit);
//	snprintf(Buffer,sizeof(Buffer), "%.*s", (int) SampleLen, Sample_Buffer);
	snprintf(Buffer,32, "%.*s", (int) SampleLen, Sample_Buffer);

	snprintf(WaveData.TimeStamp,sizeof(WaveData.TimeStamp),"%s",Buffer);

	Sample_Buffer+= SampleLen;
	Sample_Buffer++;

	int Index = 0;
	for(Index = 0; Index < 1024 ; Index++)
	{
		size_t SampleLen = strcspn(Sample_Buffer, SampleDelimit);
		snprintf(Buffer,32, "%.*s", (int) SampleLen, Sample_Buffer);
		WaveData.Yaw[Index] = atof(Buffer);
		Sample_Buffer+= SampleLen;
		Sample_Buffer++;
	}
	for(Index = 0; Index < 1024 ; Index++)
	{
		size_t SampleLen = strcspn(Sample_Buffer, SampleDelimit);
		snprintf(Buffer,32, "%.*s", (int) SampleLen, Sample_Buffer);
		WaveData.Pitch[Index] = atof(Buffer);
		Sample_Buffer+= SampleLen;
		Sample_Buffer++;
	}
	for(Index = 0; Index < 1024 ; Index++)
	{
		size_t SampleLen = strcspn(Sample_Buffer, SampleDelimit);
		snprintf(Buffer,32, "%.*s", (int) SampleLen, Sample_Buffer);
		WaveData.Roll[Index] = atof(Buffer);
		Sample_Buffer+= SampleLen;
		Sample_Buffer++;
	}

	free(Buffer);
	Buffer = NULL;
#endif

#if 1
	do
	{
		size_t SampleLen = strcspn(Sample_Buffer, SampleDelimit);
		snprintf(Buffer,32 ,"%.*s", (int) SampleLen, Sample_Buffer);
		if(BufferIndex == 0)
			snprintf(WaveData.TimeStamp,sizeof(WaveData.TimeStamp),"%s",Buffer);

		else if(BufferIndex < TOTAL_SAMPEL_PER_REC + 1)
			WaveData.Yaw[BufferIndex-1] = atof(Buffer);

		else if(BufferIndex < (TOTAL_SAMPEL_PER_REC*2) + 1)
			WaveData.Pitch[BufferIndex-( TOTAL_SAMPEL_PER_REC )-1] = atof(Buffer);

		else if(BufferIndex < (TOTAL_SAMPEL_PER_REC *3) + 1)
			WaveData.Roll[BufferIndex-(TOTAL_SAMPEL_PER_REC*2)-1] = atof(Buffer);

		Sample_Buffer+= SampleLen;
		BufferIndex++;

	} while (*Sample_Buffer++);
	free(Buffer);
	Buffer = NULL;
#endif

	return WaveData;
}

int	file_read_str(FILE *fp)
{
	struct stat CSV_Info;
	char *FileStr = NULL;
	char *CpyFileStr = NULL;
	int Ret = 0;
	int IG_Count = 0;
	int NoOfSample = 0;
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

	CpyFileStr = FileStr;

	if(fp != NULL)
	{
		if(fread(CpyFileStr ,1,CSV_Info.st_size,fp) < 0)
		{
			printf("Failed to file read");
			return Ret;
		}


		char RecordDelimit[] = {"\n"};
		NoOfSample = Total_Of_Samples(CpyFileStr,RecordDelimit);

		char TmpSamRec[NoOfSample*16] = {};
//		char *TmpSamRec = NULL;

		Get_Sample_data = (Wave_CSV *)malloc(sizeof(Wave_CSV)*(NoOfSample-1));

		int SampleIndex = 0;
		do
		{
			size_t RecordLen = strcspn(CpyFileStr, "\n");
			snprintf(TmpSamRec,sizeof(TmpSamRec), "%.*s", (int) RecordLen , CpyFileStr);
//			sprintf(TmpSamRec,"%.*s", (int) RecordLen , CpyFileStr);

			if((SampleIndex != 0) && (strlen(TmpSamRec) > 0))
			{

				Get_Sample_data[SampleIndex-1] = Set_Wave_Data(TmpSamRec);

//				char Buffer[32] = {};
//				int BufferIndex = 0;
//
//				char *Sample_Buffer = TmpSamRec;
//				char SampleDelimit[]  = {','};
//
//				do
//				{
//					size_t SampleLen = strcspn(Sample_Buffer, SampleDelimit);
//					snprintf(Buffer,sizeof(Buffer), "%.*s", (int) SampleLen, Sample_Buffer);
//
//					if(BufferIndex == 0)	snprintf(Get_Sample_data[SampleIndex-1].TimeStamp,sizeof(Get_Sample_data[SampleIndex-1].TimeStamp),"%s",Buffer);
//
//					else if(BufferIndex < TOTAL_SAMPEL_PER_REC + 1)
//						Get_Sample_data[SampleIndex-1].Yaw[BufferIndex-1] = atof(Buffer);
//
//					else if(BufferIndex < (TOTAL_SAMPEL_PER_REC *2)+ 1)
//						Get_Sample_data[SampleIndex-1].Pitch[BufferIndex-( TOTAL_SAMPEL_PER_REC )-1] = atof(Buffer); 	//1025-1024-1=0 : 2048-1024-1=0
//
//					else if(BufferIndex < (TOTAL_SAMPEL_PER_REC * 3) + 1)
//						Get_Sample_data[SampleIndex-1].Roll[BufferIndex-(TOTAL_SAMPEL_PER_REC*2)-1] = atof(Buffer);		//2049-1024*2-1= 0
//
//					Sample_Buffer+= SampleLen;
//					BufferIndex++;
//
//				} while (*Sample_Buffer++);

			}
			else { IG_Count += 1;}
			CpyFileStr += RecordLen ;
			SampleIndex++;
		} while (*CpyFileStr++);


	}

	int Ch = 0;
	printf("Total Number of Sample : %d \n",NoOfSample - IG_Count);
	printf("Which Sample you want ?\n");
	scanf("%d",&Ch);
	for(int j = 0 ; j < TOTAL_SAMPEL_PER_REC ; j++)
		printf("%d - Time : %s\t Compass : %f\t Pitch : %f\t Roll : %f\n",j,Get_Sample_data[Ch].TimeStamp,
																			Get_Sample_data[Ch].Yaw[j],
																			Get_Sample_data[Ch].Pitch[j],
																			Get_Sample_data[Ch].Roll[j]);

	free(Get_Sample_data);
	free(FileStr);
	return Ret;
}


int Open_CSV_File(char *FileName)
{
	int Ret = 0;

	FILE *fb = NULL;

	fb = fopen(FileName,"r");

	if(fb != NULL)
	{
		file_read_str(fb);
	}
	else
	{
		printf("Cannot File open\n");

		return Ret;
	}


	fclose(fb);

	return Ret;
}

int main(int argc,char *argv[])
{
//	if(argc < 2)
//	{
//		printf("Usage : <Exec Name> <CSV File Name>\n");
//		return 0;
//	}
//
//	Open_CSV_File(argv[1]);
	Open_CSV_File("/home/cornet/NIOT/DOC/AD06_HDD_WAVE_D1_CSV.csv");

	return 0;
}
