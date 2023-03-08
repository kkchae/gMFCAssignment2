#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원


namespace MyNameSpace
{
	#define IMAGE_WINDOW_WIDTH_MIN	210					// 내부 이미지 다이얼로그 가로 최소 크기
	#define IMAGE_WINDOW_HEIGHT_MIN	160					// 내부 이미지 다이얼로그 세로 최소 크기
	#define IMAGE_WINDOW_WIDTH		320					// 내부 이미지 다이얼로그 가로 크기
	#define IMAGE_WINDOW_HEIGHT		320					// 내부 이미지 다이얼로그 세로 크기
	#define IMAGE_WINDOW_MARGIN_WIDTH		10					// 내부 이미지 다이얼로그 출력 위치 가로 margin
	#define IMAGE_WINDOW_MARGIN_HEIGHT		80					// 내부 이미지 다이얼로그 출력 위치 세로 margin
	#define IMAGE_WINDOW_NUM	4

	// for BIT_PER_PIXEL_8
	#define COLOR_WHITE				RGB(255, 255, 255)	// white
	#define COLOR_BLACK				RGB(0, 0, 0)		// black
	#define COLOR_YELLOW			RGB(255, 255, 0)	// yellow

	#define CROSS_LINE_WIDTH			2		// 무게중심 십자라인 두께
	#define CROSS_LINE_LENGTH			20		// 무게중심 십자라인 크기
	#define AROUND_MARGIN		5 // 패턴 외곽에 그릴 원의 거리 margin

	typedef enum _BIT_PER_PIXEL { // 픽셀당 비트 수
		BIT_PER_PIXEL_1 = 1,
		BIT_PER_PIXEL_2 = 2,
		BIT_PER_PIXEL_4 = 4,
		BIT_PER_PIXEL_8 = 8,
		BIT_PER_PIXEL_16 = 16,
	} BIT_PER_PIXEL;
}
using namespace::MyNameSpace;


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


