//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ResultsUnit.h"
#include "Grids.h"
#include "Database.h"
#include "StartupUnit.h"
#include "GroupUnit.h"
#include "DeclarationUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFeisEnterForm *FeisEnterForm;
extern TFeisDatabase *Database;
//---------------------------------------------------------------------------
enum DanceType
{
  conv,   // Conventional solo or group dance
  prem,   // Premiership or Preliminary Championship
  champ   // Championship
};

enum QualificationSentence
{
  topri, // "... qualified to Primary level."
  toint,  // "... qualified to Intermediate level."
  toopn, // "... qualified to Open level."
  nomor, // "... will not perform this dance anymore."
  silnt  // do not mean any qualification sentence.
};

const int MaxQualified[TotalDances] =
//  Jump23 ModSet TrReel BgReel BgLigh BgSing BgSlip BgTreb BgHorn BgTrad BgPrem PrReel PrLigh PrSing PrSlip PrTreb PrHorn PrTrad PrPrem
//{ 0,     0,     0,     3,     3,     3,     3,     3,     3,     3,     3,     2,     2,     2,     2,     2,     2,     2,     2, -- current WIDA rules allow only one participant to be qualified
  { 0,     0,     0,     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
//  InReel InLigh InSing InSlip InTreb InHorn InTrad InPrem OpReel OpSlip OpTreb OpHorn OpTrad PreChm Champs 2HandR 3HandR 4HandR 4HandC Ceili  CeiliC
    1,     1,     1,     1,     1,     1,     1,     1,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0     };

const enum DanceType CountTypes[TotalDances] =  /* see also NumbersUnit::MarkType */
//  Jump23 ModSet TrReel BgReel BgLigh BgSing BgSlip BgTreb BgHorn BgTrad BgPrem PrReel PrLigh PrSing PrSlip PrTreb PrHorn PrTrad PrPrem
  { conv,  conv,  conv,  conv,  conv,  conv,  conv,  conv,  conv,  conv,  prem,  conv,  conv,  conv,  conv,  conv,  conv,  conv,  prem,
//  InReel InLigh InSing InSlip InTreb InHorn InTrad InPrem OpReel OpSlip OpTreb OpHorn OpTrad PreChm Champs 2HandR 3HandR 4HandR 4HandC Ceili  CeiliC
    conv,  conv,  conv,  conv,  conv,  conv,  conv,  prem,  conv,  conv,  conv,  conv,  conv,  prem,  champ, conv,  conv,  conv,  prem,  conv,  prem  };

const bool ConclusionAllPlaces[TotalDances] =
//  Jump23 ModSet TrReel BgReel BgLigh BgSing BgSlip BgTreb BgHorn BgTrad BgPrem PrReel PrLigh PrSing PrSlip PrTreb PrHorn PrTrad PrPrem
  { true,  true,  true,  true,  false, false, false, false, false, false, true,  true,  false, false, false, false, false, false, true,
//  InReel InLigh InSing InSlip InTreb InHorn InTrad InPrem OpReel OpSlip OpTreb OpHorn OpTrad PreChm Champs 2HandR 3HandR 4HandR 4HandC Ceili  CeiliC
    true,  false, false, false, false, false, false, true,  true,  false, false, false, false, true,  true,  false, false, false, false, false, false };

const enum QualificationSentence QualificationSentences[TotalDances] =
//  Jump23 ModSet TrReel BgReel BgLigh BgSing BgSlip BgTreb BgHorn BgTrad BgPrem PrReel PrLigh PrSing PrSlip PrTreb PrHorn PrTrad PrPrem
  { silnt, silnt, silnt, topri, topri, topri, topri, topri, topri, topri, topri, toint, toint, toint, toint, toint, toint, toint, toint,
//  InReel InLigh InSing InSlip InTreb InHorn InTrad InPrem OpReel OpSlip OpTreb OpHorn OpTrad PreChm Champs 2HandR 3HandR 4HandR 4HandC Ceili  CeiliC
    toopn, nomor, nomor, toopn, toopn, toopn, toopn, toopn, silnt, silnt, silnt, silnt, silnt, silnt, silnt, silnt, silnt, silnt, silnt, silnt, silnt };

#define MAX_TIE_Y 26
#define MAX_TIE_X 4

int Ties[MAX_TIE_Y][MAX_TIE_X] =
{
  { 10000, 8750, 8000, 7500 },
  {  7500, 7000, 6666, 6400 },
  {  6500, 6250, 6033, 5850 },
  {  6000, 5800, 5633, 5475 },
  {  5600, 5450, 5300, 5150 },
  {  5300, 5150, 5000, 4875 },
  {  5000, 4850, 4733, 4625 },
  {  4700, 4600, 4500, 4350 },
  {  4500, 4400, 4300, 4150 },
  {  4300, 4200, 4100, 4025 },
  {  4100, 4000, 3933, 3875 },
  {  3900, 3850, 3800, 3750 },
  {  3800, 3750, 3700, 3650 },
  {  3700, 3650, 3600, 3550 },
  {  3600, 3550, 3500, 3450 },
  {  3500, 3450, 3400, 3350 },
  {  3400, 3350, 3300, 3250 },
  {  3300, 3250, 3200, 3150 },
  {  3200, 3150, 3100, 3050 },
  {  3100, 3050, 3000, 2950 },
  {  3000, 2950, 2900, 2850 },
  {  2900, 2850, 2800, 2750 },
  {  2800, 2750, 2700, 2650 },
  {  2700, 2650, 2600, 2550 },
  {  2600, 2550, 2500, 2450 },
  {  2500, 2450, 2400, 2350 }
};

//---------------------------------------------------------------------------
__fastcall TFeisEnterForm::TFeisEnterForm(TComponent* Owner) : TForm(Owner)
{
  SelectedDance = Jump23;
  SelectedGroup = 0;

  ReferenceButtons[Jump23]              = ButtonJump23;
  ReferenceButtons[TrebleReel]          = ButtonTrebReel;
  ReferenceButtons[ModernSet]           = ButtonModernSet;
  ReferenceButtons[BeginnerReel]        = ButtonBegReel;
  ReferenceButtons[BeginnerSingleJig]   = ButtonBegSingle;
  ReferenceButtons[BeginnerLightJig]    = ButtonBegLight;
  ReferenceButtons[BeginnerSlipJig]     = ButtonBegSlip;
  ReferenceButtons[BeginnerTrebleJig]   = ButtonBegTreble;
  ReferenceButtons[BeginnerHornpipe]    = ButtonBegHorn;
  ReferenceButtons[BeginnerTradSet]     = ButtonBegTrad;
  ReferenceButtons[BeginnerPremiership] = ButtonBegPrem;
  ReferenceButtons[PrimaryReel]         = ButtonPriReel;
  ReferenceButtons[PrimaryLightJig]     = ButtonPriLight;
  ReferenceButtons[PrimarySingleJig]    = ButtonPriSingle;
  ReferenceButtons[PrimarySlipJig]      = ButtonPriSlip;
  ReferenceButtons[PrimaryTrebleJig]    = ButtonPriTreble;
  ReferenceButtons[PrimaryHornpipe]     = ButtonPriHorn;
  ReferenceButtons[PrimaryTradSet]      = ButtonPriTrad;
  ReferenceButtons[PrimaryPremiership]  = ButtonPriPrem;
  ReferenceButtons[IntermedReel]        = ButtonIntReel;
  ReferenceButtons[IntermedLightJig]    = ButtonIntLight;
  ReferenceButtons[IntermedSingleJig]   = ButtonIntSingle;
  ReferenceButtons[IntermedSlipJig]     = ButtonIntSlip;
  ReferenceButtons[IntermedTrebleJig]   = ButtonIntTreb;
  ReferenceButtons[IntermedHornpipe]    = ButtonIntHorn;
  ReferenceButtons[IntermedTradSet]     = ButtonIndTrad;
  ReferenceButtons[IntermedPremiership] = ButtonIntPrem;
  ReferenceButtons[OpenReel]            = ButtonOpenReel;
  ReferenceButtons[OpenSlipJig]         = ButtonOpenSlip;
  ReferenceButtons[OpenTrebleJig]       = ButtonOpenTreb;
  ReferenceButtons[OpenHornpipe]        = ButtonOpenHorn;
  ReferenceButtons[OpenTradSet]         = ButtonOpenTrad;
  ReferenceButtons[PreChampionship]     = ButtonPreChamp;
  ReferenceButtons[Championship]        = ButtonChamp;
  ReferenceButtons[Group2Hand]          = Button2Hand;
  ReferenceButtons[Group3Hand]          = Button3Hand;
  ReferenceButtons[Group4Hand]          = Button4Hand;
  ReferenceButtons[Group4HandChamp]     = Button4HandChamp;
  ReferenceButtons[GroupCeili]          = ButtonCeili;
  ReferenceButtons[GroupCeiliChamp]     = ButtonCeiliChamp;

  ReferenceAgeButtons[0]                = ButtonAgeGroup1;
  ReferenceAgeButtons[1]                = ButtonAgeGroup2;
  ReferenceAgeButtons[2]                = ButtonAgeGroup3;
  ReferenceAgeButtons[3]                = ButtonAgeGroup4;
  ReferenceAgeButtons[4]                = ButtonAgeGroup5;
  ReferenceAgeButtons[5]                = ButtonAgeGroup6;
  ReferenceAgeButtons[6]                = ButtonAgeGroup7;
  ReferenceAgeButtons[7]                = ButtonAgeGroup8;
  ReferenceAgeButtons[8]                = ButtonAgeGroup9;
  ReferenceAgeButtons[9]                = ButtonAgeGroup10;
  ReferenceAgeButtons[10]               = ButtonAgeGroup11;
  ReferenceAgeButtons[11]               = ButtonAgeGroup12;
  ReferenceAgeButtons[12]               = ButtonAgeGroup13;
  ReferenceAgeButtons[13]               = ButtonAgeGroup14;
  ReferenceAgeButtons[14]               = ButtonAgeGroup15;
  ReferenceAgeButtons[15]               = ButtonAgeGroup16;

  ResultsGrid->Cells[0][0]  = "Номер";
  ResultsGrid->Cells[1][0]  = "Участник";
  ResultsGrid->Cells[2][0]  = "Школа";
  ResultsGrid->ColWidths[0] = 40;
  ResultsGrid->ColWidths[1] = 120;
  ResultsGrid->ColWidths[2] = 200;

  ForceReanalyze = true;
  ForceRedraw    = true;
  ReselectGroup  = true;
}
//---------------------------------------------------------------------------
enum SortType {sgAscending, sgDescending};
void SortGrid(TStringGrid *Grid, int SortColumn, enum SortType Order)
{
  if (Grid->RowCount <= 2) return; // Empty or 1 item

  // Just a simple bubble sort - there is not so much items for speeding sort up
  for(bool repeat = true; repeat;)
  {
    repeat = false;
    for (int i = 2; i < Grid->RowCount; ++i)
    {
      bool DoSwap = false; // No sort on incorrect value
      if (Order == sgDescending)
        DoSwap = (PointsToInt(Grid->Cells[SortColumn][i - 1]) < PointsToInt(Grid->Cells[SortColumn][i]));
      else if (Order == sgAscending)
        DoSwap = (PointsToInt(Grid->Cells[SortColumn][i - 1]) > PointsToInt(Grid->Cells[SortColumn][i]));
      if (DoSwap)
      {
        TStringList *Temp = new TStringList;
        Temp->Assign(Grid->Rows[i - 1]);
        Grid->Rows[i - 1]->Assign(Grid->Rows[i]);
        Grid->Rows[i]->Assign(Temp);
        delete Temp;
        repeat = true;
        break;
      }
    }
  }
}
//---------------------------------------------------------------------------
void ProcessPremiership(TStringGrid *Grid, int Raw, int Normalized)
{
  // Assume that every points record are correct and table is sorted by raw total column
  for (int i = 1; i < Grid->RowCount; ++i)
  {
    int TieY = -1, TieX = -1;
    for (int j = 1; j < Grid->RowCount; ++j)
    {
      if (PointsToInt(Grid->Cells[Raw][i]) == PointsToInt(Grid->Cells[Raw][j]))
      {
        if(TieY == -1) TieY = j - 1; // Y = first position of such place (calculating at first occurence)
        ++TieX;                      // X = number of such places
      }
    }
    if (TieX >= MAX_TIE_X) TieX = MAX_TIE_X;
    if (TieY >= MAX_TIE_Y) TieY = MAX_TIE_Y;
    Grid->Cells[Normalized][i] = PointsToStr(Ties[TieY][TieX]);
  }
}
//---------------------------------------------------------------------------
void AssignPlaces(TStringGrid *Grid, int Points, int Places, bool CheckDups)
{
  // Assume that every points record are correct
  int CurrentPlace = 1, CurrentPoints = PointsToInt(Grid->Cells[Points][1]);
  for (int i = 1; i < Grid->RowCount; ++i)
  {
      if (PointsToInt(Grid->Cells[Points][i]) == CurrentPoints)
        Grid->Cells[Places][i] = CurrentPlace;
      else
      {
        CurrentPoints = PointsToInt(Grid->Cells[Points][i]);
        Grid->Cells[Places][i] = ++CurrentPlace;
      }
  }
  if(CheckDups)
  {
    for (int i = 1; i < Grid->RowCount - 1; ++i)
    {
      if((Grid->Cells[Places][i] == Grid->Cells[Places][i + 1]) && (Grid->Cells[Places][i] <= 3))
      {
        Application->MessageBox("Внимание! В таблице присутствуют участники с одинаковыми баллами за первые три места.\nНеобходимо обратиться к судьям для коррекции.","Пересчёт результатов",MB_OK);
        return;
      }
    }
  }
}
//---------------------------------------------------------------------------
bool SumColumns(TStringGrid *Grid, int Col1, int Col2, int Col3, int Col4, int ColRes, bool Optional)
{
  int Col[4] = {Col1, Col2, Col3, Col4};
  for (int i = 1; i < Grid->RowCount; ++i)
  {
    bool allempty = true, existempty = false;
    int Points, Sum = 0; Grid->Row = i;

    for (int j = 0; j < 4; ++j)
    {
      if(Col[j] != 0)
      {
        Grid->Col = Col[j];
        if(Grid->Cells[Col[j]][i] != "")
        {
          allempty = false;
          Points = PointsToInt(Grid->Cells[Col[j]][i]);
          if ((Points > 100) && (Points < 1000))
            Application->MessageBox("Внимание! В таблице присутствуют баллы от 2 до 9.\nВероятнее всего, где-то была допущена ошибка при вводе - пропущена цифра.","Пересчёт результатов",MB_OK);
          if (Points < 0) return false; else Sum += Points;
        }
        else existempty = true;
      }
    }

    Grid->Col = ColRes;

    if (allempty)
    {
      if (!Optional) return false;
      Points = PointsToInt(Grid->Cells[ColRes][i]);
      if ((Points > 100) && (Points < 1000))
        Application->MessageBox("Внимание! В таблице присутствуют баллы от 2 до 9.\nВероятнее всего, где-то была допущена ошибка при вводе - пропущена цифра.","Пересчёт результатов",MB_OK);
      if (Points < 0) return false;
    }
    else
    {
      if (existempty) return false;
      Grid->Cells[ColRes][i] = PointsToStr(Sum);
    }
  }
  return true;
}
//---------------------------------------------------------------------------
void TFeisEnterForm::SaveResults()
{
  SaveNotification->Show();
  Application->ProcessMessages();

  // Read points data from grid
  if ((ResultsGrid->RowCount != 2) || (ResultsGrid->Cells[0][1] != ""))
  {
    int Dancer, Row;
    for(Row = 1; Row < ResultsGrid->RowCount; ++Row)
    {
      TDancer* D;

      for(Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
      {
        D = Database->GetDancerByIndex(Dancer);
        AnsiString N = ((D->isGroup)? "T" : "");
        N += D->Number;
        if (ResultsGrid->Cells[0][Row] == N) break;
      }

      if (Dancer >= Database->TotalDancers())
      {
        AnsiString msg = "Участник " + ResultsGrid->Cells[1][Row] + " не существует в базе. Его результаты сохранены не будут.";
        Application->MessageBox(msg.c_str(), "Ошибка", MB_OK);
      }
      else
      {
        switch (CountTypes[SelectedDance])
        {
          case champ:
            D->RawPoints[SelectedDance][13] = PointsToInt(ResultsGrid->Cells[16][Row]);
            D->RawPoints[SelectedDance][14] = PointsToInt(ResultsGrid->Cells[17][Row]);
            D->RawPoints[SelectedDance][15] = PointsToInt(ResultsGrid->Cells[18][Row]);
            D->RawPoints[SelectedDance][16] = PointsToInt(ResultsGrid->Cells[19][Row]);
            D->RawPoints[SelectedDance][17] = PointsToInt(ResultsGrid->Cells[20][Row]);
            D->RawPoints[SelectedDance][18] = PointsToInt(ResultsGrid->Cells[21][Row]);
          case prem: // or champ
            D->RawPoints[SelectedDance][2]  = PointsToInt(ResultsGrid->Cells[5][Row]);
            D->RawPoints[SelectedDance][3]  = PointsToInt(ResultsGrid->Cells[6][Row]);
            D->RawPoints[SelectedDance][4]  = PointsToInt(ResultsGrid->Cells[7][Row]);
            D->RawPoints[SelectedDance][5]  = PointsToInt(ResultsGrid->Cells[8][Row]);
            D->RawPoints[SelectedDance][6]  = PointsToInt(ResultsGrid->Cells[9][Row]);
            D->RawPoints[SelectedDance][7]  = PointsToInt(ResultsGrid->Cells[10][Row]);
            D->RawPoints[SelectedDance][8]  = PointsToInt(ResultsGrid->Cells[11][Row]);
            D->RawPoints[SelectedDance][9]  = PointsToInt(ResultsGrid->Cells[12][Row]);
            D->RawPoints[SelectedDance][10] = PointsToInt(ResultsGrid->Cells[13][Row]);
            D->RawPoints[SelectedDance][11] = PointsToInt(ResultsGrid->Cells[14][Row]);
            D->RawPoints[SelectedDance][12] = PointsToInt(ResultsGrid->Cells[15][Row]);
          case conv: // or prem or champ
            D->RawPoints[SelectedDance][0]  = PointsToInt(ResultsGrid->Cells[3][Row]);
            D->RawPoints[SelectedDance][1]  = PointsToInt(ResultsGrid->Cells[4][Row]);
        }

        if (MaxQualified[SelectedDance] > 0)
        {
          D->CalcPoints[SelectedDance] =  PointsToInt(ResultsGrid->Cells[ResultsGrid->ColCount - 4][Row]);
          D->Places[SelectedDance]     =  ResultsGrid->Cells[ResultsGrid->ColCount - 3][Row].ToIntDef(0);
          D->Qualified[SelectedDance]  = (ResultsGrid->Cells[ResultsGrid->ColCount - 2][Row] == "+");
          D->Comment[SelectedDance]    =  ResultsGrid->Cells[ResultsGrid->ColCount - 1][Row];
        }
        else
        {
          D->CalcPoints[SelectedDance] =  PointsToInt(ResultsGrid->Cells[ResultsGrid->ColCount - 3][Row]);
          D->Places[SelectedDance]     =  ResultsGrid->Cells[ResultsGrid->ColCount - 2][Row].ToIntDef(0);
          D->Comment[SelectedDance]    =  ResultsGrid->Cells[ResultsGrid->ColCount - 1][Row];
        }
      }
    }
  }

  // Write database to disk
  if(!StartupForm->SaveDatabase())
  {
    Application->MessageBox("Невозможно сохранить файл феша!","Ошибка",MB_OK);
    return;
  }
  SaveNotification->Hide();
}
//---------------------------------------------------------------------------
void TFeisEnterForm::Renew()
{
  int Dance, Dancer, Group; bool CanOperate = false;

  // Stage A. Full renew with detection of permitted dances
  if (ForceReanalyze)
  {
    // TODO optional: deal with a condition where no participants not just on form show, as here, but on delete last participant also.

    // Stage A1: Check which competitions have participants
    for (Dance = 0; Dance < TotalDances; ++Dance)
    {
      bool Participants = false;
      for(Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
        if (Database->GetDancerByIndex(Dancer)->Dances[Dance]) { CanOperate = true; Participants = true; break; }
      ReferenceButtons[Dance]->Enabled = Participants;
    }

    // Stage A2: Check if really we had any participants
    if (!CanOperate)
    {
      Application->MessageBox("На феше нет участников с заявленными танцами","Феш провести невозможно",MB_OK);
      Close();
      return;
    }

    // Stage A3: Alter SelectedDance if it is no more possible
    while (!ReferenceButtons[SelectedDance]->Enabled)
    {
      (*(int*)&SelectedDance) += 1; // ++ doesn't work with enum
      if (SelectedDance >= TotalDances) SelectedDance = Jump23; // First dance in list
    }

    // Stage A4: Commit request for reanalyze
    ForceReanalyze = false;
  }

  // Stage B. Redraw age groups for a newly selected dance
  if (ForceRedraw)
  {
    // Stage B1: Select button of current dance, deselect all others
    for (Dance = 0; Dance < TotalDances; ++Dance)
    {
      ReferenceButtons[Dance]->Font->Style = TFontStyles();
    }
    ReferenceButtons[SelectedDance]->Font->Style = TFontStyles() << fsBold;

    // Stage B2: Clear all previous age group definitions
    for (Group = 0; Group < TotalGroups; ++Group)
      ReferenceAgeButtons[Group]->Caption = "";

    // Stage B3: Determine what age groups we have for a dance and show such buttons
    for(Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
    {
      TDancer *D = Database->GetDancerByIndex(Dancer);

      if(D->Dances[SelectedDance])
      {
        // Dancer have no age group - we should fix it
        if (D->AgeGroup[SelectedDance] == "")
        {
          AnsiString msg = "Участник " + D->Name + " танцует " + ReferenceButtons[SelectedDance]->Caption + ", но у него пустая возрастная группа.\nПроверьте этот танец в окне \"Разбивка на группы\" (сейчас это окно будет открыто).";
          Application->MessageBox(msg.c_str(),"Отсутствует возрастная группа",MB_OK);

          // Fix an error
          GroupForm->SelectedDance = SelectedDance;
          GroupForm->ShowModal();

          // Retry
          --Dancer; continue;
        }

        // If no dancer's age group exist in this dance, add it to button list for that dance
        bool exist = false;
        for (Group = 0; Group < TotalGroups; ++Group)
        {
          if (D->AgeGroup[SelectedDance] == ReferenceAgeButtons[Group]->Caption) { exist = true; break; }
        }
        if (!exist)
        {
          // We assume that database is consistent (it may be checked using group dialog)
          if (D->AgeGroup[SelectedDance] == "AA") ReferenceAgeButtons[0]->Caption = "AA";
          else if (GetGroupType(D->AgeGroup[SelectedDance]) == 'O')
          {
            for (Group = 0; Group < TotalGroups; ++Group)
              if (ReferenceAgeButtons[Group]->Caption == "")
              {
                ReferenceAgeButtons[Group]->Caption = D->AgeGroup[SelectedDance]; break;
              }
          }
          else
          {
            for (Group = 0; Group < TotalGroups; ++Group)
            {
              if (ReferenceAgeButtons[Group]->Caption == "") break;
              if (GetGroupAge(ReferenceAgeButtons[Group]->Caption) >= GetGroupAge(D->AgeGroup[SelectedDance])) break;
            }
            if (Group < TotalGroups)
            {
              for (int ShiftGroup = TotalGroups - 2; ShiftGroup >= Group; --ShiftGroup)
                ReferenceAgeButtons[ShiftGroup + 1]->Caption = ReferenceAgeButtons[ShiftGroup]->Caption;
              ReferenceAgeButtons[Group]->Caption = D->AgeGroup[SelectedDance];
            }
            else
            {
              AnsiString msg = "База групп танца " + ReferenceButtons[Dance]->Caption + " повреждена";
              Application->MessageBox(msg.c_str(),"Ошибка базы данных",MB_OK);
            }
          }
        }
      }
    }

    // Stage B4: Set "AA" if there were no group defined
    if (ReferenceAgeButtons[0]->Caption == "")
      ReferenceAgeButtons[0]->Caption = "AA";

    // Stage B5: Draw buttons for registered age groups
    for (Group = 0; Group < TotalGroups; ++Group)
      ReferenceAgeButtons[Group]->Visible = (ReferenceAgeButtons[Group]->Caption != "");

    // Stage B6: Select the first age group
    if (ReselectGroup) SelectedGroup = 0;

    // Stage B7: Enable or disable quicksearch field
    AddNameEdit->Enabled = !isGroupDance(SelectedDance);
    AddNameEdit->Color = isGroupDance(SelectedDance)? clBtnFace : clWindow;

    // Stage B8: Commit request for redraw
    ForceRedraw = false;
  }

  // Stage C: Redraw only participants list on selection of any age group in a dance

  // Stage C1: Select button of current age group, deselect all others; enable or disable merge button
  for (Group = 0; Group < TotalGroups; ++Group)
  {
    ReferenceAgeButtons[Group]->Font->Style = TFontStyles();
  }
  ReferenceAgeButtons[SelectedGroup]->Font->Style = TFontStyles() << fsBold;
  MergeButton->Enabled = true;
  if (SelectedGroup == TotalGroups - 1) MergeButton->Enabled = false;
  else if (ReferenceAgeButtons[SelectedGroup + 1]->Caption == "") MergeButton->Enabled = false;

  // Stage C2: Clear the participants list
  ResultsGrid->RowCount = 2;
  ResultsGrid->Rows[1]->Clear();

  // Stage C3: Prepare column data
  switch (CountTypes[SelectedDance])
  {
    case conv:
      ResultsGrid->ColCount      = 6;
      ResultsGrid->Cells[3][0]   = "T";
      ResultsGrid->Cells[4][0]   = "Р";
      ResultsGrid->Cells[5][0]   = "М";
    break;
    case prem:
      ResultsGrid->ColCount      = 17;
      ResultsGrid->Cells[3][0]   = "1:I";
      ResultsGrid->Cells[4][0]   = "1:II";
      ResultsGrid->Cells[5][0]   = "1:Т";
      ResultsGrid->Cells[6][0]   = "1:P";
      ResultsGrid->Cells[7][0]   = "2:I";
      ResultsGrid->Cells[8][0]   = "2:II";
      ResultsGrid->Cells[9][0]   = "2:T";
      ResultsGrid->Cells[10][0]  = "2:P";
      ResultsGrid->Cells[11][0]  = "3:I";
      ResultsGrid->Cells[12][0]  = "3:II";
      ResultsGrid->Cells[13][0]  = "3:T";
      ResultsGrid->Cells[14][0]  = "3:P";
      ResultsGrid->Cells[15][0]  = "Р";
      ResultsGrid->Cells[16][0]  = "М";
    break;
    case champ:
      ResultsGrid->ColCount      = 23;
      ResultsGrid->Cells[3][0]   = "1:I";
      ResultsGrid->Cells[4][0]   = "1:II";
      ResultsGrid->Cells[5][0]   = "1:III";
      ResultsGrid->Cells[6][0]   = "1:IV";
      ResultsGrid->Cells[7][0]   = "1:T";
      ResultsGrid->Cells[8][0]   = "1:P";
      ResultsGrid->Cells[9][0]   = "2:I";
      ResultsGrid->Cells[10][0]  = "2:II";
      ResultsGrid->Cells[11][0]  = "2:III";
      ResultsGrid->Cells[12][0]  = "2:IV";
      ResultsGrid->Cells[13][0]  = "2:T";
      ResultsGrid->Cells[14][0]  = "2:P";
      ResultsGrid->Cells[15][0]  = "3:I";
      ResultsGrid->Cells[16][0]  = "3:II";
      ResultsGrid->Cells[17][0]  = "3:III";
      ResultsGrid->Cells[18][0]  = "3:IV";
      ResultsGrid->Cells[19][0]  = "3:T";
      ResultsGrid->Cells[20][0]  = "3:P";
      ResultsGrid->Cells[21][0]  = "Р";
      ResultsGrid->Cells[22][0]  = "М";
    break;
  }

  // Stage C4: Add qualification column
  if (MaxQualified[SelectedDance] > 0)
  {
    ++ResultsGrid->ColCount;
    ResultsGrid->Cells[ResultsGrid->ColCount - 1][0] = "П";
  }

  // Stage C5: Add comments column
  ++ResultsGrid->ColCount;
  if (ResultsGrid->ColCount > 6)  ResultsGrid->ColWidths[6]  = ResultsGrid->DefaultColWidth;
  if (ResultsGrid->ColCount > 7)  ResultsGrid->ColWidths[7]  = ResultsGrid->DefaultColWidth;
  if (ResultsGrid->ColCount > 17) ResultsGrid->ColWidths[17] = ResultsGrid->DefaultColWidth;
  ResultsGrid->Cells[ResultsGrid->ColCount - 1][0]  = "Комментарии";
  ResultsGrid->ColWidths[ResultsGrid->ColCount - 1] = 200;

  // Stage C6: Fill participants list
  for(Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
  {
    TDancer* D = Database->GetDancerByIndex(Dancer);
    if (D->Dances[SelectedDance] && (D->AgeGroup[SelectedDance] == ReferenceAgeButtons[SelectedGroup]->Caption))
    {
      // No solo dancers in group tables (as in GroupUnit) and so as opposite.
      if ( isGroupDance(SelectedDance) && !D->isGroup) continue;
      if (!isGroupDance(SelectedDance) &&  D->isGroup) continue;

      if ((ResultsGrid->RowCount != 2) || (ResultsGrid->Cells[1][1] != ""))
        ++ResultsGrid->RowCount;
      int row = ResultsGrid->RowCount - 1;

      AnsiString N = (D->isGroup ? "T" : "");
      N += D->Number;

      ResultsGrid->Cells[0][row]  = N;
      ResultsGrid->Cells[1][row]  = D->Name;
      ResultsGrid->Cells[2][row]  = D->School;

      switch (CountTypes[SelectedDance])
      {
        case champ:
          ResultsGrid->Cells[16][row] = PointsToStr(D->RawPoints[SelectedDance][13]);
          ResultsGrid->Cells[17][row] = PointsToStr(D->RawPoints[SelectedDance][14]);
          ResultsGrid->Cells[18][row] = PointsToStr(D->RawPoints[SelectedDance][15]);
          ResultsGrid->Cells[19][row] = PointsToStr(D->RawPoints[SelectedDance][16]);
          ResultsGrid->Cells[20][row] = PointsToStr(D->RawPoints[SelectedDance][17]);
          ResultsGrid->Cells[21][row] = PointsToStr(D->RawPoints[SelectedDance][18]);
        case prem: // or champ
          ResultsGrid->Cells[5][row]  = PointsToStr(D->RawPoints[SelectedDance][2]);
          ResultsGrid->Cells[6][row]  = PointsToStr(D->RawPoints[SelectedDance][3]);
          ResultsGrid->Cells[7][row]  = PointsToStr(D->RawPoints[SelectedDance][4]);
          ResultsGrid->Cells[8][row]  = PointsToStr(D->RawPoints[SelectedDance][5]);
          ResultsGrid->Cells[9][row]  = PointsToStr(D->RawPoints[SelectedDance][6]);
          ResultsGrid->Cells[10][row] = PointsToStr(D->RawPoints[SelectedDance][7]);
          ResultsGrid->Cells[11][row] = PointsToStr(D->RawPoints[SelectedDance][8]);
          ResultsGrid->Cells[12][row] = PointsToStr(D->RawPoints[SelectedDance][9]);
          ResultsGrid->Cells[13][row] = PointsToStr(D->RawPoints[SelectedDance][10]);
          ResultsGrid->Cells[14][row] = PointsToStr(D->RawPoints[SelectedDance][11]);
          ResultsGrid->Cells[15][row] = PointsToStr(D->RawPoints[SelectedDance][12]);
        case conv: // or prem or champ
          ResultsGrid->Cells[3][row]  = PointsToStr(D->RawPoints[SelectedDance][0]);
          ResultsGrid->Cells[4][row]  = PointsToStr(D->RawPoints[SelectedDance][1]);
      }

      if (MaxQualified[SelectedDance] > 0)
      {
        ResultsGrid->Cells[ResultsGrid->ColCount - 4][row]  = PointsToStr(D->CalcPoints[SelectedDance]);
        ResultsGrid->Cells[ResultsGrid->ColCount - 3][row]  = D->Places[SelectedDance];
        ResultsGrid->Cells[ResultsGrid->ColCount - 2][row]  = D->Qualified[SelectedDance]? "+" : "";
        ResultsGrid->Cells[ResultsGrid->ColCount - 1][row]  = D->Comment[SelectedDance];
      }
      else
      {
        ResultsGrid->Cells[ResultsGrid->ColCount - 3][row]  = PointsToStr(D->CalcPoints[SelectedDance]);
        ResultsGrid->Cells[ResultsGrid->ColCount - 2][row]  = D->Places[SelectedDance];
        ResultsGrid->Cells[ResultsGrid->ColCount - 1][row]  = D->Comment[SelectedDance];
      }

    }
  }

  // Stage C7: Sort by place
  if (MaxQualified[SelectedDance] > 0) SortGrid(ResultsGrid, ResultsGrid->ColCount - 3, sgAscending);
  else SortGrid(ResultsGrid, ResultsGrid->ColCount - 2, sgAscending);

  // Stage C8: Empty quicksearch fields
  AddNameEdit->OnChange = NULL;
  AddNameEdit->Text = "";
  AddNameEdit->OnChange = AddNameEditChange;
  AddNumberEdit->OnChange = NULL;
  AddNumberEdit->Text="";
  AddNumberEdit->OnChange = AddNumberEditChange;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonJump23Click(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = Jump23; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonTrebReelClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = TrebleReel; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonBegReelClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = BeginnerReel; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonBegLightClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = BeginnerLightJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonBegSingleClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = BeginnerSingleJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonBegSlipClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = BeginnerSlipJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonBegHornClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = BeginnerHornpipe; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonBegTradClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = BeginnerTradSet; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonPriLightClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = PrimaryLightJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonPriSingleClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = PrimarySingleJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonPriSlipClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = PrimarySlipJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonPriTrebleClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = PrimaryTrebleJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonPriHornClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = PrimaryHornpipe; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonPriTradClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = PrimaryTradSet; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonPriPremClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = PrimaryPremiership; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonPreChampClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = PreChampionship; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonChampClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = Championship; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonIntReelClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = IntermedReel; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonIntLightClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = IntermedLightJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonIntSingleClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = IntermedSingleJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonIntSlipClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = IntermedSlipJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonIntTrebClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = IntermedTrebleJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonIntHornClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = IntermedHornpipe; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonIndTradClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = IntermedTradSet; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonIntPremClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = IntermedPremiership; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonOpenReelClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = OpenReel; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonOpenSlipClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = OpenSlipJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonOpenTrebClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = OpenTrebleJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonOpenHornClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = OpenHornpipe; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonOpenTradClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = OpenTradSet; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::Button2HandClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = Group2Hand; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::Button3HandClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = Group3Hand; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::Button4HandClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = Group4Hand; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::Button4HandChampClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = Group4HandChamp; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonCeiliClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = GroupCeili; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonCeiliChampClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = GroupCeiliChamp; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonBegTrebleClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = BeginnerTrebleJig; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonPriReelClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = PrimaryReel; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonBegPremClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = BeginnerPremiership; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonModernSetClick(TObject *Sender)
{
  SaveResults(); ForceRedraw = true; SelectedDance = ModernSet; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup1Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 0; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup2Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 1; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup3Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 2; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup4Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 3; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup5Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 4; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup6Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 5; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup7Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 6; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup8Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 7; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup9Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 8; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup10Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 9; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup11Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 10; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup12Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 11; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup13Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 12; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup14Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 13; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup15Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 14; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ButtonAgeGroup16Click(TObject *Sender)
{
  SaveResults(); SelectedGroup = 15; Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::FormShow(TObject *Sender)
{
  ForceReanalyze = true;
  ForceRedraw    = true;
  Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::SaveButtonClick(TObject *Sender)
{
  SaveResults();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::CloseButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  SaveResults();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::DeleteButtonClick(TObject *Sender)
{
  SaveResults();
  AnsiString Message = "Удалить участника \"" + ResultsGrid->Cells[1][ResultsGrid->Row] + "\" из танца?\nЕсли ему уже проставлены оценки, не забудьте нажать кнопку\"Пересчитать\"!";
  int q = Application->MessageBox(Message.c_str(),"Удалить танцора",MB_YESNO);
  if (q != IDYES) return;

  TDancer *D = Database->GetDancerByNumber(ResultsGrid->Cells[0][ResultsGrid->Row]);
  if (D == NULL)
  {
    // This should not occur, but if so, avoid exception and indicate this
    Application->MessageBox("Ошибка удаления участника: участник в базе феша не найден.","Неверный номер",MB_OK);
    return;
  }
  D->Dances[SelectedDance]   = false;
  D->AgeGroup[SelectedDance] = "";

  Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::AddButtonClick(TObject *Sender)
{
  SaveResults();

  if(AddNumberEdit->Text == "")
  {
    Application->MessageBox("Введите номер участника или танцевальной команды в поле ввода рядом с кнопкой.", "Неверный номер", MB_OK);
    ActiveControl = AddNumberEdit;
    return;
  }

  TDancer *D = Database->GetDancerByNumber(AddNumberEdit->Text);

  // Check if no such dancer
  if (D == NULL)
  {
    int Number = 0;
    if(isGroupDance(SelectedDance))
    {
      AnsiString T = "";
      if (AddNumberEdit->Text.Length() > 1)
      {
        T      = AddNumberEdit->Text.SubString(1, 1);
        Number = AddNumberEdit->Text.SubString(2, AddNumberEdit->Text.Length() - 1).ToIntDef(0);
      }
      if ((Number <= 0) || (T != "T"))
      {
        Application->MessageBox("Неверный номер танцевальной команды.", "Неверный номер", MB_OK);
        ActiveControl = AddNumberEdit;
        return;
      }
    }
    else
    {
      Number = AddNumberEdit->Text.ToIntDef(0);
      if (Number <= 0)
      {
        Application->MessageBox("Неверный номер участника сольного танца.", "Неверный номер", MB_OK);
        ActiveControl = AddNumberEdit;
        return;
      }
    }

    int result = Application->MessageBox("Этот участник не зарегистрирован на феш.\nДобавить нового участника?\nВам необходимо будет после феша ввести его данные (имя-фамилию, школу, возраст) в окне импорта и редактирования.","Добавление участника",MB_YESNO);
    if (result == IDNO) return;
    TDancer *Dancer = Database->AddNewDancer();
    Dancer->Number  = Number;
    Dancer->isGroup = isGroupDance(SelectedDance);
    Dancer->Name    = "(неизвестный участник)";
    Dancer->School  = "(неизвестная школа)";
    Dancer->Age     = 0;
    Dancer->Dances[SelectedDance]   = true;
    Dancer->AgeGroup[SelectedDance] = ReferenceAgeButtons[SelectedGroup]->Caption;
    Renew();
    return;
  }

  // Check if it is proper type of dancer
  if ((isGroupDance(SelectedDance) && !D->isGroup) || (!isGroupDance(SelectedDance) && D->isGroup))
  {
    Application->MessageBox("Нельзя добавить сольного танцора в групповой танец и наоборот.", "Неправильный тип участника", MB_OK);
    return;
  }

  // Check if we really need to add dancer
  if(D->Dances[SelectedDance])
  {
    Application->MessageBox("Этот участник уже танцует этот танец в этой или другой возрастной группе.", "Неправильный номер участника", MB_OK);
    return;
  }

  // Determine required dancer age group (assuming that groups are correct)
  AnsiString DetectedGroup = "";
  if (D->isGroup) DetectedGroup = ReferenceAgeButtons[SelectedGroup]->Caption;
  else
  {
    if (ReferenceAgeButtons[0]->Caption == "AA") DetectedGroup = "AA";
    else
    {
      for (int Group = 0; Group < TotalGroups; ++Group)
      {
        AnsiString PossibleGroup = ReferenceAgeButtons[Group]->Caption;
        if (GetGroupType(PossibleGroup) == 'O') { DetectedGroup = PossibleGroup; break; }
        else if (D->Age < GetGroupAge(PossibleGroup)) { DetectedGroup = PossibleGroup; break; }
      }
      if (DetectedGroup == "")
      {
        Application->MessageBox("Неправильно указан возраст участника. Исправьте его на странице импорта и редактирования.\nУчастник будет добавлен в текущую группу - проверьте потом, правильно ли это.", "Неправильный возраст участника", MB_OK);
        DetectedGroup = ReferenceAgeButtons[SelectedGroup]->Caption;
      }
    }
  }

  // Deal with situation of incorrect age group
  if (DetectedGroup != ReferenceAgeButtons[SelectedGroup]->Caption)
  {
    int result = Application->MessageBox("Этот участник должен танцевать этот танец в другой возрастной группе.\nДобавить его именно в текущую группу, несмотря на это?\n(\"Да\" - добавить в эту, \"Нет\" - добавить в правильную, \"Отмена\" - не добавлять)","Добавление участника",MB_YESNOCANCEL);
    if (result == IDCANCEL) return;
    if (result == IDYES) DetectedGroup = ReferenceAgeButtons[SelectedGroup]->Caption;
  }

  // Add dancer to a group and a dance
  D->Dances[SelectedDance] = true;
  D->AgeGroup[SelectedDance] = DetectedGroup;

  Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::CountButtonClick(TObject *Sender)
{
  int SaveRow = ResultsGrid->Row, SaveCol = ResultsGrid->Col;
  SaveResults();
  if (IsTableEmpty(ResultsGrid))
  {
    Application->MessageBox("Не у кого считать баллы","Ошибка подсчета баллов",MB_OK);
    return;
  }

  switch (CountTypes[SelectedDance])
  {
    case conv:
      if(!SumColumns(ResultsGrid, 3, 0, 0, 0, 4, false)) break;     // T -> P
      SortGrid(ResultsGrid, 4, sgDescending);
      AssignPlaces(ResultsGrid, 4, 5, false);
      if (MaxQualified[SelectedDance] > 0)
      {
        int Qualified = 3;
        if (ResultsGrid->RowCount < 16) Qualified = 2;
        if (ResultsGrid->RowCount < 11) Qualified = 1;
        if (ResultsGrid->RowCount < 6)  Qualified = 0;
        if (Qualified > MaxQualified[SelectedDance]) Qualified = MaxQualified[SelectedDance];
        for (int i = 1; i < ResultsGrid->RowCount; ++i)
          ResultsGrid->Cells[6][i] = (ResultsGrid->Cells[5][i].ToInt() <= Qualified) ? "+" : "";
      }
      ResultsGrid->Row = SaveRow;
      ResultsGrid->Col = SaveCol;
      SaveResults();
      return;
    case prem:
      if(!SumColumns(ResultsGrid, 3,  4,  0, 0, 5,  true)) break;   // Rounds -> T1
      if(!SumColumns(ResultsGrid, 7,  8,  0, 0, 9,  true)) break;   // Rounds -> T2
      if(!SumColumns(ResultsGrid, 11, 12, 0, 0, 13, true)) break;   // Rounds -> T3
      SortGrid(ResultsGrid, 5, sgDescending);
      ProcessPremiership(ResultsGrid, 5, 6);                        // T1 -> P1
      SortGrid(ResultsGrid, 9, sgDescending);
      ProcessPremiership(ResultsGrid, 9, 10);                       // T2 -> P2
      SortGrid(ResultsGrid, 13, sgDescending);
      ProcessPremiership(ResultsGrid, 13, 14);                      // T3 -> P3
      SumColumns(ResultsGrid, 6, 10, 14, 0, 15, false);             // P1,P2,P3 -> P
      SortGrid(ResultsGrid, 15, sgDescending);
      AssignPlaces(ResultsGrid, 15, 16, true);
      if (MaxQualified[SelectedDance] > 0)
      {
        int Qualified = 3;
        if (ResultsGrid->RowCount < 16) Qualified = 2;
        if (ResultsGrid->RowCount < 11) Qualified = 1;
        if (ResultsGrid->RowCount < 6)  Qualified = 0;
        if (Qualified > MaxQualified[SelectedDance]) Qualified = MaxQualified[SelectedDance];
        for (int i = 1; i < ResultsGrid->RowCount; ++i)
          ResultsGrid->Cells[17][i] = (ResultsGrid->Cells[16][i].ToInt() <= Qualified) ? "+" : "";
      }
      ResultsGrid->Row = SaveRow;
      ResultsGrid->Col = SaveCol;
      SaveResults();
      return;
    case champ:
      if(!SumColumns(ResultsGrid, 3,  4,  5,  6,  7,  true)) break; // Rounds -> T1
      if(!SumColumns(ResultsGrid, 9,  10, 11, 12, 13, true)) break; // Rounds -> T2
      if(!SumColumns(ResultsGrid, 15, 16, 17, 18, 19, true)) break; // Rounds -> T3
      SortGrid(ResultsGrid, 7, sgDescending);
      ProcessPremiership(ResultsGrid, 7, 8);                        // T1 -> P1
      SortGrid(ResultsGrid, 13, sgDescending);
      ProcessPremiership(ResultsGrid, 13, 14);                      // T2 -> P2
      SortGrid(ResultsGrid, 19, sgDescending);
      ProcessPremiership(ResultsGrid, 19, 20);                      // T3 -> P3
      SumColumns(ResultsGrid, 8, 14, 20, 0, 21, false);             // P1,P2,P3 -> P
      SortGrid(ResultsGrid, 21, sgDescending);
      AssignPlaces(ResultsGrid, 21, 22, true);
      ResultsGrid->Row = SaveRow;
      ResultsGrid->Col = SaveCol;
      SaveResults();
      return;
  }
  Application->MessageBox("Неверные данные в таблице. Подсчет остановлен на выделенной ячейке.","Ошибка подсчета баллов",MB_OK);
  ActiveControl = ResultsGrid;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::HelpButtonClick(TObject *Sender)
{
  Application->MessageBox("\
Принцип ввода результатов:\n\
1.  Выберите нужный танец в верхней группе кнопок;\n\
2.  Выберите нужную возрастную группу в нижней группе кнопок;\n\
3.  Снизу появится таблица для ввода результатов;\n\
4.  Если какой-то участник по какой-то причине не танцует танец - его надо удалить, выделив строку с его данными и нажав \"Удалить выделенного танцора из списка\";\n\
5.  Если вдруг танец танцует не заявленный ранее участник - его следует добавить, введя его номер в поле рядом с кнопкой \"Добавить нового участника\" (рядом будет показано его имя) и нажать кнопку;\n\
6.  Результаты вводятся только в колонки с белым фоном; содержимое серых колонок перезаписывается при пересчете баллов и мест;\n\
7.  Результаты вводятся в колонку \"Т\" для всех сольных и групповых танцев;\n\
8.  Для многораундовых танцев (Premiership, Preliminary Championship, Championship) результаты вводятся по каждому судье ИЛИ в каждую колонку по раундам, ИЛИ в колонку \"Т\", если указана только общая сумма.\n\
9.  После ввода результатов следует нажать кнопку \"Подсчитать результаты\".\n\
10. Программа заполнит колонку \"Т\" для судьи (если она не заполнена), колонку \"Р\" (результирующие очки - имеет смысл в многораундовых танцах), расставит места в колонку \"М\", а также, если танец предусматривает переход, в колонку \"П\" поставит \"+\" у танцоров, перешедших в следующую категорию.\n\
11. Программа сохраняет данные в файл феша после каждого выбора нового танца и после каждого пересчета результатов.\
","Справка",MB_OK);
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ResultsGridDrawCell(TObject *Sender,
      int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
  bool fill[23];
  for (int i = 0; i < ResultsGrid->ColCount; ++i) fill[i] = false;
  switch (CountTypes[SelectedDance])
  {
    case conv:
      fill[4] = true;
      fill[5] = true;
      if (MaxQualified[SelectedDance] > 0) fill[6] = true;
    break;
    case prem:
      fill[6]  = true;
      fill[10] = true;
      fill[14] = true;
      fill[15] = true;
      fill[16] = true;
      if (MaxQualified[SelectedDance] > 0) fill[17] = true;
    break;
    case champ:
      fill[8]  = true;
      fill[14] = true;
      fill[20] = true;
      fill[21] = true;
      fill[22] = true;
    break;
  }
  if (fill[ACol])
  {
    ResultsGrid->Canvas->Brush->Color = clBtnFace;
    ResultsGrid->Canvas->FillRect(Rect);
    ResultsGrid->Canvas->TextRect(Rect, Rect.Left + 2, Rect.Top + 2, ResultsGrid->Cells[ACol][ARow]); // Exactly the string in a runtime library
  }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::ConclusionButtonClick(TObject *Sender)
{
  // Save current results
  SaveResults();

  // Test if results were calculated.
  for(int Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
  {
    TDancer *D = Database->GetDancerByIndex(Dancer);
    if (D->Dances[SelectedDance] && (D->AgeGroup[SelectedDance] == ReferenceAgeButtons[SelectedGroup]->Caption) && (D->Places[SelectedDance] == 0) && (isGroupDance(SelectedDance) == D->isGroup) )
    {
        Application->MessageBox("Внимание! Результаты не были подсчитаны до объявления.\nНажмите кнопку \"Подсчитать результаты\" и проверьте их правильность, прежде чем объявлять.","Пересчёт результатов",MB_OK);
        return;
    }
  }

  DeclarationForm->ConclusionText->Lines->Clear();
  DeclarationForm->ConclusionText->Lines->Add("");
  AnsiString Line;

  // Make header
  DeclarationForm->ConclusionText->SelAttributes->Color = clBlack;
  Line = "      Награждение категории " + ReferenceButtons[SelectedDance]->Caption + " " + GroupToString(ReferenceAgeButtons[SelectedGroup]->Caption) + ".";
  DeclarationForm->ConclusionText->Lines->Append(Line);

  // Determine total number of places
  int MaxPlaces = 0;
  for(int Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
  {
    TDancer *D = Database->GetDancerByIndex(Dancer);
    if (D->Dances[SelectedDance] && (D->AgeGroup[SelectedDance] == ReferenceAgeButtons[SelectedGroup]->Caption) && (D->Places[SelectedDance] > MaxPlaces))
      MaxPlaces = D->Places[SelectedDance];
  }
  if (MaxPlaces > 3)
  {
    if (AllPlacesCheckBox->State == cbUnchecked) MaxPlaces = 3;
    if (AllPlacesCheckBox->State == cbGrayed && !ConclusionAllPlaces[SelectedDance]) MaxPlaces = 3;
  }
  if (MaxPlaces == 0) return; // Looks like this is impossible, but...

  // Make a line for every noticeable place
  for (int Place = MaxPlaces; Place >= 1; --Place)
  {
    AnsiString ResultList = "";
    int PlaceQuantity = 0;
    for(int Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
    {
      TDancer *D = Database->GetDancerByIndex(Dancer);
      if (D->Dances[SelectedDance] && (D->AgeGroup[SelectedDance] == ReferenceAgeButtons[SelectedGroup]->Caption) && (D->Places[SelectedDance] == Place))
      {
        // TODO optional: Sort by numbers
        ++PlaceQuantity;
        if (ResultList != "") ResultList += ", ";
        if (D->isGroup) ResultList += "\r\n        T";
        ResultList += D->Number;
        if (D->isGroup) ResultList += " (школа " + D->School + ")";
      }
    }

    if (PlaceQuantity == 0) continue; // Looks like this is impossible, but...
    Line = (AnsiString)"      " + Place + ((PlaceQuantity > 1)? " место — номера " : " место — номер ") + ResultList + ".";

    DeclarationForm->ConclusionText->SelAttributes->Color = (Place <= 3 ? clRed : clBlack);
    DeclarationForm->ConclusionText->Lines->Append(Line);
    DeclarationForm->ConclusionText->SelAttributes->Color = clBlack;
  }

  // Append School and Name
  if ((SelectedDance == PreChampionship || SelectedDance == Championship))
  {
    AnsiString ResultList = "";
    int PlaceQuantity = 0;
    for(int Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
    {
      TDancer *D = Database->GetDancerByIndex(Dancer);
      if (D->Dances[SelectedDance] && (D->AgeGroup[SelectedDance] == ReferenceAgeButtons[SelectedGroup]->Caption) && (D->Places[SelectedDance] == 1))
      {
        // TODO optional: Sort by numbers
        ++PlaceQuantity;
        ResultList += "\r\n            " + D->Name + " из школы " + D->School;
      }
    }

    if (PlaceQuantity > 0) // Looks like otherwise is impossible, but...
    {
      if (PlaceQuantity == 1)
      {
        Line = (AnsiString)"      Победителем " + ((SelectedDance == PreChampionship)? "предварительного чемпионата" : "чемпионата") + "\r\n      в категории " + GroupToString(ReferenceAgeButtons[SelectedGroup]->Caption) + " объявляется" + ResultList;
      }
      else
      {
        Line = (AnsiString)"      Победителями " + ((SelectedDance == PreChampionship)? "предварительного чемпионата" : "чемпионата") + "\r\n     в категории " + GroupToString(ReferenceAgeButtons[SelectedGroup]->Caption) + " объявляются:" + ResultList;
      }
      DeclarationForm->ConclusionText->Lines->Append(Line);
    }
  }

  // Make qualification sentence
  if (QualificationSentences[SelectedDance] != silnt)
  {
    int QualifiedQuantity = 0;

    /* The following is for the case if we want to tell dancers' numbers, not places:
    AnsiString ResultList = "";
    for(int Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
    {
      TDancer *D = Database->GetDancerByIndex(Dancer);
      if (D->Dances[SelectedDance] && (D->AgeGroup[SelectedDance] == ReferenceAgeButtons[SelectedGroup]->Caption) && D->Qualified[SelectedDance])
      {
        // TODO optional: Sort by numbers
        ++QualifiedQuantity;
        if (ResultList != "") ResultList += ", ";
        if (D->isGroup) ResultList += "T";
        ResultList += D->Number;
      }
    }*/

    // The following one is for places, not numbers:
    int MaxQualifiedPlace = 0;
    // We don't need this anymore, since we treat premierships now as a generic dance
    //   if (CountTypes[SelectedDance] != prem)
    {
      // Determine maximal qualified place
      for(int Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
      {
        TDancer *D = Database->GetDancerByIndex(Dancer);
        if (D->Dances[SelectedDance] && (D->AgeGroup[SelectedDance] == ReferenceAgeButtons[SelectedGroup]->Caption) && D->Qualified[SelectedDance])
        {
          ++QualifiedQuantity;
          if (MaxQualifiedPlace < D->Places[SelectedDance]) MaxQualifiedPlace = D->Places[SelectedDance];
        }
      }

      // Check whether any of these places does not have qualification
      if (QualifiedQuantity != 0) for(int Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
      {
        TDancer *D = Database->GetDancerByIndex(Dancer);
        if (D->Dances[SelectedDance] && (D->AgeGroup[SelectedDance] == ReferenceAgeButtons[SelectedGroup]->Caption))
        {
          if(MaxQualifiedPlace >= D->Places[SelectedDance] && !D->Qualified[SelectedDance])
          {
            MaxQualifiedPlace = 0;
            break;
          }
        }
      }
    }
    /* else
    {
      // Determine total participants number
      int Participants = 0;
      for(int Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
      {
        TDancer *D = Database->GetDancerByIndex(Dancer);
        if (D->Dances[SelectedDance] && (D->AgeGroup[SelectedDance] == ReferenceAgeButtons[SelectedGroup]->Caption))
        {
          ++Participants;
        }
      }

      // Premierships do not have D->Qualified flag, so count it here
      MaxQualifiedPlace = Participants /= 5;
      if(MaxQualified[SelectedDance] < MaxQualifiedPlace) MaxQualifiedPlace = MaxQualified[SelectedDance];
      QualifiedQuantity = MaxQualifiedPlace;
    } */

    if (QualifiedQuantity == 0)
      Line = "      Переходов в танце нет.";
    else
    {
      //Line = ((QualifiedQuantity > 1)? "  Номера " : "  Номер ") + ResultList; // numbers, not places
      // Places, not numbers: (currently non-standard qualification is disallowed: e.g. 1, 2 & 4 places, or 1, 2 places & no.123)
      if (MaxQualifiedPlace == 1) Line = "      Первое место";
      else if (MaxQualifiedPlace == 2) Line = "      Первое и второе места";
      else if (MaxQualifiedPlace == 3) Line = "      Первое, второе и третье места";
      else {QualifiedQuantity = 1; Line = "      Необходимо уточнить, кто";}

      if (QualificationSentences[SelectedDance] == topri)
        Line += (MaxQualifiedPlace /* QualifiedQuantity */ > 1)? " переходят в категорию Primary." : " переходит в категорию Primary.";

      if (QualificationSentences[SelectedDance] == toint)
        Line += (MaxQualifiedPlace /* QualifiedQuantity */ > 1)? " переходят в категорию Intermediate." : " переходит в категорию Intermediate.";

      if (QualificationSentences[SelectedDance] == toopn)
        Line += (MaxQualifiedPlace /* QualifiedQuantity */ > 1)? " переходят в категорию Open." : " переходит в категорию Open.";

      if (QualificationSentences[SelectedDance] == nomor)
        Line += (MaxQualifiedPlace /* QualifiedQuantity */ > 1)? " больше не танцуют этот танец." : " больше не танцует этот танец.";
    }

    DeclarationForm->ConclusionText->Lines->Append(Line);
  }

  // Show results
  DeclarationForm->ShowModal();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::MergeButtonClick(TObject *Sender)
{
  // Prepare names of groups
  AnsiString NameLeft  = ReferenceAgeButtons[SelectedGroup]    ->Caption;
  AnsiString NameRight = ReferenceAgeButtons[SelectedGroup + 1]->Caption;
  AnsiString NameNew   = NameRight;

  // Deal with situation of merging the only two existing groups Uxx and Oxx to AA
  if (ReferenceAgeButtons[2]->Caption == "") NameNew = "AA";
  // Deal with situation of merging last 2 groups when 3 or more exist: (... Unn, Uxx, Oxx) to (... Unn, Onn)
  else if (GetGroupType(NameRight) == 'O') NameNew = (AnsiString)"O" + GetGroupAge(ReferenceAgeButtons[SelectedGroup - 1]->Caption);

  // Confirm merging
  SaveResults();
  AnsiString Message = "Объединить группы " + NameLeft + " и " + NameRight + " в группу " + NameNew + "?";
  int q = Application->MessageBox(Message.c_str(),"Объединение групп",MB_YESNO);
  if (q != IDYES) return;

  // Change every group of NameRight to NameNew
  for(int Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
  {
    TDancer *D = Database->GetDancerByIndex(Dancer);
    if (D->Dances[SelectedDance] && (D->AgeGroup[SelectedDance] == NameRight)) D->AgeGroup[SelectedDance] = NameNew;
  }

  // Change every group of NameLeft to NameNew
  for(int Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
  {
    TDancer *D = Database->GetDancerByIndex(Dancer);
    if (D->Dances[SelectedDance] && (D->AgeGroup[SelectedDance] == NameLeft)) D->AgeGroup[SelectedDance] = NameNew;
  }

  // Renew, but without reselecting of group button
  ForceRedraw = true;
  ReselectGroup  = false;
  Renew();
  ReselectGroup  = true;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::AddNumberEditChange(TObject *Sender)
{
  AddNameEdit->OnChange = NULL;
  AddNameEdit->Text = "";
  TDancer *D = Database->GetDancerByNumber(AddNumberEdit->Text);
  if (D == NULL) return;
  if ( isGroupDance(SelectedDance) && !D->isGroup) return;
  if (!isGroupDance(SelectedDance) &&  D->isGroup) return;
  AddNameEdit->Text = D->Name;
  AddNameEdit->OnChange = AddNameEditChange;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::AddNameEditChange(TObject *Sender)
{
  // Can be called only if not a team

  AddNumberEdit->OnChange = NULL;
  AddNumberEdit->Text="";
  AddNumberEdit->OnChange = AddNumberEditChange;

  if(AddNameEdit->Text == "") return;
  TDancer *D = Database->GetDancerByPartialName(AddNameEdit->Text, true);
  if (D == NULL) return;
  if (D->isGroup) return;

  AddNumberEdit->OnChange = NULL;
  AddNumberEdit->Text = D->Number;
  AddNumberEdit->OnChange = AddNumberEditChange;

  int SelStart  = AddNameEdit->Text.Length();
  int SelLength = D->Name.Length() - SelStart;
  AddNameEdit->Text = D->Name;
  AddNameEdit->SelStart = SelStart;
  AddNameEdit->SelLength = SelLength;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::AddNameEditKeyPress(TObject *Sender, char &Key)
{
  // ESC: Abort autocompletion
  if (Key == 27)
  {
    AddNumberEdit->OnChange = NULL;
    AddNumberEdit->Text = "";
    AddNumberEdit->OnChange = AddNumberEditChange;

    AddNameEdit->OnChange = NULL;
    if (AddNameEdit->SelLength > 0)
    {
      AddNameEdit->Text = AddNameEdit->Text.SubString(1, AddNameEdit->SelStart);
      AddNameEdit->SelStart = AddNameEdit->Text.Length();
      AddNameEdit->SelLength = 0;
    }
    AddNameEdit->OnChange = AddNameEditChange;
  }

  // Backspace: delete selection and one more character, then autocomplete
  if (Key == 8)
  {
    // Only perform this if there is a non-free selection not from begin till the end
    if ((AddNameEdit->SelStart > 0) && (AddNameEdit->SelLength > 0) && (AddNameEdit->SelStart + AddNameEdit->SelLength == AddNameEdit->Text.Length()))
    {
      AddNameEdit->OnChange = NULL;
      AddNameEdit->Text = AddNameEdit->Text.SubString(1, AddNameEdit->SelStart - 1);
      AddNameEdit->SelStart = AddNameEdit->Text.Length();
      AddNameEdit->SelLength = 0;
      AddNameEdit->OnChange = AddNameEditChange;
      AddNameEditChange(NULL);
    }
  }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TFeisEnterForm::CleanButtonClick(TObject *Sender)
{
  SaveResults();
  AnsiString Message = "Точно очистить результаты группы " + ReferenceAgeButtons[SelectedGroup]->Caption + " в танце " + ReferenceButtons[SelectedDance]->Caption + "?";
  int q = Application->MessageBox(Message.c_str(),"Очистка результатов",MB_YESNO);
  if (q != IDYES) return;

  for(int Dancer = 0; Dancer < Database->TotalDancers(); ++Dancer)
  {
    TDancer *D = Database->GetDancerByIndex(Dancer);
    if (D->Dances[SelectedDance] && (D->AgeGroup[SelectedDance] == ReferenceAgeButtons[SelectedGroup]->Caption))
    {
      for (int k = 0; k < TotalRounds; ++k) D->RawPoints[SelectedDance][k] = -1;
      D->CalcPoints[SelectedDance] = -1;
      D->Places[SelectedDance] = 0;
      D->Qualified[SelectedDance] = false;
    }
  }

  ForceRedraw = true;
  ReselectGroup  = false;
  Renew();
  ReselectGroup  = true;
  return;
}
