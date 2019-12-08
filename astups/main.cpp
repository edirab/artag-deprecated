#include <iostream>

#include <opencv2/opencv.hpp>

#include <ARToolKitPlus/TrackerMultiMarkerImpl.h>
#include <ARToolKitPlus/extra/Profiler.h>

using namespace cv;

int main(int, char**)
{
	VideoCapture camera(1);
	if(!camera.isOpened()){
		std::cerr<<"Not a single cam was connected that day"<<std::endl;
		return -1;
	}
	
	//Change camera-frame size
	camera.set(CAP_PROP_FRAME_WIDTH, 640);
	camera.set(CAP_PROP_FRAME_HEIGHT, 480);
	std::cout<<"The camera has a resolution of "<<camera.get(CAP_PROP_FRAME_WIDTH)<<"x"<<camera.get(CAP_PROP_FRAME_HEIGHT)<<std::endl;

	//Start the multi-tracker to detect the tags
	//  - 6x6 sized marker images
	//  - samples at a maximum of 6x6
	//  - works with luminance (gray) images
	//  - can load a maximum of 1 pattern
	//  - can detect a maximum of 8 patterns in one image
	ARToolKitPlus::TrackerMultiMarker *tracker = new ARToolKitPlus::TrackerMultiMarkerImpl<6,6,6, 1, 16>(camera.get(CAP_PROP_FRAME_WIDTH), camera.get(CAP_PROP_FRAME_HEIGHT));
	
//	tracker->setPixelFormat(ARToolKitPlus::PIXEL_FORMAT_LUM); //Uncomment if gray-level image
	tracker->setBorderWidth(0.125f);
	tracker->setThreshold(160);
//	tracker->setUndistortionMode(ARToolKitPlus::UNDIST_LUT); //High speed distorsion computation
	tracker->setMarkerMode(ARToolKitPlus::MARKER_ID_SIMPLE);

	if(!tracker->init("data/LogitechPro4000.dat", "data/markerboard_480-499.cfg", 1.0f, 1000.0f)){
		printf("ERROR: init() failed\n");
		return -1;
	}
	
	namedWindow("camera",1);
	for(;;){
		Mat frame;
		camera >> frame; // get a new frame from camera

		imshow("camera", frame);

		int numberDetected = tracker->calc((unsigned char *)frame.data);
		std::cout<<"Detected markers = "<<numberDetected<<std::endl;
		if(numberDetected!=0){
			std::cout<<"\tFound: ";
			int *foundMarkerIDs;
			tracker->getDetectedMarkers(foundMarkerIDs);
			for(size_t multiMarkerCounter=0; multiMarkerCounter<numberDetected; multiMarkerCounter++){
				std::cout<<foundMarkerIDs[multiMarkerCounter]<<"    ";
			}
			std::cout<<std::endl;
		}
		
		if(waitKey(30) >= 0) break;
	}

	return 0;
}
