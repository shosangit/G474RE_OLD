/**
  ******************************************************************************
  * @file    network2.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Fri Sep 24 13:49:31 2021
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "network2.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"




#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network2
 
#undef AI_NETWORK2_MODEL_SIGNATURE
#define AI_NETWORK2_MODEL_SIGNATURE     "c8c027571ecb82123a1c30381a4e2cae"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Fri Sep 24 13:49:31 2021"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK2_N_BATCHES
#define AI_NETWORK2_N_BATCHES         (1)




/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  dense_input_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 12, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  dense_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 32, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  dense_1_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  nl_2_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  dense_3_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 32, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  nl_4_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 32, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  dense_5_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  nl_6_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 2, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  dense_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 384, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  dense_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 32, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  dense_1_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2048, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  dense_1_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  dense_3_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2048, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  dense_3_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 32, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  dense_5_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  dense_5_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 2, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_input_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921452909708023f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_0_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.05236427113413811f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_1_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.07347195595502853f),
    AI_PACK_INTQ_ZP(-23)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_2_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_3_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.040670014917850494f),
    AI_PACK_INTQ_ZP(-6)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_4_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_5_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08786188811063766f),
    AI_PACK_INTQ_ZP(47)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_6_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_0_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.02890017069876194f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_0_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00011333065776852891f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_1_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004915301688015461f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_1_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0002573861856944859f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_3_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.009759824723005295f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_3_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(3.812431532423943e-05f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_5_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.008493478409945965f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_5_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(3.3177650038851425e-05f),
    AI_PACK_INTQ_ZP(0)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  dense_input_output, AI_STATIC,
  0, 0x1,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 1, 1, 12, 12),
  1, &dense_input_output_array, &dense_input_output_intq)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  dense_0_output, AI_STATIC,
  1, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 1, 1, 32, 32),
  1, &dense_0_output_array, &dense_0_output_intq)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  dense_1_output, AI_STATIC,
  2, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &dense_1_output_array, &dense_1_output_intq)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  nl_2_output, AI_STATIC,
  3, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &nl_2_output_array, &nl_2_output_intq)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  dense_3_output, AI_STATIC,
  4, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 1, 1, 32, 32),
  1, &dense_3_output_array, &dense_3_output_intq)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  nl_4_output, AI_STATIC,
  5, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 1, 1, 32, 32),
  1, &nl_4_output_array, &nl_4_output_intq)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  dense_5_output, AI_STATIC,
  6, 0x1,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 1, 1, 2, 2),
  1, &dense_5_output_array, &dense_5_output_intq)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  nl_6_output, AI_STATIC,
  7, 0x1,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 1, 1, 2, 2),
  1, &nl_6_output_array, &nl_6_output_intq)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  dense_0_weights, AI_STATIC,
  8, 0x1,
  AI_SHAPE_INIT(4, 12, 32, 1, 1), AI_STRIDE_INIT(4, 1, 12, 384, 384),
  1, &dense_0_weights_array, &dense_0_weights_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  dense_0_bias, AI_STATIC,
  9, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &dense_0_bias_array, &dense_0_bias_intq)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  dense_1_weights, AI_STATIC,
  10, 0x1,
  AI_SHAPE_INIT(4, 32, 64, 1, 1), AI_STRIDE_INIT(4, 1, 32, 2048, 2048),
  1, &dense_1_weights_array, &dense_1_weights_intq)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  dense_1_bias, AI_STATIC,
  11, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_1_bias_array, &dense_1_bias_intq)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  dense_3_weights, AI_STATIC,
  12, 0x1,
  AI_SHAPE_INIT(4, 64, 32, 1, 1), AI_STRIDE_INIT(4, 1, 64, 2048, 2048),
  1, &dense_3_weights_array, &dense_3_weights_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  dense_3_bias, AI_STATIC,
  13, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &dense_3_bias_array, &dense_3_bias_intq)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  dense_5_weights, AI_STATIC,
  14, 0x1,
  AI_SHAPE_INIT(4, 32, 2, 1, 1), AI_STRIDE_INIT(4, 1, 32, 64, 64),
  1, &dense_5_weights_array, &dense_5_weights_intq)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  dense_5_bias, AI_STATIC,
  15, 0x1,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &dense_5_bias_array, &dense_5_bias_intq)



/**  Layer declarations section  **********************************************/



AI_STATIC_CONST ai_i8 nl_6_nl_params_data[] = { -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -126, -126, -126, -126, -126, -126, -125, -125, -125, -125, -124, -124, -124, -123, -123, -122, -122, -121, -121, -120, -119, -118, -118, -117, -116, -115, -113, -112, -111, -109, -108, -106, -104, -102, -100, -98, -96, -93, -90, -87, -84, -81, -78, -74, -70, -66, -62, -57, -53, -48, -43, -38, -33, -28, -22, -17, -11, -6, 0, 6, 11, 17, 22, 28, 33, 38, 43, 48, 53, 57, 62, 66, 70, 74, 78, 81, 84, 87, 90, 93, 96, 98, 100, 102, 104, 106, 108, 109, 111, 112, 113, 115, 116, 117, 118, 118, 119, 120, 121, 121, 122, 122, 123, 123, 124, 124, 124, 125, 125, 125, 125, 126, 126, 126, 126, 126, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
AI_ARRAY_OBJ_DECLARE(
    nl_6_nl_params, AI_ARRAY_FORMAT_S8,
    nl_6_nl_params_data, nl_6_nl_params_data, 256, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_6_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_6_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_6_layer, 6,
  NL_TYPE, 0x0, NULL,
  nl, forward_nl_integer,
  &nl_6_chain,
  NULL, &nl_6_layer, AI_STATIC, 
  .nl_params = &nl_6_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_5_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_5_weights, &dense_5_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_5_layer, 5,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA,
  &dense_5_chain,
  NULL, &nl_6_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_i8 nl_4_nl_params_data[] = { -126, -126, -126, -126, -126, -126, -126, -126, -126, -125, -125, -125, -125, -125, -125, -125, -125, -124, -124, -124, -124, -124, -124, -124, -123, -123, -123, -123, -123, -122, -122, -122, -122, -121, -121, -121, -120, -120, -120, -120, -119, -119, -118, -118, -118, -117, -117, -116, -116, -115, -115, -114, -114, -113, -113, -112, -112, -111, -110, -110, -109, -108, -107, -107, -106, -105, -104, -103, -102, -101, -100, -99, -98, -97, -96, -95, -94, -93, -91, -90, -89, -87, -86, -84, -83, -81, -80, -78, -77, -75, -73, -71, -70, -68, -66, -64, -62, -60, -58, -56, -54, -52, -49, -47, -45, -43, -40, -38, -35, -33, -31, -28, -26, -23, -21, -18, -16, -13, -10, -8, -5, -3, 0, 3, 5, 8, 10, 13, 16, 18, 21, 23, 26, 28, 31, 33, 35, 38, 40, 43, 45, 47, 49, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 71, 73, 75, 77, 78, 80, 81, 83, 84, 86, 87, 89, 90, 91, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 107, 108, 109, 110, 110, 111, 112, 112, 113, 113, 114, 114, 115, 115, 116, 116, 117, 117, 118, 118, 118, 119, 119, 120, 120, 120, 120, 121, 121, 121, 122, 122, 122, 122, 123, 123, 123, 123, 123, 124, 124, 124, 124, 124, 124, 124, 125, 125, 125, 125, 125, 125, 125, 125, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 127, 127, 127, 127, 127, 127, 127 };
AI_ARRAY_OBJ_DECLARE(
    nl_4_nl_params, AI_ARRAY_FORMAT_S8,
    nl_4_nl_params_data, nl_4_nl_params_data, 256, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_4_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_4_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_4_layer, 4,
  NL_TYPE, 0x0, NULL,
  nl, forward_nl_integer,
  &nl_4_chain,
  NULL, &dense_5_layer, AI_STATIC, 
  .nl_params = &nl_4_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_3_weights, &dense_3_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_3_layer, 3,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA,
  &dense_3_chain,
  NULL, &nl_4_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_i8 nl_2_nl_params_data[] = { -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -126, -126, -126, -126, -126, -126, -126, -125, -125, -125, -125, -124, -124, -124, -124, -123, -123, -123, -122, -122, -121, -121, -120, -120, -119, -118, -118, -117, -116, -115, -114, -113, -112, -111, -110, -109, -107, -106, -104, -103, -101, -99, -97, -95, -93, -91, -88, -86, -83, -80, -77, -74, -71, -68, -64, -61, -57, -53, -49, -45, -41, -37, -32, -28, -23, -19, -14, -9, -5, 0, 5, 9, 14, 19, 23, 28, 32, 37, 41, 45, 49, 53, 57, 61, 64, 68, 71, 74, 77, 80, 83, 86, 88, 91, 93, 95, 97, 99, 101, 103, 104, 106, 107, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 118, 119, 120, 120, 121, 121, 122, 122, 123, 123, 123, 124, 124, 124, 124, 125, 125, 125, 125, 126, 126, 126, 126, 126, 126, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
AI_ARRAY_OBJ_DECLARE(
    nl_2_nl_params, AI_ARRAY_FORMAT_S8,
    nl_2_nl_params_data, nl_2_nl_params_data, 256, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_2_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_2_layer, 2,
  NL_TYPE, 0x0, NULL,
  nl, forward_nl_integer,
  &nl_2_chain,
  NULL, &dense_3_layer, AI_STATIC, 
  .nl_params = &nl_2_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_1_weights, &dense_1_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_1_layer, 1,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA,
  &dense_1_chain,
  NULL, &nl_2_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_0_weights, &dense_0_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_0_layer, 0,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA,
  &dense_0_chain,
  NULL, &dense_1_layer, AI_STATIC, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 5064, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 96, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK2_IN_NUM, &dense_input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK2_OUT_NUM, &nl_6_output),
  &dense_0_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool network2_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)
  AI_UNUSED(net_ctx)

  ai_ptr activations_map[1] = AI_C_ARRAY_INIT;

  if (ai_platform_get_activations_map(activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    dense_input_output_array.data = AI_PTR(NULL);
    dense_input_output_array.data_start = AI_PTR(NULL);
    dense_0_output_array.data = AI_PTR(activations_map[0] + 0);
    dense_0_output_array.data_start = AI_PTR(activations_map[0] + 0);
    dense_1_output_array.data = AI_PTR(activations_map[0] + 32);
    dense_1_output_array.data_start = AI_PTR(activations_map[0] + 32);
    nl_2_output_array.data = AI_PTR(activations_map[0] + 32);
    nl_2_output_array.data_start = AI_PTR(activations_map[0] + 32);
    dense_3_output_array.data = AI_PTR(activations_map[0] + 0);
    dense_3_output_array.data_start = AI_PTR(activations_map[0] + 0);
    nl_4_output_array.data = AI_PTR(activations_map[0] + 32);
    nl_4_output_array.data_start = AI_PTR(activations_map[0] + 32);
    dense_5_output_array.data = AI_PTR(activations_map[0] + 0);
    dense_5_output_array.data_start = AI_PTR(activations_map[0] + 0);
    nl_6_output_array.data = AI_PTR(NULL);
    nl_6_output_array.data_start = AI_PTR(NULL);
    
    return true;
  }
  return false;
}



AI_DECLARE_STATIC
ai_bool network2_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)
  AI_UNUSED(net_ctx)

  ai_ptr weights_map[1] = AI_C_ARRAY_INIT;

  if (ai_platform_get_weights_map(weights_map, 1, params)) {
    /* Updating weights with array addresses */
    
    dense_0_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_0_weights_array.data = AI_PTR(weights_map[0] + 0);
    dense_0_weights_array.data_start = AI_PTR(weights_map[0] + 0);
    dense_0_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_0_bias_array.data = AI_PTR(weights_map[0] + 384);
    dense_0_bias_array.data_start = AI_PTR(weights_map[0] + 384);
    dense_1_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_1_weights_array.data = AI_PTR(weights_map[0] + 512);
    dense_1_weights_array.data_start = AI_PTR(weights_map[0] + 512);
    dense_1_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_1_bias_array.data = AI_PTR(weights_map[0] + 2560);
    dense_1_bias_array.data_start = AI_PTR(weights_map[0] + 2560);
    dense_3_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_3_weights_array.data = AI_PTR(weights_map[0] + 2816);
    dense_3_weights_array.data_start = AI_PTR(weights_map[0] + 2816);
    dense_3_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_3_bias_array.data = AI_PTR(weights_map[0] + 4864);
    dense_3_bias_array.data_start = AI_PTR(weights_map[0] + 4864);
    dense_5_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_5_weights_array.data = AI_PTR(weights_map[0] + 4992);
    dense_5_weights_array.data_start = AI_PTR(weights_map[0] + 4992);
    dense_5_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_5_bias_array.data = AI_PTR(weights_map[0] + 5056);
    dense_5_bias_array.data_start = AI_PTR(weights_map[0] + 5056);
    return true;
  }
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/
AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_network2_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK2_MODEL_NAME,
      .model_signature   = AI_NETWORK2_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 4772,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_bool ai_network2_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK2_MODEL_NAME,
      .model_signature   = AI_NETWORK2_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 4772,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_network2_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network2_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network2_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network2_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= network2_configure_weights(net_ctx, params);
  ok &= network2_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network2_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network2_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_NETWORK2_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

