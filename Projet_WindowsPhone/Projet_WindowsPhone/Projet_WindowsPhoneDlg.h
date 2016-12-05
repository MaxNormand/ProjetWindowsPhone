// Projet_WindowsPhoneDlg.h : fichier d'en-tête
//

#pragma once
#include <afxmt.h>
#include "afxwin.h"

// Boîte de dialogue CProjet_WindowsPhoneDlg
class CProjet_WindowsPhoneDlg : public CDialog
{
// Construction
public:
	CProjet_WindowsPhoneDlg(CWnd* pParent = NULL);	// constructeur standard
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedReset();

// Données de boîte de dialogue
	enum { IDD = IDD_PROJET_WINDOWSPHONE_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV

// Implémentation
protected:
	HICON m_hIcon;


	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnStnClickedStatic1();
	afx_msg void OnEnChangeChron();
	wchar_t * getChrono();
	afx_msg void OnBnClickedGPS_b();
	afx_msg void OnLbnSelchangeList1();
	wchar_t * getChronoValue();
//	afx_msg void OnLbnSelchangewnd2();
	afx_msg void OnLbnSelchangewnd2();
};

typedef enum State
{
	ZERO,
	RUN,
	ARRET,
};


class GPS
{
private:
	HANDLE GPSDevice;
	double latitude;
	double longitude;
	wchar_t s[128];
	CMutex * mutex;

public:
	GPS();
	~GPS();

	wchar_t * getGPS();
	HANDLE getGPSDevice();
	void setGPSPos(double new_latitude, double new_longitude);
};

