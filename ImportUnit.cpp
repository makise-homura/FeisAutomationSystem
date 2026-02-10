//---------------------------------------------------------------------------
#include <vcl.h>
#include <StrUtils.hpp>
#pragma hdrstop

#include "ImportUnit.h"
#include "Excel.h"
#include "Database.h"
#include "Grids.h"
#include "LogUnit.h"
#include "ManageTeamUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TImportForm *ImportForm;
extern TFeisDatabase *Database;
//---------------------------------------------------------------------------
__fastcall TImportForm::TImportForm(TComponent* Owner) : TForm(Owner)
{
  ListGrid->Cells[0][0]  = "Номер";
  ListGrid->Cells[1][0]  = "Участник";
  ListGrid->Cells[2][0]  = "Школа";
  ListGrid->Cells[3][0]  = "Возраст (год рождения)";
  ListGrid->ColWidths[0] = 60;
  ListGrid->ColWidths[1] = 200;
  ListGrid->ColWidths[2] = 400;
  ListGrid->ColWidths[3] = 60;

  SoloGrid->Cells[0][0]   = "Номер";
  SoloGrid->Cells[1][0]   = "Участник";
  SoloGrid->Cells[2][0]   = "Школа";
  SoloGrid->Cells[3][0]   = "Возраст";
  SoloGrid->Cells[4][0]   = "Jm23";
  SoloGrid->Cells[5][0]   = "MSet";
  SoloGrid->Cells[6][0]   = "TrbR";
  SoloGrid->Cells[7][0]   = "Reel";
  SoloGrid->Cells[8][0]   = "LigJ";
  SoloGrid->Cells[9][0]   = "SinJ";
  SoloGrid->Cells[10][0]  = "SlpJ";
  SoloGrid->Cells[11][0]  = "TrbJ";
  SoloGrid->Cells[12][0]  = "Horn";
  SoloGrid->Cells[13][0]  = "Trad";
  SoloGrid->Cells[14][0]  = "Prem";
  SoloGrid->Cells[15][0]  = "PrCh";
  SoloGrid->Cells[16][0]  = "Cham";
  SoloGrid->ColWidths[0]  = 40;
  SoloGrid->ColWidths[1]  = 200;
  SoloGrid->ColWidths[2]  = 150;
  SoloGrid->ColWidths[3]  = 40;
  SoloGrid->ColWidths[4]  = 30;
  SoloGrid->ColWidths[5]  = 30;
  SoloGrid->ColWidths[6]  = 30;
  SoloGrid->ColWidths[7]  = 30;
  SoloGrid->ColWidths[8]  = 30;
  SoloGrid->ColWidths[9]  = 30;
  SoloGrid->ColWidths[10] = 30;
  SoloGrid->ColWidths[11] = 30;
  SoloGrid->ColWidths[12] = 30;
  SoloGrid->ColWidths[13] = 30;
  SoloGrid->ColWidths[14] = 30;
  SoloGrid->ColWidths[15] = 30;
  SoloGrid->ColWidths[16] = 30;

  GroupGrid->Cells[0][0]  = "Номер";
  GroupGrid->Cells[1][0]  = "Команда";
  GroupGrid->Cells[2][0]  = "Школа";
  GroupGrid->Cells[3][0]  = "Танец";
  GroupGrid->ColWidths[0] = 40;
  GroupGrid->ColWidths[1] = 400;
  GroupGrid->ColWidths[2] = 200;
  GroupGrid->ColWidths[3] = 150;

  CurrentPage = ltList;

  UIDList  = new TList;
  UIDSolo  = new TList;
  UIDGroup = new TList;
}
//---------------------------------------------------------------------------
__fastcall TImportForm::~TImportForm()
{
  for (int i = 0; i < UIDList->Count; ++i)  delete UIDList->Items[i];
  for (int i = 0; i < UIDSolo->Count; ++i)  delete UIDSolo->Items[i];
  for (int i = 0; i < UIDGroup->Count; ++i) delete UIDGroup->Items[i];
  delete UIDList, UIDSolo, UIDGroup;
}
//---------------------------------------------------------------------------
bool ReadBPIO(AnsiString Source, bool *B, bool *P, bool *I, bool *O)
{
  bool rv = true;

  // Initialize targets
  if (B) *B = false;
  if (P) *P = false;
  if (I) *I = false;
  if (O) *O = false;

  // Switch up any target if a character is found
  if (Source.Pos("B") != 0) { if (B) *B = true; else rv = false; }
  if (Source.Pos("P") != 0) { if (P) *P = true; else rv = false; }
  if (Source.Pos("I") != 0) { if (I) *I = true; else rv = false; }
  if (Source.Pos("O") != 0) { if (O) *O = true; else rv = false; }

  // Find any characters that is not B, P, I, O.
  // Multiple occurences of each of B, P, I, O are allowed, though completely useless.
  AnsiString TestResult = Source;
  TestResult = AnsiReplaceStr(TestResult, "B", "");
  TestResult = AnsiReplaceStr(TestResult, "P", "");
  TestResult = AnsiReplaceStr(TestResult, "I", "");
  TestResult = AnsiReplaceStr(TestResult, "O", "");

  return TestResult.Trim() == "" ? rv : false;
}
//---------------------------------------------------------------------------
AnsiString MakeBPIO(bool B, bool P, bool I, bool O)
{
  AnsiString rv = "";
  if (B) rv += "B";
  if (P) rv += "P";
  if (I) rv += "I";
  if (O) rv += "O";
  return rv;
}
//---------------------------------------------------------------------------
AnsiString MakeBPIOEx(bool B, AnsiString BS, bool P, AnsiString PS, bool I, AnsiString IS, bool O, AnsiString OS)
{
  AnsiString rv = "";
  if (B) { if (rv != "") rv += ", "; rv += "B "; rv += BS; }
  if (P) { if (rv != "") rv += ", "; rv += "P "; rv += PS; }
  if (I) { if (rv != "") rv += ", "; rv += "I "; rv += IS; }
  if (O) { if (rv != "") rv += ", "; rv += "O "; rv += OS; }
  return rv;
}
//---------------------------------------------------------------------------
int GetUID(TList *UIDs, int TableRow)
{
  return *(int*)UIDs->Items[TableRow - 1];
}
//---------------------------------------------------------------------------
# define SwapStr(C, A, B) C = A; A = B; B = C;
//---------------------------------------------------------------------------
void SwapUID(TList *UIDs, int TableRowA, int TableRowB)
{
  void *UIDA = UIDs->Items[TableRowA - 1];
  void *UIDB = UIDs->Items[TableRowB - 1];
  UIDs->Items[TableRowA - 1] = UIDB;
  UIDs->Items[TableRowB - 1] = UIDA;
}
//---------------------------------------------------------------------------
bool RestrictedChars(AnsiString Haystack, AnsiString DanceType)
{
  AnsiString Needle;
  if (DanceType == "Jm23") Needle="B ";
  if (DanceType == "MSet") Needle="B ";
  if (DanceType == "TrbR") Needle="B ";
  if (DanceType == "Reel") Needle="BPIO ";
  if (DanceType == "LigJ") Needle="BPI ";
  if (DanceType == "SinJ") Needle="BPI ";
  if (DanceType == "SlpJ") Needle="BPIO ";
  if (DanceType == "TrbJ") Needle="BPIO ";
  if (DanceType == "Horn") Needle="BPIO ";
  if (DanceType == "Trad") Needle="BPIO ";
  if (DanceType == "Prem") Needle="BPI ";
  if (DanceType == "PrCh") Needle="O ";
  if (DanceType == "Cham") Needle="O ";

  for (int i = 1; i <= Haystack.Length(); ++i)
    if (Needle.Pos(Haystack[i]) == 0) return true;
  return false;
}
//---------------------------------------------------------------------------
AnsiString DancerToGroupDanceType(TDancer *Dancer) // Returns "" on failure
{
  AnsiString GDT;

  enum Dances Dance = nil;
  if (Dancer->Dances[Group2Hand])      { Dance = Group2Hand; GDT = "2-Hand ";       }
  if (Dancer->Dances[Group3Hand])      { Dance = Group3Hand; GDT = "3-Hand ";       }
  if (Dancer->Dances[Group4Hand])      { Dance = Group4Hand; GDT = "4-Hand ";       }
  if (Dancer->Dances[GroupCeili])      { Dance = GroupCeili; GDT = "Ceili ";        }
  if (Dancer->Dances[Group4HandChamp]) { Dance = Group4HandChamp; GDT = "4-Hand Champ "; }
  if (Dancer->Dances[GroupCeiliChamp]) { Dance = GroupCeiliChamp; GDT = "Ceili Champ ";  }
  if (Dance == nil) return "";

  AnsiString GDA = GroupToString(Dancer->AgeGroup[Dance]);
  if (GDA == "") return "";
  return GDT + GDA;
}
//---------------------------------------------------------------------------
enum Dances GroupDanceTypeToDance(AnsiString GDT) // Returns nil on failure
{
  if (GDT.SubString(1, 7)  == "2-Hand ")       return Group2Hand;
  if (GDT.SubString(1, 7)  == "3-Hand ")       return Group3Hand;
  if (GDT.SubString(1, 13) == "4-Hand Champ ") return Group4HandChamp;
  if (GDT.SubString(1, 7)  == "4-Hand ")       return Group4Hand;
  if (GDT.SubString(1, 12) == "Ceili Champ ")  return GroupCeiliChamp;
  if (GDT.SubString(1, 6)  == "Ceili ")        return GroupCeili;
  return nil;
}
//---------------------------------------------------------------------------
AnsiString GroupDanceTypeToAgeGroup(AnsiString GDT) // Returns "" on failure
{
  enum Dances Dance = GroupDanceTypeToDance(GDT);
  switch(Dance)
  {
    case nil:        return "";
    case Group2Hand: GDT.Delete(1, 7);  break;
    case Group3Hand: GDT.Delete(1, 7);  break;
    case Group4Hand: GDT.Delete(1, 7);  break;
    case GroupCeili: GDT.Delete(1, 6);  break;
    case Group4HandChamp: GDT.Delete(1, 13);  break;
    case GroupCeiliChamp: GDT.Delete(1, 12);  break;
  }

  if (GDT == "") return ""; // No age group
  if (GDT == "All Ages") return "AA";
  if (GDT.Length() <= 6) return ""; // this length is impossible for either "Under N" and "Over N"

  char Decision;
  if      (GDT.SubString(1,6) == "Under ") { Decision = 'U'; GDT.Delete(1,6); }
  else if (GDT.SubString(1,5) == "Over ")  { Decision = 'O'; GDT.Delete(1,5); }
  else return ""; // Neither "Under" nor "Over" in GDT

  int N = GDT.ToIntDef(0);
  if (N == 0) return ""; // Incorrect age or No string data after "Under"/"Over"

  AnsiString rv = Decision;
  rv += N;
  return rv;
}
//---------------------------------------------------------------------------
int AddUID(TList *UIDs, int nUID)
{
  int *UID = new int;
  *UID = nUID;
  UIDs->Add(UID);
  return *UID;
}
//---------------------------------------------------------------------------
/*bool MatchDanceLine(AnsiString What, AnsiString Part1, AnsiString Part2)
{
  if(What.SubString(1, Part1.Length()) != Part1) return false;
  if(Part2 == NULL) return true;
  int DelimPos = What.Pos(" / ");
  if(DelimPos == 0) return false;
  return What.SubString(DelimPos + 3, Part2.Length()) == Part2;
}*/
bool MatchDanceLine(AnsiString What, AnsiString Part)
{
  return What.SubString(1, Part.Length()) == Part;
}
//---------------------------------------------------------------------------
/* UNUSED void TImportForm::ImportGroupDance(enum Dances Dance, int MaxParticipants, TDancer *Dancer, AnsiString &Storage)
{
  TDancer *TeamDancer;
  bool found = false;

  // Step 1. Find matching group dance
  for (int i = 0; i < Database->TotalDancers(); ++i)
  {
    TeamDancer = Database->GetDancerByIndex(i);
    if (!TeamDancer->isGroup) continue;

    // Step 1.1. Compare school, number of participants, and dance type
    if (TeamDancer->School != Dancer->School) continue;
    if (!TeamDancer->Dances[Dance]) continue;
    if (TeamStringLength(TeamDancer->Name) >= MaxParticipants) continue;

    // Step 1.2. If it's ceili, find it in storage and determine, if it's fairy reel or 8-hand reel
    if (Dance != GroupCeili) { found = true; break; }
    AnsiString StoredPattern = TeamDancer->Number;
    if (MaxParticipants == 6) StoredPattern += "=FR";
    if (MaxParticipants == 8) StoredPattern += "=8H";
    if(Storage.Pos(StoredPattern) != 0) { found = true; break; }
  }

  // Step 2. If no such group dance exist, create new.
  if (!found)
  {
    // Step 2.1. Determine new team number
    int Number = 1; while(Database->GetDancerByNumber((AnsiString)"T" + Number) != NULL) ++Number;

    // Step 2.2. Create this team and set a dance to it
    TeamDancer = Database->AddNewDancer();
    TeamDancer->Number = Number;
    TeamDancer->School = Dancer->School;
    TeamDancer->isGroup = true;
    TeamDancer->Dances[Dance] = true;
    TeamDancer->AgeGroup[Dance] = "AA";
    if (Dance == GroupCeili) { Storage += Number; Storage += ((MaxParticipants == 6) ? "=FR " : "=8H "); }
  }

  // Step 3. Add a participant to the team
  TeamDancer->Name = TeamStringAdd(TeamDancer->Name, Dancer->Name);
} */
//---------------------------------------------------------------------------
void TImportForm::TableFromDatabase()
{
  switch(CurrentPage)
  {
    case ltList:

      ClearTable(ListGrid,  UIDList);
      for (int i = 0; i < Database->TotalDancers(); ++i)
      {
        TDancer *Dancer = Database->GetDancerByIndex(i);
        if (Dancer->isGroup) continue;

        int Row = NewLineToTable(ListGrid);
        AddUID(UIDList, Dancer->UID);

        ListGrid->Cells[0][Row] = Dancer->Number;
        ListGrid->Cells[1][Row] = Dancer->Name;
        ListGrid->Cells[2][Row] = Dancer->School;
        ListGrid->Cells[3][Row] = Dancer->Age;
      }
      break;

    case ltSolo:

      ClearTable(SoloGrid,  UIDSolo);
      for (int i = 0; i < Database->TotalDancers(); ++i)
      {
        TDancer *Dancer = Database->GetDancerByIndex(i);
        if (Dancer->isGroup) continue;

        int Row = NewLineToTable(SoloGrid);
        AddUID(UIDSolo, Dancer->UID);

        SoloGrid->Cells[0][Row]  = Dancer->Number;
        SoloGrid->Cells[1][Row]  = Dancer->Name;
        SoloGrid->Cells[2][Row]  = Dancer->School;
        SoloGrid->Cells[3][Row]  = Dancer->Age;

        bool *D = Dancer->Dances;

        SoloGrid->Cells[4][Row]  = MakeBPIO(D[Jump23],              false,                 false,                  false);              //jump 23
        SoloGrid->Cells[5][Row]  = MakeBPIO(D[ModernSet],           false,                 false,                  false);              //mod set
        SoloGrid->Cells[6][Row]  = MakeBPIO(D[TrebleReel],          false,                 false,                  false);              //treb reel
        SoloGrid->Cells[7][Row]  = MakeBPIO(D[BeginnerReel],        D[PrimaryReel],        D[IntermedReel],        D[OpenReel]);        //reel
        SoloGrid->Cells[8][Row]  = MakeBPIO(D[BeginnerLightJig],    D[PrimaryLightJig],    D[IntermedLightJig],    false);              //light jig
        SoloGrid->Cells[9][Row]  = MakeBPIO(D[BeginnerSingleJig],   D[PrimarySingleJig],   D[IntermedSingleJig],   false);              //single jig
        SoloGrid->Cells[10][Row] = MakeBPIO(D[BeginnerSlipJig],     D[PrimarySlipJig],     D[IntermedSlipJig],     D[OpenSlipJig]);     //slip jig
        SoloGrid->Cells[11][Row] = MakeBPIO(D[BeginnerTrebleJig],   D[PrimaryTrebleJig],   D[IntermedTrebleJig],   D[OpenTrebleJig]);   //treble jig
        SoloGrid->Cells[12][Row] = MakeBPIO(D[BeginnerHornpipe],    D[PrimaryHornpipe],    D[IntermedHornpipe],    D[OpenHornpipe]);    //hornpipe
        SoloGrid->Cells[13][Row] = MakeBPIO(D[BeginnerTradSet],     D[PrimaryTradSet],     D[IntermedTradSet],     D[OpenTradSet]);     //trad. set
        SoloGrid->Cells[14][Row] = MakeBPIO(D[BeginnerPremiership], D[PrimaryPremiership], D[IntermedPremiership], false);              //prem
        SoloGrid->Cells[15][Row] = MakeBPIO(false,                  false,                 false,                  D[PreChampionship]); //pre chmp
        SoloGrid->Cells[16][Row] = MakeBPIO(false,                  false,                 false,                  D[Championship]);    //chmp
      }
      break;

    case ltGroup:

      ClearTable(GroupGrid, UIDGroup);
      for (int i = 0; i < Database->TotalDancers(); ++i)
      {
        TDancer *Dancer = Database->GetDancerByIndex(i);
        if (!Dancer->isGroup) continue;

        int Row = NewLineToTable(GroupGrid);
        AddUID(UIDGroup, Dancer->UID);

        GroupGrid->Cells[0][Row]  = "T" + (AnsiString)Dancer->Number;
        GroupGrid->Cells[1][Row]  = Dancer->Name;
        GroupGrid->Cells[2][Row]  = Dancer->School;
        GroupGrid->Cells[3][Row]  = DancerToGroupDanceType(Dancer);
      }

      // Sort this table
      bool resort;
      do
      {
        resort = false;
        for(int i = 2; i < GroupGrid->RowCount; ++i)
        {
          if (GroupGrid->Cells[0][i].SubString(2,GroupGrid->Cells[0][i].Length() - 1).ToInt() < GroupGrid->Cells[0][i - 1].SubString(2,GroupGrid->Cells[0][i - 1].Length() - 1).ToInt())
          {
            AnsiString C;
            SwapStr(C, GroupGrid->Cells[0][i - 1], GroupGrid->Cells[0][i]);
            SwapStr(C, GroupGrid->Cells[1][i - 1], GroupGrid->Cells[1][i]);
            SwapStr(C, GroupGrid->Cells[2][i - 1], GroupGrid->Cells[2][i]);
            SwapStr(C, GroupGrid->Cells[3][i - 1], GroupGrid->Cells[3][i]);
            SwapUID(UIDGroup, i - 1, i);
            resort = true;
            break;
          }
        }
      }
      while (resort);
      break;
  }
}
//---------------------------------------------------------------------------
void TImportForm::TableToDatabase()
{
  switch(CurrentPage)
  {
    case ltList:

      // Remove all solo dancers from database if dancers list is clean. Do it from end so deletion will not cause item skipping.
      if (IsTableEmpty(ListGrid))
      {
        Database->RemoveAll(false);
        return;
      }

      // Remove dancers from database if they were deleted from dancers list, and alter information for all others.
      // Do it from end so deletion will not cause item skipping.
      for(int i = Database->TotalDancers() - 1; i >= 0; --i)
      {
        bool exist = false;
        TDancer *Dancer = Database->GetDancerByIndex(i);
        if (Dancer->isGroup) continue;

        for (int Row = 1; Row < ListGrid->RowCount; ++Row)
        {
          if (Dancer->UID == GetUID(UIDList, Row))
          {
            Dancer->Number = ListGrid->Cells[0][Row].ToIntDef(0); // Will be catched at window close
            Dancer->Name   = ListGrid->Cells[1][Row];
            Dancer->School = ListGrid->Cells[2][Row];
            Dancer->Age    = ListGrid->Cells[3][Row].ToIntDef(0); // Will be catched at window close
            if (Dancer->Age > 1000) Dancer->Age = CurrentYear() - Dancer->Age - 1;
            exist = true;
            break;
          }
        }
        if (!exist)
        {
          AnsiString msg = "Участник " + Dancer->Name + " удален из базы.";
          Application->MessageBox(msg.c_str(), "Удаление участника", MB_OK);
          Database->DeleteByUID(Dancer->UID);
        }
      }

      // Add new dancers to database, if they were not in list already
      for (int Row = 1; Row < ListGrid->RowCount; ++Row)
      {
        bool exist = false;

        for(int i = 0; i < Database->TotalDancers(); ++i)
        {
          TDancer *Dancer = Database->GetDancerByIndex(i);
          if (Dancer->isGroup) continue;

          if (Dancer->UID == GetUID(UIDList, Row))
          {
            exist = true;
            break;
          }
        }
        if (!exist)
        {
          TDancer *Dancer = Database->AddNewDancer();
          Dancer->Number  = ListGrid->Cells[0][Row].ToIntDef(0); // Will be catched at window close
          Dancer->Name    = ListGrid->Cells[1][Row];
          Dancer->School  = ListGrid->Cells[2][Row];
          Dancer->Age     = ListGrid->Cells[3][Row].ToIntDef(0); // Will be catched at window close
        }
      }

      // Everything is ok
      break;

    case ltSolo:

      if (IsTableEmpty(SoloGrid)) return; // This may be only if no dancers in database

      // Fill dancers' solo dances
      for (int Row = 1; Row < SoloGrid->RowCount; ++Row)
      {
        for(int i = 0; i < Database->TotalDancers(); ++i)
        {
          TDancer *Dancer = Database->GetDancerByIndex(i);
          if (Dancer->isGroup) continue;
          if (Dancer->UID != GetUID(UIDSolo, Row)) continue;

          // Dancer will exist in table, because this table is generated using list of them.
          bool *D = Dancer->Dances;
          if
          (
            !ReadBPIO(SoloGrid->Cells[4][Row],  &D[Jump23],              NULL,                   NULL,                    NULL)                || //jump 23
            !ReadBPIO(SoloGrid->Cells[5][Row],  &D[ModernSet],           NULL,                   NULL,                    NULL)                || //mod set
            !ReadBPIO(SoloGrid->Cells[6][Row],  &D[TrebleReel],          NULL,                   NULL,                    NULL)                || //treb reel
            !ReadBPIO(SoloGrid->Cells[7][Row],  &D[BeginnerReel],        &D[PrimaryReel],        &D[IntermedReel],        &D[OpenReel])        || //reel
            !ReadBPIO(SoloGrid->Cells[8][Row],  &D[BeginnerLightJig],    &D[PrimaryLightJig],    &D[IntermedLightJig],    NULL)                || //light jig
            !ReadBPIO(SoloGrid->Cells[9][Row],  &D[BeginnerSingleJig],   &D[PrimarySingleJig],   &D[IntermedSingleJig],   NULL)                || //single jig
            !ReadBPIO(SoloGrid->Cells[10][Row],  &D[BeginnerSlipJig],     &D[PrimarySlipJig],     &D[IntermedSlipJig],     &D[OpenSlipJig])     || //slip jig
            !ReadBPIO(SoloGrid->Cells[11][Row], &D[BeginnerTrebleJig],   &D[PrimaryTrebleJig],   &D[IntermedTrebleJig],   &D[OpenTrebleJig])   || //treble jig
            !ReadBPIO(SoloGrid->Cells[12][Row], &D[BeginnerHornpipe],    &D[PrimaryHornpipe],    &D[IntermedHornpipe],    &D[OpenHornpipe])    || //hornpipe
            !ReadBPIO(SoloGrid->Cells[13][Row], &D[BeginnerTradSet],     &D[PrimaryTradSet],     &D[IntermedTradSet],     &D[OpenTradSet])     || //trad. set
            !ReadBPIO(SoloGrid->Cells[14][Row], &D[BeginnerPremiership], &D[PrimaryPremiership], &D[IntermedPremiership], NULL)                || //prem
            !ReadBPIO(SoloGrid->Cells[15][Row], NULL,                    NULL,                   NULL,                    &D[PreChampionship]) || //pre chmp
            !ReadBPIO(SoloGrid->Cells[16][Row], NULL,                    NULL,                   NULL,                    &D[Championship])       //chmp
          )
          {
            AnsiString msg = "В танцах участника " + Dancer->Name + " указаны неверные уровни.\nВозможно, некоторые из заявленных им танцев добавлены не будут. Проверьте!";
            Application->MessageBox(msg.c_str(),"Ошибка чтения BPIO",MB_OK);
          }
          break;
        }
      }

      // Everything is ok
      break;

    case ltGroup:

      // Clean out all group dances for any solo dancers
      for(int i = 0; i < Database->TotalDancers(); ++i)
      {
        TDancer *Dancer = Database->GetDancerByIndex(i);
        if (Dancer->isGroup) continue;
        Dancer->Dances[Group2Hand] = false;
        Dancer->Dances[Group3Hand] = false;
        Dancer->Dances[Group4Hand] = false;
        Dancer->Dances[GroupCeili] = false;
        Dancer->Dances[Group4HandChamp] = false;
        Dancer->Dances[GroupCeiliChamp] = false;
        Dancer->AgeGroup[Group2Hand] = "";
        Dancer->AgeGroup[Group3Hand] = "";
        Dancer->AgeGroup[Group4Hand] = "";
        Dancer->AgeGroup[GroupCeili] = "";
        Dancer->AgeGroup[Group4HandChamp] = "";
        Dancer->AgeGroup[GroupCeiliChamp] = "";
      }

      // Remove all teams from database if team list is clean. Do it from end so deletion will not cause item skipping.
      if (IsTableEmpty(GroupGrid))
      {
        Database->RemoveAll(true);
        return;
      }

      // Remove teams from database if they were deleted from team list, and alter information for all others.
      // Do it from end so deletion will not cause item skipping.
      for(int i = Database->TotalDancers() - 1; i >= 0; --i)
      {
        bool exist = false;
        TDancer *Dancer = Database->GetDancerByIndex(i);
        if (!Dancer->isGroup) continue;

        for (int Row = 1; Row < GroupGrid->RowCount; ++Row)
        {
          if (Dancer->UID == GetUID(UIDGroup, Row))
          {
            // We assume that we have done check before writing table to database

            AnsiString NS = GroupGrid->Cells[0][Row];
            NS.Delete(1,1);
            Dancer->Number  = NS.ToIntDef(0); // Will be catched at window close

            Dancer->isGroup = true;
            Dancer->Name    = GroupGrid->Cells[1][Row];
            Dancer->School  = GroupGrid->Cells[2][Row];

            Dancer->Dances[Group2Hand] = false;
            Dancer->Dances[Group3Hand] = false;
            Dancer->Dances[Group4Hand] = false;
            Dancer->Dances[GroupCeili] = false;
            Dancer->Dances[Group4HandChamp] = false;
            Dancer->Dances[GroupCeiliChamp] = false;

            enum Dances Dance       = GroupDanceTypeToDance(GroupGrid->Cells[3][Row]);
            if (Dance != nil)
            {
              Dancer->Dances[Dance]   = true;
              Dancer->AgeGroup[Dance] = GroupDanceTypeToAgeGroup(GroupGrid->Cells[3][Row]);
            }

            exist = true;
            break;
          }
        }
        if (!exist)
        {
          AnsiString msg = "Команда " + Dancer->Name + " удалена из базы.";
          Application->MessageBox(msg.c_str(), "Удаление команды", MB_OK);
          Database->DeleteByUID(Dancer->UID);
        }
      }

      // Add new teams to database, if they were not in list already
      for (int Row = 1; Row < GroupGrid->RowCount; ++Row)
      {
        bool exist = false;
        for(int i = 0; i < Database->TotalDancers(); ++i)
        {
          TDancer *Dancer = Database->GetDancerByIndex(i);
          if (!Dancer->isGroup) continue;

          if (Dancer->UID == GetUID(UIDGroup, Row))
          {
            exist = true;
            break;
          }
        }
        if (!exist)
        {
          TDancer *Dancer = Database->AddNewDancer();

          AnsiString NS = GroupGrid->Cells[0][Row];
          NS.Delete(1,1);
          Dancer->Number  = NS.ToIntDef(0); // Will be catched at window close

          Dancer->isGroup = true;
          Dancer->Name    = GroupGrid->Cells[1][Row];
          Dancer->School  = GroupGrid->Cells[2][Row];

          enum Dances Dance       = GroupDanceTypeToDance(GroupGrid->Cells[3][Row]);
          if (Dance != nil)
          {
            Dancer->Dances[Dance]   = true;
            Dancer->AgeGroup[Dance] = GroupDanceTypeToAgeGroup(GroupGrid->Cells[3][Row]);
          }
        }
      }

      // Search every solo dancer to match group dance
      for(int i = 0; i < Database->TotalDancers(); ++i)
      {
        TDancer *Dancer = Database->GetDancerByIndex(i);
        if (!Dancer->isGroup) continue;

        enum Dances Dance = nil;
        if (Dancer->Dances[Group2Hand]) { Dance = Group2Hand; }
        if (Dancer->Dances[Group3Hand]) { Dance = Group3Hand; }
        if (Dancer->Dances[Group4Hand]) { Dance = Group4Hand; }
        if (Dancer->Dances[GroupCeili]) { Dance = GroupCeili; }
        if (Dancer->Dances[Group4HandChamp]) { Dance = Group4HandChamp; }
        if (Dancer->Dances[GroupCeiliChamp]) { Dance = GroupCeiliChamp; }
        if (Dance == nil) // Will be catched at window close
        {
          // Why tell about this earlier that user requested it?
          // AnsiString msg = "Команда Т" + (AnsiString)Dancer->Number + " не зарегистрирована на групповые танцы.";
          // Application->MessageBox(msg.c_str(), "Ошибка базы данных", MB_OK);
          continue;
        }

        for(int j = 0; j < TeamStringLength(Dancer->Name); ++j)
        {
          bool found = false;
          AnsiString DesiredName = TeamStringGet(Dancer->Name, j);
          TDancer *DesiredDancer;
          for(int k = 0; k < Database->TotalDancers(); ++k)
          {
            DesiredDancer = Database->GetDancerByIndex(k);
            if (DesiredDancer->isGroup) continue;
            if ((DesiredDancer->Name == DesiredName) && (DesiredDancer->School == Dancer->School)) { found = true; break; }
          }
          if (found)
          {
            DesiredDancer->Dances[Dance]   = true;
            DesiredDancer->AgeGroup[Dance] = Dancer->AgeGroup[Dance];
          }
          else
          {
            AnsiString msg = "Участник " + DesiredName + " из команды Т" + Dancer->Number + " не зарегистрирован на феш или зарегистрирован от другой школы.\nЕго невозможно пометить как участвующего в групповых танцах. Проверьте его имя и фамилию." ;
            Application->MessageBox(msg.c_str(), "Незарегистрированный участник команды", MB_OK);
          }
        }
      }

      // Everything is ok
      break;
  }
}
//---------------------------------------------------------------------------
bool TImportForm::Import(enum ListType Type)
{
  bool rv = true;
  if(!ImportDialog->Execute()) return false;
  ImportWarning->Show();
  Application->ProcessMessages();

  // Open Excel file
  TExcel *Excel;
  try { Excel = new TExcel(ImportDialog->FileName, xlOpen); }
  catch(...)
  {
    Application->MessageBox("Невозможно открыть импортируемый файл", "Ошибка открытия файла", MB_OK);
    ImportWarning->Hide();
    return false;
  }

  switch (Type)
  {
    case ltList:
    {
      ImportWarning->Caption = "Производится импорт списка участников...";
      Application->ProcessMessages();

      AnsiString Headers[9];

      // Check if this is correct file
      Excel->GetRow(Headers, 3, 10);
      if
      (
        (Headers[1] != "Comp #") ||
        (Headers[2] != "Dancer") ||
        (Headers[3] != "DOB") ||
        (Headers[4] != "Age") ||
        (Headers[5] != "Sex") ||
        (Headers[6] != "School") ||
        (Headers[7] != "Solo Dances") ||
        (Headers[8] != "Premierships") ||
        (Headers[9] != "Ceili Dances")
      )
      {
        Application->MessageBox("Неправильный заголовок в файле.\nПроверьте, тот ли файл вы открыли?","Некорректный файл",MB_OK);
        rv = false;
        break;
      }

      // Ask if we don't want to overwrite data
      bool empty = true;
      for(int i = 0; i < Database->TotalDancers(); ++i)
      {
        TDancer *Dancer = Database->GetDancerByIndex(i);
        if (!Dancer->isGroup) { empty = false; break; }
      }
      if (!empty)
      {
        int q = Application->MessageBox("Внимание! Старый список участников будет перезаписан, а таблица танцев будут очищена.\nПродолжить импортирование?","Перезапись данных",MB_YESNO);
        if (q != IDYES) { rv = false; break; }
      }

      // Clear the database of solo dancers
      Database->RemoveAll(false);
      int Number = 0;

      // Clear dances grid to avoid error if it is selected
      for (int i = 1; i < SoloGrid->RowCount; ++i) for (int j = 4; j < SoloGrid->ColCount; ++j) SoloGrid->Cells[j][i] = "";

      // Fill the table
      for (int ExcelRow = 4; ; ++ExcelRow)
      {
        AnsiString Data[7];
        Excel->GetRow(Data, ExcelRow, 7);

        if ((Data[0] == "") && (Data[1] == "") && (Data[2] == "") && (Data[3] == "") && (Data[4] == "") && (Data[5] == "") && (Data[6] == "")) break; // End of the file

        TDancer *Dancer = Database->AddNewDancer();

        // For now, dancer's name is in right order, so there's no need for next two commented parts:
        /* if (Data[2].Pos(", ") == 0)
        {
          AnsiString errmsg = "В импортируемом файле у участника " + Data[2] + " имя указано неправильно (не через запятую).\nИсправьте его в таблице.";
          Application->MessageBox(errmsg.c_str(),"Некорректный файл",MB_OK);
          Data[2] = Data[2] + ",...";
        } */
        Dancer->isGroup = false;
        Dancer->Number  = ++Number;
        Dancer->Name    = Data[2].Trim(); /* Data[2].SubString(Data[2].Pos(", ") + 2, Data[2].Length() - Data[2].Pos(", ") - 1).Trim() + " " + Data[2].SubString(1, Data[2].Pos(", ") - 1).Trim(); */
        Dancer->School  = Data[6].Trim();
        Dancer->Age     = Data[4].ToIntDef(0);
        if (Dancer->Age <= 0)
        {
          AnsiString errmsg = "В импортируемом файле у участника " + Data[1] + " указан неправильный возраст " + Data[3] + ".\nИсправьте его в таблице.";
          Application->MessageBox(errmsg.c_str(),"Некорректный файл",MB_OK);
        }
      }
      break;
    }
    case ltGroup:
    {
      // Check if we have participants table
      if (Database->TotalDancers() == 0)
      {
        Application->MessageBox("Сначала загрузите файл с участниками феша.","Список участников пуст",MB_OK);
        rv = false;
        break;
      }

      enum ListType what = ltList;
      int GroupNumber = 0;
      for(int ExcelRow = 0; ; ExcelRow += 1)
      {
        bool ok = false;
        if(what == ltList)
        {
          AnsiString Data = Excel->GetCell(ExcelRow, 0);
          if (Data == "START IMPORT GROUP") what = ltGroup;
          if (Data == "START IMPORT SOLO") what = ltSolo;
          if(what == ltList)
          {
            Application->MessageBox("Неверный формат файла.","Неверный формат файла",MB_OK);
            rv = false;
            break;
          }
          continue;
        }
        else
        {
          AnsiString School = Excel->GetCell(ExcelRow, 0).Trim();
          if (School == "") break;
          if (what == ltGroup)
          {
            AnsiString DanceName = Excel->GetCell(ExcelRow, 1).Trim() + " All Ages";
            AnsiString Team      = Excel->GetCell(ExcelRow, 2).Trim();

            TDancer *Dancer = Database->AddNewDancer();
            Dancer->isGroup = true;
            Dancer->Number  = ++GroupNumber;
            Dancer->Name    = Team;
            Dancer->School  = School;

            Dancer->Dances[Group2Hand] = false;
            Dancer->Dances[Group3Hand] = false;
            Dancer->Dances[Group4Hand] = false;
            Dancer->Dances[GroupCeili] = false;
            Dancer->Dances[Group4HandChamp] = false;
            Dancer->Dances[GroupCeiliChamp] = false;

            enum Dances Dance = GroupDanceTypeToDance(DanceName);
            if (Dance != nil)
            {
              Dancer->Dances[Dance]   = true;
              Dancer->AgeGroup[Dance] = GroupDanceTypeToAgeGroup(DanceName);
              ok = true;
            }
            if(!ok)
            {
              AnsiString errmsg = "У команды " + Team + " из школы " + School + " неверный тип танца: " + DanceName + ". Поправьте танец в таблице.";
              Application->MessageBox(errmsg.c_str(),"Неверный формат файла",MB_OK);
            }
          }
          else /* (what == ltSolo) */
          {
            AnsiString DancerName  = Excel->GetCell(ExcelRow, 1).Trim();

            AnsiString DanceJ23    = Excel->GetCell(ExcelRow, 2);
            AnsiString DanceModSet = Excel->GetCell(ExcelRow, 3);
            AnsiString DanceTrReel = Excel->GetCell(ExcelRow, 4);
            AnsiString DanceReel   = Excel->GetCell(ExcelRow, 5);
            AnsiString DanceLight  = Excel->GetCell(ExcelRow, 6);
            AnsiString DanceSingle = Excel->GetCell(ExcelRow, 7);
            AnsiString DanceSlip   = Excel->GetCell(ExcelRow, 8);
            AnsiString DanceTreble = Excel->GetCell(ExcelRow, 9);
            AnsiString DanceHorn   = Excel->GetCell(ExcelRow, 10);
            AnsiString DanceTrad   = Excel->GetCell(ExcelRow, 11);
            AnsiString DancePrem   = Excel->GetCell(ExcelRow, 12);
            AnsiString DancePreCh  = Excel->GetCell(ExcelRow, 13);
            AnsiString DanceChamp  = Excel->GetCell(ExcelRow, 14);

            for(int i = 0; i < Database->TotalDancers(); ++i)
            {
              TDancer *Dancer = Database->GetDancerByIndex(i);
              if (Dancer->isGroup) continue;
              if (Dancer->Name != DancerName || Dancer->School != School) continue;

              bool *D = Dancer->Dances;

              if(D[Jump23] || D[ModernSet] || D[TrebleReel] || D[BeginnerReel] || D[PrimaryReel] || D[IntermedReel] || D[OpenReel] || D[BeginnerLightJig] || D[PrimaryLightJig] || D[IntermedLightJig] || D[BeginnerSingleJig] || D[PrimarySingleJig] || D[IntermedSingleJig] || D[BeginnerSlipJig] || D[PrimarySlipJig] || D[IntermedSlipJig] || D[OpenSlipJig] || D[BeginnerTrebleJig] || D[PrimaryTrebleJig] || D[IntermedTrebleJig] || D[OpenTrebleJig] || D[BeginnerHornpipe] || D[PrimaryHornpipe] || D[IntermedHornpipe] || D[OpenHornpipe] || D[BeginnerTradSet] || D[PrimaryTradSet] || D[IntermedTradSet] || D[OpenTradSet] || D[BeginnerPremiership] || D[PrimaryPremiership] || D[IntermedPremiership] || D[PreChampionship] || D[Championship])
              {
                AnsiString msg = "У участника " + Dancer->Name + " уже есть регистрации. Проверьте!";
                Application->MessageBox(msg.c_str(),"Ошибка регистраций",MB_OK);
              }

              if
              (
                !ReadBPIO(DanceJ23,    &D[Jump23],              NULL,                   NULL,                    NULL)                || //jump 23
                !ReadBPIO(DanceModSet, &D[ModernSet],           NULL,                   NULL,                    NULL)                || //mod set
                !ReadBPIO(DanceTrReel, &D[TrebleReel],          NULL,                   NULL,                    NULL)                || //treb reel
                !ReadBPIO(DanceReel,   &D[BeginnerReel],        &D[PrimaryReel],        &D[IntermedReel],        &D[OpenReel])        || //reel
                !ReadBPIO(DanceLight,  &D[BeginnerLightJig],    &D[PrimaryLightJig],    &D[IntermedLightJig],    NULL)                || //light jig
                !ReadBPIO(DanceSingle, &D[BeginnerSingleJig],   &D[PrimarySingleJig],   &D[IntermedSingleJig],   NULL)                || //single jig
                !ReadBPIO(DanceSlip,   &D[BeginnerSlipJig],     &D[PrimarySlipJig],     &D[IntermedSlipJig],     &D[OpenSlipJig])     || //slip jig
                !ReadBPIO(DanceTreble, &D[BeginnerTrebleJig],   &D[PrimaryTrebleJig],   &D[IntermedTrebleJig],   &D[OpenTrebleJig])   || //treble jig
                !ReadBPIO(DanceHorn,   &D[BeginnerHornpipe],    &D[PrimaryHornpipe],    &D[IntermedHornpipe],    &D[OpenHornpipe])    || //hornpipe
                !ReadBPIO(DanceTrad,   &D[BeginnerTradSet],     &D[PrimaryTradSet],     &D[IntermedTradSet],     &D[OpenTradSet])     || //trad. set
                !ReadBPIO(DancePrem,   &D[BeginnerPremiership], &D[PrimaryPremiership], &D[IntermedPremiership], NULL)                || //prem
                !ReadBPIO(DancePreCh,  NULL,                    NULL,                   NULL,                    &D[PreChampionship]) || //pre chmp
                !ReadBPIO(DanceChamp,  NULL,                    NULL,                   NULL,                    &D[Championship])       //chmp
              )
              {
                AnsiString msg = "В танцах участника " + Dancer->Name + " указаны неверные уровни.\nВозможно, некоторые из заявленных им танцев добавлены не будут. Проверьте!";
                Application->MessageBox(msg.c_str(),"Ошибка чтения BPIO",MB_OK);
              }

              if(!(D[Jump23] || D[ModernSet] || D[TrebleReel] || D[BeginnerReel] || D[PrimaryReel] || D[IntermedReel] || D[OpenReel] || D[BeginnerLightJig] || D[PrimaryLightJig] || D[IntermedLightJig] || D[BeginnerSingleJig] || D[PrimarySingleJig] || D[IntermedSingleJig] || D[BeginnerSlipJig] || D[PrimarySlipJig] || D[IntermedSlipJig] || D[OpenSlipJig] || D[BeginnerTrebleJig] || D[PrimaryTrebleJig] || D[IntermedTrebleJig] || D[OpenTrebleJig] || D[BeginnerHornpipe] || D[PrimaryHornpipe] || D[IntermedHornpipe] || D[OpenHornpipe] || D[BeginnerTradSet] || D[PrimaryTradSet] || D[IntermedTradSet] || D[OpenTradSet] || D[BeginnerPremiership] || D[PrimaryPremiership] || D[IntermedPremiership] || D[PreChampionship] || D[Championship]))
              {
                AnsiString msg = "У участника " + Dancer->Name + " не прочитано ни одной регистрации. Проверьте!";
                Application->MessageBox(msg.c_str(),"Ошибка регистраций",MB_OK);
              }

              ok = true;
              break;
            }
            if(!ok)
            {
              AnsiString errmsg = "Участник " + DancerName + " из школы " + School + " не найден в списке регистраций.";
              Application->MessageBox(errmsg.c_str(),"Неверный формат файла",MB_OK);
            }

          }
        }
      }

      Application->MessageBox("Импорт завершён успешно.","Готово",MB_OK);
      break;
    }
    case ltSolo:
    {
      // (DON'T) Clear every group dances
      // Database->RemoveAll(true);

      // Check if we have participants table
      if (Database->TotalDancers() == 0)
      {
        Application->MessageBox("Сначала загрузите файл с участниками феша.","Список участников пуст",MB_OK);
        rv = false;
        break;
      }

      // This is for importing from feiskeeper that is no longer needed.
      /*
      bool Found;
      TDancer *Dancer;
      AnsiString School, Data, Storage = ""; enum {mmSchool, mmDancer, mmDance} Mode = mmSchool;
      for(int ExcelRow = 0; ; ExcelRow += 1)
      {
        Data = Excel->GetCell(ExcelRow, 0); // This may be a correct school name, or total price if we are at the end of file
        switch (Mode)
        {
          case mmSchool:
          {
            if (Data == "") break; // Complete
            School = Data.Trim();
            Mode = mmDancer;
            continue;
          }
          case mmDancer:
          {
            if (Data == "") { Mode = mmSchool; continue; }
            // Find matching dancer
            Found = false;
            for(int i = 0; i < Database->TotalDancers(); ++i)
            {
              Dancer = Database->GetDancerByIndex(i);
              if (Dancer->isGroup) continue;
              if (Dancer->Name.Trim() + " (" + Dancer->Age + ")"  != Data) continue;
              if (Dancer->School.Trim() != School)  continue;
              Found = true; break;
            }
            if(!Found) // We shall not add dancer that is not in database.
            {
              AnsiString errmsg = "Участника " + Data + " из школы " + School + " нет в списке участников.\nЕго танцы добавлены не будут.";
              Application->MessageBox(errmsg.c_str(),"Непонятный участник",MB_OK);
            }
            Mode = mmDance;
            continue;
          }
          case mmDance:
          {
            if (Data == "") { Mode = mmDancer; continue; }
            Data = AnsiReplaceStr(Data, "\xA0", " ").Trim();
            if (Found)
            {
                   if (Data == "Beginner Jump-2-3")          Dancer->Dances[Jump23]               = true;
              else if (Data == "Modern Set Competition")     Dancer->Dances[ModernSet]            = true;
              else if (Data == "Treble Reel Competition")    Dancer->Dances[TrebleReel]           = true;
              else if (Data == "Beginner Reel")              Dancer->Dances[BeginnerReel]         = true;
              else if (Data == "Beginner Light Jig")         Dancer->Dances[BeginnerLightJig]     = true;
              else if (Data == "Beginner Single Jig")        Dancer->Dances[BeginnerSingleJig]    = true;
              else if (Data == "Beginner Slip Jig")          Dancer->Dances[BeginnerSlipJig]      = true;
              else if (Data == "Beginner Treble Jig")        Dancer->Dances[BeginnerTrebleJig]    = true;
              else if (Data == "Beginner Hornpipe")          Dancer->Dances[BeginnerHornpipe]     = true;
              else if (Data == "Beginner Trad. Set")         Dancer->Dances[BeginnerTradSet]      = true;
              else if (Data == "Premiership - Beginner")     Dancer->Dances[BeginnerPremiership]  = true;
              else if (Data == "Primary Reel")               Dancer->Dances[PrimaryReel]          = true;
              else if (Data == "Primary Light Jig")          Dancer->Dances[PrimaryLightJig]      = true;
              else if (Data == "Primary Single Jig")         Dancer->Dances[PrimarySingleJig]     = true;
              else if (Data == "Primary Slip Jig")           Dancer->Dances[PrimarySlipJig]       = true;
              else if (Data == "Primary Treble Jig")         Dancer->Dances[PrimaryTrebleJig]     = true;
              else if (Data == "Primary Hornpipe")           Dancer->Dances[PrimaryHornpipe]      = true;
              else if (Data == "Primary Trad. Set")          Dancer->Dances[PrimaryTradSet]       = true;
              else if (Data == "Premiership - Primary")      Dancer->Dances[PrimaryPremiership]   = true;
              else if (Data == "Intermediate Reel")          Dancer->Dances[IntermedReel]         = true;
              else if (Data == "Intermediate Light Jig")     Dancer->Dances[IntermedLightJig]     = true;
              else if (Data == "Intermediate Single Jig")    Dancer->Dances[IntermedSingleJig]    = true;
              else if (Data == "Intermediate Slip Jig")      Dancer->Dances[IntermedSlipJig]      = true;
              else if (Data == "Intermediate Treble Jig")    Dancer->Dances[IntermedTrebleJig]    = true;
              else if (Data == "Intermediate Hornpipe")      Dancer->Dances[IntermedHornpipe]     = true;
              else if (Data == "Intermediate Trad. Set")     Dancer->Dances[IntermedTradSet]      = true;
              else if (Data == "Premiership - Intermediate") Dancer->Dances[IntermedPremiership]  = true;
              else if (Data == "Open Reel")                  Dancer->Dances[OpenReel]             = true;
              else if (Data == "Open Slip Jig")              Dancer->Dances[OpenSlipJig]          = true;
              else if (Data == "Open Treble Jig")            Dancer->Dances[OpenTrebleJig]        = true;
              else if (Data == "Open Hornpipe")              Dancer->Dances[OpenHornpipe]         = true;
              else if (Data == "Open Trad. Set")             Dancer->Dances[OpenTradSet]          = true;
              else if (Data == "Championship - Preliminary") Dancer->Dances[PreChampionship]      = true;
              else if (Data == "Championship - Open")        Dancer->Dances[Championship]         = true;
              else if (Data == "Two Hand Figure")            ImportGroupDance(Group2Hand, 2, Dancer, Storage);
              else if (Data == "Three Hand Figure")          ImportGroupDance(Group3Hand, 3, Dancer, Storage);
              else if (Data == "Four Hand Reel")             ImportGroupDance(Group4Hand, 4, Dancer, Storage);
              else if (Data == "Fairy Reel")                 ImportGroupDance(GroupCeili, 6, Dancer, Storage);
              else if (Data == "Ceili")                      ImportGroupDance(GroupCeili, 8, Dancer, Storage);
              else if (Data == "Tara Reel")                  ImportGroupDance(GroupCeili, 8, Dancer, Storage);
              else
              {
                AnsiString errmsg = "У участника " + Dancer->Name + " из школы " + School + " обнаружен неизвестный танец: " + Data + ".\nДанный танец добавлен не будет.";
                Application->MessageBox(errmsg.c_str(),"Непонятный танец",MB_OK);
              }
            }
            continue;
          }
        }
        Application->MessageBox("Импорт завершён успешно.","Готово",MB_OK);
        break;
      } */

      // This is for importing from now-actual gofeis.
      AnsiString ImportResults = "";
      AnsiString Sheets[] = {"Beginner", "Beginner Premiership", "Primary", "Primary Premiership", "Intermediate", "Intermediate Premiership", "Open", "Preliminary Championship", "Open Championship"}; // [TODO]: Modern set and treble reel is yet to be supported, as well as Ceili.
      for (int ish = 0; ish < 9; ++ish)
      {
        if(!Excel->SelectSheet(Sheets[ish]))
        {
          AnsiString sh = "В файле не обнаружена страница " + Sheets[ish] + ". Возможно, на этот танец вообще нет регистраций.";
          Application->MessageBox(sh.c_str(),"Не обнаружена страница");
          continue;
        }

        bool Found;
        TDancer *Dancer;
        AnsiString School, Data;
        enum Dances CurrentDance = nil;
        int ExcelRow = 0;
        int EmptyLines = 0;
        for(;;ExcelRow += 1)
        {
          Data = Excel->GetCell(ExcelRow, 0);
          if (Data == "Number #") continue;
          else if (Data == "" || Data.Length() < 5) // Dancer line
          {
            // For now: dancer name = column 1, school = column 5. May change in the future.
            Data = Excel->GetCell(ExcelRow, 1).Trim();
            //while (Data.Pos("  ")) Data.Delete(Data.Pos("  "), 1);
            School = Excel->GetCell(ExcelRow, 5).Trim();
            if(Data == "" && School == "") // Empty line, end of the dance
            {
              if (++EmptyLines > 3) break; // Fourth consecutive empty line = end of page
              CurrentDance = nil;
              continue;
            }
            else
            {
              EmptyLines = 0;
            }
            if(Data == "" || School == "")
            {
              AnsiString errmsg = Sheets[ish] + ", строка " + (AnsiString)(ExcelRow + 1) + ": участник с пустым именем (" + Data + ") или школой (" + School + "). Участник добавлен не будет.";
              Application->MessageBox(errmsg.c_str(),"Неверный формат файла",MB_OK);
              continue;
            }
            if (CurrentDance == nil)
            {
              AnsiString errmsg = Sheets[ish] + ", строка " + (AnsiString)(ExcelRow + 1) + ": участник " + Data + " идёт вне танца, возможно, файл обрезан сверху. Участник добавлен не будет.";
              Application->MessageBox(errmsg.c_str(),"Неверный формат файла",MB_OK);
              continue;
            }
            // Find matching dancer
            Found = false;
            for(int i = 0; i < Database->TotalDancers(); ++i)
            {
              Dancer = Database->GetDancerByIndex(i);
              if (Dancer->isGroup) continue;
              if (Dancer->Name.Trim() != Data) continue;
              if (Dancer->School.Trim() != School && Dancer->School.Trim() != "(Non-WIDA) " + School) continue;
              Found = true; break;
            }
            if(!Found) // We shall not add dancer that is not in database.
            {
              AnsiString errmsg = Sheets[ish] + ", строка " + (AnsiString)(ExcelRow + 1) + ": участника " + Data + " из школы " + School + " нет в списке участников.\nЕго танцы добавлены не будут.";
              Application->MessageBox(errmsg.c_str(),"Непонятный участник",MB_OK);
            }
            else
            {
              Dancer->Dances[CurrentDance] = true;
            }
          }
          else // Dance type
          {
            /*AnsiString SkipTest = "";
            for(int cp = 1; cp <= Data.Length(); ++cp) if (!((AnsiString)"0123456789").Pos(Data[cp])) SkipTest += Data[cp];
            if(SkipTest == "U" || SkipTest == "O" || SkipTest == "Under " || SkipTest == "Over ") continue;*/

            /*   if (MatchDanceLine(Data, "Jump 2-3", "Jump 2-3"))              CurrentDance = Jump23;
            else if (MatchDanceLine(Data, "Beginner", "Reel"))                  CurrentDance = BeginnerReel;
            else if (MatchDanceLine(Data, "Beginner", "Light Jig"))             CurrentDance = BeginnerLightJig;
            else if (MatchDanceLine(Data, "Beginner", "Single Jig"))            CurrentDance = BeginnerSingleJig;
            else if (MatchDanceLine(Data, "Beginner", "Slip Jig"))              CurrentDance = BeginnerSlipJig;
            else if (MatchDanceLine(Data, "Beginner", "Treble Jig"))            CurrentDance = BeginnerTrebleJig;
            else if (MatchDanceLine(Data, "Beginner", "Hornpipe"))              CurrentDance = BeginnerHornpipe;
            else if (MatchDanceLine(Data, "Beginner", "Traditional Set: "))     CurrentDance = BeginnerTradSet;
            else if (MatchDanceLine(Data, "Beginner Premiership", NULL))        CurrentDance = BeginnerPremiership;
            else if (MatchDanceLine(Data, "Primary", "Reel"))                   CurrentDance = PrimaryReel;
            else if (MatchDanceLine(Data, "Primary", "Light Jig"))              CurrentDance = PrimaryLightJig;
            else if (MatchDanceLine(Data, "Primary", "Single Jig"))             CurrentDance = PrimarySingleJig;
            else if (MatchDanceLine(Data, "Primary", "Slip Jig"))               CurrentDance = PrimarySlipJig;
            else if (MatchDanceLine(Data, "Primary", "Treble Jig"))             CurrentDance = PrimaryTrebleJig;
            else if (MatchDanceLine(Data, "Primary", "Hornpipe"))               CurrentDance = PrimaryHornpipe;
            else if (MatchDanceLine(Data, "Primary", "Traditional Set: "))      CurrentDance = PrimaryTradSet;
            else if (MatchDanceLine(Data, "Primary Premiership", NULL))         CurrentDance = PrimaryPremiership;
            else if (MatchDanceLine(Data, "Intermediate", "Reel"))              CurrentDance = IntermedReel;
            else if (MatchDanceLine(Data, "Intermediate", "Light Jig"))         CurrentDance = IntermedLightJig;
            else if (MatchDanceLine(Data, "Intermediate", "Single Jig"))        CurrentDance = IntermedSingleJig;
            else if (MatchDanceLine(Data, "Intermediate", "Slip Jig"))          CurrentDance = IntermedSlipJig;
            else if (MatchDanceLine(Data, "Intermediate", "Treble Jig"))        CurrentDance = IntermedTrebleJig;
            else if (MatchDanceLine(Data, "Intermediate", "Hornpipe"))          CurrentDance = IntermedHornpipe;
            else if (MatchDanceLine(Data, "Intermediate", "Traditional Set: ")) CurrentDance = IntermedTradSet;
            else if (MatchDanceLine(Data, "Intermediate Premiership", NULL))    CurrentDance = IntermedPremiership;
            else if (MatchDanceLine(Data, "Open", "Reel"))                      CurrentDance = OpenReel;
            else if (MatchDanceLine(Data, "Open", "Slip Jig"))                  CurrentDance = OpenSlipJig;
            else if (MatchDanceLine(Data, "Open", "Treble Jig"))                CurrentDance = OpenTrebleJig;
            else if (MatchDanceLine(Data, "Open", "Hornpipe"))                  CurrentDance = OpenHornpipe;
            else if (MatchDanceLine(Data, "Open", "Traditional Set: "))         CurrentDance = OpenTradSet;
            else if (MatchDanceLine(Data, "Preliminary Championship", NULL))    CurrentDance = PreChampionship;
            else if (MatchDanceLine(Data, "Open Championship", NULL))           CurrentDance = Championship; */

            // Remove "(...) " things
            AnsiString Data2 = "";
            bool Deletion = false;
            for (int sn = 1; sn <= Data.Length(); ++sn)
            {
              if (Deletion)
              {
                if (Data[sn] == ')')
                {
                  ++sn;
                  Deletion = false;
                }
              }
              else
              {
                if (Data[sn] == '(')
                {
                  Deletion = true;
                }
                else
                {
                  Data2 += Data[sn];
                }
              }
            }
            Data2 = Data2.Trim();

            ImportWarning->Caption = (AnsiString)"Импорт: " + Data2;
            Application->ProcessMessages();

                 if (Data2 == "Beginner Jump 2-3 Reel")                       CurrentDance = Jump23;
            else if (Data2 == "Beginner Reel")                                CurrentDance = BeginnerReel;
            else if (Data2 == "Beginner Light Jig")                           CurrentDance = BeginnerLightJig;
            else if (Data2 == "Beginner Single Jig")                          CurrentDance = BeginnerSingleJig;
            else if (Data2 == "Beginner Slip Jig")                            CurrentDance = BeginnerSlipJig;
            else if (Data2 == "Beginner Treble Jig")                          CurrentDance = BeginnerTrebleJig;
            else if (Data2 == "Beginner Treble Reel")                         CurrentDance = TrebleReel;
            else if (Data2 == "Beginner Hornpipe")                            CurrentDance = BeginnerHornpipe;
            else if (MatchDanceLine(Data2, "Beginner Traditional Set: "))     CurrentDance = BeginnerTradSet;
            else if (Data2 == "Beginner Premiership")                         CurrentDance = BeginnerPremiership;
            else if (Data2 == "Primary Reel")                                 CurrentDance = PrimaryReel;
            else if (Data2 == "Primary Light Jig")                            CurrentDance = PrimaryLightJig;
            else if (Data2 == "Primary Single Jig")                           CurrentDance = PrimarySingleJig;
            else if (Data2 == "Primary Slip Jig")                             CurrentDance = PrimarySlipJig;
            else if (Data2 == "Primary Treble Jig")                           CurrentDance = PrimaryTrebleJig;
            else if (Data2 == "Primary Hornpipe")                             CurrentDance = PrimaryHornpipe;
            else if (MatchDanceLine(Data2, "Primary Traditional Set: "))      CurrentDance = PrimaryTradSet;
            else if (Data2 == "Primary Premiership")                          CurrentDance = PrimaryPremiership;
            else if (Data2 == "Intermediate Reel")                            CurrentDance = IntermedReel;
            else if (Data2 == "Intermediate Light Jig")                       CurrentDance = IntermedLightJig;
            else if (Data2 == "Intermediate Single Jig")                      CurrentDance = IntermedSingleJig;
            else if (Data2 == "Intermediate Slip Jig")                        CurrentDance = IntermedSlipJig;
            else if (Data2 == "Intermediate Treble Jig")                      CurrentDance = IntermedTrebleJig;
            else if (Data2 == "Intermediate Hornpipe")                        CurrentDance = IntermedHornpipe;
            else if (MatchDanceLine(Data2, "Intermediate Traditional Set: ")) CurrentDance = IntermedTradSet;
            else if (Data2 == "Intermediate Premiership")                     CurrentDance = IntermedPremiership;
            else if (Data2 == "Open Reel")                                    CurrentDance = OpenReel;
            else if (Data2 == "Open Slip Jig")                                CurrentDance = OpenSlipJig;
            else if (Data2 == "Open Treble Jig")                              CurrentDance = OpenTrebleJig;
            else if (Data2 == "Open Treble Reel")                             CurrentDance = TrebleReel;
            else if (Data2 == "Open Hornpipe")                                CurrentDance = OpenHornpipe;
            else if (MatchDanceLine(Data2, "Open Traditional Set: "))         CurrentDance = OpenTradSet;
            else if (Data2 == "Preliminary Championship")                     CurrentDance = PreChampionship;
            else if (Data2 == "Open Championship")                            CurrentDance = Championship;
            else
            {
              AnsiString errmsg = Sheets[ish] + ", строка " + (AnsiString)(ExcelRow + 1) + ": неизвестный танец " + Data + ".\nДанный танец добавлен не будет.";
              Application->MessageBox(errmsg.c_str(),"Непонятный танец",MB_OK);
            }
          }
        }
        ImportResults += "\n" + Sheets[ish] + ": " + (AnsiString)ExcelRow + " строк";
      }
      AnsiString okmsg = "Импорт завершён успешно.\nРезультаты:" + ImportResults;
      Application->MessageBox(okmsg.c_str(),"Готово",MB_OK);
      break;
    }
  }

  // Close Excel file and hide warning
  delete Excel;
  ImportWarning->Hide();
  return rv;
}
//---------------------------------------------------------------------------
void TImportForm::SwitchToPage()
{
  CurrentPage = (enum ListType) ListChooseGroup->ItemIndex;

  switch (CurrentPage)
  {
    case ltList:
      SoloGrid->Hide();
      GroupGrid->Hide();
      AddFigureButton->Hide();
      DeleteFigureButton->Hide();
      ManageTeamButton->Hide();
      AddLineButton->Show();
      DeleteLineButton->Show();
      ResortButton->Show();
      ListGrid->Show();
      AddNameEdit->Show();
      ResortFigureButton->Hide();
      QualificationCheckBox->Hide();
      break;

    case ltSolo:
      GroupGrid->Hide();
      AddFigureButton->Hide();
      DeleteFigureButton->Hide();
      ManageTeamButton->Hide();
      AddLineButton->Hide();
      DeleteLineButton->Hide();
      ResortButton->Hide();
      ListGrid->Hide();
      SoloGrid->Show();
      AddNameEdit->Hide();
      ResortFigureButton->Hide();
      QualificationCheckBox->Hide();
      break;

    case ltGroup:
      SoloGrid->Hide();
      AddFigureButton->Show();
      DeleteFigureButton->Show();
      ManageTeamButton->Show();
      AddLineButton->Hide();
      DeleteLineButton->Hide();
      ResortButton->Hide();
      ListGrid->Hide();
      GroupGrid->Show();
      AddNameEdit->Hide();
      ResortFigureButton->Show();
      QualificationCheckBox->Show();
      break;
  }

  TableFromDatabase();
}
//---------------------------------------------------------------------------
bool TImportForm::CheckCurrentTable(bool LimitedCheck)  // Check if it is permitted to write active table into database
{
  switch(CurrentPage)
  {
    case ltSolo:

      // Checking for empty registration list is not performed due to dynamically generated list

      // Check if any dance has incorrect characters in its registration (but skip spaces)
      for (int i = 1; i < SoloGrid->RowCount; ++i)
      {
        for (int j = 4; j < SoloGrid->ColCount; ++j)
        {
          if (RestrictedChars(SoloGrid->Cells[j][i], SoloGrid->Cells[j][0]))
          {
            AnsiString msg = "У участника \"" + SoloGrid->Cells[1][i] + "\" непонятные символы в колонке \"" + SoloGrid->Cells[j][0] + "\".\nТам могут быть только символы B, P, I и O (и не во всех танцах - все).";
            Application->MessageBox(msg.c_str(), "Непонятный номер", MB_OK);
            SoloGrid->Row = i; SoloGrid->Col = j;
            return false;
          }
        }
      }

      // All checks passed
      break;

    case ltList:

      // Check if list is empty: it's ok
      if(IsTableEmpty(ListGrid)) return true;

      // Check if any dancer has incorrect number or age or empty name or school
      for (int i = 1; i < ListGrid->RowCount; ++i)
      {
        if(ListGrid->Cells[0][i].ToIntDef(0) <= 0)
        {
          AnsiString msg = "У участника \"" + ListGrid->Cells[1][i] + "\" непонятный номер.\nПросмотрите список еще раз.";
          Application->MessageBox(msg.c_str(), "Непонятный номер", MB_OK);
          ListGrid->Row = i; ListGrid->Col = 0;
          return false;
        }

        if(!LimitedCheck)
        {
          if(ListGrid->Cells[1][i] == "")
          {
            AnsiString msg = "У участника с номером " + ListGrid->Cells[0][i] + " не указано имя.\nВведите его в таблицу, или удалите участника.";
            Application->MessageBox(msg.c_str(), "Не указано имя участника", MB_OK);
            ListGrid->Row = i; ListGrid->Col = 1;
            return false;
          }
          if(ListGrid->Cells[2][i] == "")
          {
            AnsiString msg = "У участника с номером " + ListGrid->Cells[0][i] + " (" + ListGrid->Cells[1][i] + ") не указана школа.\nВпишите ее название, или фразу типа \"Dancer without school/self-taught\", если участник заявляется не от школы.";
            Application->MessageBox(msg.c_str(), "Не указана школа", MB_OK);
            ListGrid->Row = i; ListGrid->Col = 2;
            return false;
          }
          if(ListGrid->Cells[3][i].ToIntDef(0) <= 0)
          {
            AnsiString msg = "У участника с номером " + ListGrid->Cells[0][i] + " (" + ListGrid->Cells[1][i] + ") неверный возраст (" + ListGrid->Cells[2][i] + ").\nИсправьте его.";
            Application->MessageBox(msg.c_str(), "Неверный возраст", MB_OK);
            ListGrid->Row = i; ListGrid->Col = 3;
            return false;
          }
        }
      }

      // Check uniquity of solo dancers
      for (int i = 1; i < ListGrid->RowCount; ++i)
      {
        for (int j = 1; j < i; ++j)
        {
          if (ListGrid->Cells[0][i].ToInt() == ListGrid->Cells[0][j].ToInt())
          {
            AnsiString msg = "Участников с номером " + ListGrid->Cells[0][i] + " более одного.\nЭто, например, участники " + ListGrid->Cells[1][j] + " и " + ListGrid->Cells[1][i] + ".\nПросмотрите список еще раз!";
            Application->MessageBox(msg.c_str(), "Конфликт номеров", MB_OK);
            ListGrid->Row = i; ListGrid->Col = 0;
            return false;
          }
        }
      }

      // All checks passed
      break;

    case ltGroup:

      // Check if list is empty: it's ok
      if(IsTableEmpty(GroupGrid)) return true;

      // Check if any dancer has incorrect number or dance type, or empty name or school
      for (int i = 1; i < GroupGrid->RowCount; ++i)
      {
        AnsiString num1 = GroupGrid->Cells[0][i];

        if(num1.Length() < 1)
        {
          AnsiString msg = "У команды \"" + GroupGrid->Cells[1][i] + "\" пустой номер.\nВпишите номер команды в таблицу.";
          Application->MessageBox(msg.c_str(), "Пустой номер", MB_OK);
          GroupGrid->Row = i; GroupGrid->Col = 0;
          return false;
        }
        if(num1[1] != 'T')
        {
          AnsiString msg = "У команды \"" + GroupGrid->Cells[1][i] + "\" неверный номер.\nНомер команды должен начинаться с T, например T1.";
          Application->MessageBox(msg.c_str(), "Неверный номер", MB_OK);
          GroupGrid->Row = i; GroupGrid->Col = 0;
          return false;
        }
        if(num1.Delete(1, 1).ToIntDef(0) <= 0)
        {
          AnsiString msg = "У команды \"" + GroupGrid->Cells[1][i] + "\" непонятный номер.\nПросмотрите список еще раз.";
          Application->MessageBox(msg.c_str(), "Непонятный номер", MB_OK);
          GroupGrid->Row = i; GroupGrid->Col = 0;
          return false;
        }

        if(!LimitedCheck)
        {
          if(GroupGrid->Cells[1][i] == "")
          {
            AnsiString msg = "У команды с номером " + GroupGrid->Cells[0][i] + " не указан список участников.\nВведите его в таблицу (участники разделяются символом \"/\").";
            Application->MessageBox(msg.c_str(), "Не указан состав команды", MB_OK);
            GroupGrid->Row = i; GroupGrid->Col = 1;
            return false;
          }
          if(GroupGrid->Cells[2][i] == "")
          {
            AnsiString msg = "У команды с номером " + GroupGrid->Cells[0][i] + " не указана школа.\nВпишите ее название.";
            Application->MessageBox(msg.c_str(), "Не указана школа", MB_OK);
            GroupGrid->Row = i; GroupGrid->Col = 2;
            return false;
          }
          if(GroupDanceTypeToAgeGroup(GroupGrid->Cells[3][i]) == "")
          {
            AnsiString msg = "У команды с номером " + GroupGrid->Cells[0][i] + " указан неверный тип танца (" + GroupGrid->Cells[2][i] + ").\nТип танца может быть только 2-Hand/3-Hand/4-Hand/Ceili, также должна быть указана возрастная группа\nили All Ages (например, \"2-Hand Under 14\" или \"Ceili All Ages\").";
            Application->MessageBox(msg.c_str(), "Неверный тип танца", MB_OK);
            GroupGrid->Row = i; GroupGrid->Col = 3;
            return false;
          }
          // We may want to check quantity of participants in a team, but no; it will be done with database's ConsistencyCheck().
        }
      }

      // Check uniquity of teams
      for (int i = 1; i < GroupGrid->RowCount; ++i)
      {
        for (int j = 1; j < i; ++j)
        {
          AnsiString num1 = GroupGrid->Cells[0][i];
          AnsiString num2 = GroupGrid->Cells[0][j];
          if (num1.Delete(1, 1).ToInt() == num2.Delete(1, 1).ToInt())
          {
            AnsiString msg = "Команд с номером " + num1 + " более одного.\nЭто, например, команды " + GroupGrid->Cells[1][j] + "\nи " + GroupGrid->Cells[1][i] + ".\nИсправьте неверные номера.";
            Application->MessageBox(msg.c_str(), "Конфликт номеров", MB_OK);
            GroupGrid->Row = i; GroupGrid->Col = 0;
            return false;
          }
        }
      }

      // All checks passed
      break;
  }
  return true;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::ImportListButtonClick(TObject *Sender)
{
  if(!CheckCurrentTable(false)) return;
  TableToDatabase();
  if (!Import(ltList)) return;
  ListChooseGroup->ItemIndex = ltList;
  SwitchToPage();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::ImportSoloButtonClick(TObject *Sender)
{
  if(!CheckCurrentTable(false)) return;
  TableToDatabase();
  if (!Import(ltSolo)) return;
  ListChooseGroup->ItemIndex = ltSolo;
  SwitchToPage();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::ExitButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::ListChooseGroupClick(TObject *Sender)
{
  // Skip "backclicking" if selecting another page raised an error.
  if(ListChooseGroup->ItemIndex == CurrentPage) return;

  if(!CheckCurrentTable(false))
  {
    ListChooseGroup->ItemIndex = CurrentPage;
    return;
  }

  TableToDatabase();
  SwitchToPage();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::CheckRegButtonClick(TObject *Sender)
{
  if(!CheckCurrentTable(false)) return;

  TableToDatabase();

  TStringList *ErrorMessages = new TStringList;
  if (Database->ConsistencyCheck(ErrorMessages))
    Application->MessageBox("Списки не имеют ошибок", "Проверка завершена", MB_OK);
  else
  {
    LogForm->LogMemo->Lines->Clear();
    LogForm->LogMemo->Lines->AddStrings(ErrorMessages);
    LogForm->ShowModal();
  }
  delete ErrorMessages;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  if(!CheckCurrentTable(false)) { Action = caNone; return; }
  TableToDatabase();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::FormShow(TObject *Sender)
{
  TableFromDatabase();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::AddLineButtonClick(TObject *Sender)
{
  if(!CheckCurrentTable(true)) return;

  TableToDatabase();
  int Number = 1; while(Database->GetDancerByNumber(Number) != NULL) ++Number;
  TDancer *Dancer = Database->AddNewDancer();
  Dancer->Number = Number;
  Dancer->isGroup = false;
  TableFromDatabase();

  int Row = 1; while((Row < ListGrid->RowCount - 1) && (Dancer->UID != GetUID(UIDList, Row))) ++Row;
  ListGrid->Row = Row; ListGrid->Col = 1;
  ActiveControl = ListGrid;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::DeleteLineButtonClick(TObject *Sender)
{
  AnsiString Message = "Удалить участника \"" + ListGrid->Cells[1][ListGrid->Row] + "\" ?\nВсе его результаты также будут удалены!";
  int q = Application->MessageBox(Message.c_str(),"Удалить участника",MB_YESNO);
  if (q != IDYES) return;

  if(!CheckCurrentTable(true)) return;

  TableToDatabase();
  Database->DeleteByUID(GetUID(UIDList, ListGrid->Row)); // If this UID is not exist (inconsistent DB), then it is already deleted.
  TableFromDatabase();
  ActiveControl = ListGrid;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::AddFigureButtonClick(TObject *Sender)
{
  if(!CheckCurrentTable(true)) return;

  TableToDatabase();
  int Number = 1; while(Database->GetDancerByNumber((AnsiString)"T" + Number) != NULL) ++Number;
  TDancer *Dancer = Database->AddNewDancer();
  Dancer->Number = Number;
  Dancer->isGroup = true;
  TableFromDatabase();

  int Row = 1; while((Row < GroupGrid->RowCount - 1) && (Dancer->UID != GetUID(UIDGroup, Row))) ++Row;
  GroupGrid->Row = Row; GroupGrid->Col = 1;
  ActiveControl = GroupGrid;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::DeleteFigureButtonClick(TObject *Sender)
{
  AnsiString Message = "Удалить команду \"" + GroupGrid->Cells[1][GroupGrid->Row] + "\" ?\nВсе её результаты также будут удалены!";
  int q = Application->MessageBox(Message.c_str(),"Удалить команду",MB_YESNO);
  if (q != IDYES) return;

  if(!CheckCurrentTable(true)) return;

  TableToDatabase();
  Database->DeleteByUID(GetUID(UIDGroup, GroupGrid->Row));  // If this UID is not exist (inconsistent DB), then it is already deleted.
  TableFromDatabase();
  ActiveControl = GroupGrid;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::ManageTeamButtonClick(TObject *Sender)
{
  ManageTeamForm->School = GroupGrid->Cells[2][GroupGrid->Row];
  ManageTeamForm->TeamContents = GroupGrid->Cells[1][GroupGrid->Row];
  ManageTeamForm->ShowModal();
  GroupGrid->Cells[1][GroupGrid->Row] = ManageTeamForm->TeamContents;
  ActiveControl = GroupGrid;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::ResortButtonClick(TObject *Sender)
{
  TableToDatabase();

  // Just a bubble sort: no speed required.
  for(bool repeat = true; repeat;)
  {
    repeat = false;
    for(int i = 0; i < Database->TotalDancers(); ++i)
    {
      TDancer *DancerI = Database->GetDancerByIndex(i);
      if (DancerI->isGroup) continue;

      for(int j = i + 1; j < Database->TotalDancers(); ++j)
      {
        TDancer *DancerJ = Database->GetDancerByIndex(j);
        if (DancerJ->isGroup) continue;

        // Some comparison magic
        if ((DancerI->Number - DancerJ->Number) * (DancerI->Age - DancerJ->Age) < 0)
        {
          int NumberI = DancerI->Number;
          int NumberJ = DancerJ->Number;
          DancerI->Number = NumberJ;
          DancerJ->Number = NumberI;
          Database->SwapDancersByIndex(i, j); // For preserving order in table
          repeat = true; break;
        }
        if (repeat == true) break;
      }
    }
  }

  TableFromDatabase();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::AddNameEditChange(TObject *Sender)
{
  // Can be called only if not a team

  if(AddNameEdit->Text == "") return;
  TDancer *D = Database->GetDancerByPartialName(AddNameEdit->Text, false);
  if (D == NULL) return;
  if (D->isGroup) return;

  for (int Row = 1; Row < ListGrid->RowCount; ++Row)
  {
    if(GetUID(UIDList, Row) == D->UID)
    {
      ListGrid->Row = Row;

      TGridRect Rect;
      Rect.Left = 1;
      Rect.Top = Row;
      Rect.Right = 1;
      Rect.Bottom = Row;
      ListGrid->Selection = Rect;

      return;
    }
  }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::ResortFigureButtonClick(TObject *Sender)
{
  TableToDatabase();

  for(int i = 0; i < Database->TotalDancers(); ++i)
  {
    TDancer *DancerG = Database->GetDancerByIndex(i);
    if (!DancerG->isGroup) continue;

    int NumU12 = 0;
    int NumU17 = 0;
    int NumU30 = 0;
    int NumO30 = 0;
    int NumTotal = 0;
    int Numbers[16]; // Maximum Ceili group size is 16.

    // Determine what type of dance do we dance
    enum Dances Dance = nil;
    if (DancerG->Dances[Group2Hand]) { Dance = Group2Hand; }
    if (DancerG->Dances[Group3Hand]) { Dance = Group3Hand; }
    if (DancerG->Dances[Group4Hand]) { Dance = Group4Hand; }
    if (DancerG->Dances[GroupCeili]) { Dance = GroupCeili; }
    if (DancerG->Dances[Group4HandChamp]) { Dance = Group4HandChamp; }
    if (DancerG->Dances[GroupCeiliChamp]) { Dance = GroupCeiliChamp; }
    if (Dance == nil) // Will be catched at window close
    {
      AnsiString msg = "Команда Т" + (AnsiString)DancerG->Number + " не зарегистрирована на групповые танцы.";
      Application->MessageBox(msg.c_str(), "Ошибка базы данных", MB_OK);
      continue;
    }

    for (int j = 0; j < TeamStringLength(DancerG->Name); ++j)
    {
      AnsiString DancerIName = TeamStringGet(DancerG->Name, j);

      // Determine dancer ID
      bool found = false;
      TDancer *DancerI;
      for(int j = 0; j < Database->TotalDancers(); ++j)
      {
        DancerI = Database->GetDancerByIndex(j);
        if (DancerI->isGroup) continue;
        if ((DancerI->Name == DancerIName) && (DancerI->School == DancerG->School) && DancerI->Dances[Dance]) { found = true; break; }
      }
      if (!found)
      {
        AnsiString msg = "Команда Т" + (AnsiString)DancerG->Number + " содержит неизвестного участника " + DancerI->Name;
        Application->MessageBox(msg.c_str(), "Ошибка базы данных", MB_OK);
      }
      else
      {
        // Increment dancer numbers: total, and of correct age group.
        Numbers[NumTotal++]=DancerI->Number;

        if (QualificationCheckBox->Checked)
        {
          if (DancerI->Age < 11) ++NumU12;
          else if (DancerI->Age < 16) ++NumU17;
          else if (DancerI->Age < 29) ++NumU30;
          else ++NumO30;
        }
        else
        {
          if (DancerI->Age < 12) ++NumU12;
          else if (DancerI->Age < 17) ++NumU17;
          else if (DancerI->Age < 30) ++NumU30;
          else ++NumO30;
        }
      }
    }

    // Find out correct age group
    AnsiString AgeGroup = "AA";
    if (NumU12 * 2 >= NumTotal) AgeGroup = (QualificationCheckBox->Checked ? "U11" : "U12");
    else if ((NumU17 * 2 >= NumTotal) && (NumU12 * 4 <= NumTotal) && ((NumU30 + NumO30) * 4 <= NumTotal)) AgeGroup = (QualificationCheckBox->Checked ? "U16" : "U17");
    else if ((NumU30 * 2 >= NumTotal) && ((NumU12 + NumU17) * 4 <= NumTotal) && (NumO30 * 4 <= NumTotal)) AgeGroup = (QualificationCheckBox->Checked ? "U29" : "U30");
    else if (NumO30 * 2 >= NumTotal) AgeGroup = (QualificationCheckBox->Checked ? "O29" : "O30");
    else
    {
      AnsiString msg = "Команда Т" + (AnsiString)DancerG->Number + " содержит некорректный состав участников по возрастам: всего " + (AnsiString)NumTotal + ", из них " + (AnsiString)NumU12 + " участников U11/U12, " + (AnsiString)NumU17 + " участников U16/U17, " + (AnsiString)NumU30 + " участников U29/U30 и " + (AnsiString)NumO30 + " участников O29/O30.";
      Application->MessageBox(msg.c_str(), "Ошибка определения группы", MB_OK);
    }

    // Set age group for group dance and every individual one
    DancerG->AgeGroup[Dance] = AgeGroup;
    for (int j = 0; j < NumTotal; ++j)
    {
      TDancer *DancerI = Database->GetDancerByNumber(Numbers[j]);
      DancerI->AgeGroup[Dance] = AgeGroup;
    }
  }

  TableFromDatabase();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TImportForm::AddFromRawButtonClick(TObject *Sender)
{
  if(!CheckCurrentTable(false)) return;
  TableToDatabase();
  if (!Import(ltGroup)) return; /* reuse ltGroup for this purpose */
  ListChooseGroup->ItemIndex = ltSolo;
  SwitchToPage();
}
//---------------------------------------------------------------------------

