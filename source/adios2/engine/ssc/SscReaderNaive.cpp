/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * SscReaderNaive.cpp
 *
 *  Created on: Mar 7, 2022
 *      Author: Jason Wang
 */

#include "SscReaderNaive.tcc"

namespace adios2
{
namespace core
{
namespace engine
{
namespace ssc
{

SscReaderNaive::SscReaderNaive(IO &io, const std::string &name, const Mode mode,
                               MPI_Comm comm)
: SscReaderBase(io, name, mode, comm)
{
}

StepStatus SscReaderNaive::BeginStep(const StepMode stepMode,
                                     const float timeoutSeconds,
                                     const bool readerLocked)
{

    ++m_CurrentStep;

    return StepStatus::OK;
}

size_t SscReaderNaive::CurrentStep() { return m_CurrentStep; }

void SscReaderNaive::EndStep(const bool readerLocked) {}

void SscReaderNaive::PerformGets() {}

void SscReaderNaive::Close(const int transportIndex) {}

#define declare_type(T)                                                        \
    void SscReaderNaive::GetDeferred(Variable<T> &variable, T *data)           \
    {                                                                          \
        helper::Log("Engine", "SSCReader", "GetDeferred", variable.m_Name, 0,  \
                    m_ReaderRank, 5, m_Verbosity, helper::LogMode::INFO);      \
        GetDeferredCommon(variable, data);                                     \
    }                                                                          \
    std::vector<typename Variable<T>::BPInfo> SscReaderNaive::BlocksInfo(      \
        const Variable<T> &variable, const size_t step) const                  \
    {                                                                          \
        return BlocksInfoCommon(variable, step);                               \
    }
ADIOS2_FOREACH_STDTYPE_1ARG(declare_type)
#undef declare_type

}
}
}
}
