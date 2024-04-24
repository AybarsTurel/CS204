
// aturel_HW6Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Caturel_HW6Dlg dialog
class Caturel_HW6Dlg : public CDialogEx
{
// Construction
public:
	Caturel_HW6Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ATUREL_HW6_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int choiceAnd;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedCheck1();
	CEdit operand1;
	CEdit operand2;
	CButton choiceShift;
	CButton computeButton;
	CComboBox leftOrRightChoice;
	CListBox outputList;
	CEdit numOfShits;
	CListBox listOutput;
	afx_msg void OnBnClickedButton1();
};
