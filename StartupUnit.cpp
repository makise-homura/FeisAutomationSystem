//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "StartupUnit.h"
#include "ImportUnit.h"
#include "GroupUnit.h"
#include "ResultsUnit.h"
#include "NumbersUnit.h"
#include "Database.h"
#include "Excel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TStartupForm *StartupForm;
TFeisDatabase *Database;
//---------------------------------------------------------------------------
__fastcall TStartupForm::TStartupForm(TComponent* Owner) : TForm(Owner)
{
  Database = new TFeisDatabase;
  FeisOpened = false;
}
//---------------------------------------------------------------------------
__fastcall TStartupForm::~TStartupForm()
{
  delete Database;
}
//---------------------------------------------------------------------------
bool TStartupForm::SaveDatabase()
{
  if (!FeisOpened) return true;
  return Database->SaveToFile(Filename);
}
//---------------------------------------------------------------------------
void TStartupForm::DatabaseInit(enum dbops Operation)
{
  AnsiString errmsg;
  bool InitOk;

  // Forget old database
  FileField->Text = "(файл не открыт)";
  FeisOpened = false;
  ImportButton->Enabled  = false;
  FilesButton->Enabled   = false;
  GroupButton->Enabled   = false;
  ResultsButton->Enabled = false;
  ExportButton->Enabled  = false;
  SaveButton->Enabled    = false;
  LockButton->Enabled    = false;


  if(!SaveDatabase()) // If feis is not opened, then it will be just skipped
  {
    Application->MessageBox("Невозможно сохранить файл феша!","Ошибка",MB_OK);
    return;
  }

  if (Operation == doLoad)
  {
    if (!OpenFeisDialog->Execute()) return;
    Filename = OpenFeisDialog->FileName;
    InitOk = Database->LoadFromFile(Filename);
    errmsg = "Ошибка загрузки файла феша";
  }
  else
  {
    if (!NewFeisDialog->Execute()) return;
    Filename = NewFeisDialog->FileName;
    InitOk = Database->CreateFile(Filename);
    errmsg = "Ошибка создания нового файла феша";
  }

  if(!InitOk)
  {
    Application->MessageBox(errmsg.c_str(),"Ошибка",MB_OK);
    return;
  }

  // All ok, proceed to unlock first button
  FileField->Text = Filename;
  FeisOpened = true;
  ImportButton->Enabled  = true;
  FilesButton->Enabled   = true;
  GroupButton->Enabled   = true;
  ResultsButton->Enabled = true;
  ExportButton->Enabled  = true;
  LockButton->Enabled    = true;
  SaveButton->Enabled    = true;
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TStartupForm::QuitButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TStartupForm::OpenFeisButtonClick(TObject *Sender)
{
  DatabaseInit(doLoad);
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TStartupForm::NewFeisButtonClick(TObject *Sender)
{
  DatabaseInit(doNew);
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TStartupForm::ImportButtonClick(TObject *Sender)
{
  ImportForm->ShowModal();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TStartupForm::GroupButtonClick(TObject *Sender)
{
  GroupForm->ShowModal();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TStartupForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  if(!SaveDatabase()) // If feis is not opened, then it will be just skipped
  {
    Application->MessageBox("Невозможно сохранить файл феша!","Ошибка",MB_OK);
    return;
  }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TStartupForm::ResultsButtonClick(TObject *Sender)
{
  FeisEnterForm->ShowModal();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TStartupForm::ExportButtonClick(TObject *Sender)
{
  if (!ExportDialogXLS->Execute()) return;
  if (ExportResults(ExportDialogXLS->FileName, Warning, true, UnnormalizedCheckBox->Checked, AlterSchoolsCheckBox->Checked))
    Application->MessageBox("Экспорт результатов в Excel завершен.", "Экспорт файла для WIDA", MB_OK);
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TStartupForm::SaveButtonClick(TObject *Sender)
{
  if(!SaveDatabase()) // If feis is not opened, then it will be just skipped
  {
    Application->MessageBox("Невозможно сохранить файл феша!","Ошибка",MB_OK);
    return;
  }
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TStartupForm::FilesButtonClick(TObject *Sender)
{
  NumbersForm->ShowModal();
}
//---------------------------------------------------------------------------
#pragma argsused
void __fastcall TStartupForm::LockButtonClick(TObject *Sender)
{
  NewFeisButton->Enabled  = false;
  OpenFeisButton->Enabled = false;
  ImportButton->Enabled   = false;
  GroupButton->Enabled    = false;
  FilesButton->Enabled    = false;
  ExportButton->Enabled   = false;
  LockButton->Enabled     = false;
  ActiveControl           = ResultsButton;
}
//---------------------------------------------------------------------------


