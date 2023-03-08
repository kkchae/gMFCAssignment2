// ImageWindow.cpp: 구현 파일
//

#include "pch.h"
#include "gMFCProject.h"
#include "afxdialogex.h"
#include "ImageWindow.h"
#include <iostream>
using namespace std;


// CImageWindow 대화 상자

IMPLEMENT_DYNAMIC(CImageWindow, CDialogEx)

CImageWindow::CImageWindow(CWnd* pParent /*=nullptr*/, int nWindowId)
	: CDialogEx(IDD_IMAGE_WINDOW, pParent)
	, m_nId(nWindowId)
{

}

CImageWindow::~CImageWindow()
{
}

void CImageWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImageWindow, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CImageWindow 메시지 처리기


BOOL CImageWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CImageWindow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	if (m_Image != nullptr) {
		m_Image.Draw(dc, 0, 0);
	}
}

void CImageWindow::InitImage(int nBPP /*= BIT_PER_PIXEL_8*/)
{
	CRect rect;
	this->GetClientRect(&rect);
	printf("Image window %d번 size - width : %d, , height : %d", this->m_nId, rect.right, rect.bottom);

	int nWidth = rect.right;
	int nHeight = rect.bottom;

	m_Image.Create(nWidth, -nHeight, nBPP);

	if (BIT_PER_PIXEL_8 == nBPP) {
		int nColorNumber = 1 << nBPP;
		cout << " nColorNumber : " << nColorNumber << endl;

		RGBQUAD* rgb = new RGBQUAD[nColorNumber];
		for (int i = 0; i < nColorNumber; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_Image.SetColorTable(0, nColorNumber, rgb);

		unsigned char* fm = (unsigned char*)m_Image.GetBits();
		memset(fm, COLOR_BLACK, sizeof(unsigned char) * nWidth * nHeight);

		delete[] rgb;
	}
}

void CImageWindow::DrawPattern(const int nPosX, const int nPosY, const int nSize)
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();

	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	memset(fm, COLOR_BLACK, sizeof(unsigned char) * nWidth * nHeight); // 이미지 값 초기화
	
	if (1 == nSize) {
		fm[nPosY * nPitch + nPosX] = (rand() % 255) + 1; // 1~255
	}
	else {
		int nRadius = (int)(nSize / 2);
		int nCenterX = nPosX + nRadius;
		int nCenterY = nPosY + nRadius;

		for (int nCurY = nPosY; nCurY < nPosY + nSize; nCurY++) {
			for (int nCurX = nPosX; nCurX < nPosX + nSize; nCurX++) {
				if (CheckInnerCircle(nCenterX, nCenterY, nRadius, nCurX, nCurY)) {
					fm[nCurY * nPitch + nCurX] = (rand() % 255) + 1; // 1~255
				}
			}
		}
	}

	this->Invalidate();
}

BOOL CImageWindow::CheckInnerCircle(int nCenterX, int nCenterY, int nRadius, int nTargetX, int nTargetY) const
{
	BOOL bRet = FALSE;
	int dX = nTargetX - nCenterX;
	int dY = nTargetY - nCenterY;

	if ((dX * dX + dY * dY) < nRadius * nRadius)
		bRet = TRUE;

	return bRet;
}

void CImageWindow::DrawCrossLine(const int nPosX, const int nPosY, int nLineWidth /*= CROSS_LINE_WIDTH*/, int nLineLength /*= CROSS_LINE_LENGTH*/)
{
	CDC* pDC = GetDC();
	if (pDC != nullptr) {
		CPen pen;
		pen.CreatePen(PS_SOLID, nLineWidth, COLOR_YELLOW);
		CPen* oldPen = pDC->SelectObject(&pen);

		pDC->MoveTo(nPosX - nLineLength, nPosY); // 가로
		pDC->LineTo(nPosX + nLineLength, nPosY);
		pDC->MoveTo(nPosX, nPosY - nLineLength); // 세로
		pDC->LineTo(nPosX, nPosY + nLineLength);

		pDC->SelectObject(oldPen);
		pen.DeleteObject();
	}
}

void CImageWindow::DrawAroundCircle(const int nPosX, const int nPosY, const int nRadius, int nLineWidth /*= CROSS_LINE_WIDTH*/, int nLineLength /*= CROSS_LINE_LENGTH*/)
{
	CDC* pDC = GetDC();
	if (pDC != nullptr) {
		CPen pen;
		pen.CreatePen(PS_SOLID, nLineWidth, COLOR_YELLOW);
		CPen* oldPen = pDC->SelectObject(&pen);

		CBrush brush;
		brush.CreateSolidBrush(COLOR_YELLOW);
		brush.CreateStockObject(NULL_BRUSH);
		CBrush* oldBrush = pDC->SelectObject(&brush);

		pDC->Ellipse(
			nPosX - nRadius - AROUND_MARGIN, nPosY - nRadius - AROUND_MARGIN,
			nPosX + nRadius + AROUND_MARGIN, nPosY + nRadius + AROUND_MARGIN);

		pDC->SelectObject(oldPen);
		pDC->SelectObject(oldBrush);
		pen.DeleteObject();
		brush.DeleteObject();
	}
}

int CImageWindow::GetWindowId()
{
	return m_nId;
}
