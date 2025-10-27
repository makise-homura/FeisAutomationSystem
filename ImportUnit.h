//---------------------------------------------------------------------------

#ifndef ImportUnitH
#define ImportUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include "Database.h"
//---------------------------------------------------------------------------
class TImportForm : public TForm
{
__published:	// IDE-managed Components
  TStringGrid *ListGrid;
  TOpenDialog *ImportDialog;
  TGroupBox *ButtonPanel;
  TButton *ImportListButton;
  TButton *ImportSoloButton;
  TRadioGroup *ListChooseGroup;
  TButton *AddLineButton;
  TButton *DeleteLineButton;
  TButton *ExitButton;
  TPanel *ImportWarning;
  TStringGrid *SoloGrid;
  TStringGrid *GroupGrid;
  TButton *DeleteFigureButton;
  TButton *AddFigureButton;
  TButton *CheckRegButton;
  TButton *ManageTeamButton;
  TButton *ResortButton;
  TEdit *AddNameEdit;
  TButton *ResortFigureButton;
        TCheckBox *QualificationCheckBox;
  void __fastcall ImportListButtonClick(TObject *Sender);
  void __fastcall ImportSoloButtonClick(TObject *Sender);
  void __fastcall ExitButtonClick(TObject *Sender);
  void __fastcall DeleteLineButtonClick(TObject *Sender);
  void __fastcall AddLineButtonClick(TObject *Sender);
  void __fastcall ListChooseGroupClick(TObject *Sender);
  void __fastcall AddFigureButtonClick(TObject *Sender);
  void __fastcall DeleteFigureButtonClick(TObject *Sender);
  void __fastcall CheckRegButtonClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall ManageTeamButtonClick(TObject *Sender);
  void __fastcall ResortButtonClick(TObject *Sender);
  void __fastcall AddNameEditChange(TObject *Sender);
  void __fastcall ResortFigureButtonClick(TObject *Sender);
private:	// User declarations
  TList *UIDList, *UIDSolo, *UIDGroup;
  enum ListType CurrentPage;
  bool Import(enum ListType Type);
  bool PerformCheck();
  void TableToDatabase();
  void TableFromDatabase();
  void SwitchToPage();
  bool CheckCurrentTable(bool LimitedCheck);
  /* void ImportGroupDance(enum Dances Dance, int MaxParticipants, TDancer *Dancer, AnsiString &Storage); -- unused */
public:		// User declarations
  __fastcall TImportForm(TComponent* Owner);
  __fastcall ~TImportForm();
};
//---------------------------------------------------------------------------
extern PACKAGE TImportForm *ImportForm;
//---------------------------------------------------------------------------
AnsiString MakeBPIO(bool B, bool P, bool I, bool O);
AnsiString MakeBPIOEx(bool B, AnsiString BS, bool P, AnsiString PS, bool I, AnsiString IS, bool O, AnsiString OS);
//---------------------------------------------------------------------------
#endif
