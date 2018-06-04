//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "stdio.h"
#include "Unit2.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TForm2::BT_outputClick(TObject *Sender)
{
FILE* f_hex;

if (SaveDialog1->Execute())
   { f_hex=fopen(SaveDialog1->FileName.c_str(),"wt");
      for (int i=0;i<Memo1->Lines->Count;i++)
        fprintf(f_hex,"%s\n",Memo1->Lines->Strings[i]);
     fclose(f_hex);
   }
}
//---------------------------------------------------------------------------
