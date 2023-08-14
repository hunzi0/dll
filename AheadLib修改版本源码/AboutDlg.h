


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ԥ����
#pragma once
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAboutDlg ��
class CAboutDlg
{
public:
	static TCHAR m_tzStatus[64];	// ״̬��Ϣ�ַ���

private:
	static HWND m_hWnd;				// ���ھ��
	static BOOL m_bSplash;			// �Ƿ��� Splash ��ʽ��ʾ
	static INT m_iLinkIndex;		// ��ǰ������

public:
	// ��ʾ���ڶԻ���
	static VOID WINAPI Show(HWND hParent = NULL);

	// �� Splash ��ʽ��ʾ���ڶԻ���
	static VOID WINAPI Splash(HWND hParent = NULL, UINT uTimer = 1000);

	// �رմ��ڹ��ڶԻ���
	static VOID WINAPI Close(UINT uTimer = 0);

	// ����״̬��Ϣ
	static VOID WINAPI SetStatus(PCTSTR ptzText = NULL);

private:
	// ���ڶԻ���ص�����
	static INT_PTR CALLBACK AboutDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// ���ƶԻ���
	static VOID WINAPI OnPaint();

	// ��ȡָ����ĳ�����
	static INT WINAPI GetLinkIndex(POINT ptPoint);

	// ���Ƴ�����
	static VOID WINAPI PaintLinks(HDC hDC);
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
