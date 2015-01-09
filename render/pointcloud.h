#pragma once

class ZPoint : public align16
{
public:
	ZVector pos;

	ZPoint()
		: pos(ZVector(0.f, 0.f, 0.f, 1.f))
	{
	}

	ZPoint(const ZVector& pos)
		: pos(pos)
	{
	}

	static void EnableVertexAttribArrays()
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ZPoint), (GLvoid*)0);
	}

	static void DisableVertexAttribArrays()
	{
		glDisableVertexAttribArray(0);
	}
};

template <typename PointType>
class ZPointCloud
{
public:
	ZPointCloud(void)
		: pointBufferID(0)
		, maxSentPoints(0)
	{

	}
	~ZPointCloud(void) {}

	zvector<PointType> points;

	GLuint pointBufferID;
	uint32_t maxSentPoints;

	void Update()
	{
		if (pointBufferID==0)
			glGenBuffers(1, &pointBufferID);

		glBindBuffer(GL_ARRAY_BUFFER, pointBufferID);
			if (points.size() > maxSentPoints)
			{
				// Allocate buffer
				maxSentPoints = points.size();
				glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(PointType), &(points[0]), GL_STREAM_DRAW);
			}
			else
			{
				// Update buffer
				glBufferSubData(GL_ARRAY_BUFFER, 0, points.size()*sizeof(PointType), &(points[0]));
			}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Render()
	{
		glBindBuffer(GL_ARRAY_BUFFER,         pointBufferID);
		PointType::EnableVertexAttribArrays();

		glDrawArrays(GL_POINTS, 0, points.size());

		PointType::DisableVertexAttribArrays();
		glBindBuffer(GL_ARRAY_BUFFER,         0);
	}

	static void RenderSinglePoint()
	{
		static bool initialized = false;

		static ZPointCloud<PointType> singlePoint;

		if (!initialized)
		{
			singlePoint.points.push_back(PointType());
			singlePoint.Update();
			initialized = true;
		}

		singlePoint.Render();
	}
};

