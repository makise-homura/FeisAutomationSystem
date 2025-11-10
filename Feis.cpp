//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("StartupUnit.cpp", StartupForm);
USEFORM("ImportUnit.cpp", ImportForm);
USEFORM("GroupUnit.cpp", GroupForm);
USEFORM("ResultsUnit.cpp", FeisEnterForm);
USEFORM("NumbersUnit.cpp", NumbersForm);
USEFORM("ManageTeamUnit.cpp", ManageTeamForm);
USEFORM("LogUnit.cpp", LogForm);
USEFORM("DeclarationUnit.cpp", DeclarationForm);
USEFORM("ProtocolSelectUnit.cpp", ProtocolSelectForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Feis Automation System";
     Application->CreateForm(__classid(TStartupForm), &StartupForm);
     Application->CreateForm(__classid(TImportForm), &ImportForm);
     Application->CreateForm(__classid(TGroupForm), &GroupForm);
     Application->CreateForm(__classid(TFeisEnterForm), &FeisEnterForm);
     Application->CreateForm(__classid(TNumbersForm), &NumbersForm);
     Application->CreateForm(__classid(TManageTeamForm), &ManageTeamForm);
     Application->CreateForm(__classid(TLogForm), &LogForm);
     Application->CreateForm(__classid(TDeclarationForm), &DeclarationForm);
     Application->CreateForm(__classid(TProtocolSelectForm), &ProtocolSelectForm);
     Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
