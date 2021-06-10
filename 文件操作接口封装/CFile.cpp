/*
 * ===================================================================
 *
 *	Filename:  CFile.cpp
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
#include "CFile.h"
//#include <errno.h>
CFile::CFile()
{

}
CFile::~CFile()
{

}

FILE_H CFile::Open(std::string bufPath, int nMode)
{
	FILE *file;
	char mode[4] = {0};
	switch (nMode)
	{
	case MODE_R:
		strcpy(mode, "rb");
		break;
	case MODE_W:
		strcpy(mode, "wb");
		break;
	case MODE_A:
		strcpy(mode, "ab");
		break;
	case MODE_R_PLUS:
		strcpy(mode, "rb+");
		break;
	case MODE_W_PLUS:
		strcpy(mode, "wb+");
		break;
	case MODE_A_PLUS:
		strcpy(mode, "ab+");
		break;
	default:
		break;
	}
	file = fopen(bufPath.c_str(), mode);
	if(file == NULL)
	{
		RF_LOGWRN("open file error  %d   bufPath = %s",errno,bufPath.c_str());
	}
	return file;

}
int CFile::Write(FILE_H handle, void *buffer, int nLength)
{
	if( handle == NULL )
	{
		RF_LOGWRN("handle is null");
		return -1;
	}
	FILE *file = static_cast<FILE *>(handle);
	if( nLength < 0 )
	{
		return -1;
	}
	int nSize = fwrite(buffer, 1, nLength, file);

	return nSize;//warn

}
int CFile::Read(FILE_H handle, void *buffer, int nLength)
{
	if( handle == NULL )
	{
		RF_LOGWRN("handle is null");
		return -1;
	}
	FILE *file = static_cast<FILE *>(handle);

	int nSize = fread(buffer, 1, nLength, file);

	return nSize;
}
int CFile::Seek(FILE_H handle, long lOffset, int nFromwhere)
{
	if( handle == NULL )
	{
		RF_LOGWRN("handle is null");
		return -1;
	}
	FILE *file = static_cast<FILE *>(handle);
	int nRet;
	nRet = fseek(file, lOffset, nFromwhere);
	if(nRet != 0)
	{
		RF_LOGWRN("seek file error  %d",errno);
	}
	return nRet;
}
int CFile::Tell(FILE_H handle)
{
	if( handle == NULL )
	{
		RF_LOGWRN("handle is null");
		return -1;
	}
	FILE *file = static_cast<FILE *>(handle);
	int nRet;
	nRet = ftell(file);
	if(nRet == -1)
	{
		RF_LOGWRN("tell file error  %d",errno);
	}
	return nRet;
}
int CFile::Close(FILE_H handle)
{
	if( handle == NULL )
	{
		RF_LOGWRN("handle is null");
		return -1;
	}
	FILE *file = static_cast<FILE *>(handle);
	int nRet;
	nRet = fclose(file);
	return nRet;
}

int CFile::Access(std::string bufPath)
{
	int nRet;

	nRet = access(bufPath.c_str(), 0);
	if( nRet == -1 )
	{
		//RF_LOGERR("have no file , %s" , bufPath.c_str());
	}
	return nRet;
}
int CFile::Makedir(std::string bufPath)
{
	int nRet;
#ifdef _WIN32
	nRet = mkdir(bufPath.c_str());
#else
	nRet = mkdir(bufPath.c_str() , 0777);
#endif

	return nRet;
}

int CFile::Rename(std::string bufOldPath, std::string bufNewPath)
{
	int nRet;

	nRet = rename(bufOldPath.c_str() , bufNewPath.c_str() );

	return nRet;

}

int CFile::RmDir(std::string DirFullPath)
{    
    DIR* dirp = opendir(DirFullPath.c_str());    
    if(!dirp)
    {
        return -1;
    }
    struct dirent *dir;
    struct stat st;
    while((dir = readdir(dirp)) != NULL)
    {
        if(strcmp(dir->d_name,".") == 0
                || strcmp(dir->d_name,"..") == 0)
        {
            continue;
        }    
        std::string SubPath = DirFullPath + '/' + dir->d_name;
        if(lstat(SubPath.c_str(),&st) == -1)
        {
            RF_LOGERR("RmDir:lstat %s error\n",SubPath.c_str());
            continue;
        }    
        if(S_ISDIR(st.st_mode))
        {
            if(RmDir(SubPath) == -1) // 如果是目录文件，递归删除
            {
                closedir(dirp);
                return -1;
            }
            rmdir(SubPath.c_str());
        }
        else if(S_ISREG(st.st_mode))
        {
            unlink(SubPath.c_str());     // 如果是普通文件，则unlink
        }
        else
        {
            RF_LOGERR("RmDir:st_mode %s error ",SubPath.c_str());
            continue;
        }
    }
    if(rmdir(DirFullPath.c_str()) == -1)//delete dir itself.
    {
        closedir(dirp);
        return -1;
    }
    closedir(dirp);
    return 0;
}

int CFile::Rm(std::string FileName)
{
    struct stat st;    
    if(lstat(FileName.c_str(),&st) == -1)
    {
        return -1;
    }
    if(S_ISREG(st.st_mode))
    {
        if(unlink(FileName.c_str()) == -1)
        {
            return -1;
        }    
    }
    else if(S_ISDIR(st.st_mode))
    {
        if(FileName == "." || FileName == "..")
        {
            return -1;
        }    
        if(RmDir(FileName) == -1)//delete all the files in dir.
        {
            return -1;
        }
    }
    return 0;
}

unsigned int CFile::GetFileSize(std::string FileName)
{
	struct stat buf;
	if( stat( FileName.c_str() , &buf ) < 0 )
	{
		RF_LOGWRN("get file size error %s" , FileName.c_str());
		return -1;
	}
	else
	{
		return (unsigned long long int)buf.st_size;
	}
}
