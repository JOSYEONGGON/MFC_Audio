
// MFC_Audio.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_AudioApp:
// �� Ŭ������ ������ ���ؼ��� MFC_Audio.cpp�� �����Ͻʽÿ�.
//

class CMFC_AudioApp : public CWinApp
{
public:
	CMFC_AudioApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_AudioApp theApp;