
// MFC_AudioDlg.h : 헤더 파일
//

#pragma once

// CMFC_AudioDlg 대화 상자
class CMFC_AudioDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFC_AudioDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFC_AUDIO_DIALOG };

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
	afx_msg void OnBnClickedButton1();

public:
	int m_data_size;
	HGLOBAL mh_read_data;
	MCI_ANIM_OPEN_PARMS m_mci_open;
	int m_play_flag;
	afx_msg void OnBnClickedButton2();
	int OpenWavFile(const char* filename, WAVEFORMATEX* format, PWAVEHDR WaveHeader);
	int m_sound;
	afx_msg void OnBnClickedButton3();
};
