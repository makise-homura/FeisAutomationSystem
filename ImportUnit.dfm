object ImportForm: TImportForm
  Left = 359
  Top = 199
  Width = 880
  Height = 712
  Caption = #1048#1084#1087#1086#1088#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1080' '#1089' '#1089#1072#1081#1090#1072' WIDA'
  Color = clBtnFace
  Constraints.MaxWidth = 880
  Constraints.MinHeight = 500
  Constraints.MinWidth = 880
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  DesignSize = (
    872
    685)
  PixelsPerInch = 96
  TextHeight = 13
  object ListGrid: TStringGrid
    Left = 16
    Top = 16
    Width = 841
    Height = 473
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 4
    DefaultRowHeight = 18
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goRowSizing, goColSizing, goEditing, goTabs, goAlwaysShowEditor, goThumbTracking]
    TabOrder = 0
  end
  object ButtonPanel: TGroupBox
    Left = 16
    Top = 591
    Width = 337
    Height = 81
    Anchors = [akLeft, akBottom]
    Caption = ' '#1048#1084#1087#1086#1088#1090' '#1092#1072#1081#1083#1072' '
    TabOrder = 1
    object ImportListButton: TButton
      Left = 16
      Top = 24
      Width = 89
      Height = 41
      Caption = 'DLES'
      TabOrder = 0
      OnClick = ImportListButtonClick
    end
    object ImportSoloButton: TButton
      Left = 112
      Top = 24
      Width = 105
      Height = 41
      Caption = 'Dancers Report'
      TabOrder = 1
      OnClick = ImportSoloButtonClick
    end
    object AddFromRawButton: TButton
      Left = 224
      Top = 24
      Width = 97
      Height = 41
      Caption = 'Raw-'#1076#1086#1080#1084#1087#1086#1088#1090
      TabOrder = 2
      OnClick = AddFromRawButtonClick
    end
  end
  object ListChooseGroup: TRadioGroup
    Left = 16
    Top = 535
    Width = 841
    Height = 49
    Anchors = [akLeft, akBottom]
    Caption = ' '#1055#1088#1086#1089#1084#1086#1090#1088#1077#1090#1100' '#1089#1087#1080#1089#1086#1082' '
    Columns = 3
    ItemIndex = 0
    Items.Strings = (
      #1058#1072#1085#1094#1086#1088#1086#1074', '#1079#1072#1103#1074#1080#1074#1096#1080#1093#1089#1103' '#1085#1072' '#1092#1077#1096
      #1047#1072#1103#1074#1083#1077#1085#1085#1099#1093' '#1089#1086#1083#1100#1085#1099#1093' '#1090#1072#1085#1094#1077#1074
      #1047#1072#1103#1074#1083#1077#1085#1085#1099#1093' '#1075#1088#1091#1087#1087#1086#1074#1099#1093' '#1090#1072#1085#1094#1077#1074)
    TabOrder = 2
    OnClick = ListChooseGroupClick
  end
  object AddLineButton: TButton
    Left = 16
    Top = 503
    Width = 161
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1091#1095#1072#1089#1090#1085#1080#1082#1072
    TabOrder = 3
    OnClick = AddLineButtonClick
  end
  object DeleteLineButton: TButton
    Left = 184
    Top = 503
    Width = 161
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1091#1095#1072#1089#1090#1085#1080#1082#1072
    TabOrder = 4
    OnClick = DeleteLineButtonClick
  end
  object ExitButton: TButton
    Left = 688
    Top = 503
    Width = 169
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1043#1086#1090#1086#1074#1086
    Default = True
    TabOrder = 5
    OnClick = ExitButtonClick
  end
  object SoloGrid: TStringGrid
    Left = 16
    Top = 16
    Width = 841
    Height = 473
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 17
    DefaultRowHeight = 18
    FixedCols = 4
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSizing, goColSizing, goColMoving, goEditing, goTabs, goAlwaysShowEditor, goThumbTracking]
    TabOrder = 6
    Visible = False
  end
  object GroupGrid: TStringGrid
    Left = 16
    Top = 16
    Width = 841
    Height = 473
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 4
    DefaultRowHeight = 18
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSizing, goColSizing, goColMoving, goEditing, goTabs, goAlwaysShowEditor, goThumbTracking]
    TabOrder = 7
    Visible = False
  end
  object DeleteFigureButton: TButton
    Left = 184
    Top = 503
    Width = 161
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1082#1086#1084#1072#1085#1076#1091
    TabOrder = 8
    Visible = False
    OnClick = DeleteFigureButtonClick
  end
  object AddFigureButton: TButton
    Left = 16
    Top = 503
    Width = 161
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1082#1086#1084#1072#1085#1076#1091
    TabOrder = 9
    Visible = False
    OnClick = AddFigureButtonClick
  end
  object CheckRegButton: TButton
    Left = 368
    Top = 599
    Width = 489
    Height = 73
    Hint = 
      #1055#1088#1086#1074#1077#1088#1082#1072' '#1074#1089#1077#1081' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1080', '#1074#1074#1077#1076#1077#1085#1085#1086#1081' '#1074' '#1090#1072#1073#1083#1080#1094#1099'. '#1053#1072#1078#1084#1080#1090#1077' '#1101#1090#1091' '#1082#1085#1086#1087#1082 +
      #1091' '#1087#1077#1088#1077#1076' '#1090#1077#1084', '#1082#1072#1082' '#1087#1088#1080#1089#1090#1091#1087#1072#1090#1100' '#1082' '#1089#1083#1077#1076#1091#1102#1097#1080#1084' '#1096#1072#1075#1072#1084' '#1087#1086#1076#1075#1086#1090#1086#1074#1082#1080'. '#1044#1083#1103' '#1091#1089 +
      #1087#1077#1096#1085#1086#1075#1086' '#1087#1088#1086#1093#1086#1078#1076#1077#1085#1080#1103' '#1087#1088#1086#1074#1077#1088#1082#1080' '#1085#1077#1086#1073#1093#1086#1076#1080#1084#1086' '#1090#1072#1082#1078#1077' '#1079#1072#1076#1072#1090#1100' '#1074#1086#1079#1088#1072#1089#1090#1085#1099#1077' ' +
      #1075#1088#1091#1087#1087#1099' '#1074' '#1086#1082#1085#1077' "'#1088#1072#1079#1073#1080#1074#1082#1072' '#1085#1072' '#1075#1088#1091#1087#1087#1099'".'
    Anchors = [akLeft, akBottom]
    Caption = 
      #1055#1088#1086#1074#1077#1088#1080#1090#1100' '#1087#1088#1072#1074#1080#1083#1100#1085#1086#1089#1090#1100' '#1089#1087#1080#1089#1082#1086#1074' '#1090#1072#1085#1094#1086#1088#1086#1074', '#1082#1086#1084#1072#1085#1076' '#1080' '#1088#1077#1075#1080#1089#1090#1088#1072#1094#1080#1081' '#1085#1072 +
      ' '#1090#1072#1085#1094#1099
    ParentShowHint = False
    ShowHint = True
    TabOrder = 10
    OnClick = CheckRegButtonClick
  end
  object ManageTeamButton: TButton
    Left = 352
    Top = 503
    Width = 161
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100' '#1082#1086#1084#1072#1085#1076#1091
    TabOrder = 11
    Visible = False
    OnClick = ManageTeamButtonClick
  end
  object ResortButton: TButton
    Left = 520
    Top = 503
    Width = 161
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1055#1077#1088#1077#1089#1086#1088#1090#1080#1088#1086#1074#1072#1090#1100
    TabOrder = 12
    OnClick = ResortButtonClick
  end
  object AddNameEdit: TEdit
    Left = 352
    Top = 503
    Width = 161
    Height = 21
    Anchors = [akLeft, akBottom]
    TabOrder = 13
    OnChange = AddNameEditChange
  end
  object ResortFigureButton: TButton
    Left = 520
    Top = 496
    Width = 161
    Height = 17
    Anchors = [akLeft, akBottom]
    Caption = #1056#1072#1079#1073#1080#1090#1100' '#1087#1086' '#1074#1086#1079#1088#1072#1089#1090#1072#1084
    TabOrder = 15
    Visible = False
    OnClick = ResortFigureButtonClick
  end
  object QualificationCheckBox: TCheckBox
    Left = 552
    Top = 520
    Width = 97
    Height = 17
    Hint = 
      #1042' '#1086#1073#1099#1095#1085#1099#1093' '#1082#1077#1081#1083#1080' '#1075#1088#1091#1087#1087#1099' U12, U17, U30 '#1080' O30. '#1042' '#1082#1074#1072#1083#1080#1092#1080#1082#1072#1094#1080#1086#1085#1085#1099#1093' -' +
      ' U11, U16, U29, O29.'
    Anchors = [akLeft, akBottom]
    Caption = #1050#1074#1072#1083#1080#1092#1080#1082#1072#1094#1080#1103
    TabOrder = 16
    Visible = False
  end
  object ImportWarning: TPanel
    Left = 296
    Top = 519
    Width = 297
    Height = 97
    Anchors = [akLeft, akBottom]
    Caption = #1042#1085#1080#1084#1072#1085#1080#1077', '#1087#1088#1086#1080#1079#1074#1086#1076#1080#1090#1089#1103' '#1080#1084#1087#1086#1088#1090'...'
    Color = clSkyBlue
    TabOrder = 14
    Visible = False
  end
  object ImportDialog: TOpenDialog
    DefaultExt = 'xls'
    Filter = #1060#1072#1081#1083#1099' Excel|*.xls|'#1042#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1092#1072#1081#1083' '#1076#1083#1103' '#1080#1084#1087#1086#1088#1090#1080#1088#1086#1074#1072#1085#1080#1103
    Left = 16
    Top = 352
  end
end
