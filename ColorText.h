#if !defined(AFX_COLORTEXT_H__82EDE32E_4B2E_487B_A880_78B87C5C7502__INCLUDED_)
#define AFX_COLORTEXT_H__82EDE32E_4B2E_487B_A880_78B87C5C7502__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorText window

class CColorText : public CButton
{
// Construction
public:
	CColorText();

	COLORREF m_Color_In;
	COLORREF m_Color_Down;
	COLORREF m_Color_Normal;
	COLORREF m_Color_Active;
	BOOL m_IsTransparent;
	CString m_pText;
	
	BOOL EnableCheck();
	BOOL ChangeFont(int nHeight, int nWidth, int nEscapement,
		int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
		BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
		BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
			LPCTSTR lpszFacename);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorText)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorText();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorText)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	
	BOOL TimerON;
	CFont pFont;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORTEXT_H__82EDE32E_4B2E_487B_A880_78B87C5C7502__INCLUDED_)
