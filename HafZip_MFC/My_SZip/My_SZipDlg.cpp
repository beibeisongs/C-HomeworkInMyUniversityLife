
// My_SZipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "My_SZip.h"
#include "My_SZipDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"Encode_Tool.h"
#include"Decode_Tool.h"

#include "Haf.h"

using namespace std;

void encode(string source_file_path, string target_file_path) {
	ALPHA_FREQ * alphaFreq = NULL;				// 统计字符及频度的数组
	int alphaType = 0;							// 字符种类

	HAFFMAN_TAB * haffmanTab = NULL;			// 哈夫曼表
	char * code = NULL;							// 存储字符的哈夫曼编码

	int hafIndex[256] = { 0 };					// 下标为字符的ASCII码，其值为该字符在哈夫曼表中的下标，形成键值对

	Encode_Tool encode;

	// string source_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2.txt";

	const char * sourceFileName = source_file_path.data();

	// string target_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2.Haf";

	const char * targetFileName = target_file_path.data();

	alphaFreq = encode.getAlphaFreq(sourceFileName, &alphaType);
	// encode.showAlphaFreq(alphaFreq, alphaType);

	haffmanTab = encode.initHaffmanTab(alphaFreq, alphaType, hafIndex);
	encode.creatHaffmanTree(haffmanTab, alphaType);

	code = (char *)calloc(sizeof(char), alphaType);
	if (alphaType <= 0 || code == NULL) {
		// cout << "Error : Empty freq ! 或内存分配失败 ！" << endl;
		exit(1);
	}
	for (int i = 0; i < alphaType; i++) {
		code[i] = NULL;
	}

	encode.makeHaffmanCode(haffmanTab, 2 * alphaType - 2, 0, code);
	// encode.showHaffmanTab(haffmanTab, 2 * alphaType - 1);

	encode.haffmanEncoding(haffmanTab, sourceFileName, targetFileName, hafIndex, alphaType, alphaFreq);

	encode.DELETE_HaffmanTab(haffmanTab, alphaType);

	free(alphaFreq);
	free(code);

}

void decode(string source_file_path, string target_file_path) {
	HAF_FILE_HEAD fileHead;

	ALPHA_FREQ * alphaFreq = NULL;				// 统计字符及频度的数组
	int alphaType = 0;							// 字符种类

	HAFFMAN_TAB * haffmanTab = NULL;			// 哈夫曼表
	char * code = NULL;							// 存储字符的哈夫曼编码

	int hafid[256] = { 0 };						// 下标为字符的ASCII码，其值为该字符在哈夫曼表中的下标，形成键值对

	Decode_Tool decode;

	// string source_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1.Haf";

	const char * sourceFileName = source_file_path.data();

	// string target_file_path = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\2_ded.txt";

	const char * targetFileName = target_file_path.data();

	fileHead = decode.readFileHead(sourceFileName);

	alphaFreq = decode.getAlphaFreq(sourceFileName, &alphaType, fileHead);
	// decode.showAlphaFreq(alphaFreq, alphaType);

	haffmanTab = decode.initHaffmanTab(alphaFreq, alphaType, hafid);
	decode.creatHuffmanTree(haffmanTab, alphaType);

	code = (char *)calloc(sizeof(char), alphaType);

	decode.makeHaffmanCode(haffmanTab, 2 * alphaType - 2, 0, code);
	// decode.showHaffmanTab(haffmanTab, 2 * alphaType - 1);

	decode.haffmanDecoding(haffmanTab, sourceFileName, targetFileName, alphaType, fileHead);

	decode.DELETE_HaffmanTab(haffmanTab, alphaType);
	free(alphaFreq);
	free(code);
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy_SZipDlg dialog



CMy_SZipDlg::CMy_SZipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_SZIP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy_SZipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, command1);
	DDX_Text(pDX, IDC_EDIT2, source_file_path);
	DDX_Text(pDX, IDC_EDIT3, target_file_path);
}

BEGIN_MESSAGE_MAP(CMy_SZipDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMy_SZipDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CMy_SZipDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMy_SZipDlg message handlers

BOOL CMy_SZipDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy_SZipDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy_SZipDlg::OnPaint()
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
HCURSOR CMy_SZipDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy_SZipDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMy_SZipDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// 将各控件中的数据保存到相应的变量
	UpdateData(TRUE);

	// command record 1 : "SZip" "B" "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\4.rtf" "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\4.Haf"
	// command record 2 : "SZip" "Y" "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\4.Haf" "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\4_ded.rtf"


	std::string i_Szip = CT2A(this->command1.GetBuffer());
	std::string source_file_path = CT2A(this->source_file_path.GetBuffer());
	std::string target_file_path = CT2A(this->target_file_path.GetBuffer());

	if (i_Szip == "A") {

		string command_rd = "python D:\\USBei\\C++Projects_Py35_Scripts\\encode_trf.py ";
		command_rd += source_file_path;
		system(command_rd.c_str());

		encode("D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1_doc.txt", target_file_path);
	}
	else if (i_Szip == "X") {

		string target_file_path0 = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1_doc2.txt";

		decode(source_file_path, target_file_path0);

		string command_rd = "python D:\\USBei\\C++Projects_Py35_Scripts\\decode_trf.py ";
		command_rd += target_file_path;

		system(command_rd.c_str());
	}
	else if (i_Szip == "B") {
		encode(source_file_path, target_file_path);
	}
	else if (i_Szip == "Y") {
		decode(source_file_path, target_file_path);

		std::string str_m = "Ok please input ! ";

		this->command1 = str_m.c_str();
		this->source_file_path = str_m.c_str();
		this->target_file_path = str_m.c_str();

		// 根据各变量的值更新相应的控件。和的编辑框会显示m_editSum的值   
		UpdateData(FALSE);
	}
}
