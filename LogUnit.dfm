object LogForm: TLogForm
  Left = 280
  Top = 107
  Width = 868
  Height = 642
  Anchors = [akLeft, akTop, akRight, akBottom]
  Caption = #1057#1087#1080#1089#1086#1082' '#1086#1096#1080#1073#1086#1082
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    860
    615)
  PixelsPerInch = 96
  TextHeight = 13
  object ButtonOK: TButton
    Left = 8
    Top = 554
    Width = 842
    Height = 49
    Anchors = [akLeft, akRight, akBottom]
    Caption = #1047#1072#1082#1088#1099#1090#1100
    Default = True
    TabOrder = 0
    OnClick = ButtonOKClick
  end
  object LogMemo: TMemo
    Left = 8
    Top = 8
    Width = 842
    Height = 539
    Anchors = [akLeft, akTop, akRight, akBottom]
    Lines.Strings = (
      'LogMemo')
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 1
    WordWrap = False
  end
end
