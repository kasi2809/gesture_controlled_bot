import serial
import cv2
ser=serial.Serial('com5',115200)


cap=cv2.VideoCapture(0)
vid=cv2.VideoCapture("http://10.75.99.118:8080/video")
tracker=cv2.TrackerCSRT_create()
success,img=cap.read()
bbox=cv2.selectROI("Track",img,False)
print(bbox)
tracker.init(img,bbox)
cv2.destroyWindow("Track")
while True:
    suc,mob=vid.read()
    mob=cv2.resize(mob,(640,480))
    success,img=cap.read()
    success,bbox=tracker.update(img)
    x=int(bbox[0])
    y=int(bbox[1])
    w=int(bbox[2])
    h=int(bbox[3])
    point_x=x+int(w/2)
    point_y=y+int(h/2)
    cv2.circle(img,(point_x,point_y),7,(0,0,255),-1)
    #cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,0),2)
    cv2.line(img,(0,240),(640,240),(255,0,0),2)
    cv2.line(img, (320,0), (320, 480), (255, 0, 0), 2)
    cv2.putText(img,"FORWARD",(320,25),cv2.FONT_HERSHEY_TRIPLEX,1,(0,0,255),1)
    cv2.putText(img, "BACKWARD", (320,470), cv2.FONT_HERSHEY_TRIPLEX, 1, (0, 0, 255), 1)
    cv2.putText(img, "RIGHT", (530,240), cv2.FONT_HERSHEY_TRIPLEX, 1, (0, 0, 255), 1)
    cv2.putText(img, "LEFT", (0,240), cv2.FONT_HERSHEY_TRIPLEX, 1, (0, 0, 255), 1)
    cv2.putText(img, "STOP", (320,240), cv2.FONT_HERSHEY_TRIPLEX, 1, (0, 0, 255), 1)
    #Forward
    if point_y<180 and point_x>160 and point_x<480:
        ser.write(b"1")
        print("Forward")
    #Backward
    elif point_y>320 and point_x>160 and point_x<480:
        ser.write(b"2")
        print("Backward")
    # Right
    elif point_y>120 and point_y<360 and point_x<240:
        ser.write(b"3")
        print("Left")
    # Left
    elif point_y>120 and point_y<360 and point_x>400:
        ser.write(b"4")
        print("Right")
    else:
        ser.write(b"5")
        print("Stop")


    cv2.imshow("Final",img)
    cv2.imshow("Mob",mob)

    cv2.waitKey(1)

