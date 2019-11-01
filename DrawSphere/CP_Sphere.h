// CP_Sphere.h: ����CP_Point3D��CP_Vector3D��CP_Sphere
#ifndef CP_SPHERE_H
#define CP_SPHERE_H

#define PI2           6.28318530717958647692
#define PI            3.14159265358979323846
class CP_Point3D
{
public:
	double    m_x, m_y, m_z;
public:
	//���캯��
	CP_Point3D(double newx = 0.0, double newy = 0.0, double newz = 0.0) :m_x(newx), m_y(newy), m_z(newz) { };
}; // ��CP_Point3D�������

class CP_Vector3D
{
public:
	double    m_x, m_y, m_z;

public:
	CP_Vector3D(double newx = 0.0, double newy = 0.0, double newz = 0.0) :m_x(newx), m_y(newy), m_z(newz) { };
}; // ��CP_Vector3D�������
// ��������S(u, v)Ϊ:
// ����: x = m_center.m_x+m_radius * sin(v * PI) * cos(u * PI2);
//       y = m_center.m_y+m_radius * sin(v * PI) * sin(u * PI2);
//       z = m_center.m_z+m_radius * cos(v * PI);
// ����u��v�Ļ���������Ϊu, v \in [0, 1]��
class CP_Sphere
{
public:
	CP_Point3D  m_center;
	double  m_radius;
public:
	CP_Sphere();
	CP_Sphere(const CP_Point3D& c, double r);
	CP_Point3D mb_getPoint(double u, double v) const;
	CP_Vector3D mb_getUnitNormal(double u, double v) const;

	// normalFlag: true(������ȡ����); false(������ȡ����)
	void mb_drawSolid(bool normalFlag = true);
	void mb_drawWireframe();
}; // ��CP_Sphere�������

#endif
