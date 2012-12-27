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
#include <opencv2/stitching/stitcher.hpp>

using namespace std;
using namespace cv;

static void usage() {
  cout << "Using OpenCV version " << CV_VERSION << "\n" << endl;
}

float getFps (timespec start, timespec stop) {
  timespec diff;
  float fps = -1;
  
  if ((stop.tv_nsec - start.tv_nsec) < 0) {
    diff.tv_sec = stop.tv_sec - start.tv_nsec - 1;
    diff.tv_nsec = 1000000000 + stop.tv_nsec - start.tv_nsec;
  } else {
    diff.tv_sec = stop.tv_sec - start.tv_sec;
    diff.tv_nsec = stop.tv_nsec - start.tv_nsec;
  }

  fps = (float)1000000000 / (diff.tv_sec * 1000000000 + diff.tv_nsec);

  return fps;
}

int main(int argc, char** argv) {

  // time measurement
  timespec time_now;
  timespec time_past;
  char fps[10] = "";

  // video source
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

  Mat frame;  // the current frame

  vector<string> detectors, detector_names;
  detectors.push_back("/home/thomas/cv/tarantula/person.xml");
  detector_names.push_back("person");

  namedWindow("frame", CV_WINDOW_AUTOSIZE); // current frame

//  LatentSvmDetector detector = LatentSvmDetector(detectors, detector_names);
//  vector<LatentSvmDetector::ObjectDetection> detections;
  
  cout << cap.get(CV_CAP_PROP_FRAME_WIDTH) << " x " << cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
  
//  cap.set(CV_CAP_PROP_FRAME_WIDTH, 1024);
//  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 768);

  // main loop
  for (int i=0;;i++) {
    // write time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time_past);

      cap >> frame;


      // show images
      imshow("frame", frame);
    
    // calculate fps and display
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time_now);
    sprintf(fps, "%f fps", getFps(time_past, time_now));
    displayOverlay("frame", fps, 0);

    cvWaitKey(100);
  }

  return 0;

}
