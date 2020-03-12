#include "stdafx.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
	Release();
}

void CMyBitmap::Load_Bmp(const TCHAR * _pFilePath)
{
	// 이미지를 그릴 타이밍에 매번 불러오기를 하면 연산이 커지게 된다.
	// 효율적으로 관리하기 위해 이미지를 불러온 후 그려 놓는다.
	// 이미지를 그려 넣을 DC가 필요한데, GetDC()로 DC가져와 그린다면?
	// GetDC()로 가져온 DC는 화면에 출력하는 DC이므로 의미가 없어지게 된다.
	// 이를 해결하기 위해 새로운 DC가 필요한데 기존에 사용하던 DC와 호환이 되는 DC가 필요하다.
	// ##1. GetDC()로 DC를 불러온다.
	// ##2. CreateCompatibleDC()로 호환되는 DC를 할당한다. -> 복사 한다.
	// ##3. 불러온 DC는 ReleaseDC()를 통해 지워준다.
	HDC hDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	// LoadImage()
	// LR_LOADFROMFILE : 파일에서 이미지를 불러오겠다.
	// LR_CREATEDIBSECTION : 읽어온 파일을 DIB 형태로 변환하겠다.
	m_hBitmap = (HBITMAP)LoadImage(NULL, _pFilePath, IMAGE_BITMAP, 0, 0
		, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	// SelectObject()
	// LoadImage로 비트맵의 정보를 가지고 있는 상태 / 그리지 않고 있다.
	// 비트맵을 그리기 위해 m_hMemDC를 준비하였으나,현재 선택된 GDI 오브젝트는 디폴트 값이다.
	// SelectObject() 도구를 선택해주는 함수이다.
	// 단, GDI 오브젝트를 선택하기 전에 기존에 가지고 있던 도구를 반환한다.
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CMyBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
