#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <direct.h>

using namespace std;
using namespace cv;

void printHelp(const char* prog) {
	cout<< "Usage: " << prog << "\n[options] <input_file> <output_folder>\n"
		<< "Positional arguments:\n"
		<< "  input_file            Path to the source file you want to process.\n"
		<< "  output_folder         Destination folder for saving results.\n\n"
		<< "Options:\n"
		<< "  -h, --help            Display this help message and enter prompt mode\n"
		<< endl;
}

int main(int argc, char** argv)
{
	if (argc != 3) {
		printHelp(argv[0]);
		system("pause");
		return 0;
	}

	Mat frame;
	string videoPath = argv[1];
	string savePath = argv[2];
	string filename = "";
	int countFrame = 0;
	VideoCapture cap(videoPath);

	if (!cap.isOpened()) {
		printf("Error: Could not open video file %s\n", videoPath.c_str());
		return -1;
	}

	while (cap.isOpened()) {
		cap >> frame;
		if (frame.empty()) {
			printf("Frame is empty\n");
			break;
		}

		imshow("Video Frame", frame);
		filename = format("%s\\frame%05d.jpg", savePath.c_str(), countFrame);
		_mkdir(savePath.c_str());
		imwrite(filename, frame);
		cout << "Saved: " << filename << '\n';
		countFrame += 1;

		int key = waitKey(30);
		if (key == 27) break;
	}

	cap.release();
	destroyAllWindows();

	system("pause");
	return 0;
}