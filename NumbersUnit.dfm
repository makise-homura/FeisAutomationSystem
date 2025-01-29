object NumbersForm: TNumbersForm
  Left = 400
  Top = 264
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1057#1086#1079#1076#1072#1085#1080#1077' '#1089#1083#1091#1078#1077#1073#1085#1099#1093' '#1092#1072#1081#1083#1086#1074' '#1092#1077#1096#1072
  ClientHeight = 487
  ClientWidth = 622
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupNumbers: TGroupBox
    Left = 8
    Top = 8
    Width = 609
    Height = 49
    Caption = ' '#1053#1086#1084#1077#1088#1082#1080' '#1076#1083#1103' '#1091#1095#1072#1089#1090#1085#1080#1082#1086#1074' '
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 185
      Height = 21
      Hint = 
        #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1079#1072#1087#1072#1089#1085#1099#1093' '#1085#1086#1084#1077#1088#1082#1086#1074' '#1076#1083#1103' '#1090#1072#1085#1094#1086#1088#1086#1074', '#1079#1072#1103#1074#1080#1074#1096#1080#1093#1089#1103' '#1085#1072' '#1092#1077#1096' '#1087#1086 +
        #1089#1083#1077' '#1086#1082#1086#1085#1095#1072#1085#1080#1103' '#1088#1077#1075#1080#1089#1090#1088#1072#1094#1080#1080
      AutoSize = False
      Caption = #1056#1077#1079#1077#1088#1074#1085#1099#1093' '#1085#1086#1084#1077#1088#1082#1086#1074': '#1089#1086#1083#1100#1085#1099#1093':'
      ParentShowHint = False
      ShowHint = True
      Layout = tlCenter
    end
    object Label2: TLabel
      Left = 256
      Top = 16
      Width = 81
      Height = 21
      Hint = 
        #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1079#1072#1087#1072#1089#1085#1099#1093' '#1085#1086#1084#1077#1088#1082#1086#1074' '#1076#1083#1103' '#1082#1086#1084#1072#1085#1076', '#1079#1072#1103#1074#1080#1074#1096#1080#1093#1089#1103' '#1085#1072' '#1092#1077#1096' '#1087#1086#1089#1083 +
        #1077' '#1086#1082#1086#1085#1095#1072#1085#1080#1103' '#1088#1077#1075#1080#1089#1090#1088#1072#1094#1080#1080
      AutoSize = False
      Caption = ', '#1082#1086#1084#1072#1085#1076':'
      ParentShowHint = False
      ShowHint = True
      Layout = tlCenter
    end
    object EditAdditionalSolo: TEdit
      Left = 200
      Top = 16
      Width = 49
      Height = 21
      Hint = 
        #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1079#1072#1087#1072#1089#1085#1099#1093' '#1085#1086#1084#1077#1088#1082#1086#1074' '#1076#1083#1103' '#1090#1072#1085#1094#1086#1088#1086#1074', '#1079#1072#1103#1074#1080#1074#1096#1080#1093#1089#1103' '#1085#1072' '#1092#1077#1096' '#1087#1086 +
        #1089#1083#1077' '#1086#1082#1086#1085#1095#1072#1085#1080#1103' '#1088#1077#1075#1080#1089#1090#1088#1072#1094#1080#1080
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      Text = '0'
    end
    object ButtonCreateNumbers: TButton
      Left = 392
      Top = 16
      Width = 209
      Height = 25
      Hint = 
        #1057#1086#1079#1076#1072#1090#1100' excel-'#1092#1072#1081#1083', '#1089#1086#1076#1077#1088#1078#1072#1097#1080#1081' '#1085#1086#1084#1077#1088#1082#1080' '#1076#1083#1103' '#1090#1072#1085#1094#1086#1088#1086#1074' '#1074' '#1089#1086#1086#1090#1074#1077#1090#1089#1090#1074 +
        #1080#1080' '#1089' '#1079#1072#1103#1074#1083#1077#1085#1085#1099#1084#1080' '#1080#1084#1080' '#1090#1072#1085#1094#1072#1084#1080', '#1075#1086#1090#1086#1074#1099#1081' '#1082' '#1087#1077#1095#1072#1090#1080
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1092#1072#1081#1083' '#1089' '#1085#1086#1084#1077#1088#1082#1072#1084#1080
      Default = True
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = ButtonCreateNumbersClick
    end
    object EditAdditionalTeam: TEdit
      Left = 328
      Top = 16
      Width = 49
      Height = 21
      Hint = 
        #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1079#1072#1087#1072#1089#1085#1099#1093' '#1085#1086#1084#1077#1088#1082#1086#1074' '#1076#1083#1103' '#1082#1086#1084#1072#1085#1076', '#1079#1072#1103#1074#1080#1074#1096#1080#1093#1089#1103' '#1085#1072' '#1092#1077#1096' '#1087#1086#1089#1083 +
        #1077' '#1086#1082#1086#1085#1095#1072#1085#1080#1103' '#1088#1077#1075#1080#1089#1090#1088#1072#1094#1080#1080
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      Text = '0'
    end
  end
  object GroupSchedule: TGroupBox
    Left = 8
    Top = 64
    Width = 609
    Height = 377
    Caption = ' '#1055#1088#1086#1095#1080#1077' '#1084#1072#1090#1077#1088#1080#1072#1083#1099' '#1076#1083#1103' '#1092#1077#1096#1072
    TabOrder = 1
    object ButtonCreateSchedule: TButton
      Left = 8
      Top = 24
      Width = 193
      Height = 25
      Hint = 
        #1057#1086#1079#1076#1072#1090#1100' '#1092#1072#1081#1083', '#1080#1079' '#1082#1086#1090#1086#1088#1086#1075#1086' '#1087#1086#1090#1086#1084' '#1074' excel-'#1077' '#1084#1086#1078#1085#1086' '#1073#1091#1076#1077#1090' '#1089#1082#1086#1084#1087#1086#1085#1086#1074#1072 +
        #1090#1100' '#1088#1072#1089#1087#1080#1089#1072#1085#1080#1077'. '#1042' '#1092#1072#1081#1083#1077' '#1074#1089#1077' '#1090#1072#1085#1094#1099' '#1089#1090#1072#1074#1103#1090#1089#1103' '#1085#1072' '#1089#1094#1077#1085#1091' '#1040', '#1085#1091#1078#1085#1086' '#1073#1091#1076#1077 +
        #1090' '#1080#1093' '#1088#1072#1089#1087#1088#1077#1076#1077#1083#1080#1090#1100' '#1087#1086' '#1089#1094#1077#1085#1072#1084' '#1080#1083#1080' '#1086#1073#1098#1077#1076#1080#1085#1080#1090#1100' '#1080#1093'.'
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1087#1088#1086#1077#1082#1090' '#1088#1072#1089#1087#1080#1089#1072#1085#1080#1103
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnClick = ButtonCreateScheduleClick
    end
    object ButtonCreateEmptyResults: TButton
      Left = 208
      Top = 24
      Width = 193
      Height = 25
      Hint = 
        #1057#1086#1079#1076#1072#1090#1100' '#1092#1072#1081#1083', '#1072#1085#1072#1083#1086#1075#1080#1095#1085#1099#1081' '#1090#1086#1084#1091', '#1074' '#1082#1086#1090#1086#1088#1099#1081' '#1074#1074#1086#1076#1080#1083#1080#1089#1100' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1099' '#1087 +
        #1088#1086#1096#1083#1099#1093' '#1092#1077#1096#1077#1081'. '#1055#1086#1089#1083#1077' '#1089#1086#1079#1076#1072#1085#1080#1103' '#1074#1089#1077' '#1089#1090#1088#1072#1085#1080#1094#1099' '#1101#1090#1086#1075#1086' '#1092#1072#1081#1083#1072' '#1085#1072#1076#1086' '#1089#1082#1086#1087#1080 +
        #1088#1086#1074#1072#1090#1100' '#1080' '#1074#1089#1090#1072#1074#1080#1090#1100' '#1074' excel-'#1092#1072#1081#1083', '#1089#1086#1076#1077#1088#1078#1072#1097#1080#1081' '#1084#1072#1082#1088#1086#1089#1099' '#1087#1086#1076#1089#1095#1077#1090#1072' ('#1085#1072#1087 +
        #1088#1080#1084#1077#1088', '#1086#1090' '#1086#1076#1085#1086#1075#1086' '#1080#1079' '#1087#1088#1086#1096#1083#1099#1093' '#1092#1077#1096#1077#1081').'
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1092#1086#1088#1084#1091' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1086#1074
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = ButtonCreateEmptyResultsClick
    end
    object ButtonCreateList: TButton
      Left = 408
      Top = 24
      Width = 193
      Height = 25
      Hint = 
        #1057#1086#1079#1076#1072#1090#1100' '#1090#1077#1082#1089#1090#1086#1074#1099#1081' '#1092#1072#1081#1083' '#1089#1086' '#1089#1087#1080#1089#1082#1086#1084' '#1091#1095#1072#1089#1090#1085#1080#1082#1086#1074', '#1082#1086#1090#1086#1088#1099#1081' '#1073#1091#1076#1077#1090' '#1080#1089#1087#1086 +
        #1083#1100#1079#1086#1074#1072#1085' '#1087#1088#1080' '#1089#1086#1079#1076#1072#1085#1080#1080' '#1073#1091#1082#1083#1077#1090#1072'. '#1069#1083#1077#1084#1077#1085#1090#1099' '#1089#1090#1088#1086#1082#1080' ('#1085#1086#1084#1077#1088', '#1092#1072#1084#1080#1083#1080#1103'/'#1080#1084 +
        #1103' '#1080' '#1096#1082#1086#1083#1072') '#1088#1072#1079#1076#1077#1083#1077#1085#1099' '#1090#1072#1073#1091#1083#1103#1094#1080#1103#1084#1080'.'
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1089#1087#1080#1089#1086#1082' '#1091#1095#1072#1089#1090#1085#1080#1082#1086#1074
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = ButtonCreateListClick
    end
    object ButtonCreateBPIO: TButton
      Left = 8
      Top = 56
      Width = 393
      Height = 25
      Hint = 
        #1057#1086#1079#1076#1072#1090#1100' '#1090#1077#1082#1089#1090#1086#1074#1099#1081' '#1092#1072#1081#1083' '#1089#1086' '#1089#1087#1080#1089#1082#1086#1084' '#1091#1095#1072#1089#1090#1085#1080#1082#1086#1074', '#1082#1086#1090#1086#1088#1099#1081' '#1073#1091#1076#1077#1090' '#1080#1089#1087#1086 +
        #1083#1100#1079#1086#1074#1072#1085' '#1087#1088#1080' '#1089#1086#1079#1076#1072#1085#1080#1080' '#1073#1091#1082#1083#1077#1090#1072'. '#1069#1083#1077#1084#1077#1085#1090#1099' '#1089#1090#1088#1086#1082#1080' ('#1085#1086#1084#1077#1088', '#1092#1072#1084#1080#1083#1080#1103'/'#1080#1084 +
        #1103' '#1080' '#1096#1082#1086#1083#1072') '#1088#1072#1079#1076#1077#1083#1077#1085#1099' '#1090#1072#1073#1091#1083#1103#1094#1080#1103#1084#1080'.'
      Caption = #1057#1086#1079#1076#1072#1090#1100' BPIO-'#1083#1080#1089#1090' '#1076#1083#1103' '#1087#1088#1086#1074#1077#1088#1082#1080' '#1088#1091#1082#1086#1074#1086#1076#1080#1090#1077#1083#1103#1084#1080' '#1096#1082#1086#1083
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      OnClick = ButtonCreateBPIOClick
    end
    object ButtonCreateSchools: TButton
      Left = 224
      Top = 344
      Width = 377
      Height = 25
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1089#1087#1080#1089#1086#1082' '#1087#1086' '#1096#1082#1086#1083#1072#1084
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      OnClick = ButtonCreateSchoolClick
    end
    object ButtonCreateStageLists: TButton
      Left = 408
      Top = 56
      Width = 193
      Height = 25
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1089#1090#1077#1081#1076#1078'-'#1083#1080#1089#1090#1099
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      OnClick = ButtonCreateStageListsClick
    end
    object GroupSchoolParam: TGroupBox
      Left = 8
      Top = 88
      Width = 593
      Height = 249
      Caption = ' '#1055#1072#1088#1072#1084#1077#1090#1088#1099' '
      TabOrder = 6
      object Label3: TLabel
        Left = 80
        Top = 12
        Width = 65
        Height = 13
        Caption = #1056#1077#1075#1080#1089#1090#1088#1072#1094#1080#1103
      end
      object Label4: TLabel
        Left = 160
        Top = 12
        Width = 45
        Height = 13
        Caption = #1057#1086#1083#1100#1085#1099#1081
      end
      object Label5: TLabel
        Left = 304
        Top = 12
        Width = 54
        Height = 13
        Caption = 'Premiership'
      end
      object Label7: TLabel
        Left = 232
        Top = 12
        Width = 53
        Height = 13
        Caption = #1060#1080#1075#1091#1088#1085#1099#1081
      end
      object Label6: TLabel
        Left = 368
        Top = 12
        Width = 66
        Height = 13
        Caption = 'Prelim/Champ'
      end
      object Label8: TLabel
        Left = 448
        Top = 12
        Width = 51
        Height = 13
        Caption = #1050#1091#1088#1089' '#1077#1074#1088#1086
      end
      object Label9: TLabel
        Left = 32
        Top = 36
        Width = 29
        Height = 13
        Caption = 'WIDA'
      end
      object Label10: TLabel
        Left = 32
        Top = 60
        Width = 46
        Height = 13
        Caption = #1053#1077' WIDA'
      end
      object Label11: TLabel
        Left = 520
        Top = 12
        Width = 50
        Height = 13
        Caption = #1041#1077#1079#1083#1080#1084#1080#1090
      end
      object Label12: TLabel
        Left = 192
        Top = 86
        Width = 29
        Height = 13
        Caption = 'WIDA'
      end
      object Label13: TLabel
        Left = 368
        Top = 86
        Width = 46
        Height = 13
        Caption = #1053#1077' WIDA'
      end
      object SpinCostReg: TCSpinEdit
        Left = 88
        Top = 32
        Width = 57
        Height = 22
        TabOrder = 0
        Value = 5
      end
      object SpinCostSolo: TCSpinEdit
        Left = 160
        Top = 32
        Width = 57
        Height = 22
        TabOrder = 1
        Value = 5
      end
      object SpinCostFigure: TCSpinEdit
        Left = 232
        Top = 32
        Width = 57
        Height = 22
        TabOrder = 2
        Value = 5
      end
      object SpinCostEuro: TCSpinEdit
        Left = 448
        Top = 32
        Width = 57
        Height = 22
        TabOrder = 5
        Value = 100
      end
      object SpinCostChamp: TCSpinEdit
        Left = 376
        Top = 32
        Width = 57
        Height = 22
        TabOrder = 4
        Value = 20
      end
      object SpinCostPremier: TCSpinEdit
        Left = 304
        Top = 32
        Width = 57
        Height = 22
        TabOrder = 3
        Value = 15
      end
      object SpinCostRegNW: TCSpinEdit
        Left = 88
        Top = 56
        Width = 57
        Height = 22
        TabOrder = 7
        Value = 6
      end
      object SpinCostSoloNW: TCSpinEdit
        Left = 160
        Top = 56
        Width = 57
        Height = 22
        TabOrder = 8
        Value = 6
      end
      object SpinCostFigureNW: TCSpinEdit
        Left = 232
        Top = 56
        Width = 57
        Height = 22
        TabOrder = 9
        Value = 6
      end
      object SpinCostPremierNW: TCSpinEdit
        Left = 304
        Top = 56
        Width = 57
        Height = 22
        TabOrder = 10
        Value = 17
      end
      object SpinCostChampNW: TCSpinEdit
        Left = 376
        Top = 56
        Width = 57
        Height = 22
        TabOrder = 11
        Value = 23
      end
      object SpinCostEuroNW: TCSpinEdit
        Left = 448
        Top = 56
        Width = 57
        Height = 22
        TabOrder = 12
        Value = 100
      end
      object SpinCostUnlim: TCSpinEdit
        Left = 520
        Top = 32
        Width = 57
        Height = 22
        Hint = #1042' '#1077#1074#1088#1086'; 0 '#1077#1089#1083#1080' '#1073#1077#1079#1083#1080#1084#1080#1090#1072' '#1085#1077#1090
        ParentShowHint = False
        ShowHint = True
        TabOrder = 6
        Value = 45
      end
      object SpinCostUnlimNW: TCSpinEdit
        Left = 520
        Top = 56
        Width = 57
        Height = 22
        Hint = #1042' '#1077#1074#1088#1086'; 0 '#1077#1089#1083#1080' '#1073#1077#1079#1083#1080#1084#1080#1090#1072' '#1085#1077#1090
        ParentShowHint = False
        ShowHint = True
        TabOrder = 13
        Value = 50
      end
      object ListWIDA: TListBox
        Left = 8
        Top = 104
        Width = 281
        Height = 137
        ItemHeight = 13
        TabOrder = 14
      end
      object ListNonWIDA: TListBox
        Left = 304
        Top = 104
        Width = 281
        Height = 137
        ItemHeight = 13
        TabOrder = 16
      end
      object ButtonToWIDA: TButton
        Left = 304
        Top = 84
        Width = 57
        Height = 17
        Caption = '<<'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 17
        OnClick = ButtonToWIDAClick
      end
      object ButtonFromWIDA: TButton
        Left = 232
        Top = 84
        Width = 57
        Height = 17
        Caption = '>>'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 15
        OnClick = ButtonFromWIDAClick
      end
    end
    object CheckBoxSortSchools: TCheckBox
      Left = 16
      Top = 344
      Width = 201
      Height = 25
      Caption = #1057#1086#1088#1090#1080#1088#1086#1074#1072#1090#1100' '#1087#1086' '#1096#1082#1086#1083#1072#1084
      Checked = True
      State = cbChecked
      TabOrder = 7
    end
  end
  object ButtonClose: TButton
    Left = 8
    Top = 448
    Width = 609
    Height = 33
    Hint = #1047#1072#1082#1088#1099#1090#1100' '#1086#1082#1085#1086
    Caption = #1047#1072#1082#1088#1099#1090#1100
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = ButtonCloseClick
  end
  object PanelWarning: TPanel
    Left = 168
    Top = 280
    Width = 289
    Height = 89
    Color = clSkyBlue
    TabOrder = 3
    Visible = False
  end
  object SaveDialogNumbers: TSaveDialog
    DefaultExt = 'xls'
    FileName = 'Numbers.xls'
    Filter = #1060#1072#1081#1083#1099' Excel (*.xls)|*.xls|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = #1060#1072#1081#1083' '#1076#1083#1103' '#1085#1086#1084#1077#1088#1082#1086#1074
    Left = 16
    Top = 56
  end
  object SaveDialogSchedule: TSaveDialog
    DefaultExt = 'xls'
    FileName = 'Schedule.xls'
    Filter = #1060#1072#1081#1083#1099' Excel (*.xls)|*.xls|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = #1060#1072#1081#1083' '#1076#1083#1103' '#1087#1088#1086#1077#1082#1090#1072' '#1088#1072#1089#1087#1080#1089#1072#1085#1080#1103
    Left = 16
    Top = 128
  end
  object SaveDialogEmptyResults: TSaveDialog
    DefaultExt = 'xls'
    FileName = 'EmptyForm.xls'
    Filter = #1060#1072#1081#1083#1099' Excel (*.xls)|*.xls|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = #1060#1072#1081#1083' '#1076#1083#1103' '#1090#1072#1073#1083#1080#1094#1099' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1086#1074
    Left = 16
    Top = 160
  end
  object SaveDialogList: TSaveDialog
    DefaultExt = 'txt'
    FileName = 'List.txt'
    Filter = #1058#1077#1082#1089#1090#1086#1074#1099#1077' '#1092#1072#1081#1083#1099' (*.txt)|*.txt|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = #1060#1072#1081#1083' '#1076#1083#1103' '#1089#1087#1080#1089#1082#1072' '#1091#1095#1072#1089#1090#1085#1080#1082#1086#1074
    Left = 16
    Top = 192
  end
  object SaveDialogBPIO: TSaveDialog
    DefaultExt = 'xls'
    FileName = 'BPIO.xls'
    Filter = #1060#1072#1081#1083#1099' Excel (*.xls)|*.xls|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = #1060#1072#1081#1083' '#1076#1083#1103' '#1090#1072#1073#1083#1080#1094#1099' BPIO'
    Left = 16
    Top = 224
  end
  object SaveDialogSchools: TSaveDialog
    DefaultExt = 'xls'
    FileName = 'Schools.xls'
    Filter = #1060#1072#1081#1083#1099' Excel (*.xls)|*.xls|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = #1060#1072#1081#1083' '#1076#1083#1103' '#1090#1072#1073#1083#1080#1094#1099' '#1087#1086' '#1096#1082#1086#1083#1072#1084
    Left = 16
    Top = 256
  end
  object SaveDialogStageLists: TSaveDialog
    DefaultExt = 'xls'
    FileName = 'StageLists.xls'
    Filter = #1060#1072#1081#1083#1099' Excel (*.xls)|*.xls|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = #1060#1072#1081#1083' '#1076#1083#1103' '#1089#1090#1077#1081#1076#1078'-'#1083#1080#1089#1090#1086#1074
    Left = 16
    Top = 408
  end
end
