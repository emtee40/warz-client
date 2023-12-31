#ifndef	__ETERNITY_POINT3D_H
#define	__ETERNITY_POINT3D_H

#include "r3dMath.h"

class r3dPoint3D;
class r3dBox3D;
class r3dMatrix;
typedef r3dPoint3D r3dVector;
typedef r3dBox3D  r3dBoundBox;

extern	void r3dRotateVectorAboutVector(const r3dPoint3D& src, r3dPoint3D& dest, const r3dPoint3D& RotVec, float sin_a, float cos_a);

class r3dPoint2D
{
 public:
	union	{  float X, x; };
	union	{  float Y, y; };

	r3dPoint2D() {};
	r3dPoint2D(float xx, float yy) : X(xx), Y(yy) {};

	operator float*       ()       { return &X; }
	operator const float* () const { return &X; }
	float  operator [](int idx) const { return (&X)[idx]; }
	float& operator [](int idx)       { return (&X)[idx]; }

	float   Length() const
	{
		return sqrtf(X*X + Y*Y);
	}
	float   LengthSq() const
	{
		return X*X + Y*Y;
	}

	float   Dot(const r3dPoint2D& b) const
	{
		return X*b.X + Y*b.Y;
	}

	// project cur point to line ( p - point of line, n - normal
	r3dPoint2D 	Project(const r3dPoint2D& p, const r3dPoint2D& n) const
	{
		r3dPoint2D n_norm = n;
		n_norm.Normalize ();
		r3dPoint2D vDiff = ((*this)-p);
		r3dPoint2D vProj;
		float fDiffLen = vDiff.Length();
		if ( fDiffLen < 0.0001f )
			vProj = p;
		else
		{
			r3dPoint2D vDiffNorm = vDiff / fDiffLen;
			vProj = p + n_norm * fDiffLen*(n_norm.Dot(vDiffNorm));
		}

		return vProj;
	}

	void	Assign(float x, float y) { X = x; Y = y; }

	/*
	 *	normalize a 2d vec
	 */
	void	Normalize()
	{
		float invMag = r3dInvSqrt( x * x + y * y );
		if( invMag > 0 )
		{
			x *= invMag;
			y *= invMag;
		}
	}

	r3dPoint2D& operator+=(const r3dPoint2D& p)
	{
		x += p.x;
		y += p.y;
		return *this;
	}

	r3dPoint2D& operator-=(const r3dPoint2D& p)
	{
		x -= p.x;
		y -= p.y;
		return *this;
	}

	r3dPoint2D& operator*=( float inScaler )
	{
		x *= inScaler;
		y *= inScaler;
		return *this;
	}

	r3dPoint2D& operator/=( float inScaler )
	{
		x /= inScaler;
		y /= inScaler;
		return *this;
	}

	r3dPoint2D operator + (const r3dPoint2D& P1) const
	{
		return r3dPoint2D(X + P1.X, Y + P1.Y);
	}

	r3dPoint2D operator - (const r3dPoint2D& P1) const
	{
		return r3dPoint2D(X - P1.X, Y - P1.Y);
	}

	r3dPoint2D operator * (float inScaler) const
	{
		return r3dPoint2D (X*inScaler, Y*inScaler);
	}

	r3dPoint2D operator / (float inScaler) const
	{
		return r3dPoint2D (X/inScaler, Y/inScaler);
	}
};


//----------------------------------------------------------------
class r3dPoint3D
//----------------------------------------------------------------
{
  friend class r3dMatrix;

  public:
	union {	float X, x; };
	union { float Y, y; };
	union { float Z, z; };

R3D_FORCEINLINE	r3dPoint3D() {}
R3D_FORCEINLINE	r3dPoint3D(float xx, float yy, float zz) { 
	  x = xx; y = yy; z = zz; 
	}

	explicit r3dPoint3D( const D3DXVECTOR3& v )
		: x( v.x ), y( v.y ), z( v.z )
	{ 
	}

R3D_FORCEINLINE	operator float* () { 
	  return &x; 
	}
R3D_FORCEINLINE	operator const float* () const { 
	  return &x; 
	}
R3D_FORCEINLINE	float& operator[] (int idx) { 
	  return (&x)[idx]; 
	}
R3D_FORCEINLINE	const float& operator[] (int idx) const	{ 
	  return (&x)[idx]; 
	}

R3D_FORCEINLINE	void		Assign(float _x, float _y, float _z) { 
	  x = _x; y = _y; z = _z; 
	}
R3D_FORCEINLINE	void		Assign(const r3dPoint3D &v2) { 
	  x = v2.x; y = v2.y; z = v2.z; 
	}
R3D_FORCEINLINE void		Assign(const r3dPoint2D &v) {
	x = v.x; y=v.y; z = 0;
	}
R3D_FORCEINLINE	D3DXVECTOR3* d3dx() {
	  assert(sizeof(D3DXVECTOR3) == sizeof(*this));
	  return (D3DXVECTOR3*)&x;
	}
R3D_FORCEINLINE	const D3DXVECTOR3* d3dx() const {
	  assert(sizeof(D3DXVECTOR3) == sizeof(*this));
	  return (const D3DXVECTOR3*)&x;
	}

	int 		IsVoid() const;
	float 		Length() const;
	float		LengthSq() const;
	float		LengthApprox() const;			// Approximate length of vector (within 12%)
  	float 		Dot(const r3dPoint3D& b) const;
  	float		DegreesWith(const r3dPoint3D& b) const;
  	r3dPoint3D & Normalize();
  	r3dPoint3D 	NormalizeTo() const;
  	r3dPoint3D 	Cross(const r3dPoint3D& b) const;
	int 		AlmostEqual(const r3dPoint3D& n2) const;
	int 		AlmostEqual(const r3dPoint3D& n2, float delta) const;
	float		MaxElement() const; // returns max(max(x,y), z)

friend	int	 	operator == (const r3dPoint3D& One,  const r3dPoint3D& Two);
friend	int	 	operator != (const r3dPoint3D& One,  const r3dPoint3D& Two);

	r3dPoint3D 	operator + (const r3dPoint3D& P1) const;
	r3dPoint3D 	operator - (const r3dPoint3D& P1) const;
	r3dPoint3D 	operator * (const r3dPoint3D& P1) const;
	r3dPoint3D 	operator / (const r3dPoint3D& P1) const;
	r3dPoint3D 	operator + (float Num) const;
	r3dPoint3D 	operator - (float Num) const;
	r3dPoint3D 	operator * (float Num) const;
	r3dPoint3D 	operator / (float Num) const;
friend	r3dPoint3D	operator * (float Num, const r3dPoint3D& p);

	r3dPoint3D& 	operator += (const r3dPoint3D& p);
	r3dPoint3D& 	operator -= (const r3dPoint3D& p);
	r3dPoint3D& 	operator += (float Num);
	r3dPoint3D& 	operator -= (float Num);
	r3dPoint3D& 	operator *= (float Num);
	r3dPoint3D& 	operator /= (float Num);

	r3dPoint3D 	operator - () const;
   	//r3dPoint3D 	operator () (float len);

 	r3dPoint3D 	operator *= ( r3dMatrix& m);
 	r3dPoint3D 	operator *  ( r3dMatrix& m);

 	void 		Rotate(r3dMatrix& m, r3dPoint3D& dst);
	void		Rotate(float xAngle, float yAngle, float zAngle,  r3dPoint3D& About);
	void		RotateX(float Angle,  r3dPoint3D& About);
	void		RotateY(float Angle,  r3dPoint3D& About);
	void		RotateZ(float Angle,  r3dPoint3D& About);
	void		Rotate(float *m,  r3dPoint3D& r, r3dPoint3D& dst);

R3D_FORCEINLINE	r3dPoint3D 	Project(const r3dPoint3D& n) const
  	{
	  r3dPoint3D dest = *this - (n * n.Dot(*this));
    	  return dest;
  	}

  //
  // Rotation 
  //
  float GetYaw()   ;	// Y
  float GetPitch() ;	// X
  float GetRoll()  ;	// Z

  void  RotateAroundX(float angle);
  void  RotateAroundX(float angle, r3dPoint3D& dest) ;
  void  RotateAroundX(float sin_x, float cos_x);
  void  RotateAroundX(float sin_x, float cos_x, r3dPoint3D& dest) ;

  void  RotateAroundY(float angle);
  void  RotateAroundY(float angle, r3dPoint3D& dest) ;
  void  RotateAroundY(float sin_y, float cos_y);
  void  RotateAroundY(float sin_y, float cos_y, r3dPoint3D& dest) ;

  void  RotateAroundZ(float angle);
  void  RotateAroundZ(float angle, r3dPoint3D& dest) ;
  void  RotateAroundZ(float sin_z, float cos_z);
  void  RotateAroundZ(float sin_z, float cos_z, r3dPoint3D& dest) ;

  void  RotateAroundVector(const r3dPoint3D& RotVec, float angle);
  void  RotateAroundVector(const r3dPoint3D& RotVec, float angle, r3dPoint3D& dest) ;
  void  RotateAroundVector(const r3dPoint3D& RotVec, float sin_a, float cos_a);
  void  RotateAroundVector(const r3dPoint3D& RotVec, float sin_a, float cos_a, r3dPoint3D& dest) ;


  inline uint32_t GetPacked() const;

};

inline const r3dPoint3D ElementalMinimum( const r3dPoint3D& lhs, const r3dPoint3D& rhs )
{
	return r3dPoint3D( R3D_MIN( lhs.x, rhs.x ), R3D_MIN( lhs.y, rhs.y ), R3D_MIN( lhs.z, rhs.z ) );
}
inline const r3dPoint3D ElementalMaximum( const r3dPoint3D& lhs, const r3dPoint3D& rhs )
{
	return r3dPoint3D( R3D_MAX( lhs.x, rhs.x ), R3D_MAX( lhs.y, rhs.y ), R3D_MAX( lhs.z, rhs.z ) );
}


inline uint32_t r3dPoint3D::GetPacked() const
{	
	return ( 0xff000000 
		| ( ( uint32_t ) ( ( x * 127.5f ) + 127.5f ) << 16 )
		| ( ( uint32_t ) ( ( y * 127.5f ) + 127.5f ) << 8 ) 
		| ( ( uint32_t ) ( ( z * 127.5f ) + 127.5f ) ) );
}

// sanity check, sometimes r3dPoint3D used as D3DXVector3
enum {
  R3D_SIZEOF_POINT3D     = sizeof(r3dPoint3D),
  R3D_SIZEOF_D3DXVECTOR3 = sizeof(D3DXVECTOR3),
};
#if R3D_SIZEOF_POINT3D != R3D_SIZEOF_D3DXVECTOR3
  #error sizeof(D3DXVECTOR3) != sizeof(r3dPoint3D)
#endif

//----------------------------------------------------------------
class r3dMatrix
//----------------------------------------------------------------
{
  friend class r3dPoint3D;

  public:
	r3dPoint3D vRight, vUp, vForw;

  operator  float* ()                 { return (float*)&vRight; }

        r3dPoint3D& operator [] (int idx)        { return (&vRight)[idx]; }
const	r3dPoint3D& operator [] (int idx) const	{ return (&vRight)[idx]; }

  inline r3dMatrix& SetIdentity()
  {
    vRight.Assign(1, 0, 0);
    vUp.   Assign(0, 1, 0);
    vForw. Assign(0, 0, 1);
    return *this;
  }
  
  inline r3dMatrix& Assign(const r3dPoint3D& vR, const r3dPoint3D& vU, const r3dPoint3D& vF)
  {
    vRight = vR;
    vUp    = vU;
    vForw  = vF;
    return *this;
  }

  inline r3dMatrix& Assign(float a11, float a12, float a13,
                           float a21, float a22, float a23,
                           float a31, float a32, float a33)
  {
    vRight.Assign(a11, a12, a13);
    vUp   .Assign(a21, a22, a23);
    vForw .Assign(a31, a32, a33);
    return *this;
  }

  inline r3dMatrix& SetColumn(int col, r3dPoint3D &v)
  {
    vRight[col] = v[0];
    vUp   [col] = v[1];
    vForw [col] = v[2];

    return *this;
  }

  inline float Det() 
  {
    return vRight.Dot(vUp.Cross(vForw));
  }

};

//----------------------------------------------------------------
class r3dBox3D
//----------------------------------------------------------------
{
  public:
 	r3dPoint3D 	Org;
 	r3dPoint3D 	Size;

  public:
	BOOL		Intersect( const r3dBox3D &b) const;
	BOOL		ContainsPoint(const r3dPoint3D& P) const;
	BOOL		ContainsPoint2D(const r3dPoint3D& P) const;
	BOOL		ContainsBox( const r3dBoundBox &P) const;
	BOOL		ContainsRay(const r3dPoint3D& vStart, const r3dPoint3D& vNormalizedDirection, float RayLen, float *dist) const;
	void		Grow(const r3dPoint3D& vMove, r3dBoundBox &OutBox) const;

	void		Grow	( float fAdd );
	void		GrowByCoef( float fCoef );

	void		InitForExpansion();
	void		ExpandTo( const r3dPoint3D& vP );
	void		ExpandTo( const r3dBox3D& box );

	void		Transform	( const r3dMatrix * pM );
	r3dPoint3D	Center		() const;

	void		GetCorners	(r3dPoint3D pts[8]) const;

};

class r3dSegment3
{
  public:
    // The segment is represented as P+t*D, where P is the segment origin,
    // D is a unit-length direction vector and |t| <= e.  The value e is
    // referred to as the extent of the segment.  The end points of the
    // segment are P-e*D and P+e*D.  The user must ensure that the direction
    // vector is unit-length.  The representation for a segment is analogous
    // to that for an oriented bounding box.  P is the center, D is the
    // axis direction, and e is the extent.

	r3dPoint3D	Origin;
	r3dPoint3D	Direction;
	float		Extent;

	r3dPoint3D	GetPosEnd () const
	{
	  return Origin + Extent*Direction;
	}
	r3dPoint3D	GetNegEnd () const
	{
	  return Origin - Extent*Direction;
	}
};

	float r3dDistSegment3Segment3_GetSquared(r3dSegment3 &m_rkSegment0, r3dSegment3 &m_rkSegment1);
	float r3dDistVector3Triangle3_GetSquared(const r3dPoint3D& m_rkVector, r3dPoint3D *m_rkTriangle_V[3]);
	float r3dDistSegment3Triangle3_GetSquared(r3dSegment3 &m_rkSegment, r3dPoint3D *m_rkTriangle_V[3]);

	float r3dDistPoint3DSegment3D(const r3dPoint3D& p, const r3dPoint3D& s1, const r3dPoint3D& s2);
	float r3dDistPoint3DLine3D(const r3dPoint3D& p, const r3dPoint3D& s1, const r3dPoint3D& s2);

	float r3dDistancePointLine(const r3dPoint3D& p, const r3dPoint3D& l1, const r3dPoint3D& l2, float* dist_on_line);
	float r3dDistancePointSegment(const r3dPoint3D& p, const r3dPoint3D& l1, const r3dPoint3D& l2);


inline
void r3dBox3D::Grow(const r3dPoint3D& vMove, r3dBoundBox &b) const
{
	float	d;		// delta of coordinate movement

  // d = Position.##n - PrevPosition.##n;	   	

#define CALC_AXIS(n) 				\
  d = vMove.##n;				\
  if(d > 0.0f) {				\
    b.Org.##n  = Org.##n - d;			\
    b.Size.##n = Size.##n + d +d;			\
  }                                             \
  else {                                        \
    b.Org.##n  = Org.##n  + d;      		\
    b.Size.##n = Size.##n - d;			\
  }

  CALC_AXIS( X );
  CALC_AXIS( Y );
  CALC_AXIS( Z );

#undef CALC_AXIS
}

//--------------------------------------------------------------------------------------------------------
inline void r3dBox3D::Grow( float fAdd )
{
	Size.x += fAdd;
	Size.y += fAdd;
	Size.z += fAdd;

	float fHAdd = 0.5f * fAdd;

	Org.x -= fHAdd;
	Org.y -= fHAdd;
	Org.z -= fHAdd;
}

inline void	r3dBox3D::GrowByCoef( float fCoef )
{
	r3dVector toAdd = Size * fCoef;

	Size	+= toAdd;
	Org		-= toAdd * 0.5f;
}

//--------------------------------------------------------------------------------------------------------
inline r3dPoint3D r3dBox3D::Center() const
{
	return Org + Size * 0.5f;
}

inline BOOL r3dBox3D::Intersect(const r3dBox3D &b2) const
{
	float	Max1, Max2;

  Max1 = Org.X + Size.X;
  Max2 = b2.Org.X + b2.Size.X;
  if((Max1 < b2.Org.X) || (Org.X > Max2)) return 0;

  Max1 = Org.Y + Size.Y;
  Max2 = b2.Org.Y + b2.Size.Y;
  if((Max1 < b2.Org.Y) || (Org.Y > Max2)) return 0;

  Max1 = Org.Z + Size.Z;
  Max2 = b2.Org.Z + b2.Size.Z;
  if((Max1 < b2.Org.Z) || (Org.Z > Max2)) return 0;

  return 1;
}


inline
BOOL r3dBox3D::ContainsPoint(const r3dPoint3D& P) const
{
 r3dPoint3D Max1;

 Max1 = Org + Size;

 if (P.X < Org.X) return 0;
 if (P.Y < Org.Y) return 0;
 if (P.Z < Org.Z) return 0;

 if (P.X > Max1.X) return 0;
 if (P.Y > Max1.Y) return 0;
 if (P.Z > Max1.Z) return 0;

  return 1;
}


inline
BOOL r3dBox3D::ContainsBox( const r3dBoundBox &P) const
{
 r3dPoint3D Max1, Max2;

 Max1 = Org + Size;
 Max2 = P.Org + P.Size;

 if (P.Org.X < Org.X) return 0;
 if (P.Org.Y < Org.Y) return 0;
 if (P.Org.Z < Org.Z) return 0;
 
 if (Max2.X > Max1.X) return 0;
 if (Max2.Y > Max1.Y) return 0;
 if (Max2.Z > Max1.Z) return 0;

  return 1;
}



inline
BOOL r3dBox3D::ContainsPoint2D(const r3dPoint3D& P) const
{
 r3dPoint3D Max1;

 Max1 = Org + Size;

 if (P.X < Org.X) return 0;
 if (P.Z < Org.Z) return 0;

 if (P.X > Max1.X) return 0;
 if (P.Z > Max1.Z) return 0;

  return 1;
}

inline void r3dBox3D::GetCorners(r3dPoint3D pts[8]) const
{
	pts[ 0 ] = r3dPoint3D( Org.x, Org.y, Org.z );
	pts[ 1 ] = r3dPoint3D( Org.x, Org.y + Size.y, Org.z );
	pts[ 2 ] = r3dPoint3D( Org.x, Org.y + Size.y, Org.z + Size.z );
	pts[ 3 ] = r3dPoint3D( Org.x, Org.y, Org.z + Size.z );

	pts[ 4 ] = r3dPoint3D( Org.x + Size.x, Org.y, Org.z );
	pts[ 5 ] = r3dPoint3D( Org.x + Size.x, Org.y + Size.y, Org.z );
	pts[ 6 ] = r3dPoint3D( Org.x + Size.x, Org.y + Size.y, Org.z + Size.z );
	pts[ 7 ] = r3dPoint3D( Org.x + Size.x, Org.y, Org.z + Size.z );
}



/////////////////////////////////////////////////////////////////////
// Inlines
////////////////////////////////////////////////////////////////////

// 2d

R3D_FORCEINLINE r3dPoint2D operator * (float Num, const r3dPoint2D& p)
{
	return r3dPoint2D(Num * p.X, Num * p.Y);
}

// 3d

inline int r3dPoint3D::IsVoid() const
{
 return X == 0 && Y == 0 && Z == 0;
}

R3D_FORCEINLINE float r3dPoint3D::Length() const
{
 return sqrtf(X*X + Y*Y + Z*Z);
}

R3D_FORCEINLINE float r3dPoint3D::MaxElement() const
{
	return R3D_MAX(R3D_MAX(X,Y),Z);
}

R3D_FORCEINLINE float r3dPoint3D::LengthSq() const
{
  return X*X + Y*Y + Z*Z;
}

// Approximate length of vector (within 12%)
inline float r3dPoint3D::LengthApprox() const
{
	float	min, med, max;
	float	temp;

  max = R3D_ABS(X);
  med = R3D_ABS(Y);
  min = R3D_ABS(Z);

  if(max < med) {
    temp = max;
    max  = med;
    med  = temp;
  }

  if(max < min) {
    temp = max;
    max  = min;
    min  = temp;
  }

  return max + ((med + min) * 0.25f);
}

R3D_FORCEINLINE float r3dPoint3D::Dot(const r3dPoint3D& b) const
{
  return X * b.X + Y * b.Y + Z * b.Z;
}

inline float r3dPoint3D::DegreesWith(const r3dPoint3D& b) const
{
  float dot = Dot(b);

  if(dot >= 1)  return 0;
  if(dot <= -1) return 180;

  return R3D_RAD2DEG(acosf(dot));
}
  
inline r3dPoint3D& r3dPoint3D::Normalize()
{
  float len = Length();
  if (len > 0)
  {
	  *this *= (1.0f /len );
  }
  return *this;
}

inline r3dPoint3D r3dPoint3D::NormalizeTo() const
{
  r3dPoint3D dest;
  dest = *this * (1.0f / Length());
  return dest;
}

inline r3dPoint3D r3dPoint3D::Cross(const r3dPoint3D& b)  const
{
  return r3dPoint3D(
    Y * b.Z - Z * b.Y, 
    Z * b.X - X * b.Z,
    X * b.Y - Y * b.X);
}

inline int r3dPoint3D::AlmostEqual(const r3dPoint3D& n2) const
{
  return R3D_ABS(X - n2.X) <= R3D_EPSILON &&
         R3D_ABS(Y - n2.Y) <= R3D_EPSILON &&
         R3D_ABS(Z - n2.Z) <= R3D_EPSILON;
}

inline int r3dPoint3D::AlmostEqual(const r3dPoint3D& n2, float delta) const
{
	return R3D_ABS(X - n2.X) <= delta &&
		R3D_ABS(Y - n2.Y) <= delta &&
		R3D_ABS(Z - n2.Z) <= delta;
}

inline int operator == (const r3dPoint3D& One, const r3dPoint3D& Two)
{
  return One.X == Two.X && One.Y == Two.Y && One.Z == Two.Z;
}

inline int operator != (const r3dPoint3D& One, const r3dPoint3D& Two)
{
  return One.X != Two.X || One.Y != Two.Y || One.Z != Two.Z;
}

R3D_FORCEINLINE r3dPoint3D r3dPoint3D::operator + (const r3dPoint3D& P1) const
{
  return r3dPoint3D(X + P1.X, Y + P1.Y, Z + P1.Z);
}

R3D_FORCEINLINE r3dPoint3D r3dPoint3D::operator - (const r3dPoint3D& P1) const
{
  return r3dPoint3D(X - P1.X, Y - P1.Y, Z - P1.Z);
}

R3D_FORCEINLINE r3dPoint3D r3dPoint3D::operator * (const r3dPoint3D& P1) const
{
  return r3dPoint3D(X * P1.X, Y * P1.Y, Z * P1.Z);
}

R3D_FORCEINLINE r3dPoint3D r3dPoint3D::operator / (const r3dPoint3D& P1) const
{
  return r3dPoint3D(X / P1.X, Y / P1.Y, Z / P1.Z);
}

R3D_FORCEINLINE r3dPoint3D r3dPoint3D::operator + (float Num) const
{
  return r3dPoint3D(X + Num, Y + Num, Z + Num);
}

R3D_FORCEINLINE r3dPoint3D r3dPoint3D::operator - (float Num) const
{
  return r3dPoint3D(X - Num, Y - Num, Z - Num);
}

R3D_FORCEINLINE r3dPoint3D r3dPoint3D::operator * (float Num) const
{
  return r3dPoint3D(X * Num, Y * Num, Z * Num);
}

R3D_FORCEINLINE r3dPoint3D r3dPoint3D::operator / (float Num) const
{
  if(Num)
    return r3dPoint3D(X / Num, Y / Num, Z / Num);
  return r3dPoint3D(0, 0, 0);
}

R3D_FORCEINLINE r3dPoint3D operator * (float Num, const r3dPoint3D& p)
{
  return r3dPoint3D(Num * p.X, Num * p.Y, Num * p.Z);
}


R3D_FORCEINLINE r3dPoint3D& r3dPoint3D::operator += (const r3dPoint3D& p)
{
 X += p.X;
 Y += p.Y;
 Z += p.Z;
 return *this;
}

R3D_FORCEINLINE r3dPoint3D& r3dPoint3D::operator -= (const r3dPoint3D& p)
{
 X -= p.X;
 Y -= p.Y;
 Z -= p.Z;
 return *this;
}

R3D_FORCEINLINE r3dPoint3D& r3dPoint3D::operator += (float Num)
{
 X += Num;
 Y += Num;
 Z += Num;
 return *this;
}

R3D_FORCEINLINE r3dPoint3D& r3dPoint3D::operator -= (float Num)
{
 X -= Num;
 Y -= Num;
 Z -= Num;
 return *this;
}

R3D_FORCEINLINE r3dPoint3D& r3dPoint3D::operator *= (float Num)
{
 X *= Num;
 Y *= Num;
 Z *= Num;
 return *this;
}

R3D_FORCEINLINE r3dPoint3D& r3dPoint3D::operator /= (float Num)
{
 if (Num)
 {
  float t = 1.0f/Num;
  X *= t;
  Y *= t;
  Z *= t;
 } 
 return *this;
}

R3D_FORCEINLINE r3dPoint3D r3dPoint3D::operator - () const
{
  return r3dPoint3D(-X, -Y, -Z);
}
 
/*@
inline r3dPoint3D r3dPoint3D::operator() (float len) 
{
 r3dPoint3D v = *this;

 if(!IsVoid())
 {
  len /= Length();
  v.X *= len;
  v.Y *= len;
  v.Z *= len;
 }

 return v;
}
*/

//----------------------------------------------------------------
inline r3dPoint3D r3dPoint3D::operator *= ( r3dMatrix& m)
//----------------------------------------------------------------
{
  float Xt = X * m[0][0] + Y * m[1][0] + Z * m[2][0];
  float Yt = X * m[0][1] + Y * m[1][1] + Z * m[2][1];
  float Zt = X * m[0][2] + Y * m[1][2] + Z * m[2][2];

  Assign(Xt, Yt, Zt);
  return *this;
}

//----------------------------------------------------------------
inline r3dPoint3D r3dPoint3D::operator * ( r3dMatrix& m) 
//----------------------------------------------------------------
{
  return r3dPoint3D(
    X * m[0][0] + Y * m[1][0] + Z * m[2][0],
    X * m[0][1] + Y * m[1][1] + Z * m[2][1],
    X * m[0][2] + Y * m[1][2] + Z * m[2][2]);
}

//----------------------------------------------------------------
inline void r3dPoint3D::Rotate(r3dMatrix& m, r3dPoint3D& dst) 
//----------------------------------------------------------------
{
  float *a = (float *)&m;
  dst.X = X * a[0] + Y * a[3] + Z * a[6];
  dst.Y = X * a[1] + Y * a[4] + Z * a[7];
  dst.Z = X * a[2] + Y * a[5] + Z * a[8];
}

inline void r3dPoint3D::Rotate(float xAngle, float yAngle, float zAngle, r3dPoint3D& RotatePoint)
{
  r3dMatrix Matrix;
  r3dBuildRotationMatrix(Matrix, xAngle, yAngle, zAngle);

  r3dPoint3D v(X - RotatePoint.X, Y - RotatePoint.Y, Z - RotatePoint.Z);
  v *= Matrix;
  X = v.X + RotatePoint.X;
  Y = v.Y + RotatePoint.Y;
  Z = v.Z + RotatePoint.Z;
}


inline void r3dPoint3D::RotateX(float Angle,  r3dPoint3D& About)
{
  // rotate on x-axis
  if(Angle)
  {
    float oy = Y - About.Y;
    float oz = Z - About.Z;
    if(!oy && !oz) return;

    float xCos = r3dFastCos(Angle);
    float xSin = r3dFastSin(Angle);
    Y = oy * xCos - oz * xSin + About.Y;
    Z = oy * xSin + oz * xCos + About.Z;
  }
}

inline void r3dPoint3D::RotateY(float Angle,  r3dPoint3D& About)
{
  // rotate on y-axis
  if(Angle)
  {
    float oz = float(Z - About.Z);
    float ox = float(X - About.X);
    if(!oz && !ox) return;

    float yCos = r3dFastCos(Angle);
    float ySin = r3dFastSin(Angle);
    Z = oz * yCos - ox * ySin + About.Z;
    X = oz * ySin + ox * yCos + About.X;
  }
}

inline void r3dPoint3D::RotateZ(float Angle,  r3dPoint3D& About)
{
  // rotate on z-axis
  if(Angle)
  {
    float ox = X - About.X;
    float oy = Y - About.Y;
    if(!ox && !oy) return;

    float zCos = r3dFastCos(Angle);
    float zSin = r3dFastSin(Angle);
    X = ox * zSin - oy * zCos + About.X;
    Y = ox * zCos + oy * zSin + About.Y;
  }
}


inline float r3dPoint3D::GetYaw() 
{
  float yaw = atan2f(-X, Z);
  if(yaw < 0) yaw += 2*R3D_PI;
  return yaw;
}

inline float r3dPoint3D::GetPitch() 
{
  float forw  = sqrtf(X*X + Z*Z);
  float pitch = atan2f(Y, forw);
  if(pitch < 0) pitch += 2*R3D_PI;
  return pitch;
}

inline float r3dPoint3D::GetRoll() 
{
  float roll = 0;
  float forw = sqrtf(X*X + Z*Z);
  if(X && Y)
  {
    roll = -atan2f(Y, forw);
    if(roll < 0) roll += 2*R3D_PI;
  }
  return roll;
}

inline void r3dPoint3D::Rotate(float *m, r3dPoint3D& r, r3dPoint3D& dst)
{
  float Xt = X - r.X, Yt = Y - r.Y, Zt = Z - r.Z;
  dst.X = Xt * m[0] + Yt * m[3] + Zt * m[6] + r.X;
  dst.Y = Xt * m[1] + Yt * m[4] + Zt * m[7] + r.Y;
  dst.Z = Xt * m[2] + Yt * m[5] + Zt * m[8] + r.Z;
}

// around X - YZ =================================================
inline void  r3dPoint3D::RotateAroundX(float xAngle)
//----------------------------------------------------------------
{
  RotateAroundX(r3dFastSin(xAngle), r3dFastCos(xAngle));
}

//----------------------------------------------------------------
inline void r3dPoint3D::RotateAroundX(float xAngle, r3dPoint3D& v) 
//----------------------------------------------------------------
{
  RotateAroundX(r3dFastSin(xAngle), r3dFastCos(xAngle), v);
}

//----------------------------------------------------------------
inline void  r3dPoint3D::RotateAroundX(float sin_x, float cos_x)
//----------------------------------------------------------------
{
  float Yt = Y * cos_x - Z * sin_x;
         Z = Y * sin_x + Z * cos_x;
         Y = Yt;
}

//----------------------------------------------------------------
inline void r3dPoint3D::RotateAroundX(float sin_x, float cos_x, r3dPoint3D& v) 
//----------------------------------------------------------------
{
  v.X = X;
  v.Y = Y * cos_x - Z * sin_x;
  v.Z = Y * sin_x + Z * cos_x;
}


// around Y - ZX =================================================
//----------------------------------------------------------------
inline void  r3dPoint3D::RotateAroundY(float yAngle)
//----------------------------------------------------------------
{
  RotateAroundY(r3dFastSin(yAngle), r3dFastCos(yAngle));
}

//----------------------------------------------------------------
inline void r3dPoint3D::RotateAroundY(float yAngle, r3dPoint3D& v) 
//----------------------------------------------------------------
{
  RotateAroundY(r3dFastSin(yAngle), r3dFastCos(yAngle), v);
}

//----------------------------------------------------------------
inline void  r3dPoint3D::RotateAroundY(float sin_y, float cos_y)
//----------------------------------------------------------------
{
  float Zt = Z * cos_y - X * sin_y;
         X = Z * sin_y + X * cos_y;
         Z = Zt;
}

//----------------------------------------------------------------
inline void r3dPoint3D::RotateAroundY(float sin_y, float cos_y, r3dPoint3D& v) 
//----------------------------------------------------------------
{
  v.X = Z * sin_y + X * cos_y;
  v.Y = Y;
  v.Z = Z * cos_y - X * sin_y;
}

// around Z - XY =================================================
//----------------------------------------------------------------
inline void r3dPoint3D::RotateAroundZ(float zAngle, r3dPoint3D& v) 
//----------------------------------------------------------------
{
  RotateAroundZ(r3dFastSin(zAngle), r3dFastCos(zAngle), v);
}

//----------------------------------------------------------------
inline void  r3dPoint3D::RotateAroundZ(float zAngle)
//----------------------------------------------------------------
{
  RotateAroundZ(r3dFastSin(zAngle), r3dFastCos(zAngle));
}

//----------------------------------------------------------------
inline void  r3dPoint3D::RotateAroundZ(float sin_z, float cos_z)
//----------------------------------------------------------------
{
  float Xt = X * cos_z - Y * sin_z;
         Y = X * sin_z + Y * cos_z;
         X = Xt;
}

//----------------------------------------------------------------
inline void r3dPoint3D::RotateAroundZ(float sin_z, float cos_z, r3dPoint3D& v) 
//----------------------------------------------------------------
{
  v.X = X * cos_z - Y * sin_z;
  v.Y = X * sin_z + Y * cos_z;
  v.Z = Z;
}


inline void  r3dPoint3D::RotateAroundVector(const r3dPoint3D& RotVec, float angle)
{
  r3dRotateVectorAboutVector(*this, *this, RotVec, r3dFastSin(360-angle), r3dFastCos(360-angle));
}

inline void  r3dPoint3D::RotateAroundVector(const r3dPoint3D& RotVec, float angle, r3dPoint3D &dest) 
{
  r3dRotateVectorAboutVector(*this, dest, RotVec, r3dFastSin(360-angle), r3dFastCos(360-angle));
}

inline void  r3dPoint3D::RotateAroundVector(const r3dPoint3D& RotVec, float sin_a, float cos_a)
{
  r3dRotateVectorAboutVector(*this, *this, RotVec, sin_a, cos_a);
}

inline void  r3dPoint3D::RotateAroundVector(const r3dPoint3D& RotVec, float sin_a, float cos_a, r3dPoint3D &dest) 
{
  r3dRotateVectorAboutVector(*this, dest, RotVec, sin_a, cos_a);
}


#endif	// __ETERNITY_POINT3D_H

