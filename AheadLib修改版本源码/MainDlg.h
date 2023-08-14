


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ԥ����
#pragma once
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CMainDlg ��
class CMainDlg
{
public:
	static HWND m_hWnd;			// �Ի�����

private:
	static BOOL m_bShowOptions;	// �Ƿ���ʾѡ��

public:
	// ��ʾ�Ի���
	inline static INT_PTR WINAPI Show(HINSTANCE hInstance, PCTSTR ptzCmdLine = NULL)
	{
		return DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_Main), NULL, MainDlgProc, (LPARAM) ptzCmdLine);
	}

private:
	// �ص�����
	static INT_PTR CALLBACK MainDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// ��ʼ��
	static VOID WINAPI OnInitDialog(LPARAM lParam);

	// �����
	static VOID WINAPI OnCommand(WPARAM wParam);

	// ϵͳ�����
	static VOID WINAPI OnSysCommand(WPARAM wParam);

	// ��С�ı�
	static VOID WINAPI OnSize(WPARAM wParam, LPARAM lParam);

	// �ر�
	static VOID WINAPI OnClose();

	// ��ʾ����ѡ��
	static VOID WINAPI OnOptions();

	// ����ļ�
	static VOID WINAPI OnBrowse(BOOL bDllFile);

	// ��Ϣ��
	inline static INT WINAPI MsgBox(PCTSTR ptzText = NULL, UINT uType = MB_ICONINFORMATION)
	{
		return MessageBox(m_hWnd, ptzText, STR_AppName, uType);
	}

	// �����
	inline static INT WINAPI ErrorBox(PCTSTR ptzText = NULL)
	{
		return MsgBox(ptzText, MB_ICONSTOP);
	}

	// ���д���
	inline static BOOL WINAPI CenterWindow(INT iWidth, INT iHeight)
	{
		return MoveWindow(m_hWnd,
			(GetSystemMetrics(SM_CXSCREEN) - iWidth) / 2,
			(GetSystemMetrics(SM_CYSCREEN) - iHeight) / 2,
			iWidth, iHeight, TRUE);
	}

	// �϶��ļ�
	inline static VOID WINAPI OnDropFiles(WPARAM wParam)
	{
		TCHAR tzFileName[MAX_PATH];
		DragQueryFile((HDROP) wParam, 0, tzFileName, MAX_PATH);
		DragFinish((HDROP) wParam);
		SetDlgItemText(m_hWnd, IDC_DllFile, tzFileName);
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
