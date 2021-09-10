
#ifdef __cplusplus
 extern "C" {
#endif
/**
  ******************************************************************************
  * @file           : app_x-cube-ai.c
  * @brief          : AI program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
 /*
  * Description
  *   v1.0 - Minimum template to show how to use the Embedded Client API
  *          model. Only one input and one output is supported. All
  *          memory resources are allocated statically (AI_NETWORK_XX, defines
  *          are used).
  *          Re-target of the printf function is out-of-scope.
  *
  *   For more information, see the embeded documentation:
  *
  *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
  *
  *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
  *   typical : C:\Users\<user_name>\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\6.0.0
  */
/* Includes ------------------------------------------------------------------*/
/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "app_x-cube-ai.h"
#include "main.h"
#include "ai_datatypes_defines.h"

/* USER CODE BEGIN includes */
#include "MPU6050.h"
#include "math.h"
#include "stdint.h"
#include "ai_platform.h"
#include "main.h"
#include "BC20.h"

float ai_out[2];
float in_data[12];
float out_data[2];
float aiwindow_Ax[2000];
float aiwindow_Ay[2000];
float aiwindow_Az[2000];
float aiwindow_APitch[2000];
float aiwindow_Gx[2000];
float aiwindow_Gy[2000];
float aiwindow_Gz[2000];
float aiwindow_GPitch[2000];
uint8_t ti=0;
int text=2000;
float JV = 0.93;
float max_Ax, max_Ay, max_Az, max_Apitch, var_Apitch, mean_Apitch;
float max_Gx, max_Gy, max_Gz, max_Gpitch, var_Gpitch, mean_Gpitch;
extern MPU6050_t MPU6050;
extern uint8_t BC20flag;
/* USER CODE END includes */
/* Global AI objects */
static ai_handle network2 = AI_HANDLE_NULL;
static ai_network_report network2_info;

/* Global c-array to handle the activations buffer */
AI_ALIGNED(4)
static ai_u8 activations[AI_NETWORK2_DATA_ACTIVATIONS_SIZE];

/*  In the case where "--allocate-inputs" option is used, memory buffer can be
 *  used from the activations buffer. This is not mandatory.
 */
#if !defined(AI_NETWORK2_INPUTS_IN_ACTIVATIONS)
/* Allocate data payload for input tensor */
AI_ALIGNED(4)
static ai_u8 in_data_s[AI_NETWORK2_IN_1_SIZE_BYTES];
#endif

/*  In the case where "--allocate-outputs" option is used, memory buffer can be
 *  used from the activations buffer. This is no mandatory.
 */
#if !defined(AI_NETWORK2_OUTPUTS_IN_ACTIVATIONS)
/* Allocate data payload for the output tensor */
AI_ALIGNED(4)
static ai_u8 out_data_s[AI_NETWORK2_OUT_1_SIZE_BYTES];
#endif

static void ai_log_err(const ai_error err, const char *fct)
{
  /* USER CODE BEGIN log */
    if (fct)
        printf("TEMPLATE - Error (%s) - type=0x%02x code=0x%02x\r\n", fct,
               err.type, err.code);
    else
        printf("TEMPLATE - Error - type=0x%02x code=0x%02x\r\n", err.type, err.code);

    do {} while (1);
  /* USER CODE END log */
}

static int ai_boostrap(ai_handle w_addr, ai_handle act_addr)
{
  ai_error err;

  /* 1 - Create an instance of the model */
  err = ai_network2_create(&network2, AI_NETWORK2_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    ai_log_err(err, "ai_network2_create");
    return -1;
  }

  /* 2 - Initialize the instance */
  const ai_network_params params = AI_NETWORK_PARAMS_INIT(
      AI_NETWORK2_DATA_WEIGHTS(w_addr),
      AI_NETWORK2_DATA_ACTIVATIONS(act_addr) );

  if (!ai_network2_init(network2, &params)) {
      err = ai_network2_get_error(network2);
      ai_log_err(err, "ai_network2_init");
      return -1;
    }

  /* 3 - Retrieve the network info of the created instance */
  if (!ai_network2_get_info(network2, &network2_info)) {
    err = ai_network2_get_error(network2);
    ai_log_err(err, "ai_network2_get_error");
    ai_network2_destroy(network2);
    network2 = AI_HANDLE_NULL;
    return -3;
  }

  return 0;
}

static int ai_run(void *data_in, void *data_out)
{
  ai_i32 batch;

  ai_buffer *ai_input = network2_info.inputs;
  ai_buffer *ai_output = network2_info.outputs;

  ai_input[0].data = AI_HANDLE_PTR(data_in);
  ai_output[0].data = AI_HANDLE_PTR(data_out);

  batch = ai_network2_run(network2, ai_input, ai_output);
  if (batch != 1) {
    ai_log_err(ai_network2_get_error(network2),
        "ai_network2_run");
    return -1;
  }

  return 0;
}

/* USER CODE BEGIN 2 */

float mean(float a[])
{

    float ave = 0;
    int i = 1999;
    float num = 0;
    while (i + 1)
    {
        num = num + a[i];
        i--;
    }
    ave = num / 2000;
    return ave;
}

float max(float a[])
{
    int i = 1999;
    float m = a[1999];
    while (i + 1)
    {
        if (a[i - 1] > a[i])
        {
            m = a[i - 1];
        }
        i--;
    }
    return m;
}

float var(float ave, float a[])
{
    int i = 1999;
    uint32_t num = 0, va;
    while (i + 1)
    {
        num = num + pow(a[i] - ave, 2);
        i--;
    }
    va = num / 2000;
    return va;
}


int acquire_and_process_data(void * data)
{

    return 0;
}

int post_process(void * data)
{
    return 0;
}
/* USER CODE END 2 */

/*************************************************************************
  *
  */
void MX_X_CUBE_AI_Init(void)
{
    /* USER CODE BEGIN 5 */
    printf("\r\nTEMPLATE - initialization\r\n");

    ai_boostrap(ai_network2_data_weights_get(), activations);
    /* USER CODE END 5 */
}

void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 6 */

    mean_Apitch = mean(aiwindow_APitch);
    max_Ax = max(aiwindow_Ax);
    max_Ay = max(aiwindow_Ay);
    max_Az = max(aiwindow_Az);
    max_Apitch = max(aiwindow_APitch);
    var_Apitch = var(mean_Apitch, aiwindow_APitch);
    mean_Gpitch = mean(aiwindow_GPitch);
    max_Gx = max(aiwindow_Gx);
    max_Gy = max(aiwindow_Gy);
    max_Gz = max(aiwindow_Gz);
    max_Gpitch = max(aiwindow_GPitch);
    var_Gpitch = var(mean_Gpitch, aiwindow_GPitch);

    in_data[0] = max_Ax;
    in_data[1] = max_Ay;
    in_data[2] = max_Az;
    in_data[3] = max_Apitch;
    in_data[4] = var_Apitch;
    in_data[5] = mean_Apitch;
    in_data[6] = max_Gx;
    in_data[7] = max_Gy;
    in_data[8] = max_Gz;
    in_data[9] = max_Gpitch;
    in_data[10] = var_Gpitch;
    in_data[11] = mean_Gpitch;

    /* 1 - Create the AI buffer IO handlers */
    ai_buffer ai_input[AI_NETWORK2_IN_NUM] = AI_NETWORK2_IN;
    ai_buffer ai_output[AI_NETWORK2_OUT_NUM] = AI_NETWORK2_OUT;

    /* 2 - Initialize input/output buffer handlers */
    ai_input[0].n_batches = 1;
    ai_input[0].data = AI_HANDLE_PTR(in_data);
    ai_output[0].n_batches = 1;
    ai_output[0].data = AI_HANDLE_PTR(out_data);

    /* 3 - Perform the inference */
    ai_network2_run(network2, &ai_input[0], &ai_output[0]);

    /* Output results *********************************************************/
    //    printf("Inference output..\n");

    ai_out[0] = ((float *)out_data)[0];
    ai_out[1] = ((float *)out_data)[1];

    HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
    if (ai_out[1] >= JV)
    {
        printf("µøµ¹£¡");
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
        HAL_Delay(3000);
        memset(aiwindow_APitch, 0, 2000);
        memset(aiwindow_GPitch, 0, 2000);
        memset(aiwindow_Ax, 0, 2000);
        memset(aiwindow_Ay, 0, 2000);
        memset(aiwindow_Az, 0, 2000);
        memset(aiwindow_Gx, 0, 2000);
        memset(aiwindow_Gy, 0, 2000);
        memset(aiwindow_Gz, 0, 2000);
        if(BC20flag == 1)
        {
            BC20_SendMes(123,"Fall");
        }
    }
    /* USER CODE END 6 */
}
#ifdef __cplusplus
}
#endif
