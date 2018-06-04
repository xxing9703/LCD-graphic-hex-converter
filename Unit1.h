//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include "CGRID.h"
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TSaveDialog *SaveDialog1;
        TColorDialog *ColorDialog1;
        TTimer *Timer1;
        TFontDialog *FontDialog1;
        TEdit *Edit_input;
        TButton *Button3;
        TButton *BT_font;
        TSaveDialog *SaveDialog_pic;
        TOpenDialog *OpenDialog_pic;
        TMainMenu *MainMenu1;
        TMenuItem *filemain;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N6;
        TMenuItem *N7;
        TMenuItem *N8;
        TMenuItem *N9;
        TMenuItem *N12;
        TMenuItem *N13;
        TMenuItem *N14;
        TMenuItem *N15;
        TMenuItem *N16;
        TMenuItem *N5;
        TOpenPictureDialog *OpenPictureDialog1;
        TMenuItem *N4;
        TMenuItem *bmp1;
        TMenuItem *N17;
        TMenuItem *N10;
        TScrollBox *ScrollBox1;
        TImage *Image1;
        TSpeedButton *SpeedButton8;
        TCoolBar *CoolBar1;
        TToolBar *ToolBar1;
        TSpeedButton *SB_Load;
        TSpeedButton *SB_Save;
        TSpeedButton *SB_Clip;
        TSpeedButton *SB_Loadpic;
        TSpeedButton *SB_cut;
        TSpeedButton *SB_copy;
        TSpeedButton *SB_del;
        TSpeedButton *SB_undo;
        TSpeedButton *SB_setup;
        TSpeedButton *SB_zoomin;
        TSpeedButton *SB_zoomout;
        TToolBar *ToolBar3;
        TSpeedButton *SB_Pen;
        TSpeedButton *SB_Rubber;
        TSpeedButton *SB_Box;
        TToolBar *ToolBar2;
        TSpeedButton *SB_Pen1;
        TSpeedButton *SB_Pen2;
        TSpeedButton *SB_Pen4;
        TSpeedButton *SB_paste;
        TToolBar *ToolBar4;
        TSpeedButton *SB_grid;
        TSpeedButton *SB_new;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SB_l90;
        TSpeedButton *SB_r90;
        TSpeedButton *SB_fliph;
        TSpeedButton *SB_flipv;
        TSpeedButton *SB_selectall;
        TSpeedButton *SB_selectp2;
        TSpeedButton *SB_selectp1;
        TComboBox *ComboBox1;
        TSpeedButton *SB_Left;
        TSpeedButton *SB_Right;
        TSpeedButton *SB_Up;
        TSpeedButton *SB_Down;
        TSpeedButton *SB_transfer;
        TSpeedButton *SB_step;
        TLabel *CL1;
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
       
        void __fastcall SB_ClipClick(TObject *Sender);
        void __fastcall SB_stepClick(TObject *Sender);
        void __fastcall CL1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall BT_fontClick(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall SB_SaveClick(TObject *Sender);
        void __fastcall SB_LoadClick(TObject *Sender);
        void __fastcall SB_LeftMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall SB_RightMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall SB_UpMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall SB_DownMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall SB_LoadpicClick(TObject *Sender);
        void __fastcall BT_clsClick(TObject *Sender);
        void __fastcall CheckBox_modeClick(TObject *Sender);
        void __fastcall SB_undoClick(TObject *Sender);
        void __fastcall SB_setupClick(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall SB_zoominClick(TObject *Sender);
        void __fastcall SB_zoomoutClick(TObject *Sender);
        void __fastcall SB_gridClick(TObject *Sender);
        void __fastcall SB_newClick(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SB_delClick(TObject *Sender);
        void __fastcall SB_flipvClick(TObject *Sender);
        void __fastcall SB_fliphClick(TObject *Sender);
        void __fastcall SB_l90Click(TObject *Sender);
        void __fastcall SB_r90Click(TObject *Sender);
        void __fastcall SB_cutClick(TObject *Sender);
        void __fastcall SB_copyClick(TObject *Sender);
        void __fastcall SB_pasteClick(TObject *Sender);
        void __fastcall SB_selectallClick(TObject *Sender);
        void __fastcall SB_selectp1Click(TObject *Sender);
        void __fastcall SB_selectp2Click(TObject *Sender);
        void __fastcall SB_transferClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int ZOOM;
        int LCD_W;
        int LCD_H;
        int sx1,sy1,sx2,sy2,sflag;
        int stepsize;
        int pensize,rubsize;
        int hascopy;
        bool gridon;
        unsigned int penmode;
        TColor CL_SELECT,CL_THRE;
        __fastcall TForm1(TComponent* Owner);
        Graphics::TBitmap   *pBitmap ;


        void TForm1::StatusUpdate(void);
        void TForm1::DrawBox(int ssx1, int ssy1,int ssx2, int ssy2);
        void TForm1::DrawPoint(int ssx1, int ssy1);
        void TForm1::PasteBmp(void);
        void TForm1::NewStep(void);


};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
  bool bin_data[320][240],cp_data[320][240];
   static  bool buffer_data[320][240][10];
   static int buffer_sx1[10],buffer_sx2[10],buffer_sy1[10],buffer_sy2[10];
//static bool stackdata[320][240];
int cp_width,cp_height;
char hex_data[19200];
const char Hstring[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
 TStack *undostack= new TStack;
 TStack *redostack= new TStack;
int undosize,undosize_pt;
//---------------------------------------------------------------------------
#endif
