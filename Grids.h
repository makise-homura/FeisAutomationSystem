//---------------------------------------------------------------------------
#ifndef GridsH
#define GridsH
//---------------------------------------------------------------------------
#include <Grids.hpp>
//---------------------------------------------------------------------------
int NewLineToTable(TStringGrid *Grid);
void ClearTable(TStringGrid *Table, TList *UIDs);
bool IsTableEmpty(TStringGrid *Grid);
void SortGrid(TStringGrid *Grid, int SortColumn);
//---------------------------------------------------------------------------
#endif

 