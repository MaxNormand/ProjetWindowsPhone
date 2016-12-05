// Projet_WindowsPhoneDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "afxwin.h"
#include "Projet_WindowsPhone.h"
#include "Projet_WindowsPhoneDlg.h"
#include <gpsapi.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int cpt;
wchar_t chrono[11];
State state_chrono;
CMutex * mutex;

struct thread_params
{
	GPS* gps;
}th_params;

GPS* gps;



void CALLBACK display_handler( HWND hwnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime)
{
	wchar_t * chrono_value;
	HWND window_text;

	mutex->Lock();
	swprintf(chrono_value, L"%02d:%02d:%02d:%02d", (cpt / 60000000) % 99, (cpt / 60000) % 60,
		    (cpt / 1000) % 60, (cpt / 10) % 100);
	mutex->Unlock();

	window_text = (HWND) GetDlgItem(hwnd, CHRONO);
	SetWindowText(window_text, chrono_value);
}

wchar_t * getChronoValueee( void)
{
	wchar_t * s;

	mutex->Lock();
	swprintf(s, L"%02d:%02d:%02d:%02d", (cpt / 60000000) % 99, (cpt / 60000) % 60,
		    (cpt / 1000) % 60, (cpt / 10) % 100);
	mutex->Unlock();

	return s;
}


// Déclaration du thread
UINT __cdecl thread_chron_handler( LPVOID param)
{
	// Initialisation
	DWORD nbTicks_old = 0, nbTicks_new= 0;

	while(true)
	{
		nbTicks_new = GetTickCount();

		switch(state_chrono)
		{
		case ZERO :
			cpt = 0;
			break;

		case RUN :
			cpt = cpt + (nbTicks_new - nbTicks_old);
			break;

		case ARRET :
			break;
		}
	
		Sleep(10);
		nbTicks_old = nbTicks_new;
	}
 
	return 0;
}


//Déclaration du thread du GPS
UINT __cdecl thread_gps_handler( LPVOID param)
{
	GPS * gps = (GPS *) param;
	GPS_POSITION gps_pos;
	DWORD donnees;

	memset(&gps_pos, 0, sizeof(gps_pos));
	gps_pos.dwVersion = GPS_VERSION_CURRENT;
	gps_pos.dwSize = sizeof(gps_pos);

	while(true)
	{
		donnees = GPSGetPosition(gps->getGPSDevice(), &gps_pos, 500000, 0);
		gps->setGPSPos(gps_pos.dblLatitude, gps_pos.dblLongitude);
		Sleep(1000);
	}
	return 0;
}

GPS::GPS( void)
{
	CWinThread * thread_gps;

	latitude = 0;
	longitude = 0;

	mutex = new CMutex();

	thread_gps = AfxBeginThread( thread_gps_handler, this);
	
	GPSDevice = GPSOpenDevice( NULL, NULL, NULL, 0);
}

GPS::~GPS( void)
{
	GPSCloseDevice(GPSDevice);
}


wchar_t * GPS::getGPS( void)
{
	mutex->Lock();
	swprintf(s, L"l:%f L:%f", latitude, longitude, sizeof(wchar_t) * 128);
	mutex->Unlock();
	return s;
}

void GPS::setGPSPos(double new_latitude, double new_longitude)
{
	mutex->Lock();
	latitude = new_latitude;
	longitude = new_longitude;
	mutex->Unlock();
}

HANDLE GPS::getGPSDevice()
{
	return GPSDevice;
}




// Boîte de dialogue CProjet_WindowsPhoneDlg

CProjet_WindowsPhoneDlg::CProjet_WindowsPhoneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProjet_WindowsPhoneDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjet_WindowsPhoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CProjet_WindowsPhoneDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(START, &CProjet_WindowsPhoneDlg::OnBnClickedStart)
	ON_BN_CLICKED(RESET, &CProjet_WindowsPhoneDlg::OnBnClickedReset)
	ON_BN_CLICKED(GPS_b, &CProjet_WindowsPhoneDlg::OnBnClickedGPS_b)
//	ON_LBN_SELCHANGE(GPS_wnd2, &CProjet_WindowsPhoneDlg::OnLbnSelchangewnd2)
ON_LBN_SELCHANGE(GPS_wnd2, &CProjet_WindowsPhoneDlg::OnLbnSelchangewnd2)
END_MESSAGE_MAP()


// Gestionnaires de messages pour CProjet_WindowsPhoneDlg

BOOL CProjet_WindowsPhoneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Définir l'icône de cette boîte de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	// TODO : ajoutez ici une initialisation supplémentaire
	
	cpt=0;
	state_chrono = ZERO;
	mutex = new CMutex();

	CWinThread * thread_chrono = AfxBeginThread( thread_chron_handler, this);

	
	try
	{
		gps = new GPS();
	}
	catch( CString const& e)
	{
		printf("%s", e);
		return FALSE;
	}
	th_params.gps = gps;


	SetTimer(1, 5, display_handler);

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}






#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CProjet_WindowsPhoneDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_PROJET_WINDOWSPHONE_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_PROJET_WINDOWSPHONE_DIALOG));
	}
}
#endif

void CProjet_WindowsPhoneDlg::OnBnClickedStart()
{
	CWnd * Bstart = GetDlgItem(START);

	if (state_chrono == ZERO)
	{
		state_chrono = RUN;
		Bstart->SetWindowText(L"Pause");
	}
	else if (state_chrono == ARRET)
	{
		state_chrono = RUN;
		Bstart->SetWindowText(L"Pause");
	}
	else 
	{
		state_chrono = ARRET;
		Bstart->SetWindowText(L"Restart");
	}
}

void CProjet_WindowsPhoneDlg::OnBnClickedReset()
{
	CWnd * Bstart;

	Bstart = GetDlgItem(START);

	Bstart->SetWindowText(L"Start");
	state_chrono = ZERO;
}


void CProjet_WindowsPhoneDlg::OnBnClickedGPS_b()
{
	CListBox * listbox_GPS;
	wchar_t * chrono_value;
	wchar_t * GPS_coord;
	wchar_t GPS_chrono_values[256];

	listbox_GPS = (CListBox *) GetDlgItem(IDC_LIST);

	chrono_value = getChronoValueee();
	GPS_coord = gps->getGPS();

	swprintf(GPS_chrono_values, L"%s ---> %s",chrono_value, GPS_coord);

	//printf("%s", GPS_chrono_values);
    
	listbox_GPS->AddString(GPS_chrono_values);
}



void CProjet_WindowsPhoneDlg::OnLbnSelchangewnd2()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contrôle
}
