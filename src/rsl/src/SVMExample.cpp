/*
 GRT SVM Example
 his examples demonstrates how to initialize, train, and use the SVM algorithm for classification. 
 
 The Support Vector Machine (SVM) classifier is a powerful classifier that works well on a wide range of classification problems, 
 even problems in high dimensions and that are not linearly separable. 
 
 In this example we create an instance of a SVM algorithm and then train the algorithm using some pre-recorded training data.
 The trained SVM algorithm is then used to predict the class label of some test data.
 
 This example shows you how to:
 - Create an initialize the SVM algorithm using a LINEAR kernel
 - Load some ClassificationData from a file and partition the training data into a training dataset and a test dataset
 - Train the SVM algorithm using the training dataset
 - Test the SVM algorithm using the test dataset
 - Manually compute the accuracy of the classifier

You should run this example with one argument pointing to the data you want to load. A good dataset to run this example is acc-orientation.grt, which can be found in the GRT data folder.
*/

//You might need to set the specific path of the GRT header relative to your project
#include "GRT.h"
#include "Leap.h"
#include <iostream>
#include <unistd.h>
//ROS part
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int16MultiArray.h"
#include "math.h"

using namespace GRT;
using namespace std;

const std::string fingerNames[] = { "Thumb", "Index", "Middle", "Ring", "Pinky" };
const std::string boneNames[] = { "Metacarpal", "Proximal", "Middle", "Distal" };

//The physical address of Training data and Test data file
const string filename = "/home/dzhi/catkin_ws/src/rsl/data/TrainingData_static_10numbers.grt";
const string testfilename = "/home/dzhi/catkin_ws/src/rsl/data/testData_static_10numbers.grt";

//Define the data type of publishing
std_msgs::Float32MultiArray motors;//The binary position
std_msgs::Int16MultiArray enable;//enable the motors [1,1,1,1,1]

int main (int argc, char ** argv)
{
	//Initializing the ROS node
	ros::init(argc, argv, "SVM_classifier");
    ros::NodeHandle n;
	
	enable.data.push_back(1);
	enable.data.push_back(1);
	enable.data.push_back(1);
	enable.data.push_back(1);
	enable.data.push_back(1);
	
	//For enabling the motors
  	ros::Publisher enable_motors = n.advertise<std_msgs::Int16MultiArray>("/enable_motors", 1000);
	enable_motors.publish (enable);

	//Create the publisher for publishing the data on topic /position
	ros::Publisher position = n.advertise<std_msgs::Float32MultiArray>("/position", 1000);

	//Create a new SVM classifier with a linear kernel
	//Other kernel options you could choose are: POLY_KERNEL, RBF_KERNEL, SIGMOID_KERNEL, PRECOMPUTED_KERNEL
	SVM svm(SVM::LINEAR_KERNEL);
	
	//The SVM will typically work much better if we scale the training and prediction data, so turn scaling on
	svm.enableScaling( true );
	
	//Train the classifier with some training data
	ClassificationData trainingData;
	
	if( !trainingData.load( filename ) ){
		cout << "Failed to load training data: " << filename << endl;
		return EXIT_FAILURE;
	}
	
	//Use 20% of the training dataset to create a test dataset
	ClassificationData testData;
	
	//Load test dataset
	if (!testData.load(testfilename)) {
		cout << "Failed to load training data: " << testfilename << endl;
		return EXIT_FAILURE;
	}

	//Train the classifier
	if( !svm.train( trainingData ) ){
		cout << "Failed to train classifier!\n";
		return EXIT_FAILURE;
	}
	
	//Save the svm model to a file
	if( !svm.save("SVMModel.grt") ){
		cout << "Failed to save the classifier model!\n";
		return EXIT_FAILURE;
	}
	
	//Load the knn model from a file
	if( !svm.load("SVMModel.grt") ){
		cout << "Failed to load the classifier model!\n";
		return EXIT_FAILURE;
	}
	
	//-----------------------------------Calculating the recognition accuracy--------------------------------------
	//Use the test dataset to test the SVM model
	double totalaccuracy = 0;
	VectorFloat gestureAccuracy(testData.getNumClasses(), 0);// Initialize gesture accuracy vector with 0 and size of class's number
	VectorFloat gestureNumber(testData.getNumClasses(), 0);// Update if the sample used to predict

	for (UINT i = 0; i<testData.getNumSamples(); i++) {
		//Get the i'th test sample
		UINT classLabel = testData[i].getClassLabel();
		VectorFloat inputVector = testData[i].getSample();

		//Perform a prediction using the classifier
		bool predictSuccess = svm.predict(inputVector);

		if (!predictSuccess) {
			cout << "Failed to perform prediction for test sampel: " << i << "\n";
			return EXIT_FAILURE;
		}

		//Get the predicted class label
		UINT predictedClassLabel = svm.getPredictedClassLabel();
		VectorFloat classLikelihoods = svm.getClassLikelihoods();
		VectorFloat classDistances = svm.getClassDistances();

		//Update the accuracy for each gesture and total
		if (classLabel == predictedClassLabel) {
			totalaccuracy++;
			gestureAccuracy[classLabel - 1]++;
			gestureNumber[classLabel - 1]++;

		}
		else {
			gestureNumber[classLabel - 1]++;
		}

		cout << "TestSample: " << i << " ClassLabel: " << classLabel << " PredictedClassLabel: " << predictedClassLabel << endl;
	}
	for (UINT i = 0; i < testData.getNumClasses(); i++) {
		cout << "gesture " << i + 1 << " Test Accuracy: " << gestureAccuracy[i] / gestureNumber[i] * 100.0 << "%" << endl;
	}

	cout << "Total Test Accuracy: " << totalaccuracy / double(testData.getNumSamples())*100.0 << "%" << endl;
	
	//---------------------------------------Classificating in real-time---------------------------------------
	Leap::Controller controller;
	std::cout << "Starting real-time classification period, press Enter to Continue...";
	cin.ignore();
	
	VectorFloat featureVector(trainingData.getNumDimensions());
	//unsigned int i = 0;
	
	while( controller.isServiceConnected() ) {//When leap motion is connected
		
		// Get the latest frame
		Leap::Frame frame = controller.frame();
		float fps = frame.currentFramesPerSecond();
		cout << "Current frames per second: " << fps << " ";
		Leap::Hand hand = frame.hands()[0];
		bool isMoving = false;
	
		if (hand.isValid()) {//If a hand is detected

			// Get the hand's normal vector and direction
			//const Leap::Vector normal = hand.palmNormal();
			//const Leap::Vector direction = hand.direction();
			const Leap::Vector palmPosition = hand.palmPosition();

			// Get fingers object, Thumb, Index, Middle, Ring, and Pinky
			const Leap::FingerList fingers = hand.fingers();
			const Leap::Finger Thumb = fingers[0];
			const Leap::Finger Index = fingers[1];
			const Leap::Finger Middle = fingers[2];
			const Leap::Finger Ring = fingers[3];
			const Leap::Finger Pinky = fingers[4];
			int index = 0;

			// The distance between palm position to fingertip position for each finger (5 dimensions)
			// From thumb to pinky
			for (Leap::FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
				const Leap::Finger finger = *fl;// Get the finger object
				
				// get the velocity data to know is the hand moving or not, then set bool isMoving to true if it's moving
				if (std::abs(finger.tipVelocity()[0]) >= 10 && std::abs(finger.tipVelocity()[1]) >= 10 && std::abs(finger.tipVelocity()[2]) >= 10) isMoving = true;

				// Calculate the distance of current finger's tip position to palm's
				float distance = palmPosition.distanceTo(finger.tipPosition());
				featureVector[index] = distance;
				//std::cout << index << endl;
				index++;
			}

			// The distance between two adjacent fingers, in order of thumb to pinky
			featureVector[5] = Thumb.tipPosition().distanceTo(Index.tipPosition());
			featureVector[6] = Index.tipPosition().distanceTo(Middle.tipPosition());
			featureVector[7] = Middle.tipPosition().distanceTo(Ring.tipPosition());
			featureVector[8] = Ring.tipPosition().distanceTo(Pinky.tipPosition());
	
			if (!isMoving) {// If the hand is not moving, then we can predict the static gesture
	
				//GRT's job:
				//Perform the prediction
				bool predictionSuccess = svm.predict(featureVector);
	
				//You can then get the predicted class label from the pipeline
				UINT predictedClassLabel = svm.getPredictedClassLabel();
	
				//Along with some other results such as the likelihood of the most likely class or the likelihood of all the classes in the model
				double bestLoglikelihood = svm.getMaximumLikelihood();
				//std::cout << bestLoglikelihood << endl;
				vector<double> classLikelihoods = svm.getClassLikelihoods();
	
				//You can then use the predicted class label to trigger the action associated with that gesture
				if (predictedClassLabel == 1) {
					//Trigger the action associated with gesture 1
					cout << "Label 1" << ", bestLoglikelihood: " << bestLoglikelihood << endl;
					
					//[0,1,0,0,0] -- number 1, Only index finger extended
					motors.data.push_back(0);
					motors.data.push_back(0);
					motors.data.push_back(1);
					motors.data.push_back(1);
					motors.data.push_back(1);	
					position.publish(motors);
					motors.data.clear();
				}
				else if (predictedClassLabel == 2) {
					//Trigger the action associated with gesture 2
					cout << "Label 2" << ", bestLoglikelihood: " << bestLoglikelihood << endl;
					
					//[0,1,1,0,0] -- number 2, Only index and middle finger extended
					motors.data.push_back(0);
					motors.data.push_back(1);
					motors.data.push_back(0);
					motors.data.push_back(1);
					motors.data.push_back(1);	
					position.publish(motors);
					motors.data.clear();
				}
				else if (predictedClassLabel == 3) {
					//Trigger the action associated with gesture 3
					cout << "Label 3" << ", bestLoglikelihood: " << bestLoglikelihood << endl;
						
					//[1,1,1,0,0] -- number 3, Thumb, index and middle finger extended
					motors.data.push_back(0);
					motors.data.push_back(1);
					motors.data.push_back(1);
					motors.data.push_back(0);
					motors.data.push_back(1);	
					position.publish(motors);
					motors.data.clear();
				}
				else if (predictedClassLabel == 4) {
					//Trigger the action associated with gesture 4
					cout << "Label 4" << ", bestLoglikelihood: " << bestLoglikelihood << endl;
		
					//[0,1,1,1,1] -- number 4, Only pinky finger extended
					motors.data.push_back(0);
					motors.data.push_back(1);
					motors.data.push_back(1);
					motors.data.push_back(1);
					motors.data.push_back(0);	
					position.publish(motors);
					motors.data.clear();
				}
				else if (predictedClassLabel == 5) {
					//Trigger the action associated with gesture 5
					cout << "Label 5" << ", bestLoglikelihood: " << bestLoglikelihood << endl;

					//[1,1,1,1,1] -- number 5, five fingers extended
					motors.data.push_back(1);
					motors.data.push_back(1);
					motors.data.push_back(1);
					motors.data.push_back(1);
					motors.data.push_back(1);	
					position.publish(motors);
					motors.data.clear();
				}
				else if (predictedClassLabel == 6) {
					//Trigger the action associated with gesture 6
					cout << "Label 6" << ", bestLoglikelihood: " << bestLoglikelihood << endl;

					//[0,1,1,1,0] -- number 6
					motors.data.push_back(0);
					motors.data.push_back(1);
					motors.data.push_back(1);
					motors.data.push_back(1);
					motors.data.push_back(1);	
					position.publish(motors);
					motors.data.clear();
				}
				else if (predictedClassLabel == 7) {
					//Trigger the action associated with gesture 7
					cout << "Label 7" << ", bestLoglikelihood: " << bestLoglikelihood << endl;
				
					//[0,1,1,0,1] -- number 7
					motors.data.push_back(1);
					motors.data.push_back(1);
					motors.data.push_back(1);
					motors.data.push_back(0);
					motors.data.push_back(0);	
					position.publish(motors);
					motors.data.clear();
				}
				else if (predictedClassLabel == 8) {
					//Trigger the action associated with gesture 8
					cout << "Label 8" << ", bestLoglikelihood: " << bestLoglikelihood << endl;

					//[0,1,0,1,1] -- number 8
					motors.data.push_back(0);
					motors.data.push_back(1);
					motors.data.push_back(1);
					motors.data.push_back(0);
					motors.data.push_back(0);	
					position.publish(motors);
					motors.data.clear();
				}
				else if (predictedClassLabel == 9) {
					//Trigger the action associated with gesture 9
					cout << "Label 9" << ", bestLoglikelihood: " << bestLoglikelihood << endl;

					//[0,0,1,1,1] -- number 9
					motors.data.push_back(0);
					motors.data.push_back(1);
					motors.data.push_back(0);
					motors.data.push_back(0);
					motors.data.push_back(0);	
					position.publish(motors);
					motors.data.clear();
				}
				else if (predictedClassLabel == 10) {
					//Trigger the action associated with gesture 10
					cout << "Label 10" << ", bestLoglikelihood: " << bestLoglikelihood << endl;

					//[0,0,0,0,0] -- number 10
					motors.data.push_back(0);
					motors.data.push_back(0);
					motors.data.push_back(0);
					motors.data.push_back(0);
					motors.data.push_back(0);	
					position.publish(motors);
					motors.data.clear();
				}
				else {
					cout << "Gesture Not Recognized (really not)" << endl;
				}
				
				
			}
			else {// The hand has not obvious movement
				cout << "Hand detected, but it is moving!" << endl;
			}
		} //Finishes the processing of a frame (feature extraction and prediction with pipeline)
		else {// If there is no hand detected by Leap Motion
			cout << "No hands detected!" << endl;
		}
		usleep(50000); // grabs a frame every 10 ms
	
	}	//Finishes when !controller.isServiceConnected()
	
	//ros::spin();

	std::system("pause");
	return EXIT_SUCCESS;
}
