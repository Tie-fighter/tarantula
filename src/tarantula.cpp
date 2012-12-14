/*
 * tarantula.cpp
 *
 *  Created on: 06.12.2012
 *  Author: Thomas Steinbrenner
 *
 */

#include <cv.h>

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching/stitcher.hpp>

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

  Mat pano;

  cap >> pano;

  namedWindow("pano", CV_WINDOW_NORMAL);

  for (;;) {

    Mat frame1, frame2, frame3;
    Mat result;
    
    cap >> frame1;
    cap >> frame2;
    cap >> frame3;

    vector<Mat> vec;
    vec.push_back(pano);
    vec.push_back(frame1);
 
    cout << "frame1: " << frame1.cols << "x" << frame1.rows << endl;
    cout << "pano: " << pano.cols << "x"<< pano.rows << endl;

    Stitcher stitcher = Stitcher::createDefault(true);
    Stitcher::Status status = stitcher.stitch(vec, result);

    cout << status << endl;
    cout << "result: " << result.cols << "x" << result.rows << endl;

    cout << result.total() << " " <<  pano.total() << endl;

    if (result.total() >= pano.total()) {
      result.copyTo(pano);
      cout << "pew pew" << endl;
    }
 
    imshow("pano", pano);

    waitKey(100);
    cout << "---" << endl;

  }

  return 0;

}
  


/*

  Mat frame, foreground, background, contour;
  BackgroundSubtractorMOG2 bg(3000, 16, false);

  std::vector<std::vector<cv::Point> > contours;

  namedWindow("frame", CV_WINDOW_NORMAL);
  namedWindow("foreground", CV_WINDOW_NORMAL);
  namedWindow("background", CV_WINDOW_NORMAL);
//  namedWindow("contour", CV_WINDOW_NORMAL);

  for (;;) {
    cap >> frame;

    if (frame.empty()) {
      break;
    }

    bg.operator() (frame, foreground, 0.001);
    bg.getBackgroundImage(background); 

//    erode(foreground, foreground, Mat(), Point(-1, -1), 2);
//    dilate(foreground, foreground, Mat(), Point(-1, -1), 2);

    frame.copyTo(contour);
    contour &= Scalar(0, 0, 0);
    findContours(foreground, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    drawContours(contour, contours, -1, Scalar(0,0,255), -1);
    addWeighted(frame, 1, contour, 0.5, 0, frame);
    drawContours(frame, contours, -1, Scalar(0,0,0), 1);

    imshow("frame", frame);
    imshow("foreground", foreground);
    imshow("background", background);
//    imshow("contour", contour);

    int c = waitKey(30);
    if (c == 'q' || c == 'Q' || (c & 255) == 27) {
      break;
    }
  }

  return 0;

}

*/
