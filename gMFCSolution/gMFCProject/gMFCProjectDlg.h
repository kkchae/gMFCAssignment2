
// gMFCProjectDlg.h: 헤더 파일
//

#pragma once

#include "ImageWindow.h"
#include "ImageProcess.h"
#include <memory>
using namespace std;


typedef shared_ptr<CImageWindow> CImageWindowPtr;
typedef shared_ptr<CImageProcess> CImageProcessPtr;


// CgMFCProjectDlg 대화 상자
class CgMFCProjectDlg : public CDialogEx
{
private:
	CImageWindowPtr m_pImageWindow[IMAGE_WINDOW_NUM]; // 이미지를 그릴 내부 다이얼로그
	CImageProcessPtr m_pImageProcess; // 현재 단계에서는 unique_ptr도 가능
	int m_nImageWidth; // 이미지 다이얼로그 가로 크기
	int m_nImageHeight; // 이미지 다이얼로그 세로 크기
	int m_nMinImageSize; // 이미지 다이얼로그 가로, 세로 크기중 작은값

// 생성입니다.
public:
	CgMFCProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	enum EDLG_STATUS {
		EDLG_STATUS_INIT = 0,
		EDLG_STATUS_PROCESS_USABLE,		// "Process" 버튼 사용 가능
		EDLG_STATUS_PROCESS_UNUSABLE,	// "Process" 버튼 사용 불가능
	};

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GMFCPROJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	int m_nInputSize;
	afx_msg void OnBnClickedBtnMakePattern();
	afx_msg void OnBnClickedBtnProcess();
	afx_msg void OnUpdateEditInputSize();
	void UpdateDlgItems(EDLG_STATUS eStatus = EDLG_STATUS_INIT);
};
