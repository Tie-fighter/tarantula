/*
 * tarantula.cpp
 *
 *  Created on: 06.12.2012
 *  Author: Thomas Steinbrenner
 *
 */

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching/stitcher.hpp>

using namespace std;
using namespace cv;

static void usage() {
  cout << "Using OpenCV version " << CV_VERSION << "\n" << endl;
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

  Mat frame;  // the current frame

  vector<string> detectors, detector_names;
  detectors.push_back("/home/thomas/cv/datasets/person.xml");
  detector_names.push_back("person");

  namedWindow("frame", CV_WINDOW_NORMAL); // current frame

  LatentSvmDetector detector = LatentSvmDetector(detectors, detector_names);
  vector<LatentSvmDetector::ObjectDetection> detections;


  // main loop
  for (int i=0;;i++) {

	cap >> frame;

	detections.clear();

	detector.detect(frame, detections, 0.5f, 5);

	cout << detections.size() << endl;

    const vector<string> classNames = detector.getClassNames();

    for( size_t i = 0; i < detections.size(); i++ )
    {
        const LatentSvmDetector::ObjectDetection& od = detections[i];
        rectangle(frame, od.rect, Scalar(0,0,255), 1);
    }


    // show images
    imshow("frame", frame);
    
    cvWaitKey(100);
  }

  return 0;

}
