import numpy as np
import cv2
import matplotlib.pyplot as plt
import serial
import time
import math

ser = serial.Serial()
ser.baudrate = 115200
ser.port = 'COM7'
ser.open()
print(ser)

red_low_1 = np.array([0, 150, 95])
red_high_1 = np.array([10, 255, 255])
red_low_2 = np.array([0, 150, 95])
red_high_2 = np.array([160, 255, 255])
green_low = np.array([40, 20, 200])
green_high = np.array([90, 255, 255])
orange_low = np.array([10, 80, 120])
orange_high = np.array([40, 255, 255])
white_low = np.array([0, 0, 240])
white_high = np.array([179, 10, 255])
blue_low = np.array([50, 170, 100])
blue_high = np.array([130, 255, 255])

nbrBlueBal = 5
nbrWhiteBal = 5

blueThreshold = 550
whiteThreshold = 550
dif = 150
mov = 50
# CAMERA
cap = cv2.VideoCapture(0)

frame_count = 0
frame_of_action = 30

while (1):
    time.sleep(0.05)
    frame_count += 1
    if frame_count == frame_of_action:
        frame_count = 0
    # Capture the scene; detect blue, white and green; detect contours; compute centers;

    _, frame = cap.read()
    imhsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    imc = frame.copy()

    # blue contours and centroids
    mask1 = cv2.inRange(imhsv, blue_low, blue_high)

    image, contours, hierarchy = cv2.findContours(mask1, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contours_blue = sorted(contours, key=cv2.contourArea, reverse=True)
    contours_blue = [cnt for cnt in contours_blue if cv2.contourArea(cnt) > blueThreshold]
    for cnt in contours_blue:
        imc = cv2.drawContours(imc, [cnt], 0, (255, 0, 0), 3)
    moments = [cv2.moments(cnt) for cnt in contours_blue]
    centroids_blue = []
    for m in moments:
        try:
            centroids_blue += [(int(round(m['m10'] / m['m00'])), int(round(m['m01'] / m['m00'])))]
        except:
            pass
    for c in centroids_blue:
        cv2.circle(imc, c, 3, (200, 0, 0))

    # white contours and centroids
    mask2 = cv2.inRange(imhsv, white_low, white_high)

    image, contours, hierarchy = cv2.findContours(mask2, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contours_white = sorted(contours, key=cv2.contourArea, reverse=True)
    contours_white = [cnt for cnt in contours_white if cv2.contourArea(cnt) > whiteThreshold]
    for cnt in contours_white:
        imc = cv2.drawContours(imc, [cnt], 0, (200, 200, 255), 3)
    moments = [cv2.moments(cnt) for cnt in contours_white]
    centroids_white = []
    for m in moments:
        try:
            centroids_white += [(int(round(m['m10'] / m['m00'])), int(round(m['m01'] / m['m00'])))]
        except:
            pass
    for c in centroids_white:
        cv2.circle(imc, c, 3, (200, 200, 200))


    # BELOW ROBOT DETECTION

    # orange contours and centroids
    mask4 = cv2.inRange(imhsv, orange_low, orange_high)

    image, contours, hierarchy = cv2.findContours(mask4, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contours_orange = sorted(contours, key=cv2.contourArea, reverse=True)[:1]
    for cnt in contours_orange:
        imc = cv2.drawContours(imc, [cnt], 0, (0, 0, 255), 3)
    moments = [cv2.moments(cnt) for cnt in contours_orange]
    centroids_orange = []
    for m in moments:
        try:
            centroids_orange += [(int(round(m['m10'] / m['m00'])), int(round(m['m01'] / m['m00'])))]
        except:
            pass
    for c in centroids_orange:
        cv2.circle(imc, c, 3, (0, 0, 200))

    # green (robot) contours and centroids
    mask3 = cv2.inRange(imhsv, green_low, green_high)

    image, contours, hierarchy = cv2.findContours(mask3, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contours_green = sorted(contours, key=cv2.contourArea, reverse=True)[:1]
    for cnt in contours_green:
        imc = cv2.drawContours(imc, [cnt], 0, (0, 255, 0), 3)
    moments = [cv2.moments(cnt) for cnt in contours_green]
    centroids_green = []
    for m in moments:
        try:
            centroids_green += [(int(round(m['m10'] / m['m00'])), int(round(m['m01'] / m['m00'])))]
        except:
            pass
    for c in centroids_green:
        cv2.circle(imc, c, 3, (0, 200, 0))


    # OUTPUT COMMANDS VIA SERIAL


    dist_white = []
    white_tuples = []

    def getKey(item):
        return item[1]

    # try:
    #     op = centroids_orange[0]
    # except:
    #     for k in range(mov):
    #         ser.write(b's')
    #     for k in range(mov):
    #         ser.write(b'd')
    #
    # try:
    #     gp = centroids_green[0]
    # except:
    #     for k in range(mov):
    #         ser.write(b'w')
    #     for k in range(mov):
    #         ser.write(b'a')


    try:
        op = centroids_orange[0]
        gp = centroids_green[0]


        gov = np.array(op) - np.array(gp)
        opposition = np.array([-gov[1], gov[0]])

        wp = centroids_white[0]
        cv2.circle(imc, wp, 10, (150, 100, 100))
        gwv = np.array(wp) - np.array(gp)

        dp = np.dot(gwv, gov)
        op = np.dot(gwv, opposition)
        maxdp = np.linalg.norm(gwv) * np.linalg.norm(gov)

        print(maxdp - dp)

        if maxdp - dp < dif:
            print(1)
            ser.write(b'w')
        else:
            print(0)
            if op < 0:
                ser.write(b'a')
            if op > 0:
                ser.write(b'd')
                # show the final frame
    except IndexError as e:
        print(e)
        ser.write(b'z')
    ser.flushInput()
    ser.flushOutput()

    cv2.imshow('c', imc)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows(

)
