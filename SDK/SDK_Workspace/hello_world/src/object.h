/*
 * object.h
 *
 *  Created on: 05.06.2019.
 *      Author: student
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#define PATHS 3
#define MAX_OBJECTS 10

typedef struct{
	int row;
	int column;
	bool isFlower;//true-flower,false-garbage
	bool roseOrYellow; //true-pink,false-yellow
	bool position;
	bool valid; //true-draw it, false-do not draw it
}Object;

/*
typedef struct{
	Object matrix[PATHS][MAX_OBJECTS];
}ObjectMap;
*/

#endif /* OBJECT_H_ */
