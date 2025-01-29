//---------------------------------------------------------------------------
#ifndef StartupUnitH
#define StartupUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <Grids.hpp>
#include <Provider.hpp>
#include <ExtCtrls.hpp>
#include "Excel.h"
#include "Database.h"
//---------------------------------------------------------------------------
enum dbops { doNew, doLoad };
//---------------------------------------------------------------------------
class TStartupForm : public TForm
{
__published:	// IDE-managed Components
  TButton *QuitButton;
  TLabel *Label6;
  TEdit *FileField;
  TButton *NewFeisButton;
  TButton *OpenFeisButton;
  TOpenDialog *OpenFeisDialog;
  TSaveDialog *NewFeisDialog;
  TButton *SaveButton;
  TPanel *Warning;
  TButton *LockButton;
  TGroupBox *GroupStage1;
  TGroupBox *GroupStage2;
  TGroupBox *GroupStage3;
  TButton *ImportButton;
  TButton *GroupButton;
  TButton *FilesButton;
  TButton *ResultsButton;
  TButton *ExportButton;
  TSaveDialog *ExportDialogXLS;
  TLabel *Label1;
  TCheckBox *UnnormalizedCheckBox;
  TCheckBox *AlterSchoolsCheckBox;
  void __fastcall QuitButtonClick(TObject *Sender);
  void __fastcall OpenFeisButtonClick(TObject *Sender);
  void __fastcall NewFeisButtonClick(TObject *Sender);
  void __fastcall ImportButtonClick(TObject *Sender);
  void __fastcall GroupButtonClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall ResultsButtonClick(TObject *Sender);
  void __fastcall ExportButtonClick(TObject *Sender);
  void __fastcall SaveButtonClick(TObject *Sender);
  void __fastcall FilesButtonClick(TObject *Sender);
  void __fastcall LockButtonClick(TObject *Sender);
private:	// User declarations
  bool FeisOpened;
  AnsiString Filename;
  void DatabaseInit(enum dbops Operation);
  void OutputDance(TExcel *Excel, enum Dances Dance, AnsiString Header);
public:		// User declarations
  bool SaveDatabase();
  __fastcall TStartupForm(TComponent* Owner);
  __fastcall ~TStartupForm();
};
//---------------------------------------------------------------------------
extern PACKAGE TStartupForm *StartupForm;
//---------------------------------------------------------------------------
#endif
