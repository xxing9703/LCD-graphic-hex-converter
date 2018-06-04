//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TCheckBox *CheckBox1;
        TEdit *Edit6;
        TEdit *Edit5;
        TEdit *Edit4;
        TEdit *Edit3;
        TEdit *Edit2;
        TEdit *Edit1;
        TGroupBox *GroupBox2;
        TLabel *CLb;
        TLabel *CLg;
        TLabel *CLr;
        TEdit *Edit_factor;
        TUpDown *UpDown1;
        TEdit *EditB;
        TEdit *EditG;
        TEdit *EditR;
        TUpDown *UpDownB;
        TUpDown *UpDownG;
        TUpDown *UpDownR;
        TBitBtn *BitBtn1;
        TLabel *Label7;
        TLabel *Label8;
        TRadioGroup *RadioGroup1;
        TCheckBox *CheckBox_mode;
private:	// User declarations
public:		// User declarations
        __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
