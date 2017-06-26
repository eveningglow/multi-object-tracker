# multi-object-tracker
Multiple objects tracker using openCV and dlib
![Alt text](/example.png)

# Requsites
* __openCV 3.0__  
* __dlib-19.3__  
* __visual studio 15 (c+11 is necessary)__  

# How to compile
To run this program, you need to compile __opencv__ and __dlib__. You will be able to compile __opencv__ easily from many websites.
The folliwing instruction is how to compile dlib given that you are done with opencv compiling clearly and using visual studio in window. If you have troubles in compiling dlib then you can just use __tracker/vs_solution/MultiObjectTracker.sln__ instead, but you need to change opencv path with your environment in the project property.  

1. Make a new visual studio project.  

2. Include __dlib-19.3/dlib/all/source.cpp__ and __tracker/src/Tracker.cpp__ to your project. Tracker.cpp file will be divided into several files soon.

3. Make new folder(filter) in your project. Include all files(all cpp files and headers) in __dlib-19.3/dlib/external/libjpeg__ to your project.

4. Open __project properties -> Configuration Properties -> C/C++__. You can see __additional include directory__. Write __dlib-19.3__ (next directory should be dlib) to there.

5. Opem __project properties -> Configuration Properties -> C/C++ -> Preprocessor__. You can see __Preprocessor Definitions__. Write __DLIB_JPEG_STATIC__ and __DLIB_JPEG_SUPPORT__ to there.

6. Build.

# How to run 

1. Open cmd and move to the directory which has exe file.

2. Write command : __MultiObjectTracker.exe "YOUR_FRAME_IMAGE_PATH"__. If you're using frame images in this repository, the command is __MultiObjectTracker.exe "video_frame"__.

3. You will be able to see a window with the first frame image. Draw rectangles around the targets you want to track. You can use `ESC` __if you want to remove rectangles__ and `ENTER` __if you are done with drawing__.

4. Now you can see tracking all targets you made.

# Future updates

1. Attach detector. (Pedestrian detector as an example)

2. Divide __tracker/Tracker.cpp__ into several files.

3. Multi thread
