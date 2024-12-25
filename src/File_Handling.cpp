/*
 * File_Handling.cpp
 *
 *  Created on: 10-Dec-2024
 *      Author: cornet
 */

#include "File_Handling.h"

#include <iostream>
#include <memory.h>

CFile_Handle::CFile_Handle()
{
//	memset(&Fb_Csv,0,sizeof(Fb_Csv));

//	Fb_Csv.open("/home/cornet/NIOT/AD06_HDD_WAVE_D1_CSV.csv",std::ios::out);
}
CFile_Handle::~CFile_Handle()
{
//	Fb_Csv.close();
}

int CFile_Handle::FileOpen()
{
	int Ret = 0;
	return Ret;
}

int CFile_Handle::FileRead()
{
	int Ret = 0;

	std::string Data;

	std::ifstream Fileread("/home/cornet/NIOT/Tmp_Text.csv");

	while (std::getline(Fileread, Data)) {
	  // Output the text from the file
	  std::cout << Data;
	}
	return Ret;
}

int CFile_Handle::Open_CSV_SampleFile()
{
	int Ret = 0;

	FILE *fb = NULL;

	fb = fopen(ROOTPATH,"r");

	if(fb != NULL)
	{
		printf("File Opend \n");

		Get_Sample_Data(fb);
	}
	else printf("File Not open\n");

	fclose(fb);

	return Ret;

}

int	CFile_Handle::Get_Sample_Data(FILE *fp)
{
	char *Str = NULL;
	char *Buffer = NULL;
	Str = (char*)malloc(READ_SAMPLE_DATA_SIZE);
	int Ret = 0;
	int Intex = 0;
	if(fp != NULL)
	{
		fread(Str,1,READ_SAMPLE_DATA_SIZE,fp);

		Buffer = strtok(Str,"\n");

		while(Buffer != NULL)
		{
			file_write_bin(fp ,Buffer,Intex);
			Buffer = strtok(NULL,"\n");

			Intex++;
		}

		free(Str);
	}
	return Ret;

}

int	CFile_Handle::file_write_bin(FILE *fp ,char *buffer,int FileIndex)
{
	int Ret = 0;

	char FileName [32]= {};
	FILE *W_bin = NULL;
	sprintf(FileName,"Sample_data_%d.bin",FileIndex);
	W_bin = fopen(FileName,"wb");
	printf("%s",buffer);
	if(W_bin != NULL)
	{
		Ret = fwrite(buffer,1,SAMPLE_BUFFER_SIZE,W_bin);
		if(Ret > 0)
		{
			printf("File Create : %s\n",FileName);
		}
	}
	fclose(W_bin);
	return Ret;
}
