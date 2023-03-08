// ImageProcess.cpp: 구현 파일
//

#include "pch.h"
#include "gMFCProject.h"
#include "ImageProcess.h"
#include <thread>
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

// CImageProcess

CImageProcess::CImageProcess()
{
}

CImageProcess::~CImageProcess()
{
}

void ThreadFindPattern(CImageProcess* pParent, CImage* pImage, const int nThreshHold, int* nRetCenterX, int* nRetCenterY, BOOL* bRet)
{
	if (pParent != nullptr) {
		*bRet = pParent->FindPatternProcess(pImage, nThreshHold, nRetCenterX, nRetCenterY);
	}
}

BOOL CImageProcess::FindPattern(CImage* pImage, const int nThreshHold, int* nRetCenterX, int* nRetCenterY)
{
	BOOL bRet = FALSE;
	thread _thread(ThreadFindPattern, this, pImage, nThreshHold, nRetCenterX, nRetCenterY, &bRet);
	_thread.join();
	return bRet;
}

BOOL CImageProcess::FindPatternProcess(CImage* pImage, const int nThreshHold, int* nRetCenterX, int* nRetCenterY)
{
	BOOL bFound = FALSE;
	if (pImage != nullptr) {
		steady_clock::time_point beginTime = steady_clock::now();

		int nWidth = pImage->GetWidth();
		int nHeight = pImage->GetHeight();
		int nPitch = pImage->GetPitch();

		int nSumX = 0;
		int nSumY = 0;
		int nCount = 0;
		CRect rect(0, 0, nWidth, nHeight);
		unsigned char* fm = (unsigned char*)pImage->GetBits();

		for (int nCurY = rect.top; nCurY < rect.bottom; nCurY++) {
			for (int nCurX = rect.left; nCurX < rect.right; nCurX++) {
				if (fm[nCurY * nPitch + nCurX] > nThreshHold) {
					nSumX += nCurX;
					nSumY += nCurY;
					nCount++;
				}
			}
		}

		if (nCount > 0) {
			bFound = TRUE;
			int nCenterX = (int)(nSumX / nCount);
			int nCenterY = (int)(nSumY / nCount);

			// 중심좌표
			if (nRetCenterX != nullptr && nRetCenterY != nullptr) {
				*nRetCenterX = nCenterX;
				*nRetCenterY = nCenterY;
			}
			cout << "Center point : " << nCenterX << ", " << nCenterY << endl;
		}
		else {
			bFound = FALSE;
		}

		steady_clock::time_point endTime = steady_clock::now();

		microseconds microsec = duration_cast<microseconds>(endTime - beginTime); // us(micro seconds) : 1 / 1,000,000 sec
		if (microsec > steady_clock::duration::zero()) {
			cout << "Thread id :" << this_thread::get_id() << ", process time : " << microsec.count() << " micro seconds" << endl;
		}
		else {
			nanoseconds nanosec = duration_cast<nanoseconds>(endTime - beginTime); // ns(nano seconds) : 1 / 10^9 sec
			cout << "Thread id :" << this_thread::get_id() << ", process time : " << nanosec.count() << " nano seconds" << endl;
		}
	}
	return bFound;
}
