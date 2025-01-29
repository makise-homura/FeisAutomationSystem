//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>                                              
#pragma hdrstop
#include "Database.h"
//---------------------------------------------------------------------------
#define Signature 0x00FE1500 // Stylized 'Feis' word
//---------------------------------------------------------------------------
bool isGroupDance(enum Dances Dance)
{
  return (Dance == Group2Hand) || (Dance == Group3Hand) || (Dance == Group4Hand) || (Dance == GroupCeili);
}
//---------------------------------------------------------------------------
AnsiString DanceToStr(int Dance)
{
  switch((enum Dances)Dance)
  {
    case Jump23:               return "Jump 2 3";
    case ModernSet:            return "Modern Set";
    case TrebleReel:           return "Treble Reel";
    case BeginnerReel:         return "Beginner Reel";
    case BeginnerLightJig:     return "Beginner Light Jig";
    case BeginnerSingleJig:    return "Beginner Single Jig";
    case BeginnerSlipJig:      return "Beginner Slip Jig";
    case BeginnerTrebleJig:    return "Beginner Treble Jig";
    case BeginnerHornpipe:     return "Beginner Hornpipe";
    case BeginnerTradSet:      return "Beginner Traditional Set";
    case BeginnerPremiership:  return "Beginner Premiership";
    case PrimaryReel:          return "Primary Reel";
    case PrimaryLightJig:      return "Primary Light Jig";
    case PrimarySingleJig:     return "Primary Single Jig";
    case PrimarySlipJig:       return "Primary Slip Jig";
    case PrimaryTrebleJig:     return "Primary Treble Jig";
    case PrimaryHornpipe:      return "Primary Hornpipe";
    case PrimaryTradSet:       return "Primary Traditional Set";
    case PrimaryPremiership:   return "Primary Premiership";
    case IntermedReel:         return "Intermediate Reel";
    case IntermedLightJig:     return "Intermediate Light Jig";
    case IntermedSingleJig:    return "Intermediate Single Jig";
    case IntermedSlipJig:      return "Intermediate Slip Jig";
    case IntermedTrebleJig:    return "Intermediate Treble Jig";
    case IntermedHornpipe:     return "Intermediate Hornpipe";
    case IntermedTradSet:      return "Intermediate Traditional Set";
    case IntermedPremiership:  return "Intermediate Premiership";
    case OpenReel:             return "Open Reel";
    case OpenSlipJig:          return "Open Slip Jig";
    case OpenTrebleJig:        return "Open Treble Jig";
    case OpenHornpipe:         return "Open Hornpipe";
    case OpenTradSet:          return "Open Traditional Set";
    case PreChampionship:      return "Preliminary Championship";
    case Championship:         return "Open Championship";
    case Group2Hand:           return "2-Hand";
    case Group3Hand:           return "3-Hand";
    case Group4Hand:           return "4-Hand";
    case GroupCeili:           return "Ceili";
    default:                   return "Неизвестный танец";
  }
}
//---------------------------------------------------------------------------
AnsiString PointsToStr(int Points)
{
  if (Points == -1) return "";
  AnsiString String = Points / 100;
  if (Points % 100)
  {
    String += ".";
    if (Points % 10) String += Points % 100;
    else String += Points % 100 / 10;
  }
  return String;

}
//---------------------------------------------------------------------------
int PointsToInt(AnsiString String)
{
  String.Trim();

  int DecimalPointPos = String.Pos(".");
  if (DecimalPointPos == 0) DecimalPointPos = String.Pos(",");
  if (DecimalPointPos == 0)
  {
    int Number = String.ToIntDef(-1);
    if (Number >= 0) return Number * 100;
  }

  int Exp10 = String.Length() - DecimalPointPos;
  String.Delete(DecimalPointPos,1);

  if(String.Pos(".") != 0) return -1;
  if(String.Pos(",") != 0) return -1;

  int Number = String.ToIntDef(-1);
  if (Number < 0) return -1;

  if (Exp10 == 1) return Number * 10;
  if (Exp10 == 2) return Number;
  return -1;
}
//---------------------------------------------------------------------------
int GetGroupAge(AnsiString s)
{
  AnsiString n = s.SubString(2, s.Length() - 1);
  return n.ToIntDef(0);
}
//---------------------------------------------------------------------------
char GetGroupType(AnsiString s)
{
  if (s == "") return '\0';
  return s[1];
}
//---------------------------------------------------------------------------
AnsiString GroupToString(AnsiString s) // returns "" on failure
{
  if (s == "AA") return "All Ages";

  AnsiString Result = "";

  int Age = GetGroupAge(s);
  if (Age < 1) return "";

  switch(GetGroupType(s))
  {
    case 'U':
      Result = "Under ";
      Result += Age;
      break;
    case 'O':
      Result = "Over ";
      Result += Age;
      break;
  }
  return Result;
}
//---------------------------------------------------------------------------
AnsiString TeamStringGet(AnsiString TeamString, int index)
{
  AnsiString Probe;
  TeamString = TeamString.Trim();

  for(int j = 0; j < index + 1; ++j)
  {
    if (TeamString == "")
    {
      return "";
    }
    else if (TeamString.Pos("/") > 0)
    {
      Probe = TeamString.SubString(1, TeamString.Pos("/") - 1);
      TeamString.Delete(1, TeamString.Pos("/"));
    }
    else
    {
      Probe = TeamString;
      TeamString = "";
    }
  }

  return Probe.Trim();
}
//---------------------------------------------------------------------------
AnsiString TeamStringAdd(AnsiString TeamString, AnsiString Content)
{
  if (TeamString == "") return Content.Trim();
  return (TeamString + " / " + Content).Trim();
}
//---------------------------------------------------------------------------
int TeamStringLength(AnsiString TeamString)
{
  if (TeamString == "") return 0;
  int i = 1;
  for(int j = 1; j <= TeamString.Length(); ++j) if (TeamString[j] == '/') ++i;
  return i;
}
//---------------------------------------------------------------------------
AnsiString TeamStringDelete(AnsiString TeamString, AnsiString Content)
{
  AnsiString NewTeamString, Probe;
  Content = Content.Trim();

  for(int j = 0; j < TeamStringLength(TeamString); ++j)
  {
    Probe = TeamStringGet(TeamString, j);
    if (Probe != Content) NewTeamString = TeamStringAdd(NewTeamString, Probe);
  }
  return NewTeamString;
}
//---------------------------------------------------------------------------
TFeisDatabase::TFile::TFile(AnsiString FileName, AnsiString mode)
{
  Error = false;
  Handle = fopen(FileName.c_str(), mode.c_str());
  if (Handle == NULL) Error = true;
}
//---------------------------------------------------------------------------
TFeisDatabase::TFile::~TFile()
{
   fclose(Handle);
}
//---------------------------------------------------------------------------
bool TFeisDatabase::TFile::ReadBool()
{
  __int32 BinObj;
  int size = fread(&BinObj, sizeof(__int32), 1, Handle);
  if (size != 1) Error = true;
  else if (BinObj == 0) return false;
  else if (BinObj == 1) return true;
  else Error = true;
  return false;
}
//---------------------------------------------------------------------------
int TFeisDatabase::TFile::ReadInteger(int Min, int Max)
{
  __int32 BinObj;
  int size = fread(&BinObj, sizeof(__int32), 1, Handle);
  if (size != 1) Error = true;
  else if ((BinObj >= Min) && (BinObj <= Max)) return BinObj;
  else Error = true;
  return 0;
}
//---------------------------------------------------------------------------
AnsiString TFeisDatabase::TFile::ReadAnsiString()
{
  __int32 SizeObj; AnsiString Return;
  int size = fread(&SizeObj, sizeof(__int32), 1, Handle);
  if (size != 1) Error = true;
  else
  {
    if (SizeObj == 0) return "";
    char *BinObj = (char*) malloc(SizeObj + 1);
    BinObj[SizeObj] = 0;
    int size = fread(BinObj, SizeObj, 1, Handle);
    if (size != 1) Error = true;
    else Return = BinObj;
    free(BinObj);
  }
  return Return;
}
//---------------------------------------------------------------------------
void TFeisDatabase::TFile::WriteBool(bool Data)
{
  __int32 BinObj = (Data ? 1 : 0);
  int size = fwrite(&BinObj, sizeof(__int32), 1, Handle);
  if (size != 1) Error = true;
}
//---------------------------------------------------------------------------
void TFeisDatabase::TFile::WriteInteger(int Data)
{
  __int32 BinObj = Data;
  int size = fwrite(&BinObj, sizeof(__int32), 1, Handle);
  if (size != 1) Error = true;
}
//---------------------------------------------------------------------------
void TFeisDatabase::TFile::WriteAnsiString(AnsiString Data)
{
  char* BinObj = Data.c_str();
  __int32 SizeObj = strlen(BinObj);

  int size = fwrite(&SizeObj, sizeof(__int32), 1, Handle);
  if (size != 1) Error = true;

  if (SizeObj == 0) return;

  size = fwrite(BinObj, SizeObj, 1, Handle);
  if (size != 1) Error = true;
}
//---------------------------------------------------------------------------
TDancer::TDancer()
{
    isGroup  = false;
    Number   = 0;
    Name     = "";
    School   = "";
    Age      = 0;

    for (int i = 0; i < TotalDances; ++i)
    {
      Dances[i]    = false;
      for (int k = 0; k < TotalRounds; ++k) RawPoints[i][k] = -1;
      CalcPoints[i]= -1;
      Places[i]    = 0;
      Qualified[i] = false;
      AgeGroup[i]  = "";
    }
}
//---------------------------------------------------------------------------
TFeisDatabase::TFeisDatabase()
{
  Dancers = new TList;
}
//---------------------------------------------------------------------------
bool TFeisDatabase::LoadFromFile(AnsiString FileName)
{
  for (int i = 0; i < Dancers->Count; ++i) delete Dancers->Items[i];
  Dancers->Clear();

  // Load database from file
  TFile *DbFile = new TFile(FileName, "rb");
  int i, j, Count;
  if (!DbFile->Error)
  {
    DbFile->ReadInteger(Signature, Signature);
    Count = DbFile->ReadInteger(0, 10000);
    if (!DbFile->Error)
    {
      for(i = 0; i < Count; ++i)
      {
        TDancer *Dancer = new TDancer;

        Dancer->UID     = DbFile->ReadInteger(0, 32767);
        Dancer->isGroup = DbFile->ReadBool();
        Dancer->Number  = DbFile->ReadInteger(1, 10000);
        Dancer->Name    = DbFile->ReadAnsiString();
        Dancer->School  = DbFile->ReadAnsiString();
        Dancer->Age     = DbFile->ReadInteger(0, 100); // Age can be 0 for newly-added participants

        for (j = 0; j < TotalDances; ++j)
        {
          Dancer->Dances[j]         = DbFile->ReadBool();
          for (int k = 0; k < TotalRounds; ++k)
            Dancer->RawPoints[j][k] = DbFile->ReadInteger(-1, 200000); // Max 2000 points (really reachable is 1200)
          Dancer->CalcPoints[j]     = DbFile->ReadInteger(-1, 200000);
          Dancer->Places[j]         = DbFile->ReadInteger(0, 40);
          Dancer->Qualified[j]      = DbFile->ReadBool();
          Dancer->AgeGroup[j]       = DbFile->ReadAnsiString();
          Dancer->Comment[j]        = DbFile->ReadAnsiString();
        }

        Dancers->Add(Dancer);
      }
    }
  }
  bool err = DbFile->Error; // Somehow we get error on EOF, why?
  delete DbFile;
  if (err) Dancers->Clear();
  return !err;
}
//---------------------------------------------------------------------------
bool TFeisDatabase::CreateFile(AnsiString FileName)
{
  for (int i = 0; i < Dancers->Count; ++i) delete Dancers->Items[i];
  Dancers->Clear();
  return SaveToFile(FileName);
}
//---------------------------------------------------------------------------
void TFeisDatabase::RemoveAll(bool isGroup)
{
  for(int i = Dancers->Count - 1; i >= 0; --i)
  {
    TDancer *Dancer = (TDancer*) Dancers->Items[i];
    if (Dancer->isGroup != isGroup) continue;
    delete Dancer;
    Dancers->Delete(i);
  }
}

//---------------------------------------------------------------------------
bool TFeisDatabase::SaveToFile(AnsiString FileName)
{
  TFile *DbFile = new TFile(FileName, "wb");
  if (!DbFile->Error)
  {
    DbFile->WriteInteger(Signature);
    DbFile->WriteInteger(Dancers->Count);
    for(int i = 0; i < Dancers->Count; ++i)
    {
      TDancer *Dancer = (TDancer*) Dancers->Items[i];

      DbFile->WriteInteger   (Dancer->UID);
      DbFile->WriteBool      (Dancer->isGroup);
      DbFile->WriteInteger   (Dancer->Number);
      DbFile->WriteAnsiString(Dancer->Name);
      DbFile->WriteAnsiString(Dancer->School);
      DbFile->WriteInteger   (Dancer->Age);

      for (int j = 0; j < TotalDances; ++j)
      {
        DbFile->WriteBool(Dancer->Dances[j]);
        for (int k = 0; k < TotalRounds; ++k)
          DbFile->WriteInteger(Dancer->RawPoints[j][k]);
        DbFile->WriteInteger(Dancer->CalcPoints[j]);
        DbFile->WriteInteger(Dancer->Places[j]);
        DbFile->WriteBool(Dancer->Qualified[j]);
        DbFile->WriteAnsiString(Dancer->AgeGroup[j]);
        DbFile->WriteAnsiString(Dancer->Comment[j]);
      }
    }
  }
  bool err = DbFile->Error;
  delete DbFile;
  return !err;
}
//---------------------------------------------------------------------------
TFeisDatabase::~TFeisDatabase()
{
  for(int i = 0; i < Dancers->Count; ++i) delete (TDancer*) Dancers->Items[i];
  delete Dancers;
}
//---------------------------------------------------------------------------
TDancer* TFeisDatabase::GetDancerByIndex(int index)
{
  return (TDancer*) Dancers->Items[index];
}
//---------------------------------------------------------------------------
void TFeisDatabase::SwapDancersByIndex(int index1, int index2)
{
  TDancer *Dancer1 = (TDancer*) Dancers->Items[index1];
  TDancer *Dancer2 = (TDancer*) Dancers->Items[index2];
  Dancers->Items[index1] = Dancer2;
  Dancers->Items[index2] = Dancer1;
}
//---------------------------------------------------------------------------
TDancer* TFeisDatabase::GetDancerByNumber(AnsiString Number)
{
  for (int i = 0; i < Dancers->Count; ++i)
  {
    TDancer *Dancer = (TDancer*) Dancers->Items[i];
    AnsiString S = (Dancer->isGroup ? "T" : "");
    S += Dancer->Number;
    if (S == Number) return (TDancer*) Dancers->Items[i];
  }
  return NULL;
}
//---------------------------------------------------------------------------
TDancer* TFeisDatabase::GetDancerByPartialName(AnsiString PartialName, bool FromStart)
{
  for (int i = 0; i < Dancers->Count; ++i)
  {
    TDancer *Dancer = (TDancer*) Dancers->Items[i];
    if (Dancer->isGroup) continue;

    int Pos = Dancer->Name.UpperCase().Pos(PartialName.UpperCase());
    if (Pos == 0) continue;
    if (FromStart && Pos != 1) continue;
    return (TDancer*) Dancers->Items[i];
  }
  return NULL;
}
//---------------------------------------------------------------------------
int TFeisDatabase::NewUID()
{
  int UID;
  for(UID = 0; ; ++UID)
  {
    bool found = false;
    for(int i = 0; i < Dancers->Count; ++i)
    {
      if (UID == ((TDancer*)Dancers->Items[i])->UID) { found = true; break; }
    }
    if (!found) break;
  }
  return UID;
}
//---------------------------------------------------------------------------
TDancer* TFeisDatabase::AddNewDancer()
{
  TDancer *Dancer = new TDancer;
  Dancer->UID = NewUID();
  Dancers->Add(Dancer);
  return Dancer;
}
//---------------------------------------------------------------------------
bool TFeisDatabase::DeleteByUID(int UID)
{
  for(int i = 0; i < Dancers->Count; ++i)
  {
    TDancer *Dancer = (TDancer*) Dancers->Items[i];
    if (Dancer->UID == UID)
    {
      delete Dancer;
      Dancers->Delete(i);
      return true;
    }
  }
  return false;
}
//---------------------------------------------------------------------------
int TFeisDatabase::TotalDancers()
{
  return Dancers->Count;
}
//---------------------------------------------------------------------------
void TFeisDatabase::GroupsFromDatabase(AnsiString Array[TotalDances][TotalGroups])
{
  int DBEntry, Dance, Group;

  // We should clear all group definitions
  for (Group = 0; Group < TotalGroups; ++Group)
    for (Dance = 0; Dance < TotalDances; ++Dance)
      Array[Dance][Group] = "";

  // Fill groups from base
  for(DBEntry = 0; DBEntry < Dancers->Count; ++DBEntry)
  {
    TDancer *Dancer = (TDancer*) Dancers->Items[DBEntry];

    for (Dance = 0; Dance < TotalDances; ++Dance)
    {
      if(Dancer->Dances[Dance])
      {
        // Empty dancer age group means "it has been just added, so determine it later", so we skip him
        if (Dancer->AgeGroup[Dance] == "") continue;

        // If no dancer's age group exist in this dance, add it to list for that dance
        bool exist = false;
        for (Group = 0; Group < TotalGroups; ++Group)
        {
          if (Dancer->AgeGroup[Dance] == Array[Dance][Group]) { exist = true; break; }
        }
        if (!exist)
        {
          // We assume that database is consistent (it may be checked using group dialog)
          if (Dancer->AgeGroup[Dance] == "AA") Array[Dance][0] = "AA";
          else if (GetGroupType(Dancer->AgeGroup[Dance]) == 'O')
          {
            for (Group = 0; Group < TotalGroups; ++Group)
              if (Array[Dance][Group] == "")
              {
                Array[Dance][Group] = Dancer->AgeGroup[Dance]; break;
              }
          }
          else
          {
            for (Group = 0; Group < TotalGroups; ++Group)
            {
              if (Array[Dance][Group] == "") break;
              if (GetGroupAge(Array[Dance][Group]) >= GetGroupAge(Dancer->AgeGroup[Dance])) break;
            }
            if (Group < TotalGroups)
            {
              for (int ShiftGroup = TotalGroups - 2; ShiftGroup >= Group; --ShiftGroup)
                Array[Dance][ShiftGroup + 1] = Array[Dance][ShiftGroup];
              Array[Dance][Group] = Dancer->AgeGroup[Dance];
            }
            else
            {
              AnsiString msg = "База возрастных групп повреждена. Используйте окно разбивки на группы для исправления ошибки.";
              Application->MessageBox(msg.c_str(),"Ошибка базы данных",MB_OK);
            }
          }
        }
      }
    }
  }

  // Set "AA" for all dances without group definitions
  for (Dance = 0; Dance < TotalDances; ++Dance)
      if (Array[Dance][0] == "") Array[Dance][0] = "AA";
}
//---------------------------------------------------------------------------
// TODO mandatory check if no solo dances
bool TFeisDatabase::ConsistencyCheck(TStrings *ErrorMessages)
{
  // Stage 1: Check UIDs uniquity
  for (int i = 0; i < Dancers->Count; ++i)
    for (int j = 0; j < i; ++j)
    {
      TDancer *I = GetDancerByIndex(i), *J = GetDancerByIndex(j);
      if (I->UID == J->UID)
        ErrorMessages->Add((AnsiString)"Фатальное повреждение базы данных: одинаковый UID у танцоров " + I->Number + " " + J->Number + " - исправить невозможно! Работа с данным файлом феша может повлечь непредсказуемые ошибки.");
    }

  // Stage 2: Check number uniquity (distinct for group and solo dancers) and correctness of numbers
  for (int i = 0; i < Dancers->Count; ++i)
  {
    TDancer *I = GetDancerByIndex(i);
    if (I->Number < 1)
      ErrorMessages->Add((AnsiString)"Ошибка: неверный номер " + (I->isGroup ? " у танцора " : " у команды ") + I->Name + " - исправьте в окне импорта и редактирования.");

    for (int j = 0; j < i; ++j)
    {
      TDancer *J = GetDancerByIndex(j);
      if ((I->Number == J->Number) && (I->isGroup == J->isGroup))
        ErrorMessages->Add((AnsiString)"Ошибка: одинаковый номер " + I->Number + "  у танцоров " + I->Name + " " + J->Name + " - исправьте в окне импорта и редактирования.");
    }
  }

  // Stage 3: Check that solo dancers are registered for at least one dance
  for (int i = 0; i < Dancers->Count; ++i)
  {
    TDancer *I = GetDancerByIndex(i);
    if (I->isGroup) continue;

    bool detectedsolo = false;
    int detectedgroup = 0;
    for (int j = 0; j < TotalDances; ++j)
    {
      if (I->Dances[j])
      {
        if (j < Group2Hand) detectedsolo = true; else ++detectedgroup;
      }
    }

    /* This check is not valid according to current WIDA rules.
    if(detectedgroup > 1)
      ErrorMessages->Add((AnsiString)"Ошибка: танцор " + I->Number + " (" + I->Name + ") зарегистрирован более, чем на один групповой танец - исправьте в окне импорта и редактирования.");
    */

    if(!detectedsolo && (detectedgroup == 0))
      ErrorMessages->Add((AnsiString)"Ошибка: танцор " + I->Number + " (" + I->Name + ") не имеет регистрации ни на один танец (ни сольный, ни групповой) - исправьте в окне импорта и редактирования.");
  }

  // Stage 4: Check that teams are registered for one group dance and not registered to solo dances; also check number of dancers for teams
  for (int i = 0; i < Dancers->Count; ++i)
  {
    TDancer *I = GetDancerByIndex(i);
    if (!I->isGroup) continue;

    bool detectedsolo = false;
    int detectedgroup = 0;
    for (int j = 0; j < TotalDances; ++j)
    {
      if (I->Dances[j])
        if (j < Group2Hand) detectedsolo = true;
        else
        {
          ++detectedgroup;
          bool checkfailed = false;
          if         (j == Group2Hand)    checkfailed = (TeamStringLength(I->Name) != 2);
          else    if (j == Group3Hand)    checkfailed = (TeamStringLength(I->Name) != 3);
          else    if (j == Group4Hand)    checkfailed = (TeamStringLength(I->Name) != 4);
          else /* if (j == GroupCeili) */ checkfailed = (TeamStringLength(I->Name) != 6) && (TeamStringLength(I->Name) != 8);

          if (checkfailed)
            ErrorMessages->Add((AnsiString)"Ошибка: команда T" + I->Number + " (" + I->Name + ") имеет неверное количество участников - исправьте в окне импорта и редактирования.");
        }
    }
    if(detectedgroup > 1)
      ErrorMessages->Add((AnsiString)"Ошибка: команда T" + I->Number + " (" + I->Name + ") зарегистрирована более, чем на один танец - исправьте в окне импорта и редактирования.");
    else if (detectedgroup == 0)
      ErrorMessages->Add((AnsiString)"Ошибка: команда T" + I->Number + " (" + I->Name + ") не зарегистрирована ни на один танец - исправьте в окне импорта и редактирования.");
    if(detectedsolo)
      ErrorMessages->Add((AnsiString)"Предупреждение: команда T" + I->Number + " (" + I->Name + ") зарегистрирована на сольные танцы - это не имеет смысла и будет проигнорировано.");
  }

  // Stage 5: Check if every dancer in each team are exist in base and has been registered for this dance, and also has the same age group for it
  for (int i = 0; i < Dancers->Count; ++i)
  {
    TDancer *I = GetDancerByIndex(i);
    if (!I->isGroup) continue;

    for(int i = 0; i < TeamStringLength(I->Name); ++i)
    {
      AnsiString DancerName = TeamStringGet(I->Name, i);
      bool detected = false;
      for(int j = 0; j < Dancers->Count; ++j)
      {
        TDancer *J = GetDancerByIndex(j);
        if (J->isGroup) continue;
        if((J->Name == DancerName) && (J->School == I->School))
        {
          detected = true;
          if
          (
            (I->Dances[Group2Hand] && !J->Dances[Group2Hand]) ||
            (I->Dances[Group3Hand] && !J->Dances[Group3Hand]) ||
            (I->Dances[Group4Hand] && !J->Dances[Group4Hand]) ||
            (I->Dances[GroupCeili] && !J->Dances[GroupCeili])
          )
          {
            if (I->Dances[Group2Hand]) J->Dances[Group2Hand] = true;
            if (I->Dances[Group3Hand]) J->Dances[Group3Hand] = true;
            if (I->Dances[Group4Hand]) J->Dances[Group4Hand] = true;
            if (I->Dances[GroupCeili]) J->Dances[GroupCeili] = true;
            ErrorMessages->Add((AnsiString)"Предупреждение: танцор " + DancerName + " из команды T" + I->Number + " (" + I->Name + ") не был зарегистрирован на танец этой команды - исправлено автоматически.");
          }

          bool fixedgroup = false;
          if (I->Dances[Group2Hand] && (I->AgeGroup[Group2Hand] != J->AgeGroup[Group2Hand])) { J->AgeGroup[Group2Hand] = I->AgeGroup[Group2Hand]; fixedgroup = true; }
          if (I->Dances[Group3Hand] && (I->AgeGroup[Group3Hand] != J->AgeGroup[Group3Hand])) { J->AgeGroup[Group3Hand] = I->AgeGroup[Group3Hand]; fixedgroup = true; }
          if (I->Dances[Group4Hand] && (I->AgeGroup[Group4Hand] != J->AgeGroup[Group4Hand])) { J->AgeGroup[Group4Hand] = I->AgeGroup[Group4Hand]; fixedgroup = true; }
          if (I->Dances[GroupCeili] && (I->AgeGroup[GroupCeili] != J->AgeGroup[GroupCeili])) { J->AgeGroup[GroupCeili] = I->AgeGroup[GroupCeili]; fixedgroup = true; }
          if (fixedgroup)
          {
            ErrorMessages->Add((AnsiString)"Предупреждение: танцор " + DancerName + " из команды T" + I->Number + " имел возрастную группу, отличную от группы своей команды - исправлено автоматически.");
          }
          break;
        }
      }
      if(!detected)
      {
        ErrorMessages->Add((AnsiString)"Ошибка: команда T" + I->Number + " (" + I->Name + ") имеет в своем составе танцора " + DancerName + ", отсутствующего в списках школы, от которой заявлена команда - исправьте в окне импорта и редактирования.");
      }
    }
  }

  // Stage 6: Check if any dancer has either empty or incorrectly spelled age group for registered dance, or unempty age group for dance for which he is not registered, or unfitting age and group
  for (int i = 0; i < Dancers->Count; ++i)
  {
    TDancer *I = GetDancerByIndex(i);
    bool detectedless = false, detectedmore = false, detectedunmatched = false;
    AnsiString s_detectedless, s_detectedmore, s_detectedunmatched;
    for (int j = 0; j < TotalDances; ++j)
    {
      if (I->Dances[j])
      {
        if (I->AgeGroup[j] != "AA")
        {
          if ( ((GetGroupType(I->AgeGroup[j]) != 'O') && (GetGroupType(I->AgeGroup[j]) != 'U' )) || (GetGroupAge(I->AgeGroup[j]) == 0))
          {
            s_detectedless = DanceToStr(j);
            detectedless = true;
          }
          if (I->AgeGroup[j] != "" && /*!I->isGroup*/ !isGroupDance((enum Dances)j))
          {
            if ((GetGroupType(I->AgeGroup[j]) == 'O') && (I->Age <  GetGroupAge(I->AgeGroup[j])))
            {
              s_detectedunmatched = DanceToStr(j);
              detectedunmatched = true;
            }
            if ((GetGroupType(I->AgeGroup[j]) == 'U') && (I->Age >= GetGroupAge(I->AgeGroup[j])))
            {
              s_detectedunmatched = DanceToStr(j);
              detectedunmatched = true;
            }
          }
        }
      }
      else if (I->AgeGroup[j] != "")
      {
        s_detectedmore = DanceToStr(j);
        detectedmore = true;
        I->AgeGroup[j] = "";
      }
    }

    if(detectedless)
    {
      if(I->isGroup)
        ErrorMessages->Add((AnsiString)"Ошибка: команда T" + I->Number + " (" + I->Name + ") имеет неверно написанную или пустую возрастную группу в танце " + s_detectedless + " - исправьте в окне импорта и редактирования.");
      else
        ErrorMessages->Add((AnsiString)"Ошибка: участник " + I->Number + " (" + I->Name + ") имеет неверно написанную или пустую возрастную группу в одном или более из своих танцев (например, " + s_detectedless + ") - исправьте в окне разбивки на группы.");
    }

    if(detectedmore)
    {
      AnsiString what = I->isGroup? "команда T" : "танцор ";
      ErrorMessages->Add((AnsiString)"Информация: " + what + I->Number + " (" + I->Name + ") имел возрастную группу для одного или нескольких танцев, на который не имел регистрации (например, " + s_detectedmore + ") - это было исправлено.");
    }

    if(detectedunmatched) // Only non-group dances checked
    {
      ErrorMessages->Add((AnsiString)"Предупреждение: танцор " + I->Number + " (" + I->Name + ") имеет возрастную группу, не удовлетворяющую его возрасту (" + I->Age + ") для одного или более из своих танцев (например, " + s_detectedunmatched + ").");
    }
  }

  // TODO: Check if any solo dancer has unmatching age group for registered dance, i.e. dancer's group does not match any of dance's groups

  return (ErrorMessages->Count == 0);
}
//---------------------------------------------------------------------------

