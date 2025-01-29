//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Grids.h"
#include "GroupUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGroupForm *GroupForm;
extern TFeisDatabase *Database;
//---------------------------------------------------------------------------
int SubDanceNum[TotalDancesExt] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    4, 3, 4, 3, 4, 3, 2, 3 };
//---------------------------------------------------------------------------
AnsiString sdNone[4] = {"", "", "", ""};
AnsiString sdRLSS[4] = {"Reel", "Ligh", "Sing", "Slip"};
AnsiString sdTHT[4]  = {"Treb", "Horn", "Trad", ""};
AnsiString sdRS[4]   = {"Reel", "Slip", "", ""};
AnsiString *SubDancesText[TotalDancesExt] =
{
  sdNone,   sdNone,   sdNone,   sdNone,   sdNone,
  sdNone,   sdNone,   sdNone,   sdNone,   sdNone,
  sdNone,   sdNone,   sdNone,   sdNone,   sdNone,
  sdNone,   sdNone,   sdNone,   sdNone,   sdNone,
  sdNone,   sdNone,   sdNone,   sdNone,   sdNone,
  sdNone,   sdNone,   sdNone,   sdNone,   sdNone,
  sdNone,   sdNone,   sdNone,   sdNone,   sdNone,
  sdNone,   sdNone,   sdNone,

  sdRLSS,   sdTHT,  sdRLSS,   sdTHT,  sdRLSS,   sdTHT,  sdRS,   sdTHT
};
//---------------------------------------------------------------------------
enum Dances SubDances[TotalDancesExt][4] =
{
  { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil },
  { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil },
  { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil },
  { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil },
  { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil },
  { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil },
  { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil },
  { nil, nil, nil, nil }, { nil, nil, nil, nil }, { nil, nil, nil, nil },
  { BeginnerReel, BeginnerLightJig, BeginnerSingleJig, BeginnerSlipJig },
  { BeginnerTrebleJig, BeginnerHornpipe, BeginnerTradSet, nil },
  { PrimaryReel, PrimaryLightJig, PrimarySingleJig, PrimarySlipJig },
  { PrimaryTrebleJig, PrimaryHornpipe, PrimaryTradSet, nil },
  { IntermedReel, IntermedLightJig, IntermedSingleJig, IntermedSlipJig },
  { IntermedTrebleJig, IntermedHornpipe, IntermedTradSet, nil },
  { OpenReel, OpenSlipJig, nil, nil },
  { OpenTrebleJig, OpenHornpipe, OpenTradSet, nil }
};
//---------------------------------------------------------------------------
bool isSpecialDance(enum Dances Dance)
{
  return (SubDanceNum[Dance] > 0);
}
//---------------------------------------------------------------------------
bool TGroupForm::SearchGroupDance(enum Dances Dance, int Age, AnsiString &Group)
{
  if (Groups[Dance][0] == "AA") { Group = "AA"; return true; }

  bool found = false;
  int GroupIndex;
  for (GroupIndex = 0; GroupIndex < TotalGroups; ++GroupIndex)
  {
    if (Groups[Dance][GroupIndex] == "")                                break;
    if (GetGroupType(Groups[Dance][GroupIndex]) == 'O') { found = true; break; }
    if (Age < GetGroupAge(Groups[Dance][GroupIndex]))   { found = true; break; }
  }
  if (found) Group = Groups[Dance][GroupIndex];
  return found;
}
//---------------------------------------------------------------------------
bool TGroupForm::SearchGroupRef(int Age, AnsiString &Group)
{
  if (ReferenceEdits[0]->Text == "AA") { Group = "AA"; return true; }

  bool found = false;
  int GroupIndex;
  for (GroupIndex = 0; GroupIndex < TotalGroups; ++GroupIndex)
  {
    if (ReferenceEdits[GroupIndex]->Text == "")                                break;
    if (GetGroupType(ReferenceEdits[GroupIndex]->Text) == 'O') { found = true; break; }
    if (Age < GetGroupAge(ReferenceEdits[GroupIndex]->Text))   { found = true; break; }
  }
  if (found) Group = ReferenceEdits[GroupIndex]->Text;
  return found;
}
//---------------------------------------------------------------------------
__fastcall TGroupForm::TGroupForm(TComponent* Owner) : TForm(Owner)
{
  // We shall not need that until we forget to call TablesFromDatabase():
  // for (int Dance = 0; Dance < TotalDances; ++Dance) Groups[Dance][0] = "AA";

  SelectedDance = Jump23;

  SetWindowLong(ButtonBegSoft->Handle,  GWL_STYLE, GetWindowLong(ButtonBegSoft->Handle,  GWL_STYLE) | BS_MULTILINE);
  SetWindowLong(ButtonBegHard->Handle,  GWL_STYLE, GetWindowLong(ButtonBegHard->Handle,  GWL_STYLE) | BS_MULTILINE);
  SetWindowLong(ButtonPriSoft->Handle,  GWL_STYLE, GetWindowLong(ButtonPriSoft->Handle,  GWL_STYLE) | BS_MULTILINE);
  SetWindowLong(ButtonPriHard->Handle,  GWL_STYLE, GetWindowLong(ButtonPriHard->Handle,  GWL_STYLE) | BS_MULTILINE);
  SetWindowLong(ButtonIntSoft->Handle,  GWL_STYLE, GetWindowLong(ButtonIntSoft->Handle,  GWL_STYLE) | BS_MULTILINE);
  SetWindowLong(ButtonIntHard->Handle,  GWL_STYLE, GetWindowLong(ButtonIntHard->Handle,  GWL_STYLE) | BS_MULTILINE);
  SetWindowLong(ButtonOpenSoft->Handle, GWL_STYLE, GetWindowLong(ButtonOpenSoft->Handle, GWL_STYLE) | BS_MULTILINE);
  SetWindowLong(ButtonOpenHard->Handle, GWL_STYLE, GetWindowLong(ButtonOpenHard->Handle, GWL_STYLE) | BS_MULTILINE);

  ButtonBegSoft->Caption  = "Beginner\nSoft";
  ButtonBegHard->Caption  = "Beginner\nHard";
  ButtonPriSoft->Caption  = "Primary\nSoft";
  ButtonPriHard->Caption  = "Primary\nHard";
  ButtonIntSoft->Caption  = "Intermed\nSoft";
  ButtonIntHard->Caption  = "Intermed\nHard";
  ButtonOpenSoft->Caption = "Open\nSoft";
  ButtonOpenHard->Caption = "Open\nHard";

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
  ReferenceButtons[GroupCeili]          = ButtonCeili;
  ReferenceButtons[SpecialBeginnerSoft] = ButtonBegSoft;
  ReferenceButtons[SpecialBeginnerHard] = ButtonBegHard;
  ReferenceButtons[SpecialPrimarySoft]  = ButtonPriSoft;
  ReferenceButtons[SpecialPrimaryHard]  = ButtonPriHard;
  ReferenceButtons[SpecialIntermedSoft] = ButtonIntSoft;
  ReferenceButtons[SpecialIntermedHard] = ButtonIntHard;
  ReferenceButtons[SpecialOpenSoft]     = ButtonOpenSoft;
  ReferenceButtons[SpecialOpenHard]     = ButtonOpenHard;

  ReferenceEdits[0]  = EditGroup1;
  ReferenceEdits[1]  = EditGroup2;
  ReferenceEdits[2]  = EditGroup3;
  ReferenceEdits[3]  = EditGroup4;
  ReferenceEdits[4]  = EditGroup5;
  ReferenceEdits[5]  = EditGroup6;
  ReferenceEdits[6]  = EditGroup7;
  ReferenceEdits[7]  = EditGroup8;
  ReferenceEdits[8]  = EditGroup9;
  ReferenceEdits[9]  = EditGroup10;
  ReferenceEdits[10] = EditGroup11;
  ReferenceEdits[11] = EditGroup12;
  ReferenceEdits[12] = EditGroup13;
  ReferenceEdits[13] = EditGroup14;
  ReferenceEdits[14] = EditGroup15;
  ReferenceEdits[15] = EditGroup16;

  ReferenceLabels[0]  = TotalGroup1;
  ReferenceLabels[1]  = TotalGroup2;
  ReferenceLabels[2]  = TotalGroup3;
  ReferenceLabels[3]  = TotalGroup4;
  ReferenceLabels[4]  = TotalGroup5;
  ReferenceLabels[5]  = TotalGroup6;
  ReferenceLabels[6]  = TotalGroup7;
  ReferenceLabels[7]  = TotalGroup8;
  ReferenceLabels[8]  = TotalGroup9;
  ReferenceLabels[9]  = TotalGroup10;
  ReferenceLabels[10] = TotalGroup11;
  ReferenceLabels[11] = TotalGroup12;
  ReferenceLabels[12] = TotalGroup13;
  ReferenceLabels[13] = TotalGroup14;
  ReferenceLabels[14] = TotalGroup15;
  ReferenceLabels[15] = TotalGroup16;

  AgesGrid->Cells[0][0] = "Номер";
  AgesGrid->Cells[1][0] = "Участник";
  AgesGrid->Cells[2][0] = "Школа";
  AgesGrid->ColWidths[0] = 45;
  AgesGrid->ColWidths[1] = 150;
  AgesGrid->ColWidths[2] = 200;

  Renew();
}
//---------------------------------------------------------------------------
void TGroupForm::GroupsToDatabase()
{
  bool Warned[TotalDances];
  bool YesToAll = false;
  bool NoToAll = false;
  for (int Dance = 0; Dance < TotalDances; ++Dance) Warned[Dance] = false;

  for (int DBEntry = 0; DBEntry < Database->TotalDancers(); ++DBEntry)
  {
    TDancer *Dancer = Database->GetDancerByIndex(DBEntry);

    // Don't modify age groups for teams
    if (Dancer->isGroup) continue;

    for (int Dance = 0; Dance < TotalDances; ++Dance)
    {
      if (!Dancer->Dances[Dance]) continue;

      AnsiString Group;
      if (!SearchGroupDance((enum Dances)Dance, Dancer->Age, Group))
      {
        // We can reach here only for group dances that are not checked.
        if(!Warned[Dance])
        {
          AnsiString msg = "Возрастные группы для танца " + ReferenceButtons[Dance]->Caption + " заданы неправильно.\nЕсли группа одна, она должна называться \"All Ages\";\nЕсли групп несколько, последняя должна быть типа Over, а все остальные - типа Under.\nВозраст в последней и предпоследней группе должен совпадать, например Under 24 и Over 24.\nПерезадайте их на странице регистрации групповых танцев.";
          Application->MessageBox(msg.c_str(),"Ошибка базы данных",MB_OK);
          Warned[Dance] = true;
        }
      }
      else
      {
        // Skip group dances rearrangement: this age group actually does not matter after all, and if needed, this might be checked using Import form check button.
        if (isGroupDance((enum Dances)Dance)) continue;

        if (Dancer->AgeGroup[Dance] == "") Dancer->AgeGroup[Dance] = Group;
        else if (Dancer->AgeGroup[Dance] != Group)
        {
          bool Do;
          if (NoToAll)  Do = false;
          if (YesToAll) Do = true;
          if (!YesToAll && !NoToAll)
          {
            AnsiString Msg = "Участник номер ";
            Msg += Dancer->Number;
            Msg += " (" + Dancer->Name + ") в танце " + ReferenceButtons[Dance]->Caption + " имеет возрастную группу " + Dancer->AgeGroup[Dance] + ".\nЕго возраст - ";
            Msg += Dancer->Age;
            Msg += " лет, значит он должен быть в группе " + Group + ". Переместить его в неё?";
            int res = MessageDlg(Msg, mtInformation,  TMsgDlgButtons() << mbYes << mbYesToAll << mbNo << mbNoToAll, 0);
            if ((res == mrYes) || (res == mrYesToAll)) Do = true;
            if ((res == mrNo) || (res == mrNoToAll))  Do = false;
            if (res == mrYesToAll) YesToAll = true;
            if (res == mrNoToAll)  NoToAll  = true;
          }
          if (Do) Dancer->AgeGroup[Dance] = Group;
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
bool TGroupForm::SaveGroups()
{
  // No need to save anything because we cannot edit anything
  if (isGroupDance(SelectedDance)) return true;

  // Don't save if we found any errors
  bool checked = CheckGroups();
  if (checked == false) return false;

  for (int GroupIndex = 0; GroupIndex < TotalGroups; ++GroupIndex)
    if (isSpecialDance(SelectedDance))
      for (int SubDanceIndex = 0; SubDanceIndex < SubDanceNum[SelectedDance]; ++SubDanceIndex)
        Groups[SubDances[SelectedDance][SubDanceIndex]][GroupIndex] = ReferenceEdits[GroupIndex]->Text;
    else
      Groups[SelectedDance][GroupIndex] = ReferenceEdits[GroupIndex]->Text;

  return true;
}
//---------------------------------------------------------------------------
bool TGroupForm::CheckGroups()
{
  AnsiString errmsg = "";

  // Determine raw quantity of groups
  int Quantity;
  for (Quantity = TotalGroups; Quantity > 0; --Quantity)
    if (ReferenceEdits[Quantity - 1]->Text != "") break;

  // Compactify groups and alter quantity, if needed
  for (int Group = 0; Group < Quantity; ++Group)
  {
    bool DeleteThis = false;
    if (ReferenceEdits[Group]->Text == "") DeleteThis = true;
    if (Group > 0) { if (ReferenceEdits[Group]->Text == ReferenceEdits[Group - 1]->Text) DeleteThis = true; }
    if (DeleteThis)
    {
      for (int SubGroup = Group; SubGroup < Quantity - 1; ++SubGroup)
        ReferenceEdits[SubGroup]->Text = ReferenceEdits[SubGroup + 1]->Text;
      --Quantity;
      ReferenceEdits[Quantity]->Text = "";
      --Group; // Do this to check this line again by `for' statement
    }
  }

  // Checking the following:
  // if group is AA, then it shall be the only group in list, else:
  // Last group in list shall be Oxx, pre-last group shall be exactly Uxx (xx's are equal)
  // Each next Uxx shall have greater xx than previous

  if (Quantity < 1) {errmsg = "Определите хотя бы одну группу.";}
  else if (Quantity == 1)
  {
    if (ReferenceEdits[0]->Text == "AA") return true;
    errmsg = "Если группа одна, она должна быть AA.";
  }
  else
  {
    if (GetGroupType(ReferenceEdits[Quantity - 1]->Text) != 'O')
      errmsg = "Последняя группа должна быть Охх.";
    else
    {
      int prelast = GetGroupAge(ReferenceEdits[Quantity - 2]->Text);
      int last    = GetGroupAge(ReferenceEdits[Quantity - 1]->Text);
      if (prelast == 0)
        errmsg = "Неправильный возраст в предпоследней группе.";
      else if (last == 0)
        errmsg = "Неправильный возраст в последней группе.";
      else if (prelast != last)
        errmsg = "Возраст в предпоследней и последней группе должен совпадать\n(например, U24 и O24).";
      else
      {
        for (int Group = 0; Group < Quantity - 1; ++Group)
        {
          if (GetGroupType(ReferenceEdits[Group]->Text) != 'U')
          {
            errmsg = "Все группы, кроме последней, должны быть Uхх.";
            break;
          }
          else if (Group > 0)
          {
            int prev = GetGroupAge(ReferenceEdits[Group - 1]->Text);
            int next = GetGroupAge(ReferenceEdits[Group]->Text);
            if ((prev == 0) || (next == 0))
              errmsg = "Неправильный возраст в одной из групп.";
            else if(prev > next)
            {
              errmsg = "Группы должны быть упорядочены по возрастанию.";
              break;
            }
          }
        }
        if (errmsg == "") return true;
      }
    }
  }
  Application->MessageBox(errmsg.c_str(), "Проверьте определения групп", MB_OK);
  return false;
}
//---------------------------------------------------------------------------
void TGroupForm::CopyGroups(enum Dances Source, enum Dances Target)
{
  for (int Group = 0; Group < TotalGroups; ++Group)
    Groups[Target][Group] = Groups[Source][Group];
}
//---------------------------------------------------------------------------
bool TGroupForm::GroupsDifferent(enum Dances Dance1, enum Dances Dance2)
{
  for (int Group = 0; Group < TotalGroups; ++Group)
    if(Groups[Dance1][Group] != Groups[Dance2][Group]) return true;
  return false;
}
//---------------------------------------------------------------------------
AnsiString TGroupForm::MakeGroupCounter(int GroupCol, AnsiString Group, AnsiString *Declined, int Count, enum Dances Dance1, enum Dances Dance2, enum Dances Dance3, enum Dances Dance4)
{
  if (Group == "") return "";

  enum Dances DanceArr[4] = {Dance1, Dance2, Dance3, Dance4};
  AnsiString result = "";
  for(int i = 0; i < Count; ++i)
  {
    if (result != "") result += " / ";
    int N = 0;
    for (int Line = 1; Line < AgesGrid->RowCount; ++Line)
      if ((AgesGrid->Cells[GroupCol][Line] == Group) && (Database->GetDancerByNumber(AgesGrid->Cells[0][Line])->Dances[DanceArr[i]])) ++N;
    if ((N == 0) && (Group != "AA"))
    {
      if (*Declined != "") *Declined += ", ";
      *Declined += ReferenceButtons[DanceArr[i]]->Caption + " " + Group;
    }
    result += N;
  }
  return result;
}
//---------------------------------------------------------------------------
void TGroupForm::Renew()
{
  int GroupCol;

  // If we select a special dance, expand group definitions
  if (isSpecialDance(SelectedDance))
  {
    bool equal = true;
    for (int SubDanceIndex = 1; SubDanceIndex < SubDanceNum[SelectedDance]; ++SubDanceIndex)
      if(GroupsDifferent(SubDances[SelectedDance][SubDanceIndex], SubDances[SelectedDance][0])) { equal = false; break; }
    if (!equal)
    {
      int answer = Application->MessageBox("Внимание! В выбранной группе танцев разные танцы имеют разный набор групп.\nЭто могло получиться, если какие-то группы были автоматически удалены, поскольку были пустыми.\nСделать везде один набор?\n\"Да\" - сделать во всей группе танцев такие же возрастные группы, как в первом танце из группы;\n\"Нет\" - не делать этого, и вместо группы танцев перейти к первому танцу из группы.","Несоответствие групп", MB_YESNO);
      if (answer == IDNO) { SelectedDance = SubDances[SelectedDance][0]; ActiveControl = ReferenceButtons[SelectedDance]; Renew(); return;}
    }
    for (int SubDanceIndex = 1; SubDanceIndex < SubDanceNum[SelectedDance]; ++SubDanceIndex)
      CopyGroups(SubDances[SelectedDance][0], SubDances[SelectedDance][SubDanceIndex]);
  }

  // Fill group definitions
  for (int Group = 0; Group < TotalGroups; ++Group)
  {
    if (isSpecialDance(SelectedDance))
      ReferenceEdits[Group]->Text = Groups[SubDances[SelectedDance][0]][Group];
    else
      ReferenceEdits[Group]->Text = Groups[SelectedDance][Group];
  }

  // Select button of current dance, deselect all others (italicize subdances, if we have dance group)
  for (int Dance = 0; Dance < TotalDancesExt; ++Dance)
  {
    ReferenceButtons[Dance]->Font->Style = TFontStyles();
  }
  ReferenceButtons[SelectedDance]->Font->Style = TFontStyles() << fsBold;
  if (isSpecialDance(SelectedDance))
    for (int SubDanceIndex = 0; SubDanceIndex < SubDanceNum[SelectedDance]; ++SubDanceIndex)
      ReferenceButtons[SubDances[SelectedDance][SubDanceIndex]]->Font->Style = TFontStyles() << fsItalic;

  // Restrict editing for group dances
  if (isGroupDance(SelectedDance))
  {
    NoGroupWarn->Show();
    for (int i = 0; i < TotalGroups; ++i) ReferenceEdits[i]->Enabled = false;
    ButtonRenew->Enabled = false;
    ButtonInsert->Enabled = false;
    AgesGrid->ColCount = 4;
    AgesGrid->Cells[3][0] = "Группа";
    AgesGrid->ColWidths[3] = 50;
    GroupCol = 3;
  }
  else
  {
    NoGroupWarn->Hide();
    for (int i = 0; i < TotalGroups; ++i) ReferenceEdits[i]->Enabled = true;
    ButtonRenew->Enabled = true;
    ButtonInsert->Enabled = true;
    AgesGrid->ColCount = 6;
    AgesGrid->Cells[3][0] = "Возраст";
    AgesGrid->Cells[4][0] = "Группа";
    AgesGrid->ColWidths[3] = 60;
    AgesGrid->ColWidths[4] = 50;
    AgesGrid->ColWidths[5] = 0;
    GroupCol = 4;
  }

  // Repaint grid
  AgesGrid->RowCount = 2;
  AgesGrid->Rows[1]->Clear();
  if(isSpecialDance(SelectedDance))
  {
    AgesGrid->ColCount = GroupCol + 2 + SubDanceNum[SelectedDance];
    for (int SubDanceIndex = 0; SubDanceIndex < SubDanceNum[SelectedDance]; ++SubDanceIndex)
    {
      AgesGrid->Cells[GroupCol + 1 + SubDanceIndex][0] = SubDancesText[SelectedDance][SubDanceIndex];
      AgesGrid->ColWidths[GroupCol + 1 + SubDanceIndex] = 30;
    }
  }

  AgesGrid->Cells[AgesGrid->ColCount - 1][0] = "(Color)"; // Technical column
  AgesGrid->ColWidths[AgesGrid->ColCount - 1] = 0;

  // Fill grid
  for (int DBEntry = 0; DBEntry < Database->TotalDancers(); ++DBEntry)
  {
    TDancer *Dancer = Database->GetDancerByIndex(DBEntry);

    // Skip solo dancers if we are showing teams
    if (isGroupDance(SelectedDance) && !Dancer->isGroup) continue;

    // Skip dancers that do not participate in this dance, or indicate who dances one of the compound
    int GridRow;
    bool added = false;
    if(isSpecialDance(SelectedDance))
    {
      bool skip = true;
      for (int SubDanceIndex = 0; SubDanceIndex < SubDanceNum[SelectedDance]; ++SubDanceIndex)
      {
        if (Dancer->Dances[SubDances[SelectedDance][SubDanceIndex]])
        {
          if(!added) { GridRow = NewLineToTable(AgesGrid); added = true; }
          AgesGrid->Cells[GroupCol + 1 + SubDanceIndex][GridRow] = "+";
          skip = false;
        }
      }
      if (skip) continue;
    }
    else if (!Dancer->Dances[SelectedDance]) continue;

    // Add new string to grid and specify dances's info
    if(!added) GridRow = NewLineToTable(AgesGrid);
    AnsiString DancerNumber;
    if (Dancer->isGroup) DancerNumber += "T";
    DancerNumber += Dancer->Number;
    AgesGrid->Cells[0][GridRow] = DancerNumber;
    AgesGrid->Cells[1][GridRow] = Dancer->Name;
    AgesGrid->Cells[2][GridRow] = Dancer->School;

    // Add age group to grid
    if (!Dancer->isGroup)
    {
      AgesGrid->Cells[3][GridRow] = Dancer->Age;
      AnsiString CalculatedGroup;
      SearchGroupRef(Dancer->Age, CalculatedGroup);

      if (CheckBoxInitial->Checked) // Overwrite existing groups
      {
        AgesGrid->Cells[4][GridRow] = CalculatedGroup;
        AgesGrid->Cells[AgesGrid->ColCount - 1][GridRow] = clWhite;
      }
      else
      {
        // Mark dancers for whom age group does not meet database contents
        if (Dancer->AgeGroup[SelectedDance] == "") // No group at all -> blue
        {
          AgesGrid->Cells[4][GridRow] = CalculatedGroup;
          AgesGrid->Cells[AgesGrid->ColCount - 1][GridRow] = clBlue;
        }
        else if ((Dancer->AgeGroup[SelectedDance] != CalculatedGroup)) // Incorrect group -> red
        {
          AgesGrid->Cells[4][GridRow] = Dancer->AgeGroup[SelectedDance];
          AgesGrid->Cells[AgesGrid->ColCount - 1][GridRow] = clRed;
        }
        else // Matching and existing group -> white
        {
          AgesGrid->Cells[4][GridRow] = CalculatedGroup;
          AgesGrid->Cells[AgesGrid->ColCount - 1][GridRow] = clWhite;
        }
      }
    }
    else AgesGrid->Cells[3][GridRow] = Dancer->AgeGroup[SelectedDance];

  }

  // Count group totals
  AnsiString Declined = "";
  for (int Group = 0; Group < TotalGroups; ++Group)
  {
    if (!isSpecialDance(SelectedDance))
      ReferenceLabels[Group]->Caption = MakeGroupCounter(GroupCol, ReferenceEdits[Group]->Text, &Declined, 1, SelectedDance, nil, nil, nil);
    else
      ReferenceLabels[Group]->Caption = MakeGroupCounter(GroupCol, ReferenceEdits[Group]->Text, &Declined, SubDanceNum[SelectedDance],
                                                         SubDances[SelectedDance][0], SubDances[SelectedDance][1],
                                                         SubDances[SelectedDance][2], SubDances[SelectedDance][3]);
  }
  if (Declined != "")
  {
    AnsiString msg = "В следующих возрастных группах нет ни одного человека:\n" + Declined + "\nДанные группы будут удалены при закрытии окна разбивки на группы.";
    Application->MessageBox(msg.c_str(),"Пустая возрастная группа",MB_OK);
  }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonRenewClick(TObject *Sender)
{
  if(SaveGroups()) { Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonCloseClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  if (!SaveGroups()) Action = caNone;
  else
  {
    Renew(); // Check counters for groups that contains 0 dancers
    GroupsToDatabase();
  }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::FormShow(TObject *Sender)
{
  Database->GroupsFromDatabase(Groups);
  ActiveEdit = NULL;
  Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonJump23Click(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = Jump23; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonTrebReelClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = TrebleReel; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonBegReelClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = BeginnerReel; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonBegLightClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = BeginnerLightJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonBegSingleClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = BeginnerSingleJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonBegSlipClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = BeginnerSlipJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonBegHornClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = BeginnerHornpipe; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonBegTradClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = BeginnerTradSet; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonPriLightClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = PrimaryLightJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonPriSingleClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = PrimarySingleJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonPriSlipClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = PrimarySlipJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonPriTrebleClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = PrimaryTrebleJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonPriHornClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = PrimaryHornpipe; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonPriTradClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = PrimaryTradSet; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonPriPremClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = PrimaryPremiership; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonPreChampClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = PreChampionship; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonChampClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = Championship; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonIntReelClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = IntermedReel; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonIntLightClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = IntermedLightJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonIntSingleClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = IntermedSingleJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonIntSlipClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = IntermedSlipJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonIntTrebClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = IntermedTrebleJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonIntHornClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = IntermedHornpipe; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonIndTradClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = IntermedTradSet; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonIntPremClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = IntermedPremiership; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonOpenReelClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = OpenReel; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonOpenSlipClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = OpenSlipJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonOpenTrebClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = OpenTrebleJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonOpenHornClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = OpenHornpipe; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonOpenTradClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = OpenTradSet; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonModernSetClick(TObject *Sender)
{
    if(SaveGroups()) { SelectedDance = ModernSet; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::Button2HandClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = Group2Hand; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::Button3HandClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = Group3Hand; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::Button4HandClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = Group4Hand; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonCeiliClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = GroupCeili; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonBegTrebleClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = BeginnerTrebleJig; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonPriReelClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = PrimaryReel; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonBegPremClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = BeginnerPremiership; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonBegSoftClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = SpecialBeginnerSoft; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonBegHardClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = SpecialBeginnerHard; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonPriSoftClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = SpecialPrimarySoft; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonPriHardClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = SpecialPrimaryHard; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonIntSoftClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = SpecialIntermedSoft; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonIntHardClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = SpecialIntermedHard; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonOpenSoftClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = SpecialOpenSoft; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonOpenHardClick(TObject *Sender)
{
  if(SaveGroups()) { SelectedDance = SpecialOpenHard; Renew(); }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::ButtonInsertClick(TObject *Sender)
{
  if (ReferenceEdits[TotalGroups - 1]->Text != "")
  {
    Application->MessageBox("Группы добавлять некуда. Последняя строка должна быть пуста.", "Добавление строки", MB_OK);
    return;
  }

  if (ActiveEdit == 0)
  {
    Application->MessageBox("Перед нажатием этой кнопки поставьте курсор в поле ввода, над которым надо добавить пустую строку.", "Добавление строки", MB_OK);
    return;
  }

  for (int j = TotalGroups - 1; j >= ActiveEdit; --j)
    ReferenceEdits[j]->Text = ReferenceEdits[j - 1]->Text;
  ReferenceEdits[ActiveEdit - 1]->Text = "";
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::EditEnter(TObject *Sender)
{
  ActiveEdit = ActiveControl->Tag;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TGroupForm::AgesGridDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
  if (!State.Contains(gdSelected) && !State.Contains(gdFocused) && !State.Contains(gdFixed))
  {
    TRect RectForText = AgesGrid->CellRect(ACol,ARow);

    AgesGrid->Canvas->Brush->Color = clWhite;
    if (!isGroupDance(SelectedDance))
    {
      AgesGrid->Canvas->Brush->Color = (TColor)StrToInt(AgesGrid->Cells[AgesGrid->ColCount - 1][ARow]);
    }
    AgesGrid->Canvas->FillRect(RectForText);

    AgesGrid->Canvas->Font->Color = clWhite;
    if(AgesGrid->Canvas->Brush->Color == clWhite) AgesGrid->Canvas->Font->Color = clBlack;

    RectForText.Left += 2;
    RectForText.Top  += 2;
    AgesGrid->Canvas->TextRect(RectForText, RectForText.Left, RectForText.Top, AgesGrid->Cells[ACol][ARow]);
  }
}
//---------------------------------------------------------------------------

