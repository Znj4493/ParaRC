#!/bin/bash

# 缓存优化验证脚本
# 用于测试和验证缓存优化的效果

echo "=========================================="
echo "  GenMLP 缓存优化 - 验证脚本"
echo "=========================================="
echo ""

# 编译
echo "[1/3] 编译代码..."
cd D:\XMU\Erasure-Code\ParaRC
./compile.sh 2>&1 | grep -E "error|warning" || echo "✓ 编译成功"

echo ""
echo "[2/3] 运行测试案例..."
echo ""

# 测试案例1：Clay 编码 6-4-8
echo "--- 测试案例1: Clay 6-4-8 ---"
time ./GenMLP Clay 6 4 8 0

echo ""

# 测试案例2：Clay 编码 9-6-27
echo "--- 测试案例2: Clay 9-6-27 ---"
time ./GenMLP Clay 9 6 27 0

echo ""

# 测试案例3：Butterfly 编码
echo "--- 测试案例3: Butterfly 8-6-32 ---"
time ./GenMLP Butterfly 8 6 32 0

echo ""
echo "[3/3] 验证完成"
echo ""
echo "=========================================="
echo "缓存统计信息已在上方输出"
echo "如要查看更详细的缓存命中率，请修改代码取消注释调试输出"
echo "=========================================="

