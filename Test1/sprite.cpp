#include "sprite.h"

#include "vertex.h"

#include<cstddef>


sprite::sprite()
{
	_vboID = 0;
}


void sprite::init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);//Generates the VBO
	}
	

	vertex vertexData[6];

	//Sets the Vertice Coordinates for the 6 vertex coordinates needed

	//Since the Vertices here are a structure, these vertices are called Interleaved Vertices

	vertexData[0].setPosition(x + width, y+height);
	vertexData[1].setPosition(x, y +height);
	vertexData[2].setPosition(x, y);
	vertexData[3].setPosition(x, y);
	vertexData[4].setPosition(x + width, y);
	vertexData[5].setPosition(x + width, y + height);

	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setUV(0.0f, 0.0f);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setUV(1.0f, 1.0f);
	
	for (int i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 0, 255, 255);

		
	}
	
	vertexData[1].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);//Binds the type of Data that is being uploaded to the GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);//Uploads the Data to the VBO present in the GPU

	glBindBuffer(GL_ARRAY_BUFFER, 0);//UNbinds the Buffer
}

void sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);//Enables the Vertex Attributes

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex,position));//Defines an array from which data is used to draw
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);


	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//Unbinds the Data.

}


sprite::~sprite()
{
	if (_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}
