//
//  main.cpp
//  Face_Detection
//
//  Created by shubham  saxena  on 09/01/21.
//

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    
    double scale = 3.5;

    CascadeClassifier faceCascade;
    faceCascade.load("/opt/homebrew/Cellar/opencv/4.5.1_1/data/haarcascades/haarcascade_frontalface_alt.xml");

    VideoCapture cap(0);
    if(!cap.isOpened())
        return -1;

    for(;;){
        Mat frame;
        cap >> frame;

        Mat grayscale;
        cvtColor(frame, grayscale , COLOR_BGR2GRAY);
        resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

        vector<Rect> faces;
        faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));
        
        for(Rect area: faces){
            Scalar drawColor = Scalar(0, 255, 0);
            rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), drawColor);
        }
        
        imshow("Face Detection", frame);

        if(waitKey(30) >= 0)
            break;

    }
    
}
