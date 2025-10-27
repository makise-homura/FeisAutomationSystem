object FeisEnterForm: TFeisEnterForm
  Left = 299
  Top = 178
  Width = 817
  Height = 640
  Caption = #1042#1074#1086#1076' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1086#1074' '#1092#1077#1096#1072
  Color = clBtnFace
  Constraints.MinHeight = 640
  Constraints.MinWidth = 817
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  DesignSize = (
    809
    613)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 184
    Top = 576
    Width = 41
    Height = 25
    Anchors = [akLeft, akBottom]
    AutoSize = False
    Caption = #1053#1086#1084#1077#1088':'
    Layout = tlCenter
  end
  object Label2: TLabel
    Left = 280
    Top = 576
    Width = 33
    Height = 25
    Anchors = [akLeft, akBottom]
    AutoSize = False
    Caption = #1048#1084#1103':'
    Layout = tlCenter
  end
  object GroupBoxDances: TGroupBox
    Left = 8
    Top = 8
    Width = 793
    Height = 233
    Caption = ' '#1042#1099#1073#1086#1088' '#1090#1072#1085#1094#1072' '
    TabOrder = 0
    object ButtonJump23: TButton
      Left = 16
      Top = 24
      Width = 145
      Height = 24
      Caption = 'Jump 2 3'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = ButtonJump23Click
    end
    object ButtonTrebReel: TButton
      Left = 16
      Top = 48
      Width = 145
      Height = 24
      Caption = 'Treble Reel'
      TabOrder = 1
      OnClick = ButtonTrebReelClick
    end
    object ButtonBegReel: TButton
      Left = 176
      Top = 24
      Width = 145
      Height = 24
      Caption = 'Beginners Reel'
      TabOrder = 2
      OnClick = ButtonBegReelClick
    end
    object ButtonBegSingle: TButton
      Left = 176
      Top = 96
      Width = 145
      Height = 24
      Caption = 'Beginners Single Jig'
      TabOrder = 5
      OnClick = ButtonBegSingleClick
    end
    object ButtonBegLight: TButton
      Left = 176
      Top = 48
      Width = 145
      Height = 24
      Caption = 'Beginners Light Jig'
      TabOrder = 3
      OnClick = ButtonBegLightClick
    end
    object ButtonBegSlip: TButton
      Left = 176
      Top = 72
      Width = 145
      Height = 24
      Caption = 'Beginners Slip Jig'
      TabOrder = 4
      OnClick = ButtonBegSlipClick
    end
    object ButtonBegTreble: TButton
      Left = 176
      Top = 120
      Width = 145
      Height = 24
      Caption = 'Beginners Treble Jig'
      TabOrder = 6
      OnClick = ButtonBegTrebleClick
    end
    object ButtonBegHorn: TButton
      Left = 176
      Top = 144
      Width = 145
      Height = 24
      Caption = 'Beginners Hornpipe'
      TabOrder = 7
      OnClick = ButtonBegHornClick
    end
    object ButtonBegTrad: TButton
      Left = 176
      Top = 168
      Width = 145
      Height = 24
      Caption = 'Beginners Traditional Set'
      TabOrder = 8
      OnClick = ButtonBegTradClick
    end
    object ButtonBegPrem: TButton
      Left = 176
      Top = 192
      Width = 145
      Height = 24
      Caption = 'Beginners Premiership'
      TabOrder = 9
      OnClick = ButtonBegPremClick
    end
    object ButtonPriReel: TButton
      Left = 328
      Top = 24
      Width = 145
      Height = 24
      Caption = 'Primary Reel'
      TabOrder = 10
      OnClick = ButtonPriReelClick
    end
    object ButtonPriLight: TButton
      Left = 328
      Top = 48
      Width = 145
      Height = 24
      Caption = 'Primary Light Jig'
      TabOrder = 11
      OnClick = ButtonPriLightClick
    end
    object ButtonPriSingle: TButton
      Left = 328
      Top = 96
      Width = 145
      Height = 24
      Caption = 'Primary Single Jig'
      TabOrder = 13
      OnClick = ButtonPriSingleClick
    end
    object ButtonPriSlip: TButton
      Left = 328
      Top = 72
      Width = 145
      Height = 24
      Caption = 'Primary Slip Jig'
      TabOrder = 12
      OnClick = ButtonPriSlipClick
    end
    object ButtonPriTreble: TButton
      Left = 328
      Top = 120
      Width = 145
      Height = 24
      Caption = 'Primary Treble Jig'
      TabOrder = 14
      OnClick = ButtonPriTrebleClick
    end
    object ButtonPriHorn: TButton
      Left = 328
      Top = 144
      Width = 145
      Height = 24
      Caption = 'Primary Hornpipe'
      TabOrder = 15
      OnClick = ButtonPriHornClick
    end
    object ButtonPriTrad: TButton
      Left = 328
      Top = 168
      Width = 145
      Height = 24
      Caption = 'Primary Traditional Set'
      TabOrder = 16
      OnClick = ButtonPriTradClick
    end
    object ButtonPriPrem: TButton
      Left = 328
      Top = 192
      Width = 145
      Height = 24
      Caption = 'Primary Premiership'
      TabOrder = 17
      OnClick = ButtonPriPremClick
    end
    object ButtonIntReel: TButton
      Left = 480
      Top = 24
      Width = 145
      Height = 24
      Caption = 'Intermediate Reel'
      TabOrder = 18
      OnClick = ButtonIntReelClick
    end
    object ButtonIntLight: TButton
      Left = 480
      Top = 48
      Width = 145
      Height = 24
      Caption = 'Intermediate Light Jig'
      TabOrder = 19
      OnClick = ButtonIntLightClick
    end
    object ButtonIntSingle: TButton
      Left = 480
      Top = 96
      Width = 145
      Height = 24
      Caption = 'Intermediate Single Jig'
      TabOrder = 21
      OnClick = ButtonIntSingleClick
    end
    object ButtonIntSlip: TButton
      Left = 480
      Top = 72
      Width = 145
      Height = 24
      Caption = 'Intermediate Slip Jig'
      TabOrder = 20
      OnClick = ButtonIntSlipClick
    end
    object ButtonIntTreb: TButton
      Left = 480
      Top = 120
      Width = 145
      Height = 24
      Caption = 'Intermediate Treble Jig'
      TabOrder = 22
      OnClick = ButtonIntTrebClick
    end
    object ButtonIntHorn: TButton
      Left = 480
      Top = 144
      Width = 145
      Height = 24
      Caption = 'Intermediate Hornpipe'
      TabOrder = 23
      OnClick = ButtonIntHornClick
    end
    object ButtonIndTrad: TButton
      Left = 480
      Top = 168
      Width = 145
      Height = 24
      Caption = 'Intermediate Traditional Set'
      TabOrder = 24
      OnClick = ButtonIndTradClick
    end
    object ButtonIntPrem: TButton
      Left = 480
      Top = 192
      Width = 145
      Height = 24
      Caption = 'Intermediate Premiership'
      TabOrder = 25
      OnClick = ButtonIntPremClick
    end
    object ButtonOpenReel: TButton
      Left = 632
      Top = 24
      Width = 145
      Height = 24
      Caption = 'Open Reel'
      TabOrder = 26
      OnClick = ButtonOpenReelClick
    end
    object ButtonOpenSlip: TButton
      Left = 632
      Top = 48
      Width = 145
      Height = 24
      Caption = 'Open Slip Jig'
      TabOrder = 27
      OnClick = ButtonOpenSlipClick
    end
    object ButtonOpenTreb: TButton
      Left = 632
      Top = 72
      Width = 145
      Height = 24
      Caption = 'Open Treble Jig'
      TabOrder = 28
      OnClick = ButtonOpenTrebClick
    end
    object ButtonOpenHorn: TButton
      Left = 632
      Top = 96
      Width = 145
      Height = 24
      Caption = 'Open Hornpipe'
      TabOrder = 29
      OnClick = ButtonOpenHornClick
    end
    object ButtonOpenTrad: TButton
      Left = 632
      Top = 120
      Width = 145
      Height = 24
      Caption = 'Open Traditional Set'
      TabOrder = 30
      OnClick = ButtonOpenTradClick
    end
    object ButtonPreChamp: TButton
      Left = 632
      Top = 168
      Width = 145
      Height = 24
      Caption = 'Preliminary Championship'
      TabOrder = 31
      OnClick = ButtonPreChampClick
    end
    object ButtonChamp: TButton
      Left = 632
      Top = 192
      Width = 145
      Height = 24
      Caption = 'Championship'
      TabOrder = 32
      OnClick = ButtonChampClick
    end
    object Button2Hand: TButton
      Left = 16
      Top = 120
      Width = 145
      Height = 24
      Caption = '2-Hand Figure'
      TabOrder = 34
      OnClick = Button2HandClick
    end
    object Button3Hand: TButton
      Left = 16
      Top = 144
      Width = 145
      Height = 24
      Caption = '3-Hand Figure'
      TabOrder = 35
      OnClick = Button3HandClick
    end
    object Button4Hand: TButton
      Left = 16
      Top = 168
      Width = 65
      Height = 24
      Caption = '4-Hand'
      TabOrder = 36
      OnClick = Button4HandClick
    end
    object ButtonCeili: TButton
      Left = 16
      Top = 192
      Width = 65
      Height = 24
      Caption = 'Ceili'
      TabOrder = 38
      OnClick = ButtonCeiliClick
    end
    object SaveNotification: TPanel
      Left = 304
      Top = 80
      Width = 193
      Height = 57
      Caption = #1057#1086#1093#1088#1072#1085#1103#1102' '#1076#1072#1085#1085#1099#1077'...'
      Color = clSkyBlue
      TabOrder = 40
      Visible = False
    end
    object ButtonModernSet: TButton
      Left = 16
      Top = 88
      Width = 145
      Height = 24
      Caption = 'Modern Set'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 33
      OnClick = ButtonModernSetClick
    end
    object ButtonCeiliChamp: TButton
      Left = 80
      Top = 192
      Width = 81
      Height = 24
      Caption = 'Ceili Champ'
      TabOrder = 39
      OnClick = ButtonCeiliChampClick
    end
    object Button4HandChamp: TButton
      Left = 80
      Top = 168
      Width = 81
      Height = 24
      Caption = '4-Hand Champ'
      TabOrder = 37
      OnClick = Button4HandChampClick
    end
  end
  object GroupBoxAges: TGroupBox
    Left = 8
    Top = 248
    Width = 793
    Height = 65
    Caption = ' '#1042#1099#1073#1086#1088' '#1074#1086#1079#1088#1072#1089#1090#1085#1086#1081' '#1075#1088#1091#1087#1087#1099' '
    TabOrder = 1
    object ButtonAgeGroup1: TButton
      Left = 16
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      Visible = False
      OnClick = ButtonAgeGroup1Click
    end
    object ButtonAgeGroup2: TButton
      Left = 64
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Visible = False
      OnClick = ButtonAgeGroup2Click
    end
    object ButtonAgeGroup3: TButton
      Left = 112
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      Visible = False
      OnClick = ButtonAgeGroup3Click
    end
    object ButtonAgeGroup4: TButton
      Left = 160
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      Visible = False
      OnClick = ButtonAgeGroup4Click
    end
    object ButtonAgeGroup5: TButton
      Left = 208
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      Visible = False
      OnClick = ButtonAgeGroup5Click
    end
    object ButtonAgeGroup6: TButton
      Left = 256
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      Visible = False
      OnClick = ButtonAgeGroup6Click
    end
    object ButtonAgeGroup7: TButton
      Left = 304
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      Visible = False
      OnClick = ButtonAgeGroup7Click
    end
    object ButtonAgeGroup8: TButton
      Left = 352
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 7
      Visible = False
      OnClick = ButtonAgeGroup8Click
    end
    object ButtonAgeGroup9: TButton
      Left = 400
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 8
      Visible = False
      OnClick = ButtonAgeGroup9Click
    end
    object ButtonAgeGroup10: TButton
      Left = 448
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 9
      Visible = False
      OnClick = ButtonAgeGroup10Click
    end
    object ButtonAgeGroup11: TButton
      Left = 496
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 10
      Visible = False
      OnClick = ButtonAgeGroup11Click
    end
    object ButtonAgeGroup12: TButton
      Left = 544
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 11
      Visible = False
      OnClick = ButtonAgeGroup12Click
    end
    object ButtonAgeGroup13: TButton
      Left = 592
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 12
      Visible = False
      OnClick = ButtonAgeGroup13Click
    end
    object ButtonAgeGroup14: TButton
      Left = 640
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 13
      Visible = False
      OnClick = ButtonAgeGroup14Click
    end
    object ButtonAgeGroup15: TButton
      Left = 688
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 14
      Visible = False
      OnClick = ButtonAgeGroup15Click
    end
    object ButtonAgeGroup16: TButton
      Left = 736
      Top = 25
      Width = 41
      Height = 24
      Caption = 'AA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 15
      Visible = False
      OnClick = ButtonAgeGroup16Click
    end
  end
  object CountButton: TButton
    Left = 8
    Top = 320
    Width = 97
    Height = 25
    Caption = #1055#1086#1076#1089#1095#1080#1090#1072#1090#1100
    TabOrder = 2
    OnClick = CountButtonClick
  end
  object SaveButton: TButton
    Left = 584
    Top = 320
    Width = 73
    Height = 25
    Anchors = [akTop, akRight]
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 3
    OnClick = SaveButtonClick
  end
  object AddNumberEdit: TEdit
    Left = 224
    Top = 576
    Width = 49
    Height = 21
    Anchors = [akLeft, akBottom]
    TabOrder = 4
    OnChange = AddNumberEditChange
  end
  object AddButton: TButton
    Left = 8
    Top = 576
    Width = 169
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1085#1086#1074#1086#1075#1086' '#1091#1095#1072#1089#1090#1085#1080#1082#1072
    TabOrder = 5
    OnClick = AddButtonClick
  end
  object DeleteButton: TButton
    Left = 568
    Top = 576
    Width = 233
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1099#1076#1077#1083#1077#1085#1085#1086#1075#1086' '#1090#1072#1085#1094#1086#1088#1072' '#1080#1079' '#1089#1087#1080#1089#1082#1072
    TabOrder = 6
    OnClick = DeleteButtonClick
  end
  object ResultsGrid: TStringGrid
    Left = 8
    Top = 352
    Width = 793
    Height = 217
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 4
    DefaultColWidth = 25
    DefaultRowHeight = 18
    FixedCols = 3
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSizing, goColSizing, goEditing, goTabs, goAlwaysShowEditor, goThumbTracking]
    TabOrder = 7
    OnDrawCell = ResultsGridDrawCell
  end
  object CloseButton: TButton
    Left = 664
    Top = 320
    Width = 137
    Height = 25
    Anchors = [akTop, akRight]
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080' '#1079#1072#1082#1088#1099#1090#1100
    TabOrder = 8
    OnClick = CloseButtonClick
  end
  object HelpButton: TButton
    Left = 520
    Top = 320
    Width = 57
    Height = 25
    Anchors = [akTop, akRight]
    Caption = #1057#1087#1088#1072#1074#1082#1072
    TabOrder = 9
    OnClick = HelpButtonClick
  end
  object ConclusionButton: TButton
    Left = 112
    Top = 320
    Width = 97
    Height = 25
    Caption = #1054#1073#1098#1103#1074#1080#1090#1100
    TabOrder = 10
    OnClick = ConclusionButtonClick
  end
  object MergeButton: TButton
    Left = 328
    Top = 320
    Width = 121
    Height = 25
    Caption = #1054#1073#1098#1077#1076#1080#1085#1080#1090#1100' '#1075#1088#1091#1087#1087#1099
    TabOrder = 11
    OnClick = MergeButtonClick
  end
  object AddNameEdit: TEdit
    Left = 312
    Top = 576
    Width = 241
    Height = 21
    Anchors = [akLeft, akBottom]
    TabOrder = 12
    OnChange = AddNameEditChange
    OnKeyPress = AddNameEditKeyPress
  end
  object AllPlacesCheckBox: TCheckBox
    Left = 216
    Top = 323
    Width = 97
    Height = 17
    AllowGrayed = True
    Caption = #1042#1089#1077' '#1084#1077#1089#1090#1072
    State = cbGrayed
    TabOrder = 13
  end
  object ButtonClean: TButton
    Left = 456
    Top = 320
    Width = 57
    Height = 25
    Hint = 
      #1054#1095#1080#1097#1072#1077#1090' '#1091' '#1074#1099#1073#1088#1072#1085#1085#1086#1081' '#1075#1088#1091#1087#1087#1099' '#1074#1089#1077' '#1073#1072#1083#1083#1099' ('#1074#1074#1077#1076#1105#1085#1085#1099#1077' '#1080' '#1087#1086#1089#1095#1080#1090#1072#1085#1085#1099#1077'), ' +
      #1084#1077#1089#1090#1072' '#1080' '#1092#1083#1072#1075#1080' '#1082#1074#1072#1083#1080#1092#1080#1082#1072#1094#1080#1080', '#1085#1086' '#1085#1077' '#1082#1086#1084#1084#1077#1085#1090#1072#1088#1080#1080
    Anchors = [akTop, akRight]
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    ParentShowHint = False
    ShowHint = True
    TabOrder = 14
    OnClick = CleanButtonClick
  end
end
