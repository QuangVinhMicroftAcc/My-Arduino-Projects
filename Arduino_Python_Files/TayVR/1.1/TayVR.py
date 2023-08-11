import mouse,sys
import tkinter
from tkinter import *
import tkinter.messagebox
import time
import serial
import keyboard
import os
import ctypes

# This is for customize ability. And easy to change and/or debug
maxcom = 12

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
cmd("cls")
found = 0

global ArduinoSerial

mouse.FAILSAFE = False
for comint in range(0,maxcom):
    com = 'com'+str(comint+1)
    print(f"Trying {com}")
    try:
        ArduinoSerial = serial.Serial(com,9600)
        found = 1
        break
    except serial.serialutil.SerialException:
        if comint == 12:
            tkinter.messagebox.showerror(f"Serial Device NOT Found","Your device have not been found. You can check if there is any application is conflicting with your device, or maybe you plugged it in a port that have the COM number over {maxcom}. If you tried plug in every port you can but this 'driver' still can't detect it then please tell a friend who understand these or contact someone who can deal with technical issues, if the issue persists, you can restart your computer OR ask for a refund and accept that you lost.")
            print("EXITTING")
            exit()
        else:
            continue
print("The com is",com)
try:
    data = str(ArduinoSerial.readline().decode('ascii'))
except UnicodeDecodeError:
    tkinter.messagebox.showerror("ERROR: ","We're not sure that are you so unluck that you can even encountered this error. You can restart the driver.")
    run = False
    exit()
try:
    (xc,yc, b1, b2) = data.split(" ")
except ValueError:
    tkinter.messagebox.showerror("ERROR: Invalid value","Your device is showing unexpected errors. Please refrain from touch the wire too much and run the driver again. Thanks for your patience.")
(xc,yc) = (int(xc),int(yc))
time.sleep(1)
cmd("cls")
print("░█  ░█ ░█▀▀█   ▀▀█▀▀ ░█▀▀▀█ ░█▀▀▀█ ░█    ░█▀▀▀█")
print(" ░█░█  ░█▄▄▀    ░█   ░█  ░█ ░█  ░█ ░█     ▀▀▀▄▄")
print("  ▀▄▀  ░█ ░█    ░█   ░█▄▄▄█ ░█▄▄▄█ ░█▄▄█ ░█▄▄▄█")
print("Preparing...")
modeask = tkinter.messagebox.askyesno("Setup","Do you want to use 2D mode?")
time.sleep(1)
print("All fine, off we go.")
tkinter.messagebox.showinfo("Instructions","If you need to quit the driver to use the WINDOWS key then you can press Ctrl+Alt+M to do it. 2D Mode will disable the acceleration sensor and 3D mode will do the exact opposite. To show the console window to debug, press Ctrl+Alt+P. Every inputs and special keys are not very responsive. Remember that.")
show = 0
if modeask == False:
    mode = "3D"
else:
    mode = "2D"
print("Mode:",mode)
time.sleep(1)
hide_console()
run = True
while run:
    try:
        (xo,yo) = mouse.get_position()
        data = str(ArduinoSerial.readline().decode('ascii'))
        print (data)
        (x,y,b1,b2) = data.split(" ")
        (x,y) = (float(x),float(y))
        if x >= xc+1000 or x <= xc-1000 or y >= yc+1000 or y <= yc-1000:
            for i in range(8):
                (Xo,Yo) = mouse.get_position()
                (xt,yt) = (x/1200,y/1200)
                mouse.move(Xo+xt, Yo-yt)
                time.sleep(0.01)
        b1 = int(b1)
        b2 = int(b2)
        if b1 == 123:
            mouse.click(button='right')
        if b2 == 123:
            mouse.click(button='left')
        if keyboard.is_pressed('ctrl+alt+m'):
            checkclose = tkinter.messagebox.askyesno("Stop the driver","Are you sure you want to stop the driver for VR tools?")
            if checkclose == True:
                run = False
                exit()
            else:
                continue
        if keyboard.is_pressed('ctrl+alt+p'):
            if show == 1:
                hide_console()
                show = 0
                continue
            elif show == 0:
                show_console()
                show = 1
                continue
    except UnicodeDecodeError:
        tkinter.messagebox.showerror("ERROR: ","We're not sure that are you so unlucky that you can even encountered this error. You can restart the driver but please refrain from touching the cables to much. They are case sensitive.")
        run = False
        exit()
    except KeyboardInterrupt:
        run = False
        exit()
    except:
        if checkclose == False:
            tkinter.messagebox.showerror("ERROR: Unspecified","There is an error, we're not sure what is it. But please try and restart the driver. If the issue persists, call someone who have knowledge on computers, specifically python and Arduino boards. Thanks for your patience.")
        run = False
        exit()
