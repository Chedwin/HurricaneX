struct Input {
	float4 position : SV_POSITION;
	float3 color : COLOR;
};


// this PIXEL shader (or fragment in glsl) returns a colour per pixel

float4 main(Input _input) : SV_TARGET // SV_TARGET = goes to the render target
{
	return float4(_input.color.r, _input.color.g, _input.color.b, 1);
}