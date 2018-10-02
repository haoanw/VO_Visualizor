#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

#include <png++/png.hpp>

#include <sys/stat.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace cv;

#include <math.h>
#include <time.h>

#include <eigen3/Eigen/Dense>

using namespace std;

float imgscl = 0.5;
#define pi 3.1415

std::vector<float> GotoLine (std::ifstream& file)
{
	std::vector<float> gposelineVector;
	std::string line;
	getline (file, line);
	std::istringstream iss (line);
	float value; // auxiliary variable to which you extract float from stringstream
	while (iss >> value)        // yields true if extraction succeeded
		gposelineVector.push_back (value); // and pushes value into the vector
	return gposelineVector;
}

void Drawtrajectory3d (IplImage* img, vector<Eigen::Vector3d> traj, vector<
		Eigen::Vector3d> groundtruth)
{

	cvZero (img);
	int width = img->width;
	int height = img->height;

	if (2 * height / 3 - imgscl * traj[traj.size () - 1] (2) < 60)
		imgscl *= 0.9;

	if (2 * height / 3 - imgscl * traj[traj.size () - 1] (2) > height - 50)
		imgscl *= 0.9;

	// adding groundtruth
	if (2 * height / 3 - imgscl * groundtruth[groundtruth.size () - 1] (2) < 60)
		imgscl *= 0.9;

	if (2 * height / 3 - imgscl * groundtruth[groundtruth.size () - 1] (2) > height - 50)
		imgscl *= 0.9;
	// end adding

	cvSet (img, cvScalar (255, 255, 255));
	CvScalar lcolor = cvScalar (0, 0, 0);
	int lw = 1;
	cvLine (img, cvPoint (10, 2 * height / 3), cvPoint (width / 2 - 10, 2 * height / 3), lcolor, lw);
	cvLine (img, cvPoint (1 * width / 4, 10), cvPoint (1 * width / 4, height - 10), lcolor, lw);

	cvLine (img, cvPoint (width / 2 + 10, 2 * height / 3), cvPoint (width - 10, 2 * height / 3), lcolor, lw);
	cvLine (img, cvPoint (3 * width / 4, 10), cvPoint (3 * width / 4, height - 10), lcolor, lw);

	CvPoint p0, p1, p2;
	CvPoint p4, p5, p6; // Points for ground truth

	float fl = 10;
	float ang = pi / 6.0;
	p0 = cvPoint (width - 10, 2 * height / 3);
	p1.x = p0.x - fl * cos (ang);
	p1.y = p0.y - fl * sin (ang);
	p2.x = p0.x - fl * cos (ang);
	p2.y = p0.y + fl * sin (ang);
	cvLine (img, p0, p1, lcolor, lw);
	cvLine (img, p0, p2, lcolor, lw);

	//
	p4 = cvPoint (width - 10, 2 * height / 3);
	p5.x = p4.x - fl * cos (ang);
	p5.y = p4.y - fl * sin (ang);
	p6.x = p4.x - fl * cos (ang);
	p6.y = p4.y + fl * sin (ang);
//	cvLine (img, p4, p5, lcolor, lw);
//	cvLine (img, p4, p6, lcolor, lw);
	//

	p0 = cvPoint (width / 2 - 10, 2 * height / 3);
	p1.x = p0.x - fl * cos (ang);
	p1.y = p0.y - fl * sin (ang);
	p2.x = p0.x - fl * cos (ang);
	p2.y = p0.y + fl * sin (ang);
	cvLine (img, p0, p1, lcolor, lw);
	cvLine (img, p0, p2, lcolor, lw);

	//
	p4 = cvPoint (width / 2 - 10, 2 * height / 3);
	p5.x = p4.x - fl * cos (ang);
	p5.y = p4.y - fl * sin (ang);
	p6.x = p4.x - fl * cos (ang);
	p6.y = p4.y + fl * sin (ang);
//	cvLine (img, p4, p5, lcolor, lw);
//	cvLine (img, p4, p6, lcolor, lw);
	//

	ang = pi / 3.0;
	p0 = cvPoint (width / 4, 10);
	p1.x = p0.x - fl * cos (ang);
	p1.y = p0.y + fl * sin (ang);
	p2.x = p0.x + fl * cos (ang);
	p2.y = p0.y + fl * sin (ang);
	cvLine (img, p0, p1, lcolor, lw);
	cvLine (img, p0, p2, lcolor, lw);

	//
	ang = pi / 3.0;
	p4 = cvPoint (width / 4, 10);
	p5.x = p4.x - fl * cos (ang);
	p5.y = p4.y + fl * sin (ang);
	p6.x = p4.x + fl * cos (ang);
	p6.y = p4.y + fl * sin (ang);
//	cvLine (img, p4, p5, lcolor, lw);
//	cvLine (img, p4, p6, lcolor, lw);
	//

	ang = pi / 3.0;
	p0 = cvPoint (3 * width / 4, 10);
	p1.x = p0.x - fl * cos (ang);
	p1.y = p0.y + fl * sin (ang);
	p2.x = p0.x + fl * cos (ang);
	p2.y = p0.y + fl * sin (ang);
	cvLine (img, p0, p1, lcolor, lw);
	cvLine (img, p0, p2, lcolor, lw);

	//
	ang = pi / 3.0;
	p4 = cvPoint (3 * width / 4, 10);
	p5.x = p4.x - fl * cos (ang);
	p5.y = p4.y + fl * sin (ang);
	p6.x = p4.x + fl * cos (ang);
	p6.y = p4.y + fl * sin (ang);
//	cvLine (img, p4, p5, lcolor, lw);
//	cvLine (img, p4, p6, lcolor, lw);
	//

	CvFont font;
	double hScale = 0.5;
	double vScale = 0.5;
	int lineWidth = 1;
	cvInitFont (&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, hScale, vScale, 0, lineWidth);
	char txt[10];
	CvScalar fcolor = cvScalar (0, 0, 0);
	CvPoint p3;
	CvPoint p7; //

	for (int i = 0; i < traj.size () - 1; i++)
	{

		p1.x = imgscl * traj[i] (0) + width / 4;
		p1.y = 2 * height / 3 - imgscl * traj[i] (2);

		p2.x = imgscl * traj[i + 1] (0) + width / 4;
		p2.y = 2 * height / 3 - imgscl * traj[i + 1] (2);
		//cout<<"px: "<<p1.x<<"  "<<p1.y<<"  "<<p2.x<<"  "<<p2.y<<endl;
		cvLine (img, p1, p2, cvScalar (255, 0, 0), 2);
		p3 = p2;
		p1.x = imgscl * traj[i] (1) + 3 * width / 4;
		p1.y = 2 * height / 3 - imgscl * traj[i] (2);

		p2.x = imgscl * traj[i + 1] (1) + 3 * width / 4;
		p2.y = 2 * height / 3 - imgscl * traj[i + 1] (2);
		//cout<<"px: "<<p1.x<<"  "<<p1.y<<"  "<<p2.x<<"  "<<p2.y<<endl;
		cvLine (img, p1, p2, cvScalar (255, 0, 0), 2);

		double dst = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
		dst = sqrt (dst);
		if (dst > 100)
			cvWaitKey ();
	}

	//adding ground truth
	for (int i = 0; i < groundtruth.size () - 1; i++)
	{

		p5.x = imgscl * groundtruth[i] (0) + width / 4;
		p5.y = 2 * height / 3 - imgscl * groundtruth[i] (2);

		p6.x = imgscl * groundtruth[i + 1] (0) + width / 4;
		p6.y = 2 * height / 3 - imgscl * groundtruth[i + 1] (2);
		//cout<<"px: "<<p1.x<<"  "<<p1.y<<"  "<<p2.x<<"  "<<p2.y<<endl;
		cvLine (img, p5, p6, cvScalar (0, 0, 255), 2);
		p7 = p6;
		p5.x = imgscl * groundtruth[i] (1) + 3 * width / 4;
		p5.y = 2 * height / 3 - imgscl * groundtruth[i] (2);

		p6.x = imgscl * groundtruth[i + 1] (1) + 3 * width / 4;
		p6.y = 2 * height / 3 - imgscl * groundtruth[i + 1] (2);
		//cout<<"px: "<<p1.x<<"  "<<p1.y<<"  "<<p2.x<<"  "<<p2.y<<endl;
		cvLine (img, p5, p6, cvScalar (0, 0, 255), 2);

		double dst = (p5.x - p6.x) * (p5.x - p6.x) + (p5.y - p6.y) * (p5.y - p6.y);
		dst = sqrt (dst);
		if (dst > 100)
			cvWaitKey ();
	}
	//end

	cvCircle (img, p2, 5, cvScalar (0, 100, 100), 2);
	cvCircle (img, p3, 5, cvScalar (100, 100, 0), 2);

	cvCircle (img, p6, 5, cvScalar (0, 100, 100), 2); // ground truth
	cvCircle (img, p7, 5, cvScalar (100, 100, 0), 2); // ground truth

	for (int x = width / 4; x < width / 2 - 10; x += (width / 4) / 3)
	{
		int y = 2 * height / 3 + 20;
		int val = int ((x - width / 4)) / imgscl;

		sprintf (txt, "%d", val);
		cvPutText (img, txt, cvPoint (x - 10, y), &font, fcolor);
	}

	for (int x = width / 4 - (width / 4) / 3; x > 20; x -= (width / 4) / 3)
	{
		int y = 2 * height / 3 + 20;
		int val = int ((x - width / 4)) / imgscl;
		sprintf (txt, "%d", val);
		cvPutText (img, txt, cvPoint (x - 10, y), &font, fcolor);
	}

	for (int y = 2 * height / 3; y > 10; y -= (2 * height / 3) / 3)
	{
		int x = width / 4;
		int val = int ((y - 2 * height / 3)) / imgscl;

		sprintf (txt, "%d", -val);
		cvPutText (img, txt, cvPoint (x + 5, y), &font, fcolor);
	}

	//----------------------------------------
	for (int x = 3 * width / 4; x < width - 50; x += (width / 4) / 3)
	{
		int y = 2 * height / 3 + 20;
		int val = int ((x - 3 * width / 4)) / imgscl;

		sprintf (txt, "%d", val);
		cvPutText (img, txt, cvPoint (x - 10, y), &font, fcolor);
	}

	for (int x = 3 * width / 4 - (width / 4) / 3; x > width / 2 + 50;
			x -= (width / 4) / 3)
	{
		int y = 2 * height / 3 + 20;
		int val = int ((x - 3 * width / 4)) / imgscl;
		sprintf (txt, "%d", val);
		cvPutText (img, txt, cvPoint (x - 10, y), &font, fcolor);
	}

	for (int y = 2 * height / 3; y > 10; y -= (2 * height / 3) / 3)
	{
		int x = 3 * width / 4;
		int val = int ((y - 2 * height / 3)) / imgscl;

		sprintf (txt, "%d", -val);
		cvPutText (img, txt, cvPoint (x + 5, y), &font, fcolor);
	}

	cvPutText (img, "X [m]", cvPoint (width / 2 - 50, 2 * height / 3 + 20), &font, fcolor);

	cvPutText (img, "Z [m]", cvPoint (width / 4 - 50, 40), &font, fcolor);

	cvPutText (img, "Y [m]", cvPoint (width - 50, 2 * height / 3 + 20), &font, fcolor);

	cvPutText (img, "Z [m]", cvPoint (3 * width / 4 - 50, 40), &font, fcolor);

}

int main (int argc, char** argv)
{
/*
	// open groundtruth file
	ifstream groundtruthfile ("08.txt");
	if (groundtruthfile.is_open ())
		cout << "Open ground truth file successfully" << endl;
	else
		cout << "Unable to open ground truth file" << endl;

	// open keyframe file
	ifstream keyframefile ("CameraTrajectory_stereo_08.txt");
	if (groundtruthfile.is_open ())
		cout << "Open keyframe file successfully" << endl;
	else
		cout << "Unable to open keyframe file" << endl;
	vector<Eigen::Vector3d> groundtruth;
	vector<Eigen::Vector3d> traj;
	IplImage* traject = cvCreateImage (cvSize (1300, 500), 8, 3);

	for (int32_t i = 1; i < 4071; i++)
	{
		cout << "Processing: Frame: " << i << endl;
		std::vector<float> realposeVector;
		realposeVector = GotoLine (groundtruthfile);
		Eigen::Vector3d cpose;
		Eigen::Vector3d gpose;
		std::vector<float> keyframeposeVector;
		float ORBMapScale = 1; // Mono Scale: 16.894
		keyframeposeVector = GotoLine (keyframefile);
		cpose << ORBMapScale * keyframeposeVector.at (3), ORBMapScale * keyframeposeVector.at (7), ORBMapScale * keyframeposeVector.at (11);
		traj.push_back (cpose);
		gpose << realposeVector.at (3), realposeVector.at (7), realposeVector.at (11);
		groundtruth.push_back (gpose);
		if (i % 3 == 0)
			Drawtrajectory3d (traject, traj, groundtruth);
		Mat imgtraj (traject);
		imshow ("trajectory", imgtraj);
		waitKey (10);
	}
*/


	// open groundtruth file
	ifstream groundtruthfile ("00.txt");
	if (groundtruthfile.is_open ())
		cout << "Open ground truth file successfully" << endl;
	else
		cout << "Unable to open ground truth file" << endl;

	// open keyframe file
	ifstream keyframefile ("CameraTrajectory.txt");
	if (groundtruthfile.is_open ())
		cout << "Open keyframe file successfully" << endl;
	else
		cout << "Unable to open keyframe file" << endl;
	vector<Eigen::Vector3d> groundtruth;
	vector<Eigen::Vector3d> traj;
	IplImage* traject = cvCreateImage (cvSize (1300, 500), 8, 3);

	for (int32_t i = 1; i < 2474; i = i + 2)
	{
		cout << "Processing: Frame: " << i << endl;
		std::vector<float> realposeVector;
		std::vector<float> keyframeposeVector;
		keyframeposeVector = GotoLine (keyframefile);
		keyframeposeVector = GotoLine (keyframefile);
//		cout << keyframeposeVector.at(1) << endl;
		realposeVector = GotoLine (groundtruthfile);
		realposeVector = GotoLine (groundtruthfile);
//		cout << realposeVector.at(1) << endl;


		Eigen::Vector3d cpose;
		Eigen::Vector3d gpose;

		float ORBMapScale = 1; // Mono Scale: 16.894
		cpose << ORBMapScale * keyframeposeVector.at (1), 0, ORBMapScale * keyframeposeVector.at (2);
		traj.push_back (cpose);
		gpose << 0, 0, 0;
		groundtruth.push_back (gpose);
		if (i % 3 == 0)
			Drawtrajectory3d (traject, traj, groundtruth);
		Mat imgtraj (traject);
		imshow ("trajectory", imgtraj);
		waitKey (10);
	}

// output
	cout << "Demo complete! Exiting ..." << endl;
	waitKey ();

// exit
	return 0;
}

