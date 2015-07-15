//#include "Camera.h"
//
//
//Camera::Camera(void)
//{
//	//camera position
//	eye[0] = 0.0f;  eye[1] = 0.0f;  eye[2] =  0.0f; 
//
//	// Orthogonal Camera Base with eye as origin
//	up[0] = 0.0f;   up[1] = 1.0f;   up[2] =  0.0f;
//	side[0] = 1.0f; side[1] = 0.0f; side[2] =  0.0f;
//	look[0] = 0.0f; look[1] = 0.0f; look[2] = -1.0f;
//
//	//world to camera matrix
//	matrix[0][0] = side[0] - eye[0];
//	matrix[0][1] = up[0] - eye[0];
//	matrix[0][2] = look[0] - eye[0];
//	matrix[1][0] = side[1] - eye[1];
//	matrix[1][1] = up[1] - eye[1];
//	matrix[1][2] = look[1] - eye[1];
//	matrix[2][0] = side[2] - eye[2];
//	matrix[2][1] = up[2] - eye[2];
//	matrix[2][2] = look[2] - eye[2];
//	
//}
//
//void Camera::updateCamera()
//{
//	glLoadIdentity(); // Restore the MODEL-VIEW MATRIX
//	// Update the camera
//	gluLookAt( eye[0], eye[1], eye[2], 
//		look[0], look[1], look[2], 
//		up[0] - eye[0], up[1] - eye[1], up[2] - eye[2]);
//}
//
//Camera::~Camera(void)
//{
//}
