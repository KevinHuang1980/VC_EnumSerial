// DPDlg.cpp : implementation file
//
/*2 命令字 ＝ 1，2，3，4
1： 打开对应通道电源
2： 关闭对应通道电源
3： 设置对应通道电源参数
4： 读出对应通道电源参数
当命令字为1，2，3 时，如果控制器接收命令成功，则返回特征字$；如
果控制器接收命令失败，则返回&。
当命令字为4 时，如果控制器接收命令成功，则返回对应通道的电源设置
参数（返回格式跟发送格式相同）；如果控制器接收命令失败，则返回&。*/

#include "stdafx.h"
#include "DP.h"
#include "DPDlg.h"

//--
#include "EnumSerial.h"
#include "ColorText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	CColorText m_link;
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();

	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()

};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BUTTON_Link, m_link);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDPDlg dialog

CDPDlg::CDPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDPDlg)
	m_EditChannel1 = 0;
	m_EditTestValue = 0;
	m_EditChannel2 = 0;
	m_EditChannel3 = 0;
	m_EditChannel4 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDPDlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_SLIDER_CHANNEL4, m_SliderChannel4);
	DDX_Control(pDX, IDC_SLIDER_CHANNEL3, m_SliderChannel3);
	DDX_Control(pDX, IDC_SLIDER_CHANNEL2, m_SliderChannel2);
	DDX_Control(pDX, IDC_SLIDER_CHANNEL1, m_SliderChannel1);
	DDX_Control(pDX, IDC_SCROLLBAR_CHANNEL4, m_ScrollBarChannel4);
	DDX_Control(pDX, IDC_SCROLLBAR_CHANNEL3, m_ScrollBarChannel3);
	DDX_Control(pDX, IDC_SCROLLBAR_CHANNEL2, m_ScrollBarChannel2);
	DDX_Control(pDX, IDC_SCROLLBAR_TEST_VALUE, m_TestValue);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_CboChannel);
	DDX_Control(pDX, IDC_COMBO_FUNCTION, m_CboFunction);
	DDX_Control(pDX, IDC_COMBO_COM, m_COMList);
	DDX_Control(pDX, IDC_SCROLLBAR_CHANNEL1, m_ScrollBarChannel1);
	DDX_Text(pDX, IDC_EDIT_CHANNEL1, m_EditChannel1);
	DDV_MinMaxInt(pDX, m_EditChannel1, 0, 255);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_EditTestValue);
	DDV_MinMaxInt(pDX, m_EditTestValue, 0, 255);
	DDX_Text(pDX, IDC_EDIT_CHANNEL2, m_EditChannel2);
	DDV_MinMaxInt(pDX, m_EditChannel2, 0, 255);
	DDX_Text(pDX, IDC_EDIT_CHANNEL3, m_EditChannel3);
	DDV_MinMaxInt(pDX, m_EditChannel3, 0, 255);
	DDX_Text(pDX, IDC_EDIT_CHANNEL4, m_EditChannel4);
	DDV_MinMaxInt(pDX, m_EditChannel4, 0, 255);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDPDlg, CDialog)
	//{{AFX_MSG_MAP(CDPDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_WM_VSCROLL()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CHANNEL1, OnCustomdrawSliderChannel1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CHANNEL1, OnReleasedcaptureSliderChannel1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_CBN_SELCHANGE(IDC_COMBO_COM, OnSelchangeComboCom)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CHANNEL2, OnReleasedcaptureSliderChannel2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CHANNEL3, OnReleasedcaptureSliderChannel3)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CHANNEL4, OnReleasedcaptureSliderChannel4)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON01, OnButton01)
	ON_BN_CLICKED(IDC_BUTTON02, OnButton02)
	ON_BN_CLICKED(IDC_BUTTON03, OnButton03)
	ON_BN_CLICKED(IDC_BUTTON04, OnButton04)
	ON_BN_CLICKED(IDC_BUTTON01, OnButton01)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDPDlg message handlers
CString strTitle;
CString strProductName;
int flag1=0,flag2=0,flag3=0,flag4=0;//按钮的标志位
CString strUrl;
//CBitmapButton m_btn;//位图按钮显示
BOOL CDPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON01))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));//初始化按键位图
	((CButton*)GetDlgItem(IDC_BUTTON02))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));//初始化按键位图
	((CButton*)GetDlgItem(IDC_BUTTON03))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));//初始化按键位图
	((CButton*)GetDlgItem(IDC_BUTTON04))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));//初始化按键位图
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon



	//read configs
	//获取当前路径
	CString szCurPath("");
	GetModuleFileName(NULL,szCurPath.GetBuffer(MAX_PATH),MAX_PATH);	
	szCurPath.ReleaseBuffer();
	szCurPath=	 szCurPath.Left(szCurPath.ReverseFind('\\') + 1);
	//path 
	CString   strFileName=szCurPath+"Config.ini"; 
	
	//save
	
    GetPrivateProfileString("ConfigInfo","ProductName",""/*这里是默认的*/,strProductName.GetBuffer(MAX_PATH),MAX_PATH,strFileName); 
	if(strProductName=="")//如果这个文件不存在就创建一个
	{
		//create file
		::WritePrivateProfileString("ConfigInfo","Title","Digital controller A series PC software",strFileName);
		::WritePrivateProfileString("ConfigInfo","ProductName","Digital controller A series PC software V1.1",strFileName); 
		//::WritePrivateProfileString("ConfigInfo","Tel","0755-(null)",strFileName); 
	//	::WritePrivateProfileString("ConfigInfo","Url","Http://www.Ti-times.com",strFileName); 
	}
	GetPrivateProfileString("ConfigInfo","Title","Digital controller A series PC software V1.1",strTitle.GetBuffer(MAX_PATH),MAX_PATH,strFileName); 
	GetPrivateProfileString("ConfigInfo","ProductName","ProductName"/*这里是默认的*/,strProductName.GetBuffer(MAX_PATH),MAX_PATH,strFileName); 
//	GetPrivateProfileString("ConfigInfo","Url","Http://www.Ti-times.com",strUrl.GetBuffer(MAX_PATH),MAX_PATH,strFileName); 
//	GetPrivateProfileString("ConfigInfo","Tel","0755-(null)",str/Tel.GetBuffer(MAX_PATH),MAX_PATH,strFileName); 
	
	this->SetWindowText(strTitle);
	//------
	
	//------
		//set m_ComboType to drop show
	 CRect rc; 
     m_COMList.GetWindowRect(&rc);
     ScreenToClient(&rc);
      m_COMList.MoveWindow(rc.left,rc.top,rc.Width(),rc.Height()*6);

	  this->m_CboFunction.GetWindowRect(&rc);
	  ScreenToClient(&rc);
      m_CboFunction.MoveWindow(rc.left,rc.top,rc.Width(),rc.Height()*6);
	  m_CboFunction.SetCurSel(0);
	  this->m_CboChannel.GetWindowRect(&rc);
	  ScreenToClient(&rc);
      m_CboChannel.MoveWindow(rc.left,rc.top,rc.Width(),rc.Height()*6);
	  m_CboChannel.SetCurSel(0);
	// TODO: Add extra initialization here
	/*this->m_ChannelImage1.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
	this->m_ChannelImage2.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
	this->m_ChannelImage3.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));*/
	//---------------

	CArray<SSerInfo,SSerInfo&> asi;

	// Populate the list of serial ports.
	EnumSerialPorts(asi,FALSE/*include all*/);
	m_COMList.ResetContent();
	for (int i=0; i<asi.GetSize(); i++) {

		///	
		CString fullPortName = asi[i].strFriendlyName;
			int startdex = fullPortName.Find(" (");
			int enddex = fullPortName.Find(")");
			if (startdex > 0 && enddex ==(fullPortName.GetLength()-1))
			{fullPortName = fullPortName.Right(enddex-startdex-1);
			fullPortName=fullPortName.Left(fullPortName.GetLength()-1);
			}
		m_COMList.AddString(fullPortName);
	}
	this->m_COMList.SetCurSel(0);
	m_OpenFlag=false;
	OnSelchangeComboCom() ;
	//---init slider
	this->m_SliderChannel1.SetRange(0,255,false);
	this->m_SliderChannel2.SetRange(0,255,false);
	this->m_SliderChannel3.SetRange(0,255,false);
	this->m_SliderChannel4.SetRange(0,255,false);
	//---    
	CheckDlgButton(IDC_RADIO_C1_ON,BST_CHECKED);
CheckDlgButton(IDC_RADIO_C1_ON2,BST_CHECKED);
CheckDlgButton(IDC_RADIO_C1_ON3,BST_CHECKED);
CheckDlgButton(IDC_RADIO_C1_ON4,BST_CHECKED);
	this->m_SliderChannel1.SetPos(255-this->m_EditChannel1);
		this->m_SliderChannel2.SetPos(255-this->m_EditChannel2);
			this->m_SliderChannel3.SetPos(255-this->m_EditChannel3);
				this->m_SliderChannel4.SetPos(255-this->m_EditChannel4);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDPDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDPDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDPDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	
	/*turn ON
	turn OFF
	intensity write
	intensity read*/
	BYTE command,channel,data;
	
	CString strGetText;
	m_CboFunction.GetWindowText(strGetText);	
	if(strGetText=="turn ON")
	{
		command=1;
	}else if(strGetText=="turn OFF")
	{
		command=2;
	}else if(strGetText=="intensity write")
	{command=3;}
	else
	{command=4;
	}
	this->m_CboChannel.GetWindowText(strGetText);
	channel=atoi(strGetText);
   //  UpdateData(false);
	 GetDlgItemText(IDC_EDIT_VALUE,strGetText);

	data=atoi(strGetText);
	//	SetDlgItemText(IDC_STATIC_STATE,this->createStr(command,channel,data));
	if(this->m_OpenFlag)
	{
		if(this->SendData(createStr(command,channel,data)))
		{
			if(command==1)
			{
				if(channel==1)
				{
					
				((CButton*)GetDlgItem(IDC_BUTTON01))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
			
					flag1=1;
					
				}else if(channel==2)
				{
				((CButton*)GetDlgItem(IDC_BUTTON02))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
				
					flag2=1;	
				}else if(channel==3)
				{
						((CButton*)GetDlgItem(IDC_BUTTON03))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
			
					flag3=1;
				}else if(channel==4)
				{
						((CButton*)GetDlgItem(IDC_BUTTON04))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
			
					flag4=1;
				}
			}
			else if(command==2)
			{	
				if(channel==1)
				{
					
					((CButton*)GetDlgItem(IDC_BUTTON01))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
				
					flag1=0;
					
				}else if(channel==2)
				{	
					((CButton*)GetDlgItem(IDC_BUTTON02))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
				
					flag2=0;
				
				}else if(channel==3)
				{
				((CButton*)GetDlgItem(IDC_BUTTON03))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
				
					flag3=0;
				}else if(channel==4)
				{
					((CButton*)GetDlgItem(IDC_BUTTON04))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
			
					flag4=0;
				}
			}
			else if(command==3)
			{
				UpdateData(true);
				if(channel==1)
				{				
					this->m_EditChannel1=data;
					this->m_SliderChannel1.SetPos(255-data);
					
				}else if(channel==2)
				{	this->m_EditChannel2=data;
				this->m_SliderChannel2.SetPos(255-data);
				
				}else if(channel==3)
				{
					this->m_EditChannel3=data;
					this->m_SliderChannel3.SetPos(255-data);
				}else if(channel==4)
				{
					this->m_EditChannel4=data;
					this->m_SliderChannel4.SetPos(255-data);
				}
				UpdateData(false);
			}
			else if(command==4)
			{
				if(channel==1)
					{				
						SetDlgItemText(IDC_EDIT_VALUE,strGetText);
						
					}else if(channel==2)
					{
						
					SetDlgItemText(IDC_EDIT_VALUE,strGetText);
					}
					else if(channel==3)
					{
						
					SetDlgItemText(IDC_EDIT_VALUE,strGetText);
					}
					else if(channel==4)
					{
						SetDlgItemText(IDC_EDIT_VALUE,strGetText);
					}
			}
			
			
		}else{MessageBox("Set falied!");}
	}
}


CString CDPDlg::createStr(BYTE command,BYTE channle,BYTE data)
{
	char *conHex =new char[3];

	CString returnStr="$",temp; //将第1通道亮度设为50，则以ASCII码向下写“$3103217”
	
	temp.Format("%d",command);
	returnStr+=temp;
	temp.Format("%d",channle);
	returnStr+=temp;
	if(data>15)
	{
		sprintf(conHex, "0%X", data);
	}else
	{
		sprintf(conHex, "00%X", data);
	}
	returnStr=returnStr+conHex;
	//把所有的字符异或运算
	int i;
	BYTE xorData=returnStr[0];
	for(i=1;i<returnStr.GetLength();i++)
	{
	xorData=xorData^returnStr[i];
	}
	sprintf(conHex, "%X", xorData);
	returnStr=returnStr+conHex;
	return returnStr;
}

BOOL CDPDlg::PreTranslateMessage(MSG *pMsg)
{//(pMsg->message==WM_CHAR)||
	
/*	if(pMsg->message==WM_KEYDWON)
	{
		MessageBox("Mouse down");
	}*/
	if(pMsg->message==WM_MOUSEWHEEL)
	{
		if(this->GetFocus()->m_hWnd==GetDlgItem(IDC_SLIDER_CHANNEL1)->m_hWnd)
		{
			this->m_EditChannel1=255-this->m_SliderChannel1.GetPos();
			UpdateData(false);

			this->SendData(this->createStr(3,1,this->m_EditChannel1));
			
		}else if(this->GetFocus()->m_hWnd==GetDlgItem(IDC_SLIDER_CHANNEL2)->m_hWnd)
		{
			this->m_EditChannel2=255-this->m_SliderChannel2.GetPos();
			UpdateData(false);
			this->SendData(this->createStr(3,2,this->m_EditChannel2));
			
		}else if(this->GetFocus()->m_hWnd==GetDlgItem(IDC_SLIDER_CHANNEL3)->m_hWnd)
		{	
			this->m_EditChannel3=255-this->m_SliderChannel3.GetPos();
			UpdateData(false);
			this->SendData(this->createStr(3,3,this->m_EditChannel3));

		}else if(this->GetFocus()->m_hWnd==GetDlgItem(IDC_SLIDER_CHANNEL4)->m_hWnd)
		{	
			this->m_EditChannel4=255-this->m_SliderChannel4.GetPos();
			UpdateData(false);
			this->SendData(this->createStr(3,4,this->m_EditChannel4));
		}
	}
	return false;
}

void CDPDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	   CString strGetValue;
	   if(nSBCode==8){	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);return;}
		    if(pScrollBar==&this->m_ScrollBarChannel1)
              {
			      GetDlgItemText(IDC_EDIT_CHANNEL1,strGetValue);
				  if(this->m_EditChannel1!=atoi(strGetValue))
				  {m_EditChannel1=atoi(strGetValue);
				  	if(m_EditChannel1>255)
					  {
						  m_EditChannel1=255;
					  }else if(m_EditChannel1<0)
					  {
						  m_EditChannel1=0;
					  }
				  }
				  if( SB_LINEDOWN==nSBCode)
				  {    if(m_EditChannel1>0)
					  this->m_EditChannel1--;
				  }else if(nSBCode==SB_LINEUP)
				  {  if(m_EditChannel1<255)
					  this->m_EditChannel1++;
				  }  
				  //slider				
				  this->m_SliderChannel1.SetPos(255-m_EditChannel1);
				  //send data
				  this->SendData(this->createStr(3,1,m_EditChannel1));
			}else if(pScrollBar==&this->m_ScrollBarChannel2)
			{	  GetDlgItemText(IDC_EDIT_CHANNEL2,strGetValue);
				  if(this->m_EditChannel1!=atoi(strGetValue))
				  {m_EditChannel2=atoi(strGetValue);
				  	  	if(m_EditChannel2>255)
					  {
						  m_EditChannel2=255;
					  }else if(m_EditChannel2<0)
					  {
						  m_EditChannel2=0;
					  }
				  }
				  if( SB_LINEDOWN==nSBCode)
				  {    if(m_EditChannel2>0)
					  this->m_EditChannel2--;
				  }else if(nSBCode==SB_LINEUP)
				  {  if(m_EditChannel2<255)
					  this->m_EditChannel2++;
				  }  
				   //slider				
				  this->m_SliderChannel2.SetPos(255-m_EditChannel2);
				  //send data
				  this->SendData(this->createStr(3,2,m_EditChannel2));
			}
			else if(pScrollBar==&this->m_ScrollBarChannel3)
			{	  GetDlgItemText(IDC_EDIT_CHANNEL3,strGetValue);
				  if(this->m_EditChannel3!=atoi(strGetValue))
				  {m_EditChannel3=atoi(strGetValue);
				  	  	if(m_EditChannel3>255)
					  {
						  m_EditChannel3=255;
					  }else if(m_EditChannel3<0)
					  {
						  m_EditChannel3=0;
					  }
				  }
				  if( SB_LINEDOWN==nSBCode)
				  {    if(m_EditChannel3>0)
					  this->m_EditChannel3--;
				  }else if(nSBCode==SB_LINEUP)
				  {  if(m_EditChannel3<255)
					  this->m_EditChannel3++;
				  }    
				  //slider				
				  this->m_SliderChannel3.SetPos(255-m_EditChannel3);
				  //send data
				  this->SendData(this->createStr(3,3,m_EditChannel3));
			}
			else if(pScrollBar==&this->m_ScrollBarChannel4)
			{	  		      GetDlgItemText(IDC_EDIT_CHANNEL4,strGetValue);
				  if(this->m_EditChannel4!=atoi(strGetValue))
				  {m_EditChannel4=atoi(strGetValue);
				  	if(m_EditChannel4>255)
					  {
						  m_EditChannel4=255;
					  }else if(m_EditChannel4<0)
					  {
						  m_EditChannel4=0;
					  }
				  }
				  if( SB_LINEDOWN==nSBCode)
				  {    if(m_EditChannel4>0)
					  this->m_EditChannel4--;
				  }else if(nSBCode==SB_LINEUP)
				  {  if(m_EditChannel4<255)
					  this->m_EditChannel4++;
				  }  
				  //slider				
				  this->m_SliderChannel4.SetPos(255-m_EditChannel4);
				  //send data
				  this->SendData(this->createStr(3,4,m_EditChannel4));
			}
			else if(pScrollBar==&this->m_TestValue)
			  {                 
				  GetDlgItemText(IDC_EDIT_VALUE,strGetValue);
				  if(m_EditTestValue!=atoi(strGetValue))
				  {m_EditTestValue=atoi(strGetValue);
					  if(m_EditTestValue>255)
					  {
						  m_EditTestValue=255;
					  }else if(m_EditTestValue<0)
					  {
						  m_EditTestValue=0;
					  }
				  }
				  if( SB_LINEDOWN==nSBCode)
				  {    if(m_EditTestValue>0)
					  this->m_EditTestValue--;
				  }else if(nSBCode==SB_LINEUP)
				  {  if(m_EditTestValue<255)
					  this->m_EditTestValue++;
				  }
				 
			  }
 UpdateData(false);
       
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}



void CDPDlg::OnCustomdrawSliderChannel1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
   /*CString str;
	str.Format("%d %d  %d %d",pNMHDR->code,pNMHDR->hwndFrom,pNMHDR->idFrom,pResult);

	SetDlgItemText(IDC_STATIC_STATE,str);*/
	*pResult = 0;
}



void CDPDlg::OnReleasedcaptureSliderChannel1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
 			UpdateData(true);
	this->m_EditChannel1=255-this->m_SliderChannel1.GetPos();
	UpdateData(false);
		this->SendData(this->createStr(3,1,this->m_EditChannel1));
	*pResult = 0;
}

void CDPDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(MessageBox("are you sure to exit?","Information",MB_YESNO|MB_ICONINFORMATION)==IDYES)
	CDialog::OnClose();
}

void CDPDlg::OnButtonExit() 
{		

	if(MessageBox("are you sure to exit?","Information",MB_YESNO|MB_ICONINFORMATION)==IDYES)
	exit(1);	
}
bool CDPDlg::OpenComPort(CString comPortName)
{

	char* fullportname = new char[10];
    //  sprintf(fullportname,"\\\\.\\%s",portName);
//	sprintf(portName, "COM%d", comX);
//	MessageBox(NULL,portName,"",MB_OK);
	comPortName="\\\\.\\"+comPortName;
			m_hCom = CreateFile(comPortName,
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL );
			if(m_hCom == INVALID_HANDLE_VALUE)
			{
				return false;
			}

		GetCommState(m_hCom,&dcb);
		dcb.BaudRate=9600; //波特率为9600
		dcb.StopBits=0; //一个停止位为0，两个是1
		dcb.ByteSize=8; //每个字节有8位
		dcb.Parity=NOPARITY; //无奇偶校验位
		
		SetCommState(m_hCom,&dcb);


	return true;

}
void CDPDlg::ClosePort()
{
	if(this->m_OpenFlag)
	{
		//SetCommMask(m_hCom, 0);
		if(m_hCom!=NULL)
		CloseHandle(m_hCom);
		m_OpenFlag = false;
	}
}

//readdata for buf
DWORD CDPDlg::getBufferLength()
{
	memset(&m_osRead,0,sizeof(OVERLAPPED));
	COMSTAT comStat;
	DWORD dwErrorFlags;
	ClearCommError(m_hCom, &dwErrorFlags, &comStat);
	return comStat.cbInQue;
}
DWORD CDPDlg::ReadSerial(BYTE *chBuf, DWORD dwLength)
{
	//	memset(&m_osRead,0,sizeof(OVERLAPPED));
	DWORD nLen;
	COMSTAT comStat;
	DWORD dwErrorFlags;
	ClearCommError(m_hCom, &dwErrorFlags, &comStat);
	nLen = min(dwLength, comStat.cbInQue);
	ReadFile(m_hCom, chBuf, nLen, &nLen, &m_osRead);
	return nLen;
}
//write data 
DWORD CDPDlg::WriteSerial(BYTE *chBuf, DWORD dwLength)
{
	memset(&m_osWrite,0,sizeof(OVERLAPPED));
	BOOL bState;
	COMSTAT comStat;
	DWORD dwErrorFlags;	
	ClearCommError(m_hCom, &dwErrorFlags, &comStat);	
	bState = WriteFile(m_hCom, chBuf, dwLength, &dwLength, &m_osWrite);
	if(!bState)
	{
		if(GetLastError() == ERROR_IO_PENDING)
		{
			GetOverlappedResult(m_hCom, &m_osWrite, &dwLength, TRUE);// 等待
		}
		else
		{
			dwLength = 0;
		}
	}
	return dwLength;
}
BYTE conHexStrToByte(char str)
{
	if(str>='0' &&str<='9')
	{
		return str-48;
	}else if(str=='a'||str=='A')
	{
		return 10;
	}else if(str=='b'||str=='B')
	{
		return 11;
	}else if(str=='c'||str=='C')
	{
			return 12;
	}else if(str=='d'||str=='D')
	{
		return 13;
	}else if(str=='e'||str=='E')
	{
		return 14;
	}else if(str=='f'||str=='F')
	{
		return 15;
	}
	return 0;
}
bool CDPDlg::SendData(CString data)
{
	//初始化缓冲区中的信息
  PurgeComm(this->m_hCom, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	BYTE *buf=new BYTE[8];
	BYTE reciveBuf[20];
	DWORD readLen=0;
	memset(buf,0,8*sizeof(BYTE));
	buf=(BYTE*)(data.GetBuffer(data.GetLength()));
	if(WriteSerial(buf,8)>0)
	{
        
	}else {
		SetDlgItemText(IDC_EDIT_COMSTATE,"failed");
		return false;
	}
	Sleep(50);
	int c=0;
	for( c=0;c<10;c++)
	{    int getReciveLength,readBufferLength;
		
	getReciveLength=getBufferLength();
		if(getReciveLength>0)		
		{  
			CString strShow;
			strShow.Format("length=%d",getReciveLength);
			this->m_List.AddString(strShow);
	    	readBufferLength=ReadSerial(reciveBuf,getBufferLength());
			if(readBufferLength==1)
			{
				if(reciveBuf[0]=='$')
				{
					SetDlgItemText(IDC_EDIT_COMSTATE,"Success");
					return true;	
				}else if(reciveBuf[0]=='&')
				{
					SetDlgItemText(IDC_EDIT_COMSTATE,"failed");
					return false;
				}else
				{
					SetDlgItemText(IDC_EDIT_COMSTATE,"failed.");
					return false;
				}
			}else
			{//读取
				int l=0;
				if(reciveBuf[1]=='$')//前移八个字节
				{
					for(l=0;l<8;l++)
					{
					reciveBuf[l]=reciveBuf[l+1];
					}
				}
				if(reciveBuf[2]=='$')//前移八个字节
				{
					for(int l=0;l<9;l++)
					{
					reciveBuf[l]=reciveBuf[l+1];
					}
				}
				if(reciveBuf[0]=='$')
				{
					CString strValue="00",strValueTemp;
					strValue.Format("%c%c",reciveBuf[4],reciveBuf[5]);
					BYTE decValue=(BYTE)(conHexStrToByte((char)strValue[0])*16+conHexStrToByte((char)strValue[1]));

					if(reciveBuf[2]=='1')
					{					
						    this->m_EditChannel1=decValue;	
							UpdateData(false);
							this->m_SliderChannel1.SetPos(255-decValue);
					}else if(buf[2]=='2')//第二通道
					{						
						this->m_EditChannel2=decValue;
						UpdateData(false);	
						GetDlgItemText(IDC_EDIT_CHANNEL2,strValueTemp);
							this->m_SliderChannel2.SetPos(255-atoi(strValueTemp));
					}else if(buf[2]=='3')//第三通道
					{
						this->m_SliderChannel3.SetPos(255-decValue);
						UpdateData(false);
						this->m_EditChannel3=decValue;						

					}else if(buf[2]=='4')//第四通道
					{		
						this->m_SliderChannel4.SetPos(255-decValue);
						UpdateData(false);
						this->m_EditChannel4=decValue;				
					
					}
					UpdateData(false);
				}else
				{
					SetDlgItemText(IDC_EDIT_COMSTATE,"Data format error");return false;
					
				}
			}

 break;
		}
		Sleep(15);
	}
	if(c>=10)
	{
		SetDlgItemText(IDC_EDIT_COMSTATE,"time out!set failed!");
		return false;
	}
	SetDlgItemText(IDC_EDIT_COMSTATE,"Success");

return true;

}

void CDPDlg::OnSelchangeComboCom() 
{
	// TODO: Add your control notification handler code here
	CString comPortName;

	m_COMList.GetWindowText(comPortName);
	
	if(this->m_OpenFlag)
	{
		this->ClosePort();
	}
	if(OpenComPort(comPortName))
	{
		this->m_OpenFlag=true;
		this->OnButtonRefresh();
	}else{
		MessageBox("Open " + comPortName + "falied!");
		m_OpenFlag=false;
	}
}

void CDPDlg::OnButtonRefresh() 
{

	for(int i=1;i<=4;i++)
	{
		this->SendData(this->createStr(4,i,0));
		Sleep(50);
	}
}

void CDPDlg::OnButton01()
{	
	flag1++;
	BYTE command;
	if(flag1%2==1)// 启动开关
	{
	((CButton*)GetDlgItem(IDC_BUTTON01))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
		command=1;
	}
	if(flag1%2==0)//关闭开关 
	{

	((CButton*)GetDlgItem(IDC_BUTTON01))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
		command=2;
	}
	if(flag1==2)
		flag1=0;
	this->SendData(this->createStr(command,1,this->m_EditChannel1));
}
void CDPDlg::OnButton02() //第二个通道开关
{
	flag2++;
	BYTE command;
	if(flag2%2==1)// 启动开关
	{
	((CButton*)GetDlgItem(IDC_BUTTON02))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
		command=1;
	}
	if(flag2%2==0)//关闭开关 
	{

	((CButton*)GetDlgItem(IDC_BUTTON02))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
		command=2;
		flag2=0;
	}
	
	this->SendData(this->createStr(command,2,this->m_EditChannel2));
	
}
void CDPDlg::OnButton03() 
{
	// TODO: Add your control notification handler code here
		flag3++;
	BYTE command;
	if(flag3%2==1)// 启动开关
	{
	((CButton*)GetDlgItem(IDC_BUTTON03))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
		command=1;
	}
	if(flag3%2==0)//关闭开关 
	{

	((CButton*)GetDlgItem(IDC_BUTTON03))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
		command=2;
		flag3=0;
	}	
	this->SendData(this->createStr(command,3,this->m_EditChannel3));	
}

void CDPDlg::OnButton04() 
{
	// TODO: Add your control notification handler code here
		flag4++;
	BYTE command;
	if(flag4%2==1)// 启动开关
	{
	((CButton*)GetDlgItem(IDC_BUTTON04))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
		command=1;
	}
	if(flag4%2==0)//关闭开关 
	{

	((CButton*)GetDlgItem(IDC_BUTTON04))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
		command=2;
		flag4=0;
	}
	this->SendData(this->createStr(command,4,this->m_EditChannel4));
	
}



void CDPDlg::OnReleasedcaptureSliderChannel2(NMHDR* pNMHDR, LRESULT* pResult) 
{

	UpdateData(true);
	this->m_EditChannel2=255-this->m_SliderChannel2.GetPos();
	UpdateData(false);
	this->SendData(this->createStr(3,2,this->m_EditChannel2));
	*pResult = 0;
}

void CDPDlg::OnReleasedcaptureSliderChannel3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	UpdateData(true);
	this->m_EditChannel3=255-this->m_SliderChannel3.GetPos();
	UpdateData(false);
	this->SendData(this->createStr(3,3,this->m_EditChannel3));
	*pResult = 0;
}

void CDPDlg::OnReleasedcaptureSliderChannel4(NMHDR* pNMHDR, LRESULT* pResult) 
{

	UpdateData(true);
	this->m_EditChannel4=255-this->m_SliderChannel4.GetPos();
	UpdateData(false);	
	this->SendData(this->createStr(3,4,this->m_EditChannel4));
	*pResult = 0;
}


void CDPDlg::OnButton1() 
{
	CString strShow;
			strShow.Format("length=%d",this->getBufferLength());
			this->m_List.AddString(strShow);
}

void CDPDlg::OnButton2() 
{BYTE bf[1024];
  int readRealLeng;
  readRealLeng= this->ReadSerial(bf,this->getBufferLength());	
  CString strShow;
			strShow.Format("read length=%d",readRealLeng);
			this->m_List.AddString(strShow);
}

void CDPDlg::OnButton3() 
{

  //return TRUE;

this->m_List.ResetContent();	
}

void CDPDlg::OnButton4() 
{
	//初始化缓冲区中的信息
  PurgeComm(this->m_hCom, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	

	SetDlgItemText(IDC_STATIC_ProductName,strProductName);
//	SetDlgItemText(IDC_BUTTON_Link,strUrl);
//	SetDlgItemText(IDC_STATIC_TelNO,strTel);

//	m_link.m_Color_Active = RGB(50,100,100);
//	m_link.m_Color_Down = RGB(100,100,255);
//	m_link.m_Color_In = RGB(255,100,100);
//	m_link.m_Color_Normal = RGB(50,50,100);
//	m_link.m_IsTransparent = TRUE;	
	/*这里设置字体*/
//	m_link.ChangeFont(10,6,0,0,230,FALSE,TRUE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
//	DEFAULT_QUALITY,DEFAULT_PITCH,"宋体");
//	m_link.EnableCheck();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



/*void CAboutDlg::OnSTATICLink() 
{
	//链接到网址
	//ShellExecute(NULL, NULL, "Iexplore", link, NULL, SW_NORMAL);
	CString strTxt;
GetDlgItemText(IDC_BUTTON_Link,strTxt);

    ShellExecute(0, _T("open"), strTxt, NULL, NULL, SW_SHOWMAXIMIZED);  	
}*/










