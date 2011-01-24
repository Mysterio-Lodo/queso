//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
// 
// QUESO - a library to support the Quantification of Uncertainty
// for Estimation, Simulation and Optimization
//
// Copyright (C) 2008,2009,2010 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor, 
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-
// 
// $Id$
//
//--------------------------------------------------------------------------

#ifndef __UQ_SEQUENCE_OF_VECTORS_H__
#define __UQ_SEQUENCE_OF_VECTORS_H__

#include <uqVectorSequence.h>
#define UQ_SEQ_VEC_USES_SCALAR_SEQ_CODE
#undef UQ_SEQ_VEC_USES_OPERATOR

template <class V, class M>
class uqSequenceOfVectorsClass : public uqBaseVectorSequenceClass<V,M>
{
public:
  typedef typename std::vector<const V*>::const_iterator seqVectorPositionConstIteratorTypedef;
  typedef typename std::vector<const V*>::iterator       seqVectorPositionIteratorTypedef;
  uqSequenceOfVectorsClass(const uqVectorSpaceClass<V,M>& vectorSpace,
                           unsigned int                   subSequenceSize,
                           const std::string&             name);
 ~uqSequenceOfVectorsClass();

  uqSequenceOfVectorsClass<V,M>& operator= (const uqSequenceOfVectorsClass<V,M>& rhs);

        unsigned int subSequenceSize            () const;
        void         resizeSequence             (unsigned int newSubSequenceSize);
        void         resetValues                (unsigned int initialPos, unsigned int numPos);
        void         erasePositions             (unsigned int initialPos, unsigned int numPos);
#ifdef UQ_SEQ_VEC_USES_OPERATOR
	const V*     operator[]                 (unsigned int posId) const;
	const V*&    operator[]                 (unsigned int posId);
#endif
        void         getPositionValues          (unsigned int posId,       V& vec) const;
        void         setPositionValues          (unsigned int posId, const V& vec);
        void         setGaussian                (const gsl_rng* rng, const V& meanVec, const V& stdDevVec);
        void         setUniform                 (const gsl_rng* rng, const V& aVec,    const V& bVec     );
#ifdef UQ_ALSO_COMPUTE_MDFS_WITHOUT_KDE
        void         subUniformlySampledMdf     (const V&                             numEvaluationPointsVec,
                                                 uqArrayOfOneDGridsClass <V,M>&       mdfGrids,
                                                 uqArrayOfOneDTablesClass<V,M>&       mdfValues) const;
#endif
        void         subUniformlySampledCdf     (const V&                             numEvaluationPointsVec,
                                                 uqArrayOfOneDGridsClass <V,M>&       cdfGrids,
                                                 uqArrayOfOneDTablesClass<V,M>&       cdfValues) const;
        void         unifiedUniformlySampledCdf (const V&                             numEvaluationPointsVec,
                                                 uqArrayOfOneDGridsClass <V,M>&       unifiedCdfGrids,
                                                 uqArrayOfOneDTablesClass<V,M>&       unifiedCdfValues) const;

        void         subMean                    (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 V&                                   meanVec) const;
        void         unifiedMean                (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 V&                                   unifiedMeanVec) const;
        void         subMeanCltStd              (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 const V&                             meanVec,
                                                 V&                                   samVec) const;
        void         unifiedMeanCltStd          (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 const V&                             unifiedMeanVec,
                                                 V&                                   unifiedSamVec) const;
        void         subSampleVariance          (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 const V&                             meanVec,
                                                 V&                                   samVec) const;
        void         unifiedSampleVariance      (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 const V&                             unifiedMeanVec,
                                                 V&                                   unifiedSamVec) const;
        void         subPopulationVariance      (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 const V&                             meanVec,
                                                 V&                                   popVec) const;
        void         unifiedPopulationVariance  (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 const V&                             unifiedMeanVec,
                                                 V&                                   unifiedPopVec) const;
        void         autoCovariance             (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 const V&                             meanVec,
                                                 unsigned int                         lag,
                                                 V&                                   covVec) const;
 
        void         autoCorrViaDef             (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 unsigned int                         lag,
                                                 V&                                   corrVec) const;
        void         autoCorrViaFft             (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 const std::vector<unsigned int>&     lags,
                                                 std::vector<V*>&                     corrVecs) const;
        void         autoCorrViaFft             (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 unsigned int                         numSum,
                                                 V&                                   autoCorrsSumVec) const;
        void         bmm                        (unsigned int                         initialPos,
                                                 unsigned int                         batchLength,
                                                 V&                                   bmmVec) const;
        void         fftForward                 (unsigned int                         initialPos,
                                                 unsigned int                         fftSize,
                                                 unsigned int                         paramId,
                                                 std::vector<std::complex<double> >&  fftResult) const;
      //void         fftInverse                 (unsigned int fftSize);
        void         psd                        (unsigned int                         initialPos,
                                                 unsigned int                         numBlocks,
                                                 double                               hopSizeRatio,
                                                 unsigned int                         paramId,
                                                 std::vector<double>&                 psdResult) const;
        void         psdAtZero                  (unsigned int                         initialPos,
                                                 unsigned int                         numBlocks,
                                                 double                               hopSizeRatio,
                                                 V&                                   psdVec) const;
        void         geweke                     (unsigned int                         initialPos,
                                                 double                               ratioNa,
                                                 double                               ratioNb,
                                                 V&                                   gewVec) const;
        void         meanStacc                  (unsigned int                         initialPos,
                                                 V&                                   meanStaccVec) const;
        void         subMinMax                  (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 V&                                   minVec,
                                                 V&                                   maxVec) const;
        void         unifiedMinMax              (unsigned int                         initialPos,
                                                 unsigned int                         numPos,
                                                 V&                                   unifiedMinVec,
                                                 V&                                   unifiedMaxVec) const;
        void         subHistogram               (unsigned int                         initialPos,
                                                 const V&                             minVec,
                                                 const V&                             maxVec,
                                                 std::vector<V*>&                     centersForAllBins,
                                                 std::vector<V*>&                     quanttsForAllBins) const;
        void         unifiedHistogram           (unsigned int                         initialPos,
                                                 const V&                             unifiedMinVec,
                                                 const V&                             unifiedMaxVec,
                                                 std::vector<V*>&                     unifiedCentersForAllBins,
                                                 std::vector<V*>&                     unifiedQuanttsForAllBins) const;
        void         subCdfStacc                (unsigned int                         initialPos,
                                                 std::vector<V*>&                     cdfStaccVecs,
                                                 std::vector<V*>&                     cdfStaccVecsUp,
                                                 std::vector<V*>&                     cdfStaccVecsLow,												 
                                                 std::vector<V*>&                     sortedDataVecs) const;
        void         subCdfStacc                (unsigned int                         initialPos,
                                                 const std::vector<V*>&               evalPositionsVecs,
                                                 std::vector<V*>&                     cdfStaccVecs) const;
        void         subInterQuantileRange      (unsigned int                         initialPos,
                                                 V&                                   iqrVec) const;
        void         unifiedInterQuantileRange  (unsigned int                         initialPos,
                                                 V&                                   unifiedIqrVec) const;
        void         subScalesForKde            (unsigned int                         initialPos,
                                                 const V&                             iqrVec,
                                                 unsigned int                         kdeDimension,
                                                 V&                                   scaleVec) const;
        void         unifiedScalesForKde        (unsigned int                         initialPos,
                                                 const V&                             unifiedIqrVec,
                                                 unsigned int                         kdeDimension,
                                                 V&                                   unifiedScaleVec) const;
        void         subGaussian1dKde           (unsigned int                         initialPos,
                                                 const V&                             scaleVec,
                                                 const std::vector<V*>&               evalParamVecs,
                                                 std::vector<V*>&                     densityVecs) const;
        void         unifiedGaussian1dKde       (unsigned int                         initialPos,
                                                 const V&                             unifiedScaleVec,
                                                 const std::vector<V*>&               unifiedEvalParamVecs,
                                                 std::vector<V*>&                     unifiedDensityVecs) const;
        void         subWriteContents           (const std::string&                   fileName,
                                                 const std::string&                   fileType,
                                                 const std::set<unsigned int>&        allowedSubEnvIds) const;
        void         subWriteContents           (uqFilePtrSetStruct&                  filePtrSet,
                                                 const std::string&                   fileType) const;
        void         subWriteContents           (std::ofstream&                       ofs,
                                                 const std::string&                   fileType) const;
        void         unifiedWriteContents       (const std::string&                   fileName,
                                                 const std::string&                   fileType) const;
        void         unifiedReadContents        (const std::string&                   fileName,
                                                 const std::string&                   fileType,
                                                 const unsigned int                   subSequenceSize);
        void         select                     (const std::vector<unsigned int>&     idsOfUniquePositions);
        void         filter                     (unsigned int                         initialPos,
                                                 unsigned int                         spacing);

        double       estimateConvBrooksGelman   (unsigned int                         initialPos,
                                                 unsigned int                         numPos) const;

        void         append                     (const uqSequenceOfVectorsClass<V,M>& src,
                                                 unsigned int                         initialPos,
                                                 unsigned int                         numPos);

        void         extractScalarSeq           (unsigned int                         initialPos,
                                                 unsigned int                         spacing,
                                                 unsigned int                         numPos,
                                                 unsigned int                         paramId,
                                                 uqScalarSequenceClass<double>&       scalarSeq) const;
private:
        void         subMeanMonitorAlloc        (unsigned int numberOfMonitorPositions);
        void         subMeanInter0MonitorAlloc  (unsigned int numberOfMonitorPositions);
        void         unifiedMeanMonitorAlloc    (unsigned int numberOfMonitorPositions);

        void         subMeanMonitorRun          (unsigned int monitorPosition,
                                                 V&           subMeanVec,
                                                 V&           subMeanCltStd);
        void         subMeanInter0MonitorRun    (unsigned int currentPosition,
                                                 V&           subMeanInter0Mean,
                                                 V&           subMeanInter0Clt95,
                                                 V&           subMeanInter0Empirical90,
                                                 V&           subMeanInter0Min,
                                                 V&           subMeanInter0Max);
        void         unifiedMeanMonitorRun      (unsigned int currentPosition,
                                                 V&           unifiedMeanVec,
                                                 V&           unifiedMeanCltStd);

        void         subMeanMonitorStore        (unsigned int i,
                                                 unsigned int monitorPosition,
                                                 const V&     subMeanVec,
                                                 const V&     subMeanCltStd);
        void         subMeanInter0MonitorStore  (unsigned int i,
                                                 unsigned int monitorPosition,
                                                 const V&     subMeanInter0Mean,
                                                 const V&     subMeanInter0Clt95,
                                                 const V&     subMeanInter0Empirical90,
                                                 const V&     subMeanInter0Min,
                                                 const V&     subMeanInter0Max);
        void         unifiedMeanMonitorStore    (unsigned int i,
                                                 unsigned int monitorPosition,
                                                 V&           unifiedMeanVec,
                                                 V&           unifiedMeanCltStd);

        void         subMeanMonitorFree         ();
        void         subMeanInter0MonitorFree   ();
        void         unifiedMeanMonitorFree     ();

        void         subMeanMonitorWrite        (std::ofstream& ofs);
        void         subMeanInter0MonitorWrite  (std::ofstream& ofs);
        void         unifiedMeanMonitorWrite    (std::ofstream& ofs);

        void         copy                       (const uqSequenceOfVectorsClass<V,M>& src);
        void         extractRawData             (unsigned int                         initialPos,
                                                 unsigned int                         spacing,
                                                 unsigned int                         numPos,
                                                 unsigned int                         paramId,
                                                 std::vector<double>&                 rawData) const;

  using uqBaseVectorSequenceClass<V,M>::m_env;
  using uqBaseVectorSequenceClass<V,M>::m_vectorSpace;
  using uqBaseVectorSequenceClass<V,M>::m_name;
  using uqBaseVectorSequenceClass<V,M>::m_fftObj;

  std::vector<const V*>          m_seq;
  uqScalarSequenceClass<double>* m_subMeanMonitorPosSeq;
  uqSequenceOfVectorsClass<V,M>* m_subMeanVecSeq;
  uqSequenceOfVectorsClass<V,M>* m_subMeanCltStdSeq;

  uqScalarSequenceClass<double>* m_subMeanInter0MonitorPosSeq;
  uqSequenceOfVectorsClass<V,M>* m_subMeanInter0Mean;
  uqSequenceOfVectorsClass<V,M>* m_subMeanInter0Clt95;
  uqSequenceOfVectorsClass<V,M>* m_subMeanInter0Empirical90;
  uqSequenceOfVectorsClass<V,M>* m_subMeanInter0Min;
  uqSequenceOfVectorsClass<V,M>* m_subMeanInter0Max;

  uqScalarSequenceClass<double>* m_unifiedMeanMonitorPosSeq;
  uqSequenceOfVectorsClass<V,M>* m_unifiedMeanVecSeq;
  uqSequenceOfVectorsClass<V,M>* m_unifiedMeanCltStdSeq;
};

template <class V, class M>
uqSequenceOfVectorsClass<V,M>::uqSequenceOfVectorsClass(
  const uqVectorSpaceClass<V,M>& vectorSpace,
  unsigned int                   subSequenceSize,
  const std::string&             name)
  :
  uqBaseVectorSequenceClass<V,M>(vectorSpace,subSequenceSize,name),
  m_seq                         (subSequenceSize,NULL),
  m_subMeanMonitorPosSeq        (NULL),
  m_subMeanVecSeq               (NULL),
  m_subMeanCltStdSeq            (NULL),
  m_subMeanInter0MonitorPosSeq  (NULL),
  m_subMeanInter0Mean           (NULL),
  m_subMeanInter0Clt95          (NULL),
  m_subMeanInter0Empirical90    (NULL),
  m_subMeanInter0Min            (NULL),
  m_subMeanInter0Max            (NULL),
  m_unifiedMeanMonitorPosSeq    (NULL),
  m_unifiedMeanVecSeq           (NULL),
  m_unifiedMeanCltStdSeq        (NULL)
{
  //if (m_env.subDisplayFile()) {
  //  *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::constructor()"
  //                          << std::endl;
  //}

  //if (m_env.subDisplayFile()) {
  //  *m_env.subDisplayFile() << "Leaving uqSequenceOfVectorsClass<V,M>::constructor()"
  //                          << std::endl;
  //}
}

template <class V, class M>
uqSequenceOfVectorsClass<V,M>::~uqSequenceOfVectorsClass()
{
  if (m_subMeanMonitorPosSeq) delete m_subMeanMonitorPosSeq;
  if (m_subMeanVecSeq       ) delete m_subMeanVecSeq;
  if (m_subMeanCltStdSeq    ) delete m_subMeanCltStdSeq;

  if (m_subMeanInter0MonitorPosSeq) delete m_subMeanInter0MonitorPosSeq;
  if (m_subMeanInter0Mean         ) delete m_subMeanInter0Mean;
  if (m_subMeanInter0Clt95        ) delete m_subMeanInter0Clt95;
  if (m_subMeanInter0Empirical90  ) delete m_subMeanInter0Empirical90;
  if (m_subMeanInter0Min          ) delete m_subMeanInter0Min;
  if (m_subMeanInter0Max          ) delete m_subMeanInter0Max;

  if (m_unifiedMeanMonitorPosSeq) delete m_unifiedMeanMonitorPosSeq;
  if (m_unifiedMeanVecSeq       ) delete m_unifiedMeanVecSeq;
  if (m_unifiedMeanCltStdSeq    ) delete m_unifiedMeanCltStdSeq;

  for (unsigned int i = 0; i < (unsigned int) m_seq.size(); ++i) {
    if (m_seq[i]) delete m_seq[i];
  }
}

template <class V, class M>
uqSequenceOfVectorsClass<V,M>&
uqSequenceOfVectorsClass<V,M>::operator= (const uqSequenceOfVectorsClass<V,M>& rhs)
{
  this->copy(rhs);
  return *this;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMeanMonitorAlloc(unsigned int numberOfMonitorPositions)
{
  m_subMeanMonitorPosSeq = new uqScalarSequenceClass<double>(m_env,        numberOfMonitorPositions,(m_name+"_subMeanMonitorPosSeq").c_str());
  m_subMeanVecSeq        = new uqSequenceOfVectorsClass<V,M>(m_vectorSpace,numberOfMonitorPositions,(m_name+"_subMeanVecSeq").c_str()       );
  m_subMeanCltStdSeq     = new uqSequenceOfVectorsClass<V,M>(m_vectorSpace,numberOfMonitorPositions,(m_name+"_subMeanCltStdSeq").c_str()    );

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMeanInter0MonitorAlloc(unsigned int numberOfMonitorPositions)
{
  m_subMeanInter0MonitorPosSeq = new uqScalarSequenceClass<double>(m_env,        numberOfMonitorPositions,(m_name+"_subMeanInter0MonitorPosSeq").c_str() );
  m_subMeanInter0Mean          = new uqSequenceOfVectorsClass<V,M>(m_vectorSpace,numberOfMonitorPositions,(m_name+"_subMeanInter0MeanSeq").c_str()       );
  m_subMeanInter0Clt95         = new uqSequenceOfVectorsClass<V,M>(m_vectorSpace,numberOfMonitorPositions,(m_name+"_subMeanInter0Clt95Seq").c_str()      );
  m_subMeanInter0Empirical90   = new uqSequenceOfVectorsClass<V,M>(m_vectorSpace,numberOfMonitorPositions,(m_name+"_subMeanInter0Empirical90Seq").c_str());
  m_subMeanInter0Min           = new uqSequenceOfVectorsClass<V,M>(m_vectorSpace,numberOfMonitorPositions,(m_name+"_subMeanInter0MinSeq").c_str()        );
  m_subMeanInter0Max           = new uqSequenceOfVectorsClass<V,M>(m_vectorSpace,numberOfMonitorPositions,(m_name+"_subMeanInter0MaxSeq").c_str()        );

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedMeanMonitorAlloc(unsigned int numberOfMonitorPositions)
{
  m_unifiedMeanMonitorPosSeq = new uqScalarSequenceClass<double>(m_env,        numberOfMonitorPositions,(m_name+"_unifiedMeanMonitorPosSeq").c_str());
  m_unifiedMeanVecSeq        = new uqSequenceOfVectorsClass<V,M>(m_vectorSpace,numberOfMonitorPositions,(m_name+"_unifiedMeanVecSeq").c_str()       );
  m_unifiedMeanCltStdSeq     = new uqSequenceOfVectorsClass<V,M>(m_vectorSpace,numberOfMonitorPositions,(m_name+"_unifiedMeanCltStdSeq").c_str()    );

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMeanMonitorRun(unsigned int monitorPosition,
                                                 V&           subMeanVec,
                                                 V&           subMeanCltStd)
{
  this->subMean(0,
                monitorPosition,
                subMeanVec);

  this->subMeanCltStd(0,
                      monitorPosition,
                      subMeanVec,
                      subMeanCltStd);

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMeanInter0MonitorRun(unsigned int monitorPosition,
                                                       V&           subMeanInter0Mean,
                                                       V&           subMeanInter0Clt95,
                                                       V&           subMeanInter0Empirical90,
                                                       V&           subMeanInter0Min,
                                                       V&           subMeanInter0Max)
{
  V subMeanVec(m_vectorSpace.zeroVector());
  this->subMean(0,
                monitorPosition,
                subMeanVec);

  subMeanVec.mpiAllReduce(MPI_SUM,m_env.inter0Comm(),subMeanInter0Mean);
  subMeanInter0Mean /= ((double) m_env.inter0Comm().NumProc());

  V subMeanInter0CltVariance = subMeanVec-subMeanInter0Mean;
  subMeanInter0CltVariance *= subMeanInter0CltVariance;
  subMeanInter0CltVariance.mpiAllReduce(MPI_SUM,m_env.inter0Comm(),subMeanInter0Clt95);
  subMeanInter0Clt95 /= ((double) (m_env.inter0Comm().NumProc()-1));
  subMeanInter0Clt95 /= ((double) (m_env.inter0Comm().NumProc()-1));
  subMeanInter0Clt95.cwSqrt();
  subMeanInter0Clt95 *= 3.;

  V subMeanInter0Quantile5(m_vectorSpace.zeroVector());
  subMeanVec.mpiAllQuantile(.05,m_env.inter0Comm(),subMeanInter0Quantile5);
  V subMeanInter0Quantile95(m_vectorSpace.zeroVector());
  subMeanVec.mpiAllQuantile(.95,m_env.inter0Comm(),subMeanInter0Quantile95);
  subMeanInter0Empirical90 = subMeanInter0Quantile95 - subMeanInter0Quantile5;

  subMeanVec.mpiAllReduce(MPI_MIN,m_env.inter0Comm(),subMeanInter0Min);

  subMeanVec.mpiAllReduce(MPI_MAX,m_env.inter0Comm(),subMeanInter0Max);

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedMeanMonitorRun(unsigned int monitorPosition,
                                                     V&           unifiedMeanVec,
                                                     V&           unifiedMeanCltStd)
{
  this->unifiedMean(0,
                    monitorPosition,
                    unifiedMeanVec);

  this->unifiedMeanCltStd(0,
                          monitorPosition,
                          unifiedMeanVec,
                          unifiedMeanCltStd);
  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMeanMonitorStore(unsigned int i,
                                                   unsigned int monitorPosition,
                                                   const V&     subMeanVec,
                                                   const V&     subMeanCltStd)
{
  (*m_subMeanMonitorPosSeq)[i] = monitorPosition;
  m_subMeanVecSeq->setPositionValues(i,subMeanVec);
  m_subMeanCltStdSeq->setPositionValues(i,subMeanCltStd);

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMeanInter0MonitorStore(unsigned int i,
                                                         unsigned int monitorPosition,
                                                         const V&     subMeanInter0Mean,
                                                         const V&     subMeanInter0Clt95,
                                                         const V&     subMeanInter0Empirical90,
                                                         const V&     subMeanInter0Min,
                                                         const V&     subMeanInter0Max)
{
  (*m_subMeanInter0MonitorPosSeq)[i] = monitorPosition;
  m_subMeanInter0Mean->setPositionValues(i,subMeanInter0Mean);
  m_subMeanInter0Clt95->setPositionValues(i,subMeanInter0Clt95);
  m_subMeanInter0Empirical90->setPositionValues(i,subMeanInter0Empirical90);
  m_subMeanInter0Min->setPositionValues(i,subMeanInter0Min);
  m_subMeanInter0Max->setPositionValues(i,subMeanInter0Max);

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedMeanMonitorStore(unsigned int i,
                                                       unsigned int monitorPosition,
                                                       V&           unifiedMeanVec,
                                                       V&           unifiedMeanCltStd)
{
  (*m_unifiedMeanMonitorPosSeq)[i] = monitorPosition;
  m_unifiedMeanVecSeq->setPositionValues(i,unifiedMeanVec);
  m_unifiedMeanCltStdSeq->setPositionValues(i,unifiedMeanCltStd);

  return;
}


template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMeanMonitorWrite(std::ofstream& ofs)
{
  m_subMeanMonitorPosSeq->subWriteContents(ofs,UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT); // Yes, always ".m"
  m_subMeanVecSeq->subWriteContents(ofs,UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT); // Yes, always ".m"
  m_subMeanCltStdSeq->subWriteContents(ofs,UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT); // Yes, always ".m"

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMeanInter0MonitorWrite(std::ofstream& ofs)
{
  m_subMeanInter0MonitorPosSeq->subWriteContents(ofs,UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT); // Yes, always ".m"
  m_subMeanInter0Mean->subWriteContents(ofs,UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT); // Yes, always ".m"
  m_subMeanInter0Clt95->subWriteContents(ofs,UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT); // Yes, always ".m"
  m_subMeanInter0Empirical90->subWriteContents(ofs,UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT); // Yes, always ".m"
  m_subMeanInter0Min->subWriteContents(ofs,UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT); // Yes, always ".m"
  m_subMeanInter0Max->subWriteContents(ofs,UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT); // Yes, always ".m"

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedMeanMonitorWrite(std::ofstream& ofs)
{
  // std::set<unsigned int> tmpSet;
  // tmpSet.insert(0);
  m_unifiedMeanMonitorPosSeq->subWriteContents(ofs,UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT); // Yes, always ".m" // Yes, 'subWriteContents()'
  m_unifiedMeanVecSeq->subWriteContents(ofs,UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT); // Yes, always ".m"        // Yes, 'subWriteContents()'
  m_unifiedMeanCltStdSeq->subWriteContents(ofs,UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT); // Yes, always ".m"     // Yes, 'subWriteContents()'

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMeanMonitorFree()
{
  delete m_subMeanMonitorPosSeq;
  m_subMeanMonitorPosSeq = NULL;
  delete m_subMeanVecSeq;
  m_subMeanVecSeq = NULL;
  delete m_subMeanCltStdSeq;
  m_subMeanCltStdSeq = NULL;

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMeanInter0MonitorFree()
{
  delete m_subMeanInter0MonitorPosSeq;
  m_subMeanInter0MonitorPosSeq = NULL;
  delete m_subMeanInter0Mean;
  m_subMeanInter0Mean = NULL;
  delete m_subMeanInter0Clt95;
  m_subMeanInter0Clt95 = NULL;
  delete m_subMeanInter0Empirical90;
  m_subMeanInter0Empirical90 = NULL;
  delete m_subMeanInter0Min;
  m_subMeanInter0Min = NULL;
  delete m_subMeanInter0Max;
  m_subMeanInter0Max = NULL;

  return;
}


template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedMeanMonitorFree()
{
  delete m_unifiedMeanMonitorPosSeq;
  m_unifiedMeanMonitorPosSeq = NULL;
  delete m_unifiedMeanVecSeq;
  m_unifiedMeanVecSeq = NULL;
  delete m_unifiedMeanCltStdSeq;
  m_unifiedMeanCltStdSeq = NULL;

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::copy(const uqSequenceOfVectorsClass<V,M>& src)
{
  uqBaseVectorSequenceClass<V,M>::copy(src);
  for (unsigned int i = 0; i < (unsigned int) m_seq.size(); ++i) {
    if (m_seq[i]) delete m_seq[i];
  }
  m_seq.resize(src.subSequenceSize(),NULL);
  for (unsigned int i = 0; i < m_seq.size(); ++i) {
    m_seq[i] = new V(*(src.m_seq[i]));
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::append(
  const uqSequenceOfVectorsClass<V,M>& src,
  unsigned int                         initialPos,
  unsigned int                         numPos)
{
  UQ_FATAL_TEST_MACRO((src.subSequenceSize() < (initialPos+1)),
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<T>::append()",
                      "initialPos is too big");

  UQ_FATAL_TEST_MACRO((src.subSequenceSize() < (initialPos+numPos)),
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<T>::append()",
                      "numPos is too big");

  uqBaseVectorSequenceClass<V,M>::deleteStoredVectors();
  unsigned int currentSize = this->subSequenceSize();
  m_seq.resize(currentSize+numPos,NULL);
  for (unsigned int i = 0; i < numPos; ++i) {
    m_seq[currentSize+i] = new V(*(src.m_seq[initialPos+i]));
  }

  return;
}

template <class V, class M>
unsigned int
uqSequenceOfVectorsClass<V,M>::subSequenceSize() const
{
  return m_seq.size();
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::resizeSequence(unsigned int newSubSequenceSize)
{
  if (newSubSequenceSize != this->subSequenceSize()) {
    if (newSubSequenceSize < this->subSequenceSize()) {
      this->resetValues(newSubSequenceSize,this->subSequenceSize()-newSubSequenceSize);
    }
    m_seq.resize(newSubSequenceSize,NULL);
    std::vector<const V*>(m_seq).swap(m_seq);
  }

  uqBaseVectorSequenceClass<V,M>::deleteStoredVectors();

 return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::resetValues(unsigned int initialPos, unsigned int numPos)
{
  bool bRC = ((initialPos          <  this->subSequenceSize()) &&
              (0                   <  numPos                 ) &&
              ((initialPos+numPos) <= this->subSequenceSize()));
  if ((bRC == false) && (m_env.subDisplayFile())) {
    *m_env.subDisplayFile() << "In uqSequenceOfVectorsClass<V,M>::resetValues()"
                           << ", initialPos = "              << initialPos
                           << ", this->subSequenceSize() = " << this->subSequenceSize()
                           << ", numPos = "                  << numPos
                           << std::endl;
  }
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::resetValues()",
                      "invalid input data");

  for (unsigned int j = 0; j < numPos; ++j) {
    if (m_seq[initialPos+j] != NULL) {
      delete m_seq[initialPos+j];
      m_seq[initialPos+j] = NULL;
    }
  }

  uqBaseVectorSequenceClass<V,M>::deleteStoredVectors();

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::erasePositions(unsigned int initialPos, unsigned int numPos)
{
  bool bRC = ((initialPos          <  this->subSequenceSize()) &&
              (0                   <  numPos                 ) &&
              ((initialPos+numPos) <= this->subSequenceSize()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::erasePositions()",
                      "invalid input data");

  for (unsigned int j = 0; j < numPos; ++j) {
    if (m_seq[initialPos+j] != NULL) delete m_seq[initialPos+j];
  }

  seqVectorPositionIteratorTypedef posIteratorBegin = m_seq.begin();
  if (initialPos < this->subSequenceSize()) std::advance(posIteratorBegin,initialPos);
  else                                      posIteratorBegin = m_seq.end();

  unsigned int posEnd = initialPos + numPos - 1;
  seqVectorPositionIteratorTypedef posIteratorEnd = m_seq.begin();
  if (posEnd < this->subSequenceSize()) std::advance(posIteratorEnd,posEnd);
  else                                  posIteratorEnd = m_seq.end();

  unsigned int oldSubSequenceSize = this->subSequenceSize();
  m_seq.erase(posIteratorBegin,posIteratorEnd);
  UQ_FATAL_TEST_MACRO((oldSubSequenceSize - numPos) != this->subSequenceSize(),
                      m_env.worldRank(),
                      "uqSequenceOfVectors::erasePositions()",
                      "(oldSubSequenceSize - numPos) != this->subSequenceSize()");

  uqBaseVectorSequenceClass<V,M>::deleteStoredVectors();

  return;
}

#ifdef UQ_SEQ_VEC_USES_OPERATOR
template <class V, class M>
const V*
uqSequenceOfVectorsClass<V,M>::operator[](unsigned int posId) const
{
  UQ_FATAL_TEST_MACRO((posId >= this->subSequenceSize()),
                      m_env.worldRank(),
                      "uqSequenceOfVectorss<V,M>::operator[] const",
                      "posId > subSequenceSize()");

  return (const V*) (m_seq[posId]);
}

template <class V, class M>
const V*&
uqSequenceOfVectorsClass<V,M>::operator[](unsigned int posId)
{
  UQ_FATAL_TEST_MACRO((posId >= this->subSequenceSize()),
                      m_env.worldRank(),
                      "uqSequenceOfVectorss<V,M>::operator[] const",
                      "posId > subSequenceSize()");

  return m_seq[posId];
}
#endif

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::getPositionValues(unsigned int posId, V& vec) const
{
  UQ_FATAL_TEST_MACRO((posId >= this->subSequenceSize()),
                      m_env.worldRank(),
                      "uqSequenceOfVectorss<V,M>::getPositionValues()",
                      "posId > subSequenceSize()");

  vec = *(m_seq[posId]); // *(const_cast<V*>(m_seq[posId])); // prudenci 2010-06-17 mox

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::setPositionValues(unsigned int posId, const V& vec)
{
  UQ_FATAL_TEST_MACRO((posId >= this->subSequenceSize()),
                      m_env.worldRank(),
                      "uqSequenceOfVectorss<V,M>::setPositionValues()",
                      "posId > subSequenceSize()");

  if (m_seq[posId] != NULL) delete m_seq[posId];
  m_seq[posId] = new V(vec);

  //if (posId == 0) {
  //  std::cout << "In uqSequenceOfVectorsClass<V,M>::setPositionValues(): m_seq[0] = " << m_seq[0] << ", *(m_seq[0]) = " << *(m_seq[0])
  //            << std::endl;
  //}

  uqBaseVectorSequenceClass<V,M>::deleteStoredVectors();

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::setGaussian(const gsl_rng* rng, const V& meanVec, const V& stdDevVec)
{
  V gaussianVector(m_vectorSpace.zeroVector());
  for (unsigned int j = 0; j < this->subSequenceSize(); ++j) {
    gaussianVector.cwSetGaussian(m_env.rng(),meanVec,stdDevVec);
    if (m_seq[j] != NULL) delete m_seq[j];
    m_seq[j] = new V(gaussianVector);
  }

  uqBaseVectorSequenceClass<V,M>::deleteStoredVectors();

  return;
}


template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::setUniform(const gsl_rng* rng, const V& aVec, const V& bVec)
{
  V uniformVector(m_vectorSpace.zeroVector());
  for (unsigned int j = 0; j < this->subSequenceSize(); ++j) {
    uniformVector.cwSetUniform(m_env.rng(),aVec,bVec);
    if (m_seq[j] != NULL) delete m_seq[j];
    m_seq[j] = new V(uniformVector);
  }

  uqBaseVectorSequenceClass<V,M>::deleteStoredVectors();

  return;
}

#ifdef UQ_ALSO_COMPUTE_MDFS_WITHOUT_KDE
template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subUniformlySampledMdf(
  const V&                       numEvaluationPointsVec,
  uqArrayOfOneDGridsClass <V,M>& mdfGrids,
  uqArrayOfOneDTablesClass<V,M>& mdfValues) const
{
  V minDomainValues(m_vectorSpace.zeroVector());
  V maxDomainValues(m_vectorSpace.zeroVector());

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(0,                 // initialPos
                           1,                 // spacing
                           subSequenceSize(), // numPos
                           i,
                           data);

    std::vector<double> aMdf(0);
    data.subUniformlySampledMdf((unsigned int) numEvaluationPointsVec[i],
                                minDomainValues[i],
                                maxDomainValues[i],
                                aMdf);
    mdfValues.setOneDTable(i,aMdf);
  }

  mdfGrids.setUniformGrids(numEvaluationPointsVec,
                           minDomainValues,
                           maxDomainValues);

  return;
}
#endif
template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subUniformlySampledCdf(
  const V&                       numEvaluationPointsVec,
  uqArrayOfOneDGridsClass <V,M>& cdfGrids,
  uqArrayOfOneDTablesClass<V,M>& cdfValues) const
{
  V minDomainValues(m_vectorSpace.zeroVector());
  V maxDomainValues(m_vectorSpace.zeroVector());

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(0,                 // initialPos
                           1,                 // spacing
                           subSequenceSize(), // numPos
                           i,
                           data);

    std::vector<double> aCdf(0);
    data.subUniformlySampledCdf((unsigned int) numEvaluationPointsVec[i],
                                minDomainValues[i],
                                maxDomainValues[i],
                                aCdf);
    cdfValues.setOneDTable(i,aCdf);
  }

  cdfGrids.setUniformGrids(numEvaluationPointsVec,
                           minDomainValues,
                           maxDomainValues);

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedUniformlySampledCdf(
  const V&                       numEvaluationPointsVec,
  uqArrayOfOneDGridsClass <V,M>& unifiedCdfGrids,
  uqArrayOfOneDTablesClass<V,M>& unifiedCdfValues) const
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
    *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::unifiedUniformlySampledCdf()"
                           << std::endl;
  }

  V unifiedMinDomainValues(m_vectorSpace.zeroVector());
  V unifiedMaxDomainValues(m_vectorSpace.zeroVector());

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(0,                 // initialPos
                           1,                 // spacing
                           subSequenceSize(), // numPos
                           i,
                           data);

    std::vector<double> aCdf(0);
    data.unifiedUniformlySampledCdf(m_vectorSpace.numOfProcsForStorage() == 1,
                                    (unsigned int) numEvaluationPointsVec[i],
                                    unifiedMinDomainValues[i],
                                    unifiedMaxDomainValues[i],
                                    aCdf);
    unifiedCdfValues.setOneDTable(i,aCdf);
  }

  unifiedCdfGrids.setUniformGrids(numEvaluationPointsVec,
                                  unifiedMinDomainValues,
                                  unifiedMaxDomainValues);

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
    *m_env.subDisplayFile() << "Leaving uqSequenceOfVectorsClass<V,M>::unifiedUniformlySampledCdf()"
                           << std::endl;
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMean(
  unsigned int initialPos,
  unsigned int numPos,
  V&           meanVec) const
{
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::subMean()"
                           << ": initialPos = "        << initialPos
                           << ", numPos = "            << numPos
                           << ", sub sequence size = " << this->subSequenceSize()
                           << std::endl;
  }

  bool bRC = ((initialPos          <  this->subSequenceSize()) &&
              (0                   <  numPos                 ) &&
              ((initialPos+numPos) <= this->subSequenceSize()) &&
              (this->vectorSizeLocal()  == meanVec.sizeLocal()         ));
  if ((bRC == false) && (m_env.subDisplayFile())) {
    *m_env.subDisplayFile() << "In uqSequenceOfVectorsClass<V,M>::subMean()"
                           << ", initialPos = "              << initialPos
                           << ", this->subSequenceSize() = " << this->subSequenceSize()
                           << ", numPos = "                  << numPos
                           << ", this->vectorSizeLocal() = " << this->vectorSizeLocal()
                           << ", meanVec.sizeLocal() = "     << meanVec.sizeLocal()
                           << std::endl;
  }
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subMean()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    meanVec[i] = data.subMean(0,
                              numPos);
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqSequenceOfVectorsClass<V,M>::subMean()"
                           << ": initialPos = "        << initialPos
                           << ", numPos = "            << numPos
                           << ", sub sequence size = " << this->subSequenceSize()
                           << ", meanVec = "           << meanVec
                           << std::endl;
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedMean(
  unsigned int initialPos,
  unsigned int numPos,
  V&           unifiedMeanVec) const
{
  unsigned int tmpUnif = this->unifiedSequenceSize();
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::unifiedMean()"
                            << ": initialPos = "            << initialPos
                            << ", numPos = "                << numPos
                            << ", sub sequence size = "     << this->subSequenceSize()
                            << ", unified sequence size = " << tmpUnif
                            << std::endl;
  }

  bool bRC = ((initialPos              <  this->subSequenceSize()   ) &&
              (0                       <  numPos                    ) &&
              ((initialPos+numPos)     <= this->subSequenceSize()   ) &&
              (this->vectorSizeLocal() == unifiedMeanVec.sizeLocal()));
  if ((bRC == false) && (m_env.subDisplayFile())) {
    *m_env.subDisplayFile() << "In uqSequenceOfVectorsClass<V,M>::unifiedMean()"
                            << ", initialPos = "                 << initialPos
                            << ", this->subSequenceSize() = "    << this->subSequenceSize()
                            << ", numPos = "                     << numPos
                            << ", this->vectorSizeLocal() = "    << this->vectorSizeLocal()
                            << ", unifiedMeanVec.sizeLocal() = " << unifiedMeanVec.sizeLocal()
                            << std::endl;
  }
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::unifiedMean()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    unifiedMeanVec[i] = data.unifiedMean(m_vectorSpace.numOfProcsForStorage() == 1,
                                         0,
                                         numPos);
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 5)) {
    *m_env.subDisplayFile() << "Leaving uqSequenceOfVectorsClass<V,M>::unifiedMean()"
                           << ": initialPos = "            << initialPos
                           << ", numPos = "                << numPos
                           << ", sub sequence size = "     << this->subSequenceSize()
                           << ", unified sequence size = " << tmpUnif
                           << ", unifiedMeanVec = "        << unifiedMeanVec
                           << std::endl;
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMeanCltStd(
  unsigned int initialPos,
  unsigned int numPos,
  const V&     meanVec,
  V&           stdVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()) &&
              (0                       <  numPos                 ) &&
              ((initialPos+numPos)     <= this->subSequenceSize()) &&
              (this->vectorSizeLocal() == meanVec.sizeLocal()    ) &&
              (this->vectorSizeLocal() == stdVec.sizeLocal()     ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subMeanCltStd()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    stdVec[i] = data.subMeanCltStd(0,
                                   numPos,
                                   meanVec[i]);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedMeanCltStd(
  unsigned int initialPos,
  unsigned int numPos,
  const V&     unifiedMeanVec,
  V&           unifiedSamVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()   ) &&
              (0                       <  numPos                    ) &&
              ((initialPos+numPos)     <= this->subSequenceSize()   ) &&
              (this->vectorSizeLocal() == unifiedMeanVec.sizeLocal()) &&
              (this->vectorSizeLocal() == unifiedSamVec.sizeLocal() ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::unifiedMeanCltStd()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    unifiedSamVec[i] = data.unifiedMeanCltStd(m_vectorSpace.numOfProcsForStorage() == 1,
                                              0,
                                              numPos,
                                              unifiedMeanVec[i]);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subSampleVariance(
  unsigned int initialPos,
  unsigned int numPos,
  const V&     meanVec,
  V&           samVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()) &&
              (0                       <  numPos                 ) &&
              ((initialPos+numPos)     <= this->subSequenceSize()) &&
              (this->vectorSizeLocal() == meanVec.sizeLocal()    ) &&
              (this->vectorSizeLocal() == samVec.sizeLocal()     ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subSampleVariance()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    samVec[i] = data.subSampleVariance(0,
                                       numPos,
                                       meanVec[i]);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedSampleVariance(
  unsigned int initialPos,
  unsigned int numPos,
  const V&     unifiedMeanVec,
  V&           unifiedSamVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()   ) &&
              (0                       <  numPos                    ) &&
              ((initialPos+numPos)     <= this->subSequenceSize()   ) &&
              (this->vectorSizeLocal() == unifiedMeanVec.sizeLocal()) &&
              (this->vectorSizeLocal() == unifiedSamVec.sizeLocal() ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::unifiedSampleVariance()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    unifiedSamVec[i] = data.unifiedSampleVariance(m_vectorSpace.numOfProcsForStorage() == 1,
                                                  0,
                                                  numPos,
                                                  unifiedMeanVec[i]);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subPopulationVariance(
  unsigned int initialPos,
  unsigned int numPos,
  const V&     meanVec,
  V&           popVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()) &&
              (0                       <  numPos                 ) &&
              ((initialPos+numPos)     <= this->subSequenceSize()) &&
              (this->vectorSizeLocal() == meanVec.sizeLocal()    ) &&
              (this->vectorSizeLocal() == popVec.sizeLocal()     ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subPopulationVariance()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    popVec[i] = data.subPopulationVariance(0,
                                           numPos,
                                           meanVec[i]);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedPopulationVariance(
  unsigned int initialPos,
  unsigned int numPos,
  const V&     unifiedMeanVec,
  V&           unifiedPopVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()   ) &&
              (0                       <  numPos                    ) &&
              ((initialPos+numPos)     <= this->subSequenceSize()   ) &&
              (this->vectorSizeLocal() == unifiedMeanVec.sizeLocal()) &&
              (this->vectorSizeLocal() == unifiedPopVec.sizeLocal() ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::unifiedPopulationVariance()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    unifiedPopVec[i] = data.unifiedPopulationVariance(m_vectorSpace.numOfProcsForStorage() == 1,
                                                      0,
                                                      numPos,
                                                      unifiedMeanVec[i]);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::autoCovariance(
  unsigned int initialPos,
  unsigned int numPos,
  const V&     meanVec,
  unsigned int lag,
  V&           covVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()) &&
              (0                       <  numPos                 ) &&
              ((initialPos+numPos)     <= this->subSequenceSize()) &&
              (this->vectorSizeLocal() == meanVec.sizeLocal()    ) &&
              (lag                     <  numPos                 ) && // lag should not be too large
              (this->vectorSizeLocal() == covVec.sizeLocal()     ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::autoCovariance()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    covVec[i] = data.autoCovariance(0,
                                    numPos,
                                    meanVec[i],
                                    lag);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::autoCorrViaDef(
  unsigned int initialPos,
  unsigned int numPos,
  unsigned int lag,
  V&           corrVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()) &&
              (0                       <  numPos                 ) &&
              ((initialPos+numPos)     <= this->subSequenceSize()) &&
              (lag                     <  numPos                 ) && // lag should not be too large
              (this->vectorSizeLocal() == corrVec.sizeLocal()    ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::autoCorrViaDef()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    corrVec[i] = data.autoCorrViaDef(0,
                                     numPos,
                                     lag);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::autoCorrViaFft(
  unsigned int                     initialPos,
  unsigned int                     numPos,
  const std::vector<unsigned int>& lags,
  std::vector<V*>&                 corrVecs) const
{
  bool bRC = ((initialPos          <  this->subSequenceSize()) &&
              (0                   <  numPos                 ) &&
              ((initialPos+numPos) <= this->subSequenceSize()) &&
              (0                   <  lags.size()            ) &&
              (lags[lags.size()-1] <  numPos                 )); // lag should not be too large
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::autoCorrViaFft()",
                      "invalid input data");

  for (unsigned int j = lags.size(); j < corrVecs.size(); ++j) {
    if (corrVecs[j] != NULL) delete corrVecs[j];
  }
  corrVecs.resize(lags.size(),NULL);
  for (unsigned int j = 0;           j < corrVecs.size(); ++j) {
    if (corrVecs[j] == NULL) corrVecs[j] = new V(m_vectorSpace.zeroVector());
  }

  uqScalarSequenceClass<double> data(m_env,0,"");
  unsigned int maxLag = lags[lags.size()-1];
  std::vector<double> autoCorrs(maxLag+1,0.); // Yes, +1

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);

    //if (m_env.subDisplayFile()) {
    //  *m_env.subDisplayFile() << "In uqSequenceOfVectorsClass<V,M>::autoCorrViaFft()"
    //                         << ": about to call data.autoCorrViaFft() for paramId = " << i
    //                         << ", with numPos = "      << numPos
    //                         << ", maxLag = "           << maxLag
    //                         << ", autoCorrs.size() = " << autoCorrs.size()
    //                         << std::endl;
    //}
    data.autoCorrViaFft(0,
                        numPos,
                        maxLag,
                        autoCorrs);

    for (unsigned int j = 0; j < lags.size(); ++j) {
      (*(corrVecs[j]))[i] = autoCorrs[lags[j]];
    }
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::autoCorrViaFft(
  unsigned int initialPos,
  unsigned int numPos,
  unsigned int numSum,
  V&           autoCorrsSumVec) const
{
  bool bRC = ((initialPos             <  this->subSequenceSize()) &&
              (0                      <  numPos                 ) &&
              ((initialPos+numPos)    <= this->subSequenceSize()) &&
              (0                      <  numSum                 ) &&
              (numSum                 <= numPos                 ) &&
              (autoCorrsSumVec.sizeLocal() == this->vectorSizeLocal()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::autoCorrViaFft(), for sum",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);

    data.autoCorrViaFft(0,
                        numPos,
                        numSum,
                        autoCorrsSumVec[i]);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::bmm(
  unsigned int initialPos,
  unsigned int batchLength,
  V&           bmmVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()            ) &&
              (batchLength             < (this->subSequenceSize()-initialPos)) &&
              (this->vectorSizeLocal() == bmmVec.sizeLocal()                 ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::bmm()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           this->subSequenceSize()-initialPos,
                           i,
                           data);
    bmmVec[i] = data.bmm(0,
                         batchLength);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::fftForward(
  unsigned int                        initialPos,
  unsigned int                        fftSize,
  unsigned int                        paramId,
  std::vector<std::complex<double> >& fftResult) const
{
  bool bRC = ((initialPos           <  this->subSequenceSize()) &&
              (paramId              <  this->vectorSizeLocal()) &&
              (0                    <  fftSize                ) &&
              ((initialPos+fftSize) <= this->subSequenceSize()) &&
              (fftSize              <  this->subSequenceSize()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::fftForward()",
                      "invalid input data");

  std::vector<double> rawData(fftSize,0.);
  this->extractRawData(initialPos,
                       1, // spacing
                       fftSize,
                       paramId,
                       rawData);

  m_fftObj->forward(rawData,fftSize,fftResult);

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::psd(
  unsigned int         initialPos,
  unsigned int         numBlocks,
  double               hopSizeRatio,
  unsigned int         paramId,
  std::vector<double>& psdResult) const
{
  bool bRC = ((initialPos < this->subSequenceSize()) &&
              (paramId    < this->vectorSizeLocal()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::psd()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");

  this->extractScalarSeq(initialPos,
                         1, // spacing
                         this->subSequenceSize()-initialPos,
                         paramId,
                         data);
  data.psd(0,
           numBlocks,
           hopSizeRatio,
           psdResult);

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::psdAtZero(
  unsigned int initialPos,
  unsigned int numBlocks,
  double       hopSizeRatio,
  V&           psdVec) const
{
  bool bRC = ((initialPos         <  this->subSequenceSize()) &&
              (this->vectorSizeLocal() == psdVec.sizeLocal()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::psdAtZero()",
                      "invalid input data");

  uqScalarSequenceClass<double> data(m_env,0,"");
  std::vector<double> psdResult(0,0.); // size will be determined by 'data.psd()'

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           this->subSequenceSize()-initialPos,
                           i,
                           data);
    data.psd(0,
             numBlocks,
             hopSizeRatio,
             psdResult);
    psdVec[i] = psdResult[0];
    //*m_env.subDisplayFile() << "psdResult[0] = " << psdResult[0] << std::endl;
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::geweke(
  unsigned int initialPos,
  double       ratioNa,
  double       ratioNb,
  V&           gewVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()) &&
              (this->vectorSizeLocal() == gewVec.sizeLocal()     ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::geweke()",
                      "invalid input data");

  unsigned int numPos = this->subSequenceSize() - initialPos;
  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    gewVec[i] = data.geweke(0,
                            ratioNa,
                            ratioNb);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::meanStacc(
  unsigned int initialPos,
  V&           meanStaccVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize() ) &&
              (this->vectorSizeLocal() == meanStaccVec.sizeLocal()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::meanStacc()",
                      "invalid input data");

  unsigned int numPos = this->subSequenceSize() - initialPos;
  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    meanStaccVec[i] = data.meanStacc(0);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subMinMax(
  unsigned int initialPos,
  unsigned int numPos,
  V&           minVec,
  V&           maxVec) const
{
  bool bRC = ((0                       <  numPos                 ) &&
              ((initialPos+numPos)     <= this->subSequenceSize()) &&
              (this->vectorSizeLocal() == minVec.sizeLocal()     ) &&
              (this->vectorSizeLocal() == maxVec.sizeLocal()     ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subMinMax()",
                      "invalid input data");

  //unsigned int numPos = this->subSequenceSize() - initialPos;
  unsigned int numParams = this->vectorSizeLocal();
  uqScalarSequenceClass<double> data(m_env,0,"");

  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    data.subMinMax(0,numPos,minVec[i],maxVec[i]);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedMinMax(
  unsigned int initialPos,
  unsigned int numPos,
  V&           unifiedMinVec,
  V&           unifiedMaxVec) const
{
  bool bRC = ((0                       <  numPos                   ) &&
              ((initialPos+numPos)     <= this->subSequenceSize()  ) &&
              (this->vectorSizeLocal() == unifiedMinVec.sizeLocal()) &&
              (this->vectorSizeLocal() == unifiedMaxVec.sizeLocal()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::unifiedMinMax()",
                      "invalid input data");

  //unsigned int numPos = this->subSequenceSize() - initialPos;
  unsigned int numParams = this->vectorSizeLocal();
  uqScalarSequenceClass<double> data(m_env,0,"");

  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    data.unifiedMinMax(m_vectorSpace.numOfProcsForStorage() == 1,
                       0,
                       numPos,
                       unifiedMinVec[i],
                       unifiedMaxVec[i]);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subHistogram(
  unsigned int     initialPos,
  const V&         minVec,
  const V&         maxVec,
  std::vector<V*>& centersForAllBins,
  std::vector<V*>& quanttsForAllBins) const
{
  bool bRC = ((initialPos               <  this->subSequenceSize() ) &&
              (this->vectorSizeLocal()  == minVec.sizeLocal()      ) &&
              (this->vectorSizeLocal()  == maxVec.sizeLocal()      ) &&
              (0                        <  centersForAllBins.size()) &&
              (centersForAllBins.size() == quanttsForAllBins.size()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subHistogram()",
                      "invalid input data");

  for (unsigned int j = 0; j < quanttsForAllBins.size(); ++j) {
    centersForAllBins[j] = new V(m_vectorSpace.zeroVector());
    quanttsForAllBins [j] = new V(m_vectorSpace.zeroVector());
  }

  unsigned int dataSize = this->subSequenceSize() - initialPos;
  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    uqScalarSequenceClass<double> data(m_env,dataSize,"");
    for (unsigned int j = 0; j < dataSize; ++j) {
      data[j] = (*(m_seq[initialPos+j]))[i];
    }

    std::vector<double      > centers(centersForAllBins.size(),0.);
    std::vector<unsigned int> quantts(quanttsForAllBins.size(), 0 );
    data.subHistogram(0,
                      minVec[i],
                      maxVec[i],
                      centers,
                      quantts);

    for (unsigned int j = 0; j < quantts.size(); ++j) {
      (*(centersForAllBins[j]))[i] = centers[j];
      (*(quanttsForAllBins[j]))[i] = (double) quantts[j];
    }
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedHistogram(
  unsigned int     initialPos,
  const V&         unifiedMinVec,
  const V&         unifiedMaxVec,
  std::vector<V*>& unifiedCentersForAllBins,
  std::vector<V*>& unifiedQuanttsForAllBins) const
{
  bool bRC = ((initialPos                      <  this->subSequenceSize()        ) &&
              (this->vectorSizeLocal()         == unifiedMinVec.sizeLocal()      ) &&
              (this->vectorSizeLocal()         == unifiedMaxVec.sizeLocal()      ) &&
              (0                               <  unifiedCentersForAllBins.size()) &&
              (unifiedCentersForAllBins.size() == unifiedQuanttsForAllBins.size()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::unifiedHistogram()",
                      "invalid input data");

  for (unsigned int j = 0; j < unifiedQuanttsForAllBins.size(); ++j) {
    unifiedCentersForAllBins[j] = new V(m_vectorSpace.zeroVector());
    unifiedQuanttsForAllBins [j] = new V(m_vectorSpace.zeroVector());
  }

  unsigned int dataSize = this->subSequenceSize() - initialPos;
  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    uqScalarSequenceClass<double> data(m_env,dataSize,"");
    for (unsigned int j = 0; j < dataSize; ++j) {
      data[j] = (*(m_seq[initialPos+j]))[i];
    }

    std::vector<double      > unifiedCenters(unifiedCentersForAllBins.size(),0.);
    std::vector<unsigned int> unifiedQuantts(unifiedQuanttsForAllBins.size(), 0 );
    data.unifiedHistogram(m_vectorSpace.numOfProcsForStorage() == 1,
                          0,
                          unifiedMinVec[i],
                          unifiedMaxVec[i],
                          unifiedCenters,
                          unifiedQuantts);

    for (unsigned int j = 0; j < unifiedQuantts.size(); ++j) {
      (*(unifiedCentersForAllBins[j]))[i] = unifiedCenters[j];
      (*(unifiedQuanttsForAllBins[j]))[i] = (double) unifiedQuantts[j];
    }
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subCdfStacc(
  unsigned int     initialPos,
  std::vector<V*>& cdfStaccVecs,
  std::vector<V*>& cdfStaccVecsUp,
  std::vector<V*>& cdfStaccVecsLow,  
  std::vector<V*>& sortedDataVecs) const
{
  bool bRC = (initialPos < this->subSequenceSize());
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subCdfStacc()",
                      "invalid input data");

  unsigned int numPos = this->subSequenceSize() - initialPos;
  unsigned int numEvals = numPos;
  for (unsigned int j = 0; j < numEvals; ++j) {
    cdfStaccVecs   [j] = new V(m_vectorSpace.zeroVector());
    cdfStaccVecsUp [j] = new V(m_vectorSpace.zeroVector());
    cdfStaccVecsLow[j] = new V(m_vectorSpace.zeroVector());
    sortedDataVecs [j] = new V(m_vectorSpace.zeroVector());
  }
  std::vector<double> cdfStaccs   (numEvals,0.);
  std::vector<double> cdfStaccsup (numEvals,0.);
  std::vector<double> cdfStaccslow(numEvals,0.);

  uqScalarSequenceClass<double> data      (m_env,0,"");
  uqScalarSequenceClass<double> sortedData(m_env,0,"");
  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    //std::cout << "x-data" << data<< std::endl;
    data.subSort(initialPos,sortedData);
    data.subCdfStacc(initialPos,
                     cdfStaccs,
                     cdfStaccsup,
                     cdfStaccslow,
                     sortedData);

    for (unsigned int j = 0; j < numEvals; ++j) {
      (*sortedDataVecs [j])[i] = sortedData  [j];
      (*cdfStaccVecs   [j])[i] = cdfStaccs   [j];
      (*cdfStaccVecsUp [j])[i] = cdfStaccsup [j];
      (*cdfStaccVecsLow[j])[i] = cdfStaccslow[j];
    }
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subCdfStacc(
  unsigned int           initialPos,
  const std::vector<V*>& evalPositionsVecs,
  std::vector<V*>&       cdfStaccVecs) const
{
  bool bRC = ((initialPos               <  this->subSequenceSize() ) &&
              (0                        <  evalPositionsVecs.size()) &&
              (evalPositionsVecs.size() == cdfStaccVecs.size()     ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subCdfStacc()",
                      "invalid input data");

  unsigned int numPos = this->subSequenceSize() - initialPos;
  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numEvals = evalPositionsVecs.size();
  for (unsigned int j = 0; j < numEvals; ++j) {
    cdfStaccVecs[j] = new V(m_vectorSpace.zeroVector());
  }
  std::vector<double> evalPositions(numEvals,0.);
  std::vector<double> cdfStaccs    (numEvals,0.);

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);

    for (unsigned int j = 0; j < numEvals; ++j) {
      evalPositions[j] = (*evalPositionsVecs[j])[i];
    }

    data.subCdfStacc(0,
                     evalPositions,
                     cdfStaccs);

    for (unsigned int j = 0; j < numEvals; ++j) {
      (*cdfStaccVecs[j])[i] = cdfStaccs[j];
    }
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subInterQuantileRange(
  unsigned int initialPos,
  V&           iqrVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()) &&
              (this->vectorSizeLocal() == iqrVec.sizeLocal()     ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subInterQuantileRange()",
                      "invalid input data");

  unsigned int numPos = this->subSequenceSize() - initialPos;
  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    iqrVec[i] = data.subInterQuantileRange(0);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedInterQuantileRange(
  unsigned int initialPos,
  V&           unifiedIqrVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()  ) &&
              (this->vectorSizeLocal() == unifiedIqrVec.sizeLocal()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::unifiedInterQuantileRange()",
                      "invalid input data");

  unsigned int numPos = this->subSequenceSize() - initialPos;
  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    unifiedIqrVec[i] = data.unifiedInterQuantileRange(m_vectorSpace.numOfProcsForStorage() == 1,
                                                      0);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subScalesForKde(
  unsigned int initialPos,
  const V&     iqrVec,
  unsigned int kdeDimension,
  V&           scaleVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()) &&
              (this->vectorSizeLocal() == iqrVec.sizeLocal()     ) &&
              (this->vectorSizeLocal() == scaleVec.sizeLocal()   ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subScalesForKde()",
                      "invalid input data");

  unsigned int numPos = this->subSequenceSize() - initialPos;
  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    scaleVec[i] = data.subScaleForKde(0,
                                      iqrVec[i],
                                      kdeDimension);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedScalesForKde(
  unsigned int initialPos,
  const V&     unifiedIqrVec,
  unsigned int kdeDimension,
  V&           unifiedScaleVec) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()    ) &&
              (this->vectorSizeLocal() == unifiedIqrVec.sizeLocal()  ) &&
              (this->vectorSizeLocal() == unifiedScaleVec.sizeLocal()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::unifiedScalesForKde()",
                      "invalid input data");

  unsigned int numPos = this->subSequenceSize() - initialPos;
  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);
    unifiedScaleVec[i] = data.unifiedScaleForKde(m_vectorSpace.numOfProcsForStorage() == 1,
                                                 0,
                                                 unifiedIqrVec[i],
                                                 kdeDimension);
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subGaussian1dKde(
  unsigned int           initialPos,
  const V&               scaleVec,
  const std::vector<V*>& evalParamVecs,
  std::vector<V*>&       densityVecs) const
{
  bool bRC = ((initialPos              <  this->subSequenceSize()) &&
              (this->vectorSizeLocal() == scaleVec.sizeLocal()   ) &&
              (0                       <  evalParamVecs.size()   ) &&
              (evalParamVecs.size()    == densityVecs.size()     ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subGaussian1dKde()",
                      "invalid input data");

  unsigned int numPos = this->subSequenceSize() - initialPos;
  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numEvals = evalParamVecs.size();
  for (unsigned int j = 0; j < numEvals; ++j) {
    densityVecs[j] = new V(m_vectorSpace.zeroVector());
  }
  std::vector<double> evalParams(numEvals,0.);
  std::vector<double> densities  (numEvals,0.);

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);

    for (unsigned int j = 0; j < numEvals; ++j) {
      evalParams[j] = (*evalParamVecs[j])[i];
    }

    data.subGaussian1dKde(0,
                          scaleVec[i],
                          evalParams,
                          densities);

    for (unsigned int j = 0; j < numEvals; ++j) {
      (*densityVecs[j])[i] = densities[j];
    }
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedGaussian1dKde(
  unsigned int           initialPos,
  const V&               unifiedScaleVec,
  const std::vector<V*>& unifiedEvalParamVecs,
  std::vector<V*>&       unifiedDensityVecs) const
{
  bool bRC = ((initialPos                  <  this->subSequenceSize()    ) &&
              (this->vectorSizeLocal()     == unifiedScaleVec.sizeLocal()) &&
              (0                           <  unifiedEvalParamVecs.size()) &&
              (unifiedEvalParamVecs.size() == unifiedDensityVecs.size()  ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::unifiedGaussian1dKde()",
                      "invalid input data");

  unsigned int numPos = this->subSequenceSize() - initialPos;
  uqScalarSequenceClass<double> data(m_env,0,"");

  unsigned int numEvals = unifiedEvalParamVecs.size();
  for (unsigned int j = 0; j < numEvals; ++j) {
    unifiedDensityVecs[j] = new V(m_vectorSpace.zeroVector());
  }
  std::vector<double> unifiedEvalParams(numEvals,0.);
  std::vector<double> unifiedDensities (numEvals,0.);

  unsigned int numParams = this->vectorSizeLocal();
  for (unsigned int i = 0; i < numParams; ++i) {
    this->extractScalarSeq(initialPos,
                           1, // spacing
                           numPos,
                           i,
                           data);

    for (unsigned int j = 0; j < numEvals; ++j) {
      unifiedEvalParams[j] = (*unifiedEvalParamVecs[j])[i];
    }

    data.unifiedGaussian1dKde(m_vectorSpace.numOfProcsForStorage() == 1,
                              0,
                              unifiedScaleVec[i],
                              unifiedEvalParams,
                              unifiedDensities);

    for (unsigned int j = 0; j < numEvals; ++j) {
      (*unifiedDensityVecs[j])[i] = unifiedDensities[j];
    }
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::select(const std::vector<unsigned int>& idsOfUniquePositions)
{
  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::filter(
  unsigned int initialPos,
  unsigned int spacing)
{
  if (m_env.subDisplayFile()) {
    *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::filter()"
                           << ": initialPos = "      << initialPos
                           << ", spacing = "         << spacing
                           << ", subSequenceSize = " << this->subSequenceSize()
                           << std::endl;
  }

  unsigned int i = 0;
  unsigned int j = initialPos;
  unsigned int originalSubSequenceSize = this->subSequenceSize();
  while (j < originalSubSequenceSize) {
    if (i != j) {
      //*m_env.subDisplayFile() << i << "--" << j << " ";
      delete m_seq[i];
      m_seq[i] = new V(*(m_seq[j]));
    }
    i++;
    j += spacing;
  }

  this->resetValues(i,originalSubSequenceSize-i);
  this->resizeSequence(i);

  if (m_env.subDisplayFile()) {
    *m_env.subDisplayFile() << "Leaving uqSequenceOfVectorsClass<V,M>::filter()"
                           << ": initialPos = "      << initialPos
                           << ", spacing = "         << spacing
                           << ", subSequenceSize = " << this->subSequenceSize()
                           << std::endl;
  }

  return;
}

template <class V, class M>
double
uqSequenceOfVectorsClass<V,M>::estimateConvBrooksGelman(
  unsigned int initialPos,
  unsigned int numPos) const
{
  // This method requires *at least* two sequences. Error if there is only one.
  UQ_FATAL_RC_MACRO( (m_env.numSubEnvironments() < 2),
		     UQ_UNAVAILABLE_RANK,
		     "uqSequenceOfVectorsClass<V,M>::estimateConvBrooksGelman()",
		     "At least two sequences required for Brooks-Gelman convergence test.");

  // TODO: Need special case for 1-dimensional parameter space.

  // Initialize with garbage to give the user a clue something is funky.
  double convMeasure = -1.0;

  // We only do the work on the subenvironment where the sequence data
  // is stashed.
  if( m_env.inter0Rank() >= 0 )
    {
      // Sanity Checks
      
      
      // REMEMBER: \psi is a *vector* of parameters    
      // Get quantities we will use several times
      V psi_j_dot = m_vectorSpace.zeroVector();
      V psi_dot_dot = m_vectorSpace.zeroVector();
      V work = m_vectorSpace.zeroVector();

      // m = number of chains > 1
      // n = number of steps for which we are computing the metric
      int m = m_env.numSubEnvironments();
      int n = numPos;
	
      this->subMean( initialPos, numPos , psi_j_dot );
      this->unifiedMean( initialPos, numPos, psi_dot_dot );

#if 0
      std::cout << "psi_j_dot = " << psi_j_dot << std::endl;
      std::cout << "psi_dot_dot = " << psi_dot_dot << std::endl;
#endif

      /* W = \frac{1}{m*(n-1)}*\sum_{j=1}^m \sum{t=1}^n 
	 (\psi_{jt} - \overline{\psi_{j\cdot}})*(\psi_{jt} - \overline{\psi_{j\cdot}})^T
	 This corresponds to the "within-sequence" covariance matrix. */
      M* W_local = m_vectorSpace.newDiagMatrix( m_vectorSpace.zeroVector() );
      M* W = m_vectorSpace.newDiagMatrix( m_vectorSpace.zeroVector() );
      V  psi_j_t = m_vectorSpace.zeroVector();

      // Sum within the chain
      for( unsigned int t = initialPos; t < initialPos+numPos; ++t )
	{
	  psi_j_t = *(m_seq[t]);

	  work = psi_j_t - psi_j_dot;

	  (*W_local) += matrixProduct( work, work );
	}

      // Now do the sum over the chains
      // W will be available on all inter0 processors
      W_local->mpiSum( m_env.inter0Comm().Comm(), (*W) );

      (*W) = 1.0/(double(m)*(double(n)-1.0)) * (*W);

#if 0
      std::cout << "n, m = " << n << ", " << m << std::endl;
      std::cout << "W_local = " << *W_local << std::endl;
      std::cout << "W = " << *W << std::endl;
#endif

      // Need to delete pointers to temporary covariance matrices
      delete W_local;

      /* B/n = \frac{1}{m-1}\sum_{j=1}^m
	 (\overline{\psi_{j\cdot}} - \overline{\psi_{\cdot \cdot}})*
	 (\overline{\psi_{j\cdot}} - \overline{\psi_{\cdot \cdot}})^T
	 This corresponds to the "between-sequence" covariance matrix. */
      M* B_over_n_local = m_vectorSpace.newDiagMatrix( m_vectorSpace.zeroVector() );
      M* B_over_n = m_vectorSpace.newDiagMatrix( m_vectorSpace.zeroVector() );

      work = psi_j_dot - psi_dot_dot;
      (*B_over_n_local) = matrixProduct( work, work );

      B_over_n_local->mpiSum( m_env.inter0Comm().Comm(), (*B_over_n) );

      // Need to delete pointers to temporary covariance matrices
      delete B_over_n_local;

      (*B_over_n) = 1.0/(double(m)-1.0) * (*B_over_n); 

#if 0
      std::cout << "B_over_n = " << *B_over_n << std::endl;
#endif
      

      /* R_p = (n-1)/n + (m+1)/m * \lambda
	 \lambda = largest eigenvalue of W^{-1}*B/n */
      M* A = m_vectorSpace.newDiagMatrix( m_vectorSpace.zeroVector() );

      W->invertMultiply( *B_over_n, *A );

#if 0
      std::cout << "A = " << *A << std::endl;
      std::cout.flush();
#endif
      // Need to delete pointers to temporary covariance matrices
      delete W;
      delete B_over_n;

      double eigenValue;
      V eigenVector = m_vectorSpace.zeroVector(); 

      A->largestEigen( eigenValue, eigenVector );

      // Need to delete pointers to temporary covariance matrices
      delete A;

      // Now, finally compute the final convMeasure
      convMeasure = (double(n)-1.0)/double(n) + (double(m)+1.0)/double(m)*eigenValue;

    } // End of check on inter0Rank

  //TODO: Do we need a Barrier here?
  //TODO: Error checking on MPI.
  //m_env.fullComm().Barrier(); // Dangerous to barrier on fullComm ...

  return convMeasure;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subWriteContents(
  const std::string&            fileName,
  const std::string&            fileType,
  const std::set<unsigned int>& allowedSubEnvIds) const
{
  UQ_FATAL_TEST_MACRO(m_env.subRank() < 0,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subWriteContents(1)",
                      "unexpected subRank");

  uqFilePtrSetStruct filePtrSet;
  if (m_env.openOutputFile(fileName,
                           fileType,
                           allowedSubEnvIds,
                           false, // A 'true' causes problems when the user chooses (via options
                                  // in the input file) to use just one file for all outputs.
                           filePtrSet)) {
    this->subWriteContents(filePtrSet,fileType);
    m_env.closeFile(filePtrSet,fileType);
  }
  m_env.subComm().Barrier();

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subWriteContents(
  uqFilePtrSetStruct& filePtrSet,
  const std::string&  fileType) const // "m or hdf"
{
  UQ_FATAL_TEST_MACRO(filePtrSet.ofsVar == NULL,
                      m_env.worldRank(),
                      "uqSequenceOfVectorsClass<V,M>::subWriteContents(2)",
                      "filePtrSet.ofsVar should not be NULL");

  if (fileType == UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT) {
    this->subWriteContents(*filePtrSet.ofsVar,fileType);
  }
  else if (fileType == UQ_FILE_EXTENSION_FOR_HDF_FORMAT) {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqSequenceOfVectorsClass<V,M>::subWriteContents(2)",
                        "hdf file type not supported yet");
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqSequenceOfVectorsClass<V,M>::subWriteContents(2)",
                        "invalid file type");
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::subWriteContents(
  std::ofstream&     ofs,
  const std::string& fileType) const // "m or hdf"
{
  ofs << m_name << "_sub" << m_env.subIdString() << " = zeros(" << this->subSequenceSize()
      << ","                                                    << this->vectorSizeLocal()
      << ");"
      << std::endl;
  ofs << m_name << "_sub" << m_env.subIdString() << " = [";

  unsigned int chainSize = this->subSequenceSize();
  for (unsigned int j = 0; j < chainSize; ++j) {
    bool savedVectorPrintScientific = m_seq[j]->getPrintScientific();
    bool savedVectorPrintState      = m_seq[j]->getPrintHorizontally();
    m_seq[j]->setPrintScientific  (true);
    m_seq[j]->setPrintHorizontally(true);

    ofs << *(m_seq[j])
        << std::endl;

    m_seq[j]->setPrintHorizontally(savedVectorPrintState);
    m_seq[j]->setPrintScientific  (savedVectorPrintScientific);
  }
  ofs << "];\n";

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(
  const std::string& fileName,
  const std::string& fileType) const
{
  // All processors in 'fullComm' should call this routine...

  //m_env.fullComm().Barrier(); // Dangerous to barrier on fullComm ... // prudenci-2011-01-17
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
    *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::unifiedWriteContents()"
                            << ": worldRank "      << m_env.worldRank()
                            << ", fullRank "       << m_env.fullRank()
                            << ", subEnvironment " << m_env.subId()
                            << ", subRank "        << m_env.subRank()
                            << ", inter0Rank "     << m_env.inter0Rank()
                          //<< ", m_env.inter0Comm().NumProc() = " << m_env.inter0Comm().NumProc()
                            << ", fileName = "     << fileName
                            << std::endl;
  }

  if (m_env.inter0Rank() >= 0) {
    for (unsigned int r = 0; r < (unsigned int) m_env.inter0Comm().NumProc(); ++r) {
      if (m_env.inter0Rank() == (int) r) {
        // My turn
        if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
          *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::unifiedWriteContents()"
                                  << ": worldRank "      << m_env.worldRank()
                                  << ", fullRank "       << m_env.fullRank()
                                  << ", subEnvironment " << m_env.subId()
                                  << ", subRank "        << m_env.subRank()
                                  << ", inter0Rank "     << m_env.inter0Rank()
                                //<< ", m_env.inter0Comm().NumProc() = " << m_env.inter0Comm().NumProc()
                                  << ", fileName = "     << fileName
                                  << ", about to open file for r = " << r
                                  << std::endl;
        }

        // bool writeOver = (r == 0);
        bool writeOver = false; // A 'true' causes problems when the user chooses (via options
                                // in the input file) to use just one file for all outputs.
        uqFilePtrSetStruct unifiedFilePtrSet;
        if (m_env.openUnifiedOutputFile(fileName,
                                        fileType, // "m or hdf"
                                        writeOver,
                                        unifiedFilePtrSet)) {
          if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
            *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::unifiedWriteContents()"
                                    << ": worldRank "      << m_env.worldRank()
                                    << ", fullRank "       << m_env.fullRank()
                                    << ", subEnvironment " << m_env.subId()
                                    << ", subRank "        << m_env.subRank()
                                    << ", inter0Rank "     << m_env.inter0Rank()
                                  //<< ", m_env.inter0Comm().NumProc() = " << m_env.inter0Comm().NumProc()
                                    << ", fileName = "     << fileName
                                    << ", just opened file for r = " << r
                                    << std::endl;
          }

          unsigned int chainSize = this->subSequenceSize();
          if (fileType == UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT) {
            if (r == 0) {
              *unifiedFilePtrSet.ofsVar << m_name << "_unified" << " = zeros(" << this->subSequenceSize()*m_env.inter0Comm().NumProc()
                                        << ","                                 << this->vectorSizeLocal()
                                        << ");"
                                        << std::endl;
              *unifiedFilePtrSet.ofsVar << m_name << "_unified" << " = [";
            }

            for (unsigned int j = 0; j < chainSize; ++j) {
	      //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(): m_seq[" << j << "] = " << m_seq[j]
              //          << std::endl;
    	      //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(): &(m_seq[" << j << "].map()) = " << &(m_seq[j]->map())
              //          << std::endl;
              //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(): (m_seq[" << j << "].map().NumMyElements = " << m_seq[j]->map().NumMyElements()
              //          << std::endl;
              //V tmpVec(*(m_seq[j]));
	      //std::cout << "*(m_seq[" << j << "]) = " << tmpVec
              //          << std::endl;
	      //std::cout << "*(m_seq[" << j << "]) = " << *(m_seq[j])
              //          << std::endl;

              bool savedVectorPrintScientific = m_seq[j]->getPrintScientific();
              bool savedVectorPrintState      = m_seq[j]->getPrintHorizontally();
              m_seq[j]->setPrintScientific  (true);
              m_seq[j]->setPrintHorizontally(true);

              *unifiedFilePtrSet.ofsVar << *(m_seq[j])
                                        << std::endl;

              m_seq[j]->setPrintHorizontally(savedVectorPrintState);
              m_seq[j]->setPrintScientific  (savedVectorPrintScientific);
            }
          }
          else if (fileType == UQ_FILE_EXTENSION_FOR_HDF_FORMAT) {
            unsigned int numParams = m_vectorSpace.dimLocal();
            if (r == 0) {
              hid_t datatype = H5Tcopy(H5T_NATIVE_DOUBLE);
              //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(): h5 case, data type created" << std::endl;
              hsize_t dimsf[2];
              dimsf[0] = numParams;
              dimsf[1] = chainSize;
              hid_t dataspace = H5Screate_simple(2, dimsf, NULL); // HDF5_rank = 2
              //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(): h5 case, data space created" << std::endl;
              hid_t dataset = H5Dcreate2(unifiedFilePtrSet.h5Var,
                                         "seq_of_vectors",
                                         datatype,
                                         dataspace,
                                         H5P_DEFAULT,  // Link creation property list
                                         H5P_DEFAULT,  // Dataset creation property list
                                         H5P_DEFAULT); // Dataset access property list 
              //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(): h5 case, data set created" << std::endl;

              struct timeval timevalBegin;
              int iRC = UQ_OK_RC;
              iRC = gettimeofday(&timevalBegin,NULL);

              double* dataOut[numParams];
              dataOut[0] = (double*) malloc(numParams*chainSize*sizeof(double));
              for (unsigned int i = 1; i < numParams; ++i) { // Yes, from '1'
                dataOut[i] = dataOut[i-1] + chainSize; // Yes, just 'chainSize', not 'chainSize*sizeof(double)'
              }
              //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(): h5 case, memory allocated" << std::endl;
              for (unsigned int j = 0; j < chainSize; ++j) {
                V tmpVec(*(m_seq[j]));
                for (unsigned int i = 0; i < numParams; ++i) {
                  dataOut[i][j] = tmpVec[i];
                }
              }
              //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(): h5 case, memory filled" << std::endl;

              herr_t status;
              status = H5Dwrite(dataset,
                                H5T_NATIVE_DOUBLE,
                                H5S_ALL,
                                H5S_ALL,
                                H5P_DEFAULT,
                                (void*) dataOut[0]);
              //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(): h5 case, data written" << std::endl;

              double writeTime = uqMiscGetEllapsedSeconds(&timevalBegin);
              if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 2)) {
                *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::unifiedWriteContents()"
                                        << ": worldRank "      << m_env.worldRank()
                                        << ", fullRank "       << m_env.fullRank()
                                        << ", subEnvironment " << m_env.subId()
                                        << ", subRank "        << m_env.subRank()
                                        << ", inter0Rank "     << m_env.inter0Rank()
                                        << ", fileName = "     << fileName
                                        << ", numParams = "    << numParams
                                        << ", chainSize = "    << chainSize
                                        << ", writeTime = "    << writeTime << " seconds"
                                        << std::endl;
              }

              H5Dclose(dataset);
              //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(): h5 case, data set closed" << std::endl;
              H5Sclose(dataspace);
              //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(): h5 case, data space closed" << std::endl;
              H5Tclose(datatype);
              //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(): h5 case, data type closed" << std::endl;
              free(dataOut[0]);
            }
            else {
              UQ_FATAL_TEST_MACRO(true,
                                  m_env.worldRank(),
                                  "uqSequenceOfVectorsClass<V,M>::unifiedWriteContents()",
                                  "hdf file type not supported for multiple subenvironments yet");
            }
          }
          else {
            UQ_FATAL_TEST_MACRO(true,
                                m_env.worldRank(),
                                "uqSequenceOfVectorsClass<V,M>::unifiedWriteContents()",
                                "invalid file type");
          }

          if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
            *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::unifiedWriteContents()"
                                    << ": worldRank "      << m_env.worldRank()
                                    << ", fullRank "       << m_env.fullRank()
                                    << ", subEnvironment " << m_env.subId()
                                    << ", subRank "        << m_env.subRank()
                                    << ", inter0Rank "     << m_env.inter0Rank()
                                  //<< ", m_env.inter0Comm().NumProc() = " << m_env.inter0Comm().NumProc()
                                    << ", fileName = "     << fileName
                                    << ", about to close file for r = " << r
                                    << std::endl;
          }

          m_env.closeFile(unifiedFilePtrSet,fileType);

          if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
            *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::unifiedWriteContents()"
                                    << ": worldRank "      << m_env.worldRank()
                                    << ", fullRank "       << m_env.fullRank()
                                    << ", subEnvironment " << m_env.subId()
                                    << ", subRank "        << m_env.subRank()
                                    << ", inter0Rank "     << m_env.inter0Rank()
                                  //<< ", m_env.inter0Comm().NumProc() = " << m_env.inter0Comm().NumProc()
                                    << ", fileName = "     << fileName
                                    << ", just closed file for r = " << r
                                    << std::endl;
          }
        } // if (m_env.openUnifiedOutputFile())
      } // if (m_env.inter0Rank() == (int) r)
      m_env.inter0Comm().Barrier();
    } // for r

    if (m_env.inter0Rank() == 0) {
      if (fileType == UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT) {
        uqFilePtrSetStruct unifiedFilePtrSet;
        if (m_env.openUnifiedOutputFile(fileName,
                                        fileType,
                                        false, // Yes, 'writeOver = false' in order to close the array for matlab
                                        unifiedFilePtrSet)) {
          *unifiedFilePtrSet.ofsVar << "];\n";
          m_env.closeFile(unifiedFilePtrSet,fileType);
        }
      }
      else if (fileType == UQ_FILE_EXTENSION_FOR_HDF_FORMAT) {
        // Do nothing
      }
      else {
        UQ_FATAL_TEST_MACRO(true,
                            m_env.worldRank(),
                            "uqSequenceOfVectorsClass<V,M>::unifiedWriteContents(), final",
                            "invalid file type");
      }
    }
  } // if (m_env.inter0Rank() >= 0)

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
    *m_env.subDisplayFile() << "Leaving uqSequenceOfVectorsClass<V,M>::unifiedWriteContents()"
                            << ", fileName = " << fileName
                            << std::endl;
  }
  //m_env.fullComm().Barrier(); // Dangerous to barrier on fullComm ... // prudenci-2011-01-17

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::unifiedReadContents(
  const std::string& fileName,
  const std::string& fileType,
  const unsigned int subReadSize)
{
  //m_env.fullComm().Barrier(); // Dangerous to barrier on fullComm ...
  if (m_env.subDisplayFile()) {
    *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::unifiedReadContents()"
                            << ": worldRank "                      << m_env.worldRank()
                            << ", fullRank "                       << m_env.fullRank()
                            << ", subEnvironment "                 << m_env.subId()
                            << ", subRank "                        << m_env.subRank()
                            << ", inter0Rank "                     << m_env.inter0Rank()
      //<< ", m_env.inter0Comm().NumProc() = " << m_env.inter0Comm().NumProc()
                            << ", fileName = "                     << fileName
                            << ", subReadSize = "                  << subReadSize
      //<< ", unifiedReadSize = "              << unifiedReadSize
                            << std::endl;
  }

  this->resizeSequence(subReadSize);

  if (m_env.inter0Rank() >= 0) {
    double unifiedReadSize = subReadSize*m_env.inter0Comm().NumProc();

    // In the logic below, the id of a line' begins with value 0 (zero)
    unsigned int idOfMyFirstLine = 1 + m_env.inter0Rank()*subReadSize;
    unsigned int idOfMyLastLine = (1 + m_env.inter0Rank())*subReadSize;
    unsigned int numParams = this->vectorSizeLocal();

    for (unsigned int r = 0; r < (unsigned int) m_env.inter0Comm().NumProc(); ++r) { // "m or hdf"
      if (m_env.inter0Rank() == (int) r) {
        // My turn
        uqFilePtrSetStruct unifiedFilePtrSet;
        if (m_env.openUnifiedInputFile(fileName,
                                       fileType,
                                       unifiedFilePtrSet)) {
          if (fileType == UQ_FILE_EXTENSION_FOR_MATLAB_FORMAT) {
            if (r == 0) {
              // Read number of chain positions in the file by taking care of the first line,
              // which resembles something like 'variable_name = zeros(n_positions,m_params);'
	      std::string tmpString;

              // Read 'variable name' string
              *unifiedFilePtrSet.ifsVar >> tmpString;
	      //std::cout << "Just read '" << tmpString << "'" << std::endl;

              // Read '=' sign
              *unifiedFilePtrSet.ifsVar >> tmpString;
  	      //std::cout << "Just read '" << tmpString << "'" << std::endl;
              UQ_FATAL_TEST_MACRO(tmpString != "=",
                                  m_env.worldRank(),
                                  "uqSequenceOfVectorsClass<V,M>::unifiedReadContents()",
                                  "string should be the '=' sign");

              // Read 'zeros(n_positions,n_params)' string
              *unifiedFilePtrSet.ifsVar >> tmpString;
	      //std::cout << "Just read '" << tmpString << "'" << std::endl;
              unsigned int posInTmpString = 6;

              // Isolate 'n_positions' in a string
              char nPositionsString[tmpString.size()-posInTmpString+1];
              unsigned int posInPositionsString = 0;
              do {
                UQ_FATAL_TEST_MACRO(posInTmpString >= tmpString.size(),
                                    m_env.worldRank(),
                                    "uqSequenceOfVectorsClass<V,M>::unifiedReadContents()",
                                    "symbol ',' not found in first line of file");
                nPositionsString[posInPositionsString++] = tmpString[posInTmpString++];
              } while (tmpString[posInTmpString] != ',');
              nPositionsString[posInPositionsString] = '\0';

              // Isolate 'n_params' in a string
              posInTmpString++; // Avoid reading ',' char
              char nParamsString[tmpString.size()-posInTmpString+1];
              unsigned int posInParamsString = 0;
              do {
                UQ_FATAL_TEST_MACRO(posInTmpString >= tmpString.size(),
                                    m_env.worldRank(),
                                    "uqSequenceOfVectorsClass<V,M>::unifiedReadContents()",
                                    "symbol ')' not found in first line of file");
                nParamsString[posInParamsString++] = tmpString[posInTmpString++];
              } while (tmpString[posInTmpString] != ')');
              nParamsString[posInParamsString] = '\0';

              // Convert 'n_positions' and 'n_params' strings to numbers
              unsigned int sizeOfChainInFile = (unsigned int) strtod(nPositionsString,NULL);
              unsigned int numParamsInFile   = (unsigned int) strtod(nParamsString,   NULL);
              if (m_env.subDisplayFile()) {
                *m_env.subDisplayFile() << "In uqSequenceOfVectorsClass<V,M>::unifiedReadContents()"
                                        << ": worldRank "           << m_env.worldRank()
                                        << ", fullRank "            << m_env.fullRank()
                                        << ", sizeOfChainInFile = " << sizeOfChainInFile
                                        << ", numParamsInFile = "   << numParamsInFile
                                        << std::endl;
              }

              // Check if [size of chain in file] >= [requested unified sequence size]
              UQ_FATAL_TEST_MACRO(sizeOfChainInFile < unifiedReadSize,
                                  m_env.worldRank(),
                                  "uqSequenceOfVectorsClass<V,M>::unifiedReadContents()",
                                  "size of chain in file is not big enough");

              // Check if [num params in file] == [num params in current chain]
              UQ_FATAL_TEST_MACRO(numParamsInFile != numParams,
                                  m_env.worldRank(),
                                  "uqSequenceOfVectorsClass<V,M>::unifiedReadContents()",
                                  "number of parameters of chain in file is different than number of parameters in this chain object");
            } // if (r == 0)

            // Code common to any core in 'inter0Comm', including core of rank 0
            unsigned int maxCharsPerLine = 64*numParams; // Up to about 60 characters to represent each parameter value

            unsigned int lineId = 0;
            while (lineId < idOfMyFirstLine) {
              unifiedFilePtrSet.ifsVar->ignore(maxCharsPerLine,'\n');
              lineId++;
            };

            if (r == 0) {
              // Take care of initial part of the first data line,
              // which resembles something like 'variable_name = [value1 value2 ...'
	      std::string tmpString;

              // Read 'variable name' string
              *unifiedFilePtrSet.ifsVar >> tmpString;
  	      //std::cout << "Core 0 just read '" << tmpString << "'" << std::endl;

              // Read '=' sign
              *unifiedFilePtrSet.ifsVar >> tmpString;
	      //std::cout << "Core 0 just read '" << tmpString << "'" << std::endl;
              UQ_FATAL_TEST_MACRO(tmpString != "=",
                                  m_env.worldRank(),
                                  "uqSequenceOfVectorsClass<V,M>::unifiedReadContents()",
                                  "in core 0, string should be the '=' sign");

              // Take into account the ' [' portion
	      std::streampos tmpPos = unifiedFilePtrSet.ifsVar->tellg();
              unifiedFilePtrSet.ifsVar->seekg(tmpPos+(std::streampos)2);
            }

            V tmpVec(m_vectorSpace.zeroVector());
            while (lineId <= idOfMyLastLine) {
              for (unsigned int i = 0; i < numParams; ++i) {
                *unifiedFilePtrSet.ifsVar >> tmpVec[i];
              }
              this->setPositionValues(lineId - idOfMyFirstLine, tmpVec);
              lineId++;
            };
          }
          else if (fileType == UQ_FILE_EXTENSION_FOR_HDF_FORMAT) {
            if (r == 0) {
              hid_t dataset = H5Dopen2(unifiedFilePtrSet.h5Var,
                                       "seq_of_vectors",
                                       H5P_DEFAULT); // Dataset access property list 
              hid_t datatype  = H5Dget_type(dataset);
              H5T_class_t t_class = H5Tget_class(datatype);
              UQ_FATAL_TEST_MACRO(t_class != H5T_FLOAT,
                                  m_env.worldRank(),
                                  "uqSequenceOfVectorsClass<V,M>::unifiedReadContents()",
                                  "t_class is not H5T_DOUBLE");
              hid_t dataspace = H5Dget_space(dataset);
              int   rank      = H5Sget_simple_extent_ndims(dataspace);
              UQ_FATAL_TEST_MACRO(rank != 2,
                                  m_env.worldRank(),
                                  "uqSequenceOfVectorsClass<V,M>::unifiedReadContents()",
                                  "hdf rank is not 2");
              hsize_t dims_in[2];
              int     status_n;
              status_n  = H5Sget_simple_extent_dims(dataspace, dims_in, NULL);
	      //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedReadContents()"
              //          << ": dims_in[0] = " << dims_in[0]
              //          << ", dims_in[1] = " << dims_in[1]
              //          << std::endl;
              UQ_FATAL_TEST_MACRO(dims_in[0] != numParams,
                                  m_env.worldRank(),
                                  "uqSequenceOfVectorsClass<V,M>::unifiedReadContents()",
                                  "dims_in[0] is not equal to 'numParams'");
              UQ_FATAL_TEST_MACRO(dims_in[1] < subReadSize,
                                  m_env.worldRank(),
                                  "uqSequenceOfVectorsClass<V,M>::unifiedReadContents()",
                                  "dims_in[1] is smaller that requested 'subReadSize'");

              struct timeval timevalBegin;
              int iRC = UQ_OK_RC;
              iRC = gettimeofday(&timevalBegin,NULL);

              unsigned int chainSizeIn = (unsigned int) dims_in[1];
              double* dataIn[numParams];
              dataIn[0] = (double*) malloc(numParams*chainSizeIn*sizeof(double));
              for (unsigned int i = 1; i < numParams; ++i) { // Yes, from '1'
                dataIn[i] = dataIn[i-1] + chainSizeIn; // Yes, just 'chainSizeIn', not 'chainSizeIn*sizeof(double)'
              }
              //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedReadContents(): h5 case, memory allocated" << std::endl;
              herr_t status;
              status = H5Dread(dataset,
                               H5T_NATIVE_DOUBLE,
                               H5S_ALL,
                               dataspace,
                               H5P_DEFAULT,
                               dataIn[0]);
              //std::cout << "In uqSequenceOfVectorsClass<V,M>::unifiedReadContents(): h5 case, data read" << std::endl;
              V tmpVec(m_vectorSpace.zeroVector());
              for (unsigned int j = 0; j < subReadSize; ++j) { // Yes, 'subReadSize', not 'chainSizeIn'
                for (unsigned int i = 0; i < numParams; ++i) {
                  tmpVec[i] = dataIn[i][j];
                }
                this->setPositionValues(j, tmpVec);
              }

              double readTime = uqMiscGetEllapsedSeconds(&timevalBegin);
              if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 2)) {
                *m_env.subDisplayFile() << "Entering uqSequenceOfVectorsClass<V,M>::unifiedReadContents()"
                                        << ": worldRank "      << m_env.worldRank()
                                        << ", fullRank "       << m_env.fullRank()
                                        << ", subEnvironment " << m_env.subId()
                                        << ", subRank "        << m_env.subRank()
                                        << ", inter0Rank "     << m_env.inter0Rank()
                                        << ", fileName = "     << fileName
                                        << ", numParams = "    << numParams
                                        << ", chainSizeIn = "  << chainSizeIn
                                        << ", subReadSize = "  << subReadSize
                                        << ", readTime = "     << readTime << " seconds"
                                        << std::endl;
              }

              H5Sclose(dataspace);
              H5Tclose(datatype);
              H5Dclose(dataset);
              free(dataIn[0]);
            }
            else {
              UQ_FATAL_TEST_MACRO(true,
                                  m_env.worldRank(),
                                  "uqSequenceOfVectorsClass<V,M>::unifiedReadContents()",
                                  "hdf file type not supported for multiple subenvironments yet");
            }
          }
          else {
            UQ_FATAL_TEST_MACRO(true,
                                m_env.worldRank(),
                                "uqSequenceOfVectorsClass<V,M>::unifiedReadContents()",
                                "invalid file type");
          }
          m_env.closeFile(unifiedFilePtrSet,fileType);
        } // if (m_env.openUnifiedInputFile())
      } // if (m_env.inter0Rank() == (int) r)
      m_env.inter0Comm().Barrier();
    } // for r
  } // if (m_env.inter0Rank() >= 0)
  else {
    V tmpVec(m_vectorSpace.zeroVector());
    for (unsigned int i = 1; i < subReadSize; ++i) {
      this->setPositionValues(i,tmpVec);
    }
  }

  if (m_env.subDisplayFile()) {
    *m_env.subDisplayFile() << "Leaving uqSequenceOfVectorsClass<V,M>::unifiedReadContents()"
                            << ", fileName = " << fileName
                            << std::endl;
  }
  //m_env.fullComm().Barrier(); // Dangerous to barrier on fullComm ...

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::extractScalarSeq(
  unsigned int                   initialPos,
  unsigned int                   spacing,
  unsigned int                   numPos,
  unsigned int                   paramId,
  uqScalarSequenceClass<double>& scalarSeq) const
{
  scalarSeq.resizeSequence(numPos);
  if (spacing == 1) {
    for (unsigned int j = 0; j < numPos; ++j) {
      scalarSeq[j] = (*(m_seq[initialPos+j        ]))[paramId];
    }
  }
  else {
    for (unsigned int j = 0; j < numPos; ++j) {
      scalarSeq[j] = (*(m_seq[initialPos+j*spacing]))[paramId];
    }
  }

  return;
}

template <class V, class M>
void
uqSequenceOfVectorsClass<V,M>::extractRawData(
  unsigned int         initialPos,
  unsigned int         spacing,
  unsigned int         numPos,
  unsigned int         paramId,
  std::vector<double>& rawData) const
{
  rawData.resize(numPos);
  if (spacing == 1) {
    for (unsigned int j = 0; j < numPos; ++j) {
      rawData[j] = (*(m_seq[initialPos+j        ]))[paramId];
    }
  }
  else {
    for (unsigned int j = 0; j < numPos; ++j) {
      rawData[j] = (*(m_seq[initialPos+j*spacing]))[paramId];
    }
  }

  return;
}
#endif // __UQ_SEQUENCE_OF_VECTORS_H__
