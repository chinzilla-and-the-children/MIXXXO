import os, tkinter, sys
from tkinter import font, filedialog, messagebox
import ctypes as c

blue = "#30a9de"
black = "#090707"
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
        self.window.title("MIXXXO - Jigsaw Ransomware Decryptor")
        self.window.geometry("640x400+300+150")
        self.window.resizable(True, True)
        self.window.configure(background = black)
        self.window.iconbitmap(default = "img/icon.ico")

        self.font = tkinter.font.Font(family = "맑은 고딕", size = 10)
        self.titleimg = tkinter.PhotoImage(file = "img/title.png")
        self.mg2img = tkinter.PhotoImage(file = "img/mg2.png")
        self.infoimg = tkinter.PhotoImage(file = "img/info.png")

        # --- Main Window Objects --- #
        self.titleLabel = tkinter.Label(
            self.window,
            image = self.titleimg,
            bg = black,
        )

        self.mg2 = tkinter.Label(
            self.window,
            image = self.mg2img,
            bg = black,
        )

        self.dec_start = tkinter.Button(
            self.window,
            text = "복호화 시작",
            command = self.aesDec,
            width = 12,
            repeatdelay = 1000,
            repeatinterval = 100,
            bd = 0,
            fg = white,
            bg = blue,
            font = self.font
        )

        self.info = tkinter.Label (
            self.window,
            i = self.infoimg,
            bg = black
        )

        # --- Pack Window Objects --- #
        self.titleLabel.pack()
        self.mg2.pack(pady = 10)
        self.dec_start.pack(pady = 10)
        self.info.pack()

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
        
        tkinter.messagebox.showinfo("복호화 완료", "복호화가 완료되었습니다. MIXXXO를 종료합니다.")
        self.window.quit()
        self.window.destroy()
        #self.label = tkinter.Label(self.window, text="복호화 완료" )
        #self.label.pack()

aesDec()