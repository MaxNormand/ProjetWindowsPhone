// Projet_WindowsPhone.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "Projet_WindowsPhone.h"
#include "Projet_WindowsPhoneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProjet_WindowsPhoneApp

BEGIN_MESSAGE_MAP(CProjet_WindowsPhoneApp, CWinApp)
END_MESSAGE_MAP()


// construction CProjet_WindowsPhoneApp
CProjet_WindowsPhoneApp::CProjet_WindowsPhoneApp()
	: CWinApp()
{
	// TODO : ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CProjet_WindowsPhoneApp
CProjet_WindowsPhoneApp theApp;

// initialisation de CProjet_WindowsPhoneApp

BOOL CProjet_WindowsPhoneApp::InitInstance()
{
    // SHInitExtraControls doit être appelé une fois lors de l'initialisation de votre application afin d'initialiser
    // l'un des contrôles spécifiques à Windows Mobile, tels que CAPEDIT et SIPPREF.
    SHInitExtraControls();

	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalités et que vous souhaitez réduire la taille
	// de votre exécutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation spécifiques dont vous n'avez pas besoin.
	// Changez la clé de Registre sous laquelle nos paramètres sont enregistrés
	// TODO : modifiez cette chaîne avec des informations appropriées,
	// telles que le nom de votre société ou organisation
	SetRegistryKey(_T("Applications locales générées par AppWizard"));

	CProjet_WindowsPhoneDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO : placez ici le code définissant le comportement lorsque la boîte de dialogue est
		//  fermée avec OK
	}

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}
