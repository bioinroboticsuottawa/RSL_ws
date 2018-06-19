/*
 GRT DTW Example
 This examples demonstrates how to initialize, train, and use the DTW algorithm for classification.
 
 The Dynamic Time Warping (DTW) algorithm is a powerful classifier that works very well for recognizing temporal gestures.
 
 In this example we create an instance of an DTW algorithm and then train the algorithm using some pre-recorded training data.
 The trained DTW algorithm is then used to predict the class label of some test data.
 
 This example shows you how to:
 - Create an initialize the DTW algorithm
 - Load some LabelledTimeSeriesClassificationData from a file and partition the training data into a training dataset and a test dataset
 - Trim any periods of non-movement from the start and end of each timeseries recording 
 - Train the DTW algorithm using the training dataset
 - Test the DTW algorithm using the test dataset
 - Manually compute the accuracy of the classifier
*/

#include "GRT.h"
#include "LMListener.h"
#include <iostream>
#include "Leap.h"
#include <unistd.h> //include the time sleep class
//ROS part
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int16MultiArray.h"
#include "math.h"

using namespace GRT;
using namespace std;

//The physical address of Training data and Test data file (testData coming soon...)
const std::string fileName = "/home/dzhi/catkin_ws/src/rsl/data/DTWTrainingData_10_gestures.grt";
//const std::string testfileName = "/home/dzhi/catkin_ws/src/rsl/data/testData_10_gestures.grt";

//Define the data type of publishing
std_msgs::Float32MultiArray position_hand_data;//The binary position
std_msgs::Int16MultiArray enable_hand;//enable the motors [1,1,1,1,1]
std_msgs::Int16MultiArray enable_wrist;//enable the wrist's motors [1]
std_msgs::Float32MultiArray position_wrist_data;

//int main(int argc, const char * argv[])
int main(int argc, char ** argv)
{
	//Initializing the ROS node
	ros::init(argc, argv, "DTW_classifier");
    ros::NodeHandle n;
	
	//For enabling the hand's motors
	enable_hand.data.push_back(1);
	enable_hand.data.push_back(1);
	enable_hand.data.push_back(1);
	enable_hand.data.push_back(1);
	enable_hand.data.push_back(1);
  	ros::Publisher enable_motors_hand = n.advertise<std_msgs::Int16MultiArray>("/enable_motors", 1000);
	enable_motors_hand.publish (enable_hand);
	
	//For enabling the wrist's motors
	enable_wrist.data.push_back(1);
  	ros::Publisher enable_motors_wrist = n.advertise<std_msgs::Int16MultiArray>("/enable_motors_wrist", 1000);
  	enable_motors_wrist.publish(enable_wrist);
	
	//Create the publishers for publishing the data on topic /position and /position_wrist
	ros::Publisher position = n.advertise<std_msgs::Float32MultiArray>("/position", 1000);
	ros::Publisher position_wrist = n.advertise<std_msgs::Float32MultiArray>("/position_wrist", 1000);
	
	//Create a new DTW instance, using the default parameters
	//DTW dtw(false, true, 3.0, DTW::TEMPLATE_THRESHOLDS, true, 0.2, false, false, 5, 0.99);
	DTW dtw;
	//dtw.enableNullRejection(true);

	//Load some training data to train the classifier - the DTW uses TimeSeriesClassificationData
	TimeSeriesClassificationData trainingData;
	
	if( !trainingData.load(fileName) ){
		cout << "Failed to load training data!\n";
		return EXIT_FAILURE;
	}
	std::cout << "DTW training data has loaded!" << endl;
	//Printing some status about the training data
	trainingData.printStats();
	
	//Use 20% of the training dataset to create a test dataset
	TimeSeriesClassificationData testData = trainingData.split( 70 );
	
	//Trim the training data for any sections of non-movement at the start or end of the recordings
	dtw.enableTrimTrainingData(true,0,25);
	
	//------------------------------------------Train the classifier------------------------------------------
	//if( !dtw.train( trainingData ) ){
		//cout << "Failed to train classifier!\n";
		//return EXIT_FAILURE;
	//}
	//std::cout << "DTW model trained!" << endl;
	
	//Save the DTW model to a file
	//if( !dtw.save("DTWModel_10_gestures.grt") ){
		//cout << "Failed to save the classifier model!\n";
		//return EXIT_FAILURE;
	//}
	
	//Load the DTW model from a file
	if( !dtw.load("DTWModel_10_gestures.grt") ){
		cout << "Failed to load the classifier model!\n";
		return EXIT_FAILURE;
	}
	
	//-----------------------------------Calculating the recognition accuracy--------------------------------------
	
	//Use the test dataset to test the DTW model
	double totalaccuracy = 0;
	VectorFloat gestureAccuracy(testData.getNumClasses(), 0);// Initialize gesture accuracy vector with 0 and size of class's number
	VectorFloat gestureNumber(testData.getNumClasses(), 0);// Update if the sample used to predict
		
	for (UINT i = 0; i<testData.getNumSamples(); i++) {
		//Get the i'th test sample
		UINT classLabel = testData[i].getClassLabel();
		MatrixDouble timeseries = testData[i].getData();
		
		//Perform a prediction using the classifier
		bool predictSuccess = dtw.predict(timeseries);
		
		if (!predictSuccess) {
			cout << "Failed to perform prediction for test sampel: " << i << "\n";
			return EXIT_FAILURE;
		}
		
		//Get the predicted class label
		UINT predictedClassLabel = dtw.getPredictedClassLabel();
		VectorDouble classLikelihoods = dtw.getClassLikelihoods();
		VectorDouble classDistances = dtw.getClassDistances();
		
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
	//std::vector<std::vector <float> > inputFeatureVector(30, std::vector<float>( trainingData.getNumDimensions(), 0) );
	MatrixFloat inputFeatureVector(30, 39);
	inputFeatureVector.setAll(0);
	unsigned int i = 0;
	unsigned int predictedClassLabel = 0;
	//TODO:the real-time classification rate is not match the training data rate. So in this case, it will result in the inaccurate of classification
	//A potential solution is add a counter to continue recording the prediction label, when the prediction label isn't change in a time period, then 
	//we believe the prediction is good.

	while( controller.isServiceConnected() ) //When leap motion is connected
	{	
		// Get the latest frame
		Leap::Frame frame = controller.frame();
		float fps = frame.currentFramesPerSecond();
		cout << "Current frames per second: " << fps << " ";
		Leap::Hand firstHand = frame.hands()[0];
		bool isMoving = false;
		//Frame firstFrame = controller.frame(29);
		//Hand firstFrameHand = firstFrame.hands()[0];
		//unsigned int i = 0;

		if (firstHand.isValid()) {//If a hand is detected
			
			//Generate the empty vector, ready to save the features
			//std::vector<std::vector <float> > inputFeatureVector(0);
			//MatrixFloat inputFeatureVector;
			//inputFeatureVector.clear();
			//inputFeatureVector.erase(inputFeatureVector.begin());
			
			Leap::Frame currentFrame = controller.frame();
			Leap::Hand hand = currentFrame.hands()[0];
				
			// Get the hand's normal vector, direction, and position
			const Leap::Vector normal = hand.palmNormal();
			const Leap::Vector direction = hand.direction();
			featureVector[0] = hand.palmPosition()[0];
			featureVector[1] = hand.palmPosition()[1];
			featureVector[2] = hand.palmPosition()[2];

			// Calculate the hand's pitch, roll, and yaw angles, stored as sample[0] = pitch, sample[1] = roll, sample[2] = yaw angles
			featureVector[3] = direction.pitch() * 57.295779513f;
			featureVector[4] = direction.roll() * 57.295779513f;
			featureVector[5] = direction.yaw() * 57.295779513f;
			featureVector[6] = normal.pitch() * 57.295779513f;
			featureVector[7] = normal.roll() * 57.295779513f;
			featureVector[8] = normal.yaw() * 57.295779513f;

			// Should we have really need the arm's position and directions? Maybe.
			// Get the Arm bone
			/*Leap::Arm arm = hand.arm();
			featureVector[3] = arm.direction()[0];
			featureVector[4] = arm.direction()[1];
			featureVector[5] = arm.direction()[2];*/
			int currIndex = 8;

			// Get fingers, including the fingers position and directions using a 2d vectors representing the finger list
			const Leap::FingerList fingers = hand.fingers();
			for (Leap::FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
				const Leap::Finger finger = *fl;
				//cout << finger.type() << ": " << finger.tipVelocity() << " mm/s;" << endl;
				if (std::abs(finger.tipVelocity()[0]) >= 5 && std::abs(finger.tipVelocity()[1]) >= 5 && std::abs(finger.tipVelocity()[2]) >= 5) isMoving = true;
				// Get each finger bones, Get the fingers' direction
				/*for (int b = 0; b < 4; ++b) {
					Leap::Bone::Type boneType = static_cast<Leap::Bone::Type>(b);
					Leap::Bone bone = finger.bone(boneType);
					featureVector[++currIndex] = bone.direction()[0];
					featureVector[++currIndex] = bone.direction()[1];
					featureVector[++currIndex] = bone.direction()[2];
				}*/
				featureVector[++currIndex] = finger.tipPosition()[0];
				featureVector[++currIndex] = finger.tipPosition()[1];
				featureVector[++currIndex] = finger.tipPosition()[2];
				featureVector[++currIndex] = finger.direction()[0];
				featureVector[++currIndex] = finger.direction()[1];
				featureVector[++currIndex] = finger.direction()[2];

			}
			if (isMoving) {
				if (i > 29) {//When the first 30 frames' data has filled the Matrix
					//cout << "entered" << endl;
					for (unsigned int j = 0; j < 29; j++) {
						inputFeatureVector.setRowVector(inputFeatureVector.getRowVector(j + 1), j);
					}
					inputFeatureVector.setRowVector(featureVector, 29);
					//bool contents = inputFeatureVector.print("the lastest time series");

					//GRT's job:
					//Perform the prediction
					bool predictionSuccess = dtw.predict(inputFeatureVector);
					//You can then get the predicted class label from the pipeline
					UINT ClassLabel = dtw.getPredictedClassLabel();
					//Along with some other results such as the likelihood of the most likely class or the likelihood of all the classes in the model
					double bestLoglikelihood = dtw.getMaximumLikelihood();
					
					predictedClassLabel = predictedClassLabel + 1;
					cout << "Current class label:" << predictedClassLabel <<endl;
			
					//You can then use the predicted class label to trigger the action associated with that gesture
					if (predictedClassLabel == 1) {
						//Trigger the action associated with gesture 1
						cout << "Label 1, Clenched" << ", bestLoglikelihood: " << bestLoglikelihood << endl;
						
						//[0,0,0,0,0] -- Clenched
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(2000000);
						//To fully Open
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(2000000);
					}
					else if (predictedClassLabel == 2) {
						//Trigger the action associated with gesture 2
						cout << "Label 2, Only Index finger move" << ", bestLoglikelihood: " << bestLoglikelihood << endl;
					
						//[1,0,1,1,1] -- Only index finger extended
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(2000000);
						//To fully Open
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(2000000);
					}
					else if (predictedClassLabel == 3) {
						//Trigger the action associated with gesture 3
						cout << "Label 3, Middle&Ring fingers move" << ", bestLoglikelihood: " << bestLoglikelihood << endl;

						//[1,1,0,0,1] -- Middle & Ring fingers move
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(2000000);
						//To fully Open
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(2000000);
					}
					else if (predictedClassLabel == 4) {
						//Trigger the action associated with gesture 4
						cout << "Label 4, Only Thumb move" << ", bestLoglikelihood: " << bestLoglikelihood << endl;

						//[0,1,1,1,1] -- Only Thumb move
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(2000000);
						//To fully Open
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(2000000);
					}
					else if (predictedClassLabel == 5) {
						//Trigger the action associated with gesture 5
						cout << "Label 5, Only Pinky move" << ", bestLoglikelihood: " << bestLoglikelihood << endl;

						//[1,1,1,1,0] -- Only Pinky move
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(2000000);
						//To fully Open
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(2000000);
					}
					else if (predictedClassLabel == 6) {
						//Trigger the action associated with gesture 6
						cout << "Label 6, number 5 and rotate" << ", bestLoglikelihood: " << bestLoglikelihood << endl;
					
						//[1,1,1,1,1] -- Number 5
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						//Move wrist position to -90 degree
						position_wrist_data.data.push_back(1);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						usleep(2000000);
						//Move wrist position to 90 degree
						position_wrist_data.data.push_back(0);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						usleep(2000000);
						//Move wrist position to 0 degree
						position_wrist_data.data.push_back(0.5);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						//Reset the palm's posture to the defult (all five fingers extended)
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(1500000);
					}
					else if (predictedClassLabel == 7) {
						//Trigger the action associated with gesture 7
						cout << "Label 7, 'Love you' and rotate" << ", bestLoglikelihood: " << bestLoglikelihood << endl;

						//[1,1,0,0,1] -- Love you
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						//Move wrist position to -90 degree
						position_wrist_data.data.push_back(1);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						usleep(2000000);
						//Move wrist position to 90 degree
						position_wrist_data.data.push_back(0);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						usleep(2000000);
						//Move wrist position to 0 degree
						position_wrist_data.data.push_back(0.5);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						//Reset the palm's posture to the defult (all five fingers extended)
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(1500000);
					}
					else if (predictedClassLabel == 8) {
						//Trigger the action associated with gesture 8
						cout << "Label 8, 'OK' and rotate" << ", bestLoglikelihood: " << bestLoglikelihood << endl;

						//[0,0,1,1,1] -- Okay
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						//Move wrist position to -90 degree
						position_wrist_data.data.push_back(1);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						usleep(2000000);
						//Move wrist position to 90 degree
						position_wrist_data.data.push_back(0);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						usleep(2000000);
						//Move wrist position to 0 degree
						position_wrist_data.data.push_back(0.5);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						//Reset the palm's posture to the defult (all five fingers extended)
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(1500000);
					}
					else if (predictedClassLabel == 9) {
						//Trigger the action associated with gesture 9
						cout << "Label 9, Letter 'L' and rotate" << ", bestLoglikelihood: " << bestLoglikelihood << endl;

						//[1,1,0,0,0] -- Letter L
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						//Move wrist position to -90 degree
						position_wrist_data.data.push_back(1);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						usleep(2000000);
						//Move wrist position to 90 degree
						position_wrist_data.data.push_back(0);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						usleep(2000000);
						//Move wrist position to 0 degree
						position_wrist_data.data.push_back(0.5);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						//Reset the palm's posture to the defult (all five fingers extended)
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(1500000);
					}
					else if (predictedClassLabel == 10) {
						//Trigger the action associated with gesture 10
						cout << "Label 10, Number 1 and rotate" << ", bestLoglikelihood: " << bestLoglikelihood << endl;

						//[0,1,0,0,0] -- Number 5
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(0);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						//Move wrist position to -90 degree
						position_wrist_data.data.push_back(1);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						usleep(2000000);
						//Move wrist position to 90 degree
						position_wrist_data.data.push_back(0);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						usleep(2000000);
						//Move wrist position to 0 degree
						position_wrist_data.data.push_back(0.5);
						position_wrist.publish(position_wrist_data);
						position_wrist_data.data.clear();
						//Reset the palm's posture to the defult (all five fingers extended)
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);
						position_hand_data.data.push_back(1);	
						position.publish(position_hand_data);
						position_hand_data.data.clear();
						usleep(1500000);
					}
					else {
						cout << "Gesture Not Recognized (really not)" << endl;
					}
				}
				else {
					inputFeatureVector.setRowVector(featureVector, i);
					i++;
					cout << "Gesture Not Recognized (fake)" << endl;
				}
			}
			else {// The hand has not obvious movement
				cout << "Hand detected but not moving" << endl;
				inputFeatureVector.setAll(0);//clear current matrix
				i = 0;//reset the counter
			}
		} //Finishes the processing of a frame (feature extraction and prediction with pipeline)
		
		else {// If there is no hand detected by Leap Motion
			cout << "No hands detected!" << endl;
			inputFeatureVector.setAll(0);//clear current matrix
			i = 0;//reset the counter
			predictedClassLabel = 0; // Reset the predicted label
		}
		usleep(40000); // grabs a frame every 0.04 s.

	}	//Finishes when !controller.isServiceConnected()


	std::system("pause");
	return EXIT_SUCCESS;
}
