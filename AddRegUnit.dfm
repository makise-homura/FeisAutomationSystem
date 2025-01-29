object AddRegForm: TAddRegForm
  Left = 229
  Top = 107
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1088#1077#1075#1080#1089#1090#1088#1072#1094#1080#1102' '#1085#1072' '#1090#1072#1085#1077#1094
  ClientHeight = 440
  ClientWidth = 571
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
  object Label1: TLabel
    Left = 8
    Top = 368
    Width = 553
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1085#1077#1079#1072#1088#1077#1075#1080#1089#1090#1088#1080#1088#1086#1074#1072#1085#1085#1086#1075#1086' '#1091#1095#1072#1089#1090#1085#1080#1082#1072' '#1080' '#1085#1072#1078#1084#1080#1090#1077' "'#1044#1086#1073#1072#1074#1080#1090#1100'"'
    Layout = tlCenter
  end
  object DancersGrid: TStringGrid
    Left = 8
    Top = 8
    Width = 553
    Height = 345
    ColCount = 4
    DefaultRowHeight = 18
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSizing, goColSizing, goRowSelect, goThumbTracking]
    TabOrder = 0
  end
  object AddButton: TButton
    Left = 64
    Top = 392
    Width = 161
    Height = 33
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    TabOrder = 1
    OnClick = AddButtonClick
  end
  object CancelButton: TButton
    Left = 344
    Top = 392
    Width = 161
    Height = 33
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    Default = True
    TabOrder = 2
    OnClick = CancelButtonClick
  end
end
