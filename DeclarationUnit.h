//---------------------------------------------------------------------------

#ifndef DeclarationUnitH
#define DeclarationUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TDeclarationForm : public TForm
{
__published:	// IDE-managed Components
  TButton *ButtonClose;
  TLabel *Label1;
  TEdit *EditFontSize;
  TButton *ButtonApply;
  TRichEdit *ConclusionText;
  void __fastcall ButtonCloseClick(TObject *Sender);
  void __fastcall ButtonApplyClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TDeclarationForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDeclarationForm *DeclarationForm;
//---------------------------------------------------------------------------
#endif
