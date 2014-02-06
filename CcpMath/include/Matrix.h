////////////////////////////////////////////////////////////////////////////////
//
// Creator:		Snorri Sturluson
// Created:		May 2013
// Copyright:	CCP 2013
//

#pragma once
#ifndef Matrix_h
#define Matrix_h

struct Matrix;
struct Quaternion;
struct Vector3;
struct Vector2;
struct Vector4;
struct Plane;

#include "xnamath.h"
#include "Vector3.h"


struct Matrix
{
	Matrix() {};
	Matrix( const float * );
	Matrix( float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44 );


	// access grants
	float& operator () ( uint32_t Row, uint32_t Col );
	float  operator () ( uint32_t Row, uint32_t Col ) const;

	// ----------------------------------------------------------------------------------
	// Description
	//   XMMATRIX assignment constructor
	// Arguments:
	//   other - The XMMATRIX to copy
	// ----------------------------------------------------------------------------------
	explicit Matrix( const XMMATRIX& other )
	{
		XMStoreFloat4x4( (XMFLOAT4X4*)this, other );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Const XMMATRIX conversion operator
	// Return Value:
	//   XMMATRIX constructed from the Matrix
	// ----------------------------------------------------------------------------------
	operator XMMATRIX() const 
	{ 
		return XMLoadFloat4x4( (const XMFLOAT4X4*)this );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   XMMATRIX assignment operator
	// Arguments:
	//   other - the XMMATRIX to assign to this Matrix
	// Return Value:
	//   Reference to this Matrix
	// ----------------------------------------------------------------------------------
	const Matrix& operator=( const XMMATRIX& other )
	{
		XMStoreFloat4x4( (XMFLOAT4X4*)this, other );
		return *this;
	}

	const float* GetAsFloatArray() const
	{
		return &_11;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Addition-assignment operator
	// Arguments:
	//   other - The Matrix to add to this Matrix
	// Return Value:
	//   This Matrix, after adding the other Matrix
	// ----------------------------------------------------------------------------------
	Matrix& operator+=( const Matrix& other )
	{
		_11 += other._11;
		_12 += other._12;
		_13 += other._13;
		_14 += other._14;

		_21 += other._21;
		_22 += other._22;
		_23 += other._23;
		_24 += other._24;

		_31 += other._31;
		_32 += other._32;
		_33 += other._33;
		_34 += other._34;

		_41 += other._41;
		_42 += other._42;
		_43 += other._43;
		_44 += other._44;

		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Subtraction-assignment operator
	// Arguments:
	//   other - The Matrix to subtract from this Matrix
	// Return Value:
	//   This Matrix, after subtracting off the other Matrix
	// ----------------------------------------------------------------------------------
	Matrix& operator-=( const Matrix& other )
	{
		_11 -= other._11;
		_12 -= other._12;
		_13 -= other._13;
		_14 -= other._14;
			
		_21 -= other._21;
		_22 -= other._22;
		_23 -= other._23;
		_24 -= other._24;
			
		_31 -= other._31;
		_32 -= other._32;
		_33 -= other._33;
		_34 -= other._34;
			
		_41 -= other._41;
		_42 -= other._42;
		_43 -= other._43;
		_44 -= other._44;

		return *this;
	}

	Matrix& operator*=( const Matrix& other );

	// ----------------------------------------------------------------------------------
	// Description
	//   Scalar multiplication-assignment operator
	// Arguments:
	//   f - The scalar by which to multiply this Matrix
	// Return Value:
	//   This Matrix, after multiplying each component by the scalar
	// ----------------------------------------------------------------------------------
	Matrix& operator*=( float f )
	{
		_11 *= f;
		_12 *= f;
		_13 *= f;
		_14 *= f;

		_21 *= f;
		_22 *= f;
		_23 *= f;
		_24 *= f;

		_31 *= f;
		_32 *= f;
		_33 *= f;
		_34 *= f;

		_41 *= f;
		_42 *= f;
		_43 *= f;
		_44 *= f;

		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Scalar division-assignment operator
	// Arguments:
	//   f - The scalar by which to divide this Matrix
	// Return Value:
	//   This Matrix, after dividing by the scalar
	// ----------------------------------------------------------------------------------
	Matrix& operator/=( float f )
	{
		const float fDiv = 1.0f / f;

		_11 *= fDiv;
		_12 *= fDiv;
		_13 *= fDiv;
		_14 *= fDiv;

		_21 *= fDiv;
		_22 *= fDiv;
		_23 *= fDiv;
		_24 *= fDiv;

		_31 *= fDiv;
		_32 *= fDiv;
		_33 *= fDiv;
		_34 *= fDiv;

		_41 *= fDiv;
		_42 *= fDiv;
		_43 *= fDiv;
		_44 *= fDiv;

		return *this;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Unary + operator (effectively a no-op)
	// Return Value:
	//   A copy of this Matrix
	// ----------------------------------------------------------------------------------
	Matrix operator+( void ) const 
	{ 
		return Matrix( *this ); 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Unary negation operator
	// Return Value:
	//   A copy of this Matrix, with each component negated
	// ----------------------------------------------------------------------------------
	Matrix operator-( void ) const
	{
		return Matrix( -_11, -_12, -_13, -_14,
			-_21, -_22, -_23, -_24,
			-_31, -_32, -_33, -_34,
			-_41, -_42, -_43, -_44 );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary addition operator
	// Arguments:
	//   other - The Matrix to add to this Matrix
	// Return Value:
	//   Matrix containing the sum of this Matrix and the other operand
	// ----------------------------------------------------------------------------------
	const Matrix operator+( const Matrix& other ) const
	{
		return Matrix( *this ) += other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary subtraction operator
	// Arguments:
	//   other - The Matrix to subtract from this Matrix
	// Return Value:
	//   Matrix containing the result of the subtraction of the other operand from 
	//   this Matrix
	// ----------------------------------------------------------------------------------
	const Matrix operator-( const Matrix& other ) const
	{
		return Matrix( *this ) -= other;
	}


	// ----------------------------------------------------------------------------------
	// Description
	//   Binary multiplication operator
	// Arguments:
	//   other - The Matrix by which to multiply this Matrix
	// Return Value:
	//   Matrix containing the product of this Matrix and the other operand
	// ----------------------------------------------------------------------------------
	const Matrix operator*( const Matrix& other ) const
	{
		return Matrix( *this ) *= other;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary scalar multiplication operator
	// Arguments:
	//   f - The scalar by which to multiply this Matrix
	// Return Value:
	//   Matrix containing product of this Matrix and the scalar operand
	// ----------------------------------------------------------------------------------
	const Matrix operator*( float f ) const
	{
		return Matrix( *this ) *= f;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Binary scalar division operator
	// Arguments:
	//   f - The scalar by which to divide this Matrix
	// Return Value:
	//   Matrix containing this Matrix divided by the scalar operand
	// ----------------------------------------------------------------------------------
	const Matrix operator/( float f ) const
	{
		return Matrix( *this ) /= f;
	}

	// Declare friend operator
	friend const Matrix operator*( float f, const Matrix& other );

	// ----------------------------------------------------------------------------------
	// Description
	//   Equality comparison operator
	// Arguments:
	//   other - The Matrix with which to compare for equality
	// Return Value:
	//   true, if the two Matrices are component-wise equal
	//   false, if the two Matrices are not component-wise equal
	// ----------------------------------------------------------------------------------
	bool operator==( const Matrix& other ) const
	{
		return ( 
			_11 == other._11 && _12 == other._12 && _13 == other._13 && _14 == other._14 &&
			_21 == other._21 && _22 == other._22 && _23 == other._23 && _24 == other._24 &&
			_31 == other._31 && _32 == other._32 && _33 == other._33 && _34 == other._34 &&
			_41 == other._41 && _42 == other._42 && _43 == other._43 && _44 == other._44 );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Inequality comparison operator
	// Arguments:
	//   other - The Matrix with which to compare for inequality
	// Return Value:
	//   true, if the two Matrices are not component-wise equal
	//   false, if the two Matrices are component-wise equal
	// ----------------------------------------------------------------------------------
	bool operator!=( const Matrix& other ) const
	{
		return ( 
			_11 != other._11 || _12 != other._12 || _13 != other._13 || _14 != other._14 ||
			_21 != other._21 || _22 != other._22 || _23 != other._23 || _24 != other._24 ||
			_31 != other._31 || _32 != other._32 || _33 != other._33 || _34 != other._34 ||
			_41 != other._41 || _42 != other._42 || _43 != other._43 || _44 != other._44 );
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Const translation getter.  Gets the translational component of the Matrix as a
	//   reference to a const Vector3.
	// Return Value:
	//   Const reference to the fourth row of the Matrix, as a Vector3
	// ----------------------------------------------------------------------------------
	const Vector3& GetTranslation( void ) const 
	{ 
		return *(const Vector3*)&_41; 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//  Translation getter.  Gets the translational component of the Matrix as a
	//   reference to a Vector3.
	// Return Value:
	//   Reference to the fourth row of the Matrix, as a Vector3
	// ----------------------------------------------------------------------------------
	Vector3& GetTranslation( void ) 
	{ 
		return *(Vector3*)&_41; 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//  Translation setter.  Sets the translational component of the Matrix with a
	//   Vector3.
	// ----------------------------------------------------------------------------------
	void SetTranslation( const Vector3* translation ) 
	{ 
		*((Vector3*)&_41) = *translation;
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Const x-axis getter.  Gets the x-axis of the Matrix as a reference to a const 
	//   Vector3.
	// Return Value:
	//   Const reference to the first row of the Matrix, as a Vector3
	// ----------------------------------------------------------------------------------
	const Vector3& GetX( void ) const 
	{ 
		return *(const Vector3*)&_11; 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   X-axis getter.  Gets the x-axis of the Matrix as a reference to a Vector3.
	// Return Value:
	//   Reference to the first row of the Matrix, as a Vector3
	// ----------------------------------------------------------------------------------
	Vector3& GetX( void ) 
	{ 
		return *(Vector3*)&_11; 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Const y-axis getter.  Gets the y-axis of the Matrix as a reference to a const 
	//   Vector3.
	// Return Value:
	//   Const reference to the second row of the Matrix, as a Vector3
	// ----------------------------------------------------------------------------------
	const Vector3& GetY( void ) const 
	{ 
		return *(const Vector3*)&_21; 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Y-axis getter.  Gets the y-axis of the Matrix as a reference to a Vector3.
	// Return Value:
	//   Reference to the second row of the Matrix, as a Vector3
	// ----------------------------------------------------------------------------------
	Vector3& GetY( void ) 
	{ 
		return *(Vector3*)&_21; 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Const z-axis getter.  Gets the z-axis of the Matrix as a reference to a const 
	//   Vector3.
	// Return Value:
	//   Const reference to the third row of the Matrix, as a Vector3
	// ----------------------------------------------------------------------------------
	const Vector3& GetZ( void ) const 
	{ 
		return *(const Vector3*)&_31; 
	}

	// ----------------------------------------------------------------------------------
	// Description
	//   Z-axis getter.  Gets the z-axis of the Matrix as a reference to a Vector3.
	// Return Value:
	//   Reference to the third row of the Matrix, as a Vector3
	// ----------------------------------------------------------------------------------
	Vector3& GetZ( void ) 
	{ 
		return *(Vector3*)&_31; 
	}


	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float m[4][4];
	};
};

namespace CcpMath
{

Matrix& MatrixIdentity( Matrix& out );
Matrix MatrixIdentity();

bool MatrixIsIdentity( const Matrix& m );

float MatrixDeterminant( const Matrix& m );

Matrix& MatrixTranspose( Matrix& out, const Matrix& m );
Matrix MatrixTranspose( const Matrix& m );

// Matrix multiplication.  The result represents the transformation M2
// followed by the transformation M1.  (Out = M1 * M2)
Matrix& MatrixMultiply( Matrix& out, const Matrix& m1, const Matrix& m2 );
Matrix MatrixMultiply( const Matrix& m1, const Matrix& m2 );

Matrix& MatrixInverse( Matrix& out, float& determinant, const Matrix& m );
Matrix& MatrixInverse( Matrix& out, const Matrix& m );
Matrix MatrixInverse( float& determinant, const Matrix& m );
Matrix MatrixInverse( const Matrix& m );

Matrix& MatrixScaling( Matrix& out, float sx, float sy, float sz );
Matrix MatrixScaling( float sx, float sy, float sz );

Matrix& MatrixTranslation( Matrix& out, float x, float y, float z );
Matrix MatrixTranslation( float x, float y, float z );

Matrix& MatrixRotationX( Matrix& out, float angle );
Matrix MatrixRotationX( float angle );

Matrix& MatrixRotationY( Matrix& out, float angle );
Matrix MatrixRotationY( float angle );

Matrix& MatrixRotationZ( Matrix& out, float angle );
Matrix MatrixRotationZ( float angle );

Matrix& MatrixRotationAxis( Matrix& out, const Vector3& v, float angle );
Matrix MatrixRotationAxis( const Vector3& v, float angle );

Matrix& MatrixRotationQuaternion( Matrix& out, const Quaternion& q );
Matrix MatrixRotationQuaternion( const Quaternion& q );

Matrix& MatrixRotationYawPitchRoll( Matrix& out, float yaw, float pitch, float roll );
Matrix MatrixRotationYawPitchRoll( float yaw, float pitch, float roll );

Matrix& MatrixTransformation( 
	Matrix& out, 
	const Vector3* scalingCenter,
	const Quaternion* scalingRotation, 
	const Vector3* scaling,
	const Vector3* rotationCenter, 
	const Quaternion *rotation,
	const Vector3* translation );
Matrix MatrixTransformation( 
	const Vector3* scalingCenter,
	const Quaternion* scalingRotation, 
	const Vector3* scaling,
	const Vector3* rotationCenter, 
	const Quaternion *rotation,
	const Vector3* translation );

Matrix& MatrixTransformation2D( 
	Matrix& out, 
	const Vector2* scalingCenter, 
	float scalingRotation, 
	const Vector2* scaling, 
	const Vector2* rotationCenter, 
	float rotation, 
	const Vector2* translation );
Matrix MatrixTransformation2D( 
	const Vector2* scalingCenter, 
	float scalingRotation, 
	const Vector2* scaling, 
	const Vector2* rotationCenter, 
	float rotation, 
	const Vector2* translation );

Matrix& MatrixAffineTransformation( 
	Matrix& out, 
	float scaling, 
	const Vector3 *rotationCenter,
	const Quaternion *rotation, 
	const Vector3 *translation );
Matrix MatrixAffineTransformation( 
	float scaling, 
	const Vector3 *rotationCenter,
	const Quaternion *rotation, 
	const Vector3 *translation );

Matrix& MatrixLookAtRH( 
	Matrix& out, 
	const Vector3& eye, 
	const Vector3& at,
	const Vector3& up );
Matrix MatrixLookAtRH( 
	const Vector3& eye, 
	const Vector3& at,
	const Vector3& up );

Matrix& MatrixLookAtLH( 
	Matrix& out, 
	const Vector3& eye, 
	const Vector3& at,
	const Vector3& up );
Matrix MatrixLookAtLH( 
	const Vector3& eye, 
	const Vector3& at,
	const Vector3& up );

Matrix& MatrixPerspectiveRH( Matrix& out, float w, float h, float zn, float zf );
Matrix MatrixPerspectiveRH( float w, float h, float zn, float zf );

Matrix& MatrixPerspectiveLH( Matrix& out, float w, float h, float zn, float zf );
Matrix MatrixPerspectiveLH( float w, float h, float zn, float zf );

Matrix& MatrixPerspectiveFovRH( Matrix& out, float fovy, float aspect, float zn, float zf );
Matrix MatrixPerspectiveFovRH( float fovy, float aspect, float zn, float zf );

Matrix& MatrixPerspectiveFovLH( Matrix& out, float fovy, float aspect, float zn, float zf );
Matrix MatrixPerspectiveFovLH( float fovy, float aspect, float zn, float zf );

Matrix& MatrixPerspectiveOffCenterRH( 
	Matrix& out, 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn, 
	float zf );
Matrix MatrixPerspectiveOffCenterRH( 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn, 
	float zf );

Matrix& MatrixPerspectiveOffCenterLH( 
	Matrix& out, 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn, 
	float zf );
Matrix MatrixPerspectiveOffCenterLH( 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn, 
	float zf );

Matrix& MatrixOrthoRH( Matrix& out, float w, float h, float zn, float zf );
Matrix MatrixOrthoRH( float w, float h, float zn, float zf );

Matrix& MatrixOrthoLH( Matrix& out, float w, float h, float zn, float zf );
Matrix MatrixOrthoLH( float w, float h, float zn, float zf );

Matrix& MatrixOrthoOffCenterRH( 
	Matrix& out, 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn,
	float zf );
Matrix MatrixOrthoOffCenterRH( 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn,
	float zf );

Matrix& MatrixOrthoOffCenterLH( 
	Matrix& out, 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn,
	float zf );
Matrix MatrixOrthoOffCenterLH( 
	float l, 
	float r, 
	float b, 
	float t, 
	float zn,
	float zf );

void MatrixDecompose( 
	Vector3& scale, 
	Quaternion& rotation, 
	Vector3& translation, 
	const Matrix& m );

}

Matrix* D3DXMatrixIdentity
	( Matrix *pOut );

bool D3DXMatrixIsIdentity
	( const Matrix *pM );

float D3DXMatrixDeterminant
	( const Matrix *pM );

Matrix* D3DXMatrixTranspose
	( Matrix *pOut, const Matrix *pM );

// Matrix multiplication.  The result represents the transformation M2
// followed by the transformation M1.  (Out = M1 * M2)
Matrix* D3DXMatrixMultiply
	( Matrix *pOut, const Matrix *pM1, const Matrix *pM2 );

// Matrix multiplication, followed by a transpose. (Out = T(M1 * M2))
// Not used in trinity - skipping
Matrix* D3DXMatrixMultiplyTranspose
	( Matrix *pOut, const Matrix *pM1, const Matrix *pM2 );

// Calculate inverse of matrix.  Inversion my fail, in which case NULL will
// be returned.  The determinant of pM is also returned it pfDeterminant
// is non-NULL.
Matrix* D3DXMatrixInverse
	( Matrix *pOut, float *pDeterminant, const Matrix *pM );

// Build a matrix which scales by (sx, sy, sz)
Matrix* D3DXMatrixScaling
	( Matrix *pOut, float sx, float sy, float sz );

// Build a matrix which translates by (x, y, z)
Matrix* D3DXMatrixTranslation
	( Matrix *pOut, float x, float y, float z );

// Build a matrix which rotates around the X axis
Matrix* D3DXMatrixRotationX
	( Matrix *pOut, float Angle );

// Build a matrix which rotates around the Y axis
Matrix* D3DXMatrixRotationY
	( Matrix *pOut, float Angle );

// Build a matrix which rotates around the Z axis
Matrix* D3DXMatrixRotationZ
	( Matrix *pOut, float Angle );

// Build a matrix which rotates around an arbitrary axis
Matrix* D3DXMatrixRotationAxis
	( Matrix *pOut, const Vector3 *pV, float Angle );

// Build a matrix from a quaternion
Matrix* D3DXMatrixRotationQuaternion
	( Matrix *pOut, const Quaternion *pQ);

// Yaw around the Y axis, a pitch around the X axis,
// and a roll around the Z axis.
Matrix* D3DXMatrixRotationYawPitchRoll
	( Matrix *pOut, float Yaw, float Pitch, float Roll );

// Build transformation matrix.  NULL arguments are treated as identity.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
Matrix* D3DXMatrixTransformation
	( Matrix *pOut, const Vector3 *pScalingCenter,
	const Quaternion *pScalingRotation, const Vector3 *pScaling,
	const Vector3 *pRotationCenter, const Quaternion *pRotation,
	const Vector3 *pTranslation);

// Build 2D transformation matrix in XY plane.  NULL arguments are treated as identity.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
Matrix* D3DXMatrixTransformation2D
	( Matrix *pOut, const Vector2* pScalingCenter, 
	float ScalingRotation, const Vector2* pScaling, 
	const Vector2* pRotationCenter, float Rotation, 
	const Vector2* pTranslation);

// Build affine transformation matrix.  NULL arguments are treated as identity.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
Matrix* D3DXMatrixAffineTransformation
	( Matrix *pOut, float Scaling, const Vector3 *pRotationCenter,
	const Quaternion *pRotation, const Vector3 *pTranslation);

// Build 2D affine transformation matrix in XY plane.  NULL arguments are treated as identity.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
// Not used in trinity - skipping
Matrix* D3DXMatrixAffineTransformation2D
	( Matrix *pOut, float Scaling, const Vector2* pRotationCenter, 
	float Rotation, const Vector2* pTranslation);

// Build a lookat matrix. (right-handed)
Matrix* D3DXMatrixLookAtRH
	( Matrix *pOut, const Vector3 *pEye, const Vector3 *pAt,
	const Vector3 *pUp );

// Build a lookat matrix. (left-handed)
Matrix* D3DXMatrixLookAtLH
	( Matrix *pOut, const Vector3 *pEye, const Vector3 *pAt,
	const Vector3 *pUp );

// Build a perspective projection matrix. (right-handed)
Matrix* D3DXMatrixPerspectiveRH
	( Matrix *pOut, float w, float h, float zn, float zf );

// Build a perspective projection matrix. (left-handed)
Matrix* D3DXMatrixPerspectiveLH
	( Matrix *pOut, float w, float h, float zn, float zf );

// Build a perspective projection matrix. (right-handed)
Matrix* D3DXMatrixPerspectiveFovRH
	( Matrix *pOut, float fovy, float Aspect, float zn, float zf );

// Build a perspective projection matrix. (left-handed)
Matrix* D3DXMatrixPerspectiveFovLH
	( Matrix *pOut, float fovy, float Aspect, float zn, float zf );

// Build a perspective projection matrix. (right-handed)
Matrix* D3DXMatrixPerspectiveOffCenterRH
	( Matrix *pOut, float l, float r, float b, float t, float zn,
	float zf );

// Build a perspective projection matrix. (left-handed)
Matrix* D3DXMatrixPerspectiveOffCenterLH
	( Matrix *pOut, float l, float r, float b, float t, float zn,
	float zf );

// Build an ortho projection matrix. (right-handed)
Matrix* D3DXMatrixOrthoRH
	( Matrix *pOut, float w, float h, float zn, float zf );

// Build an ortho projection matrix. (left-handed)
Matrix* D3DXMatrixOrthoLH
	( Matrix *pOut, float w, float h, float zn, float zf );

// Build an ortho projection matrix. (right-handed)
Matrix* D3DXMatrixOrthoOffCenterRH
	( Matrix *pOut, float l, float r, float b, float t, float zn,
	float zf );

// Build an ortho projection matrix. (left-handed)
Matrix* D3DXMatrixOrthoOffCenterLH
	( Matrix *pOut, float l, float r, float b, float t, float zn,
	float zf );

void D3DXMatrixDecompose( 
	Vector3* pOutScale, 
	Quaternion* pOutRotation, 
	Vector3* pOutTranslation, 
	const Matrix* pM );

// Build a matrix which flattens geometry into a plane, as if casting
// a shadow from a light.
Matrix* D3DXMatrixShadow( Matrix* out, const Vector4* light, const Plane* plane );

// Build a matrix which reflects the coordinate system about a plane
Matrix* D3DXMatrixReflect( Matrix* out, const Plane* plane );

#endif // Matrix_h