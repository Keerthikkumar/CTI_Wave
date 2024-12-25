/*
 * File_Handling.h
 *
 *  Created on: 10-Dec-2024
 *      Author: cornet
 */

#ifndef FILE_HANDLING_H_
#define FILE_HANDLING_H_

#include <iostream>
#include <fstream>

#define ROOTPATH "/home/cornet/NIOT/AD06_HDD_WAVE_D1_CSV.csv"
#define SAMPLE_BUFFER_SIZE 32*1024
#define READ_SAMPLE_DATA_SIZE 100*1024*1024

using namespace std;

typedef struct _Wave_CSV_
{
	int TimeStamp;
	float Pitch[1024];
	float Yaw[1024];
	float Roll[1024];
}Wave_CSV;


class CFile_Handle
{
	public:
		CFile_Handle();
		virtual ~CFile_Handle();
		int FileOpen();
		int FileRead();
		int Open_CSV_SampleFile();
		int	Get_Sample_Data(FILE *fp);
		int	file_write_bin(FILE *fp ,char *buffer,int FileIndex);
};


#endif /* FILE_HANDLING_H_ */
