object DeclarationForm: TDeclarationForm
  Left = 278
  Top = 159
  Width = 873
  Height = 644
  ActiveControl = ButtonClose
  Caption = #1053#1072#1075#1088#1072#1078#1076#1077#1085#1080#1077
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    865
    617)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 8
    Width = 97
    Height = 21
    AutoSize = False
    Caption = #1056#1072#1079#1084#1077#1088' '#1096#1088#1080#1092#1090#1072':'
    Layout = tlCenter
  end
  object ButtonClose: TButton
    Left = 752
    Top = 8
    Width = 105
    Height = 25
    Anchors = [akTop, akRight]
    Caption = #1047#1072#1082#1088#1099#1090#1100
    Default = True
    TabOrder = 0
    OnClick = ButtonCloseClick
  end
  object EditFontSize: TEdit
    Left = 120
    Top = 8
    Width = 33
    Height = 21
    TabOrder = 1
    Text = '20'
  end
  object ButtonApply: TButton
    Left = 160
    Top = 8
    Width = 105
    Height = 22
    Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
    TabOrder = 2
    OnClick = ButtonApplyClick
  end
  object ConclusionText: TRichEdit
    Left = 8
    Top = 40
    Width = 849
    Height = 569
    Anchors = [akLeft, akTop, akRight, akBottom]
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Calibri'
    Font.Style = [fsBold]
    Lines.Strings = (
      'ConclusionText')
    ParentFont = False
    TabOrder = 3
  end
end
