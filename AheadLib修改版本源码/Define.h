


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ԥ����
#pragma once


#define _CHS
#define _WINVER					0x0400

#if (_WINVER >= 0x0500)
#define UNICODE
#define _UNICODE
#endif

#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������Ϣ
#define VER_Major				2
#define VER_Minor				2
#define VER_Release				150 
#define VER_Build				653  
#define VER_Version				MAKELONG(MAKEWORD(VER_Major, VER_Minor), VER_Release)

#define _Stringizing(v)			#v
#define _VerJoin(a, b, c, d)	_Stringizing(a.b.c.d)

#define STR_BuildDate			TEXT(__DATE__)
#define STR_BuildTime			TEXT(__TIME__)
#define STR_BuilDateTime		TEXT(__DATE__) TEXT(" ") TEXT(__TIME__)
#define STR_Version				TEXT(_VerJoin(VER_Major, VER_Minor, VER_Release, VER_Build))

#define STR_AppName				TEXT("AheadLib")
#define STR_Author				TEXT("Yonsm")
#define STR_Corporation			TEXT("Yonsm.com")
#define STR_Web					TEXT("www.luocong.com/bbs")
#define STR_Email				TEXT("Yonsm@163.com")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��չ��
#define EXT_Chm					TEXT(".chm")
#define EXT_Dll					TEXT(".dll")
#define EXT_Exe					TEXT(".exe")
#define EXT_Ini					TEXT(".ini")
#define EXT_Cpp					TEXT(".cpp")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INI ����
#define INI_Main				STR_AppName
#define INI_WindowLeft			TEXT("WindowLeft")
#define INI_WindowTop			TEXT("WindowTop")
#define INI_WindowWidth			TEXT("WindowWidth")
#define INI_WindowHeight		TEXT("WindowHeight")
#define INI_WindowState			TEXT("WindowState")
#define INI_ShowSplash			TEXT("ShowSplash")

#define INI_ShowOptions			TEXT("ShowOptions")
#define INI_CallRedirect		TEXT("CallRedirect")
#define INI_LoadIfNeed			TEXT("LoadIfNeed")
#define INI_JumpToOrign			TEXT("JumpToOrign")
#define INI_MultiThread			TEXT("MultiThread")
#define INI_SystemPath			TEXT("SystemPath")
#define INI_GenerateHook		TEXT("GenerateHook")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����ַ���
#define	STR_CheckUpdate			TEXT("������")
#define	STR_VisitWeb			TEXT("������վ")
#define	STR_WriteEmail			TEXT("д�Ÿ�����")

#define STR_CheckUpdateTip		TEXT("�� Internet �ϼ�����������Ϣ")
#define STR_VisitWebTip			TEXT("���� ") STR_Web
#define STR_WriteEmailTip		TEXT("д�ŵ� ") STR_Email

#define STR_VisitWebUrl			TEXT("http://") STR_Web
#define STR_WriteEmailUrl		TEXT("mailto:") STR_Email TEXT("?Subject=") STR_AppName

#define STR_VersionStamp		TEXT("�汾: ") STR_Version
#define STR_BuildStamp			TEXT("����: ") STR_BuilDateTime
#define STR_Description			TEXT("�����ݵ����� Trojan DLL ���롣")
#define STR_Copyright			TEXT("��Ȩ���� (C) 2004 ") STR_Corporation TEXT("����������Ȩ����")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ļ���չ��������
#define FILTER_All				TEXT("�����ļ�(*.*)\0*.*\0")
#define FILTER_Dll				TEXT("DLL �ļ�(*.dll)\0*.dll\0")
#define FILTER_Cpp				TEXT("CPP �ļ�(*.cpp)\0*.cpp\0")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
