// Projet_WindowsPhone.cpp : D�finit les comportements de classe pour l'application.
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
	// TODO�: ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CProjet_WindowsPhoneApp
CProjet_WindowsPhoneApp theApp;

// initialisation de CProjet_WindowsPhoneApp

BOOL CProjet_WindowsPhoneApp::InitInstance()
{
    // SHInitExtraControls doit �tre appel� une fois lors de l'initialisation de votre application afin d'initialiser
    // l'un des contr�les sp�cifiques � Windows Mobile, tels que CAPEDIT et SIPPREF.
    SHInitExtraControls();

	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalit�s et que vous souhaitez r�duire la taille
	// de votre ex�cutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation sp�cifiques dont vous n'avez pas besoin.
	// Changez la cl� de Registre sous laquelle nos param�tres sont enregistr�s
	// TODO : modifiez cette cha�ne avec des informations appropri�es,
	// telles que le nom de votre soci�t� ou organisation
	SetRegistryKey(_T("Applications locales g�n�r�es par AppWizard"));

	CProjet_WindowsPhoneDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO�: placez ici le code d�finissant le comportement lorsque la bo�te de dialogue est
		//  ferm�e avec OK
	}

	// Lorsque la bo�te de dialogue est ferm�e, retourner FALSE afin de quitter
	//  l'application, plut�t que de d�marrer la pompe de messages de l'application.
	return FALSE;
}
