//---------------------------------------------------------------------------
#ifndef ExcelH
#define ExcelH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
enum FileType         {xlOpen, xlCreate};
enum AlignmentTypes   {xlTop = -4160, xlBottom = -4107, xlLeft = -4131, xlCenter = -4108, xlRight = -4152};
enum EdgeTypes        {xlEdgeTop = 8, xlEdgeBottom = 9, xlEdgeLeft =7, xlEdgeRight = 10, xlInsideHorizontal = 12, xlInsideVertical = 11};
enum LineTypes        {xlContinuous = 1};
enum LineWeights      {xlHairline = 1, xlMedium = -4138, xlThick = 4, xlThin = 2};
enum OrientationTypes {xlLandscape = 2, xlPortrait = 1};
enum PaperSizes       {xlPaperA6 = 70, xlPaperA4 = 9};
enum SortOrders       {xlAscending = 1, xlDescending = 2};
const TColor clGold       = 0x00D7FF;
const TColor clPaleRed    = 0x9999FF;
const TColor clPaleGreen  = 0xCCFFCC;
const TColor clPaleBlue   = 0xFFCCCC;
const TColor clPaleYellow = 0x99FFFF;
//---------------------------------------------------------------------------
class TExcel
{
  private:
    bool ReadOnly;
    Variant var_Excel, var_Sheet, var_Cell;

  public:
    void SelectCell(int Row, int Column);
    void SelectRange(int Column, int Row, int Width, int Height);
    void Join();
    void SetValue(AnsiString Data);
    void SetAlignment(enum AlignmentTypes Horz, enum AlignmentTypes Vert);
    void SetFontFace(AnsiString Font);
    void SetFontBold();
    int  GetTop();
    int  GetLeft();
    int  GetWidth();
    int  GetHeight();
    TColor GetBkColor();
    void CreateSheet(AnsiString Name, bool ClearAllDatabase);
    void DeleteSheet(bool *ClearAllDatabase);
    void SetFontSize(int Size);
    bool SelectSheet(AnsiString Name);
    void SetFontColor(TColor Color);
    void SetBkColor(TColor Color);
    void PutPicture(AnsiString FileName, int XPix, int YPix, int WidthPix, int HeightPix);
    void SetBorder(enum EdgeTypes Type, enum LineTypes Line, enum LineWeights Weight);
    AnsiString GetCell(int Row, int Column);
    void SetColWidth(int Column, int Width);
    void SetRowHeight(int Column, int Height);
    void Sort(int Column, int Row, int Width, int Height, int ColNum, enum SortOrders Order);
    bool SetPageSetup(enum PaperSizes PaperSize, enum OrientationTypes Orientation, int MarginLeft, int MarginTop, int MarginRight, int MarginBottom);
    AnsiString GetValue();
    int CentimetersToPoints(int Centimeters);
    void PutCell(int Row, int Column, AnsiString Data);
    void GetRow(AnsiString *Strings, int Row, int Length);
    void DeleteColumn(int Column);

    TExcel(AnsiString FileName, enum FileType Type);
    ~TExcel();
};
//---------------------------------------------------------------------------
#endif
