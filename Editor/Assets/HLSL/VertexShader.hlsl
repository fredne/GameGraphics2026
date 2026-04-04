#include "Common.hlsl"
#include "Constant.hlsl"

VertexOut VSMain(VertexIn input)
{
    VertexOut output;
    output.pos = mul(float4(input.pos, 1.0f), MVP);
    output.uv = input.uv;
	return output;
}
