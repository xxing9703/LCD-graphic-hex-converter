//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include   "clipbrd.hpp"
#include "stdio.h"
#include "math.h"
#include <stack>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"

//#define
#define xor 0
#define copy 1
#define undomax 10


TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{ ZOOM=8;
  LCD_W=128;
  LCD_H=64;
  penmode=copy;
  ComboBox1->ItemIndex=1;
  gridon=false;
  //undomax=10;
  undosize=0;undosize_pt=0;SB_undo->Enabled=false;//SB_redo->Enabled=false;

 sflag=2; sx1=0; sy1=0;sx2=LCD_W-1;sy2=LCD_H-1; stepsize=1; hascopy=0;
      buffer_sx1[0]=sx1;
      buffer_sx2[0]=sx2;
      buffer_sy1[0]=sy1;
      buffer_sy2[0]=sy2;
 CL1->Color=0x00FFFFFF-0x00700000;
 CL_SELECT=0x00FFFFFF-CL1->Color;
 pBitmap = new   Graphics::TBitmap();


 Form1->Left=1;Form1->Top=1;


Screen->Cursors[1] = LoadCursor(HInstance, "PEN4");
Screen->Cursors[2] = LoadCursor(HInstance, "PEN8");
Screen->Cursors[3] = LoadCursor(HInstance, "PEN16");
Screen->Cursors[4] = LoadCursor(HInstance, "PEN32");

Screen->Cursors[5] = LoadCursor(HInstance, "RUB4");
Screen->Cursors[6] = LoadCursor(HInstance, "RUB8");
Screen->Cursors[7] = LoadCursor(HInstance, "RUB16");
Screen->Cursors[8] = LoadCursor(HInstance, "RUB32");


  for (int i=0;i<LCD_W;i++)
   for (int j=0;j<LCD_H;j++)
    bin_data[i][j]=0;
  Image1->Canvas->CopyMode=cmSrcInvert;
  Image1->Canvas->Pen->Mode=pmXor;

 Image1->AutoSize=false;
 Image1->Height=LCD_H*ZOOM+1;
 Image1->Width=LCD_W*ZOOM+1;
 Image1->Canvas->Brush->Color=clBlack;
 Image1->Canvas->Pen->Color=clBlack;
 Image1->Canvas->Rectangle(0,0,Image1->Width, Image1->Height);
 DrawBox(sx1,sy1,sx2,sy2);
 SB_grid->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{int i,j;
 int Bt;
 if(X/ZOOM>=0&&Y/ZOOM>=0&&X/ZOOM<LCD_W&&Y/ZOOM<LCD_H)
 {
   if (SB_Pen->Down==true)
       {Image1->Cursor=1;
         if (SB_Pen1->Down==true) {Image1->Cursor=2;pensize=8;}
         if (SB_Pen2->Down==true) {Image1->Cursor=3;pensize=16;}
         if (SB_Pen4->Down==true) {Image1->Cursor=4;pensize=32;}
       }
   else if(SB_Rubber->Down==true)
       {if (SB_Pen1->Down==true) {Image1->Cursor=6;pensize=8;}
        if (SB_Pen2->Down==true) {Image1->Cursor=7;pensize=16;}
        if (SB_Pen4->Down==true) {Image1->Cursor=8;pensize=32;}
       }
   else  Image1->Cursor=crCross;

 StatusBar1->Panels->Items[0]->Text="当前坐标 X= ";
 StatusBar1->Panels->Items[0]->Text+=IntToStr(X/ZOOM);
 StatusBar1->Panels->Items[0]->Text+="    Y= ";
 StatusBar1->Panels->Items[0]->Text+=IntToStr(Y/ZOOM);
 if(Shift.Contains(ssLeft))
   { if (SB_Box->Down==true)
        {
         if(sflag==1)
          if(sx2!=X/ZOOM||sy2!=Y/ZOOM)
           {if(sx2<sx1) sx2=sx1;
            if(sy2<sy1) sy2=sy1;

            DrawBox(sx1,sy1,sx2,sy2);
            sx2=X/ZOOM;sy2=Y/ZOOM;
            if(sx2<sx1) sx2=sx1;
            if(sy2<sy1) sy2=sy1;
            DrawBox(sx1,sy1,sx2,sy2);
            }
        }
    else if (SB_Pen->Down==true) //drawing mode
        {
        Image1->Canvas->Brush->Color=clWhite;
        Image1->Canvas->Pen->Color=clWhite;
        for (int i=0;i<pensize/ZOOM;i++)
         for (int j=0;j<pensize/ZOOM;j++)
          if (bin_data[X/pensize*pensize/ZOOM+i][Y/pensize*pensize/ZOOM+j]==0)
             DrawPoint(X/pensize*pensize/ZOOM+i,Y/pensize*pensize/ZOOM+j);
        }
    else
        {
        Image1->Canvas->Brush->Color=clWhite;
        Image1->Canvas->Pen->Color=clWhite;
        for (int i=0;i<pensize/ZOOM;i++)
         for (int j=0;j<pensize/ZOOM;j++)
          if (bin_data[X/pensize*pensize/ZOOM+i][Y/pensize*pensize/ZOOM+j]==1)
             DrawPoint(X/pensize*pensize/ZOOM+i,Y/pensize*pensize/ZOOM+j);


        }
   }
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{  if (Shift.Contains(ssRight))
     { if(SB_Pen->Down==true)
          SB_Rubber->Down=true;
        else if (SB_Rubber->Down==true) SB_Box->Down=true;
        else SB_Pen->Down=true;

         if (SB_Pen->Down==true)
       {Image1->Cursor=1;
         if (SB_Pen1->Down==true) {Image1->Cursor=2;pensize=8;}
         if (SB_Pen2->Down==true) {Image1->Cursor=3;pensize=16;}
         if (SB_Pen4->Down==true) {Image1->Cursor=4;pensize=32;}
       }
        else if(SB_Rubber->Down==true)
       {if (SB_Pen1->Down==true) {Image1->Cursor=6;pensize=8;}
        if (SB_Pen2->Down==true) {Image1->Cursor=7;pensize=16;}
        if (SB_Pen4->Down==true) {Image1->Cursor=8;pensize=32;}
       }
        else  Image1->Cursor=crCross;
     }
   else
     { if(SB_Pen->Down==true)

       {Image1->Canvas->Brush->Color=clWhite;
        Image1->Canvas->Pen->Color=clWhite;
        //draw or erase on the image1 with pen1,pen2 or pen3
        for (int i=0;i<pensize/ZOOM;i++)
        for (int j=0;j<pensize/ZOOM;j++)
                if (bin_data[X/pensize*pensize/ZOOM+i][Y/pensize*pensize/ZOOM+j]==0)
                        DrawPoint(X/pensize*pensize/ZOOM+i,Y/pensize*pensize/ZOOM+j);
       }

       else if(SB_Rubber->Down==true)

         {Image1->Canvas->Brush->Color=clWhite;
        Image1->Canvas->Pen->Color=clWhite;
        //draw or erase on the image1 with pen1,pen2 or pen3
        for (int i=0;i<pensize/ZOOM;i++)
        for (int j=0;j<pensize/ZOOM;j++)
                if (bin_data[X/pensize*pensize/ZOOM+i][Y/pensize*pensize/ZOOM+j]==1)
                        DrawPoint(X/pensize*pensize/ZOOM+i,Y/pensize*pensize/ZOOM+j);
       }
      else
       {

         { DrawBox(sx1,sy1,sx2,sy2);
           sflag=1;sx1=X/ZOOM; sy1=Y/ZOOM;sx2=X/ZOOM; sy2=Y/ZOOM;
           DrawBox(sx1,sy1,sx2,sy2);
         }


        }


     }

     //select=true


}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{ if (SB_Box->Down==true)
     { if(sflag==1) sflag=2;
     }
  if (SB_Box->Down==false&&Button==mbLeft)
     NewStep();


}
//---------------------------------------------------------------------------
void __fastcall TForm1::SB_transferClick(TObject *Sender)
{
   AnsiString sHex;
 int i,j,n,m,rows,lines;
  n=0;m=0;
 switch(Form3->RadioGroup1->ItemIndex)
 { case 0:
     for(j=sy1;j<=sy2;j++)
       for(i=sx1;i<=sx2;i+=8)
        {hex_data[n++]=Hstring[bin_data[i][j]*8+bin_data[i+1][j]*4+bin_data[i+2][j]*2+bin_data[i+3][j]];
         hex_data[n++]=Hstring[bin_data[i+4][j]*8+bin_data[i+5][j]*4+bin_data[i+6][j]*2+bin_data[i+7][j]];

        }break;

    case 1:
       for(j=sy1;j<=sy2;j+=8)
        for(i=sx1;i<=sx2;i++)
        {hex_data[n++]=Hstring[bin_data[i][j]*8+bin_data[i][j+1]*4+bin_data[i][j+2]*2+bin_data[i][j+3]];
         hex_data[n++]=Hstring[bin_data[i][j+4]*8+bin_data[i][j+5]*4+bin_data[i][j+6]*2+bin_data[i][j+7]];
        } break;
    case 2:
      for(j=sy1;j<=sy2;j++)
       for(i=sx1;i<=sx2;i+=8)
        {hex_data[n++]=Hstring[bin_data[i+7][j]*8+bin_data[i+6][j]*4+bin_data[i+5][j]*2+bin_data[i+4][j]];
         hex_data[n++]=Hstring[bin_data[i+3][j]*8+bin_data[i+2][j]*4+bin_data[i+1][j]*2+bin_data[i][j]];
        } break;
    case 3:
       for(j=sy1;j<=sy2;j+=8)
         for(i=sx1;i<=sx2;i++)
        {hex_data[n++]=Hstring[bin_data[i][j+7]*8+bin_data[i][j+6]*4+bin_data[i][j+5]*2+bin_data[i][j+4]];
         hex_data[n++]=Hstring[bin_data[i][j+3]*8+bin_data[i][j+2]*4+bin_data[i][j+1]*2+bin_data[i][j]];
        } break;


  }

  sHex="";
 Form2->Memo1->Lines->Clear();
 rows=StrToInt(Form3->Edit6->Text);

 lines=n/rows/2;

 if(Form3->CheckBox1->Checked==true)
  {sHex+=Form3->Edit5->Text;
  sHex+="     Left=";
  sHex+=IntToStr(sx1);
  sHex+="     Top=";
  sHex+=IntToStr(sy1);
  sHex+="     Width=";
  sHex+=IntToStr(sx2-sx1+1);
  sHex+="     Height=";
  sHex+=IntToStr(sy2-sy1+1);
  sHex+="     Bytes=";
  sHex+=IntToStr(n/2);
  Form2->Memo1->Lines->Add(sHex);
   }
  sHex="";

  for(i=0;i<lines;i++)
    { sHex+=Form3->Edit3->Text;
       for(j=0;j<rows;j++)
        {
         sHex+=Form3->Edit1->Text;
         sHex+=AnsiString(hex_data[m++]);
         sHex+=AnsiString(hex_data[m++]);
         if(j!=rows-1)sHex+=Form3->Edit2->Text;
        }
        sHex+=Form3->Edit4->Text;
        Form2->Memo1->Lines->Add(sHex);
        sHex="";
    }
    if (m<n)
    { sHex+=Form3->Edit3->Text;
       while(m<n)
         {sHex+=Form3->Edit1->Text;
          sHex+=AnsiString(hex_data[m++]);
          sHex+=AnsiString(hex_data[m++]);
          if(m!=n) sHex+=Form3->Edit2->Text;
         };
        sHex+=Form3->Edit4->Text;
        Form2->Memo1->Lines->Add(sHex);
    }
        Form2->ShowModal();

}

//---------------------------------------------------------------------------



void __fastcall TForm1::SB_ClipClick(TObject *Sender)
{

   TClipboard   *pCB   =   Clipboard();
      if   (pCB->HasFormat(CF_BITMAP))
      {
          try
          {
           pBitmap->LoadFromClipboardFormat(CF_BITMAP,   pCB->GetAsHandle(CF_BITMAP),   0);
           PasteBmp();
          }
          catch   (...)
          {
              MessageBeep(0);
          }
      }
      else
          MessageBeep(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SB_LoadpicClick(TObject *Sender)
{
 FILE* f_bmp;
   if(OpenPictureDialog1->Execute())
     {
       try
         {
                pBitmap->LoadFromFile(OpenPictureDialog1->FileName);
                if(!pBitmap->Empty)
                PasteBmp();
          }
           catch   (...)
          {
              MessageBeep(0);
          }

      }

}
void TForm1::PasteBmp(void)
 {float fct;
  int i,j,imax,jmax;
  int colortp,clb,clg,clr;
  int data;
  fct=StrToFloat(Form3->Edit_factor->Text);

          imax=floor((pBitmap->Width)/fct+sx1+0.5)-1; if(imax>=LCD_W) imax=LCD_W-1;
           jmax=floor((pBitmap->Height)/fct+sy1+0.5)-1; if(jmax>=LCD_H) jmax=LCD_H-1;
           StatusBar1->Panels->Items[4]->Text=IntToStr(pBitmap->Width);
           StatusBar1->Panels->Items[4]->Text+=";   ";
           StatusBar1->Panels->Items[4]->Text+=IntToStr(pBitmap->Height);

    Image1->Canvas->Brush->Color=clWhite;
    Image1->Canvas->Pen->Color=clWhite;


           for (i=sx1;i<=imax;i++)
             for (j=sy1;j<=jmax;j++)
           {  colortp=pBitmap->Canvas->Pixels[(i-sx1+0.5)*fct][(j-sy1+0.5)*fct];
              clb=colortp/256/256;
              clg=(colortp-clb*256*256)/256;
              clr=colortp-clb*256*256-clg*256;
              data=clb<Form3->UpDownB->Position&&clg<Form3->UpDownG->Position&&clr<Form3->UpDownR->Position;
              if (data!=(bin_data[i][j]&&penmode))
              DrawPoint(i,j);

           }
          DrawBox(sx1,sy1,sx2,sy2);
          sx2=imax; sy2=jmax;
          DrawBox(sx1,sy1,sx2,sy2);

}
//--------------------------------------------------


void __fastcall TForm1::SB_stepClick(TObject *Sender)
{
 stepsize*=2;
 if(stepsize>8)  stepsize=1;
 SB_step->Caption=IntToStr(stepsize);
 }
//---------------------------------------------------------------------------

void __fastcall TForm1::CL1Click(TObject *Sender)
{
  if(ColorDialog1->Execute())
   if(ColorDialog1->Color!=clWhite)
   {
  CL1->Color=ColorDialog1->Color;
     DrawBox(sx1,sy1,sx2,sy2);
    CL_SELECT=0x00FFFFFF-CL1->Color;
      DrawBox(sx1,sy1,sx2,sy2);
   }
  
}
//---------------------------------------------------------------------------
void TForm1::StatusUpdate()
{StatusBar1->Panels->Items[1]->Text="窗体 ( ";
 StatusBar1->Panels->Items[1]->Text+=IntToStr(sx1);
 StatusBar1->Panels->Items[1]->Text+=", ";
 StatusBar1->Panels->Items[1]->Text+=IntToStr(sy1);
 StatusBar1->Panels->Items[1]->Text+=", ";
 StatusBar1->Panels->Items[1]->Text+=IntToStr(sx2);
 StatusBar1->Panels->Items[1]->Text+=", ";
 StatusBar1->Panels->Items[1]->Text+=IntToStr(sy2);
 StatusBar1->Panels->Items[1]->Text+=")";

 StatusBar1->Panels->Items[2]->Text="窗体大小  ";
 StatusBar1->Panels->Items[2]->Text+=IntToStr(sx2-sx1+1);
 StatusBar1->Panels->Items[2]->Text+="  X  ";
 StatusBar1->Panels->Items[2]->Text+=IntToStr(sy2-sy1+1);

 SB_paste->Enabled=hascopy;
 if(hascopy)  StatusBar1->Panels->Items[3]->Text="已复制";
 else StatusBar1->Panels->Items[3]->Text="";


}
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
 StatusUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BT_fontClick(TObject *Sender)
{
 FontDialog1->Options.Clear();
  FontDialog1->Options << fdLimitSize;
  FontDialog1->MaxFontSize = 48;
  FontDialog1->MinFontSize = 8;
  FontDialog1->Options <<fdForceFontExist;
   FontDialog1->Options <<fdNoVectorFonts;
 //  FontDialog1->Options <<fdFixedPitchOnly ;
  if (FontDialog1->Execute())
       ;// BT_font->Caption=FontDialog1->Font->Name;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
int i,j;
int imax, jmax;
bool data;

   Graphics::TBitmap   *wBitmap   =   new   Graphics::TBitmap();
   wBitmap->Canvas->Font=FontDialog1->Font;
   i=wBitmap->Canvas->Font->Height;
   wBitmap->Height=-wBitmap->Canvas->Font->Height;
   wBitmap->Canvas->TextOut(0,0,Edit_input->Text);
   wBitmap->Width=wBitmap->Canvas->PenPos.x;
   wBitmap->Canvas->TextOut(0,0,Edit_input->Text);

   imax=wBitmap->Width+sx1; if(imax>LCD_W) imax=LCD_W;
   jmax=wBitmap->Height+sy1; if(jmax>LCD_H) jmax=LCD_H;

   Image1->Canvas->Brush->Color=clWhite;
   Image1->Canvas->Pen->Color=clWhite;
   for (i=sx1;i<imax;i++)
    for (j=sy1;j<jmax;j++)
         {if(wBitmap->Canvas->Pixels[i-sx1][j-sy1]==clWhite)
           data=0;
          else data=1;

          if (data!=(bin_data[i][j]&&penmode))
                  DrawPoint(i,j);
          }

      delete   wBitmap;

    NewStep();


}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_SaveClick(TObject *Sender)
{
 FILE* f_bin;
  int i,j;
  if(SaveDialog_pic->Execute())
    {
      f_bin=fopen(SaveDialog_pic->FileName.c_str(),"wt");
      fprintf(f_bin,"%d, %d,  %d,  %d \n",sx1, sy1, sx2-sx1+1, sy2-sy1+1);
     for(j=sy1;j<=sy2;j++)
       { for(i=sx1;i<=sx2;i++)
            fprintf(f_bin, "%d",bin_data[i][j]);
         fprintf(f_bin,"\n");
        }

    }


 fclose(f_bin);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_LoadClick(TObject *Sender)
{
 FILE* f_bin;
  int i,j;
  char mychar;
  if(OpenDialog_pic->Execute())
    {
      f_bin=fopen(OpenDialog_pic->FileName.c_str(),"rt");
    DrawBox(sx1,sy1,sx2,sy2);
    //load point data
      fscanf(f_bin,"%d, %d,  %d,  %d \n",&sx1, &sy1, &sx2, &sy2);
      sx2+=sx1;sy2+=sy1;sx2--;sy2--;
     DrawBox(sx1,sy1,sx2,sy2);
    //clear data in selected box
          SB_del->Click();

          //write new data, and draw
           Image1->Canvas->Brush->Color=clWhite;
           Image1->Canvas->Pen->Color=clWhite;

     for(j=sy1;j<=sy2;j++)
       { for(i=sx1;i<=sx2;i++)
            {fscanf(f_bin, "%c",&mychar);
              if(mychar=='1')
                {
                 if(bin_data[i][j]==0)Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
                 bin_data[i][j]=1;
                }
                else
                { if(bin_data[i][j]==1)Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
                 bin_data[i][j]=0;
                }
            }
        fscanf(f_bin,"\n");
        }

    }


 fclose(f_bin);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SB_LeftMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  int i,j;
 if (Shift.Contains(ssCtrl)||Shift.Contains(ssShift))
   for(int s=0;s<stepsize;s++)
    { DrawBox(sx1,sy1,sx2,sy2);
      if (Shift.Contains(ssCtrl))
          {if(sx1>0) {sx1--;sx2--;}}
      if (Shift.Contains(ssShift))
          {if(sx1<sx2) sx2--;}
      DrawBox(sx1,sy1,sx2,sy2);

    }

 else
    {

  for(int s=0;s<stepsize;s++){
   if(sflag==2)
   { Image1->Canvas->Brush->Color=clWhite;
     Image1->Canvas->Pen->Color=clWhite;
     if(sx1>0){ for(j=sy1;j<=sy2;j++)
          {if(bin_data[sx1-1][j]!=bin_data[sx1][j])
                Image1->Canvas->Rectangle((sx1-1)*ZOOM,j*ZOOM,(sx1-1+1)*ZOOM,(j+1)*ZOOM);
             bin_data[sx1-1][j]=bin_data[sx1][j];
           }
              }
     for(i=sx1;i<=sx2-1;i++)
        for(j=sy1;j<=sy2;j++)
          {if(bin_data[i][j]!=bin_data[i+1][j])
                Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
           bin_data[i][j]=bin_data[i+1][j];
           }
     for(j=sy1;j<=sy2;j++)
          {if(bin_data[sx2][j]==1)
                Image1->Canvas->Rectangle((sx2)*ZOOM,j*ZOOM,(sx2+1)*ZOOM,(j+1)*ZOOM);
             bin_data[sx2][j]=0;
           }

       if(sx1>0)
     {  DrawBox(sx1,sy1,sx2,sy2);
        sx1-=1;sx2-=1;
        DrawBox(sx1,sy1,sx2,sy2);
     }

   }  }

   }NewStep();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_RightMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
int i,j;
if (Shift.Contains(ssCtrl)||Shift.Contains(ssShift))
   for(int s=0;s<stepsize;s++)
    {  DrawBox(sx1,sy1,sx2,sy2);
      if (Shift.Contains(ssCtrl))
          {if(sx2<LCD_W-1) {sx1++;sx2++;}}
      if (Shift.Contains(ssShift))
          {if(sx2<LCD_W-1) sx2++;}
         DrawBox(sx1,sy1,sx2,sy2);

    }

 else
    {


 for(int s=0;s<stepsize;s++){
  if(sflag==2)
   {
     Image1->Canvas->Brush->Color=clWhite;
     Image1->Canvas->Pen->Color=clWhite;
     if( sx2<LCD_W-1)
        {for(j=sy1;j<=sy2;j++)
          {if(bin_data[sx2+1][j]!=bin_data[sx2][j])
                Image1->Canvas->Rectangle((sx2+1)*ZOOM,j*ZOOM,(sx2+1+1)*ZOOM,(j+1)*ZOOM);
            bin_data[sx2+1][j]=bin_data[sx2][j];
           }

        }
     for(i=sx2;i>sx1;i--)
        for(j=sy1;j<=sy2;j++)
          {if(bin_data[i][j]!=bin_data[i-1][j])
                Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
           bin_data[i][j]=bin_data[i-1][j];
           }


      for(j=sy1;j<=sy2;j++)
          {if(bin_data[sx1][j]==1)
                Image1->Canvas->Rectangle((sx1)*ZOOM,j*ZOOM,(sx1+1)*ZOOM,(j+1)*ZOOM);
            bin_data[sx1][j]=0;
           }


      if( sx2<LCD_W-1)
     { DrawBox(sx1,sy1,sx2,sy2);
        sx1+=1;sx2+=1;
       DrawBox(sx1,sy1,sx2,sy2);

     }

   }  }
   }NewStep();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_UpMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
int i,j;
//SB_Select->Down=true;
if (Shift.Contains(ssCtrl)||Shift.Contains(ssShift))
    for(int s=0;s<stepsize;s++)
    { DrawBox(sx1,sy1,sx2,sy2);

      if (Shift.Contains(ssCtrl))
          {if(sy1>0) {sy1--; sy2--;}}
      if (Shift.Contains(ssShift))
           {if(sy2>sy1) sy2--; }
      DrawBox(sx1,sy1,sx2,sy2);

    }

 else
    {

  for(int s=0;s<stepsize;s++){
  if(sflag==2)
   {
     Image1->Canvas->Brush->Color=clWhite;
     Image1->Canvas->Pen->Color=clWhite;

     if(sy1>0) {
       for(i=sx1;i<=sx2;i++)
          {if(bin_data[i][sy1-1]!=bin_data[i][sy1])
                Image1->Canvas->Rectangle(i*ZOOM,(sy1-1)*ZOOM,(i+1)*ZOOM,(sy1-1+1)*ZOOM);
            bin_data[i][sy1-1]=bin_data[i][sy1];
           }
                }

     for(i=sx1;i<=sx2;i++)
        for(j=sy1;j<=sy2-1;j++)
          {if(bin_data[i][j]!=bin_data[i][j+1])
                Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
           bin_data[i][j]=bin_data[i][j+1];
           }

       for(i=sx1;i<=sx2;i++)
          {if(bin_data[i][sy2]==1)
                Image1->Canvas->Rectangle(i*ZOOM,(sy2)*ZOOM,(i+1)*ZOOM,(sy2+1)*ZOOM);
            bin_data[i][sy2]=0;
           }


       if(sy1>0)
     { DrawBox(sx1,sy1,sx2,sy2);
        sy1-=1;sy2-=1;
     DrawBox(sx1,sy1,sx2,sy2);
 }

   }   }
  }NewStep();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_DownMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
int i,j;

//SB_Select->Down=true;
if (Shift.Contains(ssCtrl)||Shift.Contains(ssShift))
    for(int s=0;s<stepsize;s++)
    {  DrawBox(sx1,sy1,sx2,sy2);

      if (Shift.Contains(ssCtrl))
          {if(sy2<LCD_H-1) {sy1++;sy2++;}}
      if (Shift.Contains(ssShift))
          {if(sy2<LCD_H-1) sy2++;}
         DrawBox(sx1,sy1,sx2,sy2);

    }

 else
    {

  for(int s=0;s<stepsize;s++){
  if(sflag==2)
   {

     Image1->Canvas->Brush->Color=clWhite;
     Image1->Canvas->Pen->Color=clWhite;
     if(sy2<LCD_H-1) {
      for(i=sx1;i<=sx2;i++)
          {if(bin_data[i][sy2+1]!=bin_data[i][sy2])
                Image1->Canvas->Rectangle(i*ZOOM,(sy2+1)*ZOOM,(i+1)*ZOOM,(sy2+1+1)*ZOOM);
           bin_data[i][sy2+1]=bin_data[i][sy2];
           }
                    }


     for(i=sx1;i<=sx2;i++)
        for(j=sy2;j>sy1;j--)
          {if(bin_data[i][j]!=bin_data[i][j-1])
                Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
           bin_data[i][j]=bin_data[i][j-1];
           }

       for(i=sx1;i<=sx2;i++)
          {if(bin_data[i][sy1]==1)
                Image1->Canvas->Rectangle(i*ZOOM,(sy1)*ZOOM,(i+1)*ZOOM,(sy1+1)*ZOOM);
           bin_data[i][sy1]=0;
           }




          if(sy2<LCD_H-1)
     { DrawBox(sx1,sy1,sx2,sy2);
        sy1+=1;sy2+=1;
      DrawBox(sx1,sy1,sx2,sy2);
        }

   } }
  }NewStep();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N5Click(TObject *Sender)
{
  exit(0);
}
//---------------------------------------------------------------------------
 void TForm1::DrawBox(int ssx1, int ssy1, int ssx2, int ssy2 )
 {Image1->Canvas->Brush->Color=CL_SELECT;
  Image1->Canvas->Pen->Color=CL_SELECT;
  Image1->Canvas->Rectangle(ssx1*ZOOM,ssy1*ZOOM,(ssx2+1)*ZOOM+1,(ssy2+1)*ZOOM+1);
 }
//--------------------------------------------------------------------------
void TForm1::DrawPoint(int ssx1, int ssy1)
 {//Image1->Canvas->Brush->Color=clWhite;
  //Image1->Canvas->Pen->Color=clWhite;
  Image1->Canvas->Rectangle(ssx1*ZOOM,ssy1*ZOOM,(ssx1+1)*ZOOM,(ssy1+1)*ZOOM);
  bin_data[ssx1][ssy1]=!bin_data[ssx1][ssy1];
 }

//--------------------------------------------------------------------------








void __fastcall TForm1::BT_clsClick(TObject *Sender)
{
 for (int i=0;i<LCD_W;i++)
   for (int j=0;j<LCD_H;j++)
    bin_data[i][j]=0;

Image1->Canvas->CopyMode=cmWhiteness;
Image1->Canvas->Pen->Mode=pmWhite;
Image1->Canvas->Rectangle(0,0, Image1->Width, Image1->Height);

 Image1->Canvas->CopyMode=cmSrcInvert;
 Image1->Canvas->Pen->Mode=pmXor;
   sx1=0; sy1=0;sx2=LCD_W-1; sy2=LCD_H-1;
  DrawBox(sx1,sy1,sx2,sy2);
  if(gridon==true) {gridon=false; SB_grid->Click();}

}
//---------------------------------------------------------------------------







void __fastcall TForm1::CheckBox_modeClick(TObject *Sender)
{
 penmode=!Form3->CheckBox_mode->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_undoClick(TObject *Sender)
{int i,j;

 undosize--;
 undosize_pt--;
  if(undosize_pt<0) undosize_pt=undomax-1;
 //clear
  SB_selectall->Click();
  Image1->Canvas->Brush->Color=clWhite;
  Image1->Canvas->Pen->Color=clWhite;
  for(i=sx1;i<=sx2;i++)
      for(j=sy1;j<=sy2;j++)
    {
    if(bin_data[i][j]==1)
     Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
    bin_data[i][j]=0;

    }


   Image1->Canvas->Brush->Color=clWhite;
   Image1->Canvas->Pen->Color=clWhite;
   for(i=0;i<LCD_W;i++)
    for(j=0;j<LCD_H;j++)
      {if(buffer_data[i][j][undosize_pt]==1)
         Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
       bin_data[i][j]=buffer_data[i][j][undosize_pt];
      }
      DrawBox(sx1,sy1,sx2,sy2);
      sx1=buffer_sx1[undosize_pt];
      sx2=buffer_sx2[undosize_pt];
      sy1=buffer_sy1[undosize_pt];
      sy2=buffer_sy2[undosize_pt];

      DrawBox(sx1,sy1,sx2,sy2);

   if(undosize==0) SB_undo->Enabled=false;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_setupClick(TObject *Sender)
{
 Form3->ShowModal();

}
//---------------------------------------------------------------------------
void TForm1::NewStep(void)
{ int i,j;
 // unsigned *test= new unsigned[320*240];
  undosize_pt++;
  undosize++;
  if(undosize_pt>=undomax) undosize_pt=0;
  if(undosize>=undomax) undosize--;

  for (i=0;i<LCD_W;i++)
    for (j=0;j<LCD_H;j++)
        buffer_data[i][j][undosize_pt]=bin_data[i][j];

      buffer_sx1[undosize_pt]=sx1;
      buffer_sx2[undosize_pt]=sx2;
      buffer_sy1[undosize_pt]=sy1;
      buffer_sy2[undosize_pt]=sy2;

   SB_undo->Enabled=true;
}
void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
  switch(ComboBox1->ItemIndex)
        {case 3:
                LCD_W=320;LCD_H=240;ZOOM=8;
                break;
         case 2:
                LCD_W=240;LCD_H=128;ZOOM=8;
                break;
         case 1:
                LCD_W=128;LCD_H=64;ZOOM=8;
                break;
         case 0:
                LCD_W=64;LCD_H=32;ZOOM=8;
                break;

        }

   SB_new->Click();


}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_zoominClick(TObject *Sender)
{
int i,j;
  ZOOM*=2;
  if(ZOOM>16)    {ZOOM=16;}
  if(ComboBox1->ItemIndex==3&&ZOOM==16)
    ZOOM=8;
  if(ZOOM==16&&SB_Pen1->Down==true) {SB_Pen2->Down=true;SB_Pen1->Enabled=false;}
  if(ZOOM<16&&SB_Pen1->Enabled==false) {SB_Pen1->Down=true;SB_Pen1->Enabled=true;}

   Image1->Width=LCD_W*ZOOM+1;
   Image1->Height=LCD_H*ZOOM+1;
   Image1->Picture->Bitmap->Width = Image1->Width;
   Image1->Picture->Bitmap->Height = Image1->Height;
   Image1->Canvas->CopyMode=cmWhiteness;
   Image1->Canvas->Pen->Mode=pmWhite;
   Image1->Canvas->Rectangle(0,0, Image1->Width, Image1->Height);
   Image1->Canvas->CopyMode=cmSrcInvert;
   Image1->Canvas->Pen->Mode=pmXor;
   DrawBox(sx1,sy1,sx2,sy2);
   Image1->Canvas->Brush->Color=clWhite;
   Image1->Canvas->Pen->Color=clWhite;
   for(i=0;i<LCD_W;i++)
    for(j=0;j<LCD_H;j++)
     if(bin_data[i][j]==1)
      Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);

  if(gridon==true) {gridon=false; SB_grid->Click();}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_zoomoutClick(TObject *Sender)
{
int i,j;
  ZOOM/=2;
  if(ZOOM<2)    {ZOOM=2;}
  if(ZOOM==16&&SB_Pen1->Down==true) {SB_Pen2->Down=true;SB_Pen1->Enabled=false;}
  if(ZOOM<16&&SB_Pen1->Enabled==false) {SB_Pen1->Down=true;SB_Pen1->Enabled=true;}

   Image1->Width=LCD_W*ZOOM+1;
   Image1->Height=LCD_H*ZOOM+1;
   Image1->Picture->Bitmap->Width = Image1->Width;
   Image1->Picture->Bitmap->Height = Image1->Height;
   Image1->Canvas->CopyMode=cmWhiteness;
   Image1->Canvas->Pen->Mode=pmWhite;
   Image1->Canvas->Rectangle(0,0, Image1->Width, Image1->Height);
  if(gridon==true)
   {gridon=false;
    SB_grid->Click();
   }
   Image1->Canvas->CopyMode=cmSrcInvert;
   Image1->Canvas->Pen->Mode=pmXor;
   DrawBox(sx1,sy1,sx2,sy2);
   Image1->Canvas->Brush->Color=clWhite;
   Image1->Canvas->Pen->Color=clWhite;
   for(i=0;i<LCD_W;i++)
    for(j=0;j<LCD_H;j++)
     if(bin_data[i][j]==1)
      Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
    if(gridon==true) {gridon=false; SB_grid->Click();}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::SB_gridClick(TObject *Sender)
{
 gridon=!gridon;
 Image1->Canvas->Pen->Color=0x00111111;
 for (int i=0;i<=LCD_W;i++)
   { Image1->Canvas->MoveTo(i*ZOOM,0);
    Image1->Canvas->LineTo(i*ZOOM,ZOOM*LCD_H);
   }
 for (int i=0;i<=LCD_H;i++)
  { Image1->Canvas->MoveTo(0,i*ZOOM);
    Image1->Canvas->LineTo(ZOOM*LCD_W,i*ZOOM);
   }
   Image1->Canvas->Pen->Color=0x00222222;
 for (int i=0;i<=LCD_W/8;i++)
   { Image1->Canvas->MoveTo(i*ZOOM*8,0);
    Image1->Canvas->LineTo(i*ZOOM*8,ZOOM*LCD_H);
   }
 for (int i=0;i<=LCD_H/8;i++)
  { Image1->Canvas->MoveTo(0,i*ZOOM*8);
    Image1->Canvas->LineTo(ZOOM*LCD_W,i*ZOOM*8);
   }
   Image1->Canvas->Pen->Color=0x00444444;
 for (int i=0;i<=LCD_W/16;i++)
   { Image1->Canvas->MoveTo(i*ZOOM*16,0);
    Image1->Canvas->LineTo(i*ZOOM*16,ZOOM*LCD_H);
   }
 for (int i=0;i<=LCD_H/16;i++)
  { Image1->Canvas->MoveTo(0,i*ZOOM*16);
    Image1->Canvas->LineTo(ZOOM*LCD_W,i*ZOOM*16);
   }


}
//---------------------------------------------------------------------------


void __fastcall TForm1::SB_newClick(TObject *Sender)
{
 undosize=0;undosize_pt=0;
 SB_undo->Enabled=false;
 Image1->Width=LCD_W*ZOOM+1;
   Image1->Height=LCD_H*ZOOM+1;
   Image1->Picture->Bitmap->Width = Image1->Width;
   Image1->Picture->Bitmap->Height = Image1->Height;
 for (int i=0;i<LCD_W;i++)
   for (int j=0;j<LCD_H;j++)
    {bin_data[i][j]=0;
     buffer_data[i][j][0]=0;
     }

   sx1=0; sy1=0;sx2=LCD_W-1; sy2=LCD_H-1;

      buffer_sx1[0]=sx1;
      buffer_sx2[0]=sx2;
      buffer_sy1[0]=sy1;
      buffer_sy2[0]=sy2;

Image1->Canvas->CopyMode=cmWhiteness;
Image1->Canvas->Pen->Mode=pmWhite;
Image1->Canvas->Rectangle(0,0, Image1->Width, Image1->Height);

 Image1->Canvas->CopyMode=cmSrcInvert;
 Image1->Canvas->Pen->Mode=pmXor;
  DrawBox(sx1,sy1,sx2,sy2);
  if(gridon==true) {gridon=false; SB_grid->Click();}
 

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
  int i,j;
  Image1->Canvas->Brush->Color=clWhite;
  Image1->Canvas->Pen->Color=clWhite;


  for (i=sx1;i<=sx2;i++)
   for (j=sy1;j<=sy2;j++)
    { bin_data[i][j]=!bin_data[i][j];
    Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
    }
 NewStep();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SB_cutClick(TObject *Sender)
{
 SB_copy->Click();
 SB_del->Click();
 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_copyClick(TObject *Sender)
{
 int i,j;
  cp_width=sx2-sx1+1;
  cp_height=sy2-sy1+1;

  for (i=0;i<cp_width;i++)
   for (j=0;j<cp_height;j++)
     cp_data[i][j]= bin_data[i+sx1][j+sy1];
  hascopy=1;
  SB_paste->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_pasteClick(TObject *Sender)
{
int i,j,imax,jmax;

  if(hascopy)
  {
  Image1->Canvas->Brush->Color=clWhite;
  Image1->Canvas->Pen->Color=clWhite;
   imax=cp_width+sx1; if(imax>LCD_W) imax=LCD_W;
   jmax=cp_height+sy1; if(jmax>LCD_H) jmax=LCD_H;


   for (i=sx1;i<imax;i++)
    for (j=sy1;j<jmax;j++)
        {//if(bin_data[i][j]!=cp_data[i-sx1][j-sy1])
         //    Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
         //bin_data[i][j]=cp_data[i-sx1][j-sy1];

         if (cp_data[i-sx1][j-sy1]!=(bin_data[i][j]&&penmode))
                  DrawPoint(i,j);

         }
        DrawBox(sx1,sy1,sx2,sy2);
        sx2=imax-1; sy2=jmax-1;
        DrawBox(sx1,sy1,sx2,sy2);
    NewStep();
   }

}

void __fastcall TForm1::SB_delClick(TObject *Sender)
{
 int i,j;
 Image1->Canvas->Brush->Color=clWhite;
 Image1->Canvas->Pen->Color=clWhite;
 for(i=sx1;i<=sx2;i++)
      for(j=sy1;j<=sy2;j++)
    {
    if(bin_data[i][j]==1)
     Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
    bin_data[i][j]=0;

    }
 //NewStep();   
        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SB_flipvClick(TObject *Sender)
{
unsigned short  tp_data[320][240];
 int i,j;
SB_selectp1->Click();
  Image1->Canvas->Brush->Color=clWhite;
   Image1->Canvas->Pen->Color=clWhite;

 for (i=sx1;i<=sx2;i++)
  for (j=sy1;j<=sy2;j++)
    tp_data[i][j]=bin_data[i][sy1+sy2-j];
 SB_del->Click();
 for (i=sx1;i<=sx2;i++)
  for (j=sy1;j<=sy2;j++)
      {
     bin_data[i][j]=tp_data[i][j];
      if(tp_data[i][j]==1)
      Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_fliphClick(TObject *Sender)
{
 unsigned short  tp_data[320][240];
 int i,j;
SB_selectp1->Click();
  Image1->Canvas->Brush->Color=clWhite;
   Image1->Canvas->Pen->Color=clWhite;

 for (i=sx1;i<=sx2;i++)
  for (j=sy1;j<=sy2;j++)
    tp_data[i][j]=bin_data[sx1+sx2-i][j];
 SB_del->Click();
 for (i=sx1;i<=sx2;i++)
  for (j=sy1;j<=sy2;j++)
      {
     bin_data[i][j]=tp_data[i][j];
      if(tp_data[i][j]==1)
      Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
      }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_l90Click(TObject *Sender)
{ int imax,jmax;
 bool  tp_data[320][320];
 int i,j;
 SB_selectp1->Click();
  Image1->Canvas->Brush->Color=clWhite;
  Image1->Canvas->Pen->Color=clWhite;

 for (i=0;i<=sy2-sy1;i++)
  for (j=0;j<=sx2-sx1;j++)
     tp_data[i][j]=bin_data[sx2-j][i+sy1];
 imax=sx1+sy2-sy1; jmax=sy1+sx2-sx1;
 if(imax>=LCD_W) imax=LCD_W-1;
 if(jmax>=LCD_H) jmax=LCD_H-1;
 SB_del->Click();
        DrawBox(sx1,sy1,sx2,sy2);
        sx2=imax; sy2=jmax;
        DrawBox(sx1,sy1,sx2,sy2);
 SB_del->Click();

 for (i=sx1;i<=imax;i++)
  for (j=sy1;j<=jmax;j++)
      {
      bin_data[i][j]=tp_data[i-sx1][j-sy1];
      if(bin_data[i][j]==1)
      Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
      }

   NewStep();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_r90Click(TObject *Sender)
{
 int imax,jmax;
 bool  tp_data[320][320];
 int i,j;
 SB_selectp1->Click();
  Image1->Canvas->Brush->Color=clWhite;
  Image1->Canvas->Pen->Color=clWhite;

 for (i=0;i<=sy2-sy1;i++)
  for (j=0;j<=sx2-sx1;j++)
     tp_data[i][j]=bin_data[sx1+j][sy2-i];
 imax=sx1+sy2-sy1; jmax=sy1+sx2-sx1;
 if(imax>=LCD_W) imax=LCD_W-1;
 if(jmax>=LCD_H) jmax=LCD_H-1;
 SB_del->Click();
        DrawBox(sx1,sy1,sx2,sy2);
        sx2=imax; sy2=jmax;
        DrawBox(sx1,sy1,sx2,sy2);
 SB_del->Click();

 for (i=sx1;i<=imax;i++)
  for (j=sy1;j<=jmax;j++)
      {
      bin_data[i][j]=tp_data[i-sx1][j-sy1];
      if(bin_data[i][j]==1)
      Image1->Canvas->Rectangle(i*ZOOM,j*ZOOM,(i+1)*ZOOM,(j+1)*ZOOM);
      }

   NewStep();

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TForm1::SB_selectallClick(TObject *Sender)
{
        DrawBox(sx1,sy1,sx2,sy2);
        sx1=0; sy1=0;sx2=LCD_W-1; sy2=LCD_H-1;
        DrawBox(sx1,sy1,sx2,sy2);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_selectp1Click(TObject *Sender)
{
int xmax,xmin,ymax,ymin;
       xmax=0;xmin=LCD_W-1;ymax=0;ymin=LCD_H-1;
       DrawBox(sx1,sy1,sx2,sy2);
       if(sx2<0||sy2<0) {sx2=LCD_W-1;sy2=LCD_H-1;}
          for(int i=sx1;i<=sx2;i++)
                for(int j=sy1;j<=sy2;j++)
                   { if(bin_data[i][j]==1)
                        { if(i>xmax) xmax=i;
                          if(i<xmin) xmin=i;
                          if(j>ymax) ymax=j;
                          if(j<ymin) ymin=j;

                        }
                   }
          sx1=xmin;sx2=xmax;sy1=ymin;sy2=ymax;

          if(sx2<sx1 || sy2<sy1)
            {sx1=0;sx2=LCD_W-1;sy1=0;sy2=LCD_H-1;
             for(int i=sx1;i<=sx2;i++)
                for(int j=sy1;j<=sy2;j++)
                   { if(bin_data[i][j]==1)
                        { if(i>xmax) xmax=i;
                          if(i<xmin) xmin=i;
                          if(j>ymax) ymax=j;
                          if(j<ymin) ymin=j;

                        }
                   }
          sx1=xmin;sx2=xmax;sy1=ymin;sy2=ymax;
             }

             if(sx2<sx1 || sy2<sy1)
            {sx1=0;sx2=LCD_W-1;sy1=0;sy2=LCD_H-1;}

       DrawBox(sx1,sy1,sx2,sy2);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::SB_selectp2Click(TObject *Sender)
{
  int xmax,xmin,ymax,ymin;
       xmax=0;xmin=LCD_W-1;ymax=0;ymin=LCD_H-1;
       DrawBox(sx1,sy1,sx2,sy2);
       if(sx2<0||sy2<0) {sx2=LCD_W-1;sy2=LCD_H-1;}
          for(int i=sx1;i<=sx2;i++)
                for(int j=sy1;j<=sy2;j++)
                   { if(bin_data[i][j]==1)
                        { if(i>xmax) xmax=i;
                          if(i<xmin) xmin=i;
                          if(j>ymax) ymax=j;
                          if(j<ymin) ymin=j;

                        }
                   }
          sx1=xmin;sx2=xmax;sy1=ymin;sy2=ymax;
        if(sx2<sx1 || sy2<sy1)
            {sx1=0;sx2=LCD_W-1;sy1=0;sy2=LCD_H-1;
             if(sx2<0||sy2<0) {sx2=LCD_W-1;sy2=LCD_H-1;}
          for(int i=sx1;i<=sx2;i++)
                for(int j=sy1;j<=sy2;j++)
                   { if(bin_data[i][j]==1)
                        { if(i>xmax) xmax=i;
                          if(i<xmin) xmin=i;
                          if(j>ymax) ymax=j;
                          if(j<ymin) ymin=j;

                        }
                   }
          sx1=xmin;sx2=xmax;sy1=ymin;sy2=ymax;

            }
             if(sx2<sx1 || sy2<sy1)
            {sx1=0;sx2=LCD_W-1;sy1=0;sy2=LCD_H-1;}

         if(Form3->RadioGroup1->ItemIndex==0||Form3->RadioGroup1->ItemIndex==2)
               {sx1=sx1/8*8;sx2=sx2/8*8+7;}
               else
               {sy1=sy1/8*8; sy2=sy2/8*8+7;}

         DrawBox(sx1,sy1,sx2,sy2);

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


