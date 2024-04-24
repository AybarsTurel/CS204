
// aturel_HW6Dlg.cpp : implementation file

/*************
Purpose: This code was writen to make bit operations with using GUI.
Usage: There are no external files that are used. 
Author: Sevki Aybars Turel 28238
Date: 21/12/2021
Any known bugs: There are any known bugs. However code has to be executed by numbers.
References: Opening windows, taking parameters, making horizantal scroll, and conversion of Cstring to unsigned int functions were taken from CS 204 lab materials

**************/

#include "stdafx.h"
#include "aturel_HW6.h"
#include "aturel_HW6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Caturel_HW6Dlg dialog



Caturel_HW6Dlg::Caturel_HW6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Caturel_HW6Dlg::IDD, pParent)
	, choiceAnd(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Caturel_HW6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, listOutput);
	DDX_Radio(pDX, IDC_RADIO1, choiceAnd);
	DDX_Control(pDX, IDC_EDIT1, operand1);
	DDX_Control(pDX, IDC_EDIT2, operand2);
	DDX_Control(pDX, IDC_CHECK1, choiceShift);
	DDX_Control(pDX, IDC_BUTTON1, computeButton);
	DDX_Control(pDX, IDC_COMBO1, leftOrRightChoice);
	DDX_Control(pDX, IDC_EDIT3, numOfShits);
}

BEGIN_MESSAGE_MAP(Caturel_HW6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &Caturel_HW6Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_CHECK1, &Caturel_HW6Dlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &Caturel_HW6Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Caturel_HW6Dlg message handlers

BOOL Caturel_HW6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// TODO: Add extra initialization here
	leftOrRightChoice.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Caturel_HW6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Caturel_HW6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Caturel_HW6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Caturel_HW6Dlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	
}


void Caturel_HW6Dlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	if(choiceShift.GetCheck())
	{
		leftOrRightChoice.EnableWindow(TRUE);
		numOfShits.EnableWindow(TRUE);
	}
	else
	{
		leftOrRightChoice.EnableWindow(FALSE);
		numOfShits.EnableWindow(FALSE);
	}
}

int maxSize = 0;
void Caturel_HW6Dlg::OnBnClickedButton1()
{
	
	CString Coperand1, Coperand2, result, CnumOfShifts,myCString,c, myCStringOperand1, myCStringOperand2;
	CDC *pDC = GetDC();// This class is necessary to get the length of the string 
	CSize cz;//

	operand1.GetWindowTextW(Coperand1);
	operand2.GetWindowTextW(Coperand2);
	numOfShits.GetWindowTextW(CnumOfShifts);
	UpdateData(TRUE);
	if(Coperand1.GetLength() == 0 || Coperand2.GetLength() == 0 || (Coperand1.GetLength() == 0 && Coperand2.GetLength() == 0) )
	{
		result = "At least one operand was not entered.";
		listOutput.AddString(result);
		cz = pDC->GetTextExtent(result);// This function was taken from CS204 Lab materials. It makes result box with horizantal scroll
		if(cz.cx > maxSize)
			maxSize = cz.cx; 
		

		
	}
	else if(choiceShift.GetCheck() == 1 && CnumOfShifts.GetLength() == 0)
	{
		result = "Specify by how many bits you want to shift.";
		listOutput.AddString(result); 
		cz = pDC->GetTextExtent(result); // This function was taken from CS204 Lab materials. It makes result box with horizantal scroll
		if(cz.cx > maxSize) 
			maxSize = cz.cx; 
		
		
	}
	else
	{
		unsigned int unsignedOperand1 = _tcstoul(Coperand1,nullptr,10); //In this section, CString inputs turn into unsigned int.
		unsigned int unsignedOperand2 = _tcstoul(Coperand2,nullptr,10);
		unsigned int unsignedNumOfShifts = _tcstoul(CnumOfShifts,nullptr,10);

		if(choiceAnd == 0)
		{
			if(choiceShift.GetCheck() == 1)
			{
				int selectedIdx = leftOrRightChoice.GetCurSel(); // taking choice from list.
				leftOrRightChoice.GetLBText(selectedIdx,c);
				//leftOrRightChoice.GetWindowTextW(c);
				if(c ==	"Left")
				{
					unsignedOperand1 = unsignedOperand1 << unsignedNumOfShifts ;
					unsignedOperand2 = unsignedOperand2 << unsignedNumOfShifts ;

				}
				else if(c == "Right")
				{
					unsignedOperand1 = unsignedOperand1 >> unsignedNumOfShifts ;
					unsignedOperand2 = unsignedOperand2 >> unsignedNumOfShifts ;
				}
			}
			unsigned int total = unsignedOperand1 & unsignedOperand2;
			myCString.Format(_T("%u"), total); // turns unsigned int into CString to put it to result box. 
			myCStringOperand1.Format(_T("%u"), unsignedOperand1);
			myCStringOperand2.Format(_T("%u"), unsignedOperand2);
			result = myCStringOperand1+ _T(" AND ")+ myCStringOperand2 + _T(" = ") + myCString;	
		}
		if(choiceAnd == 1)
		{
			if(choiceShift.GetCheck() == 1)
			{
				int selectedIdx = leftOrRightChoice.GetCurSel();
				leftOrRightChoice.GetLBText(selectedIdx,c);
				//leftOrRightChoice.GetWindowTextW(c);
				if(c ==	"Left")
				{
					unsignedOperand1 = unsignedOperand1 << unsignedNumOfShifts ;
					unsignedOperand2 = unsignedOperand2 << unsignedNumOfShifts ;
				}
				else if(c == "Right")
				{
					unsignedOperand1 = unsignedOperand1 >> unsignedNumOfShifts ;
					unsignedOperand2 = unsignedOperand2 >> unsignedNumOfShifts ;
				}
			}
			unsigned int total = unsignedOperand1 | unsignedOperand2;
			myCString.Format(_T("%u"), total);
			myCStringOperand1.Format(_T("%u"), unsignedOperand1); // turns unsigned int into CString to put it to result box.
			myCStringOperand2.Format(_T("%u"), unsignedOperand2);
			result = myCStringOperand1+ _T(" OR ")+ myCStringOperand2 + _T(" = ") + myCString;
		}
		if(choiceAnd == 2)
		{
			if(choiceShift.GetCheck() == 1)
			{
				int selectedIdx = leftOrRightChoice.GetCurSel();
				leftOrRightChoice.GetLBText(selectedIdx,c);
				//leftOrRightChoice.GetWindowTextW(c);
				if(c ==	"Left")
				{
					unsignedOperand1 = unsignedOperand1 << unsignedNumOfShifts ;
					unsignedOperand2 = unsignedOperand2 << unsignedNumOfShifts ;

				}
				else if(c == "Right")
				{
					unsignedOperand1 = unsignedOperand1 >> unsignedNumOfShifts ;
					unsignedOperand2 = unsignedOperand2 >> unsignedNumOfShifts ;
				}
			}
			unsigned int total = unsignedOperand1 ^ unsignedOperand2;
			myCString.Format(_T("%u"), total);
			myCStringOperand1.Format(_T("%u"), unsignedOperand1); // turns unsigned int into CString to put it to result box.
			myCStringOperand2.Format(_T("%u"), unsignedOperand2);
			result = myCStringOperand1+  _T(" XOR ") + myCStringOperand2 + _T(" = ") + myCString;
		}

		listOutput.AddString(result); 
		cz = pDC->GetTextExtent(result);
		if(cz.cx > maxSize)
		{
			maxSize = cz.cx;
		}
	}

	listOutput.SetHorizontalExtent(maxSize);
	
}
