object ManageTeamForm: TManageTeamForm
  Left = 496
  Top = 212
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077' '#1082#1086#1084#1072#1085#1076#1086#1081
  ClientHeight = 257
  ClientWidth = 642
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
  object LabelSchool: TLabel
    Left = 8
    Top = 8
    Width = 273
    Height = 17
    AutoSize = False
  end
  object Label2: TLabel
    Left = 360
    Top = 8
    Width = 273
    Height = 17
    AutoSize = False
    Caption = #1058#1077#1082#1091#1097#1080#1081' '#1089#1086#1089#1090#1072#1074' '#1082#1086#1084#1072#1085#1076#1099
  end
  object SourceGrid: TStringGrid
    Left = 8
    Top = 24
    Width = 273
    Height = 225
    ColCount = 2
    DefaultRowHeight = 18
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goRowSelect]
    TabOrder = 0
  end
  object TargetGrid: TStringGrid
    Left = 360
    Top = 24
    Width = 273
    Height = 225
    ColCount = 2
    DefaultRowHeight = 18
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goRowSelect]
    TabOrder = 1
  end
  object ButtonAdd: TButton
    Left = 288
    Top = 40
    Width = 65
    Height = 33
    Caption = '>>'
    TabOrder = 2
    OnClick = ButtonAddClick
  end
  object ButtonRemove: TButton
    Left = 288
    Top = 88
    Width = 65
    Height = 33
    Caption = '<<'
    TabOrder = 3
    OnClick = ButtonRemoveClick
  end
  object ButtonOK: TButton
    Left = 288
    Top = 192
    Width = 65
    Height = 33
    Caption = 'OK'
    Default = True
    TabOrder = 4
    OnClick = ButtonOKClick
  end
end
