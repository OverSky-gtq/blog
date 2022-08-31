import pyautogui,time
# pyautogui.PAUSE = 1
pyautogui.FAILSAFE = True # 自动防故障，将鼠标移动到左上角强制停止
width,height = pyautogui.size()

time.sleep(5)
#count = 0
while True:
    #pyautogui.typewrite(str(count))
    #count = count + 1
    pyautogui.leftClick(1327,334)
