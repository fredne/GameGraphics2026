#include "Common.hlsl"
#include "Transform.hlsl"

VertexOut VSMain(VertexIn input)
{
    VertexOut output;
    output.pos = mul(float4(input.pos, 1.0f), MVP);
    output.color = input.color;
	return output;
}
