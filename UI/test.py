import os, tkinter
from tkinter import font, filedialog

mainblue = "#155c7b"
white = "#fff"

# --- Main Window Settings --- #
window = tkinter.Tk()
window.title("test")
window.geometry("640x400+300+150")
window.resizable(False, False)
window.configure(background = white)
titleFont = tkinter.font.Font(family = "나눔스퀘어", size = 20)
font = tkinter.font.Font(family = "나눔스퀘어", size = 12)

# --- Main Window Objects --- #
titleLabel = tkinter.Label(
    window,
    text = "미친직소",
    fg = mainblue,
    bg = white,
    font = titleFont
)

button = tkinter.Button(
    window,
    text = "폴더 열기",
    relief = "groove",
    overrelief = "groove",
    width = 15,
    repeatdelay = 1000,
    repeatinterval = 100,
    bd = 0,
    fg = white,
    bg = mainblue,
    font = font
)

# --- Pack Objects --- #
titleLabel.pack(pady = 50)
button.pack()

# --- Window Execute --- #
window.mainloop()