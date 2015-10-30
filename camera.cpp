#include "./space/objectstructs.hpp"
#include "math.h"

class camera : public Object{

	public:

	shared_ptr<Force> UpForce;
	shared_ptr<Force> ForwardForce;
	shared_ptr<Force> RightForce;

	float zoom;
	float maxSpeed;
	float minSpeed;

	//controller state
	bool buttonInput[12]={0,//up
		0,//left
		0,//forward
		0,//down
		0,//right
		0,//backward

		0,//rotUp
		0,//rotLeft
		0,//rotForward
		0,//rotDown
		0,//rotRight
		0};//rotBackward

	void stepAxis(bool positiveButton, bool negativeButton, float* speedAlongAxis){
		if(positiveButton == false && negativeButton == false){//coast to a stop
			if(*speedAlongAxis > 0 &&  *speedAlongAxis < minSpeed){
				*speedAlongAxis = 0;
			}else if(*speedAlongAxis<0 && *speedAlongAxis > -minSpeed){
				*speedAlongAxis = 0;
			}else if(*speedAlongAxis>0){
				*speedAlongAxis = *speedAlongAxis-minSpeed;
			}else if(*speedAlongAxis<0){
				*speedAlongAxis = *speedAlongAxis+minSpeed;
			}
		}else if((positiveButton && speedAlongAxis>=0) || (negativeButton && speedAlongAxis<=0)){//accelerate towards full speed
			*speedAlongAxis = *speedAlongAxis + ((int) positiveButton - (int) negativeButton);
		}else{//actively braking / changing direction. stop faster
			*speedAlongAxis = *speedAlongAxis + ((int) positiveButton - (int) negativeButton) * 6;
		}
	}

	
	void step(){
		//set acceleration
		/*
			index = direction * (positive*1 || negative*2)
			index = {up,left,forward,down,right,backward}
		*/
		stepAxis(buttonInput[0],buttonInput[3], &yVel);
		stepAxis(buttonInput[4],buttonInput[1], &xVel);
		stepAxis(buttonInput[2],buttonInput[5], &zVel);

		float rotSpeed = 1;
		if(buttonInput[6]){
			rotateX(rotSpeed);
		}
		if(buttonInput[9]){
			rotateX(-rotSpeed);
		}
		if(buttonInput[10]){
			rotateY(rotSpeed);
		}
		if(buttonInput[7]){
			rotateY(-rotSpeed);
		}
		if(buttonInput[8]){
			rotateZ(rotSpeed);
		}
		if(buttonInput[11]){
			rotateZ(-rotSpeed);
		}



		if(xVel>maxSpeed){//enforce max speeds
			xVel = maxSpeed;
		}else if(xVel < -maxSpeed){
			xVel = -maxSpeed;
		}  
		if(yVel>maxSpeed){//enforce max speeds
			yVel = maxSpeed;
		}else if(yVel < -maxSpeed){
			yVel = -maxSpeed;
		}  
		if(zVel>maxSpeed){//enforce max speeds
			zVel = maxSpeed;
		}else if(zVel < -maxSpeed){
			zVel = -maxSpeed;
		}  

		translateRight(xVel);
		translateUp(yVel);
		translateForward(zVel);
	}


	void pushUp(bool btnDown){
		buttonInput[0] = btnDown;
	}
	void pushLeft(bool btnDown){
		buttonInput[1] = btnDown;
	}
	void pushForward(bool btnDown){
		buttonInput[2] = btnDown;
	}
	void pushDown(bool btnDown){
		buttonInput[3] = btnDown;
	}
	void pushRight(bool btnDown){
		buttonInput[4] = btnDown;
	}
	void pushBackward(bool btnDown){
		buttonInput[5] = btnDown;
	}
	void tiltDown(bool btnDown){
		buttonInput[6] = btnDown;
	}
	void tiltUp(bool btnDown){
		buttonInput[9] = btnDown;
	}
	void panLeft(bool btnDown){
		buttonInput[10] = btnDown;
	}
	void panRight(bool btnDown){
		buttonInput[7] = btnDown;
	}
	void yawCW(bool btnDown){
		buttonInput[8] = btnDown;
	}
	void yawCCW(bool btnDown){
		buttonInput[11] = btnDown;
	}

	camera(){
			//convention: XYZ maps to element 012 respectively

			//x-axis
			shared_ptr<Coordinate> R (new Coordinate());
			R->push_back(1);
			R->push_back(0);
			R->push_back(0);
			Right = R;

			//camera looks down the z-axis
			shared_ptr<Coordinate> T (new Coordinate());
			T->push_back(0);
			T->push_back(0);
			T->push_back(1);
			Target=T;

			//y-axis at the top
			shared_ptr<Coordinate> U (new Coordinate());
			U->push_back(0);
			U->push_back(1);
			U->push_back(0);
			Up=U;
			
			//camera is a point...
			Dimensions.push_back(0);
			Dimensions.push_back(0);
			Dimensions.push_back(0);
			//...at the origin...
			Location.push_back(0);
			Location.push_back(0);
			Location.push_back(0);
			//..with no rotation
			Rotation.push_back(0);
			Rotation.push_back(0);
			Rotation.push_back(0);
		
			mass = 10.0;
			friction = 0.5;
			zoom = 45.0;
			maxSpeed=0.01;
			minSpeed=0.0001;

			xVel = 0.0;
			yVel = 0.0;
			zVel = 0.0;

			xAcc = 0.0;
			yAcc = 0.0;
			zAcc = 0.0;
	}

};
