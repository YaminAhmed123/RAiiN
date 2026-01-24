struct VSInput {
    float3 color : COLOR0;
    float3 colorx : COLOR1;
};

struct FSOutput {
    float4 color : SV_Target0;
};

[shader("fragment")]
FSOutput main(VSInput input) {
    FSOutput output;
    float constant_value = 1.5;
    output.color = float4(input.color.x + input.colorx.y, input.color.y + input.colorx.z, input.color.z + input.colorx.x, 1.0); // Output the interpolated color
    output.color *= constant_value;
    return output;
}
