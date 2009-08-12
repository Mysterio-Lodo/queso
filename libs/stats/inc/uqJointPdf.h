/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------
 *
 * Copyright (C) 2008 The PECOS Development Team
 *
 * Please see http://pecos.ices.utexas.edu for more information.
 *
 * This file is part of the QUESO Library (Quantification of Uncertainty
 * for Estimation, Simulation and Optimization).
 *
 * QUESO is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QUESO is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QUESO. If not, see <http://www.gnu.org/licenses/>.
 *
 *--------------------------------------------------------------------------
 *
 * $Id$
 *
 * Brief description of this file: 
 * 
 *--------------------------------------------------------------------------
 *-------------------------------------------------------------------------- */

#ifndef __UQ_JOINT_PROB_DENSITY_H__
#define __UQ_JOINT_PROB_DENSITY_H__

#include <uqEnvironment.h>
#include <math.h>
#include <uqScalarFunction.h>

//*****************************************************
// Classes to accomodate a probability density.
//*****************************************************

//*****************************************************
// Base class
//*****************************************************
template<class V, class M>
class uqBaseJointPdfClass : public uqBaseScalarFunctionClass<V,M> {
public:
           uqBaseJointPdfClass(const char*                  prefix,
                               const uqVectorSetClass<V,M>& domainSet,
                               const V&                     domainExpVector,
                               const V&                     domainVarVector);
           uqBaseJointPdfClass(const char*                  prefix,
                               const uqVectorSetClass<V,M>& domainSet,
                               const V&                     domainExpVector);
           uqBaseJointPdfClass(const char*                  prefix,
                               const uqVectorSetClass<V,M>& domainSet);
  virtual ~uqBaseJointPdfClass();

  virtual       double                        actualValue  (const V& domainVector, const V* domainDirection, V* gradVector, M* hessianMatrix, V* hessianEffect) const = 0;
  virtual       double                        minus2LnValue(const V& domainVector, const V* domainDirection, V* gradVector, M* hessianMatrix, V* hessianEffect) const = 0;

//        const uqBaseScalarPdfClass<double>& component      (unsigned int componentId) const;
          const V&                            domainExpVector() const;
          const V&                            domainVarVector() const;

protected:
  using uqBaseScalarFunctionClass<V,M>::m_env;
  using uqBaseScalarFunctionClass<V,M>::m_prefix;
  using uqBaseScalarFunctionClass<V,M>::m_domainSet;

  V* m_domainExpVector;
  V* m_domainVarVector;

//std::vector<uqBaseScalarPdfClass<double>*> m_components; // FIXME: will need to be a parallel vector in case of a very large number of components
//uqBaseScalarPdfClass<double>               m_dummyComponent;
};

template<class V, class M>
uqBaseJointPdfClass<V,M>::uqBaseJointPdfClass(
  const char*                  prefix,
  const uqVectorSetClass<V,M>& domainSet,
  const V&                     domainExpVector,
  const V&                     domainVarVector)
  :
  uqBaseScalarFunctionClass<V,M>(((std::string)(prefix)+"pd_").c_str(), domainSet),
  m_domainExpVector(new V(domainExpVector)),
  m_domainVarVector(new V(domainVarVector))
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqBaseJointPdfClass<V,M>::constructor() [1]"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqBaseJointPdfClass<V,M>::constructor() [1]"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }
}

template<class V, class M>
uqBaseJointPdfClass<V,M>::uqBaseJointPdfClass(
  const char*                  prefix,
  const uqVectorSetClass<V,M>& domainSet,
  const V&                     domainExpVector)
  :
  uqBaseScalarFunctionClass<V,M>(((std::string)(prefix)+"pd_").c_str(), domainSet),
  m_domainExpVector(new V(domainExpVector    )),
  m_domainVarVector(domainSet.vectorSpace().newVector(INFINITY))
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqBaseJointPdfClass<V,M>::constructor() [2]"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqBaseJointPdfClass<V,M>::constructor() [2]"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }
}

template<class V, class M>
uqBaseJointPdfClass<V,M>::uqBaseJointPdfClass(
  const char*                  prefix,
  const uqVectorSetClass<V,M>& domainSet)
  :
  uqBaseScalarFunctionClass<V,M>(((std::string)(prefix)+"pd_").c_str(), domainSet),
  m_domainExpVector(domainSet.vectorSpace().newVector(       0.)),
  m_domainVarVector(domainSet.vectorSpace().newVector( INFINITY))
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqBaseJointPdfClass<V,M>::constructor() [3]"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqBaseJointPdfClass<V,M>::constructor() [3]"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }
}

template<class V, class M>
uqBaseJointPdfClass<V,M>::~uqBaseJointPdfClass()
{
}

#if 0
template <class V, class M>
const uqBaseScalarPdfClass&
uqBaseJointPdfClass<V,M>::component(unsigned int componentId) const
{
  if (componentId > m_components.size()) return m_dummyComponent;
  if (m_components[componentId] == NULL) return m_dummyComponent;
  return *(m_components[componentId]);
}
#endif

template <class V, class M>
const V&
uqBaseJointPdfClass<V,M>::domainExpVector() const
{
  return *m_domainExpVector;
}

template <class V, class M>
const V&
uqBaseJointPdfClass<V,M>::domainVarVector() const
{
  return *m_domainVarVector;
}

//*****************************************************
// Generic probability density class
//*****************************************************
template<class V, class M>
class uqGenericJointPdfClass : public uqBaseJointPdfClass<V,M> {
public:
  uqGenericJointPdfClass(const char*                           prefix,
                          const uqBaseScalarFunctionClass<V,M>& scalarFunction,
                          const V&                              domainExpVector,
                          const V&                              domainVarVector);
  uqGenericJointPdfClass(const char*                           prefix,
                          const uqBaseScalarFunctionClass<V,M>& scalarFunction);
 ~uqGenericJointPdfClass();

  double actualValue     (const V& domainVector, const V* domainDirection, V* gradVector, M* hessianMatrix, V* hessianEffect) const;
  double minus2LnValue   (const V& domainVector, const V* domainDirection, V* gradVector, M* hessianMatrix, V* hessianEffect) const;

protected:
  using uqBaseScalarFunctionClass<V,M>::m_env;
  using uqBaseScalarFunctionClass<V,M>::m_prefix;
  using uqBaseScalarFunctionClass<V,M>::m_domainSet;
  using uqBaseJointPdfClass<V,M>::m_domainExpVector;
  using uqBaseJointPdfClass<V,M>::m_domainVarVector;

  const uqBaseScalarFunctionClass<V,M>& m_scalarFunction;
};

template<class V, class M>
uqGenericJointPdfClass<V,M>::uqGenericJointPdfClass(
  const char*                           prefix,
  const uqBaseScalarFunctionClass<V,M>& scalarFunction,
  const V&                              domainExpVector,
  const V&                              domainVarVector)
  :
  uqBaseJointPdfClass<V,M>(((std::string)(prefix)+"gen").c_str(),
                            scalarFunction.domainSet(),
                            domainExpVector,
                            domainVarVector),
  m_scalarFunction(scalarFunction)
{
}

template<class V, class M>
uqGenericJointPdfClass<V,M>::uqGenericJointPdfClass(
  const char*                           prefix,
  const uqBaseScalarFunctionClass<V,M>& scalarFunction)
  :
  uqBaseJointPdfClass<V,M>(((std::string)(prefix)+"gen").c_str(),scalarFunction.domainSet()),
  m_scalarFunction(scalarFunction)
{
}

template<class V, class M>
uqGenericJointPdfClass<V,M>::~uqGenericJointPdfClass()
{
}

template<class V, class M>
double
uqGenericJointPdfClass<V,M>::actualValue(
  const V& domainVector,
  const V* domainDirection,
        V* gradVector,
        M* hessianMatrix,
        V* hessianEffect) const
{
  return m_scalarFunction.actualValue(domainVector);
}

template<class V, class M>
double
uqGenericJointPdfClass<V,M>::minus2LnValue(
  const V& domainVector,
  const V* domainDirection,
        V* gradVector,
        M* hessianMatrix,
        V* hessianEffect) const
{
  return m_scalarFunction.minus2LnValue(domainVector);
}

//*****************************************************
// Bayesian probability density class
//*****************************************************
template<class V, class M>
class uqBayesianJointPdfClass : public uqBaseJointPdfClass<V,M> {
public:
  uqBayesianJointPdfClass(const char*                           prefix,
                          const uqBaseJointPdfClass      <V,M>& priorDensity,
                          const uqBaseScalarFunctionClass<V,M>& likelihoodFunction,
                                double                          likelihoodExponent,
                          const uqVectorSetClass         <V,M>& intersectionDomain); 
 ~uqBayesianJointPdfClass();

  double actualValue     (const V& domainVector, const V* domainDirection, V* gradVector, M* hessianMatrix, V* hessianEffect) const;
  double minus2LnValue   (const V& domainVector, const V* domainDirection, V* gradVector, M* hessianMatrix, V* hessianEffect) const;

protected:
  using uqBaseScalarFunctionClass<V,M>::m_env;
  using uqBaseScalarFunctionClass<V,M>::m_prefix;
  using uqBaseScalarFunctionClass<V,M>::m_domainSet;
  using uqBaseJointPdfClass<V,M>::m_domainExpVector;
  using uqBaseJointPdfClass<V,M>::m_domainVarVector;

  const uqBaseJointPdfClass      <V,M>& m_priorDensity;
  const uqBaseScalarFunctionClass<V,M>& m_likelihoodFunction;
        double                          m_likelihoodExponent;

  mutable V  m_tmpVector1;
  mutable V  m_tmpVector2;
  mutable M* m_tmpMatrix;
};

template<class V,class M>
uqBayesianJointPdfClass<V,M>::uqBayesianJointPdfClass(
  const char*                           prefix,
  const uqBaseJointPdfClass     <V,M>&  priorDensity,
  const uqBaseScalarFunctionClass<V,M>& likelihoodFunction,
        double                          likelihoodExponent,
  const uqVectorSetClass         <V,M>& intersectionDomain)
  :
  uqBaseJointPdfClass<V,M>(((std::string)(prefix)+"bay").c_str(),intersectionDomain),
  m_priorDensity           (priorDensity),
  m_likelihoodFunction     (likelihoodFunction),
  m_likelihoodExponent     (likelihoodExponent),
  m_tmpVector1             (m_domainSet.vectorSpace().zeroVector()),
  m_tmpVector2             (m_domainSet.vectorSpace().zeroVector()),
  m_tmpMatrix              (m_domainSet.vectorSpace().newMatrix())
{
}

template<class V,class M>
uqBayesianJointPdfClass<V,M>::~uqBayesianJointPdfClass()
{
  delete m_tmpMatrix;
}

template<class V, class M>
double
uqBayesianJointPdfClass<V,M>::actualValue(
  const V& domainVector,
  const V* domainDirection,
        V* gradVector,
        M* hessianMatrix,
        V* hessianEffect) const
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqBayesianJointPdfClass<V,M>::actualValue()"
                           << ": domainVector = " << domainVector
                           << std::endl;
  }

  V* gradVLike = NULL;
  if (gradVector) gradVLike = &m_tmpVector1;

  M* hessianMLike = NULL;
  if (hessianMatrix) hessianMLike = m_tmpMatrix;

  V* hessianELike = NULL;
  if (hessianEffect) hessianELike = &m_tmpVector2;

  double value1 = m_priorDensity.actualValue      (domainVector,domainDirection,gradVector,hessianMatrix,hessianEffect);
  double value2 = m_likelihoodFunction.actualValue(domainVector,domainDirection,gradVLike ,hessianMLike ,hessianELike );

  UQ_FATAL_TEST_MACRO((gradVector || hessianMatrix || hessianEffect),
                      m_env.fullRank(),
                      "uqBayesianJointPdfClass<V,M>::actualValue()",
                      "incomplete code for gradVector, hessianMatrix and hessianEffect calculations");

  double returnValue = value1;
  if (m_likelihoodExponent == 0.) {
    // Do nothing
  }
  else if (m_likelihoodExponent == 1.) {
    returnValue *= value2;
  }
  else {
    returnValue *= pow(value2,m_likelihoodExponent);
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqBayesianJointPdfClass<V,M>::actualValue()"
                           << ": domainVector = " << domainVector
                           << ", returnValue = "  << returnValue
                           << std::endl;
  }

  return returnValue;
}

template<class V, class M>
double
uqBayesianJointPdfClass<V,M>::minus2LnValue(
  const V& domainVector,
  const V* domainDirection,
        V* gradVector,
        M* hessianMatrix,
        V* hessianEffect) const
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqBayesianJointPdfClass<V,M>::minus2LnValue()"
                           << ": domainVector = " << domainVector
                           << std::endl;
  }

  V* gradVLike = NULL;
  if (gradVector) gradVLike = &m_tmpVector1;

  M* hessianMLike = NULL;
  if (hessianMatrix) hessianMLike = m_tmpMatrix;

  V* hessianELike = NULL;
  if (hessianEffect) hessianELike = &m_tmpVector2;

  double value1 = m_priorDensity.minus2LnValue      (domainVector,domainDirection,gradVector,hessianMatrix,hessianEffect);

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "In uqBayesianJointPdfClass<V,M>::minus2LnValue()"
                           << ", domainVector = " << domainVector
                           << ": about to call likelihood()"
                           << std::endl;
  }

  double value2 = m_likelihoodFunction.minus2LnValue(domainVector,domainDirection,gradVLike, hessianMLike, hessianELike );

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "In uqBayesianJointPdfClass<V,M>::minus2LnValue()"
                           << ", domainVector = " << domainVector
                           << ": value1 = "       << value1
                           << ", value2 = "       << value2
                           << std::endl;
    if (gradVector) {
      *m_env.subDisplayFile() << "In uqBayesianJointPdfClass<V,M>::minus2LnValue()"
                             << ", domainVector = " << domainVector
                             << ": gradVector = "   << *gradVector
                             << ", gradVLike = "    << *gradVLike
                             << std::endl;
    }
    if (hessianMatrix) {
      *m_env.subDisplayFile() << "In uqBayesianJointPdfClass<V,M>::minus2LnValue()"
                             << ", domainVector = "  << domainVector
                             << ": hessianMatrix = " << *hessianMatrix
                             << ", hessianMLike = "  << *hessianMLike
                             << std::endl;
    }
    if (hessianEffect) {
      *m_env.subDisplayFile() << "In uqBayesianJointPdfClass<V,M>::minus2LnValue()"
                             << ", domainVector = "  << domainVector
                             << ": hessianEffect = " << *hessianEffect
                             << ", hessianELike = "  << *hessianELike
                             << std::endl;
    }
  }

  if (gradVector   ) *gradVector    += *gradVLike;
  if (hessianMatrix) *hessianMatrix += *hessianMLike;
  if (hessianEffect) *hessianEffect += *hessianELike;

  double returnValue = value1;
  if (m_likelihoodExponent == 0.) {
    // Do nothing
  }
  else if (m_likelihoodExponent == 1.) {
    returnValue += value2;
  }
  else {
    returnValue += value2*m_likelihoodExponent;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqBayesianJointPdfClass<V,M>::minus2LnValue()"
                           << ": domainVector = " << domainVector
                           << ", returnValue = "  << returnValue
                           << std::endl;
  }

  return returnValue;
}

//*****************************************************
// Gaussian probability density class
//*****************************************************
template<class V, class M>
class uqGaussianJointPdfClass : public uqBaseJointPdfClass<V,M> {
public:
  uqGaussianJointPdfClass(const char*                  prefix,
                           const uqVectorSetClass<V,M>& domainSet,
                           const V&                     domainExpVector,
                           const V&                     domainVarVector);
  uqGaussianJointPdfClass(const char*                  prefix,
                           const uqVectorSetClass<V,M>& domainSet,
                           const V&                     domainExpVector,
                           const M&                     covMatrix);
 ~uqGaussianJointPdfClass();

  double   actualValue    (const V& domainVector, const V* domainDirection, V* gradVector, M* hessianMatrix, V* hessianEffect) const;
  double   minus2LnValue  (const V& domainVector, const V* domainDirection, V* gradVector, M* hessianMatrix, V* hessianEffect) const;
  void     updateExpVector(const V& newExpVector);
  void     updateCovMatrix(const M& newCovMatrix);
  const M& covMatrix      () const;

protected:
  using uqBaseScalarFunctionClass<V,M>::m_env;
  using uqBaseScalarFunctionClass<V,M>::m_prefix;
  using uqBaseScalarFunctionClass<V,M>::m_domainSet;
  using uqBaseJointPdfClass<V,M>::m_domainExpVector;
  using uqBaseJointPdfClass<V,M>::m_domainVarVector;

  bool     m_diagonalCovMatrix;
  const M* m_covMatrix;
};

template<class V,class M>
uqGaussianJointPdfClass<V,M>::uqGaussianJointPdfClass(
  const char*                  prefix,
  const uqVectorSetClass<V,M>& domainSet,
  const V&                     domainExpVector,
  const V&                     domainVarVector)
  :
  uqBaseJointPdfClass<V,M>(((std::string)(prefix)+"gau").c_str(),domainSet,domainExpVector,domainVarVector),
  m_diagonalCovMatrix(true),
  m_covMatrix        (m_domainSet.vectorSpace().newDiagMatrix(domainVarVector))
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqGaussianJointPdfClass<V,M>::constructor() [1]"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "In uqGaussianJointPdfClass<V,M>::constructor()"
                         //<< ", prefix = "     << m_prefix
                           << ": meanVector = " << this->domainExpVector()
	                   << ", Variances = "  << this->domainVarVector()
                           << std::endl;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqGaussianJointPdfClass<V,M>::constructor() [1]"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }
}

template<class V,class M>
uqGaussianJointPdfClass<V,M>::uqGaussianJointPdfClass(
  const char*                  prefix,
  const uqVectorSetClass<V,M>& domainSet,
  const V&                     domainExpVector,
  const M&                     covMatrix)
  :
  uqBaseJointPdfClass<V,M>(((std::string)(prefix)+"gau").c_str(),domainSet,domainExpVector),
  m_diagonalCovMatrix      (false),
  m_covMatrix              (new M(covMatrix))
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqGaussianJointPdfClass<V,M>::constructor() [2]"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "In uqGaussianJointPdfClass<V,M>::constructor()"
                         //<< ", prefix = "            << m_prefix
                           << ": meanVector = "        << this->domainExpVector()
	                   << ", Covariance Matrix = " << covMatrix
                           << std::endl;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqGaussianJointPdfClass<V,M>::constructor() [2]"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }
}

template<class V,class M>
uqGaussianJointPdfClass<V,M>::~uqGaussianJointPdfClass()
{
  delete m_covMatrix;
}

template<class V, class M>
double
uqGaussianJointPdfClass<V,M>::actualValue(
  const V& domainVector,
  const V* domainDirection,
        V* gradVector,
        M* hessianMatrix,
        V* hessianEffect) const
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqGaussianJointPdfClass<V,M>::actualValue()"
                           << ", meanVector = "   << *m_domainExpVector
	                   << ", covMatrix = "    << *m_covMatrix
                           << ": domainVector = " << domainVector
                           << std::endl;
  }

  UQ_FATAL_TEST_MACRO((gradVector || hessianMatrix || hessianEffect),
                      m_env.fullRank(),
                      "uqGaussianJointPdfClass<V,M>::actualValue()",
                      "incomplete code for gradVector, hessianMatrix and hessianEffect calculations");

  double returnValue = std::exp(-0.5*this->minus2LnValue(domainVector,domainDirection,gradVector,hessianMatrix,hessianEffect));

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqGaussianJointPdfClass<V,M>::actualValue()"
                           << ", meanVector = "   << *m_domainExpVector
	                   << ", covMatrix = "    << *m_covMatrix
                           << ": domainVector = " << domainVector
                           << ", returnValue = "  << returnValue
                           << std::endl;
  }

  return returnValue;
}

template<class V, class M>
double
uqGaussianJointPdfClass<V,M>::minus2LnValue(
  const V& domainVector,
  const V* domainDirection,
        V* gradVector,
        M* hessianMatrix,
        V* hessianEffect) const
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqGaussianJointPdfClass<V,M>::minus2LnValue()"
                           << ", meanVector = "   << *m_domainExpVector
	                   << ", covMatrix = "    << *m_covMatrix
                           << ": domainVector = " << domainVector
                           << std::endl;
  }

  double returnValue = 0.;

  if (m_diagonalCovMatrix) {
    V diffVec(domainVector - this->domainExpVector());
    returnValue = ((diffVec*diffVec)/this->domainVarVector()).sumOfComponents();
  }
  else {
    V diffVec(domainVector - this->domainExpVector());
    V tmpVec = this->m_covMatrix->invertMultiply(diffVec);
    returnValue = (diffVec*tmpVec).sumOfComponents();
  }

  UQ_FATAL_TEST_MACRO((gradVector || hessianMatrix || hessianEffect),
                      m_env.fullRank(),
                      "uqGaussianJointPdfClass<V,M>::minus2LnValue()",
                      "incomplete code for gradVector, hessianMatrix and hessianEffect calculations");

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqGaussianJointPdfClass<V,M>::minus2LnValue()"
                           << ", meanVector = "   << *m_domainExpVector
	                   << ", covMatrix = "    << *m_covMatrix
                           << ": domainVector = " << domainVector
                           << ", returnValue = "  << returnValue
                           << std::endl;
  }

  return returnValue;
}

template<class V, class M>
void
uqGaussianJointPdfClass<V,M>::updateExpVector(const V& newExpVector)
{
  // delete old expected values (alloced at construction or last call to this function)
  delete m_domainExpVector;
  m_domainExpVector = new V(newExpVector);
  return;
}

template<class V, class M>
void
uqGaussianJointPdfClass<V,M>::updateCovMatrix(const M& newCovMatrix)
{
  // delete old expected values (alloced at construction or last call to this function)
  delete m_covMatrix;
  m_covMatrix = new M(newCovMatrix);
  return;
}

template<class V, class M>
const M&
uqGaussianJointPdfClass<V,M>::covMatrix() const
{
  return *m_covMatrix;
}

//*****************************************************
// Uniform probability density class
//*****************************************************
template<class V, class M>
class uqUniformJointPdfClass : public uqBaseJointPdfClass<V,M> {
public:
  uqUniformJointPdfClass(const char*                  prefix,
                          const uqVectorSetClass<V,M>& domainSet);
 ~uqUniformJointPdfClass();

  double actualValue     (const V& domainVector, const V* domainDirection, V* gradVector, M* hessianMatrix, V* hessianEffect) const;
  double minus2LnValue   (const V& domainVector, const V* domainDirection, V* gradVector, M* hessianMatrix, V* hessianEffect) const;

protected:
  using uqBaseScalarFunctionClass<V,M>::m_env;
  using uqBaseScalarFunctionClass<V,M>::m_prefix;
  using uqBaseScalarFunctionClass<V,M>::m_domainSet;
  using uqBaseJointPdfClass<V,M>::m_domainExpVector;
  using uqBaseJointPdfClass<V,M>::m_domainVarVector;
};

template<class V,class M>
uqUniformJointPdfClass<V,M>::uqUniformJointPdfClass(
  const char*                  prefix,
  const uqVectorSetClass<V,M>& domainSet)
  :
  uqBaseJointPdfClass<V,M>(((std::string)(prefix)+"uni").c_str(),
                            domainSet)
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqUniformJointPdfClass<V,M>::constructor()"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqUniformJointPdfClass<V,M>::constructor()"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }
}

template<class V,class M>
uqUniformJointPdfClass<V,M>::~uqUniformJointPdfClass()
{
}

template<class V, class M>
double
uqUniformJointPdfClass<V,M>::actualValue(
  const V& domainVector,
  const V* domainDirection,
        V* gradVector,
        M* hessianMatrix,
        V* hessianEffect) const
{
  if (gradVector   ) *gradVector     = m_domainSet.vectorSpace().zeroVector();
  if (hessianMatrix) *hessianMatrix *= 0.;
  if (hessianEffect) *hessianEffect  = m_domainSet.vectorSpace().zeroVector();

  return 1.;
}

template<class V, class M>
double
uqUniformJointPdfClass<V,M>::minus2LnValue(
  const V& domainVector,
  const V* domainDirection,
        V* gradVector,
        M* hessianMatrix,
        V* hessianEffect) const
{
  if (gradVector   ) *gradVector     = m_domainSet.vectorSpace().zeroVector();
  if (hessianMatrix) *hessianMatrix *= 0.;
  if (hessianEffect) *hessianEffect  = m_domainSet.vectorSpace().zeroVector();

  return 0.;
}

//*****************************************************
// Gaussian probability density class
//*****************************************************
template<class V, class M>
class uqPoweredJointPdfClass : public uqBaseJointPdfClass<V,M> {
public:
  uqPoweredJointPdfClass(const char*                     prefix,
                         const uqBaseJointPdfClass<V,M>& srcDensity,
                               double                    exponent);
 ~uqPoweredJointPdfClass();

  double   actualValue  (const V& domainVector, const V* domainDirection, V* gradVector, M* hessianMatrix, V* hessianEffect) const;
  double   minus2LnValue(const V& domainVector, const V* domainDirection, V* gradVector, M* hessianMatrix, V* hessianEffect) const;

protected:
  using uqBaseScalarFunctionClass<V,M>::m_env;
  using uqBaseScalarFunctionClass<V,M>::m_prefix;
  using uqBaseScalarFunctionClass<V,M>::m_domainSet;

  const uqBaseJointPdfClass<V,M>& m_srcDensity;
        double                    m_exponent;
};

template<class V,class M>
uqPoweredJointPdfClass<V,M>::uqPoweredJointPdfClass(
  const char*                     prefix,
  const uqBaseJointPdfClass<V,M>& srcDensity,
        double                    exponent)
  :
  uqBaseJointPdfClass<V,M>(((std::string)(prefix)+"pow").c_str(),srcDensity.domainSet()),
  m_srcDensity            (srcDensity),
  m_exponent              (exponent)
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqPoweredJointPdfClass<V,M>::constructor()"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "In uqPoweredJointPdfClass<V,M>::constructor()"
                         //<< ", prefix = "     << m_prefix
                           << ": meanVector = " << this->domainExpVector()
	                   << ", Variances = "  << this->domainVarVector()
                           << std::endl;
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqPoweredJointPdfClass<V,M>::constructor()"
                           << ": prefix = " << m_prefix
                           << std::endl;
  }
}

template<class V,class M>
uqPoweredJointPdfClass<V,M>::~uqPoweredJointPdfClass()
{
}

template<class V, class M>
double
uqPoweredJointPdfClass<V,M>::actualValue(
  const V& domainVector,
  const V* domainDirection,
        V* gradVector,
        M* hessianMatrix,
        V* hessianEffect) const
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqPoweredJointPdfClass<V,M>::actualValue()"
                           << ": domainVector = " << domainVector
                           << std::endl;
  }

  double value = m_srcDensity.actualValue(domainVector,domainDirection,gradVector,hessianMatrix,hessianEffect);

  UQ_FATAL_TEST_MACRO((domainDirection || gradVector || hessianMatrix || hessianEffect),
                      m_env.fullRank(),
                      "uqPoweredJointPdfClass<V,M>::actualValue()",
                      "incomplete code for domainDirection, gradVector, hessianMatrix and hessianEffect calculations");

  double returnValue = pow(value,m_exponent);

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqPoweredJointPdfClass<V,M>::actualValue()"
                           << ": domainVector = " << domainVector
                           << ", returnValue = "  << returnValue
                           << std::endl;
  }

  return returnValue;
}

template<class V, class M>
double
uqPoweredJointPdfClass<V,M>::minus2LnValue(
  const V& domainVector,
  const V* domainDirection,
        V* gradVector,
        M* hessianMatrix,
        V* hessianEffect) const
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqPoweredJointPdfClass<V,M>::minus2LnValue()"
                            << ": domainVector = " << domainVector
                            << std::endl;
  }

  double value = m_srcDensity.minus2LnValue(domainVector,domainDirection,gradVector,hessianMatrix,hessianEffect);

  UQ_FATAL_TEST_MACRO((domainDirection || gradVector || hessianMatrix || hessianEffect),
                      m_env.fullRank(),
                      "uqPoweredJointPdfClass<V,M>::minus2LnValue()",
                      "incomplete code for domainDirection, gradVector, hessianMatrix and hessianEffect calculations");

  double returnValue = m_exponent*value;

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqPoweredJointPdfClass<V,M>::minus2LnValue()"
                            << ": domainVector = " << domainVector
                            << ", returnValue = "  << returnValue
                            << std::endl;
  }

  return returnValue;
}
#endif // __UQ_JOINT_PROB_DENSITY_H__
