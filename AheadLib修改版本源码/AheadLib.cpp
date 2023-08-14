


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ԥ����
#include "Main.h"
#include "AheadLib.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����
const CHAR STR_BlockHeader[] = "\r\n\r\n\r\n////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\r\n";
const CHAR STR_BlockTail[] = "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\r\n";

const CHAR STR_Preprocessor[] = "// ͷ�ļ�\r\n#include <Windows.h>\r\n";

const CHAR STR_ExportComment[] = "// ��������\r\n";
const CHAR STR_ExportRedirect[] = "#pragma comment(linker, \"/EXPORT:%s=%s.%s,@%d\")\r\n";
const CHAR STR_ExportNormal[] = "#pragma comment(linker, \"/EXPORT:%s%s=_AheadLib_%s,@%d\")\r\n";
const CHAR STR_ExportNoname[] = "#pragma comment(linker, \"/EXPORT:Noname%d=_AheadLib_Noname%d,@%d,NONAME\")\r\n";
const CHAR STR_pfnExport[] = "PVOID pfn%s;\r\n";
const CHAR STR_pfnExportAddr[] = "pfn%s=GetAddress(\"%s\");\r\n";

const CHAR STR_Macro[] =
	"// �궨��\r\n"
	"#define EXTERNC extern \"C\"\r\n"
	"#define NAKED __declspec(naked)\r\n"
	"#define EXPORT __declspec(dllexport)\r\n"
	"\r\n"
	"#define ALCPP EXPORT NAKED\r\n"
	"#define ALSTD EXTERNC EXPORT NAKED void __stdcall\r\n"
	"#define ALCFAST EXTERNC EXPORT NAKED void __fastcall\r\n"
	"#define ALCDECL EXTERNC NAKED void __cdecl\r\n";

const CHAR STR_Hook[] =
	"// Hook �����ռ�\r\n"
	"namespace Hook\r\n"
	"{\r\n"
	"	HHOOK m_hHook;\r\n			// HOOK ���\r\n"
	"\r\n"
	"\r\n"
	"	// HOOK ����\r\n"
	"	LRESULT CALLBACK HookProc(INT iCode, WPARAM wParam, LPARAM lParam)\r\n"
	"	{\r\n"
	"		if (iCode > 0)\r\n"
	"		{\r\n"
	"			;\r\n"
	"		}\r\n"
	"\r\n"
	"		return CallNextHookEx(m_hHook, iCode, wParam, lParam);\r\n"
	"	}\r\n"
	"\r\n"
	"	// Hook\r\n"
	"	inline BOOL WINAPI Hook(INT iHookId = WH_CALLWNDPROC)\r\n"
	"	{\r\n"
	"		m_hHook = SetWindowsHookEx(iHookId, HookProc, NULL, GetCurrentThreadId());\r\n"
	"		return (m_hHook != NULL);\r\n"
	"	}\r\n"
	"\r\n"
	"	// Unhook\r\n"
	"	inline VOID WINAPI Unhook()\r\n"
	"	{\r\n"
	"		if (m_hHook)\r\n"
	"		{\r\n"
	"			UnhookWindowsHookEx(m_hHook);\r\n"
	"		}\r\n"
	"	}\r\n"
	"}\r\n";

const CHAR STR_AheadLib1[] =
	"// AheadLib �����ռ�\r\n"
	"namespace AheadLib\r\n"
	"{\r\n"
	"	HMODULE m_hModule = NULL;	// ԭʼģ����\r\n"
	"	DWORD m_dwReturn[%d] = {0};	// ԭʼ�������ص�ַ\r\n"
	"\r\n"
	"\r\n"
	"	// ����ԭʼģ��\r\n"
	"	inline BOOL WINAPI Load()\r\n"
	"	{\r\n"
	"		TCHAR tzPath[MAX_PATH];\r\n"
	"		TCHAR tzTemp[MAX_PATH * 2];\r\n"
	"\r\n"
	"		%s%s\"));\r\n"
	"		m_hModule = LoadLibrary(tzPath);\r\n"
	"		if (m_hModule == NULL)\r\n"
	"		{\r\n"
	"			wsprintf(tzTemp, TEXT(\"�޷����� %%s�������޷��������С�\"), tzPath);\r\n"
	"			MessageBox(NULL, tzTemp, TEXT(\"AheadLib\"), MB_ICONSTOP);\r\n"
	"		}\r\n"
	"\r\n"
	"		return (m_hModule != NULL);	\r\n"
	"	}\r\n"
	"		\r\n"
	"	// �ͷ�ԭʼģ��\r\n"
	"	inline VOID WINAPI Free()\r\n"
	"	{\r\n"
	"		if (m_hModule)\r\n"
	"		{\r\n"
	"			FreeLibrary(m_hModule);\r\n"
	"		}\r\n"
	"	}\r\n"
	"\r\n";

const CHAR STR_AheadLib2[] =
	"	// ��ȡԭʼ������ַ\r\n"
	"	FARPROC WINAPI GetAddress(PCSTR pszProcName)\r\n"
	"	{\r\n"
	"		FARPROC fpAddress;\r\n"
	"		CHAR szProcName[16];\r\n"
	"		TCHAR tzTemp[MAX_PATH];\r\n"
	"\r\n"
	"%s"
	"		fpAddress = GetProcAddress(m_hModule, pszProcName);\r\n"
	"		if (fpAddress == NULL)\r\n"
	"		{\r\n"
	"			if (HIWORD(pszProcName) == 0)\r\n"
	"			{\r\n"
	"				wsprintf(szProcName, \"%%d\", pszProcName);\r\n"
	"				pszProcName = szProcName;\r\n"
	"			}\r\n"
	"\r\n"
	"			wsprintf(tzTemp, TEXT(\"�޷��ҵ����� %%hs�������޷��������С�\"), pszProcName);\r\n"
	"			MessageBox(NULL, tzTemp, TEXT(\"AheadLib\"), MB_ICONSTOP);\r\n"
	"			ExitProcess(-2);\r\n"
	"		}\r\n"
	"\r\n"
	"		return fpAddress;\r\n"
	"	}\r\n"
	"}\r\n"
	"using namespace AheadLib;\r\n";

const CHAR STR_SystemPath[] = "GetSystemDirectory(tzPath, MAX_PATH);\r\n		lstrcat(tzPath, TEXT(\"\\\\";
const CHAR STR_DefaultPath[] = "lstrcpy(tzPath, TEXT(\"";
const CHAR STR_LoadInNeed[] =
	"		if (m_hModule == NULL)\r\n"
	"		{\r\n"
	"			if (Load() == FALSE)\r\n"
	"			{\r\n"
	"				ExitProcess(-1);\r\n"
	"			}\r\n"
	"		}\r\n"
	"\r\n";

const CHAR STR_DllMain[] =
	"// ��ں���\r\n"
	"BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)\r\n"
	"{\r\n"
	"	if (dwReason == DLL_PROCESS_ATTACH)\r\n"
	"	{\r\n"
	"		DisableThreadLibraryCalls(hModule);\r\n"
	"%s%s%s"
	"	}\r\n"
	"	else if (dwReason == DLL_PROCESS_DETACH)\r\n"
	"	{"
	"%s%s%s"
	"\r\n"
	"	}\r\n"
	"\r\n"
	"	return TRUE;\r\n"
	"}\r\n";

const CHAR STR_TlsAlloc[] =
"\r\n"
"		for (INT i = 0; i < sizeof(m_dwReturn) / sizeof(DWORD); i++)\r\n"
"		{\r\n"
"			m_dwReturn[i] = TlsAlloc();\r\n"
"		}\r\n";

const CHAR STR_TlsFree[] =
"\r\n"
"		for (INT i = 0; i < sizeof(m_dwReturn) / sizeof(DWORD); i++)\r\n"
"		{\r\n"
"			TlsFree(m_dwReturn[i]);\r\n"
"		}\r\n";

const CHAR STR_HookHook[] = "\r\n		Hook::Hook();\r\n";
const CHAR STR_HookUnhook[] = "\r\n		Hook::Unhook();\r\n";
const CHAR STR_LoadInEntry[] = "\r\n		return Load();\r\n";
const CHAR STR_FreeInEntry[] = "\r\n		Free();";

const CHAR STR_JumpToOrigin[] =
	"// ��������\r\n"
	"%s\r\n"
	"{\r\n"
	"	GetAddress(%s);\r\n"
	"	__asm JMP EAX;\r\n"
	"}\r\n";

const CHAR STR_CallOrigin[] =
	"// ��������\r\n"
	"%s\r\n"
	"{\r\n"
	"	// ���淵�ص�ַ\r\n"
	"	__asm POP m_dwReturn[%d * TYPE long];\r\n\r\n"
	"	// ����ԭʼ����\r\n"
	"	GetAddress(%s)();\r\n\r\n"
	"	// ת�������ص�ַ\r\n"
	"	__asm JMP m_dwReturn[%d * TYPE long];\r\n"
	"}\r\n";

const CHAR STR_JumpToAddr[] =
	"// ��������\r\n"
	"%s\r\n"
	"{\r\n"
//	"	GetAddress(%s);\r\n"
	"	__asm JMP pfn%s;\r\n"
	"}\r\n";

const CHAR STR_CallOriginTls[] =
	"// ��������\r\n"
	"%s\r\n"
	"{\r\n"
	"	// ���淵�ص�ַ�� TLS\r\n"
	"	__asm PUSH m_dwReturn[%d * TYPE long];\r\n"
	"	__asm CALL DWORD PTR [TlsSetValue];\r\n\r\n"
	"	// ����ԭʼ����\r\n"
	"	GetAddress(%s)();\r\n\r\n"
	"	// ��ȡ���ص�ַ������\r\n"
	"	__asm PUSH EAX;\r\n"
	"	__asm PUSH m_dwReturn[%d * TYPE long];\r\n"
	"	__asm CALL DWORD PTR [TlsGetValue];\r\n"
	"	__asm XCHG EAX, [ESP];\r\n"
	"	__asm RET;\r\n"
	"}\r\n";

const CHAR STR_ExportVariable[] = "// ��������\r\nEXPORT %s;\r\n";

const CHAR STR_AheadLib2s[] =
	"	// ��ȡԭʼ������ַ\r\n"
	"	FARPROC WINAPI GetAddress(PCSTR pszProcName)\r\n{\r\n";
const CHAR STR_AheadLib2e[] =
	"	}\r\n";
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAheadLib �ྲ̬��Ա����
BOOL CAheadLib::m_bCallRedirect = FALSE;
BOOL CAheadLib::m_bLoadIfNeed = FALSE;
BOOL CAheadLib::m_bJumpToOrigin = FALSE;
BOOL CAheadLib::m_bMultiThread = FALSE;
BOOL CAheadLib::m_bSystemPath = FALSE;
BOOL CAheadLib::m_bGenerateHook = FALSE;
TCHAR CAheadLib::m_tzDllFile[MAX_PATH] = {0};
TCHAR CAheadLib::m_tzCppFile[MAX_PATH] = {0};
CHAR CAheadLib::m_szOriginDll[MAX_PATH] = {0};
CHAR CAheadLib::m_szOrigin[MAX_PATH] = {0};
HMODULE CAheadLib::m_hDbgHelp = NULL;
UNDECORATESYMBOLNAME CAheadLib::m_pUnDecorateSymbolName = NULL;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ALRESULT WINAPI CAheadLib::Generate(BOOL bWriteCppFile)
{
	DWORD i;
	PSTR pszFile;
	DWORD dwSize;
	PSTR pszBuffer;
	PSTR *ppszNames;
	PDWORD pdwNames;
	BOOL bLoadOrigin;
	ALRESULT alResult;
	PWORD pwNamesOrdinals;
	PIMAGE_NT_HEADERS pInh;
	PIMAGE_EXPORT_DIRECTORY pIed;

	_Try
	{
		// ��ʼ��
		pszFile = NULL;
		ppszNames = NULL;
		pszBuffer = NULL;
		SetDlgItemTextA(CMainDlg::m_hWnd, IDC_Preview, NULL);

		// �жϲ����Ƿ�����
		_LeaveExIf((m_szOrigin[0] == 0) || (m_tzDllFile[0] == 0) || (bWriteCppFile && (m_tzDllFile[0] == 0)),
			alResult = ALResult_InvalidArgs);

		// �� DLL �ļ�
		CMapFile mfFile(m_tzDllFile);
		pszFile = (PSTR) mfFile.m_pvFile;
		_LeaveExIf(pszFile == NULL, alResult = ALResult_OpenDllFile);
		_LeaveExIf(mfFile.m_dwSize < 512, alResult = ALResult_InvalidPeFile);

		// �ж��Ƿ�Ϊ PE �ļ�
		pInh = (PIMAGE_NT_HEADERS) (pszFile + ((PIMAGE_DOS_HEADER) pszFile)->e_lfanew);
		_LeaveExIf(pInh->Signature != IMAGE_NT_SIGNATURE, alResult = ALResult_InvalidPeFile);

		// ��λ������
		dwSize = pInh->OptionalHeader.DataDirectory[0].VirtualAddress;
		_LeaveExIf(dwSize == 0, alResult = ALResult_NoExportTable);
		pIed = (PIMAGE_EXPORT_DIRECTORY) (pszFile + RvaToOffset(pInh, dwSize));

		// ��ȡ Names �� Ordinals
		pdwNames = (PDWORD) (pszFile + RvaToOffset(pInh, pIed->AddressOfNames));
		pwNamesOrdinals = (PWORD) (pszFile + RvaToOffset(pInh, pIed->AddressOfNameOrdinals));

		// �����ڴ�
		ppszNames = (PSTR *) _HeapAllocZero(sizeof(PSTR) * pIed->NumberOfFunctions);
		_LeaveExIf(ppszNames == NULL, alResult = ALResult_HeapAlloc);

		// ��ȡ������������
		for (i = 0; i < pIed->NumberOfNames; i++)
		{
			ppszNames[pwNamesOrdinals[i]] = pszFile + RvaToOffset(pInh, pdwNames[i]);
		}

		// �����ڴ�
		pszBuffer = (PSTR) _HeapAlloc(4096 + 1024 * pIed->NumberOfFunctions);
		_LeaveExIf(pszBuffer == NULL, alResult = ALResult_HeapAlloc);

		// ���ɴ��벢���õ�Ԥ���༭��
		dwSize = GenerateCode(pszBuffer, ppszNames, pIed->Base, pIed->NumberOfFunctions, bLoadOrigin);
		SetDlgItemTextA(CMainDlg::m_hWnd, IDC_Preview, pszBuffer);

		// д�뵽�ļ�
		if (bWriteCppFile)
		{
			_LeaveExIf(WriteCppFile(pszBuffer, dwSize) == FALSE, alResult = ALResult_WriteCppFile);
		}

		// ִ�гɹ�
		alResult = (bLoadOrigin && m_bCallRedirect) ? ALResult_NotAllRedirect : ALResult_Success;
	}
	_Finally
	{
		// �ͷ�
		_ExIf(pszBuffer, _HeapFree(pszBuffer));
		_ExIf(ppszNames, _HeapFree(ppszNames));

		return alResult;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ɴ���
DWORD WINAPI CAheadLib::GenerateCode(PSTR pszBuffer, PSTR* ppszNames, DWORD dwBase, DWORD dwCount, BOOL& bLoadOrigin)
{
	PSTR p;
	DWORD i;

	// Ԥ����
	p = pszBuffer;
	CopyString(p, STR_BlockHeader, _LengthOf(STR_BlockHeader));
	CopyString(p, STR_Preprocessor, _LengthOf(STR_Preprocessor));
	CopyString(p, STR_BlockTail, _LengthOf(STR_BlockTail));

	// ��������
	bLoadOrigin = GenerateExport(p, ppszNames, dwBase, dwCount);

	// �궨��
	if (bLoadOrigin)
	{
		CopyString(p, STR_BlockHeader, _LengthOf(STR_BlockHeader));
		CopyString(p, STR_Macro, _LengthOf(STR_Macro));
		CopyString(p, STR_BlockTail, _LengthOf(STR_BlockTail));
	}

	// HOOK ����
	if (m_bGenerateHook)
	{
		CopyString(p, STR_BlockHeader, _LengthOf(STR_BlockHeader));
		CopyString(p, STR_Hook, _LengthOf(STR_Hook));
		CopyString(p, STR_BlockTail, _LengthOf(STR_BlockTail));
	}

	// AheadLib ����
	if (bLoadOrigin)
	{
		CopyString(p, STR_BlockHeader, _LengthOf(STR_BlockHeader));
		p += wsprintfA(p, STR_AheadLib1,
			dwCount,
			m_bSystemPath ? STR_SystemPath : STR_DefaultPath,
			m_szOrigin);
		p += wsprintfA(p, STR_AheadLib2, m_bLoadIfNeed ? STR_LoadInNeed : NULL);
		CopyString(p, STR_BlockTail, _LengthOf(STR_BlockTail));
	}

	// ��ں���
	CopyString(p, STR_BlockHeader, _LengthOf(STR_BlockHeader));
	p += wsprintfA(p, STR_DllMain,
		m_bMultiThread ? STR_TlsAlloc: NULL,
		m_bGenerateHook ? STR_HookHook : NULL,
		bLoadOrigin && (m_bLoadIfNeed == FALSE) ? STR_LoadInEntry : NULL,

		m_bMultiThread ? STR_TlsFree: NULL,
		bLoadOrigin ? STR_FreeInEntry : NULL,
		m_bGenerateHook ? STR_HookUnhook : NULL);
	CopyString(p, STR_BlockTail, _LengthOf(STR_BlockTail));

	// ����
	for (i = 0; i < dwCount; i++)
	{
		// �������ֱ��ת��
		if (CanRedirect(ppszNames[i]) == FALSE)
		{
			GenerateFunction(p, ppszNames[i], dwBase, i);
		}
	}

	*p = 0;

	return (DWORD) (p - pszBuffer);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ѡ�����״̬
VOID WINAPI CAheadLib::SetOptionsEnabled()
{
	EnableWindow(GetDlgItem(CMainDlg::m_hWnd, IDC_LoadInEntry), m_bCallRedirect == FALSE);
	EnableWindow(GetDlgItem(CMainDlg::m_hWnd, IDC_LoadIfNeed), m_bCallRedirect == FALSE);
	EnableWindow(GetDlgItem(CMainDlg::m_hWnd, IDC_JumpToOrigin), m_bCallRedirect == FALSE);
	EnableWindow(GetDlgItem(CMainDlg::m_hWnd, IDC_CallOrigin), m_bCallRedirect == FALSE);
	EnableWindow(GetDlgItem(CMainDlg::m_hWnd, IDC_MultiThread), (m_bCallRedirect == FALSE) && (m_bJumpToOrigin == FALSE));
	EnableWindow(GetDlgItem(CMainDlg::m_hWnd, IDC_SystemPath), m_bCallRedirect == FALSE);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �� INI ������ѡ������
VOID WINAPI CAheadLib::LoadOptions()
{
	m_bCallRedirect = CIni::GetInt(INI_CallRedirect);
	m_bLoadIfNeed = CIni::GetInt(INI_LoadIfNeed);
	m_bJumpToOrigin = CIni::GetInt(INI_JumpToOrign);
	m_bMultiThread = CIni::GetInt(INI_MultiThread);
	m_bSystemPath = CIni::GetInt(INI_SystemPath);
	m_bGenerateHook = CIni::GetInt(INI_GenerateHook);

	CheckRadioButton(CMainDlg::m_hWnd, IDC_CallRedirect, IDC_CallInTime,
		m_bCallRedirect ? IDC_CallRedirect : IDC_CallInTime);
	CheckRadioButton(CMainDlg::m_hWnd, IDC_LoadInEntry, IDC_LoadIfNeed,
		m_bLoadIfNeed ? IDC_LoadIfNeed : IDC_LoadInEntry);
	CheckRadioButton(CMainDlg::m_hWnd, IDC_JumpToOrigin, IDC_CallOrigin,
		m_bJumpToOrigin ? IDC_JumpToOrigin : IDC_CallOrigin);
	CheckDlgButton(CMainDlg::m_hWnd, IDC_MultiThread, m_bMultiThread);
	CheckDlgButton(CMainDlg::m_hWnd, IDC_SystemPath, m_bSystemPath);
	CheckDlgButton(CMainDlg::m_hWnd, IDC_GenerateHook, m_bGenerateHook);

	SetOptionsEnabled();

	m_hDbgHelp = LoadLibrary(TEXT("DbgHelp"));
	if (m_hDbgHelp)
	{
		m_pUnDecorateSymbolName = (UNDECORATESYMBOLNAME) GetProcAddress(m_hDbgHelp, "UnDecorateSymbolName");
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ѡ������
VOID WINAPI CAheadLib::SaveOptions()
{
	CIni::SetInt(INI_CallRedirect, m_bCallRedirect);
	CIni::SetInt(INI_LoadIfNeed, m_bLoadIfNeed);
	CIni::SetInt(INI_JumpToOrign, m_bJumpToOrigin);
	CIni::SetInt(INI_MultiThread, m_bMultiThread);
	CIni::SetInt(INI_SystemPath, m_bSystemPath);
	CIni::SetInt(INI_GenerateHook, m_bGenerateHook);

	_SafeFreeLibrary(m_hDbgHelp);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ȡѡ������
VOID WINAPI CAheadLib::GetOptions()
{
	m_bCallRedirect = IsDlgButtonChecked(CMainDlg::m_hWnd, IDC_CallRedirect);
	m_bLoadIfNeed = IsDlgButtonChecked(CMainDlg::m_hWnd, IDC_LoadIfNeed);
	m_bJumpToOrigin = IsDlgButtonChecked(CMainDlg::m_hWnd, IDC_JumpToOrigin);
	m_bMultiThread = IsDlgButtonChecked(CMainDlg::m_hWnd, IDC_MultiThread);
	m_bSystemPath = IsDlgButtonChecked(CMainDlg::m_hWnd, IDC_SystemPath);
	m_bGenerateHook = IsDlgButtonChecked(CMainDlg::m_hWnd, IDC_GenerateHook);

	SetOptionsEnabled();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ɵ���ָʾ��
BOOL WINAPI CAheadLib::GenerateExport(PSTR& pszBuffer, PSTR* ppszNames, DWORD dwBase, DWORD dwCount)
{
	PSTR p;
	DWORD i;
	BOOL bLoadOrigin;
	BOOL bPragmaExport;

	bLoadOrigin = FALSE;
	bPragmaExport = FALSE;
	for (i = 0; i < dwCount; i++)
	{
		// �������ֱ��ת��
		if (CanRedirect(ppszNames[i]))
		{
			// ת����������
			PragmaExport(pszBuffer, bPragmaExport, dwBase + i, ppszNames[i], TRUE);
		}
		else
		{
			switch (GetExportType(ppszNames[i], p))
			{
			case ET_NONAME:
				// �����Ƶ�������
				PragmaExport(pszBuffer, bPragmaExport, dwBase + i);
				break;

			case ET_CDECL:
				// ���浼������
				PragmaExport(pszBuffer, bPragmaExport, dwBase + i, ppszNames[i]);
				break;

			//default:
				// ֱ���� __declspec(dllexport) ����
			}

			bLoadOrigin = TRUE;
		}
	}

	if (bPragmaExport)
	{
		CopyString(pszBuffer, STR_BlockTail, _LengthOf(STR_BlockTail));
		CopyString(pszBuffer, STR_AheadLib2s, _LengthOf(STR_AheadLib2s));

	}
	for (i = 0; i < dwCount; i++)
	{
		// �������ֱ��ת��
		if (CanRedirect(ppszNames[i]))
		{
			// ת����������
			PragmaExport2(pszBuffer, bPragmaExport, dwBase + i, ppszNames[i], TRUE);
		}
		else
		{
			switch (GetExportType(ppszNames[i], p))
			{
			case ET_NONAME:
				// �����Ƶ�������
				PragmaExport2(pszBuffer, bPragmaExport, dwBase + i);
				break;

			case ET_CDECL:
				// ���浼������
				PragmaExport2(pszBuffer, bPragmaExport, dwBase + i, ppszNames[i]);
				break;

			//default:
				// ֱ���� __declspec(dllexport) ����
			}

			bLoadOrigin = TRUE;
		}
	}

	if (bPragmaExport)
	{
		CopyString(pszBuffer, STR_AheadLib2e, _LengthOf(STR_AheadLib2e));
		CopyString(pszBuffer, STR_BlockTail, _LengthOf(STR_BlockTail));
	}
	return bLoadOrigin;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ɺ���
VOID WINAPI CAheadLib::GenerateFunction(PSTR& pszBuffer, PSTR pszName, DWORD dwBase, DWORD dwIndex)
{
	CHAR szCallName[MAX_PATH];
	CHAR szDeclaration[MAX_PATH * 2];

	CopyString(pszBuffer, STR_BlockHeader, _LengthOf(STR_BlockHeader));
	GenerateDeclaration(szDeclaration, szCallName, pszName, dwBase + dwIndex);
	if (szDeclaration[lstrlenA(szDeclaration) - 1] == ')')
	{
		// ����
		if (m_bJumpToOrigin)
		{
			// ֱ��ת����ԭʼ����
//			pszBuffer += wsprintfA(pszBuffer, STR_JumpToOrigin, szDeclaration, szCallName);
			pszBuffer += wsprintfA(pszBuffer, STR_JumpToAddr, szDeclaration, pszName);

		}
		else
		{
			// ���ú󷵻�
			pszBuffer += wsprintfA(pszBuffer,
				(m_bMultiThread ? STR_CallOriginTls : STR_CallOrigin),
				szDeclaration, dwIndex, szCallName, dwIndex);
		}
	}
	else
	{
		// ����
		pszBuffer += wsprintfA(pszBuffer, STR_ExportVariable, szDeclaration);
	}
	CopyString(pszBuffer, STR_BlockTail, _LengthOf(STR_BlockTail));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ɺϷ��ĺ�������
VOID WINAPI CAheadLib::GenerateDeclaration(PSTR pszDeclaration, PSTR pszCallName, PSTR pszName, DWORD Ordinals)
{
	PSTR p;
	EXPORTTYPE etType;

	etType = GetExportType(pszName, p);
	switch (etType)
	{
	case ET_CPP:
		// C++ ��ʽ����
		if (pszName[lstrlenA(pszName) - 1] != 'A')
		{
			// ����ǵ�������
			CopyString(pszDeclaration, "ALCPP ", _LengthOf("ALCPP "));
		}
		m_pUnDecorateSymbolName(pszName, pszDeclaration, MAX_PATH * 2, 0);
		break;

	case ET_STD:
	case ET_FAST:
		// __fastcall/__stdcall ��ʽ����
		if (etType == ET_STD)
		{
			CopyString(pszDeclaration,  "ALSTD ", _LengthOf("ALSTD "));
		}
		else
		{
			CopyString(pszDeclaration,  "ALFAST ", _LengthOf("ALFAST "));
		}
		CopyString(pszDeclaration, pszName + 1, (INT) (p - pszName - 1));
		GenerateParam(pszDeclaration, (_AStrToInt(p + 1) / 4));
		break;

	case ET_CDECL:
		// __cdecl ��ʽ����
		wsprintfA(pszDeclaration, "ALCDECL AheadLib_%s(void)", pszName);
		break;

	case ET_NONAME:
		// __cdecl ��ʽ����
		wsprintfA(pszDeclaration, "ALCDECL AheadLib_Noname%d(void)", Ordinals);

		// ��������
		wsprintfA(pszCallName, "MAKEINTRESOURCE(%d)", Ordinals);
		return;
	}

	// ��������
	wsprintfA(pszCallName, "\"%s\"", pszName);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �� RVA ת��Ϊ�ļ�ƫ��
DWORD WINAPI CAheadLib::RvaToOffset(const PIMAGE_NT_HEADERS pInh, DWORD dwRva)
{
	INT i;
	PIMAGE_SECTION_HEADER pIsh;

	pIsh = (PIMAGE_SECTION_HEADER) ((PBYTE) pInh + sizeof(IMAGE_NT_HEADERS));
	for (i = 0; i < pInh->FileHeader.NumberOfSections; i++, pIsh++)
	{
		if (dwRva >= (pIsh->VirtualAddress))
		{
			if (((pIsh->VirtualAddress) + (pIsh->SizeOfRawData)) > dwRva)
			{
				return dwRva - pIsh->VirtualAddress + pIsh->PointerToRawData;
			}
		}
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �жϵ�����������
EXPORTTYPE WINAPI CAheadLib::GetExportType(PCSTR pszName, PSTR& pAt)
{
	if(pszName == NULL)
	{
		return ET_NONAME;
	}
	else if (m_pUnDecorateSymbolName && (pszName[0] == '?'))
	{
		return ET_CPP;
	}
	else if ((pszName[0] == '@') || (pszName[0] == '_'))
	{
		pAt = _AStrChr(pszName + 1, '@');
		if (pAt && IsStringNumberic(pAt + 1))
		{
			return (pszName[0] == '@') ? ET_FAST : ET_STD;
		}
	}
	return ET_CDECL;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ɲ����б�
VOID WINAPI CAheadLib::GenerateParam(PSTR pszBuffer, INT iParamCount)
{
	if (iParamCount)
	{
		// ������
		*pszBuffer++ = '(';
		for (INT i = 0; i < iParamCount; i++)
		{
			CopyString(pszBuffer, "long, ", _LengthOf("long, "));
		}
		*(pszBuffer - 2) = ')';
		*(pszBuffer - 1) = 0;
	}
	else
	{
		// �޲�����
		lstrcpyA(pszBuffer, "(void)");
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� #pragma ����ָʾ��
VOID WINAPI CAheadLib::PragmaExport(PSTR& pszBuffer, BOOL& bPragmaExport, DWORD Ordinals, PCSTR pszName, BOOL bRedirect)
{
	if (bPragmaExport == FALSE)
	{
		CopyString(pszBuffer, STR_BlockHeader, _LengthOf(STR_BlockHeader));
		CopyString(pszBuffer, STR_ExportComment, _LengthOf(STR_ExportComment));
		bPragmaExport = TRUE;
	}

	if (bRedirect)
	{
		pszBuffer += wsprintfA(pszBuffer, STR_ExportRedirect, pszName, m_szOrigin, pszName, Ordinals);
	}
	else
	{
		if (pszName)
		{
//			pszBuffer += wsprintfA(pszBuffer, STR_ExportNormal,
//				(pszName[0] == '_') ? "_" :NULL,
//				pszName, pszName, Ordinals);
			pszBuffer += wsprintfA(pszBuffer, STR_pfnExport,
				pszName);
//			pszBuffer += wsprintfA(pszBuffer, STR_pfnExportAddr,
//				pszName,pszName);

		}
		else
		{
			pszBuffer += wsprintfA(pszBuffer, STR_ExportNoname, Ordinals, Ordinals, Ordinals);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// д�뵽 CPP �ļ�
BOOL WINAPI CAheadLib::WriteCppFile(PCSTR pszBuffer, DWORD dwSize)
{
	BOOL bResult;
	HANDLE hFile;

	hFile = _CreateFileForWrite(m_tzCppFile);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	bResult = WriteFile(hFile, pszBuffer, dwSize, &dwSize, NULL);
	CloseHandle(hFile);
	return bResult;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VOID CAheadLib::PragmaExport2(PSTR& pszBuffer, BOOL& bPragmaExport, DWORD Ordinals, PCSTR pszName, BOOL bRedirect)
{
	if (bPragmaExport == FALSE)
	{
		CopyString(pszBuffer, STR_BlockHeader, _LengthOf(STR_BlockHeader));
		CopyString(pszBuffer, STR_ExportComment, _LengthOf(STR_ExportComment));
		bPragmaExport = TRUE;
	}

	if (bRedirect)
	{
		pszBuffer += wsprintfA(pszBuffer, STR_ExportRedirect, pszName, m_szOrigin, pszName, Ordinals);
	}
	else
	{
		if (pszName)
		{
//			pszBuffer += wsprintfA(pszBuffer, STR_ExportNormal,
//				(pszName[0] == '_') ? "_" :NULL,
//				pszName, pszName, Ordinals);
//			pszBuffer += wsprintfA(pszBuffer, STR_pfnExport,
//				pszName);
			pszBuffer += wsprintfA(pszBuffer, STR_pfnExportAddr,
				pszName,pszName);

		}
		else
		{
			pszBuffer += wsprintfA(pszBuffer, STR_ExportNoname, Ordinals, Ordinals, Ordinals);
		}
	}

}
