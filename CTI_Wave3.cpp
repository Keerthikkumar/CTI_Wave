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

int To_Print_SampleDate(int Total_Sample,char *Sample_Buffer)
{
	int Ret = 0;
	Wave_CSV *Get_Sample_data;
	Get_Sample_data = (Wave_CSV *)malloc(sizeof(Wave_CSV)*Total_Sample);

	char *tmp_Buffer = NULL;
	int Rec_index = 0;
	int Data_index = 0;

	if(Get_Sample_data == NULL)
	{
		printf("Sample Data Memory Allocation is failed\n");
		return Ret = 1;
	}
	free(Get_Sample_data);
	return Ret;
}

int	file_read_str(FILE *fp)
{
	struct stat CSV_Info;
	char *FileStr = NULL;
	char *TmpFileStr = NULL;
	char *TmpSamStr = NULL;
	int Ret = 0;
	int StartIndex = 0,StopIndex = 0;

	Wave_CSV *Get_Sample_data;


	int Ret_Fstat = fstat(fileno(fp),&CSV_Info);

	if(Ret_Fstat < 0)
	{
		printf("File Cannot find\n");
		return Ret_Fstat;
	}

	FileStr = (char*)malloc(CSV_Info.st_size);
	TmpFileStr = (char*)malloc(CSV_Info.st_size);

	if(FileStr == NULL)
	{
		printf("Memory Allocate Fail\n");
		return Ret=1;
	}


	char *TmpFileData = NULL;
	char *TmpSamRec = NULL;

	if(fp != NULL)
	{
		fread(FileStr ,1,CSV_Info.st_size,fp);
		strcpy(TmpFileStr,FileStr);
		int NoOfSample = 1;
		int NoOfData = 0;

		char Delimit[] = {"\n"};

		NoOfSample = Find_Intex_Delimiter(FileStr,Delimit);

 		printf("%d \t Sampl Total str %ld\n",NoOfSample, strlen(FileStr));

 		Get_Sample_data = (Wave_CSV *)malloc(sizeof(Wave_CSV)*NoOfSample);

 		int TmpIndex = 0;
 		int RecIndex = 0;
 		TmpFileData  = strtok(TmpFileStr,"\n");
 		while(TmpFileData != NULL)
 		{

 			if(TmpIndex > 0)
 			{

 				TmpSamRec = strtok(TmpFileData,",");
// 				for(int SampleIndex = 0 ; TmpSamRec != NULL ; SampleIndex++)
 				int SampleIndex = 0;
 				while(TmpSamRec != NULL)
 				{
// 					if(SampleIndex == 1)
 					{
 	 					if(SampleIndex == 0) strcpy(Get_Sample_data[RecIndex].TimeStamp ,TmpSamRec);
 	 					if (SampleIndex < 1024) Get_Sample_data[RecIndex].Yaw[SampleIndex] = atof(TmpSamRec);
 	 					else if (SampleIndex < 2049) Get_Sample_data[RecIndex].Pitch[SampleIndex] = atof(TmpSamRec);
 	 					else if (SampleIndex < 3063) Get_Sample_data[RecIndex].Roll[SampleIndex] = atof(TmpSamRec);

 					}
 					TmpSamRec = strtok(NULL,",");
 					SampleIndex++;
 				}
 				RecIndex++;
 			}
 			free(TmpSamStr);
 			TmpFileData = strtok(NULL,"\n");
 			TmpIndex++;
 		}

 		for(int SampleIndex = 0 ; SampleIndex < NoOfSample ; SampleIndex++)
 		{
 			if(SampleIndex == 0)
 			{
 				for(int Pintex = 0 ; Pintex < 1024 ; Pintex++)
 				printf("[%d - %d] TimeStamp : %s \t Yaw : %f \t Pitch : %f \t Roll : %f\n",SampleIndex,Pintex,
 						Get_Sample_data[SampleIndex].TimeStamp
 						,Get_Sample_data[SampleIndex].Yaw[Pintex]
						,Get_Sample_data[SampleIndex].Pitch[Pintex]
						,Get_Sample_data[SampleIndex].Roll[Pintex]);
 			}

 		}


	}
	free(TmpFileStr);
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
