object ProtocolSelectForm: TProtocolSelectForm
  Left = 192
  Top = 107
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1089#1091#1076#1100#1102' '#1080' '#1088#1072#1091#1085#1076' '#1076#1083#1103'  '#1087#1086#1076#1089#1095#1105#1090#1072
  ClientHeight = 121
  ClientWidth = 319
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object JudgeGroup: TRadioGroup
    Left = 8
    Top = 8
    Width = 81
    Height = 105
    Caption = ' '#1057#1091#1076#1100#1103' '
    ItemIndex = 0
    Items.Strings = (
      #1057#1091#1076#1100#1103' 1'
      #1057#1091#1076#1100#1103' 2'
      #1057#1091#1076#1100#1103' 3')
    TabOrder = 0
  end
  object RoundGroup: TRadioGroup
    Left = 104
    Top = 8
    Width = 97
    Height = 105
    Caption = ' '#1056#1072#1091#1085#1076' '
    ItemIndex = 0
    Items.Strings = (
      #1056#1072#1091#1085#1076' 1'
      #1056#1072#1091#1085#1076' 2'
      #1056#1072#1091#1085#1076' 3'
      #1056#1072#1091#1085#1076' 4')
    TabOrder = 1
  end
  object ButtonOk: TButton
    Left = 216
    Top = 16
    Width = 97
    Height = 33
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
  object ButtonCancel: TButton
    Left = 216
    Top = 56
    Width = 97
    Height = 33
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 3
  end
end
