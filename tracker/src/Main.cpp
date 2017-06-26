#include "FrameReader.h"
#include "InitRectDrawer.h"
#include "Tracker.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		std::cout << "======================= Error Occured! ======================" << std::endl;
		std::cout << "Function : main" << std::endl;
		std::cout << "Command : solution YOUR_FRAME_IMAGE_PATH (ex. solution D:/frame_image_directory)" << std::endl;
		std::cout << "=============================================================" << std::endl;

		return FAIL;
	}
	cv::Mat mat_img;

	// Create TrackingSystem Object
	TrackingSystem system(argv[1]);
	system.initTrackingSystem();

	// Create FrameReader Object
	FrameReader frame_reader = system.getFrameReader();

	// Track targets
	while (true)
	{
		// Get next frame
		bool frame_read_success = frame_reader.getNextFrame(mat_img);
		if (frame_read_success == FAIL)
			break;

		// Tracking
		bool tracking_success = system.startTracking(mat_img);
		if (tracking_success == FAIL)
			break;

		// Draw tracking result
		if (system.getTrackerManager().getTrackerVec().size() != 0)
			system.drawTrackingResult(mat_img);

		cv::imshow("Tracking System", mat_img);
		cv::waitKey(1);
	}

	system.terminateSystem();
}
