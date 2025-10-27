//---------------------------------------------------------------------------

#include <vcl.h>
#include <ComObj.hpp>
#pragma hdrstop

#include "Excel.h"
//---------------------------------------------------------------------------
TExcel::TExcel(AnsiString FileName, enum FileType Type)
{
  var_Excel = CreateOleObject("Excel.Application");
  var_Excel.OlePropertySet("Visible", false);
  var_Excel.OlePropertyGet("Application").OlePropertySet("DisplayAlerts", false);
  var_Excel.OlePropertyGet("Application").OlePropertyGet("Workbooks").OleProcedure("Close");

  switch (Type)
  {
    case xlCreate:
      var_Excel.OlePropertyGet("Application").OlePropertyGet("Workbooks").OleProcedure("Add");
      var_Excel.OlePropertyGet("Application").OlePropertySet("DisplayAlerts", true);
      var_Excel.OlePropertyGet("Application").OlePropertyGet("ActiveWorkbook").OleProcedure("SaveAs", FileName.c_str());
      var_Excel.OlePropertyGet("Application").OlePropertySet("DisplayAlerts", false);
      ReadOnly = false;
    break;
    case xlOpen:
      var_Excel.OlePropertyGet("Application").OlePropertyGet("Workbooks").OleProcedure("Open", FileName.c_str(), 0, true);
      ReadOnly = true;
    break;
  }
  var_Sheet = var_Excel.OlePropertyGet("ActiveSheet");
}
//---------------------------------------------------------------------------
TExcel::~TExcel()
{
  if (!ReadOnly)
  {
    var_Excel.OlePropertyGet("Application").OlePropertySet("DisplayAlerts", true);
    var_Excel.OlePropertyGet("Application").OlePropertyGet("ActiveWorkbook").OleProcedure("Save");
    var_Excel.OlePropertyGet("Application").OlePropertySet("DisplayAlerts", false);
  }
  var_Excel.OlePropertyGet("Application").OlePropertyGet("ActiveWorkbook").OleProcedure("Close", false);
  var_Excel.OlePropertyGet("Application").OleProcedure("Quit");
}
//---------------------------------------------------------------------------
void TExcel::GetRow(AnsiString *Strings, int Row, int Length)
{
  for (int i = 0; i < Length; ++i)
    Strings[i] = GetCell(Row, i);
}
//---------------------------------------------------------------------------
void TExcel::DeleteColumn(int Column)
{
  AnsiString Range = (char)('A' + Column);
  var_Cell = var_Sheet.OlePropertyGet("Range", (Range + ":" + Range).c_str());
  var_Cell.OleProcedure("Delete");
}
//---------------------------------------------------------------------------
void TExcel::SelectRange(int Column, int Row, int Width, int Height)
{
  // Column + Width should be less than 26 !

  AnsiString Range = "";
  Range += (char)('A' + Column);
  Range += (Row + 1);
  Range += ':';
  Range += (char)('A' + Column + Width - 1);
  Range += (Row + Height);

  var_Cell = var_Sheet.OlePropertyGet("Range", Range.c_str());
  var_Cell.OleProcedure("Select");
}
//---------------------------------------------------------------------------
void TExcel::PutCell(int Row, int Column, AnsiString Data)
{
  SelectCell(Row, Column);
  SetValue(Data);
}
//---------------------------------------------------------------------------
void TExcel::SelectCell(int Row, int Column)
{
  var_Cell = var_Sheet.OlePropertyGet("Cells")
                      .OlePropertyGet("Item", Row + 1, Column + 1);
}
//---------------------------------------------------------------------------
void TExcel::Sort(int Column, int Row, int Width, int Height, int ColNum, enum SortOrders Order)
{
  SelectRange(Column, Row, Width, Height);

  Variant var_Col = var_Sheet.OlePropertyGet("Cells")
                             .OlePropertyGet("Item", Row + 1, Column + 1 + ColNum);

  var_Cell.OleProcedure("Sort", var_Col, Order);
}
//---------------------------------------------------------------------------
AnsiString TExcel::GetCell(int Row, int Column)
{
  SelectCell(Row, Column);
  return GetValue();
}
//---------------------------------------------------------------------------
void TExcel::SetValue(AnsiString Data)
{
  var_Cell.OlePropertySet("Value", Data.c_str());
}
//---------------------------------------------------------------------------
AnsiString TExcel::GetValue()
{
  return var_Cell.OlePropertyGet("Value");
}
//---------------------------------------------------------------------------
void TExcel::SetAlignment(enum AlignmentTypes Horz, enum AlignmentTypes Vert)
{
  var_Cell.OlePropertySet("HorizontalAlignment", Horz);
  var_Cell.OlePropertySet("VerticalAlignment", Vert);
}
//---------------------------------------------------------------------------
void TExcel::SetFontFace(AnsiString Font)
{
  var_Cell.OlePropertyGet("Font").OlePropertySet("Name",Font.c_str());
}
//---------------------------------------------------------------------------
void TExcel::SetFontBold()
{
  var_Cell.OlePropertyGet("Font").OlePropertySet("Bold",true);
}
//---------------------------------------------------------------------------
void TExcel::SetFontSize(int Size)
{
  var_Cell.OlePropertyGet("Font").OlePropertySet("Size",Size);
}
//---------------------------------------------------------------------------
void TExcel::PutPicture(AnsiString FileName, int XPix, int YPix, int WidthPix, int HeightPix)
{
  var_Sheet.OlePropertyGet("Shapes")
           .OleProcedure  ("AddPicture", FileName.c_str(), true, true, XPix, YPix, WidthPix, HeightPix);
}
//---------------------------------------------------------------------------
int TExcel::GetTop()
{
  return var_Cell.OlePropertyGet("Top");
}
//---------------------------------------------------------------------------
int TExcel::GetLeft()
{
  return var_Cell.OlePropertyGet("Left");
}
//---------------------------------------------------------------------------
int TExcel::GetWidth()
{
  return var_Cell.OlePropertyGet("Width");
}
//---------------------------------------------------------------------------
int TExcel::GetHeight()
{
  return var_Cell.OlePropertyGet("Height");
}
//---------------------------------------------------------------------------
void TExcel::SetBorder(enum EdgeTypes Type, enum LineTypes Line, enum LineWeights Weight)
{
  var_Cell.OlePropertyGet("Borders", Type)
          .OlePropertySet("LineStyle", Line);
  var_Cell.OlePropertyGet("Borders", Type)
          .OlePropertySet("Weight", Weight);
}
//---------------------------------------------------------------------------
void TExcel::Join()
{
  var_Cell.OleProcedure("Merge");
}
//---------------------------------------------------------------------------
void TExcel::SelectSheet(AnsiString Name)
{
  var_Sheet = var_Excel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Worksheets",Name.c_str());
  var_Sheet.OleProcedure("Activate");
}
//---------------------------------------------------------------------------
void TExcel::CreateSheet(AnsiString Name, bool ClearAllDatabase)
{
  if (ClearAllDatabase)
  {
    while(var_Excel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Worksheets").OlePropertyGet("Count") > 1)
      var_Excel.OlePropertyGet("ActiveSheet").OleProcedure("Delete");
  }
  else
    var_Excel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Worksheets").OleProcedure("Add");

  var_Sheet = var_Excel.OlePropertyGet("ActiveSheet");
  var_Sheet.OlePropertySet("Name", Name.SubString(0,31).c_str());

  var_Sheet.OleProcedure("Activate");
}
//---------------------------------------------------------------------------
void TExcel::DeleteSheet(bool *ClearAllDatabase)
{
  if(var_Excel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Worksheets").OlePropertyGet("Count") > 1)
  {
    var_Sheet.OleProcedure("Delete");
    var_Sheet = var_Excel.OlePropertyGet("ActiveSheet");
    *ClearAllDatabase = false;
  }
  else
  {
    var_Cell = var_Sheet.OlePropertyGet("Cells");
    var_Cell.OleProcedure("Select");
    var_Cell.OleProcedure("Clear");

    var_Sheet.OlePropertySet("Name", "-");
    *ClearAllDatabase = true;
  }
}
//---------------------------------------------------------------------------
void TExcel::SetFontColor(TColor Color)
{
  var_Cell.OlePropertyGet("Font").OlePropertySet("Color", Color);
}
//---------------------------------------------------------------------------
void TExcel::SetBkColor(TColor Color)
{
  var_Cell.OlePropertyGet("Interior").OlePropertySet("Color", Color);
}
//---------------------------------------------------------------------------
TColor TExcel::GetBkColor()
{
  int Color = var_Cell.OlePropertyGet("Interior").OlePropertyGet("Color");
  return (TColor) Color;
}
//---------------------------------------------------------------------------
void TExcel::SetColWidth(int Column, int Width) // -1 to set for active cell's column
{
  if (Column >= 0) SelectCell(0, Column);
  var_Cell.OlePropertySet("ColumnWidth", Width);
}
//---------------------------------------------------------------------------
void TExcel::SetRowHeight(int Row, int Height) // -1 to set for active cell's row
{
  if (Row >= 0) SelectCell(Row, 0);
  var_Cell.OlePropertySet("RowHeight", Height);
}
//---------------------------------------------------------------------------
int TExcel::CentimetersToPoints(int Centimeters)
{
  return var_Excel.OlePropertyGet("Application").OleFunction("CentimetersToPoints", Centimeters);
}
//---------------------------------------------------------------------------
bool TExcel::SetPageSetup(enum PaperSizes PaperSize, enum OrientationTypes Orientation, int MarginLeft, int MarginTop, int MarginRight, int MarginBottom)
{
  try
  {
    var_Sheet.OlePropertyGet("PageSetup").OlePropertySet("PaperSize", PaperSize);
  }
  catch (...)
  {
    return false;
  }
  var_Sheet.OlePropertyGet("PageSetup").OlePropertySet("Orientation",  Orientation);
  var_Sheet.OlePropertyGet("PageSetup").OlePropertySet("LeftMargin",   CentimetersToPoints(MarginLeft));
  var_Sheet.OlePropertyGet("PageSetup").OlePropertySet("TopMargin",    CentimetersToPoints(MarginTop));
  var_Sheet.OlePropertyGet("PageSetup").OlePropertySet("RightMargin",  CentimetersToPoints(MarginRight));
  var_Sheet.OlePropertyGet("PageSetup").OlePropertySet("BottomMargin", CentimetersToPoints(MarginBottom));
  return true;
}
//---------------------------------------------------------------------------

