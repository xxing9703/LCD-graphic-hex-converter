object Form2: TForm2
  Left = 971
  Top = 137
  Width = 1004
  Height = 586
  Caption = '文本输出'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 996
    Height = 480
    Align = alTop
    TabOrder = 0
    object Memo1: TMemo
      Left = 0
      Top = 0
      Width = 992
      Height = 476
      Align = alClient
      Lines.Strings = (
        '')
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
  object BT_output: TButton
    Left = 328
    Top = 504
    Width = 99
    Height = 41
    Caption = '输出文本'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = BT_outputClick
  end
  object BitBtn1: TBitBtn
    Left = 512
    Top = 504
    Width = 99
    Height = 41
    Caption = '&关闭'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    Kind = bkClose
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'txt'
    Filter = 
      'Text file (.txt)|*.txt|DAT file (.dat)|*.dat|ASM file (.asm)|*.a' +
      'sm'
    Left = 8
    Top = 464
  end
end
