#ifndef RAY_H
#define RAY_H

#include "../qbLinAlg/qbVector.h"

class Ray 
{
public:
	// Construcctor
	Ray(const qbVector<double>& point1, const qbVector<double>& point2);

	// Return point of ray
	qbVector<double> GetPoint1() const;
	qbVector<double> GetPoint2() const;

public:
	qbVector<double> m_point1{ 3 };
	qbVector<double> m_point2{ 3 };
	// Vector from point1 to point2
	qbVector<double> m_lab{ 3 };
};

#endif