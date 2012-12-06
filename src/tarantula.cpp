/*
 * tarantula.cpp
 *
 *  Created on: 06.12.2012
 *  Author: Thomas Steinbrenner
 *
 */

#include <cv.h>

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

static void usage() {
  std::cout <<
  "Using OpenCV version " << CV_VERSION << "\n"<<std::endl;
}

int main(int argc, char** argv) {

    VideoCapture cap;

    if (argc > 1) {
      for (int i = 1; i < argc; i++) {

        // -f <filename>
        if (string(argv[i]) == "-f") {
          string filename = string(argv[i+1]);
          cap.open(filename);
          i++;

          if (cap.isOpened() != true) {
            cerr << "Error: \"" << filename << "\" could not be opened.\n exiting..." << endl;
          }
        }

        // noise
//        else if (string(argv[i]) == 

        // history
 
        // mode

        else {
          cerr << "Error: unknown parameter \"" << string(argv[i]) << "\"\n";
          usage();
          return -1;
        }
     }
  }
        
  if (cap.isOpened() != true) {
    cap.open(0);
  }

  if (cap.isOpened()!= true) {
    cerr << "Error: Cannot read device 0.\n exiting..." << endl;
    return -1;
  }


  Mat frame, foreground, background;
  BackgroundSubtractorMOG2 bg(300, 16, false);

  std::vector<std::vector<cv::Point> > contours;

  namedWindow("frame", CV_WINDOW_NORMAL);
  namedWindow("foreground", CV_WINDOW_NORMAL);
  namedWindow("background", CV_WINDOW_NORMAL);

  for (;;) {
    cap >> frame;

    if (frame.empty()) {
      break;
    }

    bg.operator() (frame, foreground);
    bg.getBackgroundImage(background); 

    erode(foreground, foreground, Mat(), Point(-1, -1), 1);
    dilate(foreground, foreground, Mat(), Point(-1, -1), 1);

    findContours(foreground, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    drawContours(frame, contours, -1, Scalar(0,0,255), 2);

    imshow("frame", frame);
    imshow("foreground", foreground);
    imshow("background", background);

    int c = waitKey(30);
    if (c == 'q' || c == 'Q' || (c & 255) == 27) {
      break;
    }
  }

  return 0;

}

