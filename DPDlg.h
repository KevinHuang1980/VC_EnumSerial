// DPDlg.h : header file
//
#include "ColorText.h"
#if !defined(AFX_DPDLG_H__C4DB322E_E1EB_4F26_92A5_6D26F1E0D5C0__INCLUDED_)
#define AFX_DPDLG_H__C4DB322E_E1EB_4F26_92A5_6D26F1E0D5C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDPDlg dialog

class CDPDlg : public CDialog
{
// Construction
	public:


			DCB dcb;
			BOOL m_OpenFlag;		// ���ڵ�����״̬��־
			HANDLE m_hCom;			// ���пھ��
			OVERLAPPED m_osRead;			// �����ص���
			OVERLAPPED m_osWrite;			// �����ص�д
			DWORD WriteSerial(BYTE * chBuf, DWORD dwLength);
			DWORD ReadSerial(BYTE* chBuf, DWORD dwLength);
			bool OpenComPort(CString comPortName);
			void ClosePort();
			bool SendData(CString data);
            DWORD getBufferLength();
			BOOL PreTranslateMessage(MSG *pMsg);
			HICON hIco; 
	CString createStr(BYTE command,BYTE channel,BYTE data);
public:
	CDPDlg(CWnd* pParent = NULL);	// standard constructor
	//�����¼��ĺ���


// Dialog Data
	//{{AFX_DATA(CDPDlg)

	enum { IDD = IDD_DP_DIALOG };
	CListBox	m_List;
	CSliderCtrl	m_SliderChannel4;
	CSliderCtrl	m_SliderChannel3;
	CSliderCtrl	m_SliderChannel2;
	CSliderCtrl	m_SliderChannel1;
	CScrollBar	m_ScrollBarChannel4;
	CScrollBar	m_ScrollBarChannel3;
	CScrollBar	m_ScrollBarChannel2;
	CScrollBar	m_TestValue;
	CComboBox	m_CboChannel;
	CComboBox	m_CboFunction;
	CComboBox	m_COMList;
	CScrollBar	m_ScrollBarChannel1;
	int		m_EditChannel1;
	int		m_EditTestValue;
	int		m_EditChannel2;
	int		m_EditChannel3;
	int		m_EditChannel4;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSend();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCustomdrawSliderChannel1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderChannel1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	afx_msg void OnButtonExit();
	afx_msg void OnSelchangeComboCom();
	afx_msg void OnButtonRefresh();
	afx_msg void OnReleasedcaptureSliderChannel2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderChannel3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderChannel4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton01();
	afx_msg void OnButton02();
	afx_msg void OnButton03();
	afx_msg void OnButton04();
	afx_msg void OnChangeEditValue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DPDLG_H__C4DB322E_E1EB_4F26_92A5_6D26F1E0D5C0__INCLUDED_)
