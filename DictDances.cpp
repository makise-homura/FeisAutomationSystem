//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DictDances.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TDictDances::TDictDances()
{
  LastItem = 0;
}

void TDictDances::Add(AnsiString School, int Dance)
{
  for (int i = 0; i < LastItem; ++i)
  {
    if (Schools[i] == School)
    {
      Dances[i] += Dance;
      return;
    }
  }
  Schools[LastItem] = School;
  Dances[LastItem]  = Dance;
  ++LastItem;
}

bool TDictDances::Get(AnsiString &School, int &Dance)
{
  if (LastItem == 0) return false;
  --LastItem;
  School = Schools[LastItem];
  Dance  = Dances[LastItem];
  return true;
}

TDictDances::~TDictDances()
{
}

