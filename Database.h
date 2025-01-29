//---------------------------------------------------------------------------
#ifndef DatabaseH
#define DatabaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <stdio.h>
//---------------------------------------------------------------------------
enum ListType // RadioGroup IDs
{
  ltList = 0,
  ltSolo = 1,
  ltGroup = 2
};
//---------------------------------------------------------------------------
#define TotalDances    38 // Total number of dances in enum Dances
#define TotalDancesExt 46 // The same but including special dance groups for Group form
enum Dances
{
  nil = -1,

  // Solo
  Jump23 = 0,              // No qualification
  ModernSet,               // No qualification
  TrebleReel,              // No qualification
  BeginnerReel,
  BeginnerLightJig,
  BeginnerSingleJig,
  BeginnerSlipJig,
  BeginnerTrebleJig,
  BeginnerHornpipe,
  BeginnerTradSet,
  BeginnerPremiership,     // No qualification
  PrimaryReel,
  PrimaryLightJig,
  PrimarySingleJig,
  PrimarySlipJig,
  PrimaryTrebleJig,
  PrimaryHornpipe,
  PrimaryTradSet,
  PrimaryPremiership,      // No qualification
  IntermedReel,
  IntermedLightJig,
  IntermedSingleJig,
  IntermedSlipJig,
  IntermedTrebleJig,
  IntermedHornpipe,
  IntermedTradSet,
  IntermedPremiership,     // No qualification
  OpenReel,                // No qualification
  OpenSlipJig,             // No qualification
  OpenTrebleJig,           // No qualification
  OpenHornpipe,            // No qualification
  OpenTradSet,             // No qualification
  PreChampionship,         // No qualification
  Championship,            // No qualification

  // Group
  Group2Hand,              // No qualification
  Group3Hand,              // No qualification
  Group4Hand,              // No qualification
  GroupCeili,              // No qualification

  // Special
  SpecialBeginnerSoft,
  SpecialBeginnerHard,
  SpecialPrimarySoft,
  SpecialPrimaryHard,
  SpecialIntermedSoft,
  SpecialIntermedHard,
  SpecialOpenSoft,
  SpecialOpenHard
};
//---------------------------------------------------------------------------
#define TotalGroups 16 // Total number of possible age groups
//---------------------------------------------------------------------------
#define TotalRounds 20 // Total number of possible point records for one dance
//---------------------------------------------------------------------------
bool isGroupDance(enum Dances Dance);
int GetGroupAge(AnsiString s);
char GetGroupType(AnsiString s);
AnsiString GroupToString(AnsiString s);
int TeamStringLength(AnsiString TeamString);
AnsiString TeamStringGet(AnsiString TeamString, int index);
AnsiString TeamStringAdd(AnsiString TeamString, AnsiString Content);
AnsiString TeamStringDelete(AnsiString TeamString, AnsiString Content);
AnsiString PointsToStr(int Points);
int PointsToInt(AnsiString String);
//---------------------------------------------------------------------------
bool ExportResults(AnsiString FileName, TPanel *Warning, bool SaveResults);
//---------------------------------------------------------------------------
class TDancer
{
  public:
    TDancer();

    int UID;

    bool isGroup;
    int Number;         // Different numbering for solo and group teams
    AnsiString Name;
    AnsiString School;
    int Age;

    bool       Dances[TotalDances];
    int        RawPoints[TotalDances][TotalRounds];
    int        CalcPoints[TotalDances];
    int        Places[TotalDances];
    bool       Qualified[TotalDances];
    AnsiString AgeGroup[TotalDances];
    AnsiString Comment[TotalDances];
};
//---------------------------------------------------------------------------
class TFeisDatabase
{
  private:
    class TFile
    {
      private:
        FILE *Handle;
      public:
        bool Error;

        TFile(AnsiString FileName, AnsiString mode);
        ~TFile();

        bool ReadBool();
        int ReadInteger(int Min, int Max);
        AnsiString ReadAnsiString();
        void WriteBool(bool Data);
        void WriteInteger(int Data);
        void WriteAnsiString(AnsiString Data);
    };

    TList *Dancers;

    int NewUID();

  public:
    TFeisDatabase();
    int TotalDancers();
    bool ConsistencyCheck(TStrings *ErrorMessages);
    TDancer* GetDancerByIndex(int index);
    void SwapDancersByIndex(int index1, int index2);
    TDancer* GetDancerByNumber(AnsiString Number);
    TDancer* GetDancerByPartialName(AnsiString PartialName, bool FromStart);
    TDancer* AddNewDancer();
    void GroupsFromDatabase(AnsiString Array[TotalDances][TotalGroups]);
    void RemoveAll(bool isGroup);
    bool DeleteByUID(int UID);
    bool LoadFromFile(AnsiString FileName);
    bool CreateFile(AnsiString FileName);
    bool SaveToFile(AnsiString FileName);
    ~TFeisDatabase();
};
//---------------------------------------------------------------------------
#endif

