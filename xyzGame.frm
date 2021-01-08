VERSION 5.00
Begin VB.Form xyzGame 
   Caption         =   "xyzGame_v0.1"
   ClientHeight    =   4365
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   3345
   LinkTopic       =   "Form1"
   ScaleHeight     =   4365
   ScaleWidth      =   3345
   StartUpPosition =   3  '´°¿ÚÈ±Ê¡
   Begin VB.CommandButton ¾®×ÖÆå 
      Caption         =   "¾®×ÖÆå"
      Height          =   975
      Index           =   0
      Left            =   480
      TabIndex        =   2
      Top             =   3000
      Width           =   2415
   End
   Begin VB.CommandButton ¶íÂÞË¹·½¿é 
      Caption         =   "¶íÂÞË¹·½¿é"
      Height          =   975
      Index           =   1
      Left            =   480
      TabIndex        =   1
      Top             =   1680
      Width           =   2415
   End
   Begin VB.CommandButton Ì°³ÔÉß 
      Caption         =   "Ì°³ÔÉß"
      Height          =   975
      Index           =   0
      Left            =   480
      TabIndex        =   0
      Top             =   360
      Width           =   2415
   End
End
Attribute VB_Name = "xyzGame"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub ¶íÂÞË¹·½¿é_Click(Index As Integer)
Shell App.Path & "\Game\tetris\¶íÂÞË¹·½¿é.exe", vbNormalFocus
End Sub

Private Sub ¾®×ÖÆå_Click(Index As Integer)
Shell App.Path & "\Game\Tic-Tac-Toe\¾®×ÓÆå.exe", vbNormalFocus
End Sub

Private Sub Ì°³ÔÉß_Click(Index As Integer)
Shell App.Path & "\Game\snake\Ì°³ÔÉß.exe", vbNormalFocus
End Sub
