/* Auto-generated by utensor cli */
#include "uTensor.h"
#include "params_my_model.hpp"
#include "my_model.hpp"


My_model::My_model () :
op_DequantizeOperator_000()
, op_ReshapeOperator_001({ 1, 800 })
, op_FullyConnectedOperator_002(TFLM::TfLiteFusedActivation::kTfLiteActRelu)
, op_QuantizeOperator_003()
, op_FullyConnectedOperator_004(TFLM::TfLiteFusedActivation::kTfLiteActNone)
, op_DepthwiseSeparableConvOperator_005({ 1, 1 }, VALID, 32, { 1, 1 }, TFLM::TfLiteFusedActivation::kTfLiteActRelu)
, op_MaxPoolOperator_006({ 5, 5 }, { 1, 5, 5, 1 }, VALID)
{
  Context::get_default_context()->set_ram_data_allocator(&ram_allocator);
  Context::get_default_context()->set_metadata_allocator(&metadata_allocator);
  // TODO: moving ROMTensor declarations here
}

void My_model::compute()
{
  // update context in case there are multiple models being run
  Context::get_default_context()->set_ram_data_allocator(&ram_allocator);
  Context::get_default_context()->set_metadata_allocator(&metadata_allocator);
  // start rendering local snippets
  Tensor t_input_1_int80 = new RamTensor({ 1, 28, 28, 1 }, i8);
    int32_t t_input_1_int80_zp = -128;
    float t_input_1_int80_scale = 0.003921569;
    PerTensorQuantizationParams t_input_1_int80_quant_params(t_input_1_int80_zp, t_input_1_int80_scale);
    t_input_1_int80->set_quantization_params(t_input_1_int80_quant_params);


  op_QuantizeOperator_003
    .set_inputs({
        { TflmSymQuantOps::QuantizeOperator<int8_t, float>::input, inputs[input_0].tensor() },
    })
    .set_outputs({
        { TflmSymQuantOps::QuantizeOperator<int8_t, float>::output, t_input_1_int80}
    })
    .eval();

  Tensor t_StatefulPartitionedCallmy_modelconv2dConv2DReadVariableOp0 = new RomTensor({ 1, 3, 3, 32 }, i8, data_StatefulPartitionedCall_my_model_conv2d_Conv2D_ReadVariableOp_0);
    int32_t arr_t_StatefulPartitionedCallmy_modelconv2dConv2DReadVariableOp0_zp[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    float arr_t_StatefulPartitionedCallmy_modelconv2dConv2DReadVariableOp0_scale[32] = { 0.0022965057, 0.003961854, 0.001750327, 0.0041499413, 0.0016950963, 0.0022431654, 0.0032952628, 0.001350477, 0.003253412, 0.002877407, 0.00485543, 0.0021301708, 0.0022865545, 0.002246709, 0.0058361627, 0.0043498315, 0.0034469299, 0.0034273113, 0.0015768212, 0.0022821329, 0.0026361337, 0.0016714067, 0.0031550953, 0.0028917901, 0.004315673, 0.0040093106, 0.0018948448, 0.0030664743, 0.0030591465, 0.0023772824, 0.0030947286, 0.0013230531 };
    PerChannelQuantizationParams t_StatefulPartitionedCallmy_modelconv2dConv2DReadVariableOp0_quant_params(arr_t_StatefulPartitionedCallmy_modelconv2dConv2DReadVariableOp0_zp, arr_t_StatefulPartitionedCallmy_modelconv2dConv2DReadVariableOp0_scale);
    t_StatefulPartitionedCallmy_modelconv2dConv2DReadVariableOp0->set_quantization_params(t_StatefulPartitionedCallmy_modelconv2dConv2DReadVariableOp0_quant_params);


  Tensor t_StatefulPartitionedCallmy_modelconv2dConv2D_bias0 = new RomTensor({ 32 }, i32, data_StatefulPartitionedCall_my_model_conv2d_Conv2D_bias_0);
    int32_t arr_t_StatefulPartitionedCallmy_modelconv2dConv2D_bias0_zp[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    float arr_t_StatefulPartitionedCallmy_modelconv2dConv2D_bias0_scale[32] = { 9.005906e-06, 1.5536683e-05, 6.8640275e-06, 1.627428e-05, 6.6474367e-06, 8.796727e-06, 1.29226e-05, 5.2959886e-06, 1.2758479e-05, 1.128395e-05, 1.9040905e-05, 8.3536115e-06, 8.966881e-06, 8.810624e-06, 2.2886914e-05, 1.7058164e-05, 1.3517373e-05, 1.3440437e-05, 6.183613e-06, 8.949542e-06, 1.033778e-05, 6.5545364e-06, 1.2372923e-05, 1.1340354e-05, 1.6924208e-05, 1.5722788e-05, 7.4307645e-06, 1.202539e-05, 1.19966535e-05, 9.322676e-06, 1.2136191e-05, 5.188444e-06 };
    PerChannelQuantizationParams t_StatefulPartitionedCallmy_modelconv2dConv2D_bias0_quant_params(arr_t_StatefulPartitionedCallmy_modelconv2dConv2D_bias0_zp, arr_t_StatefulPartitionedCallmy_modelconv2dConv2D_bias0_scale);
    t_StatefulPartitionedCallmy_modelconv2dConv2D_bias0->set_quantization_params(t_StatefulPartitionedCallmy_modelconv2dConv2D_bias0_quant_params);


  Tensor t_StatefulPartitionedCallmy_modelconv2dRelu0 = new RamTensor({ 1, 26, 26, 32 }, i8);
    int32_t t_StatefulPartitionedCallmy_modelconv2dRelu0_zp = -128;
    float t_StatefulPartitionedCallmy_modelconv2dRelu0_scale = 0.0052410257;
    PerTensorQuantizationParams t_StatefulPartitionedCallmy_modelconv2dRelu0_quant_params(t_StatefulPartitionedCallmy_modelconv2dRelu0_zp, t_StatefulPartitionedCallmy_modelconv2dRelu0_scale);
    t_StatefulPartitionedCallmy_modelconv2dRelu0->set_quantization_params(t_StatefulPartitionedCallmy_modelconv2dRelu0_quant_params);


  op_DepthwiseSeparableConvOperator_005
    .set_inputs({
        { TflmSymQuantOps::DepthwiseSeparableConvOperator<int8_t>::in, t_input_1_int80 },
        { TflmSymQuantOps::DepthwiseSeparableConvOperator<int8_t>::filter, t_StatefulPartitionedCallmy_modelconv2dConv2DReadVariableOp0 },
        { TflmSymQuantOps::DepthwiseSeparableConvOperator<int8_t>::bias, t_StatefulPartitionedCallmy_modelconv2dConv2D_bias0 },
    })
    .set_outputs({
        { TflmSymQuantOps::DepthwiseSeparableConvOperator<int8_t>::out, t_StatefulPartitionedCallmy_modelconv2dRelu0}
    })
    .eval();

  t_StatefulPartitionedCallmy_modelconv2dConv2DReadVariableOp0.free();

  t_input_1_int80.free();

  t_StatefulPartitionedCallmy_modelconv2dConv2D_bias0.free();

  Tensor t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool0 = new RamTensor({ 1, 5, 5, 32 }, i8);
    int32_t t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool0_zp = -128;
    float t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool0_scale = 0.0052410257;
    PerTensorQuantizationParams t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool0_quant_params(t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool0_zp, t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool0_scale);
    t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool0->set_quantization_params(t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool0_quant_params);


  op_MaxPoolOperator_006
    .set_inputs({
        { ReferenceOperators::MaxPoolOperator<int8_t>::in, t_StatefulPartitionedCallmy_modelconv2dRelu0 },
    })
    .set_outputs({
        { ReferenceOperators::MaxPoolOperator<int8_t>::out, t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool0}
    })
    .eval();

  t_StatefulPartitionedCallmy_modelconv2dRelu0.free();

  Tensor t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool_0_Reshape00 = new RamTensor({ 1, 800 }, i8);
    int32_t t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool_0_Reshape00_zp = -128;
    float t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool_0_Reshape00_scale = 0.0052410257;
    PerTensorQuantizationParams t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool_0_Reshape00_quant_params(t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool_0_Reshape00_zp, t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool_0_Reshape00_scale);
    t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool_0_Reshape00->set_quantization_params(t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool_0_Reshape00_quant_params);


  op_ReshapeOperator_001
    .set_inputs({
        { ReferenceOperators::ReshapeOperator<int8_t>::input, t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool0 },
    })
    .set_outputs({
        { ReferenceOperators::ReshapeOperator<int8_t>::output, t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool_0_Reshape00}
    })
    .eval();

  t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool0.free();

  Tensor t_StatefulPartitionedCallmy_modeldenseMatMulReadVariableOptranspose0 = new RomTensor({ 800, 32 }, i8, data_StatefulPartitionedCall_my_model_dense_MatMul_ReadVariableOp_transpose_0);
    int32_t t_StatefulPartitionedCallmy_modeldenseMatMulReadVariableOptranspose0_zp = 0;
    float t_StatefulPartitionedCallmy_modeldenseMatMulReadVariableOptranspose0_scale = 0.004779708;
    PerTensorQuantizationParams t_StatefulPartitionedCallmy_modeldenseMatMulReadVariableOptranspose0_quant_params(t_StatefulPartitionedCallmy_modeldenseMatMulReadVariableOptranspose0_zp, t_StatefulPartitionedCallmy_modeldenseMatMulReadVariableOptranspose0_scale);
    t_StatefulPartitionedCallmy_modeldenseMatMulReadVariableOptranspose0->set_quantization_params(t_StatefulPartitionedCallmy_modeldenseMatMulReadVariableOptranspose0_quant_params);


  Tensor t_StatefulPartitionedCallmy_modeldenseMatMul_bias0 = new RomTensor({ 32 }, i32, data_StatefulPartitionedCall_my_model_dense_MatMul_bias_0);
    int32_t t_StatefulPartitionedCallmy_modeldenseMatMul_bias0_zp = 0;
    float t_StatefulPartitionedCallmy_modeldenseMatMul_bias0_scale = 2.5050573e-05;
    PerTensorQuantizationParams t_StatefulPartitionedCallmy_modeldenseMatMul_bias0_quant_params(t_StatefulPartitionedCallmy_modeldenseMatMul_bias0_zp, t_StatefulPartitionedCallmy_modeldenseMatMul_bias0_scale);
    t_StatefulPartitionedCallmy_modeldenseMatMul_bias0->set_quantization_params(t_StatefulPartitionedCallmy_modeldenseMatMul_bias0_quant_params);


  Tensor t_StatefulPartitionedCallmy_modeldenseRelu0 = new RamTensor({ 1, 32 }, i8);
    int32_t t_StatefulPartitionedCallmy_modeldenseRelu0_zp = -128;
    float t_StatefulPartitionedCallmy_modeldenseRelu0_scale = 0.04437606;
    PerTensorQuantizationParams t_StatefulPartitionedCallmy_modeldenseRelu0_quant_params(t_StatefulPartitionedCallmy_modeldenseRelu0_zp, t_StatefulPartitionedCallmy_modeldenseRelu0_scale);
    t_StatefulPartitionedCallmy_modeldenseRelu0->set_quantization_params(t_StatefulPartitionedCallmy_modeldenseRelu0_quant_params);


  op_FullyConnectedOperator_002
    .set_inputs({
        { TflmSymQuantOps::FullyConnectedOperator<int8_t>::input, t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool_0_Reshape00 },
        { TflmSymQuantOps::FullyConnectedOperator<int8_t>::filter, t_StatefulPartitionedCallmy_modeldenseMatMulReadVariableOptranspose0 },
        { TflmSymQuantOps::FullyConnectedOperator<int8_t>::bias, t_StatefulPartitionedCallmy_modeldenseMatMul_bias0 },
    })
    .set_outputs({
        { TflmSymQuantOps::FullyConnectedOperator<int8_t>::output, t_StatefulPartitionedCallmy_modeldenseRelu0}
    })
    .eval();

  t_StatefulPartitionedCallmy_modelmax_pooling2dMaxPool_0_Reshape00.free();

  t_StatefulPartitionedCallmy_modeldenseMatMul_bias0.free();

  t_StatefulPartitionedCallmy_modeldenseMatMulReadVariableOptranspose0.free();

  Tensor t_StatefulPartitionedCallmy_modeldense_1MatMulReadVariableOptranspose0 = new RomTensor({ 32, 10 }, i8, data_StatefulPartitionedCall_my_model_dense_1_MatMul_ReadVariableOp_transpose_0);
    int32_t t_StatefulPartitionedCallmy_modeldense_1MatMulReadVariableOptranspose0_zp = 0;
    float t_StatefulPartitionedCallmy_modeldense_1MatMulReadVariableOptranspose0_scale = 0.0046267025;
    PerTensorQuantizationParams t_StatefulPartitionedCallmy_modeldense_1MatMulReadVariableOptranspose0_quant_params(t_StatefulPartitionedCallmy_modeldense_1MatMulReadVariableOptranspose0_zp, t_StatefulPartitionedCallmy_modeldense_1MatMulReadVariableOptranspose0_scale);
    t_StatefulPartitionedCallmy_modeldense_1MatMulReadVariableOptranspose0->set_quantization_params(t_StatefulPartitionedCallmy_modeldense_1MatMulReadVariableOptranspose0_quant_params);


  Tensor t_StatefulPartitionedCallmy_modeldense_1MatMul_bias0 = new RomTensor({ 10 }, i32, data_StatefulPartitionedCall_my_model_dense_1_MatMul_bias_0);
    int32_t t_StatefulPartitionedCallmy_modeldense_1MatMul_bias0_zp = 0;
    float t_StatefulPartitionedCallmy_modeldense_1MatMul_bias0_scale = 0.00020531483;
    PerTensorQuantizationParams t_StatefulPartitionedCallmy_modeldense_1MatMul_bias0_quant_params(t_StatefulPartitionedCallmy_modeldense_1MatMul_bias0_zp, t_StatefulPartitionedCallmy_modeldense_1MatMul_bias0_scale);
    t_StatefulPartitionedCallmy_modeldense_1MatMul_bias0->set_quantization_params(t_StatefulPartitionedCallmy_modeldense_1MatMul_bias0_quant_params);


  Tensor t_Identity_int80 = new RamTensor({ 1, 10 }, i8);
    int32_t t_Identity_int80_zp = 3;
    float t_Identity_int80_scale = 0.113868386;
    PerTensorQuantizationParams t_Identity_int80_quant_params(t_Identity_int80_zp, t_Identity_int80_scale);
    t_Identity_int80->set_quantization_params(t_Identity_int80_quant_params);


  op_FullyConnectedOperator_004
    .set_inputs({
        { TflmSymQuantOps::FullyConnectedOperator<int8_t>::input, t_StatefulPartitionedCallmy_modeldenseRelu0 },
        { TflmSymQuantOps::FullyConnectedOperator<int8_t>::filter, t_StatefulPartitionedCallmy_modeldense_1MatMulReadVariableOptranspose0 },
        { TflmSymQuantOps::FullyConnectedOperator<int8_t>::bias, t_StatefulPartitionedCallmy_modeldense_1MatMul_bias0 },
    })
    .set_outputs({
        { TflmSymQuantOps::FullyConnectedOperator<int8_t>::output, t_Identity_int80}
    })
    .eval();

  t_StatefulPartitionedCallmy_modeldenseRelu0.free();

  t_StatefulPartitionedCallmy_modeldense_1MatMul_bias0.free();

  t_StatefulPartitionedCallmy_modeldense_1MatMulReadVariableOptranspose0.free();

  op_DequantizeOperator_000
    .set_inputs({
        { TflmSymQuantOps::DequantizeOperator<float, int8_t>::a, t_Identity_int80 },
    })
    .set_outputs({
        { TflmSymQuantOps::DequantizeOperator<float, int8_t>::b, outputs[output_0].tensor()}
    })
    .eval();

  t_Identity_int80.free();
  // end of rendering local snippets
}