import mouse,sys
import tkinter
from tkinter import *
import tkinter.messagebox
import time
import serial
import keyboard
mouse.FAILSAFE = False
comint = int(input("Type the COM number (NUM ONLY): "))
com = 'com'+str(comint)
print("The com is",com)
ArduinoSerial = serial.Serial(com,74880)
time.sleep(1)
run = True
mode = "2d"
# tkinter.messagebox.showinfo('ARDUINO NANO JOYSTICK CONTROLLER 1.0.0','Successfully started ARDUINO NANO JOYSTICK CONTROLLER 1.0.0. Maybe there will be errors later. Better check out. And this controller will ONLY SUPPORT 2D games')
while run:
    # if mode == "2d":
    # up = 'up arrow'
    # down = 'down arrow'
    # right = 'right arrow'
    # left = 'left arrow'
    # elif mode == "3d":
    up = 'w'
    down = 's'
    right = 'd'
    left = 'a'
    # else:
    # mode = "2d"
    data = str(ArduinoSerial.readline().decode('ascii'))
    # a = list(data)
    # x = a[0]+a[1]+a[2]
    # y = a[3]+a[4]+a[5]
    # c = a[6]+a[7]+a[8]
    # x2 = a[9]+a[10]+a[11]
    # y2 = a[12]+a[13]+a[14]
    # switcher = a[15]+a[16]+a[17]

    print(data)
    (x,y,c,x2,y2,switcher) = data.split(" ")
    (Xo,Yo) = mouse.get_position()
    (x,y) = (int(x),int(y))
    (x,y) = (float(x),float(y))
    if x <= 600 and x >= 400:
        xt = x
    if y <= 600 and y >= 400:
        yt = x
    (x,y) = (x-xt, y-yt)
    (x,y) = (x/10,y/10)
    mouse.move(Xo-x, Yo+y)
    c = int(c)
    (x,y) = (int(x),int(y))
    (x2,y2) = (int(x2),int(y2))
    if c == '123' or c == 123:
        mouse.press(button='left')
    else:
        mouse.release(button='left')
    x = int(x)
    y = int(y)
    
    # if y < 100:
    #     # keyboard.press(up)
    #     mouse.move(Xo,Yo-100)
    # if y > 900:
    #     # keyboard.press(down)
    #     mouse.move(Xo,Yo+100)
    # if x < 100:
    #     # keyboard.press(left)
    #     mouse.move(Xo-100,Yo)
    # if x > 900:
    #     # keyboard.press(right)
    #     mouse.move(Xo+100,Yo)

    if y2 < 100:
        keyboard.press(up)
    else:
        keyboard.release(up)
    if y2 > 900:
        keyboard.press(down)
    else:
        keyboard.release(down)
    if x2 < 100:
        keyboard.press(left)
    else:
        keyboard.release(left)
    if x2 > 900:
        keyboard.press(right)
    else:
        keyboard.release(right)
    switcher = int(switcher)
    if keyboard.is_pressed('ctrl+alt+m'):
        run = False
        print("CONTROLLER DISABLED")
        print("Thanks for using ARDUINO NANO JOYSTICK CONTROLLER 1.0.0")
        exit()
    if switcher == 1:
        keyboard.press('space')
    #     if mode == "2d":
    #         mode = "3d"
    #         tkinter.messagebox.showinfo('ARDUINO NANO JOYSTICK CONTROLLER 1.0.0','Your controller has changed mode into 3D mode')
    #     else:
    #         mode = "2d"
    #         tkinter.messagebox.showinfo('ARDUINO NANO JOYSTICK CONTROLLER 1.0.0','Your controller has changed mode into 2D mode')
    else :
        keyboard.release('space')
    print("Is clicked =",c)
