import os, tkinter
from tkinter import font, filedialog, messagebox
import ctypes as c
import sys

mainblue = "#155c7b"
white = "#fff"

dll2 = c.WinDLL('./dec_pro.dll')
aes_decrypt = dll2['aes_decrypt']
aes_decrypt.argtypes = [c.c_char_p]
aes_decrypt.restype = c.c_int

kill_pro = dll2['KillPro']
kill_pro.argtypes = [c.c_char_p]
kill_pro.restype = c.c_int

reg_del = dll2['RegDelFunc']
reg_del.restype = c.c_int

class aesDec:
    # ========== Start of __init__(self) ========== #
    def __init__(self):
        # --- Windows Settings --- #
        self.window = tkinter.Tk()
        self.window.title("mixxxo")
        self.window.geometry("640x400+300+150")
        self.window.resizable(False, False)
        self.window.configure(background = white)
        self.titleFont = tkinter.font.Font(family = "ChopinScript", size = 20)
        self.font = tkinter.font.Font(family = "나눔스퀘어", size = 10)

        # --- Main Window Objects --- #
        self.titleLabel = tkinter.Label(
            self.window,
            text = "mixxxo",
            fg = mainblue,
            bg = white,
            font = self.titleFont
        )

        self.dec_start = tkinter.Button(
            self.window,
            text = "복호화 시작",
            command = self.aesDec,
            relief = "groove",
            overrelief = "groove",
            width = 10,
            repeatdelay = 1000,
            repeatinterval = 100,
            bd = 0,
            fg = white,
            bg = mainblue,
            font = self.font
        )

        self.label = tkinter.Label(self.window, text="복호화 시작" )
        self.titleLabel.pack(pady = 50)

        self.label.pack()
        self.dec_start.pack()

        self.window.mainloop()      # Window Execute
    # ========== End of __init__(self) ========== #

    def aesDec(self):
        kill_pro(b"HxD.exe")
        reg_del()
        f = open("./list.txt")
        lists = f.readlines()
        
        for fi in lists:
            fi = fi.replace("\n","")
            aes_decrypt(c.c_char_p(fi.encode(), encoding='utf-8'))

        self.label = tkinter.Label(self.window, text="복호화 완료" )
        self.label.pack()


aesDec()