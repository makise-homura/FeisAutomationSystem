//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddRegUnit.h"
#include "ImportUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddRegForm *AddRegForm;
//---------------------------------------------------------------------------
__fastcall TAddRegForm::TAddRegForm(TComponent* Owner)
  : TForm(Owner)
{
  DancersGrid->Cells[0][0] = "Номер";
  DancersGrid->Cells[1][0] = "Участник";
  DancersGrid->Cells[2][0] = "Школа";
  DancersGrid->Cells[3][0] = "Возраст";
  DancersGrid->ColWidths[0] = 60;
  DancersGrid->ColWidths[1] = 200;
  DancersGrid->ColWidths[2] = 400;
  DancersGrid->ColWidths[3] = 60;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TAddRegForm::FormShow(TObject *Sender)
{
  int i, j, GridRow = 1;
  DancersGrid->RowCount = 2;
  Selected = false;

  if((ImportForm->ListGrid->RowCount    == 2 ) &&
     (ImportForm->ListGrid->Cells[0][1] == "") &&
     (ImportForm->ListGrid->Cells[1][1] == "") &&
     (ImportForm->ListGrid->Cells[2][1] == "") &&
     (ImportForm->ListGrid->Cells[3][1] == "")) // No dancers list specified
  {
    Application->MessageBox("Список танцоров пуст", "Ошибка", MB_OK);
    ModalResult = mrCancel;
    return;
  }


  for(i = 1; i < ImportForm->ListGrid->RowCount; ++i)
  {
    bool detected = true;
    for(j = 1; j < ImportForm->SoloGrid->RowCount; ++j)
    {
      if((ImportForm->ListGrid->Cells[0][i] == ImportForm->SoloGrid->Cells[0][j]) &&
         (ImportForm->ListGrid->Cells[1][i] == ImportForm->SoloGrid->Cells[1][j]) &&
         (ImportForm->ListGrid->Cells[2][i] == ImportForm->SoloGrid->Cells[2][j]) &&
         (ImportForm->ListGrid->Cells[3][i] == ImportForm->SoloGrid->Cells[3][j]))
      {
        detected = false;
        break;
      }
    }

    if (detected)
    {
      if (GridRow > 1) ++DancersGrid->RowCount;

      DancersGrid->Cells[0][GridRow]  = ImportForm->ListGrid->Cells[0][i];
      DancersGrid->Cells[1][GridRow]  = ImportForm->ListGrid->Cells[1][i];
      DancersGrid->Cells[2][GridRow]  = ImportForm->ListGrid->Cells[2][i];
      DancersGrid->Cells[3][GridRow]  = ImportForm->ListGrid->Cells[3][i];
      ++GridRow;
    }
  }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TAddRegForm::CancelButtonClick(TObject *Sender)
{
  Selected = false;
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TAddRegForm::AddButtonClick(TObject *Sender)
{
  Selected = true;
  Number = DancersGrid->Cells[0][DancersGrid->Row];
  Name   = DancersGrid->Cells[1][DancersGrid->Row];
  School = DancersGrid->Cells[2][DancersGrid->Row];
  Age    = DancersGrid->Cells[3][DancersGrid->Row];
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
