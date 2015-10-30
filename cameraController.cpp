#include "camera.cpp"

class cameraController{

	camera* cam;

	bool upButton = 0;
	bool downButton = 0;
	bool leftButton = 0;
	bool rightButton = 0;
	bool forwardButton = 0;
	bool backwardButton = 0;


/*
	index = direction * (positive*1 || negative*2)
	index = {up,left,forward,down,right,backward}
*/

/*	void changeForce(int direction, bool positive, bool negative,float maxSpeed,obj){
	var stopSpeed = 4
	if(obj["keyboard"][posKey] == 0 && obj["keyboard"][negKey] == 0){//coast to a stop
		if(obj[direction]> 0 &&  obj[direction] < stopSpeed){
			obj[direction] = 0
		}else if(obj[direction]<0 && obj[direction] > -stopSpeed){
			obj[direction] = 0
		}else if(obj[direction]> 0){
			obj[direction] = obj[direction]-stopSpeed
		}else if(obj[direction]<0){
			obj[direction] = obj[direction]+stopSpeed
		}
	}else if((obj["keyboard"][posKey] && obj[direction]>=0) || (obj["keyboard"][negKey] && obj[direction]<=0)){//accelerate towards full speed
		obj[direction] = obj[direction] + (obj["keyboard"][posKey] - obj["keyboard"][negKey])
	}else{//actively braking / changing direction. stop faster
		obj[direction] = obj[direction] + (obj["keyboard"][posKey] - obj["keyboard"][negKey]) * 6
	}

	if(obj[direction]>maxSpeed){//enforce max speeds
		obj[direction] = maxSpeed
	}else if(obj[direction] < -maxSpeed){
		obj[direction] = -maxSpeed
	}  
	}*/
};
