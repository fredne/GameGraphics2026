#include "Common.hlsl"

float4 PSMain(VertexOut input) : SV_Target
{
    return input.color;
}