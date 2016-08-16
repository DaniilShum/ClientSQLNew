//---------------------------------------------------------------------------
#ifndef client_sqlH
#define client_sqlH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SvcMgr.hpp>
#include <vcl.h>
#include <ADODB.hpp>
#include <DB.hpp>
#include "BSSxml.h"
//---------------------------------------------------------------------------
class TService1 : public TService
{
__published:    // IDE-managed Components
        TADOQuery *ADOQuery1;
        TDataSource *DataSource1;
private:        // User declarations
public:         // User declarations
	__fastcall TService1(TComponent* Owner);
	TServiceController __fastcall GetServiceController(void);

	friend void __stdcall ServiceController(unsigned CtrlCode);
};
//---------------------------------------------------------------------------
extern PACKAGE TService1 *Service1;
//---------------------------------------------------------------------------
#endif
