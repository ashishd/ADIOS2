/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * CompressZFP.h : wrapper to ZFP compression library
 * https://computation.llnl.gov/projects/floating-point-compression
 *
 *  Created on: Jul 25, 2017
 *      Author: William F Godoy godoywf@ornl.gov
 */

#ifndef ADIOS2_TRANSFORM_COMPRESS_COMPRESSZFP_H_
#define ADIOS2_TRANSFORM_COMPRESS_COMPRESSZFP_H_

extern "C" {
#include <zfp.h>
}

#include "adios2/core/Operator.h"

namespace adios2
{
namespace core
{
namespace compress
{

class CompressZFP : public Operator
{

public:
    /**
     * Unique constructor
     */
    CompressZFP(const Params &parameters);

    ~CompressZFP() = default;

    /**
     * Wrapper around zfp compression
     * @param dataIn
     * @param dimensions
     * @param type
     * @param bufferOut
     * @param parameters
     * @return size of compressed buffer in bytes
     */
    size_t Compress(const char *dataIn, const Dims &blockStart,
                    const Dims &blockCount, DataType type, char *bufferOut,
                    const Params &parameters, Params &info) final;

    /**
     * Wrapper around zfp decompression
     * @param bufferIn
     * @param sizeIn
     * @param dataOut
     * @param dimensions
     * @param type
     * @return size of decompressed data in dataOut
     */
    size_t Decompress(const char *bufferIn, const size_t sizeIn, char *dataOut,
                      const DataType type, const Dims &blockStart,
                      const Dims &blockCount, const Params &parameters,
                      Params &info) final;

    bool IsDataTypeValid(const DataType type) const final;

private:
    /**
     * Returns Zfp supported zfp_type based on adios string type
     * @param type adios type as string, see GetDataType<T> in
     * helper/adiosType.inl
     * @return zfp_type
     */
    zfp_type GetZfpType(DataType type) const;

    /**
     * Constructor Zfp zfp_field based on input information around the data
     * pointer
     * @param data
     * @param shape
     * @param type
     * @return zfp_field*
     */
    zfp_field *GetZFPField(const char *data, const Dims &shape,
                           DataType type) const;

    zfp_stream *GetZFPStream(const Dims &dimensions, DataType type,
                             const Params &parameters) const;

    /**
     * check status from BZip compression and decompression functions
     * @param status returned by BZip2 library
     * @param hint extra exception information
     */
    void CheckStatus(const int status, const std::string hint) const;
};

} // end namespace compress
} // end namespace core
} // end namespace adios2

#endif /* ADIOS2_TRANSFORM_COMPRESS_COMPRESSZFP_H_ */
