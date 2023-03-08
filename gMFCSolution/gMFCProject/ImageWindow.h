#pragma once
#include "afxdialogex.h"


// CImageWindow 대화 상자

class CImageWindow : public CDialogEx
{
	DECLARE_DYNAMIC(CImageWindow)

public:
	CImage m_Image;

	CImageWindow(CWnd* pParent = nullptr, int nWindowId = 0);   // 표준 생성자입니다.
	virtual ~CImageWindow();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGE_WINDOW };
#endif
private:
	int m_nId;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void InitImage(int nBPP = BIT_PER_PIXEL_8);
	void DrawPattern(const int nPosX, const int nPosY, const int nSize);
	BOOL CheckInnerCircle(int nCenterX, int nCenterY, int nRadius, int nTargetX, int nTargetY) const;
	void DrawCrossLine(const int nPosX, const int nPosY, int nLineWidth = CROSS_LINE_WIDTH, int nLineLength = CROSS_LINE_LENGTH);
	void DrawAroundCircle(const int nPosX, const int nPosY, const int nRadius, int nLineWidth = CROSS_LINE_WIDTH, int nLineLength = CROSS_LINE_LENGTH);
	int GetWindowId();
};
