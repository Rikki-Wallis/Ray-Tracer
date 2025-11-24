#ifndef GTFM_H
#define GTFM_H

#include "../../qbLinAlg/qbVector.h"
#include "../../qbLinAlg/qbMatrix.h"
#include "ray.hpp"

namespace RT {
	// Direction flag values
	constexpr bool FWDTFORM = true;
	constexpr bool BCKTFORM = false;
}

class GTform {
public:
	// Constructor
	GTform();
	GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);

	// Destructor
	~GTform();

	// Set translation, scale and rotation components
	void SetTransform(const qbVector<double>& translation, const qbVector<double>& rotation, const qbVector<double>& scale);

	// Return transform matrices
	qbMatrix2<double> GetForward();
	qbMatrix2<double> GetBackward();

	// Apply transform
	Ray Apply(const Ray& inputRay, bool dirFlag);
	qbVector<double> Apply(const qbVector<double>& inputVector, bool dirFlag);

	// Overload operators
	friend GTform operator* (const GTform& lhs, const GTform& rhs);
	GTform& operator= (const GTform& rhs);

	// Debug
	void PrintMatrix(bool dirFlag);
	static void PrintVector(const qbVector<double>& vector);

// Functions
private:
	void Print(const qbMatrix2<double>& matrix);

// Members
private:
	qbMatrix2<double> m_fwdtfm{ 4, 4 };
	qbMatrix2<double> m_bcktfm{ 4, 4 };

};



#endif