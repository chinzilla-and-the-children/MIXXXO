import tkinter
from tkinter import font

# --- main window settings --- #
window = tkinter.Tk()
window.title("test")
window.geometry("640x400+300+150")
window.resizable(False, False)

font = tkinter.font.Font(family="궁서", size=20)

label = tkinter.Label(window, text="MIXXXO", font=font)
label.pack()

# --- window execute --- #
window.mainloop()