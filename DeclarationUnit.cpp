//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DeclarationUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDeclarationForm *DeclarationForm;
//---------------------------------------------------------------------------
__fastcall TDeclarationForm::TDeclarationForm(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TDeclarationForm::ButtonCloseClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TDeclarationForm::ButtonApplyClick(TObject *Sender)
{
  int Size = EditFontSize->Text.ToIntDef(0);
  if (Size != 0) ConclusionText->Font->Size = Size;
  else Application->MessageBox("Указан неверный размер шрифта", "Размер шрифта", MB_OK);
}
//---------------------------------------------------------------------------
