/*
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "unit_tests/gen12lp/special_ult_helper_gen12lp.h"

#include "runtime/helpers/hw_info.h"

namespace NEO {

bool SpecialUltHelperGen12lp::shouldEnableHdcFlush(PRODUCT_FAMILY productFamily) {
    return true;
}

bool SpecialUltHelperGen12lp::additionalCoherencyCheck(PRODUCT_FAMILY productFamily, bool coherency) {
    return false;
}

bool SpecialUltHelperGen12lp::shouldPerformimagePitchAlignment(PRODUCT_FAMILY productFamily) {
    return true;
}

bool SpecialUltHelperGen12lp::shouldTestDefaultImplementationOfSetupHardwareCapabilities(PRODUCT_FAMILY productFamily) {
    return true;
}

bool SpecialUltHelperGen12lp::isPipeControlWArequired(PRODUCT_FAMILY productFamily) {
    return true;
}

} // namespace NEO
