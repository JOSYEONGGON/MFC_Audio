
// MFC_AudioDlg.h : ��� ����
//

#pragma once

// CMFC_AudioDlg ��ȭ ����
class CMFC_AudioDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFC_AudioDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MFC_AUDIO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
