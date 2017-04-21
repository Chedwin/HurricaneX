
struct Input {
	// the video card needs this POSITION name
	// similiar to gl_Position in GLSL
	float2 position : POSITION; 

	float3 color : COLOR;
};


struct Output {
	float4 position : SV_POSITION; // sent down the pipeline
	float3 color : COLOR;
};

Output main(Input input) 
{
	Output output;

	output.position = float4(input.position.x, input.position.y, 0, 1);
	output.color = input.color;

	return output;
}