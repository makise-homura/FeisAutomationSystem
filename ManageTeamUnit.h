//---------------------------------------------------------------------------

#ifndef ManageTeamUnitH
#define ManageTeamUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TManageTeamForm : public TForm
{
__published:	// IDE-managed Components
  TStringGrid *SourceGrid;
  TStringGrid *TargetGrid;
  TButton *ButtonAdd;
  TButton *ButtonRemove;
  TButton *ButtonOK;
  TLabel *LabelSchool;
  TLabel *Label2;
  void __fastcall ButtonAddClick(TObject *Sender);
  void __fastcall ButtonRemoveClick(TObject *Sender);
  void __fastcall ButtonOKClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
  void Renew();
public:		// User declarations
  AnsiString School;
  AnsiString TeamContents;
  __fastcall TManageTeamForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TManageTeamForm *ManageTeamForm;
//---------------------------------------------------------------------------
#endif
