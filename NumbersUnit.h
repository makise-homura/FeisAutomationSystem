//---------------------------------------------------------------------------

#ifndef NumbersUnitH
#define NumbersUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include "Excel.h"
#include "Database.h"
#include "CSPIN.h"
//---------------------------------------------------------------------------
bool ExportResults(AnsiString FileName, TPanel *Warning, bool SaveResults, bool Unnormalized, bool AlterSchools = true);
//---------------------------------------------------------------------------
class TNumbersForm : public TForm
{
__published:	// IDE-managed Components
  TGroupBox *GroupNumbers;
  TLabel *Label1;
  TLabel *Label2;
  TEdit *EditAdditionalSolo;
  TButton *ButtonCreateNumbers;
  TEdit *EditAdditionalTeam;
  TSaveDialog *SaveDialogNumbers;
  TGroupBox *GroupSchedule;
  TButton *ButtonCreateSchedule;
  TButton *ButtonClose;
  TPanel *PanelWarning;
  TSaveDialog *SaveDialogSchedule;
  TButton *ButtonCreateEmptyResults;
  TSaveDialog *SaveDialogEmptyResults;
  TButton *ButtonCreateList;
  TSaveDialog *SaveDialogList;
  TButton *ButtonCreateBPIO;
  TSaveDialog *SaveDialogBPIO;
  TButton *ButtonCreateSchools;
  TSaveDialog *SaveDialogSchools;
  TButton *ButtonCreateStageLists;
  TSaveDialog *SaveDialogStageLists;
  TGroupBox *GroupSchoolParam;
  TCSpinEdit *SpinCostReg;
  TLabel *Label3;
  TCSpinEdit *SpinCostSolo;
  TCSpinEdit *SpinCostFigure;
  TLabel *Label4;
  TLabel *Label5;
  TLabel *Label7;
  TLabel *Label6;
  TLabel *Label8;
  TCSpinEdit *SpinCostEuro;
  TCSpinEdit *SpinCostChamp;
  TCSpinEdit *SpinCostPremier;
  TLabel *Label9;
  TCSpinEdit *SpinCostRegNW;
  TCSpinEdit *SpinCostSoloNW;
  TCSpinEdit *SpinCostFigureNW;
  TCSpinEdit *SpinCostPremierNW;
  TCSpinEdit *SpinCostChampNW;
  TCSpinEdit *SpinCostEuroNW;
  TLabel *Label10;
  TCSpinEdit *SpinCostUnlim;
  TCSpinEdit *SpinCostUnlimNW;
  TLabel *Label11;
  TLabel *Label12;
  TLabel *Label13;
  TListBox *ListWIDA;
  TListBox *ListNonWIDA;
  TButton *ButtonToWIDA;
  TButton *ButtonFromWIDA;
  void __fastcall ButtonCreateNumbersClick(TObject *Sender);
  void __fastcall ButtonCloseClick(TObject *Sender);
  void __fastcall ButtonCreateEmptyResultsClick(TObject *Sender);
  void __fastcall ButtonCreateListClick(TObject *Sender);
  void __fastcall ButtonCreateScheduleClick(TObject *Sender);
  void __fastcall ButtonCreateBPIOClick(TObject *Sender);
  void __fastcall ButtonCreateSchoolClick(TObject *Sender);
  void __fastcall ButtonCreateStageListsClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall ButtonFromWIDAClick(TObject *Sender);
  void __fastcall ButtonToWIDAClick(TObject *Sender);
private:	// User declarations
  AnsiString PictureFile;
public:		// User declarations
  __fastcall TNumbersForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNumbersForm *NumbersForm;
//---------------------------------------------------------------------------
#endif
