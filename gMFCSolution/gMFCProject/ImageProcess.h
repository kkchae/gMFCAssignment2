#pragma once

// CImageProcess 명령 대상

class CImageProcess : public CObject
{
public:
	CImageProcess();
	virtual ~CImageProcess();

	BOOL FindPattern(CImage* pImage, const int nThreshHold, int* nRetCenterX = nullptr, int* nRetCenterY = nullptr);
	BOOL FindPatternProcess(CImage* pImage, const int nThreshHold, int* nCenterX = nullptr, int* nCenterY = nullptr);
};


