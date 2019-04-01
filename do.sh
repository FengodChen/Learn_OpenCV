#! /bin/bash

g++ main.cpp include/fengod_compare.cpp -o run -L /usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_videoio -lopencv_highgui -lopencv_video -lopencv_imgcodecs
