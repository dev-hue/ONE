/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// TODO consider relocate this file

#ifndef __LUCI_CIRLE_NODE_CLONE__
#define __LUCI_CIRLE_NODE_CLONE__

#include <luci/IR/CircleNodes.h>
#include <luci/IR/CircleNodeVisitor.h>

#include <loco/IR/Graph.h>

namespace luci
{

/**
 * @brief Return a new cloned CircleNode object with same attributes value of node to graph.
 * @note  Each visit implementation must copy node specific attributes.
 */
CircleNode *clone_node(const CircleNode *node, loco::Graph *graph);

/**
 * @brief Copy common attributes of CircleNode from src to dst.
 * @note  Attributes of specific node type like keep_dims() of CircleSum are
 *        not copied.
 */
void copy_common_attributes(const luci::CircleNode *src, luci::CircleNode *dst);

} // namespace luci

#endif // __LUCI_CIRLE_NODE_CLONE__
