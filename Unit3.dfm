object Form3: TForm3
  Left = 574
  Top = 406
  Width = 522
  Height = 406
  Caption = '����'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 9
    Width = 249
    Height = 145
    Caption = '�ı������ʽ'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = '������'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 64
      Height = 16
      Caption = '����ǰ׺'
    end
    object Label2: TLabel
      Left = 8
      Top = 48
      Width = 64
      Height = 16
      Caption = '���ݺ�׺'
    end
    object Label3: TLabel
      Left = 8
      Top = 72
      Width = 48
      Height = 16
      Caption = '��ǰ׺'
    end
    object Label4: TLabel
      Left = 8
      Top = 96
      Width = 48
      Height = 16
      Caption = '�к�׺'
    end
    object Label5: TLabel
      Left = 8
      Top = 120
      Width = 48
      Height = 16
      Caption = 'ע�ͷ�'
    end
    object Label6: TLabel
      Left = 144
      Top = 24
      Width = 64
      Height = 16
      Caption = 'ÿ���ֽ�'
    end
    object CheckBox1: TCheckBox
      Left = 144
      Top = 56
      Width = 89
      Height = 17
      Caption = '���걣��'
      Checked = True
      State = cbChecked
      TabOrder = 6
    end
    object Edit6: TEdit
      Left = 210
      Top = 24
      Width = 31
      Height = 24
      TabOrder = 5
      Text = '32'
    end
    object Edit5: TEdit
      Left = 79
      Top = 117
      Width = 56
      Height = 24
      TabOrder = 4
      Text = ';;'
    end
    object Edit4: TEdit
      Left = 79
      Top = 93
      Width = 56
      Height = 24
      TabOrder = 3
    end
    object Edit3: TEdit
      Left = 79
      Top = 69
      Width = 56
      Height = 24
      TabOrder = 2
      Text = ' DB '
    end
    object Edit2: TEdit
      Left = 79
      Top = 45
      Width = 56
      Height = 24
      TabOrder = 1
      Text = ','
    end
    object Edit1: TEdit
      Left = 79
      Top = 21
      Width = 56
      Height = 24
      TabOrder = 0
      Text = '0x'
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 169
    Width = 249
    Height = 144
    Caption = 'ͼ����������'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = '����'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object CLb: TLabel
      Left = 12
      Top = 64
      Width = 16
      Height = 16
      Hint = '��������ɫ��ֵ'
      AutoSize = False
      Color = clBlue
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -48
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object CLg: TLabel
      Left = 12
      Top = 88
      Width = 16
      Height = 16
      Hint = '��������ɫ��ֵ'
      AutoSize = False
      Color = clGreen
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -48
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object CLr: TLabel
      Left = 12
      Top = 112
      Width = 16
      Height = 16
      Hint = '��������ɫ��ֵ'
      AutoSize = False
      Color = clRed
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -48
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object Label7: TLabel
      Left = 16
      Top = 32
      Width = 64
      Height = 16
      Caption = '��ɫ��ֵ'
    end
    object Label8: TLabel
      Left = 112
      Top = 32
      Width = 64
      Height = 16
      Caption = '��С����'
    end
    object Edit_factor: TEdit
      Left = 115
      Top = 72
      Width = 46
      Height = 24
      Hint = '��������С����'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      Text = '1'
    end
    object UpDown1: TUpDown
      Left = 161
      Top = 72
      Width = 16
      Height = 24
      Associate = Edit_factor
      Min = 1
      Max = 32
      Position = 1
      TabOrder = 0
      Wrap = False
    end
    object EditB: TEdit
      Left = 40
      Top = 64
      Width = 32
      Height = 19
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      Text = '200'
    end
    object EditG: TEdit
      Left = 40
      Top = 88
      Width = 32
      Height = 19
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      Text = '255'
    end
    object EditR: TEdit
      Left = 40
      Top = 112
      Width = 32
      Height = 19
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      Text = '255'
    end
    object UpDownB: TUpDown
      Left = 72
      Top = 64
      Width = 16
      Height = 19
      Associate = EditB
      Min = 0
      Max = 255
      Increment = 10
      Position = 200
      TabOrder = 5
      Wrap = False
    end
    object UpDownG: TUpDown
      Left = 72
      Top = 88
      Width = 16
      Height = 19
      Associate = EditG
      Min = 0
      Max = 255
      Increment = 10
      Position = 255
      TabOrder = 6
      Wrap = False
    end
    object UpDownR: TUpDown
      Left = 72
      Top = 112
      Width = 16
      Height = 19
      Associate = EditR
      Min = 0
      Max = 255
      Increment = 10
      Position = 255
      TabOrder = 7
      Wrap = False
    end
  end
  object BitBtn1: TBitBtn
    Left = 232
    Top = 328
    Width = 89
    Height = 33
    TabOrder = 2
    Kind = bkOK
  end
  object RadioGroup1: TRadioGroup
    Left = 296
    Top = 16
    Width = 193
    Height = 137
    Caption = 'ȡģ����'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = '����'
    Font.Style = []
    ItemIndex = 0
    Items.Strings = (
      '����ȡģ, bit7-0'
      '����ȡģ, bit7-0'
      '����ȡģ, bit0-7'
      '����ȡģ, bit0-7')
    ParentFont = False
    TabOrder = 3
  end
  object CheckBox_mode: TCheckBox
    Left = 304
    Top = 184
    Width = 57
    Height = 17
    Caption = '���'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = '����'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
end
