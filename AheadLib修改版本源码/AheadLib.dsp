# Microsoft Developer Studio Project File - Name="AheadLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AheadLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AheadLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AheadLib.mak" CFG="AheadLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AheadLib - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "AheadLib - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AheadLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /GZ PRECOMP_VC7_TOBEREMOVED /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /GZ PRECOMP_VC7_TOBEREMOVED /c
# ADD BASE MTL /nologo /win32
# ADD MTL /nologo /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "AheadLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Zi /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" PRECOMP_VC7_TOBEREMOVED /c
# ADD CPP /nologo /W3 /GX /Zi /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR PRECOMP_VC7_TOBEREMOVED /c
# ADD BASE MTL /nologo /win32
# ADD MTL /nologo /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /opt:ref /opt:icf
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /opt:ref /opt:icf

!ENDIF 

# Begin Target

# Name "AheadLib - Win32 Debug"
# Name "AheadLib - Win32 Release"
# Begin Group "源"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=.\AboutDlg.cpp
DEP_CPP_ABOUT=\
	".\AboutDlg.h"\
	".\AheadLib.h"\
	".\Define.h"\
	".\Ini.h"\
	".\Macro.h"\
	".\Main.h"\
	".\MainDlg.h"\
	".\MapFile.h"\
	
# End Source File
# Begin Source File

SOURCE=.\AheadLib.cpp
DEP_CPP_AHEAD=\
	".\AboutDlg.h"\
	".\AheadLib.h"\
	".\Define.h"\
	".\Ini.h"\
	".\Macro.h"\
	".\Main.h"\
	".\MainDlg.h"\
	".\MapFile.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Ini.cpp
DEP_CPP_INI_C=\
	".\AboutDlg.h"\
	".\AheadLib.h"\
	".\Define.h"\
	".\Ini.h"\
	".\Macro.h"\
	".\Main.h"\
	".\MainDlg.h"\
	".\MapFile.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Main.cpp
DEP_CPP_MAIN_=\
	".\AboutDlg.h"\
	".\AheadLib.h"\
	".\Define.h"\
	".\Ini.h"\
	".\Macro.h"\
	".\Main.h"\
	".\MainDlg.h"\
	".\MapFile.h"\
	
# End Source File
# Begin Source File

SOURCE=.\MainDlg.cpp
DEP_CPP_MAIND=\
	".\AboutDlg.h"\
	".\AheadLib.h"\
	".\Define.h"\
	".\Ini.h"\
	".\Macro.h"\
	".\Main.h"\
	".\MainDlg.h"\
	".\MapFile.h"\
	
# End Source File
# Begin Source File

SOURCE=.\MapFile.cpp
DEP_CPP_MAPFI=\
	".\AboutDlg.h"\
	".\AheadLib.h"\
	".\Define.h"\
	".\Ini.h"\
	".\Macro.h"\
	".\Main.h"\
	".\MainDlg.h"\
	".\MapFile.h"\
	
# End Source File
# End Group
# Begin Group "头"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\AheadLib.h
# End Source File
# Begin Source File

SOURCE=.\Define.h
# End Source File
# Begin Source File

SOURCE=.\Ini.h
# End Source File
# Begin Source File

SOURCE=.\Macro.h
# End Source File
# Begin Source File

SOURCE=.\Main.h
# End Source File
# Begin Source File

SOURCE=.\MainDlg.h
# End Source File
# Begin Source File

SOURCE=.\MapFile.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Group "资源"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx"
# Begin Source File

SOURCE=.\Resource\Main.ico
# End Source File
# Begin Source File

SOURCE=.\Resource.rc
# End Source File
# End Group
# Begin Source File

SOURCE=.\Resource\ClassXP.manifest
# End Source File
# End Target
# End Project
