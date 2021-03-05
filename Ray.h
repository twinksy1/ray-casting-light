#ifndef RAY_H
#define RAY_H

#define PI 3.14159
#define DEG2RAD PI/180.0
#define RAD2DEG 180.0/PI
#define RAYLEN 30

#include <iostream>
#include <cmath>


class LineSegment {
	public:
	float pt1[2];
	float pt2[2];

	inline LineSegment() {}
	inline LineSegment(float x1, float y1, float x2, float y2)
	{
		pt1[0] = x1;
		pt1[1] = y1;
		pt2[0] = x2;
		pt2[1] = y2;
	}
	inline void setCoords(float x1, float y1, float x2, float y2)
	{
		pt1[0] = x1;
		pt1[1] = y1;
		pt2[0] = x2;
		pt2[1] = y2;
	}
};

class Ray {
	public:
	float pos[2];
	float dir[2];
	float angle;
	float* intersectionPt;
	float curDist=0.0f;

	inline Ray()
	{
		pos[0] = 0.0f;
		pos[1] = 0.0f;
		dir[0] = 0.0f;
		dir[1] = 0.0f;
		angle = 0.0f;
		intersectionPt = NULL;
	}
	inline Ray(float p[2], float d[2])
	{
		pos[0] = p[0];
		pos[1] = p[1];
		dir[0] = d[0];
		dir[1] = d[1];
		angle = 0.0f;
		intersectionPt = NULL;
	}
	inline Ray(float x, float y, float xdir, float ydir)
	{
		pos[0] = x;
		pos[1] = y;
		dir[0] = xdir;
		dir[1] = ydir;
		angle = 0.0f;
	}
	inline virtual ~Ray()
	{
		if(intersectionPt != NULL) {
			delete intersectionPt;
			intersectionPt = NULL;
		}
	}
	inline void lookAt(float x, float y)
	{
		dir[0] = x;
		dir[1] = y;
	}
	inline void move(float x, float y)
	{
		pos[0] = x;
		pos[1] = y;
	}
	inline bool rayToLineIntersection(const LineSegment& l)
	{
		float x3 = pos[0];
		float x4 = pos[0] + dir[0];
		float y3 = pos[1];
		float y4 = pos[1] + dir[1];

		float x1 = l.pt1[0];
		float x2 = l.pt2[0];
		float y1 = l.pt1[1];
		float y2 = l.pt2[1];

		const float denom = ((x1-x2)*(y3-y4)) - ((y1-y2)*(x3-x4));
		if(denom == 0.0f) {
			return false;
		}

		float t = ((x1-x3)*(y3-y4) - (y1-y3)*(x3-x4)) / denom;
		
		float u = -1*((x1-x2)*(y1-y3) - (y1-y2)*(x1-x3)) / denom;

		if(t >= 0 && t <= 1 && u >= 0) {
			// Ray intersects this segment
			// Calculate point of intersection
			float ptx = x1 + t*(x2 - x1);
			float pty = y1 + t*(y2 - y1);

			if(intersectionPt != NULL) {
				// An existing point exists
				float dx = pos[0] - ptx;
				float dy = pos[1] - pty;
				float dist = dx*dx + dy*dy;
				// Find closest point
				if(dist < curDist) {
					curDist = dist;
					intersectionPt[0] = ptx;
					intersectionPt[1] = pty;
					return true;
				} else {
					return false;
				}

			} else {
				intersectionPt = new float[2];
				intersectionPt[0] = ptx;
				intersectionPt[1] = pty;
				float dx = pos[0] - ptx;
				float dy = pos[1] - pty;
				curDist = dx*dx + dy*dy;
				return true;
			}

		} else {
			return false;
		}
		
	}
	inline void update()
	{
		if(intersectionPt != NULL) {
			delete intersectionPt;
			intersectionPt = NULL;
		}
		curDist = 0.0f;
	}
	inline void setAngle(float a)
	{
		angle = a;
		dir[0] = RAYLEN*cos(angle*DEG2RAD);
		dir[1] = RAYLEN*sin(angle*DEG2RAD);
	}
};

#endif