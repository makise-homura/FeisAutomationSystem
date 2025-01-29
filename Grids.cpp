//---------------------------------------------------------------------------
#include "Grids.h"
//---------------------------------------------------------------------------
int NewLineToTable(TStringGrid *Grid)
{
  int Row;
  if (IsTableEmpty(Grid)) Row = 1;
  else
  {
    Row = Grid->RowCount;
    ++Grid->RowCount;
  }
  Grid->Rows[Row]->Clear();
  return Row;
}
//---------------------------------------------------------------------------
void ClearTable(TStringGrid *Table, TList *UIDs)
{
  Table->RowCount = 2;
  Table->Rows[1]->Clear();
  for (int i = 0; i < UIDs->Count; ++i) delete UIDs->Items[i];
  UIDs->Clear();
}
//---------------------------------------------------------------------------
bool IsTableEmpty(TStringGrid *Grid)
{
  if (Grid->RowCount != 2) return false;
  for (int i = 0; i < Grid->ColCount; ++i)
    if (Grid->Cells[i][1] != "") return false;
  return true;
}
//---------------------------------------------------------------------------

