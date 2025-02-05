//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Excel.h"
#include "Database.h"
#include "DictDances.h"
#include "ImportUnit.h"
#include "NumbersUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TNumbersForm *NumbersForm;
extern TFeisDatabase *Database;
//---------------------------------------------------------------------------
__fastcall TNumbersForm::TNumbersForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
AnsiString AlteredSchool(AnsiString School)
{
  if (School.SubString(1, 10) == "(Non-WIDA)") return "Not associated to any school";
  return School;
}
//---------------------------------------------------------------------------
bool ExportParticipants(AnsiString FileName, TPanel *Warning)
{
  Warning->Show();
  Warning->Caption = "Сохраняется список участников...";
  Application->ProcessMessages();
  TStringList *Data = new TStringList;

  // Determine number of solo dances
  int MaxSolo = 0, MaxGroup = 0;
  for (int i = 0; i < Database->TotalDancers(); ++i)
  {
    TDancer *Dancer = Database->GetDancerByIndex(i);
    if (Dancer->isGroup)  { if (Dancer->Number > MaxGroup) MaxGroup = Dancer->Number; }
    if (!Dancer->isGroup) { if (Dancer->Number > MaxSolo)  MaxSolo  = Dancer->Number; }
  }

  // Add solo dancers information
  for (int i = 1; i <= MaxSolo; ++i)
  {
    TDancer *Dancer = Database->GetDancerByNumber(i);
    if (Dancer == NULL) continue;

    AnsiString Age = "";
    if (!Dancer->isGroup) Age = (AnsiString)"\t" + Dancer->Age;
    AnsiString Line = (AnsiString)Dancer->Number + "\t" + Dancer->Name + "\t" + AlteredSchool(Dancer->School) + Age;
    Data->Append(Line);
  }

  // Add empty line
  Data->Append("");

  // Add team information
  for (int i = 1; i <= MaxGroup; ++i)
  {
    TDancer *Dancer = Database->GetDancerByNumber((AnsiString)"T" + i);
    if (Dancer == NULL) continue;

    AnsiString Line = (AnsiString)"T" + Dancer->Number + "\t" + Dancer->Name + "\t" + AlteredSchool(Dancer->School);
    Data->Append(Line);
  }

  // Save file and finalize
  Warning->Hide();
  try { Data->SaveToFile(FileName); }
  catch(...)
  {
    delete Data;
    Application->MessageBox("Невозможно создать выбранный файл", "Ошибка создания файла", MB_OK);
    return false;
  }
  delete Data;
  return true;
}
//---------------------------------------------------------------------------
int __fastcall CustomSortWrapper(TStringList* List, int Index1, int Index2)
{
  // Equivalent strings
  if  (List->Strings[Index1] == List->Strings[Index2]) return 0;

  // AA goes after any of the groups
  if ((List->Strings[Index2] == "AA")) return -1;
  if ((List->Strings[Index1] == "AA")) return +1;

  // Over XX goes after any of the Under XX
  if ((List->Strings[Index1].SubString(1, 1) == "U") && (List->Strings[Index2].SubString(1, 1) == "O")) return -1;
  if ((List->Strings[Index1].SubString(1, 1) == "O") && (List->Strings[Index2].SubString(1, 1) == "U")) return +1;

  // Otherwise compare strings as numbers
  int Num1 = List->Strings[Index1].SubString(2, List->Strings[Index1].Length() - 1).ToIntDef(0);
  int Num2 = List->Strings[Index2].SubString(2, List->Strings[Index2].Length() - 1).ToIntDef(0);
  return Num1 - Num2;
}
//---------------------------------------------------------------------------
void FormSchedule(int *Row, TExcel *Excel, TPanel *Warning, AnsiString Class, TColor Color, int num,
                  enum Dances Dance1, enum Dances Dance2, enum Dances Dance3, enum Dances Dance4,
                  AnsiString  Name1,  AnsiString  Name2,  AnsiString  Name3,  AnsiString  Name4)
{
  enum Dances Dances[4] = {Dance1, Dance2, Dance3, Dance4};
  AnsiString Names[4]  = {Name1,  Name2,  Name3,  Name4};
  AnsiString Groups[TotalDances][TotalGroups];
  Database->GroupsFromDatabase(Groups);
  Warning->Caption = "Оформление строки " + Class + "...";
  Application->ProcessMessages();

  // Find any groups in every dance of the specified
  TStringList *GroupList = new TStringList;
  for (int i = 0; i < num; ++i)
    for (int j = 0; j < TotalGroups; ++j)
      if (Groups[Dances[i]][j] != "")
        if (GroupList->IndexOf(Groups[Dances[i]][j]) == -1)
          GroupList->Add(Groups[Dances[i]][j]);

  // Sort group list
  GroupList->CustomSort(CustomSortWrapper);

  // Put group data
  for(int SubRow = 0; SubRow < GroupList->Count; ++SubRow)
  {
    // Determine which dances has this group
    bool p[4] = {false, false, false, false};
    for (int i = 0; i < num; ++i)
      for (int j = 0; j < TotalGroups; ++j)
        if (Groups[Dances[i]][j] == GroupList->Strings[SubRow]) { p[i] = true; break; }

    // See if all of the dances has this group
    bool all = true;
    for (int i = 0; i < num; ++i) if (!p[i]) { all = false; break; }

    // Put group data
    AnsiString Text = GroupToString(GroupList->Strings[SubRow]);
    if (!all)
    {
      Text += " (";
      bool ampersand = false;
      for (int i = 0; i < num; ++i)
      {
        if (p[i])
        {
          if (ampersand) Text += "&";
          Text += Names[i];
          ampersand = true;
        }
      }
      Text += ")";
    }
    Excel->PutCell(*Row + SubRow, 2, Text);
  }

  // Set appearance of line
  if (GroupList->Count > 0)
  {
    Excel->SelectRange(1, *Row, 1, GroupList->Count);
    Excel->Join();
    Excel->SetValue(Class);
    Excel->SetFontBold();
    Excel->SelectRange(0, *Row, 5, GroupList->Count);
    Excel->SetAlignment(xlCenter, xlCenter);
    Excel->SetFontFace("Arial Narrow");
    Excel->SetFontSize(11);
    Excel->SetBorder(xlEdgeTop,        xlContinuous, xlMedium);
    Excel->SetBorder(xlEdgeBottom,     xlContinuous, xlMedium);
    Excel->SetBorder(xlEdgeLeft,       xlContinuous, xlMedium);
    Excel->SetBorder(xlEdgeRight,      xlContinuous, xlMedium);
    Excel->SetBorder(xlInsideVertical, xlContinuous, xlThin);
    if (GroupList->Count > 1)
      Excel->SetBorder(xlInsideHorizontal, xlContinuous, xlThin);
    Excel->SetBkColor(Color);
    *Row += GroupList->Count;
  }
  else
  {
    Excel->PutCell(*Row, 1, Class);
    Excel->SetBorder(xlEdgeLeft,   xlContinuous, xlThin);
    Excel->SetBorder(xlEdgeRight,  xlContinuous, xlThin);
    Excel->SetFontBold();
    Excel->SelectRange(0, *Row, 5, 1);
    Excel->SetAlignment(xlCenter, xlCenter);
    Excel->SetFontFace("Arial Narrow");
    Excel->SetFontSize(11);
    Excel->SetBorder(xlEdgeTop,    xlContinuous, xlMedium);
    Excel->SetBorder(xlEdgeBottom, xlContinuous, xlMedium);
    Excel->SetBorder(xlEdgeLeft,   xlContinuous, xlMedium);
    Excel->SetBorder(xlEdgeRight,  xlContinuous, xlMedium);
    Excel->SetBkColor(Color);
    *Row += 1;
  }
  delete GroupList;
}
//---------------------------------------------------------------------------
bool ExportSchedule(AnsiString FileName, TPanel *Warning)
{
  Warning->Show();
  Warning->Caption = "Создается Excel-файл...";
  Application->ProcessMessages();

  TExcel *OutputExcel;
  try { OutputExcel = new TExcel(FileName, xlCreate); }
  catch(...)
  {
    Application->MessageBox("Невозможно создать выбранный файл", "Ошибка создания файла", MB_OK);
    Warning->Hide();
    return false;
  }

  // Make header
  OutputExcel->SelectRange(0, 1, 5, 1);
  OutputExcel->SetBorder(xlEdgeLeft,       xlContinuous, xlMedium);
  OutputExcel->SetBorder(xlEdgeRight,      xlContinuous, xlMedium);
  OutputExcel->SetBorder(xlInsideVertical, xlContinuous, xlThin);
  OutputExcel->SelectRange(0, 0, 5, 1);
  OutputExcel->SetBorder(xlEdgeTop,        xlContinuous, xlMedium);
  OutputExcel->SetBorder(xlEdgeBottom,     xlContinuous, xlMedium);
  OutputExcel->SetBorder(xlEdgeLeft,       xlContinuous, xlMedium);
  OutputExcel->SetBorder(xlEdgeRight,      xlContinuous, xlMedium);
  OutputExcel->SetBorder(xlInsideVertical, xlContinuous, xlThin);
  OutputExcel->SetAlignment(xlCenter, xlCenter);
  OutputExcel->SetFontFace("Arial Narrow");
  OutputExcel->SetFontSize(11);
  OutputExcel->SetFontBold();
  OutputExcel->PutCell(0, 0, "Time");
  OutputExcel->PutCell(0, 1, "Category");
  OutputExcel->PutCell(0, 2, "Stage A");
  OutputExcel->PutCell(0, 3, "Stage B");
  OutputExcel->PutCell(0, 4, "Stage C");
  OutputExcel->SetColWidth(0, 7);
  OutputExcel->SetColWidth(1, 17);
  OutputExcel->SetColWidth(2, 30);
  OutputExcel->SetColWidth(3, 30);
  OutputExcel->SetColWidth(4, 30);


  // Make a schedule
  int Row = 2;
  FormSchedule(&Row, OutputExcel, Warning, "Jump 2 3",             clPaleBlue, 1, Jump23,              nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Treble Reel",          clPaleBlue, 1, TrebleReel,          nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Beg Soft",             clPaleBlue, 4, BeginnerReel,        BeginnerLightJig, BeginnerSingleJig, BeginnerSlipJig, "Reel", "Light", "Single", "Slip" );
  FormSchedule(&Row, OutputExcel, Warning, "Beg Premiership",      clWhite,    1, BeginnerPremiership, nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Beg Hard",             clPaleBlue, 3, BeginnerTrebleJig,   BeginnerHornpipe, BeginnerTradSet,   nil,             "Treb", "Horn",  "Trad",   ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Results",              clPaleRed,  0, nil,                 nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Prim Soft",            clPaleBlue, 4, PrimaryReel,         PrimaryLightJig,  PrimarySingleJig,  PrimarySlipJig,  "Reel", "Light", "Single", "Slip" );
  FormSchedule(&Row, OutputExcel, Warning, "Prim Premiership",     clWhite,    1, PrimaryPremiership,  nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Prim Hard",            clPaleBlue, 3, PrimaryTrebleJig,    PrimaryHornpipe,  PrimaryTradSet,    nil,             "Treb", "Horn",  "Trad",   ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Figures (2-Hand)",     clWhite,    1, Group2Hand,          nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Figures (3-Hand)",     clWhite,    1, Group3Hand,          nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Figures (4-Hand)",     clWhite,    1, Group4Hand,          nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Figures (Ceili)",      clWhite,    1, GroupCeili,          nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Results",              clPaleRed,  0, nil,                 nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Int Soft",             clPaleBlue, 4, IntermedReel,        IntermedLightJig, IntermedSingleJig, IntermedSlipJig, "Reel", "Light", "Single", "Slip" );
  FormSchedule(&Row, OutputExcel, Warning, "Int Hard",             clWhite,    3, IntermedTrebleJig,   IntermedHornpipe, IntermedTradSet,   nil,             "Treb", "Horn",  "Trad",   ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Open Soft",            clPaleBlue, 2, OpenReel,            OpenSlipJig,      nil,               nil,             "Reel", "Slip",  "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Open Hard",            clWhite,    3, OpenTrebleJig,       OpenHornpipe,     OpenTradSet,       nil,             "Treb", "Horn",  "Trad",   ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Int Premiership",      clPaleBlue, 1, IntermedPremiership, nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Modern Set",           clPaleBlue, 1, ModernSet,           nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Preliminary",          clWhite,    1, PreChampionship,     nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Championship",         clPaleBlue, 1, Championship,        nil,              nil,               nil,             "",     "",      "",       ""     );
  FormSchedule(&Row, OutputExcel, Warning, "Results",              clPaleRed,  0, nil,                 nil,              nil,               nil,             "",     "",      "",       ""     );

  // Finalize
  delete OutputExcel;
  Warning->Hide();
  return true;
}
//---------------------------------------------------------------------------
AnsiString StdHeaderS[6] = {"Place", "Number", "Points", "Dancer's Name", "School", "Comments"};
int        StdHeaderW[6] = {6, 8, 8, 30, 35, 40};
AnsiString PrmHeaderS[9] = {"Position", "Number", "Dancer's Name", "School", "Judge A", "Judge B", "Judge C", "Total", "Comments"};
int        PrmHeaderW[9] = {8, 8, 30, 35, 9, 9, 9, 8, 40};
int        PrUHeaderW[9] = {8, 8, 30, 35, 20, 20, 20, 8, 40};
AnsiString FigHeaderS[6] = {"Position", "Number", "Points", "Dancer's name", "School name", "Comments"};
int        FigHeaderW[6] = {8, 8, 8, 70, 35, 40};
//---------------------------------------------------------------------------
void InitSheet(TExcel *Excel, int Columns, AnsiString Texts[], int Widths[])
{
  // Set row 2 appearance
  Excel->SelectRange(0, 1, Columns, 1);
  Excel->SetBkColor(clPaleGreen);
  Excel->SetFontFace("Calibri");
  Excel->SetFontSize(11);

  // Set header column titles
  for(int i = 0; i < Columns; ++i)
  {
    Excel->PutCell(0, i, Texts[i]);
    Excel->SetColWidth(i, Widths[i]);
  }

  // Set header appearance - this will be last selected area
  Excel->SelectRange(0, 0, Columns, 1);
  Excel->SetBorder(xlEdgeTop,    xlContinuous, xlThick);
  Excel->SetBorder(xlEdgeLeft,   xlContinuous, xlThick);
  Excel->SetBorder(xlEdgeRight,  xlContinuous, xlThick);
  Excel->SetBorder(xlEdgeBottom, xlContinuous, xlThick);
  Excel->SetBkColor(clGold);
  Excel->SetFontFace("Calibri");
  Excel->SetFontSize(11);
  Excel->SetFontBold();
}
//---------------------------------------------------------------------------
enum MarkType { conv, prem, champ, group };
const enum MarkType MarkTypes[TotalDances] =
//  Jump23 ModSet TrReel BgReel BgLigh BgSing BgSlip BgTreb BgHorn BgTrad BgPrem PrReel PrLigh PrSing PrSlip PrTreb PrHorn PrTrad PrPrem
  { conv,  conv,  conv,  conv,  conv,  conv,  conv,  conv,  conv,  conv,  prem,  conv,  conv,  conv,  conv,  conv,  conv,  conv,  prem,
//  InReel InLigh InSing InSlip InTreb InHorn InTrad InPrem OpReel OpSlip OpTreb OpHorn OpTrad PreChm Champs 2HandR 3HandR 4HandR Ceili
    conv,  conv,  conv,  conv,  conv,  conv,  conv,  prem,  conv,  conv,  conv,  conv,  conv,  prem,  champ, group, group, group, group };
const int MaxQualified[TotalDances] =
//  Jump23 ModSet TrReel BgReel BgLigh BgSing BgSlip BgTreb BgHorn BgTrad BgPrem PrReel PrLigh PrSing PrSlip PrTreb PrHorn PrTrad PrPrem
  { 0,     0,     0,     3,     3,     3,     3,     3,     3,     3,     0,     2,     2,     2,     2,     2,     2,     2,     0,
//  InReel InLigh InSing InSlip InTreb InHorn InTrad InPrem OpReel OpSlip OpTreb OpHorn OpTrad PreChm Champs 2HandR 3HandR 4HandR Ceili
    1,     1,     1,     1,     1,     1,     1,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0     };
//---------------------------------------------------------------------------
int OutputDance(int Row, TPanel *Warning, bool SaveResults, TExcel *Excel, enum Dances Dance, AnsiString Level, AnsiString Header, bool Unnormalized = false, bool AlterSchools = true)
{
  AnsiString Groups[TotalDances][TotalGroups];
  Database->GroupsFromDatabase(Groups);

  // Determine width of area
  int Width = ((MarkTypes[Dance] == prem) || (MarkTypes[Dance] == champ))? 9: 6;

  for (int Group = 0; ((Groups[Dance][Group] != "") && (Group < TotalGroups)); ++Group)
  {
    Warning->Caption = "Сохраняется танец " + Level + Header + " (" + Groups[Dance][Group] + ")...";
    Application->ProcessMessages();

    // Write dancers (with points and places if need)
    int Dancers = 0;
    for (int i = 0; i < Database->TotalDancers(); ++i)
    {
      TDancer *Dancer = Database->GetDancerByIndex(i);
      if (!Dancer->Dances[Dance]) continue;
      if (Dancer->AgeGroup[Dance] != Groups[Dance][Group]) continue;

      AnsiString Number = Dancer->Number;
      switch (MarkTypes[Dance])
      {
        case conv:  if (Dancer->isGroup) break;
        case group: if (!Dancer->isGroup && (MarkTypes[Dance] == group)) break;
          ++Dancers;
          // if(Dancer->isGroup) Number = "T" + Number; We'll do it later, AFTER sort.
          Excel->PutCell(Row + Dancers, 1, Number);
          Excel->PutCell(Row + Dancers, 3, Dancer->Name);
          Excel->PutCell(Row + Dancers, 4, AlterSchools? AlteredSchool(Dancer->School) : Dancer->School);
          if(!SaveResults) break;
          Excel->PutCell(Row + Dancers, 0, Dancer->Places[Dance]);
          Excel->PutCell(Row + Dancers, 2, PointsToStr(Dancer->CalcPoints[Dance]));
          Excel->PutCell(Row + Dancers, 5, Dancer->Comment[Dance]);
          break;

        case champ:
        case prem: if (Dancer->isGroup) break;
          ++Dancers;
          Excel->PutCell(Row + Dancers, 1, Number);
          Excel->PutCell(Row + Dancers, 2, Dancer->Name);
          Excel->PutCell(Row + Dancers, 3, AlterSchools? AlteredSchool(Dancer->School) : Dancer->School);
          if(!SaveResults) break;
          Excel->PutCell(Row + Dancers, 0, Dancer->Places[Dance]);
          if (Unnormalized)
          {
            if (Dance == Championship)
            {
              Excel->PutCell(Row + Dancers, 4, (AnsiString)"(" + PointsToStr(Dancer->RawPoints[Dance][0])  + ";" + PointsToStr(Dancer->RawPoints[Dance][1])  + ";" + PointsToStr(Dancer->RawPoints[Dance][2])  + ";" + PointsToStr(Dancer->RawPoints[Dance][3] ) + ")");
              Excel->PutCell(Row + Dancers, 5, (AnsiString)"(" + PointsToStr(Dancer->RawPoints[Dance][6])  + ";" + PointsToStr(Dancer->RawPoints[Dance][7])  + ";" + PointsToStr(Dancer->RawPoints[Dance][8])  + ";" + PointsToStr(Dancer->RawPoints[Dance][9] ) + ")");
              Excel->PutCell(Row + Dancers, 6, (AnsiString)"(" + PointsToStr(Dancer->RawPoints[Dance][12]) + ";" + PointsToStr(Dancer->RawPoints[Dance][13]) + ";" + PointsToStr(Dancer->RawPoints[Dance][14]) + ";" + PointsToStr(Dancer->RawPoints[Dance][15]) + ")");
            }
            else
            {
              Excel->PutCell(Row + Dancers, 4, (AnsiString)"(" + PointsToStr(Dancer->RawPoints[Dance][0]) + ";" + PointsToStr(Dancer->RawPoints[Dance][1] ) + ")");
              Excel->PutCell(Row + Dancers, 5, (AnsiString)"(" + PointsToStr(Dancer->RawPoints[Dance][4]) + ";" + PointsToStr(Dancer->RawPoints[Dance][5] ) + ")");
              Excel->PutCell(Row + Dancers, 6, (AnsiString)"(" + PointsToStr(Dancer->RawPoints[Dance][8]) + ";" + PointsToStr(Dancer->RawPoints[Dance][9]) + ")");
            }
          }
          else
          {
            Excel->PutCell(Row + Dancers, 4, PointsToStr(Dancer->RawPoints[Dance][(Dance == Championship)? 5: 3]));
            Excel->PutCell(Row + Dancers, 5, PointsToStr(Dancer->RawPoints[Dance][(Dance == Championship)? 11: 7]));
            Excel->PutCell(Row + Dancers, 6, PointsToStr(Dancer->RawPoints[Dance][(Dance == Championship)? 17: 11]));
          }
          Excel->PutCell(Row + Dancers, 7, PointsToStr(Dancer->CalcPoints[Dance]));
          Excel->PutCell(Row + Dancers, 8, Dancer->Comment[Dance]);
          break;
      }
    }

    if (Dancers == 0) continue;

    // Write header
    Excel->SelectRange(0, Row, Width, 1);
    Excel->SetBkColor(clGreen);
    Excel->SetFontColor(clWhite);
    Excel->PutCell(Row, 1, GroupToString(Groups[Dance][Group]));
    Excel->PutCell(Row, 3, Header);

    // Set border
    Excel->SelectRange(0, Row, Width, Dancers + 1);
    Excel->SetBorder(xlEdgeTop,          xlContinuous, xlThick);
    Excel->SetBorder(xlEdgeBottom,       xlContinuous, xlThick);
    Excel->SetBorder(xlEdgeLeft,         xlContinuous, xlThick);
    Excel->SetBorder(xlEdgeRight,        xlContinuous, xlThick);
    Excel->SetBorder(xlInsideHorizontal, xlContinuous, xlThin);
    Excel->SetBorder(xlInsideVertical,   xlContinuous, xlThin);
    Excel->SetFontFace("Calibri");
    Excel->SetFontSize(11);

    // Sort by numbers or places
    Excel->Sort(0, Row + 1, Width, Dancers + 1, SaveResults? 0: 1, xlAscending);

    // Add "T" to every number
    if(isGroupDance(Dance))
    {
      for (int i = 0; i < Dancers; ++i)
      {
        Excel->PutCell(Row + 1 + i, 1, "T" + Excel->GetCell(Row + 1 + i, 1));
      }
    }

    // Write qualification and set color of qualified line
    if(SaveResults && (MaxQualified[Dance] > 0))
    {
      for (int i = 0; i < Dancers; ++i)
      {
        AnsiString Number = Excel->GetCell(Row + 1 + i, 1);
        TDancer *Dancer = Database->GetDancerByNumber(Number);
        if (!Dancer->Qualified[Dance]) break; // End at first non-qualified line

        AnsiString Place = Excel->GetCell(Row + 1 + i, 0);
        Excel->PutCell(Row + 1 + i, 0, "q" + Place);
        Excel->SelectRange(0, Row + 1 + i, Width, 1);
        Excel->SetBkColor(clPaleYellow);
      }
    }

    // Write footer and alter Row
    Excel->SelectRange(0, Row + Dancers + 1, Width, 1);
    Excel->SetBkColor(clPaleGreen);
    Excel->SetFontFace("Calibri");
    Excel->SetFontSize(11);
    Row += Dancers + 2;
  }

  return Row;
}
//---------------------------------------------------------------------------
bool ExportResults(AnsiString FileName, TPanel *Warning, bool SaveResults, bool Unnormalized, bool AlterSchools)
{
  bool ClearAllDatabase = true;
  int Row;
  Warning->Show();
  Warning->Caption = "Создается Excel-файл...";
  Application->ProcessMessages();

  // Filling sheets in reverse order (so this is Excel specific)
  TExcel *OutputExcel;
  try { OutputExcel = new TExcel(FileName, xlCreate); }
  catch(...)
  {
    Application->MessageBox("Невозможно создать выбранный файл", "Ошибка создания файла", MB_OK);
    Warning->Hide();
    return false;
  }

  OutputExcel->CreateSheet("Figures", ClearAllDatabase);
  Row = OutputDance(2,   Warning, SaveResults, OutputExcel, Group2Hand,          "", "2-Hand", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, Group3Hand,          "", "3-Hand", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, Group4Hand,          "", "4-Hand", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, GroupCeili,          "", "Ceili", Unnormalized, AlterSchools);
  if (Row > 2) { InitSheet(OutputExcel, 6, FigHeaderS, FigHeaderW); ClearAllDatabase = false; }
  else OutputExcel->DeleteSheet(&ClearAllDatabase);

  OutputExcel->CreateSheet("Championship", ClearAllDatabase);
  Row = OutputDance(2,   Warning, SaveResults, OutputExcel, Championship,        "", "Championship", Unnormalized, AlterSchools);
  if (Row > 2) { InitSheet(OutputExcel, 9, PrmHeaderS, Unnormalized ? PrUHeaderW : PrmHeaderW); ClearAllDatabase = false; }
  else OutputExcel->DeleteSheet(&ClearAllDatabase);

  OutputExcel->CreateSheet("Pre championship", ClearAllDatabase);
  Row = OutputDance(2,   Warning, SaveResults, OutputExcel, PreChampionship,     "", "Pre championship", Unnormalized, AlterSchools);
  if (Row > 2) { InitSheet(OutputExcel, 9, PrmHeaderS, PrmHeaderW); ClearAllDatabase = false; }
  else OutputExcel->DeleteSheet(&ClearAllDatabase);

  OutputExcel->CreateSheet("Premierships", ClearAllDatabase);
  Row = OutputDance(2,   Warning, SaveResults, OutputExcel, BeginnerPremiership, "", "Beg Prem", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, PrimaryPremiership,  "", "Prim Prem", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, IntermedPremiership, "", "Int Prem", Unnormalized, AlterSchools);
  if (Row > 2) { InitSheet(OutputExcel, 9, PrmHeaderS, PrmHeaderW); ClearAllDatabase = false; }
  else OutputExcel->DeleteSheet(&ClearAllDatabase);

  OutputExcel->CreateSheet("Open", ClearAllDatabase);
  Row = OutputDance(2,   Warning, SaveResults, OutputExcel, OpenReel,            "Open ", "Reel", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, OpenSlipJig,         "Open ", "Slip Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, OpenTrebleJig,       "Open ", "Treble Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, OpenHornpipe,        "Open ", "Hornpipe", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, OpenTradSet,         "Open ", "Trad Set", Unnormalized, AlterSchools);
  if (Row > 2) { InitSheet(OutputExcel, 6, StdHeaderS, StdHeaderW); ClearAllDatabase = false; }
  else OutputExcel->DeleteSheet(&ClearAllDatabase);

  OutputExcel->CreateSheet("Intermediate", ClearAllDatabase);
  Row = OutputDance(2,   Warning, SaveResults, OutputExcel, IntermedReel,        "Int ",  "Reel", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, IntermedLightJig,    "Int ",  "Light Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, IntermedSingleJig,   "Int ",  "Single Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, IntermedSlipJig,     "Int ",  "Slip Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, IntermedTrebleJig,   "Int ",  "Treble Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, IntermedHornpipe,    "Int ",  "Hornpipe", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, IntermedTradSet,     "Int ",  "Trad Set", Unnormalized, AlterSchools);
  if (Row > 2) { InitSheet(OutputExcel, 6, StdHeaderS, StdHeaderW); ClearAllDatabase = false; }
  else OutputExcel->DeleteSheet(&ClearAllDatabase);

  OutputExcel->CreateSheet("Primary", ClearAllDatabase);
  Row = OutputDance(2,   Warning, SaveResults, OutputExcel, PrimaryReel,         "Prim ", "Reel", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, PrimaryLightJig,     "Prim ", "Light Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, PrimarySingleJig,    "Prim ", "Single Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, PrimarySlipJig,      "Prim ", "Slip Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, PrimaryTrebleJig,    "Prim ", "Treble Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, PrimaryHornpipe,     "Prim ", "Hornpipe", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, PrimaryTradSet,      "Prim ", "Trad Set", Unnormalized, AlterSchools);
  if (Row > 2) { InitSheet(OutputExcel, 6, StdHeaderS, StdHeaderW); ClearAllDatabase = false; }
  else OutputExcel->DeleteSheet(&ClearAllDatabase);

  OutputExcel->CreateSheet("Beginner", ClearAllDatabase);
  Row = OutputDance(2,   Warning, SaveResults, OutputExcel, Jump23,              "",      "Jump 2 3", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, BeginnerReel,        "Beg ",  "Reel", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, BeginnerLightJig,    "Beg ",  "Light Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, BeginnerSingleJig,   "Beg ",  "Single Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, BeginnerSlipJig,     "Beg ",  "Slip Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, BeginnerTrebleJig,   "Beg ",  "Treble Jig", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, BeginnerHornpipe,    "Beg ",  "Hornpipe", Unnormalized, AlterSchools);
  Row = OutputDance(Row, Warning, SaveResults, OutputExcel, BeginnerTradSet,     "Beg ",  "Trad Set", Unnormalized, AlterSchools);
  if (Row > 2) { InitSheet(OutputExcel, 6, StdHeaderS, StdHeaderW); ClearAllDatabase = false; }
  else OutputExcel->DeleteSheet(&ClearAllDatabase);

  OutputExcel->CreateSheet("Modern Set", ClearAllDatabase);
  Row = OutputDance(2,   Warning, SaveResults, OutputExcel, ModernSet,           "",      "Modern Set", Unnormalized, AlterSchools);
  if (Row > 2) { InitSheet(OutputExcel, 6, StdHeaderS, StdHeaderW); ClearAllDatabase = false; }
  else OutputExcel->DeleteSheet(&ClearAllDatabase);

  OutputExcel->CreateSheet("Treble Reel", ClearAllDatabase);
  Row = OutputDance(2,   Warning, SaveResults, OutputExcel, TrebleReel,          "",      "Treble Reel", Unnormalized, AlterSchools);
  if (Row > 2) { InitSheet(OutputExcel, 6, StdHeaderS, StdHeaderW); ClearAllDatabase = false; }
  else OutputExcel->DeleteSheet(&ClearAllDatabase);

  delete OutputExcel;
  Warning->Hide();
  return true;
}
//---------------------------------------------------------------------------
int OutputStageTable(int Row, TPanel *Warning, TExcel *Excel, enum Dances Dance, AnsiString Level, AnsiString Header)
{
  AnsiString Groups[TotalDances][TotalGroups];
  Database->GroupsFromDatabase(Groups);

  for (int Group = 0; ((Groups[Dance][Group] != "") && (Group < TotalGroups)); ++Group)
  {
    Warning->Caption = "Сохраняется танец " + Level + Header + " (" + Groups[Dance][Group] + ")...";
    Application->ProcessMessages();

    // Write dancers
    int Dancers = 0;
    for (int i = 0; i < Database->TotalDancers(); ++i)
    {
      TDancer *Dancer = Database->GetDancerByIndex(i);
      if (!Dancer->Dances[Dance]) continue;
      if (Dancer->AgeGroup[Dance] != Groups[Dance][Group]) continue;

      AnsiString Number = Dancer->Number;
      switch (MarkTypes[Dance])
      {
        case conv:  if (Dancer->isGroup) break;
        case group: if (!Dancer->isGroup && (MarkTypes[Dance] == group)) break;
          ++Dancers;
          // if(Dancer->isGroup) Number = "T" + Number; (Do it later!)
          Excel->PutCell(Row + Dancers, 1, Number);
          Excel->PutCell(Row + Dancers, 2, Dancer->Name);
          break;

        case champ:
        case prem: if (Dancer->isGroup) break;
          ++Dancers;
          Excel->PutCell(Row + Dancers, 1, Number);
          Excel->PutCell(Row + Dancers, 2, Dancer->Name);
          break;
      }
    }

    if (Dancers == 0) continue;

    // Write header
    Excel->SelectRange(1, Row, 2, 1);
    Excel->Join();
    //Excel->SetBkColor(clPaleGreen);
    //Excel->SetFontColor(clWhite);
    Excel->PutCell(Row, 1, Level + " " + Header + " " + GroupToString(Groups[Dance][Group]));

    // Sort
    Excel->Sort(1, Row + 1, 2, Dancers, 0, xlAscending);

    // Add "T" to every number
    if(isGroupDance(Dance))
    {
      for (int i = 0; i < Dancers; ++i)
      {
        Excel->PutCell(Row + 1 + i, 1, "T" + Excel->GetCell(Row + 1 + i, 1));
      }
    }

    // Set font
    Excel->SelectRange(1, Row, 2, Dancers + 1);
    Excel->SetFontFace("Calibri");
    Excel->SetFontSize(11);

    /*
      Excel->SetBorder(xlEdgeTop,          xlContinuous, xlThick);
      Excel->SetBorder(xlEdgeBottom,       xlContinuous, xlThick);
      Excel->SetBorder(xlEdgeLeft,         xlContinuous, xlThick);
      Excel->SetBorder(xlEdgeRight,        xlContinuous, xlThick);
      Excel->SetBorder(xlInsideHorizontal, xlContinuous, xlThin);
      Excel->SetBorder(xlInsideVertical,   xlContinuous, xlThin);
    */

    /*
      Excel->SelectRange(1, Row + 1, 2, Dancers);
      Excel->SetBkColor(clWhite);
      Excel->SetFontFace("Calibri");
      Excel->SetFontSize(11);
    */

    Row += 2 + Dancers;
  }

  return Row;
}
//---------------------------------------------------------------------------
bool ExportStageLists(AnsiString FileName, TPanel *Warning)
{
  Warning->Show();
  Warning->Caption = "Создаются стейдж-листы...";
  Application->ProcessMessages();

  TExcel *OutputExcel;
  try { OutputExcel = new TExcel(FileName, xlCreate); }
  catch(...)
  {
    Application->MessageBox("Невозможно создать выбранный файл", "Ошибка создания файла", MB_OK);
    Warning->Hide();
    return false;
  }

  OutputExcel->CreateSheet("Stage Lists", true);
  OutputExcel->SetColWidth(0, 8);
  OutputExcel->SetColWidth(1, 8);
  OutputExcel->SetColWidth(2, 40);

  int Row = 1;
  Row = OutputStageTable(Row, Warning, OutputExcel, Jump23,              "",      "Jump 2 3");
  Row = OutputStageTable(Row, Warning, OutputExcel, TrebleReel,          "",      "Treble Reel");
  Row = OutputStageTable(Row, Warning, OutputExcel, ModernSet,           "",      "Modern Set");
  Row = OutputStageTable(Row, Warning, OutputExcel, BeginnerReel,        "Beg ",  "Reel");
  Row = OutputStageTable(Row, Warning, OutputExcel, BeginnerLightJig,    "Beg ",  "Light Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, BeginnerSingleJig,   "Beg ",  "Single Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, BeginnerSlipJig,     "Beg ",  "Slip Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, BeginnerTrebleJig,   "Beg ",  "Treble Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, BeginnerHornpipe,    "Beg ",  "Hornpipe");
  Row = OutputStageTable(Row, Warning, OutputExcel, BeginnerTradSet,     "Beg ",  "Trad Set");
  Row = OutputStageTable(Row, Warning, OutputExcel, PrimaryReel,         "Prim ", "Reel");
  Row = OutputStageTable(Row, Warning, OutputExcel, PrimaryLightJig,     "Prim ", "Light Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, PrimarySingleJig,    "Prim ", "Single Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, PrimarySlipJig,      "Prim ", "Slip Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, PrimaryTrebleJig,    "Prim ", "Treble Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, PrimaryHornpipe,     "Prim ", "Hornpipe");
  Row = OutputStageTable(Row, Warning, OutputExcel, PrimaryTradSet,      "Prim ", "Trad Set");
  Row = OutputStageTable(Row, Warning, OutputExcel, IntermedReel,        "Int ",  "Reel");
  Row = OutputStageTable(Row, Warning, OutputExcel, IntermedLightJig,    "Int ",  "Light Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, IntermedSingleJig,   "Int ",  "Single Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, IntermedSlipJig,     "Int ",  "Slip Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, IntermedTrebleJig,   "Int ",  "Treble Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, IntermedHornpipe,    "Int ",  "Hornpipe");
  Row = OutputStageTable(Row, Warning, OutputExcel, IntermedTradSet,     "Int ",  "Trad Set");
  Row = OutputStageTable(Row, Warning, OutputExcel, OpenReel,            "Open ", "Reel");
  Row = OutputStageTable(Row, Warning, OutputExcel, OpenSlipJig,         "Open ", "Slip Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, OpenTrebleJig,       "Open ", "Treble Jig");
  Row = OutputStageTable(Row, Warning, OutputExcel, OpenHornpipe,        "Open ", "Hornpipe");
  Row = OutputStageTable(Row, Warning, OutputExcel, OpenTradSet,         "Open ", "Trad Set");
  Row = OutputStageTable(Row, Warning, OutputExcel, Group2Hand,          "",      "2-Hand");
  Row = OutputStageTable(Row, Warning, OutputExcel, Group3Hand,          "",      "3-Hand");
  Row = OutputStageTable(Row, Warning, OutputExcel, Group4Hand,          "",      "4-Hand");
  Row = OutputStageTable(Row, Warning, OutputExcel, GroupCeili,          "",      "Ceili");
  Row = OutputStageTable(Row, Warning, OutputExcel, BeginnerPremiership, "",      "Beg Prem");
  Row = OutputStageTable(Row, Warning, OutputExcel, PrimaryPremiership,  "",      "Prim Prem");
  Row = OutputStageTable(Row, Warning, OutputExcel, IntermedPremiership, "",      "Int Prem");
  Row = OutputStageTable(Row, Warning, OutputExcel, PreChampionship,     "",      "Pre championship");
  Row = OutputStageTable(Row, Warning, OutputExcel, Championship,        "",      "Championship");
  delete OutputExcel;
  Warning->Hide();
  return true;
}
//---------------------------------------------------------------------------
AnsiString DanceNames[] =
{
  "Jump 2 3",    "Modern Set",  "Treb Reel",
  "Reel",        "Light Jig",   "Single Jig",  "Slip Jig",   "Treble Jig", "Hornpipe", "Trad Set", "Beg Prem",
  "Reel",        "Light Jig",   "Single Jig",  "Slip Jig",   "Treble Jig", "Hornpipe", "Trad Set", "Pri Prem",
  "Reel",        "Light Jig",   "Single Jig",  "Slip Jig",   "Treble Jig", "Hornpipe", "Trad Set", "Int Prem",
  "Reel",                                      "Slip Jig",   "Treble Jig", "Hornpipe", "Trad Set", "Pre Champ", "Champ",
  "2-Hand Reel", "3-Hand Reel", "4-Hand Reel", "Ceili"
};
//---------------------------------------------------------------------------
AnsiString DanceLevels[] =
{
  "",   "",   "",                                    // Jump23, Modern Set, and Treble Reel
  "B ", "B ", "B ", "B ", "B ", "B ", "B ", "",      // Beginner dances
  "P ", "P ", "P ", "P ", "P ", "P ", "P ", "",      // Primary
  "I ", "I ", "I ", "I ", "I ", "I ", "I ", "",      // Intermediate
  "O ", "O ",             "O ", "O ", "O ", "",  "", // Open
  "",   "",   "",   ""                               // Group dances
};
//---------------------------------------------------------------------------
const bool DanceIsHard[] =
{
  false, true,  true,                                             // Jump23, Modern Set, and Treble Reel
  false, false, false, false, true,  true,  true,  false,         // Beginner dances
  false, false, false, false, true,  true,  true,  false,         // Primary
  false, false, false, false, true,  true,  true,  false,         // Intermediate
  false, false,               true,  true,  true,  false, false,  // Open
  true,  true,  true,  true                                       // Group dances - output at right
};
//---------------------------------------------------------------------------
void AddNewNumber(TExcel *Excel, int Pos, bool isGroup, int Number,
                  AnsiString Name, AnsiString School, AnsiString Age,
                  bool Dances[TotalDances], AnsiString AgeGroup[TotalDances],
                  AnsiString TeamString)
{
  // Step 1. Create big number area
  AnsiString NumPrefix = isGroup ? "T" : "";
  /* Previously it was like this:
    Excel->SelectRange(0, Pos * 32, 8, 16);
    Excel->Join();
    Excel->SetRowHeight(-1, 15);
    Excel->SetValue(NumPrefix + Number);
    Excel->SetAlignment(xlCenter, xlCenter);
    Excel->SetFontFace("Arial Narrow");
    Excel->SetFontBold();
    Excel->SetFontSize(230);
    Excel->SelectRange(0, Pos * 32 + 16, 1, 2);
    Excel->SetRowHeight(-1, 17);
  */

  // Championship numbers format is as follows:
  Excel->SelectRange(0, Pos * 32, 9, 16);
  Excel->Join();
  Excel->SetRowHeight(-1, 15);
  Excel->SetValue(NumPrefix + Number);
  Excel->SetAlignment(xlCenter, xlCenter);
  Excel->SetFontFace("Arial Narrow");
  Excel->SetFontBold();
  Excel->SetFontSize(200);
  Excel->SelectRange(0, Pos * 32 + 16, 1, 3);
  Excel->SetRowHeight(-1, 16);

  // Step 2. Write number, name, age, school
  Excel->SelectCell(Pos * 32 + 19, 1);
  Excel->SetRowHeight(-1, 23);
  Excel->SetValue(NumPrefix + Number);
  Excel->SetAlignment(xlRight, xlBottom);
  Excel->SetFontFace("Arial Narrow");
  Excel->SetFontBold();
  Excel->SetFontSize(11);

  AnsiString AgeString = "Age: ";
  if (Age != 0) AgeString += Age;
  Excel->SelectCell(Pos * 32 + 19, 5);
  Excel->SetValue(AgeString);
  Excel->SetAlignment(xlLeft, xlBottom);
  Excel->SetFontFace("Arial Narrow");
  Excel->SetFontBold();
  Excel->SetFontSize(11);

  Excel->SelectRange(2, Pos * 32 + 19, 3, 1);
  Excel->Join();
  Excel->SetValue(Name);
  Excel->SetAlignment(xlLeft, xlBottom);
  Excel->SetFontFace("Arial Narrow");
  Excel->SetFontBold();
  Excel->SetFontSize(11);

  Excel->SelectRange(2, Pos * 32 + 20, 4, 1);
  Excel->SetRowHeight(-1, 24);
  Excel->Join();
  Excel->SetValue(AlteredSchool(School));
  Excel->SetAlignment(xlLeft, xlTop);
  Excel->SetFontFace("Arial Narrow");
  Excel->SetFontSize(11);

  // Step 3. Underline top part and set parameters for bottom one
  Excel->SelectRange(1, Pos * 32 + 30, 6, 1);
  Excel->SetRowHeight(-1, 10);
  Excel->SelectRange(1, Pos * 32 + 31, 6, 1);
  Excel->SetRowHeight(-1, 1);
  Excel->SelectRange(1, Pos * 32 + 21, 6, 9);
  //Excel->SetBorder(xlEdgeTop, xlContinuous, xlThin);
  Excel->SetRowHeight(-1, 15);
  Excel->SetAlignment(xlLeft, xlTop);
  Excel->SetFontFace("Arial Narrow");
  Excel->SetFontSize(10);

  // Step 4a. Write team members
  if(isGroup)
  {
    for(int j = 0; j < TeamStringLength(TeamString); ++j)
    {
      Excel->SelectRange(2, Pos * 32 + 21 + j, 4, 1);
      Excel->Join();
      Excel->SetValue(TeamStringGet(TeamString, j));
    }
    return;
  }

  // Step 4b. Write dances
  if ((Dances == NULL) || (AgeGroup == NULL)) return;
  int LeftLine = 21, RightLine = 21;
  for (int j = Jump23; j < TotalDances; ++j)
  {
    if (!Dances[j]) continue;
    int X, Y;
    if (DanceIsHard[j]) { X = 4; Y = RightLine; ++RightLine; }
    else                { X = 1; Y = LeftLine; ++LeftLine; }

    if (Y >= 30)
    {
      AnsiString errmsg = "Невозможно добавить танец " + DanceNames[j] + " " + DanceLevels[j] + "участнику " + Name + ".\nНет нужного места на бланке номерка.";
      Application->MessageBox(errmsg.c_str(), "Ошибка", MB_OK);
      continue;
    }

    AnsiString AgeGroupString = GroupToString(AgeGroup[j]);
    if (AgeGroupString != "")
    {
      Excel->PutCell(Pos * 32 + Y, X,     DanceNames[j]);
      Excel->PutCell(Pos * 32 + Y, X + 1, DanceLevels[j] + AgeGroupString);
    }
    else
    {
      AnsiString errmsg = "Неверная возрастная группа " + AgeGroup[j] + " в танце " + DanceNames[j] + " " + DanceLevels[j] + "у участника " + Name + ".\nТанец вписан в номерок не будет.";
      Application->MessageBox(errmsg.c_str(), "Ошибка", MB_OK);
      continue;
    }
  }
}
//---------------------------------------------------------------------------
bool ExportNumbers(AnsiString FileName, TPanel *Warning, int AdditionalSolo, int AdditionalTeam)
{
  Warning->Caption = "Подготовка файла...";
  Warning->Show();
  Application->ProcessMessages();

  TExcel *OutputExcel;
  try { OutputExcel = new TExcel(FileName, xlCreate); }
  catch(...)
  {
    Application->MessageBox("Невозможно создать выбранный файл", "Ошибка создания файла", MB_OK);
    Warning->Hide();
    return false;
  }

  int Total = Database->TotalDancers() + AdditionalSolo + AdditionalTeam;
  int CurrentPos = 0;
  OutputExcel->SetPageSetup(xlPaperA6, xlLandscape, 0, 1, 0, 1);
  OutputExcel->SetColWidth(0, 3);
  OutputExcel->SetColWidth(1, 9);
  OutputExcel->SetColWidth(2, 9);
  OutputExcel->SetColWidth(3, 7);
  OutputExcel->SetColWidth(4, 9);
  OutputExcel->SetColWidth(5, 9);
  OutputExcel->SetColWidth(6, 8);
  OutputExcel->SetColWidth(7, 9);
  OutputExcel->SetColWidth(8, 5 /*1*/);

  // Step 1. Add every solo dancer

  // Determine max number of existing dancers
  int MaxNumber = 0;
  for (int i = 0; i < Database->TotalDancers(); ++i)
  {
    TDancer *Dancer = Database->GetDancerByIndex(i);
    if (Dancer->isGroup) continue;
    if (MaxNumber < Dancer->Number) MaxNumber = Dancer->Number;
  }

  // Create numbers for them, skipping those who have no numbers
  for (int i = 1; i <= MaxNumber; ++i)
  {
    TDancer *Dancer = Database->GetDancerByNumber(i);
    if (Dancer == NULL) continue;
    AnsiString Info = "Создается номерок " + (AnsiString)Dancer->Number + " (всего " + Total + ")";
    Warning->Caption = Info;
    Application->ProcessMessages();
    AddNewNumber
    (
      OutputExcel,
      CurrentPos,
      false,
      Dancer->Number,
      Dancer->Name,
      Dancer->School,
      Dancer->Age,
      Dancer->Dances,
      Dancer->AgeGroup,
      ""
    );
    ++CurrentPos;
  }

  // Step 2. Add additional numbers for solo dancers
  ++MaxNumber;
  for (int i = MaxNumber; i < MaxNumber + AdditionalSolo; ++i)
  {
    AnsiString Info = "Создается номерок " + (AnsiString)i + " (всего " + Total + ")";
    Warning->Caption = Info;
    Application->ProcessMessages();
    AddNewNumber
    (
      OutputExcel,
      CurrentPos,
      false,
      i,
      "",
      "",
      "",
      NULL,
      NULL,
      ""
    );
    ++CurrentPos;
  }

  // Step 3. Add every team dancer

  // Determine max number of existing dancers
  MaxNumber = 0;
  for (int i = 0; i < Database->TotalDancers(); ++i)
  {
    TDancer *Dancer = Database->GetDancerByIndex(i);
    if (!Dancer->isGroup) continue;
    if (MaxNumber < Dancer->Number) MaxNumber = Dancer->Number;
  }

  // Create numbers for them, skipping those who have no numbers
  for (int i = 1; i <= MaxNumber; ++i)
  {
    TDancer *Dancer = Database->GetDancerByNumber(((AnsiString)"T") + i);
    if (Dancer == NULL) continue;
    for (int j = Group2Hand; j <= GroupCeili; ++j)  // We assume database is consistent
    {
      if (Dancer->Dances[j])
      {
        AnsiString Info = "Создается номерок T" + (AnsiString)Dancer->Number + " (всего " + Total + ")";
        Warning->Caption = Info;
        Application->ProcessMessages();
        AddNewNumber
        (
          OutputExcel,
          CurrentPos,
          true,
          Dancer->Number,
          DanceNames[j],
          Dancer->School,
          Dancer->AgeGroup[j],
          NULL,
          NULL,
          Dancer->Name
        );
        ++CurrentPos;
        break;
      }
    }
  }

  // Step 4. Add additional numbers for team dancers
  ++MaxNumber;
  for (int i = MaxNumber; i < MaxNumber + AdditionalTeam; ++i)
  {
    AnsiString Info = "Создается номерок T" + (AnsiString)i + " (всего " + Total + ")";
    Warning->Caption = Info;
    Application->ProcessMessages();
    AddNewNumber
    (
      OutputExcel,
      CurrentPos,
      true,
      i,
      "",
      "",
      "",
      NULL,
      NULL,
      ""
    );
    ++CurrentPos;
  }

  delete OutputExcel;
  Warning->Hide();
  return true;
}
//---------------------------------------------------------------------------
void OutputRow(int Row, TExcel *OutputExcel, AnsiString S1,  AnsiString S2,  AnsiString S3,  AnsiString S4,  AnsiString S5,
                                             AnsiString S6,  AnsiString S7,  AnsiString S8,  AnsiString S9,  AnsiString S10,
                                             AnsiString S11, AnsiString S12, AnsiString S13, AnsiString S14, AnsiString S15,
                                             AnsiString S16, AnsiString S17)
{
  OutputExcel->PutCell(Row, 0,  S1);
  OutputExcel->PutCell(Row, 1,  S2);
  OutputExcel->PutCell(Row, 2,  S3);
  OutputExcel->PutCell(Row, 3,  S4);
  OutputExcel->PutCell(Row, 4,  S5);
  OutputExcel->PutCell(Row, 5,  S6);
  OutputExcel->PutCell(Row, 6,  S7);
  OutputExcel->PutCell(Row, 7,  S8);
  OutputExcel->PutCell(Row, 8,  S9);
  OutputExcel->PutCell(Row, 9,  S10);
  OutputExcel->PutCell(Row, 10, S11);
  OutputExcel->PutCell(Row, 11, S12);
  OutputExcel->PutCell(Row, 12, S13);
  OutputExcel->PutCell(Row, 13, S14);
  OutputExcel->PutCell(Row, 14, S15);
  OutputExcel->PutCell(Row, 15, S16);
  OutputExcel->PutCell(Row, 16, S17);
}
//---------------------------------------------------------------------------
bool IsWIDA(TStrings *SchoolsWIDA, TDancer *D)
{
  return SchoolsWIDA->IndexOf(D->School) >= 0;
}
//---------------------------------------------------------------------------
void ExportBPIOPage(TExcel *OutputExcel, bool WithAgeGroups, AnsiString SchoolFilter, int CostRegW = 0, int CostSoloW = 0, int CostFigureW = 0, int CostPremW = 0, int CostChampW = 0, int CostEuroW = 0, int CostUnlimW = 0, int CostRegNW = 0, int CostSoloNW = 0, int CostFigureNW = 0, int CostPremNW = 0, int CostChampNW = 0, int CostEuroNW = 0, int CostUnlimNW = 0, TStrings *SchoolsWIDA = NULL, bool SortBySchools = false)
{
  OutputExcel->SetColWidth(0,  5);
  OutputExcel->SetColWidth(1,  5);
  OutputExcel->SetColWidth(2,  30);
  OutputExcel->SetColWidth(3,  40);
  OutputExcel->SetColWidth(4,  6);
  OutputExcel->SetColWidth(5,  6);
  OutputExcel->SetColWidth(6,  6);
  OutputExcel->SetColWidth(7,  6);
  OutputExcel->SetColWidth(8,  6);
  OutputExcel->SetColWidth(9,  6);
  OutputExcel->SetColWidth(10, 6);
  OutputExcel->SetColWidth(11, 6);
  OutputExcel->SetColWidth(12, 6);
  OutputExcel->SetColWidth(13, 6);
  OutputExcel->SetColWidth(14, 6);
  OutputExcel->SetColWidth(15, 6);
  OutputExcel->SetColWidth(16, 6);
  if (WithAgeGroups)
  {
    OutputExcel->SetColWidth(17, 6);
    OutputExcel->PutCell(0, 17, "Евро");
    OutputExcel->SetColWidth(18, 6);
    OutputExcel->PutCell(0, 18, "Рубли");
    OutputExcel->SetColWidth(19, 10);
    OutputExcel->PutCell(0, 19, "Безлимит");
    OutputExcel->SetColWidth(20, 6);
    OutputExcel->PutCell(0, 20, "Танцы");
  }

  int Row = 0;

  // Step 1. Add solo header
  OutputRow(Row++, OutputExcel, "№","Возр.","Имя и фамилия", "Название школы",
                                "J23", "ModSet", "TrReel", "Reel", "Light", "Single", "Slip",
                                "Treble", "Horn", "Trad", "Prem", "PreCh", "Champ");
  if (WithAgeGroups)
  {
    OutputExcel->SelectRange(0, 0, 21, 1);
  }
  else
  {
    OutputExcel->SelectRange(0, 0, 17, 1);
  }
  OutputExcel->SetAlignment(xlCenter, xlCenter);
  OutputExcel->SetFontBold();
  OutputExcel->SetBkColor(clGreen);
  OutputExcel->SetFontColor(clWhite);
  OutputExcel->SetBorder(xlEdgeTop,          xlContinuous, xlThin);
  OutputExcel->SetBorder(xlEdgeBottom,       xlContinuous, xlThin);
  OutputExcel->SetBorder(xlEdgeLeft,         xlContinuous, xlThin);
  OutputExcel->SetBorder(xlEdgeRight,        xlContinuous, xlThin);
  OutputExcel->SetBorder(xlInsideVertical,   xlContinuous, xlThin);

  // Step 2. Add every solo dancer
  TDictDances *SchoolDances = new TDictDances;
  for (int i = 0; i < Database->TotalDancers(); ++i)
  {
    TDancer *Dancer = Database->GetDancerByIndex(i);
    if (Dancer->isGroup || (SchoolFilter != "" && SchoolFilter != Dancer->School)) continue;
    bool       *D = Dancer->Dances;
    AnsiString *G = Dancer->AgeGroup;
    AnsiString School = Dancer->School;
    OutputExcel->SelectCell(Row, 3);
    OutputExcel->SetFontColor(SchoolsWIDA->IndexOf(School) >= 0 ? clBlack : clRed);
    if (SchoolsWIDA->IndexOf(School) < 0) School = StringReplace(School, "(Non-WIDA) ", "", TReplaceFlags() << rfReplaceAll);
    if(WithAgeGroups)
    {
      OutputRow
      (
        Row, OutputExcel, Dancer->Number, Dancer->Age, Dancer->Name, School,
        MakeBPIOEx(D[Jump23],               G[Jump23],              false,                 "",                    false,                  "",                     false,              ""),                 //jump 23
        MakeBPIOEx(D[ModernSet],            G[ModernSet],           false,                 "",                    false,                  "",                     false,              ""),                 //mod set
        MakeBPIOEx(D[TrebleReel],           G[TrebleReel],          false,                 "",                    false,                  "",                     false,              ""),                 //treb reel
        MakeBPIOEx(D[BeginnerReel],         G[BeginnerReel],        D[PrimaryReel],        G[PrimaryReel],        D[IntermedReel],        G[IntermedReel],        D[OpenReel],        G[OpenReel]),        //reel
        MakeBPIOEx(D[BeginnerLightJig],     G[BeginnerLightJig],    D[PrimaryLightJig],    G[PrimaryLightJig],    D[IntermedLightJig],    G[IntermedLightJig],    false,              ""),                 //light jig
        MakeBPIOEx(D[BeginnerSingleJig],    G[BeginnerSingleJig],   D[PrimarySingleJig],   G[PrimarySingleJig],   D[IntermedSingleJig],   G[IntermedSingleJig],   false,              ""),                 //single jig
        MakeBPIOEx(D[BeginnerSlipJig],      G[BeginnerSlipJig],     D[PrimarySlipJig],     G[PrimarySlipJig],     D[IntermedSlipJig],     G[IntermedSlipJig],     D[OpenSlipJig],     G[OpenSlipJig]),     //slip jig
        MakeBPIOEx(D[BeginnerTrebleJig],    G[BeginnerTrebleJig],   D[PrimaryTrebleJig],   G[PrimaryTrebleJig],   D[IntermedTrebleJig],   G[IntermedTrebleJig],   D[OpenTrebleJig],   G[OpenTrebleJig]),   //treble jig
        MakeBPIOEx(D[BeginnerHornpipe],     G[BeginnerHornpipe],    D[PrimaryHornpipe],    G[PrimaryHornpipe],    D[IntermedHornpipe],    G[IntermedHornpipe],    D[OpenHornpipe],    G[OpenHornpipe]),    //hornpipe
        MakeBPIOEx(D[BeginnerTradSet],      G[BeginnerTradSet],     D[PrimaryTradSet],     G[PrimaryTradSet],     D[IntermedTradSet],     G[IntermedTradSet],     D[OpenTradSet],     G[OpenTradSet]),     //trad. set
        MakeBPIOEx(D[BeginnerPremiership],  G[BeginnerPremiership], D[PrimaryPremiership], G[PrimaryPremiership], D[IntermedPremiership], G[IntermedPremiership], false,              ""),                 //prem
        MakeBPIOEx(false,                   "",                     false,                 "",                    false,                  "",                     D[PreChampionship], G[PreChampionship]), //pre chmp
        MakeBPIOEx(false,                   "",                     false,                 "",                    false,                  "",                     D[Championship],    G[Championship])     //chmp
      );

      int CostReg    = IsWIDA(SchoolsWIDA, Dancer) ? CostRegW    : CostRegNW;
      int CostSolo   = IsWIDA(SchoolsWIDA, Dancer) ? CostSoloW   : CostSoloNW;
      int CostFigure = IsWIDA(SchoolsWIDA, Dancer) ? CostFigureW : CostFigureNW;
      int CostPrem   = IsWIDA(SchoolsWIDA, Dancer) ? CostPremW   : CostPremNW;
      int CostChamp  = IsWIDA(SchoolsWIDA, Dancer) ? CostChampW  : CostChampNW;
      int CostEuro   = IsWIDA(SchoolsWIDA, Dancer) ? CostEuroW   : CostEuroNW;
      int CostUnlim  = IsWIDA(SchoolsWIDA, Dancer) ? CostUnlimW  : CostUnlimNW;

      int dances = CostReg, regs = 0;
      if(D[Jump23])              {dances += CostSolo;  ++regs; }
      if(D[ModernSet])           {dances += CostSolo;  ++regs; }
      if(D[TrebleReel])          {dances += CostSolo;  ++regs; }
      if(D[BeginnerReel])        {dances += CostSolo;  ++regs; }
      if(D[PrimaryReel])         {dances += CostSolo;  ++regs; }
      if(D[IntermedReel])        {dances += CostSolo;  ++regs; }
      if(D[OpenReel])            {dances += CostSolo;  ++regs; }
      if(D[BeginnerLightJig])    {dances += CostSolo;  ++regs; }
      if(D[PrimaryLightJig])     {dances += CostSolo;  ++regs; }
      if(D[IntermedLightJig])    {dances += CostSolo;  ++regs; }
      if(D[BeginnerSingleJig])   {dances += CostSolo;  ++regs; }
      if(D[PrimarySingleJig])    {dances += CostSolo;  ++regs; }
      if(D[IntermedSingleJig])   {dances += CostSolo;  ++regs; }
      if(D[BeginnerSlipJig])     {dances += CostSolo;  ++regs; }
      if(D[PrimarySlipJig])      {dances += CostSolo;  ++regs; }
      if(D[IntermedSlipJig])     {dances += CostSolo;  ++regs; }
      if(D[OpenSlipJig])         {dances += CostSolo;  ++regs; }
      if(D[BeginnerTrebleJig])   {dances += CostSolo;  ++regs; }
      if(D[PrimaryTrebleJig])    {dances += CostSolo;  ++regs; }
      if(D[IntermedTrebleJig])   {dances += CostSolo;  ++regs; }
      if(D[OpenTrebleJig])       {dances += CostSolo;  ++regs; }
      if(D[BeginnerHornpipe])    {dances += CostSolo;  ++regs; }
      if(D[PrimaryHornpipe])     {dances += CostSolo;  ++regs; }
      if(D[IntermedHornpipe])    {dances += CostSolo;  ++regs; }
      if(D[OpenHornpipe])        {dances += CostSolo;  ++regs; }
      if(D[BeginnerTradSet])     {dances += CostSolo;  ++regs; }
      if(D[PrimaryTradSet])      {dances += CostSolo;  ++regs; }
      if(D[IntermedTradSet])     {dances += CostSolo;  ++regs; }
      if(D[OpenTradSet])         {dances += CostSolo;  ++regs; }
      if(D[BeginnerPremiership]) {dances += CostPrem;  ++regs; }
      if(D[PrimaryPremiership])  {dances += CostPrem;  ++regs; }
      if(D[IntermedPremiership]) {dances += CostPrem;  ++regs; }
      if(D[PreChampionship])     {dances += CostChamp; ++regs; }
      if(D[Championship])        {dances += CostChamp; ++regs; }
      // Each group dance should count as additional one
      for (int j = 0; j < Database->TotalDancers(); ++j)
      {
        TDancer *DGroup = Database->GetDancerByIndex(j);
        if (!DGroup->isGroup || DGroup->School != Dancer->School) continue;

        for(int k = 0; k < TeamStringLength(DGroup->Name); ++k)
        {
          AnsiString DancerName = TeamStringGet(DGroup->Name, k);
          if (Dancer->Name == DancerName) { dances += CostFigure; ++regs; }
        }
      }

      if (CostUnlim > 0 && dances >= CostUnlim)
      {
        dances = CostUnlim;
        OutputExcel->SelectCell(Row, 17);
        OutputExcel->SetFontBold();
        OutputExcel->SelectCell(Row, 18);
        OutputExcel->SetFontBold();
        OutputExcel->SelectCell(Row, 19);
        OutputExcel->SetFontBold();
      }
      OutputExcel->SelectCell(Row, 17);
      OutputExcel->SetFontColor(IsWIDA(SchoolsWIDA, Dancer) ? clBlack : clRed);
      OutputExcel->SelectCell(Row, 18);
      OutputExcel->SetFontColor(IsWIDA(SchoolsWIDA, Dancer) ? clBlack : clRed);
      OutputExcel->SelectCell(Row, 19);
      OutputExcel->SetFontColor(IsWIDA(SchoolsWIDA, Dancer) ? clBlack : clRed);
      OutputExcel->PutCell(Row, 17, (AnsiString)dances);
      OutputExcel->PutCell(Row, 18, (AnsiString)(dances * CostEuro));
      OutputExcel->PutCell(Row, 19, (dances == CostUnlim ? "Безлимит" : ""));
      OutputExcel->PutCell(Row, 20, (AnsiString)regs);
      SchoolDances->Add(Dancer->School, dances);
      Row++;
    }
    else
    {
      OutputRow
      (
        Row++, OutputExcel, Dancer->Number, Dancer->Age, Dancer->Name, School,
        MakeBPIO(D[Jump23],               false,                 false,                  false),              //jump 23
        MakeBPIO(D[ModernSet],            false,                 false,                  false),              //mod set
        MakeBPIO(D[TrebleReel],           false,                 false,                  false),              //treb reel
        MakeBPIO(D[BeginnerReel],         D[PrimaryReel],        D[IntermedReel],        D[OpenReel]),        //reel
        MakeBPIO(D[BeginnerLightJig],     D[PrimaryLightJig],    D[IntermedLightJig],    false),              //light jig
        MakeBPIO(D[BeginnerSingleJig],    D[PrimarySingleJig],   D[IntermedSingleJig],   false),              //single jig
        MakeBPIO(D[BeginnerSlipJig],      D[PrimarySlipJig],     D[IntermedSlipJig],     D[OpenSlipJig]),     //slip jig
        MakeBPIO(D[BeginnerTrebleJig],    D[PrimaryTrebleJig],   D[IntermedTrebleJig],   D[OpenTrebleJig]),   //treble jig
        MakeBPIO(D[BeginnerHornpipe],     D[PrimaryHornpipe],    D[IntermedHornpipe],    D[OpenHornpipe]),    //hornpipe
        MakeBPIO(D[BeginnerTradSet],      D[PrimaryTradSet],     D[IntermedTradSet],     D[OpenTradSet]),     //trad. set
        MakeBPIO(D[BeginnerPremiership],  D[PrimaryPremiership], D[IntermedPremiership], false),              //prem
        MakeBPIO(false,                   false,                 false,                  D[PreChampionship]), //pre chmp
        MakeBPIO(false,                   false,                 false,                  D[Championship])     //chmp
      );
    }
  }
  if (Row > 1)
  {
    if (WithAgeGroups)
    {
      if (SortBySchools) OutputExcel->Sort(0, 1, 21, Row - 1, 3, xlAscending);
      OutputExcel->SelectRange(0, 1, 21, Row - 1);
    }
    else
    {
      if (SortBySchools) OutputExcel->Sort(0, 1, 17, Row - 1, 3, xlAscending);
      OutputExcel->SelectRange(0, 1, 17, Row - 1);
    }
    OutputExcel->SetBkColor(clPaleYellow);
    OutputExcel->SetBorder(xlEdgeTop,          xlContinuous, xlThin);
    OutputExcel->SetBorder(xlEdgeBottom,       xlContinuous, xlThin);
    OutputExcel->SetBorder(xlEdgeLeft,         xlContinuous, xlThin);
    OutputExcel->SetBorder(xlEdgeRight,        xlContinuous, xlThin);
    OutputExcel->SetBorder(xlInsideVertical,   xlContinuous, xlThin);
    if (Row > 2) OutputExcel->SetBorder(xlInsideHorizontal, xlContinuous, xlThin);
  }

  // Step 3. Add teams header
  OutputRow(++Row, OutputExcel, "№","","Танец", "Название школы", "Участники команды", "", "", "", "", "", "", "", "", "", "", "", "");
  OutputExcel->SelectRange(0, Row, 17, 1);
  OutputExcel->SetAlignment(xlCenter, xlCenter);
  OutputExcel->SetFontBold();
  OutputExcel->SetBkColor(clGreen);
  OutputExcel->SetFontColor(clWhite);
  OutputExcel->SetBorder(xlEdgeTop,          xlContinuous, xlThin);
  OutputExcel->SetBorder(xlEdgeBottom,       xlContinuous, xlThin);
  OutputExcel->SetBorder(xlEdgeLeft,         xlContinuous, xlThin);
  OutputExcel->SetBorder(xlEdgeRight,        xlContinuous, xlThin);
  OutputExcel->SetBorder(xlInsideVertical,   xlContinuous, xlThin);
  OutputExcel->SelectRange(0, Row, 2,  1); OutputExcel->Join();
  OutputExcel->SelectRange(4, Row, 13, 1); OutputExcel->Join();

  // Step 4. Add every team dancer
  int StartRow = ++Row;
  for (int i = 0; i < Database->TotalDancers(); ++i)
  {
    TDancer *Dancer = Database->GetDancerByIndex(i);
    if (!Dancer->isGroup || (SchoolFilter != "" && SchoolFilter != Dancer->School)) continue;
    for (int j = Group2Hand; j <= GroupCeili; ++j)  // We assume database is consistent
    {
      if (Dancer->Dances[j])
      {
        AnsiString Dance = DanceNames[j] + " " + GroupToString(Dancer->AgeGroup[j]);
        AnsiString School = Dancer->School;
        OutputExcel->SelectCell(Row, 3);
        OutputExcel->SetFontColor(SchoolsWIDA->IndexOf(School) >= 0 ? clBlack : clRed);
        OutputRow(Row, OutputExcel, Dancer->Number, "", Dance, SchoolsWIDA->IndexOf(School) >= 0 ? School : StringReplace(School, "(Non-WIDA) ", "", TReplaceFlags() << rfReplaceAll), Dancer->Name, "", "", "", "", "", "", "", "", "", "", "", "");
        //SchoolDances->Add(Dancer->School, 1);
        ++Row;
        break;
      }
    }
  }
  if (Row > StartRow)
  {
    OutputExcel->Sort(0, StartRow, 17, Row - StartRow, SortBySchools ? 3 : 0, xlAscending);
    for (int i = StartRow; i < Row; ++i)
    {
      // We can't sort with joined cells and "T" in number, so do it here, after sort.
      OutputExcel->PutCell(i, 0, (AnsiString)"T" + OutputExcel->GetCell(i, 0));
      OutputExcel->SelectRange(0, i, 2,  1); OutputExcel->Join();
      OutputExcel->SelectRange(4, i, 13, 1); OutputExcel->Join();
    }
    OutputExcel->SelectRange(0, StartRow, 17, Row - StartRow);
    OutputExcel->SetBkColor(clPaleYellow);
    OutputExcel->SetBorder(xlEdgeTop,          xlContinuous, xlThin);
    OutputExcel->SetBorder(xlEdgeBottom,       xlContinuous, xlThin);
    OutputExcel->SetBorder(xlEdgeLeft,         xlContinuous, xlThin);
    OutputExcel->SetBorder(xlEdgeRight,        xlContinuous, xlThin);
    OutputExcel->SetBorder(xlInsideVertical,   xlContinuous, xlThin);
    if (Row > StartRow + 1) OutputExcel->SetBorder(xlInsideHorizontal, xlContinuous, xlThin);
  }

  // Step 5. Add fee list
  if(WithAgeGroups && SchoolFilter == "")
  {
    ++Row;
    OutputExcel->PutCell(Row, 3,  "Название школы");
    OutputExcel->PutCell(Row, 4,  "Евро");
    OutputExcel->PutCell(Row, 5,  "Рубли");
    OutputExcel->SelectRange(3, Row, 3, 1);
    OutputExcel->SetAlignment(xlCenter, xlCenter);
    OutputExcel->SetFontBold();
    OutputExcel->SetBkColor(clGreen);
    OutputExcel->SetFontColor(clWhite);
    OutputExcel->SetBorder(xlEdgeTop,          xlContinuous, xlThin);
    OutputExcel->SetBorder(xlEdgeBottom,       xlContinuous, xlThin);
    OutputExcel->SetBorder(xlEdgeLeft,         xlContinuous, xlThin);
    OutputExcel->SetBorder(xlEdgeRight,        xlContinuous, xlThin);
    OutputExcel->SetBorder(xlInsideVertical,   xlContinuous, xlThin);
    StartRow = ++Row;

    int dances;
    AnsiString School;
    while (SchoolDances->Get(School, dances))
    {
      OutputExcel->SelectCell(Row, 4);
      OutputExcel->SetFontColor(SchoolsWIDA->IndexOf(School) >= 0 ? clBlack : clRed);
      OutputExcel->PutCell(Row, 4, (AnsiString)dances);
      OutputExcel->SelectCell(Row, 5);
      OutputExcel->SetFontColor(SchoolsWIDA->IndexOf(School) >= 0 ? clBlack : clRed);
      OutputExcel->PutCell(Row, 5, (AnsiString)(dances * (SchoolsWIDA->IndexOf(School) >= 0 ? CostEuroW : CostEuroNW)));
      OutputExcel->SelectCell(Row, 3);
      OutputExcel->SetFontColor(SchoolsWIDA->IndexOf(School) >= 0 ? clBlack : clRed);
      OutputExcel->PutCell(Row, 3, SchoolsWIDA->IndexOf(School) >= 0 ? School : StringReplace(School, "(Non-WIDA) ", "", TReplaceFlags() << rfReplaceAll));
      ++Row;
    }

    if (SortBySchools) OutputExcel->Sort(3, StartRow, 3, Row - StartRow, 0, xlAscending);
    OutputExcel->SelectRange(3, StartRow, 3, Row - StartRow);
    OutputExcel->SetBkColor(clPaleYellow);
    OutputExcel->SetBorder(xlEdgeTop,          xlContinuous, xlThin);
    OutputExcel->SetBorder(xlEdgeBottom,       xlContinuous, xlThin);
    OutputExcel->SetBorder(xlEdgeLeft,         xlContinuous, xlThin);
    OutputExcel->SetBorder(xlEdgeRight,        xlContinuous, xlThin);
    OutputExcel->SetBorder(xlInsideVertical,   xlContinuous, xlThin);
    if (Row > StartRow + 1) OutputExcel->SetBorder(xlInsideHorizontal, xlContinuous, xlThin);
  }

  delete SchoolDances;
}
//---------------------------------------------------------------------------
bool ExportBPIOGeneric(AnsiString FileName, TPanel *Warning, bool WithAgeGroups, TStrings *SchoolsWIDA, bool SortBySchools = false, TStringList *SchoolsList = new TStringList(), int CostRegW = 0, int CostSoloW = 0, int CostFigureW = 0, int CostPremW = 0, int CostChampW = 0, int CostEuroW = 0, int CostUnlimW = 0, int CostRegNW = 0, int CostSoloNW = 0, int CostFigureNW = 0, int CostPremNW = 0, int CostChampNW = 0, int CostEuroNW = 0, int CostUnlimNW = 0)
{
  Warning->Caption = "Подготовка файла...";
  Warning->Show();
  Application->ProcessMessages();

  TExcel *OutputExcel;
  try { OutputExcel = new TExcel(FileName, xlCreate); }
  catch(...)
  {
    Application->MessageBox("Невозможно создать выбранный файл", "Ошибка создания файла", MB_OK);
    Warning->Hide();
    return false;
  }

  OutputExcel->CreateSheet("Все школы", true);
  ExportBPIOPage(OutputExcel, WithAgeGroups, "", CostRegW, CostSoloW, CostFigureW, CostPremW, CostChampW, CostEuroW, CostUnlimW, CostRegNW, CostSoloNW, CostFigureNW, CostPremNW, CostChampNW, CostEuroNW, CostUnlimNW, SchoolsWIDA, SortBySchools);
  if(WithAgeGroups)
  {
    for(int i = 0; i < SchoolsList->Count; ++i)
    {
      OutputExcel->CreateSheet(StringReplace((*SchoolsList)[i], "(Non-WIDA) ", "! ", TReplaceFlags() << rfReplaceAll), false);
      ExportBPIOPage(OutputExcel, WithAgeGroups, (*SchoolsList)[i], CostRegW, CostSoloW, CostFigureW, CostPremW, CostChampW, CostEuroW, CostUnlimW, CostRegNW, CostSoloNW, CostFigureNW, CostPremNW, CostChampNW, CostEuroNW, CostUnlimNW, SchoolsWIDA, false);
      OutputExcel->DeleteColumn(3);
    }
  }

  delete OutputExcel;
  Warning->Hide();
  return true;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TNumbersForm::ButtonCloseClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TNumbersForm::ButtonCreateNumbersClick(TObject *Sender)
{
  if (!SaveDialogNumbers->Execute()) return;
  ExportNumbers(SaveDialogNumbers->FileName, PanelWarning, EditAdditionalSolo->Text.ToIntDef(0), EditAdditionalTeam->Text.ToIntDef(0));
  Application->MessageBox("Экспорт номерков завершен. Проверьте содержимое файла.", "Экспорт номерков", MB_OK);
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TNumbersForm::ButtonCreateEmptyResultsClick(TObject *Sender)
{
  if (!SaveDialogEmptyResults->Execute()) return;
  if (ExportResults(SaveDialogEmptyResults->FileName, PanelWarning, false, false))
    Application->MessageBox("Создание файла пустой формы результатов завершено.\nТеперь каждый лист этой формы следует вставить в файл с макросами (например, XLSM-файл с одного из прошлых фешей).", "Экспорт пустой формы результатов", MB_OK);
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TNumbersForm::ButtonCreateListClick(TObject *Sender)
{
  if (!SaveDialogList->Execute()) return;
  if (ExportParticipants(SaveDialogList->FileName, PanelWarning))
    Application->MessageBox("Экспорт списка участников завершен.\nТеперь его можно вставить в Word или другой текстовый процессор,\nпроставить размер табуляций, сделать колонки и прочее необходимое оформление.", "Экспорт списка участников для буклета", MB_OK);
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TNumbersForm::ButtonCreateScheduleClick(TObject *Sender)
{
  if (!SaveDialogSchedule->Execute()) return;
  if (ExportSchedule(SaveDialogSchedule->FileName, PanelWarning))
    Application->MessageBox("Создание проекта расписания завершено.\nТеперь следует его отредактировать, чтобы получить готовое расписание.", "Экспорт проекта расписания", MB_OK);
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TNumbersForm::ButtonCreateBPIOClick(TObject *Sender)
{
  if (!SaveDialogBPIO->Execute()) return;
  if (ExportBPIOGeneric(SaveDialogBPIO->FileName, PanelWarning, false, ListWIDA->Items, false /* CheckBoxSortSchools->Checked : use this if you want this to react to the check box */))
    Application->MessageBox("Создание списка завершено.", "Экспорт BPIO-списка", MB_OK);
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TNumbersForm::ButtonCreateSchoolClick(TObject *Sender)
{
  if (!SaveDialogSchools->Execute()) return;

  TStringList* SchoolsList = new TStringList();
  for (int i = 0; i < Database->TotalDancers(); ++i)
  {
    TDancer *Dancer = Database->GetDancerByIndex(i);
    if (SchoolsList->IndexOf(Dancer->School) < 0) SchoolsList->Add(Dancer->School);
  }
  SchoolsList->Sort();
  if (ExportBPIOGeneric(SaveDialogSchools->FileName, PanelWarning, true, ListWIDA->Items, CheckBoxSortSchools->Checked, SchoolsList, SpinCostReg->Value, SpinCostSolo->Value, SpinCostFigure->Value, SpinCostPremier->Value, SpinCostChamp->Value, SpinCostEuro->Value, SpinCostUnlim->Value, SpinCostRegNW->Value, SpinCostSoloNW->Value, SpinCostFigureNW->Value, SpinCostPremierNW->Value, SpinCostChampNW->Value, SpinCostEuroNW->Value, SpinCostUnlimNW->Value))
    Application->MessageBox("Создание списка завершено.", "Экспорт списка по школам", MB_OK);
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TNumbersForm::ButtonCreateStageListsClick(TObject *Sender)
{
  if (!SaveDialogStageLists->Execute()) return;
  if (ExportStageLists(SaveDialogStageLists->FileName, PanelWarning))
    Application->MessageBox("Создание стейдж-листов завершено.", "Экспорт стейдж-листов", MB_OK);
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TNumbersForm::FormShow(TObject *Sender)
{
  // Fill school lists
  for (int i = 0; i < Database->TotalDancers(); ++i)
  {
    TDancer *Dancer = Database->GetDancerByIndex(i);
    if(ListWIDA->Items->IndexOf(Dancer->School) < 0 && ListNonWIDA->Items->IndexOf(Dancer->School) < 0)
    {
      ((Dancer->School.SubString(1, 10) == "(Non-WIDA)") ? ListNonWIDA : ListWIDA)->Items->Add(Dancer->School);
    }
  }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TNumbersForm::ButtonFromWIDAClick(TObject *Sender)
{
  if (ListWIDA->ItemIndex >= 0 && ListWIDA->ItemIndex < ListWIDA->Count)
  {
    AnsiString School = ListWIDA->Items->Strings[ListWIDA->ItemIndex];
    ListNonWIDA->Items->Add(School);
    ListWIDA->DeleteSelected();
  }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TNumbersForm::ButtonToWIDAClick(TObject *Sender)
{
  if (ListNonWIDA->ItemIndex >= 0 && ListNonWIDA->ItemIndex < ListNonWIDA->Count)
  {
    AnsiString School = ListNonWIDA->Items->Strings[ListNonWIDA->ItemIndex];
    ListWIDA->Items->Add(School);
    ListNonWIDA->DeleteSelected();
  }
}
//---------------------------------------------------------------------------


