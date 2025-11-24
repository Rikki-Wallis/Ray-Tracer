#include "headers/gtfm.hpp"

// Constructor
GTform::GTform() {
	m_fwdtfm.SetToIdentity();
	m_bcktfm.SetToIdentity();
}

GTform::GTform(const qbMatrix2<double>& fwd, const qbMatrix2<double>& bck) {
	// Verift that the inputs are 4x4
	if ((fwd.GetNumRows() != 4) || (fwd.GetNumCols() != 4) || (bck.GetNumRows() != 4) || (bck.GetNumCols() != 4)) {
		throw std::invalid_argument("Cannot construct GTform, inputs are not all 4x4");
	}

	m_fwdtfm = fwd;
	m_bcktfm = bck;
}


// Destructor
GTform::~GTform() {

}

// Set transform
void GTform::SetTransform(const qbVector<double>& translation, const qbVector<double>& rotation, const qbVector<double>& scale) {
	// Define matrix for each component of the transform
	qbMatrix2<double> translationMatrix{ 4,4 };
	qbMatrix2<double> rotationMatrixX{ 4,4 };
	qbMatrix2<double> rotationMatrixY{ 4,4 };
	qbMatrix2<double> rotationMatrixZ{ 4,4 };
	qbMatrix2<double> scaleMatrix{ 4,4 };

	// Set these to identity
	translationMatrix.SetToIdentity();
	rotationMatrixX.SetToIdentity();
	rotationMatrixY.SetToIdentity();
	rotationMatrixZ.SetToIdentity();
	scaleMatrix.SetToIdentity();

	// Populate these with appropriate values.
	// Translation matrix
	translationMatrix.SetElement(0, 3, translation.GetElement(0));
	translationMatrix.SetElement(1, 3, translation.GetElement(1));
	translationMatrix.SetElement(2, 3, translation.GetElement(2));

	// Rotation matricies
	rotationMatrixZ.SetElement(0, 0, cos(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(0, 1, sin(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(1, 0, sin(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(1, 1, cos(rotation.GetElement(2)));

	rotationMatrixY.SetElement(0, 0, cos(rotation.GetElement(1)));
	rotationMatrixY.SetElement(0, 2, sin(rotation.GetElement(1)));
	rotationMatrixY.SetElement(2, 0, -sin(rotation.GetElement(1)));
	rotationMatrixY.SetElement(2, 2, cos(rotation.GetElement(1)));

	rotationMatrixX.SetElement(1, 1, cos(rotation.GetElement(0)));
	rotationMatrixX.SetElement(1, 2, -sin(rotation.GetElement(0)));
	rotationMatrixX.SetElement(2, 1, sin(rotation.GetElement(0)));
	rotationMatrixX.SetElement(2, 2, cos(rotation.GetElement(0)));

	// Scale Matrix
	scaleMatrix.SetElement(0, 0, scale.GetElement(0));
	scaleMatrix.SetElement(1, 1, scale.GetElement(1));
	scaleMatrix.SetElement(2, 2, scale.GetElement(2));


	// Combine to give the final forward transform matrix
	m_fwdtfm = translationMatrix * scaleMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ;

	// Compute backwards transform
	m_bcktfm = m_fwdtfm;
	m_bcktfm.Inverse();
}

// Return transform matrices
qbMatrix2<double> GTform::GetForward() {
	return m_fwdtfm;
}

qbMatrix2<double> GTform::GetBackward() {
	return m_bcktfm;
}

// Apply transform
Ray GTform::Apply(const Ray& inputRay, bool dirFlag) {
	// Create an output object
	Ray outputRay;

	// Apply transform
	outputRay.m_point1 = this->Apply(inputRay.m_point1, dirFlag);
	outputRay.m_point2 = this->Apply(inputRay.m_point2, dirFlag);
	outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;

	return outputRay;
}

qbVector<double> GTform::Apply(const qbVector<double>& inputVector, bool dirFlag) {
	// Convert inputVector to a 4 element vector
	std::vector<double> tempData{ inputVector.GetElement(0), inputVector.GetElement(1), inputVector.GetElement(2), 1.0 };
	qbVector<double> tempVector{ tempData };

	// reate a vector for the result
	qbVector<double> resultVector;

	if (dirFlag) {
		// Forward transform
		resultVector = m_fwdtfm * tempVector;
	}
	else {
		// Backward transform
		resultVector = m_bcktfm * tempVector;
	}

	// Reform the output as a 3-element vector
	qbVector<double> outputVector {std::vector<double> {resultVector.GetElement(0), resultVector.GetElement(1), resultVector.GetElement(2)}};

	return outputVector;
}

// Overload operators
GTform operator* (const GTform& lhs, const GTform& rhs) {
	// Form product of the two forward transforms
	qbMatrix2<double> fwdResult = lhs.m_fwdtfm * rhs.m_fwdtfm;

	// Compute the backward transform as the inverse of the forward transform
	qbMatrix2<double> bckResult = fwdResult;
	bckResult.Inverse();

	// Form final result
	GTform finalResult(fwdResult, bckResult);

	return finalResult;
}

GTform& GTform::operator= (const GTform& rhs) {
	// Make sure we are not assigning to ourself
	if (this == &rhs) {
		return *this;
	}

	m_fwdtfm = rhs.m_fwdtfm;
	m_bcktfm = rhs.m_bcktfm;

	return *this;
}

// Debug
void GTform::PrintMatrix(bool dirFlag) {
	if (dirFlag) {
		Print(m_fwdtfm);
	}
	else {
		Print(m_bcktfm);
	}
}

void GTform::Print(const qbMatrix2<double>& matrix) {
	int nRows = matrix.GetNumRows();
	int nCols = matrix.GetNumCols();

	for (int row = 0; row < nRows; ++row) {
		for (int col = 0; col < nCols; ++col) {
			std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(row, col) << " ";
		}

		std::cout << std::endl;
	}	
}

void GTform::PrintVector(const qbVector<double>& inputVector) {
	int nRows = inputVector.GetNumDims();
	for (int row = 0; row < nRows; ++row) {
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	}


}
