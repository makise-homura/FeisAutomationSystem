//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Grids.h"
#include "Database.h"
#include "ManageTeamUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TManageTeamForm *ManageTeamForm;
extern TFeisDatabase *Database;
//---------------------------------------------------------------------------
__fastcall TManageTeamForm::TManageTeamForm(TComponent* Owner)
  : TForm(Owner)
{
  SourceGrid->Cells[0][0] = "Номер";
  SourceGrid->Cells[1][0] = "Участник";
  SourceGrid->ColWidths[0] = 40;
  SourceGrid->ColWidths[1] = 210;

  TargetGrid->Cells[0][0] = "Номер";
  TargetGrid->Cells[1][0] = "Участник";
  TargetGrid->ColWidths[0] = 40;
  TargetGrid->ColWidths[1] = 210;
}
//---------------------------------------------------------------------------
void TManageTeamForm::Renew()
{
  // Prepare grids
  SourceGrid->RowCount = 2;
  SourceGrid->Rows[1]->Clear();
  TargetGrid->RowCount = 2;
  TargetGrid->Rows[1]->Clear();

  // Fill target grid
  for(int i = 0; i < TeamStringLength(TeamContents); ++i)
  {
    int Row = NewLineToTable(TargetGrid);
    AnsiString DancerName = TeamStringGet(TeamContents, i);
    TargetGrid->Cells[1][Row] = DancerName;

    bool found = false;
    TDancer *Dancer;
    for(int j = 0; j < Database->TotalDancers(); ++j)
    {
      Dancer = Database->GetDancerByIndex(j);
      if (Dancer->isGroup) continue;
      if ((Dancer->Name == DancerName) && (Dancer->School == School)) { found = true; break; }
    }
    TargetGrid->Cells[0][Row] = (found ? (AnsiString)Dancer->Number : (AnsiString)"?");
  }

  // Fill source grid (without dancers in target grid)
  for(int j = 0; j < Database->TotalDancers(); ++j)
  {
    TDancer *Dancer = Database->GetDancerByIndex(j);
    if (Dancer->isGroup) continue;
    if (Dancer->School != School) continue;

    bool found = false;
    if(!IsTableEmpty(TargetGrid))
      for(int i = 1; i < TargetGrid->RowCount; ++i)
        if (TargetGrid->Cells[0][i] == Dancer->Number) { found = true; break; }

    if (!found)
    {
      int Row = NewLineToTable(SourceGrid);
      SourceGrid->Cells[0][Row] = Dancer->Number;
      SourceGrid->Cells[1][Row] = Dancer->Name;
    }
  }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TManageTeamForm::ButtonAddClick(TObject *Sender)
{
  if (IsTableEmpty(SourceGrid)) return;
  TeamContents = TeamStringAdd(TeamContents, SourceGrid->Cells[1][SourceGrid->Row]);
  Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TManageTeamForm::ButtonRemoveClick(TObject *Sender)
{
  if (IsTableEmpty(TargetGrid)) return;
  TeamContents = TeamStringDelete(TeamContents, TargetGrid->Cells[1][TargetGrid->Row]);
  Renew();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TManageTeamForm::ButtonOKClick(TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TManageTeamForm::FormShow(TObject *Sender)
{
  LabelSchool->Caption = "Танцоры школы " + School;
  Renew();
}
//---------------------------------------------------------------------------
