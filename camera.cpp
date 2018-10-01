#include "camera.h"


void camera::render() {

	float delta = 2 / float(CAMERA_VIEW);

	for (int r = 0; r < CAMERA_VIEW; r++) {
		for (int c = 0; c < CAMERA_VIEW; c++) {
			
			Vertex xp = Vertex(0, i*delta - 0.99875, j*delta - 0, 99875);

			// choose eye
			Vertex ps = eye1;

			//end point
			std::vec4 D = (xp - ps) * 100;
			Vertex pe = D + ps;

			// equation ray from eye to pixel(i,j), color: white
			Ray R = Ray(ps, pe, ColorDbl(1, 1, 1));

			//rayIntersection

		}
	}
	
}
