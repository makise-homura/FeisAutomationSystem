//---------------------------------------------------------------------------

#ifndef GroupUnitH
#define GroupUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>

#include "Database.h"
//---------------------------------------------------------------------------
class TGroupForm : public TForm
{
__published:	// IDE-managed Components
  TGroupBox *GroupBoxDances;
  TButton *ButtonJump23;
  TButton *ButtonTrebReel;
  TButton *ButtonBegReel;
  TButton *ButtonBegSingle;
  TButton *ButtonBegLight;
  TButton *ButtonBegSlip;
  TButton *ButtonBegTreble;
  TButton *ButtonBegHorn;
  TButton *ButtonBegTrad;
  TButton *ButtonBegPrem;
  TButton *ButtonPriReel;
  TButton *ButtonPriLight;
  TButton *ButtonPriSingle;
  TButton *ButtonPriSlip;
  TButton *ButtonPriTreble;
  TButton *ButtonPriHorn;
  TButton *ButtonPriTrad;
  TButton *ButtonPriPrem;
  TButton *ButtonIntReel;
  TButton *ButtonIntLight;
  TButton *ButtonIntSingle;
  TButton *ButtonIntSlip;
  TButton *ButtonIntTreb;
  TButton *ButtonIntHorn;
  TButton *ButtonIndTrad;
  TButton *ButtonIntPrem;
  TButton *ButtonOpenReel;
  TButton *ButtonOpenSlip;
  TButton *ButtonOpenTreb;
  TButton *ButtonOpenHorn;
  TButton *ButtonOpenTrad;
  TButton *ButtonPreChamp;
  TButton *ButtonChamp;
  TButton *ButtonModernSet;
  TButton *Button2Hand;
  TButton *Button3Hand;
  TButton *Button4Hand;
  TButton *ButtonCeili;
  TGroupBox *GroupBoxAges;
  TEdit *EditGroup1;
  TLabel *Label1;
  TLabel *Label2;
  TEdit *EditGroup2;
  TEdit *EditGroup3;
  TEdit *EditGroup4;
  TEdit *EditGroup5;
  TEdit *EditGroup6;
  TEdit *EditGroup7;
  TEdit *EditGroup8;
  TEdit *EditGroup9;
  TEdit *EditGroup10;
  TEdit *EditGroup11;
  TEdit *EditGroup12;
  TEdit *EditGroup13;
  TEdit *EditGroup14;
  TEdit *EditGroup15;
  TEdit *EditGroup16;
  TLabel *TotalGroup1;
  TLabel *TotalGroup2;
  TLabel *TotalGroup3;
  TLabel *TotalGroup4;
  TLabel *TotalGroup5;
  TLabel *TotalGroup6;
  TLabel *TotalGroup7;
  TLabel *TotalGroup8;
  TLabel *TotalGroup9;
  TLabel *TotalGroup10;
  TLabel *TotalGroup11;
  TLabel *TotalGroup12;
  TLabel *TotalGroup13;
  TLabel *TotalGroup14;
  TLabel *TotalGroup15;
  TLabel *TotalGroup16;
  TButton *ButtonRenew;
  TStringGrid *AgesGrid;
  TButton *ButtonClose;
  TButton *ButtonBegSoft;
  TButton *ButtonPriSoft;
  TButton *ButtonIntSoft;
  TButton *ButtonBegHard;
  TButton *ButtonPriHard;
  TButton *ButtonIntHard;
  TButton *ButtonOpenHard;
  TButton *ButtonOpenSoft;
  TButton *ButtonInsert;
  TLabel *Label3;
  TLabel *Label4;
  TLabel *Label5;
  TLabel *Label6;
  TLabel *NoGroupWarn;
  TCheckBox *CheckBoxInitial;
  TButton *Button4HandChamp;
  TButton *ButtonCeiliChamp;
  void __fastcall ButtonJump23Click(TObject *Sender);
  void __fastcall ButtonTrebReelClick(TObject *Sender);
  void __fastcall ButtonBegReelClick(TObject *Sender);
  void __fastcall ButtonBegLightClick(TObject *Sender);
  void __fastcall ButtonBegSingleClick(TObject *Sender);
  void __fastcall ButtonBegSlipClick(TObject *Sender);
  void __fastcall ButtonBegHornClick(TObject *Sender);
  void __fastcall ButtonBegTradClick(TObject *Sender);
  void __fastcall ButtonPriLightClick(TObject *Sender);
  void __fastcall ButtonPriSingleClick(TObject *Sender);
  void __fastcall ButtonPriSlipClick(TObject *Sender);
  void __fastcall ButtonPriTrebleClick(TObject *Sender);
  void __fastcall ButtonPriHornClick(TObject *Sender);
  void __fastcall ButtonPriTradClick(TObject *Sender);
  void __fastcall ButtonPriPremClick(TObject *Sender);
  void __fastcall ButtonPreChampClick(TObject *Sender);
  void __fastcall ButtonChampClick(TObject *Sender);
  void __fastcall ButtonIntReelClick(TObject *Sender);
  void __fastcall ButtonIntLightClick(TObject *Sender);
  void __fastcall ButtonIntSingleClick(TObject *Sender);
  void __fastcall ButtonIntSlipClick(TObject *Sender);
  void __fastcall ButtonIntTrebClick(TObject *Sender);
  void __fastcall ButtonIntHornClick(TObject *Sender);
  void __fastcall ButtonIndTradClick(TObject *Sender);
  void __fastcall ButtonIntPremClick(TObject *Sender);
  void __fastcall ButtonOpenReelClick(TObject *Sender);
  void __fastcall ButtonOpenSlipClick(TObject *Sender);
  void __fastcall ButtonOpenTrebClick(TObject *Sender);
  void __fastcall ButtonOpenHornClick(TObject *Sender);
  void __fastcall ButtonOpenTradClick(TObject *Sender);
  void __fastcall ButtonBegTrebleClick(TObject *Sender);
  void __fastcall ButtonModernSetClick(TObject *Sender);
  void __fastcall Button2HandClick(TObject *Sender);
  void __fastcall Button3HandClick(TObject *Sender);
  void __fastcall Button4HandClick(TObject *Sender);
  void __fastcall ButtonCeiliClick(TObject *Sender);
  void __fastcall ButtonPriReelClick(TObject *Sender);
  void __fastcall ButtonBegPremClick(TObject *Sender);
  void __fastcall ButtonBegSoftClick(TObject *Sender);
  void __fastcall ButtonBegHardClick(TObject *Sender);
  void __fastcall ButtonPriSoftClick(TObject *Sender);
  void __fastcall ButtonPriHardClick(TObject *Sender);
  void __fastcall ButtonIntSoftClick(TObject *Sender);
  void __fastcall ButtonIntHardClick(TObject *Sender);
  void __fastcall ButtonOpenSoftClick(TObject *Sender);
  void __fastcall ButtonOpenHardClick(TObject *Sender);
  void __fastcall ButtonInsertClick(TObject *Sender);
  void __fastcall EditEnter(TObject *Sender);
  void __fastcall ButtonRenewClick(TObject *Sender);
  void __fastcall ButtonCloseClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall AgesGridDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
  void __fastcall Button4HandChampClick(TObject *Sender);
  void __fastcall ButtonCeiliChampClick(TObject *Sender);
private:	// User declarations
  TEdit *ReferenceEdits[TotalGroups];
  TLabel *ReferenceLabels[TotalGroups];
  TButton *ReferenceButtons[TotalDancesExt];
  AnsiString Groups[TotalDances][TotalGroups];
  int ActiveEdit;
  bool CheckGroups();
  bool SaveGroups();
  void CopyGroups(enum Dances Source, enum Dances Target);
  bool GroupsDifferent(enum Dances Dance1, enum Dances Dance2);
  void Renew();
  void GroupsToDatabase();
  bool SearchGroupDance(enum Dances Dance, int Age, AnsiString &Group);
  bool SearchGroupRef(int Age, AnsiString &Group);
  AnsiString MakeGroupCounter(int GroupCol, AnsiString Group, AnsiString *Declined, int Count, enum Dances Dance1, enum Dances Dance2, enum Dances Dance3, enum Dances Dance4);
public:		// User declarations
  enum Dances SelectedDance;
  __fastcall TGroupForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGroupForm *GroupForm;
//---------------------------------------------------------------------------
#endif
