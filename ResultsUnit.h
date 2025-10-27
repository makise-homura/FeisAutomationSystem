//---------------------------------------------------------------------------

#ifndef ResultsUnitH
#define ResultsUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>

#include "Database.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
extern const int MaxQualified[TotalDances];
//---------------------------------------------------------------------------
class TFeisEnterForm : public TForm
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
  TButton *ButtonModernSet;
  TButton *ButtonPreChamp;
  TButton *ButtonChamp;
  TButton *Button2Hand;
  TButton *Button3Hand;
  TButton *Button4Hand;
  TButton *ButtonCeili;
  TButton *ButtonAgeGroup1;
  TButton *ButtonAgeGroup2;
  TButton *ButtonAgeGroup3;
  TButton *ButtonAgeGroup4;
  TButton *ButtonAgeGroup5;
  TButton *ButtonAgeGroup6;
  TButton *ButtonAgeGroup7;
  TButton *ButtonAgeGroup8;
  TButton *ButtonAgeGroup9;
  TButton *ButtonAgeGroup10;
  TButton *ButtonAgeGroup11;
  TButton *ButtonAgeGroup12;
  TButton *ButtonAgeGroup13;
  TButton *ButtonAgeGroup14;
  TButton *ButtonAgeGroup15;
  TButton *ButtonAgeGroup16;
  TGroupBox *GroupBoxAges;
  TButton *CountButton;
  TButton *SaveButton;
  TEdit *AddNumberEdit;
  TButton *AddButton;
  TButton *DeleteButton;
  TStringGrid *ResultsGrid;
  TPanel *SaveNotification;
  TButton *CloseButton;
  TButton *HelpButton;
  TButton *ConclusionButton;
  TButton *MergeButton;
  TEdit *AddNameEdit;
  TCheckBox *AllPlacesCheckBox;
  TLabel *Label1;
  TLabel *Label2;
  TButton *ButtonCeiliChamp;
  TButton *Button4HandChamp;
  void __fastcall ButtonJump23Click(TObject *Sender);
  void __fastcall ButtonTrebReelClick(TObject *Sender);
  void __fastcall Button2HandClick(TObject *Sender);
  void __fastcall Button3HandClick(TObject *Sender);
  void __fastcall Button4HandClick(TObject *Sender);
  void __fastcall ButtonCeiliClick(TObject *Sender);
  void __fastcall ButtonBegReelClick(TObject *Sender);
  void __fastcall ButtonBegLightClick(TObject *Sender);
  void __fastcall ButtonBegSingleClick(TObject *Sender);
  void __fastcall ButtonBegSlipClick(TObject *Sender);
  void __fastcall ButtonBegTrebleClick(TObject *Sender);
  void __fastcall ButtonBegHornClick(TObject *Sender);
  void __fastcall ButtonBegTradClick(TObject *Sender);
  void __fastcall ButtonBegPremClick(TObject *Sender);
  void __fastcall ButtonPriReelClick(TObject *Sender);
  void __fastcall ButtonPriLightClick(TObject *Sender);
  void __fastcall ButtonPriSingleClick(TObject *Sender);
  void __fastcall ButtonPriSlipClick(TObject *Sender);
  void __fastcall ButtonPriTrebleClick(TObject *Sender);
  void __fastcall ButtonPriHornClick(TObject *Sender);
  void __fastcall ButtonPriTradClick(TObject *Sender);
  void __fastcall ButtonPriPremClick(TObject *Sender);
  void __fastcall ButtonIntPremClick(TObject *Sender);
  void __fastcall ButtonIndTradClick(TObject *Sender);
  void __fastcall ButtonIntHornClick(TObject *Sender);
  void __fastcall ButtonIntTrebClick(TObject *Sender);
  void __fastcall ButtonIntSlipClick(TObject *Sender);
  void __fastcall ButtonIntSingleClick(TObject *Sender);
  void __fastcall ButtonIntLightClick(TObject *Sender);
  void __fastcall ButtonIntReelClick(TObject *Sender);
  void __fastcall ButtonOpenTradClick(TObject *Sender);
  void __fastcall ButtonOpenHornClick(TObject *Sender);
  void __fastcall ButtonOpenTrebClick(TObject *Sender);
  void __fastcall ButtonOpenSlipClick(TObject *Sender);
  void __fastcall ButtonOpenReelClick(TObject *Sender);
  void __fastcall ButtonModernSetClick(TObject *Sender);
  void __fastcall ButtonPreChampClick(TObject *Sender);
  void __fastcall ButtonChampClick(TObject *Sender);
  void __fastcall ButtonAgeGroup1Click(TObject *Sender);
  void __fastcall ButtonAgeGroup2Click(TObject *Sender);
  void __fastcall ButtonAgeGroup3Click(TObject *Sender);
  void __fastcall ButtonAgeGroup4Click(TObject *Sender);
  void __fastcall ButtonAgeGroup5Click(TObject *Sender);
  void __fastcall ButtonAgeGroup6Click(TObject *Sender);
  void __fastcall ButtonAgeGroup7Click(TObject *Sender);
  void __fastcall ButtonAgeGroup8Click(TObject *Sender);
  void __fastcall ButtonAgeGroup9Click(TObject *Sender);
  void __fastcall ButtonAgeGroup10Click(TObject *Sender);
  void __fastcall ButtonAgeGroup11Click(TObject *Sender);
  void __fastcall ButtonAgeGroup12Click(TObject *Sender);
  void __fastcall ButtonAgeGroup13Click(TObject *Sender);
  void __fastcall ButtonAgeGroup14Click(TObject *Sender);
  void __fastcall ButtonAgeGroup15Click(TObject *Sender);
  void __fastcall ButtonAgeGroup16Click(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall SaveButtonClick(TObject *Sender);
  void __fastcall CloseButtonClick(TObject *Sender);
  void __fastcall DeleteButtonClick(TObject *Sender);
  void __fastcall AddButtonClick(TObject *Sender);
  void __fastcall CountButtonClick(TObject *Sender);
  void __fastcall AddNumberEditChange(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall HelpButtonClick(TObject *Sender);
  void __fastcall ResultsGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
  void __fastcall ConclusionButtonClick(TObject *Sender);
  void __fastcall MergeButtonClick(TObject *Sender);
  void __fastcall AddNameEditChange(TObject *Sender);
  void __fastcall AddNameEditKeyPress(TObject *Sender, char &Key);
  void __fastcall Button4HandChampClick(TObject *Sender);
  void __fastcall ButtonCeiliChampClick(TObject *Sender);
private:	// User declarations
  TButton *ReferenceButtons[TotalDances];
  TButton *ReferenceAgeButtons[TotalGroups];
  enum Dances SelectedDance;
  bool ForceReanalyze;
  bool ForceRedraw;
  bool ReselectGroup;
  int SelectedGroup;
  void Renew();
  void SaveResults();
public:		// User declarations
  __fastcall TFeisEnterForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFeisEnterForm *FeisEnterForm;
//---------------------------------------------------------------------------
#endif
