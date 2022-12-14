
// MFC_AudioDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_Audio.h"
#include "MFC_AudioDlg.h"
#include "afxdialogex.h"
#include <fstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_AudioDlg ��ȭ ����




CMFC_AudioDlg::CMFC_AudioDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_AudioDlg::IDD, pParent)
	, m_sound(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	mh_read_data = NULL;
}

void CMFC_AudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sound);
}

BEGIN_MESSAGE_MAP(CMFC_AudioDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC_AudioDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC_AudioDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC_AudioDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFC_AudioDlg �޽��� ó����

BOOL CMFC_AudioDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMFC_AudioDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFC_AudioDlg::OnPaint()
{
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

	// �۷ι� �޸� ������ ������� ���...
	if(mh_read_data != NULL)
	{
		// �޸𸮸� ����� �� �ְ� p_data�� �����Ų��.
		// �ش� ���̺� ������ ��� ä�ο� ���ô� 8��Ʈ�� ������ ������ �ֱ� ������
		// 8��Ʈ�� ������ ���� �� �ֵ��� char Ÿ������ �����Ѵ�.
		// ���� ���̺� �����Ͱ� ������ ���� ���� �����ͷ� ����� �� ���� 0 ~ 127�� ����ǰ�
		// 0���� ������� 128 ~ 255�� ����Ǳ� ������ unsigned char Ÿ���� �ȴ�.
		// -128 ~ 0 => 0 ~ 128,  0 ~ 127 => 128 ~ 255
		short int *p_data = (short int *)::GlobalLock(mh_read_data);

		// ������ ���� ��ġ�� ���Ѵ�.
		dc.MoveTo(0, 150);
		// �� ���� ���� �׸���.
		int size = m_data_size/2;
		unsigned int data;
		for(int i = 0; i < size; i++){
			// ������ ���̰� ��� ������ ��ʽ��� �̿��Ͽ� x ���� �����Ѵ�.
			// ������ ���� : ������ �� = ������ �ε��� : ������ �ε����� ��ġ�� x��
			// m_data_size : 1000 = i : x
			// ������ ���� ũ�Ⱑ ũ�⶧���� ��ʽ��� �̿��Ͽ� y ���� �����Ѵ�.
			// ������ �ִ밪 : �������� ���� = ������ ���簪 : y
			// p_data[i] * 300 = 65535 * y
			// p_data[i] * 300 / 65535 = y
			data = p_data[i] * 300 / 65535;
			dc.LineTo(i*1000/size, data + 150);
		}

		// p_data�� �۷ι� �޸��� ������ �����Ѵ�.
		::GlobalUnlock(p_data);      
		
	}

}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFC_AudioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFC_AudioDlg::OnBnClickedButton1()
{
	// test.wav ������ �б���� ����.
        HMMIO hmmio = mmioOpen((LPWSTR)_T("baecha.wav"), NULL, MMIO_READ);

        // ������ ���������� �� ���...
        if(hmmio != NULL)
		{
            // �θ� ûũ ������ ������ ����ü
            MMCKINFO chunk_info_parent;
 
            // �θ� ûũ�� ��õǾ� �ִ� "WAVE" ���� ����ü�� ����Ѵ�.
            chunk_info_parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
            // �θ� ûũ�� ã�´�.
            // ���������� �θ� ûũ�� ã�� ���...
            if(mmioDescend(hmmio, &chunk_info_parent, NULL, MMIO_FINDRIFF) == MMSYSERR_NOERROR )
			{
                // �ڽ� ûũ�� ������ ûũ�� ������ ����ü
                MMCKINFO chunk_info_child;
               
                // �ڽ� ûũ�� ��õǾ� �ִ� "fmt" ���� ����ü�� ����Ѵ�.
                chunk_info_child.ckid = mmioFOURCC('f', 'm', 't', ' ');
                // �ڽ� ûũ�� ã�´�. ����° ���ڿ� ������ ���� �θ� ûũ�� �ּҸ� �Ѱܼ� �ش� �ڽ� ûũ��
                // ���� �� �ֵ��� �Ѵ�. ���������� �ڽ� ûũ�� ã�� ���...
                if(mmioDescend(hmmio, &chunk_info_child, &chunk_info_parent, MMIO_FINDCHUNK) == MMSYSERR_NOERROR )
				{
                    // ���̺� ���� ������ ������ ����ü
                    PCMWAVEFORMAT wave_record;
                    // chunk_info_child.cksize ũ���� ������ ���Ͽ��� �о wave_record ����ü�� �����Ѵ�.
                    mmioRead(hmmio, (LPSTR)&wave_record, chunk_info_child.cksize);

                    // ������ ûũ�� ��õǾ� �ִ� "data" ���� ����ü�� ����Ѵ�.
                    chunk_info_child.ckid = mmioFOURCC('d', 'a', 't', 'a');
                    // ������ ûũ�� ã�´�.
                    if(mmioDescend(hmmio, &chunk_info_child, &chunk_info_parent, MMIO_FINDCHUNK) == MMSYSERR_NOERROR )
					{
                        // �������� ũ�⸦ ���Ѵ�.
                        m_data_size = chunk_info_child.cksize;
 
                        // �۷ι� �޸� ������ �Ҵ�޾Ҵٸ� �Ҵ��� �����Ѵ�.
                        if(mh_read_data != NULL) ::GlobalFree(mh_read_data);
 
                        // �������� ũ�⸸ŭ �۷ι� �޸� ������ �Ҵ�޴´�.
                        mh_read_data = ::GlobalAlloc(GMEM_MOVEABLE, m_data_size);
                        // �޸𸮸� ����� �� �ְ� p_data�� �����Ų��.
                        char *p_data = (char *)::GlobalLock(mh_read_data);
 
                        // �ش� �޸� ������ ���̺� ���Ͽ��� ���� �����͸� �о �����Ѵ�.
                        mmioRead(hmmio, p_data, m_data_size);
 
                        // p_data�� �۷ι� �޸��� ������ �����Ѵ�.
                        ::GlobalUnlock(p_data);
                        // ȭ���� �����Ѵ�.
                        Invalidate();
                    }
                }
            }
            // ���̺� ������ �ݴ´�.
            mmioClose(hmmio, 0);
        }
}


void CMFC_AudioDlg::OnBnClickedButton2()
{
	UpdateData();
	// ���� ���� ����
//	WAVEFORMATEX pFormat;
//	// ���� ������ ����ü
//	WAVEHDR WaveOutHdr;
//	// ���Ϸκ��� ���� ����� �����͸� ����Ѵ�.
//	// �� ���� ���̸� �޴´�.
////	int length = OpenWavFile("baecha.wav", &pFormat, &WaveOutHdr);
//	// WAVE_FORMAT_PCM������ ���õǴ� ��
//	pFormat.cbSize = 0;
//	// WAVE_FORMAT_PCM�̶�� �������̱� ������ nSamplesPerSec�� ���� ���̴�.
//	pFormat.nAvgBytesPerSec = pFormat.nSamplesPerSec;
//	// ���̺귯������ ���� ������ ����� ���ϴ� �Լ�(����ڰ� ����ϴ� ���� �ƴ�)
//	WaveOutHdr.dwBytesRecorded = 0;
//	// ���̺귯������ callback �Լ� ���� ���Ǵ� status flag
//	WaveOutHdr.dwFlags = 0;
//	// �ݺ� ����� ���� (������� �ʴ´�.)
//	WaveOutHdr.dwLoops = 0;
//	// ���� ����� ���� (������� �ʴ´�.)
//	WaveOutHdr.reserved = 0;

	// ������ ����ϴ� ��ġ ����ü
	HWAVEOUT hWaveOut;
	// waveOutOpen�� �� ����ü�� ��ġ�� Open�ϴ� �Լ�.
	// �Ķ���ʹ� HWAVEOUT, �ι�°�� ��ġ �����ε� ������ WAVE_MAPPER�� �־ �˴ϴ�.
	// ���� Ư���ϰ� ����Ŀ�� ������ �־(��Ʈ�� �⺻ ����Ŀ, �ص�� ����Ŀ) ���� ���߿� ������ ���ڸ� �����߽��ϴ�.
	// ����° �Ķ���ʹ� ���� ������ �ֽ��ϴ�.
	// ������ �Ķ���ʹ� WAVE_FORMAT_DIRECT�� �����ؼ� ����ȭ�� �ҽ��� �ۼ��մϴ�.
	if (waveOutOpen(&hWaveOut, /*waveInGetNumDevs() - 1*/ WAVE_MAPPER, 0, 0, 0, WAVE_FORMAT_DIRECT))
	{
		// ���� �ܼ� ���
		// ���� ����
		return;
	}
	// ��ġ�� ��� �غ� �˸��� �Լ�
	//if (waveOutPrepareHeader(hWaveOut, &WaveOutHdr, sizeof(WAVEHDR))) 
	//{
	//	// ���� �ܼ� ���
	//	// ��ġ �ݱ�
	//	waveOutClose(hWaveOut);
	//	return;
	//}

	if (waveOutSetVolume(hWaveOut, (DWORD)(0xFFFF*1.0*m_sound/100.0)))
	{
		waveOutClose(hWaveOut);
		return ;
	}

	// ��� ����
	//if (waveOutWrite(hWaveOut, &WaveOutHdr, sizeof(WAVEHDR)))
	//{
	//	// ���� �ܼ� ���
	//	// ��ġ �ݱ�
	//	waveOutClose(hWaveOut);
	//	return ;
	//}
	// WAVE_FORMAT_DIRECT�� �����߱� ������ ����� ���������� ��ٷ��� �մϴ�.
	// length�� ������ ���̸� �˱� ������ 1�ʴ����� �ֿܼ� ǥ���մϴ�.
	//for (int i = 0; i <= length; i++)
	//{
	//	// �÷��� �� ǥ��
	//	Sleep(1000);
	//}
	// ��ġ �ݱ�
	//delete WaveOutHdr.lpData;
	waveOutClose(hWaveOut);
}

int CMFC_AudioDlg::OpenWavFile(const char* filename, WAVEFORMATEX* format, PWAVEHDR WaveHeader)
{
	ifstream istream;
	istream.open(filename, fstream::binary);
	// wav���� ����ü��� �ۼ��Ѵ�.
	istream.seekg(0, ios::beg);
	// chunk id
	char riff[5];
	memset(riff, 0x00, 5);
	istream.read(riff, 4);
	int chunksize;
	// chunk size (36 + SubChunk2Size))
	istream.read((char*)&chunksize, 4);
	// format
	char wave[5];
	memset(wave, 0x00, 5);
	istream.read(wave, 4);
	// subchunk1ID - fmt
	char subchunk1ID[5];
	memset(subchunk1ID, 0x00, 5);
	istream.read(subchunk1ID, 4);
	// subchunk1size (������ PCM�̸� 16 ����)
	int subchunk1size;
	istream.read((char*)&subchunk1size, 4);
	// AudioFormat (������ PCM�̸� 1 ����)
	istream.read((char*)&format->wFormatTag, 2);
	// NumChannels
	istream.read((char*)&format->nChannels, 2);
	// sample rate  
	istream.read((char*)&format->nSamplesPerSec, 4);
	// byte rate (SampleRate * block align)
	int byteRate;
	istream.read((char*)&byteRate, 4);
	// block align
	istream.read((char*)&format->nBlockAlign, 2);
	// bits per sample
	istream.read((char*)&format->wBitsPerSample, 4); //8 == 2 , 16 == 4
	// subchunk2ID
	char data[5];
	memset(data, 0x00, 5);
	istream.read(data, 4);
	// subchunk2size (NumSamples * nBlockAlign)
	int subchunk2size;
	istream.read((char*)&subchunk2size, 4);
	// ���� ���� ������ �о����
	WaveHeader->dwBufferLength = subchunk2size / format->nChannels;
	WaveHeader->lpData = (char*)malloc(WaveHeader->dwBufferLength);
	istream.read(WaveHeader->lpData, WaveHeader->dwBufferLength);
	// ���� �ݱ�
	istream.close();

	// byteRate�� 1���� ������ ����
	// WaveHeader->dwBufferLength�� �������� ��ü ����
	// WaveHeader->dwBufferLength / byteRate�� wav�� ���� ���̰� ���´�.
	return WaveHeader->dwBufferLength / byteRate;
}

void CMFC_AudioDlg::OnBnClickedButton3()
{
	// ������ �ִ�� ����
	UpdateData();
	waveOutSetVolume(0, (DWORD)(0xFFFF*1.0*m_sound/100.0));
	PlaySound((LPWSTR)MAKEINTRESOURCE(IDR_WAVE11), NULL, SND_ASYNC | SND_RESOURCE);
}
