/*
 * ===================================================================
 *
 *	Filename:  CFile.h
 *
 *	Description:  
 *
 *	Version:  1.0
 *	Created:  07/25/2018
 *
 *	Author:  gyl 
 *	Organization:  IChinae(BEIJING) TECH.CO.,LTD. 
 *
 * ===================================================================
*/
#ifndef __CFILE_H__
#define __CFILE_H__
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "RecordPrivate.h"

#ifdef _WIN32
#include <direct.h> 
#include <io.h>
#include <sys/stat.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#endif

typedef void* FILE_H;

enum FILE_MODE
{
	MODE_R = 0,
	MODE_W,
	MODE_A,
	MODE_R_PLUS,
	MODE_W_PLUS,
	MODE_A_PLUS
};

class CFile{
public:
	CFile();
	virtual ~CFile();

	static FILE_H Open(std::string bufPath, int nMode);
	static int Write(FILE_H handle, void *buffer, int nLength);
	static int Read(FILE_H handle, void *buffer, int nLength);
	static int Seek(FILE_H handle, long lOffset, int nFromwhere);
	static int Tell(FILE_H handle);
	static int Close(FILE_H handle);

	static int Access(std::string bufPath);
	static int Makedir(std::string bufPath);
	static int Rename(std::string bufOldPath , std::string bufNewPath);
	
	static int RmDir(std::string DirFullPath);
	static int Rm(std::string FileName);
	//文件大小超过2g，则所有跟文件大小相关的变量类型都要修改！！！待完善
	static unsigned int GetFileSize(std::string FileName);
};


#endif