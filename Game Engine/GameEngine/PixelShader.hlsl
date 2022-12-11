struct PS_INPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	float time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	// Static Color 
	//return float4(input.color, 1.0f);

	// With Animation
	//return float4(lerp(input.color, input.color1, (float)((sin((float)(m_time / (float)500.0f)) + 1.0f) / 2.0f)), 1.0f);
	return float4(lerp(input.color, input.color1, (sin(time) + 1.0f) / 2.0f),1.0f);
}