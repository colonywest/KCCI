// CTrayNot window

#ifndef CTRAYNOT_h
#define CTRAYNOT_h

class CTrayNot : public CObject
{
// Construction
public:
	CTrayNot ( CWnd* pWnd, UINT uCallbackMessage,
				  LPCTSTR szTip, HICON* pList ) ;

// Attributes
public:
	BOOL			m_bEnabled ;	
	NOTIFYICONDATA	m_tnd ;
	HICON*			m_pIconList ;
	CWnd *			pWnd;

public:
	void SetState ( int id = 0 ) ;
	void Update();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrayNot)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTrayNot();

};

/////////////////////////////////////////////////////////////////////////////
#endif