/*
 * tarantula.cpp
 *
 *  Created on: 06.12.2012
 *  Author: Thomas Steinbrenner
 *
 */

#include <iostream>
#include <vector>
#include <stdio.h>
#include <sys/time.h>

#include <opencv2/opencv.hpp>

//#include "vision.h"


using namespace std;
using namespace cv;

static void usage() {
  cout << "Using OpenCV version " << CV_VERSION << "\n" << endl;
}

void calcTimeDiff (timespec start, timespec stop, timespec diff) {
    
  if ((stop.tv_nsec - start.tv_nsec) < 0) {
    diff.tv_sec = stop.tv_sec - start.tv_nsec - 1;
    diff.tv_nsec = 1000000000 + stop.tv_nsec - start.tv_nsec;
  } else {
    diff.tv_sec = stop.tv_sec - start.tv_sec;
    diff.tv_nsec = stop.tv_nsec - start.tv_nsec;
  }

  return;
}

float getFps (timespec diff) {
  float fps = -1;

  fps = (float)1000000000 / (diff.tv_sec * 1000000000 + diff.tv_nsec);

  return fps;
}

int main(int argc, char** argv) {

  bool use_gui = false;

  // time measurement
  timespec time_now;
  timespec time_past;
  timespec diff;
  char fps[10] = "";
  unsigned long int init_time;

  clock_gettime(CLOCK_MONOTONIC, &time_now);
  init_time = time_now.tv_sec;

  // video source
  VideoCapture cap;

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      
      // -d <deviceid>
      if (string(argv[i]) == "-d") {
        int device_id = -1;
        sscanf(argv[i+1], "%i", &device_id);
        cap.open(device_id);
        i++;

        if (cap.isOpened() != true) {
          cerr << "Error: Device " << device_id << " could not be opened.\n exiting..." << endl;
          return -1;
        }
      }

      // -f <filename>
      else if (string(argv[i]) == "-f") {
        string filename = string(argv[i+1]);
        cap.open(filename);
        i++;

        if (cap.isOpened() != true) {
          cerr << "Error: \"" << filename << "\" could not be opened.\n exiting..." << endl;
          return -1;
        }
      }
      // -g (gui)
      else if (string(argv[i]) == "-g") {
        use_gui = true;
      }

      // noise

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

  Mat frame;  // the current frame
  Mat foreground, background;

  BackgroundSubtractorMOG2 bg(300, 16, false);

  std::vector<std::vector<cv::Point> > contours;

//  vector<string> detectors, detector_names;
//  detectors.push_back("/home/thomas/cv/tarantula/person.xml");
//  detector_names.push_back("person");

  if (use_gui == true) {
    namedWindow("frame", CV_WINDOW_AUTOSIZE); // current frame
    namedWindow("foreground", CV_WINDOW_NORMAL);
    namedWindow("background", CV_WINDOW_NORMAL);
  }

//  LatentSvmDetector detector = LatentSvmDetector(detectors, detector_names);
//  vector<LatentSvmDetector::ObjectDetection> detections;
  
  cout << cap.get(CV_CAP_PROP_FRAME_WIDTH) << " x " << cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
  
  cap.set(CV_CAP_PROP_FRAME_WIDTH, 1024);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 768);

  // main loop
  for (int i=0;;i++) {
    // write time
    clock_gettime(CLOCK_MONOTONIC, &time_past);

    if (cap.read(frame) == NULL) {
      continue;
    }

    bg.operator() (frame, foreground);
    bg.getBackgroundImage(background);

    erode(foreground, foreground, Mat(), Point(-1, -1), 3);
    dilate(foreground, foreground, Mat(), Point(-1, -1), 3);

    findContours(foreground, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    drawContours(frame, contours, -1, Scalar(0,0,255), 2);

    double area;
    int size = contours.size();

    for(int i = 0; i < size; i++) {
      area = contourArea(contours[i]);
      if (area > 1000) {
        cout << i+1 << "/" << size << ": " << area << endl;
      }
    }

    // show images
    if (use_gui == true) {
      imshow("frame", frame);
      imshow("foreground", foreground);
      imshow("background", background);
    }
    
    // calculate fps and display
    clock_gettime(CLOCK_MONOTONIC, &time_now);
    sprintf(fps, "%.2f t-fps, frame: %i, time: %li s", getFps(diff), i, time_now.tv_sec-init_time);
    displayOverlay("frame", fps, 0);
    //cout << fps << endl;

    int c = waitKey(30);
    if (c == 'q' || c == 'Q' || (c & 255) == 27) {
    break;
    }
  }

  return 0;

}
