//---------------------------------------------------------------------------
#ifndef DictDancesH
#define DictDancesH

#define DICTSIZE 1024
//---------------------------------------------------------------------------
class TDictDances
{
  int LastItem;
  AnsiString Schools[DICTSIZE];
  int Dances[DICTSIZE];
public:
  TDictDances();
  void Add(AnsiString School, int Dance); // [TODO]: check for overflow
  bool Get(AnsiString &School, int &Dance);
  ~TDictDances();
};
#endif
