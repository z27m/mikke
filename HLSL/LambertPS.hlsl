
#include "Lambert.hlsli"

Texture2D diffuseMap : register(t0);
SamplerState diffuseMapSamplerState : register(s0);

float4 main(VS_OUT pin) : SV_TARGET
{
	float4 color = diffuseMap.Sample(diffuseMapSamplerState, pin.texcoord) *pin.color;

	const float GAMMA = 2.2;
	color.rgb = pow(color.rgb, 1.0f / GAMMA);

	return color;
}

