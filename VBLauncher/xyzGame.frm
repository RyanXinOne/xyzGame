VERSION 5.00
Begin VB.Form xyzGame 
   Caption         =   "xyzGame"
   ClientHeight    =   4365
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   3345
   LinkTopic       =   "Form1"
   ScaleHeight     =   4365
   ScaleWidth      =   3345
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton tttbtn 
      Caption         =   "井字棋"
      Height          =   975
      Index           =   0
      Left            =   480
      TabIndex        =   2
      Top             =   3000
      Width           =   2415
   End
   Begin VB.CommandButton tetrisbtn 
      Caption         =   "俄罗斯方块"
      Height          =   975
      Index           =   1
      Left            =   480
      TabIndex        =   1
      Top             =   1680
      Width           =   2415
   End
   Begin VB.CommandButton snakebtn 
      Caption         =   "贪吃蛇"
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
Private Sub tetrisbtn_Click(Index As Integer)
Shell App.Path & "\Game\tetris\俄罗斯方块.exe", vbNormalFocus
End Sub

Private Sub tttbtn_Click(Index As Integer)
Shell App.Path & "\Game\Tic-Tac-Toe\井字棋.exe", vbNormalFocus
End Sub

Private Sub snakebtn_Click(Index As Integer)
Shell App.Path & "\Game\snake\贪吃蛇.exe", vbNormalFocus
End Sub
