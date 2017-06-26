#include "FrameReader.h"

/* -----------------------------------------------------------------------------------

Function : initFrameReader

Initialize FrameReader.

----------------------------------------------------------------------------------- */
int FrameReader::initFrameReader(std::string _path, std::string _image_type)
{
	// Get the first image in the _path
	// If success to complete this function, fd is pointing to the first frame in the FrameReader::path
	handle = _findfirst((_path + "/*." + _image_type).c_str(), &fd);

	// Cannot access to the _path
	if (handle == -1)
	{
		std::cout << "======================= Error Occured! ======================" << std::endl;
		std::cout << "Function : Constructor of FrameReader" << std::endl;
		std::cout << "Cannot open image file named _path with _image_type" << std::endl;
		std::cout << "=============================================================" << std::endl;

		// Change Status CANNOT_OPEN_DIR
		this->status = CANNOT_OPEN_DIR;

		return FAIL;
	}
	// Success to get the first image 
	else
	{
		// Set the FrameReader::path
		this->path.assign(_path);
		// Set the FrameReader::image_type
		this->image_type.assign(_image_type);
		// Change Status WAITING_FOR_READING_FRAME
		this->status = WAITING_FOR_READING_FRAME;

		return SUCCESS;
	}
}

/* -----------------------------------------------------------------------------------

Function : getNextFrame

Get the next frame image from the FrameReader::path

----------------------------------------------------------------------------------- */
int FrameReader::getNextFrame(cv::Mat& mat_img)
{
	switch (status)
	{
		// If fail to access to the path
	case CANNOT_OPEN_DIR:
		std::cout << "======================= Error Occured! ======================" << std::endl;
		std::cout << "Function : int FrameReader::getNextFrame" << std::endl;
		std::cout << "Wrong Path!" << std::endl;
		std::cout << "=============================================================" << std::endl;
		return FAIL;

		// Initialize is done. Now, FrameReader::fd is pointing to the 'First' frame and we need to get this 'First' frame
	case WAITING_FOR_READING_FRAME:
		mat_img = cv::imread(this->path + "/" + this->fd.name, CV_LOAD_IMAGE_COLOR);

		// Change status from WAITING_FOR_READING_FRAME to READING_FRAME_STARTED
		status = READING_FRAME_STARTED;

		return SUCCESS;

		// Now, FrameReader::fd is pointing to the 'Previous' frame, so need to move FrameReadr::fd next and get the frame image
	case READING_FRAME_STARTED:
		// Move FrameReader::fd to the next
		int result = _findnext(handle, &fd);

		// There is no more image
		if (result == -1)
		{
			std::cout << "========================== Notice! ==========================" << std::endl;
			std::cout << "Function : getNextFrame of FrameReader" << std::endl;
			std::cout << "Image reading is done" << std::endl;
			std::cout << "=============================================================" << std::endl;

			// Change status READING_FRAME_STARTED to READING_FRAME_DONE
			status = READING_FRAME_DONE;
			return FAIL;
		}
		else
		{
			mat_img = cv::imread(this->path + "/" + this->fd.name, CV_LOAD_IMAGE_COLOR);
			return SUCCESS;
		}
	}
}