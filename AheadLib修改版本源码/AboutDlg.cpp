


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ԥ����
#include "Main.h"
#include "AboutDlg.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �궨��
#ifdef _CHS
#define FONT_NAME_AboutDlg		L"����"									// ��������
#else // _CHS
#define FONT_NAME_AboutDlg		L"MS Sans Serif"						// ��������
#endif // _CHS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AboutDlg �����ռ�
namespace AboutDlg
{
#ifdef _CHS
	const WORD WIDTH_AboutDlg = 399;									// �Ի�����
	const WORD HEIGHT_AboutDlg = 273;									// �Ի���߶�
	const WORD FONT_SIZE_AboutDlg = 9;									// �����С
#else // _CHS
	const WORD WIDTH_AboutDlg = 399;									// �Ի�����
	const WORD HEIGHT_AboutDlg = 258;									// �Ի���߶�
	const WORD FONT_SIZE_AboutDlg = 8;									// �����С
#endif // _CHS

#if defined(_CHS) && defined(_UNICODE)
	const UINT WIDTH_Text = 12;											// Ĭ��������
	const UINT HEIGHT_Text = 13;										// Ĭ������߶�
#else // defined(_CHS) && defined(_UNICODE)
	const UINT WIDTH_Text = 6;											// Ĭ��������
	const UINT HEIGHT_Text = 13;										// Ĭ������߶�
#endif // defined(_CHS) && defined(_UNICODE)

	const UINT IDT_Close = 1534;										// �ر�ʱ�ӱ�ʶ
	const COLORREF COLOR_Link = 0x00FF0000;								// ��������ɫ
	const COLORREF COLOR_HotLink = 0x000000FF;							// ����ȵ㳬������ɫ

	// �Ի���ģ��
	const struct DIALOGINFO
	{
		DLGTEMPLATE dtDialog;											// �Ի���
		WORD wNoMenu;													// û�жԻ���˵�
		WORD wNoClass;													// û�жԻ�������
		WORD wNoCaption;												// û�жԻ������
		WORD wFontSize;													// �Ի��������С
		WCHAR wszFontName[_NumberOf(FONT_NAME_AboutDlg)];				// �Ի�����������
		WORD wEndOfDialog;							// �Ի��������־
	}
	DI_Dialog =
	{
		{DS_SETFONT | DS_CENTER | WS_POPUP | WS_BORDER | WS_VISIBLE, 0, 0,
			0, 0, (WIDTH_AboutDlg * 2 / 3), (HEIGHT_AboutDlg * 2 / 3)},
			0, 0, 0, FONT_SIZE_AboutDlg, FONT_NAME_AboutDlg, 0
	};

	// ˮƽ����
	const struct LINEINFO
	{
		RECT rtRect;													// λ��
		COLORREF crColor;												// ��ɫ
	}
	LI_Lines[] =
	{
		{{0, 1, 88, 74}, 0x00FF9966},									// ������
		{{60, 116, WIDTH_AboutDlg, 132}, 0x00FF9966},					// ������
		{{60, 175, WIDTH_AboutDlg, 176}, 0x00000000},					// һ������
	};

	// ����
	const struct RECTINFO
	{
		RECT rtRect;													// λ��
		COLORREF crColor;												// ��ɫ
	}
	RI_Rects[] =
	{
		{{0, 75, WIDTH_AboutDlg, 111}, 0x00FF9966},						// ��ɫ����
		{{0, 111, WIDTH_AboutDlg, 115}, 0x00CC3333},					// ����ɫ����
		{{60, 47, 116, 103}, 0x00CC3333},								// ͼ���������ɫ����
		{{64, 51, 112, 99}, 0x00FFFFFF},								// ͼ������ɫ����
		{{68, 55, 86, 73}, RGB(0xEE, 0xEE, 0xEE + VER_Major % 16)},		// ͼ�걳������ɫ����
		{{90, 55, 108, 73}, RGB(0xEE, 0xEE, 0xEE + VER_Minor % 16)},	// ͼ�걳������ɫ����
		{{68, 79, 86, 95}, RGB(0xEE, 0xEE, 0xEE + VER_Release % 16)},	// ͼ�걳������ɫ����
		{{90, 79, 108, 95}, RGB(0xEE, 0xEE, 0xEE + VER_Build % 16)},	// ͼ�걳������ɫ����
	};

	// �ı�
	const struct TEXTINFO
	{
		INT x;															// X ����
		INT y;															// Y ����
		PCTSTR ptzText;													// �ַ���
		COLORREF crColor;												// ��ɫ
	}
	TI_Texts[] =
	{
		{60, 162, CAboutDlg::m_tzStatus, 0x00000000},					// ״̬��Ϣ
		{60, 140, STR_VersionStamp, 0x00BBBBBB},						// �汾��Ϣ
		{230, 140, STR_BuildStamp, 0x00BBBBBB},							// ������Ϣ
		{60, 240, STR_Description, 0x00000000},							// ������Ϣ
		{60, 255, STR_Copyright, 0x00000000},							// ��Ȩ��Ϣ
	};

	// ָ��������ַ���
	const struct FONTTEXTINFO
	{
		INT x;															// X ����
		INT y;															// Y ����
		PCTSTR ptzText;													// �ַ���
		COLORREF crColor;												// ��ɫ
		LOGFONT lfFont;													// ����
	}
	FTI_Texts[] =
	{
		{125, 40, STR_AppName, 0x00000000, {36, 0, 0, 0, 800, 1, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, 0, TEXT("Arial")}},
	};

	// ������
	const struct LINKINFO
	{
		RECT rtRect;													// λ��
		PCTSTR ptzTitle;												// ����
		PCTSTR ptzTip;													// ��ʾ�ַ���
		PCTSTR ptzUrl;													// ������Ŀ�� (HIWORD(ptzUrl) Ϊ 0 ��ʾ������Ϣ)
	}
	LI_Links[] =
	{
		{
			{60, 185, 60 + _LengthOf(STR_CheckUpdate) * WIDTH_Text, 185 + HEIGHT_Text},
				STR_CheckUpdate, STR_CheckUpdateTip, (PCTSTR) IDC_CheckUpdate
		},
		{
			{60, 200, 60 + _LengthOf(STR_VisitWeb) * WIDTH_Text, 200 + HEIGHT_Text},
				STR_VisitWeb, STR_VisitWebTip, STR_VisitWebUrl
		},
			{
				{60, 215, 60 + _LengthOf(STR_WriteEmail) * WIDTH_Text, 215 + HEIGHT_Text},
					STR_WriteEmail, STR_WriteEmailTip, STR_WriteEmailUrl
			},
	};

	// ͼ��λ��
	const RECT RT_Icon = RI_Rects[2].rtRect;

	// ״̬��Ϣλ��
	const RECT RT_Status = {TI_Texts[0].x, TI_Texts[0].y, WIDTH_AboutDlg, TI_Texts[0].y + HEIGHT_Text};
};
using namespace AboutDlg;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAboutDlg �ྲ̬��Ա����
HWND CAboutDlg::m_hWnd = NULL;
BOOL CAboutDlg::m_bSplash = FALSE;
INT CAboutDlg::m_iLinkIndex = -1;
TCHAR CAboutDlg::m_tzStatus[64] = {0};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʾ���ڶԻ���
VOID WINAPI CAboutDlg::Show(HWND hParent)
{
	if (m_hWnd == NULL)
	{
		DialogBoxIndirect(g_hInst, (LPDLGTEMPLATE) &DI_Dialog, hParent, AboutDlgProc);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �� Splash ��ʽ��ʾ���ڶԻ���
VOID WINAPI CAboutDlg::Splash(HWND hParent, UINT uTimer)
{
	if (m_hWnd == NULL)
	{
		// ������ģʽ�Ի���
		CreateDialogIndirect(g_hInst, (LPDLGTEMPLATE) &DI_Dialog, hParent, AboutDlgProc);

		// ���ָ�����Զ��ر�
		if (uTimer)
		{
			SetTimer(m_hWnd, IDT_Close, uTimer, NULL);
		}

		// ���õ�ǰ������ Splash ��ʽ��ʾ�ı��
		m_bSplash = TRUE;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �رմ��ڹ��ڶԻ���
VOID WINAPI CAboutDlg::Close(UINT uTimer)
{
	// ����������ر�
	if (uTimer)
	{
		SetTimer(m_hWnd, IDT_Close, uTimer, NULL);
	}
	else
	{
		// ɾ����ʱ��
		KillTimer(m_hWnd, IDT_Close);

		// �����ǰ������ Splash ��ʽ��ʾ
		if (m_bSplash)
		{
			DestroyWindow(m_hWnd);
			m_bSplash = FALSE;
		}
		else
		{
			EndDialog(m_hWnd, 0);
		}

		m_hWnd = NULL;
		m_tzStatus[0] = 0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����״̬��Ϣ
VOID WINAPI CAboutDlg::SetStatus(PCTSTR ptzText)
{
	HDC hDC;

	// ��ȡ״̬��Ϣ
	if (ptzText)
	{
		_StrToStr(m_tzStatus, ptzText);
	}
	else
	{
		m_tzStatus[0] = 0;
	}

	// ����״̬��Ϣ
	hDC = GetDC(m_hWnd);
	SetTextColor(hDC, TI_Texts[0].crColor);
	FillRect(hDC, &RT_Status, (HBRUSH) GetStockObject(WHITE_BRUSH));
	SelectObject(hDC, (HFONT) SendMessage(m_hWnd, WM_GETFONT, 0, 0));
	TextOut(hDC, TI_Texts[0].x, TI_Texts[0].y, TI_Texts[0].ptzText, lstrlen(TI_Texts[0].ptzText));
	ReleaseDC(m_hWnd, hDC);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ڶԻ���ص�����
INT_PTR CALLBACK CAboutDlg::AboutDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	INT i;
	HDC hDC;
	POINT ptPoint;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		// ��ʼ������
		m_hWnd = hWnd;
		m_iLinkIndex = NULL;

		// �������ָ��
		SetClassLong(m_hWnd, GCL_HCURSOR, 0);
		SetCursor(LoadCursor(NULL, IDC_ARROW));

		// ���öԻ�����
		if (GetParent(m_hWnd) == NULL)
		{
			SetWindowLong(m_hWnd, GWL_EXSTYLE, (GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW));
			SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		}
		break;

	case WM_CTLCOLORDLG:
	case WM_CTLCOLORSTATIC:
		return (INT_PTR) GetStockObject(WHITE_BRUSH);

	case WM_PAINT:
		OnPaint();
		break;

	case WM_ACTIVATEAPP:
		// �������
		GetCursorPos(&ptPoint);
		MapWindowPoints(NULL, m_hWnd, &ptPoint, 1);
		SendMessage(m_hWnd, WM_MOUSEMOVE, 0, MAKELONG(ptPoint.x, ptPoint.y));
		break;

	case WM_MOUSEMOVE:
		// ����������λ�õĳ����Ӹı�
		ptPoint.x = LOWORD(lParam);
		ptPoint.y = HIWORD(lParam);
		i = GetLinkIndex(ptPoint);
		if (i != m_iLinkIndex)
		{
			m_iLinkIndex = i;
			hDC = GetDC(m_hWnd);
			PaintLinks(hDC);
			ReleaseDC(m_hWnd, hDC);
		}
		break;

	case WM_LBUTTONDOWN:
		// �����ͼ����ڣ��϶��Ի���
		ptPoint.x = LOWORD(lParam);
		ptPoint.y = HIWORD(lParam);
		if (PtInRect(&RT_Icon, ptPoint))
		{
			ReleaseCapture();
			PostMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}
		break;

	case WM_ENTERSIZEMOVE:
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		break;

	case WM_EXITSIZEMOVE:
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		break;

	case WM_LBUTTONUP:
		// �������ڳ�������
		if (m_iLinkIndex != -1)
		{
			// ��� HIWORD(ptzUrl) Ϊ 0����ʾ��������ʾ������
			if (HIWORD(LI_Links[m_iLinkIndex].ptzUrl))
			{
				ShellExecute(NULL, NULL, LI_Links[m_iLinkIndex].ptzUrl, NULL, NULL, SW_NORMAL);
			}
			else
			{
				PostMessage(m_hWnd, WM_COMMAND, (WPARAM) LI_Links[m_iLinkIndex].ptzUrl, 0);
			}
		}
		else
		{
			// �رնԻ���
			Close();
		}
		break;

	case WM_COMMAND:
		// ����������Ϣ
		switch (LOWORD(wParam))
		{
		case IDC_CheckUpdate:
			// ������
			MessageBox(hWnd, TEXT("�ٺ٣���������������δʵ�֡���"), STR_AppName, MB_ICONINFORMATION);
			break;

		case IDOK:
		case IDCANCEL:
			// �رնԻ���
			Close();
			break;
		}
		break;

	case WM_TIMER:
	case WM_RBUTTONUP:
		// �رնԻ���
		Close();
		break;
	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ƶԻ���
VOID WINAPI CAboutDlg::OnPaint()
{
	INT i;
	INT j;
	HDC hDC;
	HPEN hPen;
	HBRUSH hBrush;
	POINT ptPoint;
	PAINTSTRUCT psPaint;

	// ��ʼ����
	hDC = BeginPaint(m_hWnd, &psPaint);

	// ����ˮƽ����
	for (i = 0; i < _NumberOf(LI_Lines); i++)
	{
		hPen = (HPEN) SelectObject(hDC, CreatePen(PS_SOLID, 0, LI_Lines[i].crColor));
		for(j = LI_Lines[i].rtRect.top; j < LI_Lines[i].rtRect.bottom; j += 2)
		{
			MoveToEx(hDC, LI_Lines[i].rtRect.left, j, NULL);
			LineTo(hDC, LI_Lines[i].rtRect.right, j);
		}
		DeleteObject(SelectObject(hDC, hPen));
	}

	// ���ƾ�������
	for (i = 0; i < _NumberOf(RI_Rects); i++)
	{
		hBrush = CreateSolidBrush(RI_Rects[i].crColor);
		FillRect(hDC, &RI_Rects[i].rtRect, hBrush);
		DeleteObject(hBrush);
	}

	// ����ͼ��
	DrawIcon(hDC,
		RT_Icon.left + (_RectWidth(RT_Icon) - 32) / 2,
		RT_Icon.top + (_RectHeight(RT_Icon) - 32) / 2,
		LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_Main)));

	// ���Ƴ�����
	GetCursorPos(&ptPoint);
	MapWindowPoints(NULL, m_hWnd, &ptPoint, 1);
	m_iLinkIndex = GetLinkIndex(ptPoint);
	PaintLinks(hDC);

	// ʹ�öԻ���Ĭ�����塢͸�����������ı�
	SetBkMode(hDC, TRANSPARENT);
	SelectObject(hDC, (HFONT) SendMessage(m_hWnd, WM_GETFONT, 0, 0));
	for (i = 0; i < _NumberOf(TI_Texts); i++)
	{
		SetTextColor(hDC, TI_Texts[i].crColor);
		TextOut(hDC, TI_Texts[i].x, TI_Texts[i].y, TI_Texts[i].ptzText, lstrlen(TI_Texts[i].ptzText));
	}

	// ����ָ��������ı�
	for (i = 0; i < _NumberOf(FTI_Texts); i++)
	{
		HFONT hFont = (HFONT) SelectObject(hDC, CreateFontIndirect(&FTI_Texts[i].lfFont));
		SetTextColor(hDC, FTI_Texts[i].crColor);
		TextOut(hDC, FTI_Texts[i].x, FTI_Texts[i].y, FTI_Texts[i].ptzText, lstrlen(FTI_Texts[i].ptzText));
		DeleteObject(SelectObject(hDC, hFont));
	}

	// ��������
	EndPaint(m_hWnd, &psPaint);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ȡָ����ĳ�����
INT WINAPI CAboutDlg::GetLinkIndex(POINT ptPoint)
{
	for (INT i = 0; i < _NumberOf(LI_Links); i++)
	{
		if (PtInRect(&LI_Links[i].rtRect, ptPoint))
		{
			return i;
		}
	}
	return -1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���Ƴ�����
VOID WINAPI CAboutDlg::PaintLinks(HDC hDC)
{
	HFONT hFont;
	LOGFONT lfFont;

	GetObject((HFONT) SendMessage(m_hWnd, WM_GETFONT, 0, 0), sizeof(LOGFONT), &lfFont);
	for (INT i = 0; i < _NumberOf(LI_Links); i++)
	{
		lfFont.lfUnderline = (i == m_iLinkIndex);
		hFont = (HFONT) SelectObject(hDC, CreateFontIndirect(&lfFont));
		SetTextColor(hDC, lfFont.lfUnderline ? COLOR_HotLink : COLOR_Link);
		TextOut(hDC, LI_Links[i].rtRect.left, LI_Links[i].rtRect.top,
			LI_Links[i].ptzTitle, lstrlen(LI_Links[i].ptzTitle));
		DeleteObject(SelectObject(hDC, hFont));
	}
	SetCursor(LoadCursor(NULL, ((m_iLinkIndex != -1) && _WinVerAboveEqual(4, 1)) ? IDC_HAND : IDC_ARROW));
	SetStatus((m_iLinkIndex == -1) ? NULL : LI_Links[m_iLinkIndex].ptzTip);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
