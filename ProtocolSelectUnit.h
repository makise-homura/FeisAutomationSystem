//---------------------------------------------------------------------------

#ifndef ProtocolSelectUnitH
#define ProtocolSelectUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TProtocolSelectForm : public TForm
{
__published:	// IDE-managed Components
  TRadioGroup *JudgeGroup;
  TRadioGroup *RoundGroup;
  TButton *ButtonOk;
  TButton *ButtonCancel;
private:	// User declarations
public:		// User declarations
  __fastcall TProtocolSelectForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TProtocolSelectForm *ProtocolSelectForm;
//---------------------------------------------------------------------------
#endif
