/**
 * @file  tpm2_info_tools.h
 *
 * @brief Provides TPM 2.0 "information"
 *        (e.g., data retrieval, formatting, display)
 *        utility functions for Kmyth.
 */

#ifndef TPM2_INFO_TOOLS_H
#define TPM2_INFO_TOOLS_H

#include <stdbool.h>
#include <tss2/tss2_sys.h>

/**
 * @brief Get specified TPM 2.0 property value(s).
 *
 * @param[in]  sapi_ctx       System API (SAPI) context, must be initialized -
 *                            passed in as a pointer to the context struct
 *
 * @param[in]  capability     "Capability category" value to use for query
 *
 * @param[in]  property       "Property group" value to use for query
 *
 * @param[in]  propertyCount  "Property count" value to use as max for query
 *
 * @param[out] capabilityData "Capability data" structure to hold retrieved
 *                            property values
 *
 * @return 0 if success, 1 if error
 */
int tpm2_get_properties(TSS2_SYS_CONTEXT * sapi_ctx,
                        uint32_t capability,
                        uint32_t property, uint32_t propertyCount,
                        TPMS_CAPABILITY_DATA * capabilityData);

/**
 * @brief Determine whether TPM 2.0 implementation is hardware or emulator.
 *
 * @param[in]  sapi_ctx   System API (SAPI) context, must be initialized -
 *                        passed in as a pointer to the context struct
 *
 * @param[out] isEmulator Boolean flag to hold result:
 *                        <UL>
 *                          <LI> true = emulator </LI>
 *                          <LI> false = hardware </LI>
 *                        </UL>
 *
 * @return 0 if success, 1 if error
 */
int tpm2_get_impl_type(TSS2_SYS_CONTEXT * sapi_ctx, bool *isEmulator);

/**
 * There are a number of fixed TPM properties (tagged properties)
 * that are returned as 32-bit integers into which up to four 8-byte
 * characters have been packed (four concatenated bytes that can be
 * interpreted as a string of up to four ASCII characters). This 
 * utility function can be used to recover the string representation.
 * 
 * @param[in]  uint_value 32-bit unsigned integer input value
 * 
 * @param[out] str_repr   String representation output -
 *                        passed as pointer to the string
 */
void tpm2_unpack_uint32_to_str(uint32_t uint_value, char **str_repr);

/**
 * @brief Translates error string from hex into human readable.
 *
 * Got translations from comments in:
 * <UL>
 *   <LI> tpm2-tss-2.0.1/include/tss2/tss2_common.h </LI>
 *   <LI> tpm2-tss-2.0.1/include/tss2/tss2_tpm2_types.h </LI>
 *   <LI> tpm2-abrmd-2.0.2 source files </LI>
 * </UL>
 *
 * @param[in]  err - TPM 2.0 error code (return value)
 *
 * @return String containing human readable error message
 *         mapped to input response code
 */
const char *tpm2_getErrorString(TSS2_RC err);

#endif /* TPM2_INFO_TOOLS_H */
