//---------------------------------------------------------------------------

#ifndef LogUnitH
#define LogUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TLogForm : public TForm
{
__published:	// IDE-managed Components
  TButton *ButtonOK;
  TMemo *LogMemo;
  void __fastcall ButtonOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TLogForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLogForm *LogForm;
//---------------------------------------------------------------------------
#endif
