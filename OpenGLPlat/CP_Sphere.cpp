// CP_Sphere.cpp: ʵ��CP_Sphere

#include "CP_Sphere.h"
#include "GL/GLU.H" // �Ѿ�����GL/GL.h

#include <math.h>

// //////////////////////////////////////////////////////////////
// ʵ����CP_Sphere��ʼ
CP_Sphere::CP_Sphere() : m_center(0.0, 0.0, 0.0), m_radius(1.0)
{
} // ��CP_Sphere���캯������

CP_Sphere::CP_Sphere(const CP_Point3D& c, double r)
	: m_center(c.m_x, c.m_y, c.m_z), m_radius(r)
{
} // ��CP_Sphere���캯������
CP_Point3D CP_Sphere::mb_getPoint(double u, double v) const
{
	double r1 = m_radius * sin(v * PI);
	double x = m_center.m_x + r1 * cos(u * PI2);
	double y = m_center.m_y + r1 * sin(u * PI2);
	double z = m_center.m_z + m_radius * cos(v * PI);
	CP_Point3D r(x, y, z);
	return r;
} // ��Ա����mb_getPoint����

CP_Vector3D CP_Sphere::mb_getUnitNormal(double u, double v) const
{
	double r1 = sin(v * PI);
	double x = -r1 * cos(u * PI2);
	double y = -r1 * sin(u * PI2);
	double z = -cos(v * PI);
	CP_Vector3D r(x, y, z);
	return r;
} // ��Ա����mb_getUnitNormal����

void CP_Sphere::mb_drawSolid(bool normalFlag)
{
	int i, j, k;
	int nu = 40;
	int nv = 20;
	double stepU = 1.0 / nu;
	double stepV = 1.0 / nv;
	double du, dv;
	CP_Point3D p, p0;
	CP_Vector3D v, v0;

	// �¶���������: ע��mb_getPoint(u, 0.0)��Ϊͬһ����
	p0 = mb_getPoint(0.0, 0.0);
	v0 = mb_getUnitNormal(0.0, 0.0);
	if (!normalFlag)
		v0 = CP_Vector3D(-v0.m_x, -v0.m_y, -v0.m_z);
	for (j = 0, du = 0.0; j < nu; j++)
	{
		glBegin(GL_POLYGON);
		glNormal3d(v0.m_x, v0.m_y, v0.m_z);
		glVertex3d(p0.m_x, p0.m_y, p0.m_z);
		p = mb_getPoint(du, stepV);
		v = mb_getUnitNormal(du, stepV);
		if (!normalFlag)
			v = CP_Vector3D(-v.m_x, -v.m_y, -v.m_z);
		glNormal3d(v.m_x, v.m_y, v.m_z);
		glVertex3d(p.m_x, p.m_y, p.m_z);
		du += stepU;
		p = mb_getPoint(du, stepV);
		v = mb_getUnitNormal(du, stepV);
		if (!normalFlag)
			v = CP_Vector3D(-v.m_x, -v.m_y, -v.m_z);
		glNormal3d(v.m_x, v.m_y, v.m_z);
		glVertex3d(p.m_x, p.m_y, p.m_z);
		glEnd();
	} // forѭ���ṹ����

		// �м���������
	for (i = 2, dv = stepV; i < nv; i++, dv += stepV)
	{
		for (j = 0, du = 0.0; j < nu; j++, du += stepU)
		{
			double uu[] = { du, du + stepU, du + stepU, du,       du };
			double vv[] = { dv, dv,       dv + stepV, dv + stepV, dv };
			glBegin(GL_POLYGON);
			for (k = 0; k < 3; k++)
			{
				p = mb_getPoint(uu[k], vv[k]);
				v = mb_getUnitNormal(uu[k], vv[k]);
				if (!normalFlag)
					v = CP_Vector3D(-v.m_x, -v.m_y, -v.m_z);
				glNormal3d(v.m_x, v.m_y, v.m_z);
				glVertex3d(p.m_x, p.m_y, p.m_z);
			} // �ڲ�(k)forѭ���ṹ����
			glEnd();
			glBegin(GL_POLYGON);
			for (k = 2; k < 5; k++)
			{
				p = mb_getPoint(uu[k], vv[k]);
				v = mb_getUnitNormal(uu[k], vv[k]);
				if (!normalFlag)
					v = CP_Vector3D(-v.m_x, -v.m_y, -v.m_z);
				glNormal3d(v.m_x, v.m_y, v.m_z);
				glVertex3d(p.m_x, p.m_y, p.m_z);
			} // �ڲ�(k)forѭ���ṹ����
			glEnd();
		} // �ڲ�(j)forѭ���ṹ����
	} // ���(i)forѭ���ṹ����

	 // �϶���������: ע��mb_getPoint(u, 1.0)��Ϊͬһ����
	p0 = mb_getPoint(0.0, 1.0);
	v0 = mb_getUnitNormal(0.0, 1.0);
	if (!normalFlag)
		v0 = CP_Vector3D(-v0.m_x, -v0.m_y, -v0.m_z);

	for (j = 0, du = 0.0; j < nu; j++)
	{
		glBegin(GL_POLYGON);
		glNormal3d(v0.m_x, v0.m_y, v0.m_z);
		glVertex3d(p0.m_x, p0.m_y, p0.m_z);
		p = mb_getPoint(du, 1 - stepV);
		v = mb_getUnitNormal(du, 1 - stepV);
		if (!normalFlag)
			v = CP_Vector3D(-v.m_x, -v.m_y, -v.m_z);
		glNormal3d(v.m_x, v.m_y, v.m_z);
		glVertex3d(p.m_x, p.m_y, p.m_z);
		du += stepU;
		p = mb_getPoint(du, 1 - stepV);
		v = mb_getUnitNormal(du, 1 - stepV);
		if (!normalFlag)
			v = CP_Vector3D(-v.m_x, -v.m_y, -v.m_z);
		glNormal3d(v.m_x, v.m_y, v.m_z);
		glVertex3d(p.m_x, p.m_y, p.m_z);
		glEnd();
	} // forѭ���ṹ����
} // ��Ա����mb_drawSolid����

void CP_Sphere::mb_drawWireframe()
{
	int i, j, k;
	int nu = 40;
	int nv = 20;
	double stepU = 1.0 / nu;
	double stepV = 1.0 / nv;
	double u, v;
	CP_Point3D p, p0;
	// �¶���������: ע��mb_getPoint(u, 0.0)��Ϊͬһ����
	glLineWidth(2.2f);
	p0 = mb_getPoint(0.0, 0.0);
	for (j = 0, u = 0.0; j < nu; j++)
	{
		glBegin(GL_LINE_LOOP);
		glVertex3d(p0.m_x, p0.m_y, p0.m_z);
		p = mb_getPoint(u, stepV);
		glVertex3d(p.m_x, p.m_y, p.m_z);
		u += stepU;
		p = mb_getPoint(u, stepV);
		glVertex3d(p.m_x, p.m_y, p.m_z);
		glEnd();
	} // forѭ���ṹ����
	 // �м���������
	for (i = 2, v = stepV; i < nv; i++, v += stepV)
	{
		for (j = 0, u = 0.0; j < nu; j++, u += stepU)
		{
			double uu[] = { u, u + stepU, u + stepU, u,       u };
			double vv[] = { v, v,       v + stepV, v + stepV, v };
			glBegin(GL_LINE_LOOP);
			for (k = 0; k < 3; k++)
			{
				p = mb_getPoint(uu[k], vv[k]);
				glVertex3d(p.m_x, p.m_y, p.m_z);
			} // �ڲ�(k)forѭ���ṹ����
			glEnd();
			glBegin(GL_LINE_LOOP);
			for (k = 2; k < 5; k++)
			{
				p = mb_getPoint(uu[k], vv[k]);
				glVertex3d(p.m_x, p.m_y, p.m_z);
			} // �ڲ�(k)forѭ���ṹ����
			glEnd();
		} // �ڲ�(j)forѭ���ṹ����
	} // ���(i)forѭ���ṹ����
	 // �϶���������: ע��mb_getPoint(u, 1.0)��Ϊͬһ����
	p0 = mb_getPoint(0.0, 1.0);
	for (j = 0, u = 0.0; j < nu; j++)
	{
		glBegin(GL_LINE_LOOP);
		glVertex3d(p0.m_x, p0.m_y, p0.m_z);
		p = mb_getPoint(u, 1 - stepV);
		glVertex3d(p.m_x, p.m_y, p.m_z);
		u += stepU;
		p = mb_getPoint(u, 1 - stepV);
		glVertex3d(p.m_x, p.m_y, p.m_z);
		glEnd();
	} // forѭ���ṹ����
} // ��Ա����mb_drawWireframe����

// ʵ����CP_Sphere����
// ///////////////////////////////////////////////////////////

