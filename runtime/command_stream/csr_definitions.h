/*
 * Copyright (C) 2017-2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "core/helpers/pipeline_select_args.h"
#include "core/memory_manager/memory_constants.h"
#include "runtime/helpers/csr_deps.h"
#include "runtime/helpers/hw_info.h"
#include "runtime/helpers/properties_helper.h"
#include "runtime/kernel/grf_config.h"

#include <limits>

namespace NEO {
struct FlushStampTrackingObj;

namespace CSRequirements {
//cleanup section usually contains 1-2 pipeControls BB end and place for BB start
//that makes 16 * 2 + 4 + 8 = 40 bytes
//then command buffer is aligned to cacheline that can take up to 63 bytes
//to be sure everything fits minimal size is at 2 x cacheline.

constexpr auto minCommandQueueCommandStreamSize = 2 * MemoryConstants::cacheLineSize;
constexpr auto csOverfetchSize = MemoryConstants::pageSize;
} // namespace CSRequirements

namespace TimeoutControls {
constexpr int64_t maxTimeout = std::numeric_limits<int64_t>::max();
}

namespace QueueSliceCount {
constexpr uint64_t defaultSliceCount = 0;
}

namespace L3CachingSettings {
constexpr uint32_t l3CacheOn = 0u;
constexpr uint32_t l3CacheOff = 1u;
constexpr uint32_t l3AndL1On = 2u;
} // namespace L3CachingSettings

struct DispatchFlags {
    DispatchFlags() = delete;
    DispatchFlags(CsrDependencies csrDependencies, const TimestampPacketContainer *barrierTimestampPacketNodes, PipelineSelectArgs pipelineSelectArgs,
                  FlushStampTrackingObj *flushStampReference, QueueThrottle throttle, PreemptionMode preemptionMode, uint32_t numGrfRequired,
                  uint32_t l3CacheSettings, uint64_t sliceCount, bool blocking, bool dcFlush,
                  bool useSLM, bool guardCommandBufferWithPipeControl, bool gsba32BitRequired,
                  bool requiresCoherency, bool lowPriority, bool implicitFlush,
                  bool outOfOrderExecutionAllowed, bool multiEngineQueue, bool epilogueRequired) : csrDependencies(csrDependencies),
                                                                                                   barrierTimestampPacketNodes(barrierTimestampPacketNodes),
                                                                                                   pipelineSelectArgs(pipelineSelectArgs),
                                                                                                   flushStampReference(flushStampReference),
                                                                                                   throttle(throttle),
                                                                                                   preemptionMode(preemptionMode),
                                                                                                   numGrfRequired(numGrfRequired),
                                                                                                   l3CacheSettings(l3CacheSettings),
                                                                                                   sliceCount(sliceCount),
                                                                                                   blocking(blocking),
                                                                                                   dcFlush(dcFlush),
                                                                                                   useSLM(useSLM),
                                                                                                   guardCommandBufferWithPipeControl(guardCommandBufferWithPipeControl),
                                                                                                   gsba32BitRequired(gsba32BitRequired),
                                                                                                   requiresCoherency(requiresCoherency),
                                                                                                   lowPriority(lowPriority),
                                                                                                   implicitFlush(implicitFlush),
                                                                                                   outOfOrderExecutionAllowed(outOfOrderExecutionAllowed),
                                                                                                   multiEngineQueue(multiEngineQueue),
                                                                                                   epilogueRequired(epilogueRequired){};
    CsrDependencies csrDependencies;
    const TimestampPacketContainer *barrierTimestampPacketNodes = nullptr;
    PipelineSelectArgs pipelineSelectArgs;
    FlushStampTrackingObj *flushStampReference = nullptr;
    QueueThrottle throttle = QueueThrottle::MEDIUM;
    PreemptionMode preemptionMode = PreemptionMode::Disabled;
    uint32_t numGrfRequired = GrfConfig::DefaultGrfNumber;
    uint32_t l3CacheSettings = L3CachingSettings::l3CacheOn;
    uint64_t sliceCount = QueueSliceCount::defaultSliceCount;
    bool blocking = false;
    bool dcFlush = false;
    bool useSLM = false;
    bool guardCommandBufferWithPipeControl = false;
    bool gsba32BitRequired = false;
    bool requiresCoherency = false;
    bool lowPriority = false;
    bool implicitFlush = false;
    bool outOfOrderExecutionAllowed = false;
    bool multiEngineQueue = false;
    bool epilogueRequired = false;
};

struct CsrSizeRequestFlags {
    bool l3ConfigChanged = false;
    bool coherencyRequestChanged = false;
    bool preemptionRequestChanged = false;
    bool mediaSamplerConfigChanged = false;
    bool hasSharedHandles = false;
    bool numGrfRequiredChanged = false;
    bool specialPipelineSelectModeChanged = false;
};
} // namespace NEO
