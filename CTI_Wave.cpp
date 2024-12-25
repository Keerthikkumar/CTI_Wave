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

		char RecordDelimit[] = {"\n"};
		NoOfSample = Total_Of_Samples(FileStr,RecordDelimit);
//		char TmpSamRec[NoOfSample*1024] = {};
		char TmpSamRec[NoOfSample*16] = {};

		Get_Sample_data = (Wave_CSV *)malloc(sizeof(Wave_CSV)*(NoOfSample-1));

		int SampleIndex = 0;
		do
		{
			size_t RecordLen = strcspn(FileStr, "\n");
			snprintf(TmpSamRec,sizeof(TmpSamRec), "%.*s", (int) RecordLen , FileStr);

//			printf("Rec len : %ld\n",strlen(TmpSamRec));
			if((SampleIndex != 0) && (strlen(TmpSamRec) > 0))
			{
				char Buffer[32] = {};
				int BufferIndex = 0;
				int YawIndex = 0;
				int PitchIndex = 0;
				int RollIndex = 0;
				char *Sample_Buffer = TmpSamRec;
				char SampleDelimit[]  = {','};

				do
				{
					size_t SampleLen = strcspn(Sample_Buffer, SampleDelimit);
					snprintf(Buffer,sizeof(Buffer), "%.*s", (int) SampleLen, Sample_Buffer);
					if(BufferIndex == 0)
						snprintf(Get_Sample_data[SampleIndex-1].TimeStamp,sizeof(Get_Sample_data[SampleIndex-1].TimeStamp),"%s",Buffer);

					else if(BufferIndex < TOTAL_SAMPEL_PER_REC + 1)
					{
						Get_Sample_data[SampleIndex-1].Yaw[YawIndex++] = atof(Buffer);
					}
					else if(BufferIndex < TOTAL_SAMPEL_PER_REC + 1024 + 1) 		Get_Sample_data[SampleIndex-1].Pitch[PitchIndex++] = atof(Buffer);
					else if(BufferIndex < TOTAL_SAMPEL_PER_REC + (1024*2) + 1) 	Get_Sample_data[SampleIndex-1].Roll[RollIndex++] = atof(Buffer);

					Sample_Buffer+= SampleLen;
					BufferIndex++;

				} while (*Sample_Buffer++);

			}
			FileStr += RecordLen ;
			SampleIndex++;
		} while (*FileStr++);


		//		for(int i = 0 ; i < 1/*NoOfSample*/ ; i++)
		int Ch = 0;
		printf("Total Number of Sample : %d \n",NoOfSample);
		printf("Which Sample you want ?\n");
		scanf("%d",&Ch);
		{
			for(int j = 0 ; j < TOTAL_SAMPEL_PER_REC ; j++)
				printf("%d - Time : %s\t Compass : %f\t Pitch : %f\t Roll : %f\n",j,Get_Sample_data[Ch].TimeStamp,
																					Get_Sample_data[Ch].Yaw[j],
																					Get_Sample_data[Ch].Pitch[j],
																					Get_Sample_data[Ch].Roll[j]);
		}
	}
	free(Get_Sample_data);
//	free(FileStr);  // invalid free pointer ?
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
	if(argc < 2)
	{
		printf("Usage : <Exec Name> <CSV File Name>\n");
		return 0;
	}

	Open_CSV_File(argv[1]);
	return 0;
}
