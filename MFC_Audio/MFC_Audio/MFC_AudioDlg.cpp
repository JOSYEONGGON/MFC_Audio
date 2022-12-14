
// MFC_AudioDlg.cpp : 구현 파일
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


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFC_AudioDlg 대화 상자




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


// CMFC_AudioDlg 메시지 처리기

BOOL CMFC_AudioDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFC_AudioDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	// 글로벌 메모리 영역을 사용중인 경우...
	if(mh_read_data != NULL)
	{
		// 메모리를 사용할 수 있게 p_data와 연결시킨다.
		// 해당 웨이브 파일은 모노 채널에 샘플당 8비트의 정보를 가지고 있기 때문에
		// 8비트씩 정보를 읽을 수 있도록 char 타입으로 연결한다.
		// 본래 웨이브 데이터가 가지는 음수 값은 데이터로 저장될 때 하위 0 ~ 127로 저장되고
		// 0에서 양수값은 128 ~ 255로 저장되기 때문에 unsigned char 타입이 된다.
		// -128 ~ 0 => 0 ~ 128,  0 ~ 127 => 128 ~ 255
		short int *p_data = (short int *)::GlobalLock(mh_read_data);

		// 파형의 시작 위치를 정한다.
		dc.MoveTo(0, 150);
		// 각 샘플 값을 그린다.
		int size = m_data_size/2;
		unsigned int data;
		for(int i = 0; i < size; i++){
			// 데이터 길이가 길기 때문에 비례식을 이용하여 x 값을 조정한다.
			// 데이터 길이 : 윈도우 폭 = 데이터 인덱스 : 데이터 인덱스가 위치할 x값
			// m_data_size : 1000 = i : x
			// 데이터 값의 크기가 크기때문에 비례식을 이용하여 y 값을 조정한다.
			// 데이터 최대값 : 윈도우의 높이 = 데이터 현재값 : y
			// p_data[i] * 300 = 65535 * y
			// p_data[i] * 300 / 65535 = y
			data = p_data[i] * 300 / 65535;
			dc.LineTo(i*1000/size, data + 150);
		}

		// p_data와 글로벌 메모리의 연결을 해제한다.
		::GlobalUnlock(p_data);      
		
	}

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFC_AudioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFC_AudioDlg::OnBnClickedButton1()
{
	// test.wav 파일을 읽기모드로 연다.
        HMMIO hmmio = mmioOpen((LPWSTR)_T("baecha.wav"), NULL, MMIO_READ);

        // 파일을 성공적으로 연 경우...
        if(hmmio != NULL)
		{
            // 부모 청크 정보를 저장할 구조체
            MMCKINFO chunk_info_parent;
 
            // 부모 청크에 명시되어 있는 "WAVE" 값을 구조체에 기록한다.
            chunk_info_parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
            // 부모 청크를 찾는다.
            // 성공적으로 부모 청크를 찾은 경우...
            if(mmioDescend(hmmio, &chunk_info_parent, NULL, MMIO_FINDRIFF) == MMSYSERR_NOERROR )
			{
                // 자식 청크와 데이터 청크를 저장할 구조체
                MMCKINFO chunk_info_child;
               
                // 자식 청크에 명시되어 있는 "fmt" 값을 구조체에 기록한다.
                chunk_info_child.ckid = mmioFOURCC('f', 'm', 't', ' ');
                // 자식 청크를 찾는다. 세번째 인자에 위에서 얻은 부모 청크의 주소를 넘겨서 해당 자식 청크를
                // 얻을 수 있도록 한다. 성공적으로 자식 청크를 찾은 경우...
                if(mmioDescend(hmmio, &chunk_info_child, &chunk_info_parent, MMIO_FINDCHUNK) == MMSYSERR_NOERROR )
				{
                    // 웨이브 포맷 정보를 저장할 구조체
                    PCMWAVEFORMAT wave_record;
                    // chunk_info_child.cksize 크기의 정보를 파일에서 읽어서 wave_record 구조체에 저장한다.
                    mmioRead(hmmio, (LPSTR)&wave_record, chunk_info_child.cksize);

                    // 데이터 청크에 명시되어 있는 "data" 값을 구조체에 기록한다.
                    chunk_info_child.ckid = mmioFOURCC('d', 'a', 't', 'a');
                    // 데이터 청크를 찾는다.
                    if(mmioDescend(hmmio, &chunk_info_child, &chunk_info_parent, MMIO_FINDCHUNK) == MMSYSERR_NOERROR )
					{
                        // 데이터의 크기를 구한다.
                        m_data_size = chunk_info_child.cksize;
 
                        // 글로벌 메모리 영역을 할당받았다면 할당을 해제한다.
                        if(mh_read_data != NULL) ::GlobalFree(mh_read_data);
 
                        // 데이터의 크기만큼 글로벌 메모리 영역을 할당받는다.
                        mh_read_data = ::GlobalAlloc(GMEM_MOVEABLE, m_data_size);
                        // 메모리를 사용할 수 있게 p_data와 연결시킨다.
                        char *p_data = (char *)::GlobalLock(mh_read_data);
 
                        // 해당 메모리 영역에 웨이브 파일에서 읽은 데이터를 읽어서 저장한다.
                        mmioRead(hmmio, p_data, m_data_size);
 
                        // p_data와 글로벌 메모리의 연결을 해제한다.
                        ::GlobalUnlock(p_data);
                        // 화면을 갱신한다.
                        Invalidate();
                    }
                }
            }
            // 웨이브 파일을 닫는다.
            mmioClose(hmmio, 0);
        }
}


void CMFC_AudioDlg::OnBnClickedButton2()
{
	UpdateData();
	// 음성 포멧 지정
//	WAVEFORMATEX pFormat;
//	// 음성 데이터 구조체
//	WAVEHDR WaveOutHdr;
//	// 파일로부터 음성 포멧과 데이터를 취득한다.
//	// 총 음성 길이를 받는다.
////	int length = OpenWavFile("baecha.wav", &pFormat, &WaveOutHdr);
//	// WAVE_FORMAT_PCM에서는 무시되는 값
//	pFormat.cbSize = 0;
//	// WAVE_FORMAT_PCM이라면 무압축이기 때문에 nSamplesPerSec와 같을 것이다.
//	pFormat.nAvgBytesPerSec = pFormat.nSamplesPerSec;
//	// 라이브러리에서 실제 녹음된 사이즈를 구하는 함수(사용자가 사용하는 값이 아님)
//	WaveOutHdr.dwBytesRecorded = 0;
//	// 라이브러리에서 callback 함수 사용시 사용되는 status flag
//	WaveOutHdr.dwFlags = 0;
//	// 반복 재생시 사용됨 (사용하지 않는다.)
//	WaveOutHdr.dwLoops = 0;
//	// 예약 재생시 사용됨 (사용하지 않는다.)
//	WaveOutHdr.reserved = 0;

	// 음성을 출력하는 장치 구조체
	HWAVEOUT hWaveOut;
	// waveOutOpen는 위 구조체로 장치를 Open하는 함수.
	// 파라미터는 HWAVEOUT, 두번째는 장치 선택인데 보통은 WAVE_MAPPER를 넣어도 됩니다.
	// 저는 특이하게 스피커가 여러개 있어서(노트북 기본 스피커, 해드셋 스피커) 가장 나중에 접속한 단자를 선택했습니다.
	// 세번째 파라미터는 음성 포멧을 넣습니다.
	// 마지막 파라미터는 WAVE_FORMAT_DIRECT를 설정해서 동기화된 소스를 작성합니다.
	if (waveOutOpen(&hWaveOut, /*waveInGetNumDevs() - 1*/ WAVE_MAPPER, 0, 0, 0, WAVE_FORMAT_DIRECT))
	{
		// 에러 콘솔 출력
		// 접속 실패
		return;
	}
	// 장치에 출력 준비를 알리는 함수
	//if (waveOutPrepareHeader(hWaveOut, &WaveOutHdr, sizeof(WAVEHDR))) 
	//{
	//	// 에러 콘솔 출력
	//	// 장치 닫기
	//	waveOutClose(hWaveOut);
	//	return;
	//}

	if (waveOutSetVolume(hWaveOut, (DWORD)(0xFFFF*1.0*m_sound/100.0)))
	{
		waveOutClose(hWaveOut);
		return ;
	}

	// 출력 시작
	//if (waveOutWrite(hWaveOut, &WaveOutHdr, sizeof(WAVEHDR)))
	//{
	//	// 에러 콘솔 출력
	//	// 장치 닫기
	//	waveOutClose(hWaveOut);
	//	return ;
	//}
	// WAVE_FORMAT_DIRECT를 선택했기 때문에 출력이 끝날때까지 기다려야 합니다.
	// length로 음성의 길이를 알기 때문에 1초단위로 콘솔에 표시합니다.
	//for (int i = 0; i <= length; i++)
	//{
	//	// 플레이 초 표시
	//	Sleep(1000);
	//}
	// 장치 닫기
	//delete WaveOutHdr.lpData;
	waveOutClose(hWaveOut);
}

int CMFC_AudioDlg::OpenWavFile(const char* filename, WAVEFORMATEX* format, PWAVEHDR WaveHeader)
{
	ifstream istream;
	istream.open(filename, fstream::binary);
	// wav파일 구조체대로 작성한다.
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
	// subchunk1size (무압축 PCM이면 16 고정)
	int subchunk1size;
	istream.read((char*)&subchunk1size, 4);
	// AudioFormat (무압축 PCM이면 1 고정)
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
	// 실제 음악 데이터 읽어오기
	WaveHeader->dwBufferLength = subchunk2size / format->nChannels;
	WaveHeader->lpData = (char*)malloc(WaveHeader->dwBufferLength);
	istream.read(WaveHeader->lpData, WaveHeader->dwBufferLength);
	// 파일 닫기
	istream.close();

	// byteRate는 1초의 데이터 길이
	// WaveHeader->dwBufferLength는 데이터의 전체 길이
	// WaveHeader->dwBufferLength / byteRate는 wav의 음악 길이가 나온다.
	return WaveHeader->dwBufferLength / byteRate;
}

void CMFC_AudioDlg::OnBnClickedButton3()
{
	// 볼륨값 최대로 셋팅
	UpdateData();
	waveOutSetVolume(0, (DWORD)(0xFFFF*1.0*m_sound/100.0));
	PlaySound((LPWSTR)MAKEINTRESOURCE(IDR_WAVE11), NULL, SND_ASYNC | SND_RESOURCE);
}
