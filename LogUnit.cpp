//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LogUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLogForm *LogForm;
//---------------------------------------------------------------------------
__fastcall TLogForm::TLogForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TLogForm::ButtonOKClick(TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
