


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 预处理
#pragma once
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CMapFile 类
class CMapFile
{
public:
	HANDLE m_hFile;		// 文件句柄
	HANDLE m_hMapping;	// 映射句柄
	PVOID m_pvFile;		// 映射地址
	DWORD m_dwSize;		// 文件大小

public:
	// 构造函数，映射文件为只读
	WINAPI CMapFile(PCTSTR ptzFileName);

	// 构造函数，映射文件为可读写
	WINAPI CMapFile(PCTSTR ptzFileName, DWORD dwSize);

	// 析构函数
	WINAPI ~CMapFile();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
