// Projet_WindowsPhone.h�: fichier d'en-t�te principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 

// CProjet_WindowsPhoneApp:
// Consultez Projet_WindowsPhone.cpp pour l'impl�mentation de cette classe
//

class CProjet_WindowsPhoneApp : public CWinApp
{
public:
	CProjet_WindowsPhoneApp();
	
// Substitutions
public:
	virtual BOOL InitInstance();

// Impl�mentation

	DECLARE_MESSAGE_MAP()
};

extern CProjet_WindowsPhoneApp theApp;
