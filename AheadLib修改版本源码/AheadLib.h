


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ԥ����
#pragma once
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������
typedef enum tagALRESULT
{
	ALResult_Success,
	ALResult_NotAllRedirect,
	ALResult_InvalidArgs,
	ALResult_OpenDllFile,
	ALResult_InvalidPeFile,
	ALResult_NoExportTable,
	ALResult_HeapAlloc,
	ALResult_WriteCppFile
}
ALRESULT, *PALRESULT;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������������
typedef enum tagEXPORTTYPE
{
	ET_NONAME,
	ET_CPP,
	ET_STD,
	ET_FAST,
	ET_CDECL
}
EXPORTTYPE, *PEXPORTTYPE;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ı�
const PTSTR STR_AheadLib_Result[] =
{
	TEXT("����ɹ����ɡ�"),
	TEXT("����ɹ����ɣ����ǲ������к�������ֱ��ת����"),
	TEXT("������������"),
	TEXT("�� DLL �ļ�����"),
	TEXT("��Ч�� PE �ļ���"),
	TEXT("�����ļ��в����ڵ�����"),
	TEXT("�޷������ڴ桪������Ц��ʲô�ƻ�����"),
	TEXT("�޷�д�뵽 CPP �ļ��С�")
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
typedef DWORD (WINAPI *UNDECORATESYMBOLNAME)(PCSTR, PSTR, DWORD, DWORD);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAheadLib ��
class CAheadLib
{
public:
	static BOOL m_bCallRedirect;							// ֱ��ת������
	static BOOL m_bLoadIfNeed;								// ��Ҫʱ���� DLL
	static BOOL m_bJumpToOrigin;							// ֱ��ת����ԭʼ����
	static BOOL m_bMultiThread ;							// ֧�ֶ��߳�
	static BOOL m_bSystemPath;								// ϵͳ·��
	static BOOL m_bGenerateHook;							// ���� HOOK ����
	static TCHAR m_tzDllFile[MAX_PATH];						// ���� DLL
	static TCHAR m_tzCppFile[MAX_PATH];						// ��� CPP
	static CHAR m_szOriginDll[MAX_PATH];					// ԭʼ DLL
	static CHAR m_szOrigin[MAX_PATH];						// ԭʼ����

private:
	static HMODULE m_hDbgHelp;								// DbgHelp ģ����
	static UNDECORATESYMBOLNAME m_pUnDecorateSymbolName;	// UnDecorateSymbolName ����ָ��

public:
	// ����
	static ALRESULT WINAPI Generate(BOOL bWriteCppFile = FALSE);

	// ����ѡ�����״̬
	static VOID WINAPI SetOptionsEnabled();

	// �� INI ������ѡ������
	static VOID WINAPI LoadOptions();

	// ����ѡ������
	static VOID WINAPI SaveOptions();

	// ��ȡѡ������
	static VOID WINAPI GetOptions();

	// ��ȡ����ı�
	inline static PCTSTR WINAPI GetResult(ALRESULT alResult)
	{
		return STR_AheadLib_Result[alResult];
	}

private:
	// ���ɴ���
	static DWORD WINAPI GenerateCode(PSTR pszBuffer, PSTR* ppszNames, DWORD dwBase, DWORD dwCount, BOOL& bLoadOrigin);

	// ���ɵ���ָʾ��
	static BOOL WINAPI GenerateExport(PSTR& pszBuffer, PSTR* ppszNames, DWORD dwBase, DWORD dwCount);

	// ���ɺ���
	static VOID WINAPI GenerateFunction(PSTR& pszBuffer, PSTR pszName, DWORD dwBase, DWORD dwIndex);

	// ���ɺϷ��ĺ�������
	static VOID WINAPI GenerateDeclaration(PSTR pszDeclaration, PSTR pszCallName, PSTR pszName, DWORD Ordinals);

	// �� RVA ת��Ϊ�ļ�ƫ��
	static DWORD WINAPI RvaToOffset(const PIMAGE_NT_HEADERS pInh, DWORD dwRva);

	// �жϵ�����������
	static EXPORTTYPE WINAPI GetExportType(PCSTR pszName, PSTR& pAt);

	// ���ɲ����б�
	inline static VOID WINAPI GenerateParam(PSTR pszBuffer, INT iParamCount);

	// ���� #pragma ����ָʾ��
	static VOID WINAPI PragmaExport(PSTR& pszBuffer, BOOL& bPragmaExport, DWORD Ordinals,
		PCSTR pszName = NULL, BOOL bRedirect = FALSE);
	static VOID WINAPI PragmaExport2(PSTR& pszBuffer, BOOL& bPragmaExport, DWORD Ordinals,
		PCSTR pszName = NULL, BOOL bRedirect = FALSE);

	// д�뵽 CPP �ļ�
	static BOOL WINAPI WriteCppFile(PCSTR pszBuffer, DWORD dwSize);

	// �������ݲ��ƶ�ָ��
	inline static VOID WINAPI CopyString(PSTR& pszDest, PCSTR pszSrc, SIZE_T sztSize)
	{
		CopyMemory(pszDest, pszSrc, sztSize);
		pszDest += sztSize;
	}

	// �жϵ��������Ƿ���Ա�ת��
	inline static BOOL WINAPI CanRedirect(PCSTR pszExportName)
	{
		return pszExportName && m_bCallRedirect && IsStringLegality(pszExportName);
	}

	// �ж��ַ����Ƿ�Ϊ�����ִ�
	inline static BOOL WINAPI IsStringNumberic(PCSTR pszString)
	{
		for (PCSTR p = pszString; *p; p++)
		{
			if ((*p < '0') || (*p > '9'))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	// �ж��ַ����Ƿ�Ϊ�Ϸ��ĺ����ַ���
	inline static BOOL WINAPI IsStringLegality(PCSTR pszString)
	{
		for (PCSTR p = pszString; *p; p++)
		{
			if (((*p == '_') ||
				((*p >= 'A') && (*p <= 'Z')) ||
				((*p >= 'a') && (*p <= 'z')) ||
				((*p >= '0') && (*p <= '9'))) == FALSE)
			{
				return FALSE;
			}
		}
		return TRUE;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
