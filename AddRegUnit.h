//---------------------------------------------------------------------------

#ifndef AddRegUnitH
#define AddRegUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TAddRegForm : public TForm
{
__published:	// IDE-managed Components
  TStringGrid *DancersGrid;
  TButton *AddButton;
  TLabel *Label1;
  TButton *CancelButton;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall CancelButtonClick(TObject *Sender);
  void __fastcall AddButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  bool Selected;
  AnsiString Number;
  AnsiString Name;
  AnsiString School;
  AnsiString Age;
  __fastcall TAddRegForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAddRegForm *AddRegForm;
//---------------------------------------------------------------------------
#endif
