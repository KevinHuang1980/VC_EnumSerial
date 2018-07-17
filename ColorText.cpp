// ColorText.cpp : implementation file
//

#include "stdafx.h"
#include "ColorText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorText

CColorText::CColorText()
{
	m_Color_Normal = GetSysColor(COLOR_WINDOWTEXT);
	m_Color_Active = m_Color_Normal;
	m_Color_In = COLOR_3DHILIGHT ;
	m_Color_Down = COLOR_3DHIGHLIGHT;
	TimerON = FALSE;
}

CColorText::~CColorText()
{

}


BEGIN_MESSAGE_MAP(CColorText, CButton)
	//{{AFX_MSG_MAP(CColorText)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorText message handlers
BOOL CColorText::EnableCheck()
{
	if (!TimerON)
	{
		TimerON = true;
		SetTimer(11,300,NULL);
	}
	return TRUE;
}

BOOL CColorText::ChangeFont(int nHeight, int nWidth, int nEscapement,
				int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
				BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
				BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
			LPCTSTR lpszFacename)
{
	return pFont.CreateFont(nHeight, nWidth, nEscapement,
		nOrientation, nWeight, bItalic, bUnderline,
		cStrikeOut, nCharSet, nOutPrecision,
		nClipPrecision, nQuality, nPitchAndFamily,
		lpszFacename);
}

void CColorText::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_Color_Active = m_Color_In;
	Invalidate(TRUE);
//	CButton::OnMouseMove(nFlags, point);
}

void CColorText::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_Color_Active = m_Color_Down;
	Invalidate(TRUE);

	//链接到网址
	//ShellExecute(NULL, NULL, "Iexplore", link, NULL, SW_NORMAL);
    ShellExecute(0, _T("open"), m_pText, NULL, NULL, SW_SHOWMAXIMIZED);  
//	CButton::OnLButtonDown(nFlags, point);
}

void CColorText::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_Color_Active = m_Color_Normal;
	Invalidate(TRUE);
//	CButton::OnLButtonUp(nFlags, point);
}

void CColorText::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	RECT rect;
	// TODO: Add your message handler code here
	CFont *pOldFont = NULL;
	// TODO: Add your message handler code here
	
	//获取窗口的文字
	int len = this->GetWindowTextLength() + 1;
	this->GetWindowText(m_pText.GetBufferSetLength(len),len);
	m_pText.ReleaseBuffer(len - 1);
	GetClientRect(&rect);
	dc.SetTextColor(m_Color_Active);
	dc.SetBkMode(m_IsTransparent?TRANSPARENT:OPAQUE);
	pOldFont = (CFont *)dc.SelectObject(&pFont);
	dc.DrawText(m_pText,&rect,DT_LEFT|DT_BOTTOM);
	
	dc.SelectObject(pOldFont);	
	// Do not call CButton::OnPaint() for painting messages
}

void CColorText::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	POINT pn;
	RECT rect;
	POINT pnLT;
	POINT pnRB;
	GetCursorPos(&pn);
	GetClientRect(&rect);
	pnLT.x = rect.left;
	pnLT.y = rect.top;
	pnRB.x = rect.right;
	pnRB.y = rect.bottom;
	ClientToScreen(&pnLT);
	ClientToScreen(&pnRB);

	if (pn.x < pnLT.x || pn.x > pnRB.x || pn.y < pnLT.y || pn.y > pnRB.y)
	{
		m_Color_Active = m_Color_Normal;
		Invalidate(TRUE);
	}

	CButton::OnTimer(nIDEvent);
}



void CColorText::OnDestroy() 
{
	CButton::OnDestroy();
	
	if (TimerON)
	{
		TimerON = FALSE;
		KillTimer(11);
	}	
}
