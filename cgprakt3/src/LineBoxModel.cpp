//
//  LineBoxModel.cpp
//  CGXcode
//
//  Created by Philipp Lensing on 10.10.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "LineBoxModel.h"

LineBoxModel::LineBoxModel(float Width, float Height, float Depth)
{
	Vector origin = Vector(0, 0, 0);

	// TODO: Add your code (Exercise 1) 
	VB.begin();

	//alle Linien vom Ursprung
	VB.addVertex(origin);
	VB.addVertex(0, Height, 0);

	VB.addVertex(origin);
	VB.addVertex(Width, 0, 0);

	VB.addVertex(origin);
	VB.addVertex(0, 0, Depth);

	//alle Linien von Width,Depth
	VB.addVertex(Width, 0, Depth);
	VB.addVertex(0, 0, Depth);

	VB.addVertex(Width, 0, Depth);
	VB.addVertex(Width, 0, 0);

	VB.addVertex(Width, 0, Depth);
	VB.addVertex(Width, Height, Depth);

	//alle Linien von Width,Height
	VB.addVertex(Width, Height, 0);
	VB.addVertex(Width, 0, 0);

	VB.addVertex(Width, Height, 0);
	VB.addVertex(0, Height, 0);

	VB.addVertex(Width, Height, 0);
	VB.addVertex(Width, Height, Depth);

	//alle Linien von Depth,Height
	VB.addVertex(0, Height, Depth);
	VB.addVertex(0, 0, Depth);

	VB.addVertex(0, Height, Depth);
	VB.addVertex(0, Height, 0);

	VB.addVertex(0, Height, Depth);
	VB.addVertex(Width, Height, Depth);

	VB.end();

}

void LineBoxModel::draw(const BaseCamera& Cam)
{
    BaseModel::draw(Cam);
	VB.activate();
	glDrawArrays(GL_LINES, 0, VB.vertexCount());
	VB.deactivate();
  
	// TODO: Add your code (Exercise 1)
}
