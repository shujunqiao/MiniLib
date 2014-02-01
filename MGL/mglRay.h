#ifndef MGL_PIXMAP_H_INCLUDED__
#define MGL_PIXMAP_H_INCLUDED__

#include "../MML/mmlVector.h"
#include "mglTransform.h"

class mglObject;
class mglMaterial;

class mglRay
{
public:
	mmlVector<3>	position;
	mmlVector<3>	direction;
	float			length;
	unsigned int	mask;
public:
	void Set(const mmlVector<3> &p_pos, const mmlVector<3> &p_dir, float p_len, unsigned int p_mask = 0xffffffff)
	{
		position = p_pos;
		direction = mmlNormalize(p_dir);
		length = p_len;
		mask = p_mask;
	}
	void Transform(const mglTransform &p_transform)
	{
		const mmlMatrix<4,4> m4 = p_transform.GetWorldTransformMatrix();
		const mmlMatrix<3,3> m3 = mmlMatrix<3,3>(m4);
		position *= m4;
		direction *= m3;
	}
	void ReverseTransform(const mglTransform &p_transform)
	{
		const mmlMatrix<4,4> m4 = mmlInv(p_transform.GetWorldTransformMatrix());
		const mmlMatrix<3,3> m3 = mmlMatrix<3,3>(m4);
		position *= m4;
		direction *= m3;
	}
};

struct mglRayCollision
{
	mglObject			*object;
	const mglMaterial	*material;
	mmlVector<3>		point;
	mmlVector<3>		reflection;
	mmlVector<3>		normal;
};

#endif
