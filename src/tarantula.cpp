/*
 * tarantula.cpp
 *
 *  Created on: 06.12.2012
 *  Author: Thomas Steinbrenner
 *
 */

#include <iostream>
#include <list>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching/stitcher.hpp>

using namespace std;
using namespace cv;

static void usage() {
  cout << "Using OpenCV version " << CV_VERSION << "\n" << endl;
}

int stitch(vector<Mat> pan_pics, Mat pano) {
  Mat result;

  cout << "stitch" << endl;

  Stitcher stitcher = Stitcher::createDefault(true);
  Stitcher::Status status = stitcher.stitch(pan_pics, result);

  if (result.total () >= pano.total()) {
	cout << "update" << endl;
    result.copyTo(pano);
  }

  return 0;
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
  Mat pano;  // the calculated panorama
  vector<Mat> pan_pics;  // vector for storing the stitcher input

  cap >> pano;

  namedWindow("frame", CV_WINDOW_NORMAL); // current frame
  namedWindow("pano", CV_WINDOW_NORMAL);  // calculated panorama

  // main loop
  for (int i=0;;i++) {

	cap >> frame;
	cout << i << endl;

	// every 10 frames save a new frame for the stitcher
    if (i%10 == 0) {
			Mat temp;
			temp = frame.clone();

			if (pan_pics.size() == 3) {
			  pan_pics.erase(pan_pics.begin());
			}
			pan_pics.push_back(temp);

			// if 30th frame then stitch
			if (i % 30 == 0) {
				//TODO: signal stitcher instead
				stitch(pan_pics, pano);
			}
		}

    // show images
    imshow("frame", frame);
    imshow("panorama", pano);

  }

  return 0;

}

/*

  Mat frame, foreground, background, contour;
  BackgroundSubtractorMOG2 bg(3000, 16, false);

  std::vector<std::vector<cv::Point> > contours;

 
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
