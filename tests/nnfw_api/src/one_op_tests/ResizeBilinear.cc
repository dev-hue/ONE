/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "GenModelTest.h"

#include <memory>

TEST_F(GenModelTest, OneOp_ResizeBilinear_SizeToConst)
{
  CircleGen cgen;
  std::vector<int32_t> size_data{3, 3};
  uint32_t size_buf = cgen.addBuffer(size_data);
  int size = cgen.addTensor({{1}, circle::TensorType::TensorType_INT32, size_buf});
  int in = cgen.addTensor({{1, 2, 2, 1}, circle::TensorType::TensorType_FLOAT32});
  int out = cgen.addTensor({{1, 3, 3, 1}, circle::TensorType::TensorType_FLOAT32});
  cgen.addOperatorResizeBilinear({{in, size}, {out}});
  cgen.setInputsAndOutputs({in}, {out});

  _context = std::make_unique<GenModelTestContext>(cgen.finish());
  _context->addTestCase(uniformTCD<float>(
      {{1, 1, 2, 2}}, {{1, 1, 1, 1.666666667, 1.666666667, 1.666666667, 2, 2, 2}}));
  _context->setBackends({"acl_cl", "acl_neon", "cpu"});

  SUCCEED();
}

TEST_F(GenModelTest, OneOp_ResizeBilinear_SizeToVar)
{
  CircleGen cgen;
  int size = cgen.addTensor({{2}, circle::TensorType::TensorType_INT32});
  int in = cgen.addTensor({{1, 2, 2, 1}, circle::TensorType::TensorType_FLOAT32});
  int out = cgen.addTensor({{1, 2, 1}, circle::TensorType::TensorType_FLOAT32});
  cgen.addOperatorResizeBilinear({{in, size}, {out}});
  cgen.setInputsAndOutputs({in, size}, {out});

  _context = std::make_unique<GenModelTestContext>(cgen.finish());
  TestCaseData tcd;
  tcd.addInput(std::vector<int32_t>{3, 3});
  tcd.addInput(std::vector<float>{1, 1, 2, 2});
  tcd.addOutput(std::vector<float>{1, 1, 1, 1.666666667, 1.666666667, 1.666666667, 2, 2, 2});
  _context->setBackends({"cpu"});

  SUCCEED();
}

TEST_F(GenModelTest, neg_OneOp_ResizeBilinear_InvalidSizeVal)
{
  CircleGen cgen;
  std::vector<int32_t> size_data{-3, 3};
  uint32_t size_buf = cgen.addBuffer(size_data);
  int size = cgen.addTensor({{1}, circle::TensorType::TensorType_INT32, size_buf});
  int in = cgen.addTensor({{1, 2, 2, 1}, circle::TensorType::TensorType_FLOAT32});
  int out = cgen.addTensor({{1, 2, 1}, circle::TensorType::TensorType_FLOAT32});
  cgen.addOperatorResizeBilinear({{in, size}, {out}});
  cgen.setInputsAndOutputs({in}, {out});

  _context = std::make_unique<GenModelTestContext>(cgen.finish());
  _context->setBackends({"cpu"});
  _context->setCompileFail();

  SUCCEED();
}