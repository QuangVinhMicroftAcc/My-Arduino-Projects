import mouse,sys
import tkinter
from tkinter import *
import tkinter.messagebox
import time
import serial
import keyboard
import os
import ctypes

def hide_console():
    console_handle = ctypes.windll.kernel32.GetConsoleWindow()
    ctypes.windll.user32.ShowWindow(console_handle, 0)

def show_console():
    console_handle = ctypes.windll.kernel32.GetConsoleWindow()
    ctypes.windll.user32.ShowWindow(console_handle, 1)

mode = "2D"

def cmd(cmd):
    os.system(str(cmd))

cmd("title Arduino Nano Controller VR Tools")
cmd("color 0f")

mouse.FAILSAFE = False
comint = int(input("Type the COM number (NUMBER ONLY): "))
com = 'com'+str(comint)
print("The com is",com)
ArduinoSerial = serial.Serial(com,9600)
data = str(ArduinoSerial.readline().decode('ascii'))
(xc,yc, b1, b2) = data.split(" ")
(xc,yc) = (int(xc),int(yc))
time.sleep(1)
modeask = tkinter.messagebox.askyesno("Setup","Do you want to use 2D mode?")
if modeask == False:
    mode = "3D"
else:
    mode = "2D"
print("Mode:",mode)
time.sleep(1)
run = True
while run:
    (xo,yo) = mouse.get_position()
    data = str(ArduinoSerial.readline().decode('ascii'))
    print (data)
    (x,y,b1,b2) = data.split(" ")
    (x,y) = (float(x),float(y))
    if x >= xc+1000 or x <= xc-1000 or y >= yc+1000 or y <= yc-1000:
        for i in range(10):
            (Xo,Yo) = mouse.get_position()
            (xt,yt) = (x/1300,y/1300)
            mouse.move(Xo+xt, Yo-yt)
            time.sleep(0.01)
    b1 = int(b1)
    b2 = int(b2)
    if b1 == 123:
        mouse.click(button='right')
    if b2 == 123:
        mouse.click(button='left')
    if keyboard.is_pressed('ctrl+alt+m'):
        run = False
        exit()
